use std::collections::HashMap;

use anyhow::{anyhow, Result};
use cranelift::prelude::*;
use cranelift::codegen::ir::{StackSlotData, StackSlotKind};
use cranelift_module::{FuncId, Linkage, Module};
use cranelift_object::{ObjectBuilder, ObjectModule};

use crate::ast;
use crate::shell_codegen::ShellCompiler;

// Free function to convert types (avoids borrow issues)
fn convert_ast_type(ty: &ast::Type) -> types::Type {
    match ty {
        ast::Type::I32 => types::I32,
        ast::Type::I64 => types::I64,
        ast::Type::F32 => types::F32,
        ast::Type::F64 => types::F64,
        ast::Type::Bool => types::I8,
        _ => types::I64, // Pointers, refs, arrays, structs all use I64 (pointer)
    }
}

// Get the size of a type in bytes
fn type_size(ty: &ast::Type, structs: &HashMap<String, StructLayout>) -> u32 {
    match ty {
        ast::Type::I32 => 4,
        ast::Type::I64 => 8,
        ast::Type::F32 => 4,
        ast::Type::F64 => 8,
        ast::Type::Bool => 1,
        ast::Type::Array(elem, count) => type_size(elem, structs) * (*count as u32),
        ast::Type::Named(name) => {
            structs.get(name).map(|s| s.size).unwrap_or(8)
        }
        _ => 8, // Default pointer size
    }
}

#[derive(Clone, Debug)]
pub struct StructLayout {
    pub size: u32,
    pub fields: Vec<(String, u32, ast::Type)>, // (name, offset, type)
}

fn compute_struct_layout(def: &ast::StructDef, structs: &HashMap<String, StructLayout>) -> StructLayout {
    let mut offset = 0u32;
    let mut fields = Vec::new();
    
    for field in &def.fields {
        let size = type_size(&field.ty, structs);
        // Simple alignment: align to type size (max 8)
        let align = size.min(8);
        offset = (offset + align - 1) & !(align - 1);
        
        fields.push((field.name.clone(), offset, field.ty.clone()));
        offset += size;
    }
    
    // Align total size to 8 bytes
    let size = (offset + 7) & !7;
    
    StructLayout { size, fields }
}

pub struct Compiler {
    module: ObjectModule,
    ctx: codegen::Context,
    functions: HashMap<String, FuncId>,
    structs: HashMap<String, StructLayout>,
}

impl Compiler {
    pub fn new() -> Result<Self> {
        let mut flag_builder = settings::builder();
        flag_builder.set("opt_level", "speed").unwrap();
        
        let isa_builder = cranelift_native::builder()
            .map_err(|e| anyhow!("Failed to create ISA builder: {}", e))?;
        
        let isa = isa_builder
            .finish(settings::Flags::new(flag_builder))
            .map_err(|e| anyhow!("Failed to create ISA: {}", e))?;
        
        let builder = ObjectBuilder::new(
            isa,
            "bunker_module",
            cranelift_module::default_libcall_names(),
        )
        .map_err(|e| anyhow!("Failed to create object builder: {}", e))?;
        
        let module = ObjectModule::new(builder);
        let ctx = module.make_context();
        
        Ok(Self {
            module,
            ctx,
            functions: HashMap::new(),
            structs: HashMap::new(),
        })
    }
    
    pub fn compile_kernel(&mut self, kernel: &ast::Kernel) -> Result<()> {
        // First pass: collect struct definitions
        for item in &kernel.items {
            if let ast::KernelItem::Struct(s) = item {
                let layout = compute_struct_layout(s, &self.structs);
                self.structs.insert(s.name.clone(), layout);
            }
        }
        
        // Second pass: declare all functions
        for item in &kernel.items {
            if let ast::KernelItem::Function(func) = item {
                self.declare_function(func)?;
            }
        }
        
        // Third pass: define all functions
        for item in &kernel.items {
            if let ast::KernelItem::Function(func) = item {
                self.compile_function(func)?;
            }
        }
        
        Ok(())
    }
    
    fn declare_function(&mut self, func: &ast::Function) -> Result<FuncId> {
        let mut sig = self.module.make_signature();
        
        for param in &func.params {
            sig.params.push(AbiParam::new(convert_ast_type(&param.ty)));
        }
        
        if let Some(ref ret_ty) = func.return_type {
            sig.returns.push(AbiParam::new(convert_ast_type(ret_ty)));
        }
        
        let linkage = if func.name == "main" {
            Linkage::Export
        } else {
            Linkage::Local
        };
        
        let func_id = self.module
            .declare_function(&func.name, linkage, &sig)
            .map_err(|e| anyhow!("Failed to declare function {}: {}", func.name, e))?;
        
        self.functions.insert(func.name.clone(), func_id);
        Ok(func_id)
    }
    
    fn compile_function(&mut self, func: &ast::Function) -> Result<()> {
        let func_id = *self.functions.get(&func.name)
            .ok_or_else(|| anyhow!("Function {} not declared", func.name))?;
        
        self.ctx.func.signature = self.module.declarations()
            .get_function_decl(func_id).signature.clone();
        
        let param_types: Vec<_> = func.params.iter()
            .map(|p| convert_ast_type(&p.ty))
            .collect();
        
        let mut builder_ctx = FunctionBuilderContext::new();
        {
            let mut builder = FunctionBuilder::new(&mut self.ctx.func, &mut builder_ctx);
            
            let entry_block = builder.create_block();
            builder.append_block_params_for_function_params(entry_block);
            builder.switch_to_block(entry_block);
            // Don't seal here - seal all at once after finalize
            
            let mut variables: HashMap<String, Variable> = HashMap::new();
            let mut var_index = 0u32;
            
            for (i, param) in func.params.iter().enumerate() {
                let var = Variable::new(var_index as usize);
                var_index += 1;
                builder.declare_var(var, param_types[i]);
                let val = builder.block_params(entry_block)[i];
                builder.def_var(var, val);
                variables.insert(param.name.clone(), var);
            }
            
            // Compile the body inline (no separate struct to avoid borrow issues)
            let mut returned = false;
            compile_block_inline(&mut builder, &mut self.module, &self.functions, &self.structs,
                                &mut variables, &mut var_index, &func.body, &mut returned)?;
            
            // Add fallback return if needed (only if no explicit return was emitted)
            if !returned {
                builder.ins().return_(&[]);
            }
            
            // Seal all blocks at once
            builder.seal_all_blocks();
            builder.finalize();
        }
        
        self.module
            .define_function(func_id, &mut self.ctx)
            .map_err(|e| anyhow!("Failed to define function {}: {:?}", func.name, e))?;
        
        self.module.clear_context(&mut self.ctx);
        Ok(())
    }

    pub fn compile_shell(&mut self, shell: &ast::Shell) -> Result<()> {
        let mut shell_compiler = ShellCompiler::new(
            &mut self.module,
            &mut self.ctx,
            &self.functions,
        );
        shell_compiler.compile_shell(shell)
    }
    
    pub fn finish(self) -> Result<Vec<u8>> {
        let product = self.module.finish();
        product.emit().map_err(|e| anyhow!("Failed to emit object: {}", e))
    }
}

fn compile_block_inline(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    variables: &mut HashMap<String, Variable>,
    var_index: &mut u32,
    block: &ast::Block,
    returned: &mut bool,
) -> Result<()> {
    for stmt in &block.statements {
        if *returned {
            break;
        }
        compile_stmt_inline(builder, module, functions, structs, variables, var_index, stmt, returned)?;
    }
    Ok(())
}

fn compile_stmt_inline(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    variables: &mut HashMap<String, Variable>,
    var_index: &mut u32,
    stmt: &ast::Stmt,
    returned: &mut bool,
) -> Result<()> {
    match stmt {
        ast::Stmt::Let { name, ty, value } => {
            let val = compile_expr_inline(builder, module, functions, structs, variables, value)?;
            let var = Variable::new(*var_index as usize);
            *var_index += 1;
            
            let var_type = if let Some(t) = ty {
                convert_ast_type(t)
            } else {
                builder.func.dfg.value_type(val)
            };
            
            builder.declare_var(var, var_type);
            builder.def_var(var, val);
            variables.insert(name.clone(), var);
        }
        ast::Stmt::Assign { target, value } => {
            let val = compile_expr_inline(builder, module, functions, structs, variables, value)?;
            if let ast::Expr::Ident(name) = target {
                if let Some(&var) = variables.get(name) {
                    builder.def_var(var, val);
                }
            }
        }
        ast::Stmt::Return(expr) => {
            if let Some(e) = expr {
                let val = compile_expr_inline(builder, module, functions, structs, variables, e)?;
                builder.ins().return_(&[val]);
            } else {
                builder.ins().return_(&[]);
            }
            *returned = true;
        }
        ast::Stmt::Expr(expr) => {
            compile_expr_inline(builder, module, functions, structs, variables, expr)?;
        }
        _ => {}
    }
    Ok(())
}

fn compile_expr_inline(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    variables: &HashMap<String, Variable>,
    expr: &ast::Expr,
) -> Result<Value> {
    match expr {
        ast::Expr::Literal(lit) => compile_literal_inline(builder, lit),
        ast::Expr::Ident(name) => {
            if let Some(&var) = variables.get(name) {
                Ok(builder.use_var(var))
            } else {
                Err(anyhow!("Undefined variable: {}", name))
            }
        }
        ast::Expr::Binary { op, left, right } => {
            let lhs = compile_expr_inline(builder, module, functions, structs, variables, left)?;
            let rhs = compile_expr_inline(builder, module, functions, structs, variables, right)?;
            
            let result = match op {
                ast::BinaryOp::Add => builder.ins().iadd(lhs, rhs),
                ast::BinaryOp::Sub => builder.ins().isub(lhs, rhs),
                ast::BinaryOp::Mul => builder.ins().imul(lhs, rhs),
                ast::BinaryOp::Div => builder.ins().sdiv(lhs, rhs),
                ast::BinaryOp::Mod => builder.ins().srem(lhs, rhs),
                ast::BinaryOp::Eq => builder.ins().icmp(IntCC::Equal, lhs, rhs),
                ast::BinaryOp::Ne => builder.ins().icmp(IntCC::NotEqual, lhs, rhs),
                ast::BinaryOp::Lt => builder.ins().icmp(IntCC::SignedLessThan, lhs, rhs),
                ast::BinaryOp::Le => builder.ins().icmp(IntCC::SignedLessThanOrEqual, lhs, rhs),
                ast::BinaryOp::Gt => builder.ins().icmp(IntCC::SignedGreaterThan, lhs, rhs),
                ast::BinaryOp::Ge => builder.ins().icmp(IntCC::SignedGreaterThanOrEqual, lhs, rhs),
                ast::BinaryOp::And => builder.ins().band(lhs, rhs),
                ast::BinaryOp::Or => builder.ins().bor(lhs, rhs),
                ast::BinaryOp::As => lhs,
            };
            Ok(result)
        }
        ast::Expr::Unary { op, expr: inner } => {
            let val = compile_expr_inline(builder, module, functions, structs, variables, inner)?;
            let result = match op {
                ast::UnaryOp::Neg => builder.ins().ineg(val),
                ast::UnaryOp::Not => builder.ins().bnot(val),
            };
            Ok(result)
        }
        ast::Expr::Call { func, args } => {
            if let ast::Expr::Ident(name) = func.as_ref() {
                // Skip built-in functions for now
                if matches!(name.as_str(), "log" | "print" | "println" | "panic" | "assert") {
                    return Ok(builder.ins().iconst(types::I32, 0));
                }
                if let Some(&func_id) = functions.get(name) {
                    let func_ref = module.declare_func_in_func(func_id, builder.func);
                    
                    let mut arg_vals = vec![];
                    for arg in args {
                        arg_vals.push(compile_expr_inline(builder, module, functions, structs, variables, arg)?);
                    }
                    
                    let call = builder.ins().call(func_ref, &arg_vals);
                    let results = builder.inst_results(call);
                    
                    if results.is_empty() {
                        Ok(builder.ins().iconst(types::I32, 0))
                    } else {
                        Ok(results[0])
                    }
                } else {
                    Err(anyhow!("Undefined function: {}", name))
                }
            } else {
                Err(anyhow!("Invalid function call"))
            }
        }
        ast::Expr::Index { expr: arr, index } => {
            // Array indexing: arr[index]
            let arr_ptr = compile_expr_inline(builder, module, functions, structs, variables, arr)?;
            let idx = compile_expr_inline(builder, module, functions, structs, variables, index)?;
            // For now assume i32 arrays, so element size is 4
            let elem_size = builder.ins().iconst(types::I64, 4);
            let idx_ext = builder.ins().sextend(types::I64, idx);
            let offset = builder.ins().imul(idx_ext, elem_size);
            let elem_addr = builder.ins().iadd(arr_ptr, offset);
            Ok(builder.ins().load(types::I32, MemFlags::new(), elem_addr, 0))
        }
        ast::Expr::Field { expr: obj, field } => {
            // Field access: obj.field
            let obj_ptr = compile_expr_inline(builder, module, functions, structs, variables, obj)?;
            // For now, we need to find the struct type and field offset
            // This is simplified - in a real compiler we'd track types through the AST
            for (_name, layout) in structs {
                for (fname, offset, fty) in &layout.fields {
                    if fname == field {
                        let elem_type = convert_ast_type(fty);
                        return Ok(builder.ins().load(elem_type, MemFlags::new(), obj_ptr, *offset as i32));
                    }
                }
            }
            // Fallback - just return 0
            Ok(builder.ins().iconst(types::I32, 0))
        }
        ast::Expr::Struct { name, fields: _ } => {
            // Struct construction - allocate on stack and return pointer
            if let Some(layout) = structs.get(name) {
                let slot = builder.create_sized_stack_slot(StackSlotData::new(
                    StackSlotKind::ExplicitSlot,
                    layout.size,
                    0,
                ));
                let ptr = builder.ins().stack_addr(types::I64, slot, 0);
                // TODO: Initialize fields
                Ok(ptr)
            } else {
                Ok(builder.ins().iconst(types::I64, 0))
            }
        }
        _ => Ok(builder.ins().iconst(types::I32, 0)),
    }
}

fn compile_literal_inline(builder: &mut FunctionBuilder, lit: &ast::Literal) -> Result<Value> {
    match lit {
        ast::Literal::Int(n) => Ok(builder.ins().iconst(types::I32, *n as i64)),
        ast::Literal::Float(f) => Ok(builder.ins().f64const(*f)),
        ast::Literal::Bool(b) => Ok(builder.ins().iconst(types::I8, if *b { 1 } else { 0 })),
        _ => Ok(builder.ins().iconst(types::I32, 0)),
    }
}
