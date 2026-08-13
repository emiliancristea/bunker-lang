use std::collections::HashMap;

use anyhow::{anyhow, Result};
use cranelift::prelude::*;
use cranelift_module::{FuncId, Linkage, Module};
use cranelift_object::{ObjectBuilder, ObjectModule};

use crate::shell_codegen::ShellCompiler;
use crate::{ast, builtins};

// Free function to convert types (avoids borrow issues)
fn convert_ast_type(ty: &ast::Type) -> types::Type {
    match ty {
        ast::Type::I32 => types::I32,
        ast::Type::I64 => types::I64,
        ast::Type::F32 => types::F32,
        ast::Type::F64 => types::F64,
        ast::Type::Bool => types::I8,
        ast::Type::Option(_) => types::I64,
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
        ast::Type::Option(_) => 8,
        // Arrays are represented as pointers in codegen today.
        ast::Type::Array(_, _) => 8,
        ast::Type::Named(name) => structs.get(name).map(|s| s.size).unwrap_or(8),
        _ => 8, // Default pointer size
    }
}

#[derive(Clone, Debug)]
pub struct StructLayout {
    pub size: u32,
    pub fields: Vec<(String, u32, ast::Type)>, // (name, offset, type)
}

fn compute_struct_layout(
    def: &ast::StructDef,
    structs: &HashMap<String, StructLayout>,
) -> StructLayout {
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
    fn_sigs: HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    alloc_func: FuncId,
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

        let mut module = ObjectModule::new(builder);
        let alloc_func = declare_alloc_func(&mut module)?;
        let ctx = module.make_context();

        Ok(Self {
            module,
            ctx,
            functions: HashMap::new(),
            structs: HashMap::new(),
            fn_sigs: HashMap::new(),
            alloc_func,
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

        // Second pass: collect function signatures and declare all functions
        for item in &kernel.items {
            if let ast::KernelItem::Function(func) = item {
                let param_types = func.params.iter().map(|p| p.ty.clone()).collect();
                self.fn_sigs
                    .insert(func.name.clone(), (param_types, func.return_type.clone()));
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

        let func_id = self
            .module
            .declare_function(&func.name, linkage, &sig)
            .map_err(|e| anyhow!("Failed to declare function {}: {}", func.name, e))?;

        self.functions.insert(func.name.clone(), func_id);
        Ok(func_id)
    }

    fn compile_function(&mut self, func: &ast::Function) -> Result<()> {
        let func_id = *self
            .functions
            .get(&func.name)
            .ok_or_else(|| anyhow!("Function {} not declared", func.name))?;

        self.ctx.func.signature = self
            .module
            .declarations()
            .get_function_decl(func_id)
            .signature
            .clone();

        let param_types: Vec<_> = func
            .params
            .iter()
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
            let mut var_types: HashMap<String, ast::Type> = HashMap::new();

            for (i, param) in func.params.iter().enumerate() {
                let var = Variable::new(var_index as usize);
                var_index += 1;
                builder.declare_var(var, param_types[i]);
                let val = builder.block_params(entry_block)[i];
                builder.def_var(var, val);
                variables.insert(param.name.clone(), var);
                var_types.insert(param.name.clone(), param.ty.clone());
            }

            // Compile the body inline (no separate struct to avoid borrow issues)
            let mut returned = false;
            let mut defer_stack: Vec<Vec<ast::Block>> = Vec::new();
            compile_block_inline(
                &mut builder,
                &mut self.module,
                self.alloc_func,
                &self.functions,
                &self.structs,
                &self.fn_sigs,
                &mut variables,
                &mut var_types,
                &mut var_index,
                &func.body,
                &mut returned,
                &mut defer_stack,
                None, // loop_exit - not in a loop
                None, // loop_continue - not in a loop
            )?;

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
        let mut shell_compiler =
            ShellCompiler::new(&mut self.module, &mut self.ctx, &self.functions);
        shell_compiler.compile_shell(shell)
    }

    pub fn finish(self) -> Result<Vec<u8>> {
        let product = self.module.finish();
        product
            .emit()
            .map_err(|e| anyhow!("Failed to emit object: {}", e))
    }
}

#[allow(clippy::too_many_arguments)]
fn compile_block_inline(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    alloc_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    block: &ast::Block,
    returned: &mut bool,
    defer_stack: &mut Vec<Vec<ast::Block>>,
    loop_exit: Option<Block>,
    loop_continue: Option<Block>,
) -> Result<()> {
    defer_stack.push(Vec::new());
    for stmt in &block.statements {
        if *returned {
            break;
        }
        compile_stmt_inline(
            builder,
            module,
            alloc_func,
            functions,
            structs,
            fn_sigs,
            variables,
            var_types,
            var_index,
            stmt,
            returned,
            defer_stack,
            loop_exit,
            loop_continue,
        )?;
    }
    if !*returned {
        if let Some(defers) = defer_stack.last() {
            emit_defer_blocks(
                builder, module, alloc_func, functions, structs, fn_sigs, variables, var_types,
                var_index, defers,
            )?;
        }
    }
    defer_stack.pop();
    Ok(())
}

#[allow(clippy::too_many_arguments)]
fn compile_stmt_inline(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    alloc_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    stmt: &ast::Stmt,
    returned: &mut bool,
    defer_stack: &mut Vec<Vec<ast::Block>>,
    loop_exit: Option<Block>,
    loop_continue: Option<Block>,
) -> Result<()> {
    match stmt {
        ast::Stmt::Let { name, ty, value } => {
            let mut val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                value,
            )?;
            let var = Variable::new(*var_index as usize);
            *var_index += 1;

            let inferred_type = if let Some(t) = ty {
                t.clone()
            } else {
                infer_expr_type(value, var_types, structs, fn_sigs)
            };
            var_types.insert(name.clone(), inferred_type.clone());

            let var_type = if let Some(t) = ty {
                convert_ast_type(t)
            } else {
                convert_ast_type(&inferred_type)
            };

            val = cast_value(builder, val, var_type);

            builder.declare_var(var, var_type);
            builder.def_var(var, val);
            variables.insert(name.clone(), var);
        }
        ast::Stmt::Assign { target, value } => {
            let val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                value,
            )?;
            match target {
                ast::Expr::Ident(name) => {
                    if let Some(&var) = variables.get(name) {
                        let cur = builder.use_var(var);
                        let var_ty = builder.func.dfg.value_type(cur);
                        let val = cast_value(builder, val, var_ty);
                        builder.def_var(var, val);
                    }
                }
                ast::Expr::Field { expr, field } => {
                    let obj_ptr = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        expr,
                    )?;
                    if let Some((offset, ty)) = resolve_field(structs, expr, field, var_types) {
                        let val = cast_value(builder, val, convert_ast_type(&ty));
                        builder
                            .ins()
                            .store(MemFlags::new(), val, obj_ptr, offset as i32);
                    }
                }
                ast::Expr::Index { expr, index } => {
                    let arr_ptr = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        expr,
                    )?;
                    let idx = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        index,
                    )?;
                    let (elem_ty, elem_size_bytes) =
                        infer_array_elem_type(expr, var_types, structs, fn_sigs)
                            .map(|ty| {
                                let size = type_size(&ty, structs);
                                (ty, size)
                            })
                            .unwrap_or((ast::Type::I32, 4));
                    let val = cast_value(builder, val, convert_ast_type(&elem_ty));
                    let idx = cast_value(builder, idx, types::I32);
                    let elem_size = builder.ins().iconst(types::I64, elem_size_bytes as i64);
                    let idx_ext = builder.ins().sextend(types::I64, idx);
                    let offset = builder.ins().imul(idx_ext, elem_size);
                    let elem_addr = builder.ins().iadd(arr_ptr, offset);
                    builder.ins().store(MemFlags::new(), val, elem_addr, 0);
                }
                _ => {}
            }
        }
        ast::Stmt::If {
            condition,
            then_block,
            else_block,
        } => {
            let cond_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                condition,
            )?;
            let cond_val = bool_value_to_i8(builder, cond_val)?;

            let then_bb = builder.create_block();
            let else_bb = builder.create_block();
            let merge_bb = builder.create_block();

            builder.ins().brif(cond_val, then_bb, &[], else_bb, &[]);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();

            builder.switch_to_block(then_bb);
            *variables = parent_vars.clone();
            *var_types = parent_types.clone();
            let mut then_returned = false;
            compile_block_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                then_block,
                &mut then_returned,
                defer_stack,
                loop_exit,
                loop_continue,
            )?;
            if !then_returned {
                builder.ins().jump(merge_bb, &[]);
            }

            builder.switch_to_block(else_bb);
            *variables = parent_vars.clone();
            *var_types = parent_types.clone();
            let mut else_returned = false;
            if let Some(else_block) = else_block {
                compile_block_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    else_block,
                    &mut else_returned,
                    defer_stack,
                    loop_exit,
                    loop_continue,
                )?;
            }
            if !else_returned {
                builder.ins().jump(merge_bb, &[]);
            }

            *variables = parent_vars;
            *var_types = parent_types;
            if then_returned && else_returned {
                *returned = true;
                return Ok(());
            }

            builder.switch_to_block(merge_bb);
        }
        ast::Stmt::For { var, iter, body } => {
            // Check if iterator is a range expression
            if let ast::Expr::Range {
                start,
                end,
                inclusive,
            } = iter
            {
                // Range-based for loop: for i in start..end or start..=end
                let start_val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    start,
                )?;
                let end_val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    end,
                )?;

                // Infer the element type from the start expression
                let elem_ty = infer_expr_type(start, var_types, structs, fn_sigs);
                let cr_type = convert_ast_type(&elem_ty);

                // For inclusive ranges, add 1 to end
                let end_val = if *inclusive {
                    builder.ins().iadd_imm(end_val, 1)
                } else {
                    end_val
                };

                // Create the loop index variable (initialized to start)
                let idx_var = Variable::new(*var_index as usize);
                *var_index += 1;
                builder.declare_var(idx_var, cr_type);
                builder.def_var(idx_var, start_val);

                let loop_bb = builder.create_block();
                let body_bb = builder.create_block();
                let continue_bb = builder.create_block(); // continue jumps here
                let exit_bb = builder.create_block();

                builder.ins().jump(loop_bb, &[]);

                // Loop header: check if idx < end
                builder.switch_to_block(loop_bb);
                let idx_val = builder.use_var(idx_var);
                let cond = builder.ins().icmp(IntCC::SignedLessThan, idx_val, end_val);
                builder.ins().brif(cond, body_bb, &[], exit_bb, &[]);

                // Loop body
                builder.switch_to_block(body_bb);
                let parent_vars = variables.clone();
                let parent_types = var_types.clone();

                // Bind the loop variable to the current index value
                let loop_var = Variable::new(*var_index as usize);
                *var_index += 1;
                builder.declare_var(loop_var, cr_type);
                variables.insert(var.clone(), loop_var);
                var_types.insert(var.clone(), elem_ty.clone());

                let idx_val = builder.use_var(idx_var);
                builder.def_var(loop_var, idx_val);

                let mut body_returned = false;
                compile_block_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    body,
                    &mut body_returned,
                    defer_stack,
                    Some(exit_bb),
                    Some(continue_bb),
                )?;

                if !body_returned {
                    builder.ins().jump(continue_bb, &[]);
                }

                // Continue block: increment index and jump to loop header
                builder.switch_to_block(continue_bb);
                let idx_val = builder.use_var(idx_var);
                let next = builder.ins().iadd_imm(idx_val, 1);
                builder.def_var(idx_var, next);
                builder.ins().jump(loop_bb, &[]);

                *variables = parent_vars;
                *var_types = parent_types;

                builder.switch_to_block(exit_bb);
            } else {
                // Array-based for loop (existing implementation)
                let arr_ptr = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    iter,
                )?;

                let Some(elem_ty) = infer_array_elem_type(iter, var_types, structs, fn_sigs) else {
                    return Err(anyhow!("for-loop requires an array or range expression"));
                };
                let Some(len) = infer_array_len(iter, var_types, structs, fn_sigs) else {
                    return Err(anyhow!("for-loop requires a statically sized array"));
                };

                let idx_var = Variable::new(*var_index as usize);
                *var_index += 1;
                builder.declare_var(idx_var, types::I64);
                let zero = builder.ins().iconst(types::I64, 0);
                builder.def_var(idx_var, zero);

                let loop_bb = builder.create_block();
                let body_bb = builder.create_block();
                let continue_bb = builder.create_block(); // continue jumps here
                let exit_bb = builder.create_block();

                builder.ins().jump(loop_bb, &[]);

                builder.switch_to_block(loop_bb);
                let idx_val = builder.use_var(idx_var);
                let len_val = builder.ins().iconst(types::I64, len as i64);
                let cond = builder
                    .ins()
                    .icmp(IntCC::UnsignedLessThan, idx_val, len_val);
                builder.ins().brif(cond, body_bb, &[], exit_bb, &[]);

                builder.switch_to_block(body_bb);
                let parent_vars = variables.clone();
                let parent_types = var_types.clone();

                let loop_var = Variable::new(*var_index as usize);
                *var_index += 1;
                builder.declare_var(loop_var, convert_ast_type(&elem_ty));
                variables.insert(var.clone(), loop_var);
                var_types.insert(var.clone(), elem_ty.clone());

                let idx_val = builder.use_var(idx_var);
                let elem_size = type_size(&elem_ty, structs) as i64;
                let elem_size_val = builder.ins().iconst(types::I64, elem_size);
                let offset = builder.ins().imul(idx_val, elem_size_val);
                let elem_addr = builder.ins().iadd(arr_ptr, offset);
                let elem_val =
                    builder
                        .ins()
                        .load(convert_ast_type(&elem_ty), MemFlags::new(), elem_addr, 0);
                builder.def_var(loop_var, elem_val);

                let mut body_returned = false;
                compile_block_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    body,
                    &mut body_returned,
                    defer_stack,
                    Some(exit_bb),
                    Some(continue_bb),
                )?;

                if !body_returned {
                    builder.ins().jump(continue_bb, &[]);
                }

                // Continue block: increment index and jump to loop header
                builder.switch_to_block(continue_bb);
                let idx_val = builder.use_var(idx_var);
                let next = builder.ins().iadd_imm(idx_val, 1);
                builder.def_var(idx_var, next);
                builder.ins().jump(loop_bb, &[]);

                *variables = parent_vars;
                *var_types = parent_types;

                builder.switch_to_block(exit_bb);
            }
        }
        ast::Stmt::Loop(body) => {
            let loop_bb = builder.create_block();
            let exit_bb = builder.create_block();

            builder.ins().jump(loop_bb, &[]);
            builder.switch_to_block(loop_bb);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();

            let mut body_returned = false;
            compile_block_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                body,
                &mut body_returned,
                defer_stack,
                Some(exit_bb), // break jumps to exit
                Some(loop_bb), // continue jumps to loop header
            )?;

            if !body_returned {
                builder.ins().jump(loop_bb, &[]);
            }

            *variables = parent_vars;
            *var_types = parent_types;

            builder.switch_to_block(exit_bb);
        }
        ast::Stmt::While { condition, body } => {
            let loop_header = builder.create_block();
            let loop_body = builder.create_block();
            let exit_bb = builder.create_block();

            builder.ins().jump(loop_header, &[]);
            builder.switch_to_block(loop_header);

            // Evaluate condition
            let cond_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                condition,
            )?;
            let cond_bool = bool_value_to_i8(builder, cond_val)?;
            let cond = builder.ins().icmp_imm(IntCC::NotEqual, cond_bool, 0);
            builder.ins().brif(cond, loop_body, &[], exit_bb, &[]);

            builder.switch_to_block(loop_body);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();

            let mut body_returned = false;
            compile_block_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                body,
                &mut body_returned,
                defer_stack,
                Some(exit_bb),     // break jumps to exit
                Some(loop_header), // continue jumps to loop header (re-check condition)
            )?;

            if !body_returned {
                builder.ins().jump(loop_header, &[]);
            }

            *variables = parent_vars;
            *var_types = parent_types;

            builder.switch_to_block(exit_bb);
        }
        ast::Stmt::Break => {
            if let Some(exit_block) = loop_exit {
                builder.ins().jump(exit_block, &[]);
                *returned = true; // Mark as returned to stop further code gen in this block
            } else {
                return Err(anyhow!("break statement outside of loop"));
            }
        }
        ast::Stmt::Continue => {
            if let Some(continue_block) = loop_continue {
                builder.ins().jump(continue_block, &[]);
                *returned = true; // Mark as returned to stop further code gen in this block
            } else {
                return Err(anyhow!("continue statement outside of loop"));
            }
        }
        ast::Stmt::Match { expr, arms } => {
            if arms.is_empty() {
                return Ok(());
            }

            let match_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                expr,
            )?;
            let match_expr_ty = infer_expr_type(expr, var_types, structs, fn_sigs);

            let merge_bb = builder.create_block();
            let default_bb = builder.create_block();

            let mut arm_blocks = Vec::new();
            for arm in arms {
                let block = builder.create_block();
                arm_blocks.push((arm, block));
            }

            for (i, (arm, arm_bb)) in arm_blocks.iter().enumerate() {
                let cond = if pattern_is_wildcard(&arm.pattern) {
                    builder.ins().iconst(types::I8, 1)
                } else {
                    compile_pattern_cond(builder, match_val, &arm.pattern)?
                };
                let is_last = i == arm_blocks.len() - 1;
                let fallthrough = if is_last {
                    default_bb
                } else {
                    builder.create_block()
                };
                builder.ins().brif(cond, *arm_bb, &[], fallthrough, &[]);
                if !is_last {
                    builder.switch_to_block(fallthrough);
                    builder.seal_block(fallthrough);
                }
            }

            builder.switch_to_block(default_bb);
            builder.seal_block(default_bb);
            builder.ins().jump(merge_bb, &[]);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();
            let mut all_returned = true;
            let exhaustive = arms.iter().any(|arm| pattern_is_wildcard(&arm.pattern));

            for (arm, arm_bb) in arm_blocks {
                builder.switch_to_block(arm_bb);
                builder.seal_block(arm_bb);
                let mut local_vars = parent_vars.clone();
                let mut local_types = parent_types.clone();

                match &arm.pattern {
                    ast::Pattern::Ident(name) if name != "_" => {
                        let var = Variable::new(*var_index as usize);
                        *var_index += 1;
                        let match_ty = convert_ast_type(&match_expr_ty);
                        builder.declare_var(var, match_ty);
                        let bound_val = cast_value(builder, match_val, match_ty);
                        builder.def_var(var, bound_val);
                        local_vars.insert(name.clone(), var);
                        local_types.insert(name.clone(), match_expr_ty.clone());
                    }
                    ast::Pattern::Some(name) if name != "_" => {
                        if let ast::Type::Option(inner) = &match_expr_ty {
                            let var = Variable::new(*var_index as usize);
                            *var_index += 1;
                            let inner_ty = convert_ast_type(inner);
                            builder.declare_var(var, inner_ty);
                            let loaded =
                                builder.ins().load(inner_ty, MemFlags::new(), match_val, 0);
                            builder.def_var(var, loaded);
                            local_vars.insert(name.clone(), var);
                            local_types.insert(name.clone(), inner.as_ref().clone());
                        }
                    }
                    ast::Pattern::EnumPayload { bindings, .. } => {
                        bind_enum_payload_fields(
                            builder,
                            match_val,
                            bindings,
                            var_index,
                            &mut local_vars,
                            &mut local_types,
                        );
                    }
                    _ => {}
                }

                let mut arm_returned = false;
                match &arm.body {
                    ast::MatchBody::Expr(expr) => {
                        compile_expr_inline(
                            builder,
                            module,
                            alloc_func,
                            functions,
                            structs,
                            fn_sigs,
                            &local_vars,
                            &local_types,
                            var_index,
                            defer_stack,
                            expr,
                        )?;
                    }
                    ast::MatchBody::Block(block) => {
                        compile_block_inline(
                            builder,
                            module,
                            alloc_func,
                            functions,
                            structs,
                            fn_sigs,
                            &mut local_vars,
                            &mut local_types,
                            var_index,
                            block,
                            &mut arm_returned,
                            defer_stack,
                            loop_exit,
                            loop_continue,
                        )?;
                    }
                }

                if !arm_returned {
                    builder.ins().jump(merge_bb, &[]);
                    all_returned = false;
                }
            }

            builder.switch_to_block(merge_bb);
            builder.seal_block(merge_bb);

            if exhaustive && all_returned {
                *returned = true;
            }
        }
        ast::Stmt::Return(expr) => {
            if let Some(e) = expr {
                let mut val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    e,
                )?;
                if let Some(ret) = builder.func.signature.returns.first() {
                    val = cast_value(builder, val, ret.value_type);
                }
                emit_defer_stack(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                )?;
                builder.ins().return_(&[val]);
            } else {
                emit_defer_stack(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                )?;
                builder.ins().return_(&[]);
            }
            *returned = true;
        }
        ast::Stmt::Defer(block) => {
            let Some(scope_defers) = defer_stack.last_mut() else {
                return Err(anyhow!("defer used outside of a block"));
            };
            scope_defers.push(block.clone());
        }
        ast::Stmt::Expr(expr) => {
            compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                expr,
            )?;
        }
        _ => {}
    }
    Ok(())
}

#[allow(clippy::too_many_arguments)]
fn emit_defer_stack(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    alloc_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    defer_stack: &[Vec<ast::Block>],
) -> Result<()> {
    for scope in defer_stack.iter().rev() {
        emit_defer_blocks(
            builder, module, alloc_func, functions, structs, fn_sigs, variables, var_types,
            var_index, scope,
        )?;
    }
    Ok(())
}

#[allow(clippy::too_many_arguments)]
fn emit_defer_blocks(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    alloc_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    defers: &[ast::Block],
) -> Result<()> {
    for block in defers.iter().rev() {
        let saved_vars = variables.clone();
        let saved_types = var_types.clone();
        let mut local_returned = false;
        let mut local_defer_stack: Vec<Vec<ast::Block>> = Vec::new();

        compile_block_inline(
            builder,
            module,
            alloc_func,
            functions,
            structs,
            fn_sigs,
            variables,
            var_types,
            var_index,
            block,
            &mut local_returned,
            &mut local_defer_stack,
            None, // no loop context in defer blocks
            None,
        )?;

        if local_returned {
            return Err(anyhow!(
                "return or break/continue inside defer is not supported"
            ));
        }

        *variables = saved_vars;
        *var_types = saved_types;
    }
    Ok(())
}

#[allow(clippy::too_many_arguments)]
fn compile_block_value(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    alloc_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &HashMap<String, Variable>,
    var_types: &HashMap<String, ast::Type>,
    var_index: &mut u32,
    block: &ast::Block,
    defer_stack: &mut Vec<Vec<ast::Block>>,
    loop_exit: Option<Block>,
    loop_continue: Option<Block>,
) -> Result<Option<Value>> {
    defer_stack.push(Vec::new());
    let mut last_val = None;
    let mut returned = false;
    let mut local_vars = variables.clone();
    let mut local_types = var_types.clone();

    for stmt in &block.statements {
        if returned {
            break;
        }
        match stmt {
            ast::Stmt::Expr(expr) => {
                last_val = Some(compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    &local_vars,
                    &local_types,
                    var_index,
                    defer_stack,
                    expr,
                )?);
            }
            _ => {
                compile_stmt_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    &mut local_vars,
                    &mut local_types,
                    var_index,
                    stmt,
                    &mut returned,
                    defer_stack,
                    loop_exit,
                    loop_continue,
                )?;
            }
        }
    }

    if returned {
        return Err(anyhow!(
            "return/break/continue inside match arm block expression is not supported yet"
        ));
    }

    if let Some(defers) = defer_stack.last() {
        emit_defer_blocks(
            builder,
            module,
            alloc_func,
            functions,
            structs,
            fn_sigs,
            &mut local_vars,
            &mut local_types,
            var_index,
            defers,
        )?;
    }
    defer_stack.pop();

    Ok(last_val)
}

fn bind_enum_payload_fields(
    builder: &mut FunctionBuilder,
    match_val: Value,
    bindings: &[String],
    var_index: &mut u32,
    local_vars: &mut HashMap<String, Variable>,
    local_types: &mut HashMap<String, ast::Type>,
) {
    if bindings.is_empty() {
        return;
    }
    let val = cast_value(builder, match_val, types::I64);
    if bindings.len() == 1 {
        bind_shifted_payload(
            builder,
            val,
            &bindings[0],
            8,
            None,
            var_index,
            local_vars,
            local_types,
        );
        return;
    }
    if bindings.len() == 2 {
        bind_shifted_payload(
            builder,
            val,
            &bindings[0],
            20,
            None,
            var_index,
            local_vars,
            local_types,
        );
        bind_shifted_payload(
            builder,
            val,
            &bindings[1],
            8,
            Some(4095),
            var_index,
            local_vars,
            local_types,
        );
    }
}

#[allow(clippy::too_many_arguments)]
fn bind_shifted_payload(
    builder: &mut FunctionBuilder,
    val: Value,
    name: &str,
    shift: i64,
    mask: Option<i64>,
    var_index: &mut u32,
    local_vars: &mut HashMap<String, Variable>,
    local_types: &mut HashMap<String, ast::Type>,
) {
    if name == "_" {
        return;
    }
    let var = Variable::new(*var_index as usize);
    *var_index += 1;
    builder.declare_var(var, types::I64);
    let shift_val = builder.ins().iconst(types::I64, shift);
    let mut extracted = builder.ins().ushr(val, shift_val);
    if let Some(bits) = mask {
        extracted = builder.ins().band_imm(extracted, bits);
    }
    builder.def_var(var, extracted);
    local_vars.insert(name.to_string(), var);
    local_types.insert(name.to_string(), ast::Type::I64);
}

fn pattern_is_wildcard(pattern: &ast::Pattern) -> bool {
    matches!(pattern, ast::Pattern::Ident(_))
}

fn compile_pattern_cond(
    builder: &mut FunctionBuilder,
    value: Value,
    pattern: &ast::Pattern,
) -> Result<Value> {
    match pattern {
        ast::Pattern::Ident(_) => Ok(builder.ins().iconst(types::I8, 1)),
        ast::Pattern::Bool(b) => {
            let val = bool_value_to_i8(builder, value)?;
            let expected = builder.ins().iconst(types::I8, if *b { 1 } else { 0 });
            Ok(builder.ins().icmp(IntCC::Equal, val, expected))
        }
        ast::Pattern::Literal(lit) => {
            let val_ty = builder.func.dfg.value_type(value);
            match lit {
                ast::Literal::Int(n) => {
                    if is_float_type(val_ty) {
                        return Err(anyhow!("Cannot match int literal against float value"));
                    }
                    let expected = builder.ins().iconst(val_ty, *n);
                    Ok(builder.ins().icmp(IntCC::Equal, value, expected))
                }
                ast::Literal::Char(c) => {
                    if is_float_type(val_ty) {
                        return Err(anyhow!("Cannot match char literal against float value"));
                    }
                    let expected = builder.ins().iconst(val_ty, *c as i64);
                    Ok(builder.ins().icmp(IntCC::Equal, value, expected))
                }
                ast::Literal::Float(f) => {
                    if !is_float_type(val_ty) {
                        return Err(anyhow!("Cannot match float literal against int value"));
                    }
                    let expected = if val_ty == types::F32 {
                        builder.ins().f32const(*f as f32)
                    } else {
                        builder.ins().f64const(*f)
                    };
                    Ok(builder.ins().fcmp(FloatCC::Equal, value, expected))
                }
                ast::Literal::Bool(b) => {
                    let val = bool_value_to_i8(builder, value)?;
                    let expected = builder.ins().iconst(types::I8, if *b { 1 } else { 0 });
                    Ok(builder.ins().icmp(IntCC::Equal, val, expected))
                }
                ast::Literal::String(_) | ast::Literal::HexColor(_) => Err(anyhow!(
                    "Match on string/hex literals is not supported in Kernel codegen yet"
                )),
            }
        }
        ast::Pattern::Some(_) => {
            let val = cast_value(builder, value, types::I64);
            Ok(builder.ins().icmp_imm(IntCC::NotEqual, val, 0))
        }
        ast::Pattern::None => {
            let val = cast_value(builder, value, types::I64);
            Ok(builder.ins().icmp_imm(IntCC::Equal, val, 0))
        }
        ast::Pattern::EnumVariant {
            enum_name, variant, ..
        } => Err(anyhow!(
            "Enum variant pattern '{}.{}' must be lowered before codegen",
            enum_name,
            variant
        )),
        ast::Pattern::EnumPayload { tag, .. } => {
            let val = cast_value(builder, value, types::I64);
            let masked = builder.ins().band_imm(val, 255);
            Ok(builder.ins().icmp_imm(IntCC::Equal, masked, *tag))
        }
    }
}

fn zero_value(builder: &mut FunctionBuilder, ty: types::Type) -> Value {
    if ty == types::F32 {
        builder.ins().f32const(0.0)
    } else if ty == types::F64 {
        builder.ins().f64const(0.0)
    } else {
        builder.ins().iconst(ty, 0)
    }
}

#[allow(clippy::too_many_arguments)]
fn compile_expr_inline(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    alloc_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &HashMap<String, Variable>,
    var_types: &HashMap<String, ast::Type>,
    var_index: &mut u32,
    defer_stack: &mut Vec<Vec<ast::Block>>,
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
            let lhs = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                left,
            )?;
            let rhs = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                right,
            )?;

            let lhs_ty = builder.func.dfg.value_type(lhs);
            let rhs_ty = builder.func.dfg.value_type(rhs);
            let common_ty = common_numeric_type(lhs_ty, rhs_ty);

            let (lhs, rhs) = if let Some(common_ty) = common_ty {
                (
                    cast_value(builder, lhs, common_ty),
                    cast_value(builder, rhs, common_ty),
                )
            } else {
                (lhs, rhs)
            };

            let is_float = common_ty.is_some_and(is_float_type);
            let result = match op {
                ast::BinaryOp::Add => {
                    if is_float {
                        builder.ins().fadd(lhs, rhs)
                    } else {
                        builder.ins().iadd(lhs, rhs)
                    }
                }
                ast::BinaryOp::Sub => {
                    if is_float {
                        builder.ins().fsub(lhs, rhs)
                    } else {
                        builder.ins().isub(lhs, rhs)
                    }
                }
                ast::BinaryOp::Mul => {
                    if is_float {
                        builder.ins().fmul(lhs, rhs)
                    } else {
                        builder.ins().imul(lhs, rhs)
                    }
                }
                ast::BinaryOp::Div => {
                    if is_float {
                        builder.ins().fdiv(lhs, rhs)
                    } else {
                        builder.ins().sdiv(lhs, rhs)
                    }
                }
                ast::BinaryOp::Mod => {
                    if is_float {
                        return Err(anyhow!(
                            "Floating-point remainder is not supported yet in Kernel codegen"
                        ));
                    }
                    builder.ins().srem(lhs, rhs)
                }
                ast::BinaryOp::Eq => {
                    if is_float {
                        builder.ins().fcmp(FloatCC::Equal, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::Equal, lhs, rhs)
                    }
                }
                ast::BinaryOp::Ne => {
                    if is_float {
                        builder.ins().fcmp(FloatCC::NotEqual, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::NotEqual, lhs, rhs)
                    }
                }
                ast::BinaryOp::Lt => {
                    if is_float {
                        builder.ins().fcmp(FloatCC::LessThan, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::SignedLessThan, lhs, rhs)
                    }
                }
                ast::BinaryOp::Le => {
                    if is_float {
                        builder.ins().fcmp(FloatCC::LessThanOrEqual, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::SignedLessThanOrEqual, lhs, rhs)
                    }
                }
                ast::BinaryOp::Gt => {
                    if is_float {
                        builder.ins().fcmp(FloatCC::GreaterThan, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::SignedGreaterThan, lhs, rhs)
                    }
                }
                ast::BinaryOp::Ge => {
                    if is_float {
                        builder.ins().fcmp(FloatCC::GreaterThanOrEqual, lhs, rhs)
                    } else {
                        builder
                            .ins()
                            .icmp(IntCC::SignedGreaterThanOrEqual, lhs, rhs)
                    }
                }
                ast::BinaryOp::And => builder.ins().band(lhs, rhs),
                ast::BinaryOp::Or => builder.ins().bor(lhs, rhs),
                ast::BinaryOp::BitAnd => builder.ins().band(lhs, rhs),
                ast::BinaryOp::BitOr => builder.ins().bor(lhs, rhs),
                ast::BinaryOp::BitXor => builder.ins().bxor(lhs, rhs),
                ast::BinaryOp::Shl => builder.ins().ishl(lhs, rhs),
                ast::BinaryOp::Shr => builder.ins().sshr(lhs, rhs),
                ast::BinaryOp::As => lhs,
            };
            Ok(result)
        }
        ast::Expr::Unary { op, expr: inner } => {
            let val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                inner,
            )?;
            let result = match op {
                ast::UnaryOp::Neg => {
                    if is_float_type(builder.func.dfg.value_type(val)) {
                        builder.ins().fneg(val)
                    } else {
                        builder.ins().ineg(val)
                    }
                }
                ast::UnaryOp::Not => {
                    let bool_val = bool_value_to_i8(builder, val)?;
                    builder.ins().icmp_imm(IntCC::Equal, bool_val, 0)
                }
            };
            Ok(result)
        }
        ast::Expr::Call { func, args } => {
            if let ast::Expr::Ident(name) = func.as_ref() {
                // Skip built-in functions for now
                if matches!(
                    name.as_str(),
                    "log" | "print" | "println" | "panic" | "assert"
                ) {
                    return Ok(builder.ins().iconst(types::I32, 0));
                }
                // strlen builtin: returns the length of a string
                if name == "strlen" {
                    if args.len() != 1 {
                        return Err(anyhow!("strlen expects 1 argument, got {}", args.len()));
                    }
                    let str_ptr = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        &args[0],
                    )?;
                    // Read the length from offset 0 of the string (i64)
                    let len = builder
                        .ins()
                        .load(types::I64, MemFlags::trusted(), str_ptr, 0);
                    // Convert to i32 for return
                    return Ok(builder.ins().ireduce(types::I32, len));
                }
                // len builtin: returns the length of an array or string
                if name == "len" {
                    if args.len() != 1 {
                        return Err(anyhow!("len expects 1 argument, got {}", args.len()));
                    }
                    let arg_ty = infer_expr_type(&args[0], var_types, structs, fn_sigs);
                    match arg_ty {
                        ast::Type::Array(_, size) => {
                            // For arrays, the length is known at compile time
                            return Ok(builder.ins().iconst(types::I32, size as i64));
                        }
                        ast::Type::Str => {
                            // For strings, read the length from the pointer
                            let str_ptr = compile_expr_inline(
                                builder,
                                module,
                                alloc_func,
                                functions,
                                structs,
                                fn_sigs,
                                variables,
                                var_types,
                                var_index,
                                defer_stack,
                                &args[0],
                            )?;
                            let len =
                                builder
                                    .ins()
                                    .load(types::I64, MemFlags::trusted(), str_ptr, 0);
                            return Ok(builder.ins().ireduce(types::I32, len));
                        }
                        _ => {
                            return Err(anyhow!("len expects array or str, got {:?}", arg_ty));
                        }
                    }
                }
                if let Some(&func_id) = functions.get(name) {
                    let (param_types, has_return) = {
                        let decl = module.declarations().get_function_decl(func_id);
                        (
                            decl.signature
                                .params
                                .iter()
                                .map(|p| p.value_type)
                                .collect::<Vec<_>>(),
                            !decl.signature.returns.is_empty(),
                        )
                    };

                    let func_ref = module.declare_func_in_func(func_id, builder.func);

                    let mut arg_vals = vec![];
                    for (i, arg) in args.iter().enumerate() {
                        let Some(param_ty) = param_types.get(i).copied() else {
                            return Err(anyhow!(
                                "Too many arguments in call to {} (expected {}, got {})",
                                name,
                                param_types.len(),
                                args.len()
                            ));
                        };

                        let val = compile_expr_inline(
                            builder,
                            module,
                            alloc_func,
                            functions,
                            structs,
                            fn_sigs,
                            variables,
                            var_types,
                            var_index,
                            defer_stack,
                            arg,
                        )?;
                        arg_vals.push(cast_value(builder, val, param_ty));
                    }

                    let call = builder.ins().call(func_ref, &arg_vals);
                    let results = builder.inst_results(call);

                    if !has_return || results.is_empty() {
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
            let arr_ptr = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                arr,
            )?;
            let idx = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                index,
            )?;
            let (elem_ty, elem_size_bytes) =
                infer_array_elem_type(arr, var_types, structs, fn_sigs)
                    .map(|ty| {
                        let size = type_size(&ty, structs);
                        (ty, size)
                    })
                    .unwrap_or((ast::Type::I32, 4));
            let idx = cast_value(builder, idx, types::I32);
            let elem_size = builder.ins().iconst(types::I64, elem_size_bytes as i64);
            let idx_ext = builder.ins().sextend(types::I64, idx);
            let offset = builder.ins().imul(idx_ext, elem_size);
            let elem_addr = builder.ins().iadd(arr_ptr, offset);
            Ok(builder
                .ins()
                .load(convert_ast_type(&elem_ty), MemFlags::new(), elem_addr, 0))
        }
        ast::Expr::Field { expr: obj, field } => {
            // Field access: obj.field
            let obj_ptr = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                obj,
            )?;
            if let Some((offset, ty)) = resolve_field(structs, obj, field, var_types) {
                let elem_type = convert_ast_type(&ty);
                return Ok(builder
                    .ins()
                    .load(elem_type, MemFlags::new(), obj_ptr, offset as i32));
            }
            Ok(builder.ins().iconst(types::I32, 0))
        }
        ast::Expr::Match { expr, arms } => {
            if arms.is_empty() {
                return Ok(builder.ins().iconst(types::I32, 0));
            }

            let match_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                expr,
            )?;
            let match_expr_ty = infer_expr_type(expr, var_types, structs, fn_sigs);

            let result_ast_ty = infer_match_expr_type(arms, var_types, structs, fn_sigs);
            let result_ty = convert_ast_type(&result_ast_ty);

            let merge_bb = builder.create_block();
            builder.append_block_param(merge_bb, result_ty);
            let default_bb = builder.create_block();

            let mut arm_blocks = Vec::new();
            for arm in arms {
                let block = builder.create_block();
                arm_blocks.push((arm, block));
            }

            for (i, (arm, arm_bb)) in arm_blocks.iter().enumerate() {
                let cond = if pattern_is_wildcard(&arm.pattern) {
                    builder.ins().iconst(types::I8, 1)
                } else {
                    compile_pattern_cond(builder, match_val, &arm.pattern)?
                };
                let is_last = i == arm_blocks.len() - 1;
                let fallthrough = if is_last {
                    default_bb
                } else {
                    builder.create_block()
                };
                builder.ins().brif(cond, *arm_bb, &[], fallthrough, &[]);
                if !is_last {
                    builder.switch_to_block(fallthrough);
                    builder.seal_block(fallthrough);
                }
            }

            builder.switch_to_block(default_bb);
            builder.seal_block(default_bb);
            let default_val = zero_value(builder, result_ty);
            builder.ins().jump(merge_bb, &[default_val]);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();

            for (arm, arm_bb) in arm_blocks {
                builder.switch_to_block(arm_bb);
                builder.seal_block(arm_bb);
                let mut local_vars = parent_vars.clone();
                let mut local_types = parent_types.clone();

                match &arm.pattern {
                    ast::Pattern::Ident(name) if name != "_" => {
                        let var = Variable::new(*var_index as usize);
                        *var_index += 1;
                        let match_ty = convert_ast_type(&match_expr_ty);
                        builder.declare_var(var, match_ty);
                        let bound_val = cast_value(builder, match_val, match_ty);
                        builder.def_var(var, bound_val);
                        local_vars.insert(name.clone(), var);
                        local_types.insert(name.clone(), match_expr_ty.clone());
                    }
                    ast::Pattern::Some(name) if name != "_" => {
                        if let ast::Type::Option(inner) = &match_expr_ty {
                            let var = Variable::new(*var_index as usize);
                            *var_index += 1;
                            let inner_ty = convert_ast_type(inner);
                            builder.declare_var(var, inner_ty);
                            let loaded =
                                builder.ins().load(inner_ty, MemFlags::new(), match_val, 0);
                            builder.def_var(var, loaded);
                            local_vars.insert(name.clone(), var);
                            local_types.insert(name.clone(), inner.as_ref().clone());
                        }
                    }
                    ast::Pattern::EnumPayload { bindings, .. } => {
                        bind_enum_payload_fields(
                            builder,
                            match_val,
                            bindings,
                            var_index,
                            &mut local_vars,
                            &mut local_types,
                        );
                    }
                    _ => {}
                }

                let arm_val = match &arm.body {
                    ast::MatchBody::Expr(expr) => compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        functions,
                        structs,
                        fn_sigs,
                        &local_vars,
                        &local_types,
                        var_index,
                        defer_stack,
                        expr,
                    )?,
                    ast::MatchBody::Block(block) => {
                        compile_block_value(
                            builder,
                            module,
                            alloc_func,
                            functions,
                            structs,
                            fn_sigs,
                            &local_vars,
                            &local_types,
                            var_index,
                            block,
                            defer_stack,
                            None, // no break/continue from match arm block expression
                            None,
                        )?
                        .ok_or_else(|| {
                            anyhow!("match arm block must yield a value in expression context")
                        })?
                    }
                };

                let arm_val = cast_value(builder, arm_val, result_ty);
                builder.ins().jump(merge_bb, &[arm_val]);
            }

            builder.switch_to_block(merge_bb);
            builder.seal_block(merge_bb);
            Ok(builder.block_params(merge_bb)[0])
        }
        ast::Expr::Block(block) => {
            let val = compile_block_value(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                block,
                defer_stack,
                None, // no break/continue from block expression
                None,
            )?;
            val.ok_or_else(|| anyhow!("block expression must yield a value"))
        }
        ast::Expr::Some(inner) => {
            let inner_ty = infer_expr_type(inner, var_types, structs, fn_sigs);
            let inner_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                inner,
            )?;
            let inner_val = cast_value(builder, inner_val, convert_ast_type(&inner_ty));
            let size_bytes = type_size(&inner_ty, structs) as i64;
            let align = size_bytes.max(1);
            let ptr = emit_alloc(builder, module, alloc_func, size_bytes, align)?;
            if size_bytes > 0 {
                builder.ins().store(MemFlags::new(), inner_val, ptr, 0);
            }
            Ok(ptr)
        }
        ast::Expr::None => Ok(builder.ins().iconst(types::I64, 0)),
        ast::Expr::Array(elements) => {
            let elem_ty = infer_array_literal_type(elements, var_types, structs, fn_sigs);
            let elem_size = type_size(&elem_ty, structs) as i64;
            let count = elements.len() as i64;
            let size_bytes = count.saturating_mul(elem_size);
            let ptr = emit_alloc(builder, module, alloc_func, size_bytes, elem_size)?;

            let is_all_zero = elements.iter().all(|e| match e {
                ast::Expr::Literal(ast::Literal::Int(0)) => true,
                ast::Expr::Literal(ast::Literal::Float(f)) => *f == 0.0,
                ast::Expr::Literal(ast::Literal::Bool(false)) => true,
                _ => false,
            });
            if !is_all_zero {
                for (i, elem) in elements.iter().enumerate() {
                    let val = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        elem,
                    )?;
                    let val = cast_value(builder, val, convert_ast_type(&elem_ty));
                    let offset = (i as i32).saturating_mul(elem_size as i32);
                    builder.ins().store(MemFlags::new(), val, ptr, offset);
                }
            }

            Ok(ptr)
        }
        ast::Expr::Struct { name, fields } => {
            let Some(layout) = structs.get(name) else {
                return Ok(builder.ins().iconst(types::I64, 0));
            };

            let ptr = emit_alloc(builder, module, alloc_func, layout.size as i64, 8)?;

            for (field_name, field_expr) in fields {
                let Some((offset, field_ty)) = layout
                    .fields
                    .iter()
                    .find(|(n, _o, _t)| n == field_name)
                    .map(|(_n, o, t)| (*o, t.clone()))
                else {
                    continue;
                };

                let val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    field_expr,
                )?;
                let val = cast_value(builder, val, convert_ast_type(&field_ty));
                builder
                    .ins()
                    .store(MemFlags::new(), val, ptr, offset as i32);
            }

            Ok(ptr)
        }
        ast::Expr::Cast { expr, target_type } => {
            let val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                expr,
            )?;
            let source_ty = infer_expr_type(expr, var_types, structs, fn_sigs);
            emit_type_cast(builder, val, &source_ty, target_type)
        }
        ast::Expr::Copy(inner) => {
            // Deep copy: for primitives, return value as-is; for composites, allocate and copy
            let inner_ty = infer_expr_type(inner, var_types, structs, fn_sigs);
            let val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                inner,
            )?;

            match &inner_ty {
                // Primitives: already value types, just return
                ast::Type::I32
                | ast::Type::I64
                | ast::Type::F32
                | ast::Type::F64
                | ast::Type::Bool => Ok(val),
                // Structs: allocate new memory and copy bytes
                ast::Type::Named(name) => {
                    if let Some(layout) = structs.get(name) {
                        let size = layout.size as i64;
                        let new_ptr = emit_alloc(builder, module, alloc_func, size, 8)?;
                        let len_val = builder.ins().iconst(types::I64, size);
                        // Use a unique var_index for the memcpy loop
                        let copy_var_idx = 20000 + (*var_index as usize);
                        *var_index += 1;
                        emit_memcpy_loop(builder, new_ptr, val, len_val, copy_var_idx)?;
                        Ok(new_ptr)
                    } else {
                        Ok(val)
                    }
                }
                // Fixed-size arrays: allocate new memory and copy bytes
                ast::Type::Array(elem_ty, len) => {
                    let elem_size = type_size(elem_ty, structs) as i64;
                    let total_size = elem_size * (*len as i64);
                    if total_size > 0 {
                        let new_ptr =
                            emit_alloc(builder, module, alloc_func, total_size, elem_size.max(8))?;
                        let len_val = builder.ins().iconst(types::I64, total_size);
                        let copy_var_idx = 20000 + (*var_index as usize);
                        *var_index += 1;
                        emit_memcpy_loop(builder, new_ptr, val, len_val, copy_var_idx)?;
                        Ok(new_ptr)
                    } else {
                        Ok(val)
                    }
                }
                // Option<T>: for now treat as value (tagged union representation)
                ast::Type::Option(_) => Ok(val),
                // Other types: return as-is
                _ => Ok(val),
            }
        }
        _ => Ok(builder.ins().iconst(types::I32, 0)),
    }
}

fn compile_literal_inline(builder: &mut FunctionBuilder, lit: &ast::Literal) -> Result<Value> {
    match lit {
        ast::Literal::Int(n) => {
            if i32::try_from(*n).is_ok() {
                Ok(builder.ins().iconst(types::I32, *n))
            } else {
                Ok(builder.ins().iconst(types::I64, *n))
            }
        }
        ast::Literal::Float(f) => Ok(builder.ins().f64const(*f)),
        ast::Literal::Bool(b) => Ok(builder.ins().iconst(types::I8, if *b { 1 } else { 0 })),
        _ => Ok(builder.ins().iconst(types::I32, 0)),
    }
}

fn emit_type_cast(
    builder: &mut FunctionBuilder,
    val: Value,
    source_type: &ast::Type,
    target_type: &ast::Type,
) -> Result<Value> {
    use ast::Type;

    match (source_type, target_type) {
        (a, b) if a == b => Ok(val),
        (Type::I32, Type::I64) => Ok(builder.ins().sextend(types::I64, val)),
        (Type::I64, Type::I32) => Ok(builder.ins().ireduce(types::I32, val)),
        (Type::I32 | Type::I64, Type::F64) => {
            let i64_val = if matches!(source_type, Type::I32) {
                builder.ins().sextend(types::I64, val)
            } else {
                val
            };
            Ok(builder.ins().fcvt_from_sint(types::F64, i64_val))
        }
        (Type::F64, Type::I32) => {
            let i64_val = builder.ins().fcvt_to_sint(types::I64, val);
            Ok(builder.ins().ireduce(types::I32, i64_val))
        }
        (Type::F64, Type::I64) => Ok(builder.ins().fcvt_to_sint(types::I64, val)),
        (Type::Bool, Type::I32 | Type::I64) => {
            if matches!(target_type, Type::I64) {
                Ok(builder.ins().uextend(types::I64, val))
            } else {
                Ok(builder.ins().uextend(types::I32, val))
            }
        }
        (Type::I32 | Type::I64, Type::Bool) => {
            let zero = if matches!(source_type, Type::I64) {
                builder.ins().iconst(types::I64, 0)
            } else {
                builder.ins().iconst(types::I32, 0)
            };
            Ok(builder.ins().icmp(IntCC::NotEqual, val, zero))
        }
        _ => Ok(cast_value(builder, val, convert_ast_type(target_type))),
    }
}

fn bool_value_to_i8(builder: &mut FunctionBuilder, val: Value) -> Result<Value> {
    match builder.func.dfg.value_type(val) {
        types::I8 => Ok(val),
        types::I32 | types::I64 => Ok(builder.ins().icmp_imm(IntCC::NotEqual, val, 0)),
        other => Err(anyhow!("Expected bool condition (I8), got {:?}", other)),
    }
}

fn cast_value(builder: &mut FunctionBuilder, val: Value, target: types::Type) -> Value {
    let src = builder.func.dfg.value_type(val);
    if src == target {
        return val;
    }
    match (src, target) {
        (types::I8, types::I32) => builder.ins().sextend(types::I32, val),
        (types::I8, types::I64) => builder.ins().sextend(types::I64, val),
        (types::I32, types::I8) => builder.ins().ireduce(types::I8, val),
        (types::I64, types::I8) => builder.ins().ireduce(types::I8, val),
        (types::I32, types::I64) => builder.ins().sextend(types::I64, val),
        (types::I64, types::I32) => builder.ins().ireduce(types::I32, val),
        (types::F32, types::F64) => builder.ins().fpromote(types::F64, val),
        (types::F64, types::F32) => builder.ins().fdemote(types::F32, val),
        (types::I32, types::F32) | (types::I64, types::F32) => {
            builder.ins().fcvt_from_sint(types::F32, val)
        }
        (types::I32, types::F64) | (types::I64, types::F64) => {
            builder.ins().fcvt_from_sint(types::F64, val)
        }
        (types::F32, types::I32) | (types::F64, types::I32) => {
            builder.ins().fcvt_to_sint(types::I32, val)
        }
        (types::F32, types::I64) | (types::F64, types::I64) => {
            builder.ins().fcvt_to_sint(types::I64, val)
        }
        _ => val,
    }
}

fn is_float_type(ty: types::Type) -> bool {
    matches!(ty, types::F32 | types::F64)
}

fn is_numeric_type(ty: types::Type) -> bool {
    matches!(ty, types::I32 | types::I64 | types::F32 | types::F64)
}

fn common_numeric_type(lhs_ty: types::Type, rhs_ty: types::Type) -> Option<types::Type> {
    if !is_numeric_type(lhs_ty) || !is_numeric_type(rhs_ty) {
        return None;
    }
    Some(if lhs_ty == types::F64 || rhs_ty == types::F64 {
        types::F64
    } else if lhs_ty == types::F32 || rhs_ty == types::F32 {
        types::F32
    } else if lhs_ty == types::I64 || rhs_ty == types::I64 {
        types::I64
    } else {
        types::I32
    })
}

fn infer_expr_type(
    expr: &ast::Expr,
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> ast::Type {
    match expr {
        ast::Expr::Literal(lit) => match lit {
            ast::Literal::Int(_) => ast::Type::I32,
            ast::Literal::Float(_) => ast::Type::F64,
            ast::Literal::Bool(_) => ast::Type::Bool,
            ast::Literal::Char(_) => ast::Type::I32,
            ast::Literal::String(_) => ast::Type::Str,
            ast::Literal::HexColor(_) => ast::Type::I32,
        },
        ast::Expr::Ident(name) => var_types.get(name).cloned().unwrap_or(ast::Type::I32),
        ast::Expr::Unary { op, expr } => {
            let inner = infer_expr_type(expr, var_types, structs, fn_sigs);
            match op {
                ast::UnaryOp::Neg => inner,
                ast::UnaryOp::Not => ast::Type::Bool,
            }
        }
        ast::Expr::Binary { op, left, right } => {
            let left_ty = infer_expr_type(left, var_types, structs, fn_sigs);
            let right_ty = infer_expr_type(right, var_types, structs, fn_sigs);
            match op {
                ast::BinaryOp::Add
                | ast::BinaryOp::Sub
                | ast::BinaryOp::Mul
                | ast::BinaryOp::Div
                | ast::BinaryOp::Mod => merge_numeric_types(&left_ty, &right_ty),
                ast::BinaryOp::Eq
                | ast::BinaryOp::Ne
                | ast::BinaryOp::Lt
                | ast::BinaryOp::Le
                | ast::BinaryOp::Gt
                | ast::BinaryOp::Ge
                | ast::BinaryOp::And
                | ast::BinaryOp::Or => ast::Type::Bool,
                ast::BinaryOp::BitAnd
                | ast::BinaryOp::BitOr
                | ast::BinaryOp::BitXor
                | ast::BinaryOp::Shl
                | ast::BinaryOp::Shr => {
                    // Bitwise operators return the wider integer type
                    if matches!(left_ty, ast::Type::I64) || matches!(right_ty, ast::Type::I64) {
                        ast::Type::I64
                    } else {
                        ast::Type::I32
                    }
                }
                ast::BinaryOp::As => left_ty,
            }
        }
        ast::Expr::Call { func, .. } => {
            if let ast::Expr::Ident(name) = func.as_ref() {
                let arg_types = if let ast::Expr::Call { args, .. } = expr {
                    args.iter()
                        .map(|arg| infer_expr_type(arg, var_types, structs, fn_sigs))
                        .collect::<Vec<_>>()
                } else {
                    Vec::new()
                };
                if let Some(ty) = builtins::infer_special_builtin_call_type(name, &arg_types, None)
                {
                    return ty;
                }
                if let Some((_, ret)) = fn_sigs.get(name) {
                    return ret.clone().unwrap_or(ast::Type::I32);
                }
            }
            ast::Type::I32
        }
        ast::Expr::Index { expr, .. } => {
            if let Some(elem) = infer_array_elem_type(expr, var_types, structs, fn_sigs) {
                elem
            } else {
                ast::Type::I32
            }
        }
        ast::Expr::Field { expr, field } => {
            if let Some((_offset, ty)) = resolve_field(structs, expr, field, var_types) {
                ty
            } else {
                ast::Type::I32
            }
        }
        ast::Expr::Array(elements) => {
            let elem_ty = infer_array_literal_type(elements, var_types, structs, fn_sigs);
            ast::Type::Array(Box::new(elem_ty), elements.len())
        }
        ast::Expr::Struct { name, .. } => ast::Type::Named(name.clone()),
        ast::Expr::If {
            then_expr,
            else_expr,
            ..
        } => {
            let then_is_none = matches!(then_expr.as_ref(), ast::Expr::None)
                || matches!(
                    then_expr.as_ref(),
                    ast::Expr::Block(block)
                        if infer_block_value_type(block, var_types, structs, fn_sigs).is_none()
                );
            let else_is_none = matches!(else_expr.as_ref(), ast::Expr::None)
                || matches!(
                    else_expr.as_ref(),
                    ast::Expr::Block(block)
                        if infer_block_value_type(block, var_types, structs, fn_sigs).is_none()
                );
            if then_is_none && !else_is_none {
                return infer_expr_type(else_expr, var_types, structs, fn_sigs);
            }
            if else_is_none && !then_is_none {
                return infer_expr_type(then_expr, var_types, structs, fn_sigs);
            }
            let then_ty = infer_expr_type(then_expr, var_types, structs, fn_sigs);
            let else_ty = infer_expr_type(else_expr, var_types, structs, fn_sigs);
            if types_compatible_ast(&then_ty, &else_ty) {
                merge_types(&then_ty, &else_ty)
            } else {
                then_ty
            }
        }
        ast::Expr::Match { arms, .. } => infer_match_expr_type(arms, var_types, structs, fn_sigs),
        ast::Expr::Block(block) => {
            infer_block_value_type(block, var_types, structs, fn_sigs).unwrap_or(ast::Type::I32)
        }
        ast::Expr::Some(inner) => {
            let inner_ty = infer_expr_type(inner, var_types, structs, fn_sigs);
            ast::Type::Option(Box::new(inner_ty))
        }
        ast::Expr::None => ast::Type::Option(Box::new(ast::Type::I32)),
        ast::Expr::Copy(expr) => infer_expr_type(expr, var_types, structs, fn_sigs),
        _ => ast::Type::I32,
    }
}

fn infer_array_elem_type(
    expr: &ast::Expr,
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> Option<ast::Type> {
    match infer_expr_type(expr, var_types, structs, fn_sigs) {
        ast::Type::Array(elem, _) => Some(*elem),
        _ => None,
    }
}

fn infer_array_len(
    expr: &ast::Expr,
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> Option<usize> {
    match infer_expr_type(expr, var_types, structs, fn_sigs) {
        ast::Type::Array(_, len) => Some(len),
        _ => None,
    }
}

fn infer_array_literal_type(
    elements: &[ast::Expr],
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> ast::Type {
    if elements.is_empty() {
        return ast::Type::I32;
    }
    let mut current = infer_expr_type(&elements[0], var_types, structs, fn_sigs);
    for elem in elements.iter().skip(1) {
        let next = infer_expr_type(elem, var_types, structs, fn_sigs);
        current = merge_numeric_types(&current, &next);
    }
    current
}

fn infer_block_value_type(
    block: &ast::Block,
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> Option<ast::Type> {
    let mut env = var_types.clone();
    let mut last = None;
    for stmt in &block.statements {
        match stmt {
            ast::Stmt::Let { name, ty, value } => {
                let inferred = ty
                    .clone()
                    .unwrap_or_else(|| infer_expr_type(value, &env, structs, fn_sigs));
                env.insert(name.clone(), inferred);
            }
            ast::Stmt::Expr(expr) => {
                if matches!(expr, ast::Expr::None) {
                    last = None;
                } else {
                    last = Some(infer_expr_type(expr, &env, structs, fn_sigs));
                }
            }
            _ => {}
        }
    }
    last
}

fn infer_match_expr_type(
    arms: &[ast::MatchArm],
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> ast::Type {
    let mut result = None;
    let mut saw_none = false;
    for arm in arms {
        let arm_ty = match &arm.body {
            ast::MatchBody::Expr(expr) => {
                if matches!(expr, ast::Expr::None) {
                    saw_none = true;
                    None
                } else {
                    Some(infer_expr_type(expr, var_types, structs, fn_sigs))
                }
            }
            ast::MatchBody::Block(block) => {
                let inferred = infer_block_value_type(block, var_types, structs, fn_sigs);
                if inferred.is_none() {
                    saw_none = true;
                }
                inferred
            }
        };

        if let Some(arm_ty) = arm_ty {
            result = match result {
                None => Some(arm_ty),
                Some(existing) => Some(merge_types(&existing, &arm_ty)),
            };
        }
    }

    if saw_none {
        match result.as_ref() {
            Some(ast::Type::Option(_)) => {}
            None => return ast::Type::Option(Box::new(ast::Type::I32)),
            _ => {}
        }
    }

    result.unwrap_or(ast::Type::I32)
}

fn merge_numeric_types(left: &ast::Type, right: &ast::Type) -> ast::Type {
    use ast::Type::*;
    match (left, right) {
        (F64, _) | (_, F64) => F64,
        (F32, _) | (_, F32) => F32,
        (I64, _) | (_, I64) => I64,
        (I32, _) | (_, I32) => I32,
        (Bool, Bool) => Bool,
        _ => I32,
    }
}

fn merge_types(left: &ast::Type, right: &ast::Type) -> ast::Type {
    use ast::Type::*;

    if left == right {
        return left.clone();
    }
    if let (Option(a), Option(b)) = (left, right) {
        return Option(Box::new(merge_types(a, b)));
    }
    if let (Vec(a), Vec(b)) = (left, right) {
        return Vec(Box::new(merge_types(a, b)));
    }
    if let (HashMap(key_a, value_a), HashMap(key_b, value_b)) = (left, right) {
        return HashMap(
            Box::new(merge_types(key_a, key_b)),
            Box::new(merge_types(value_a, value_b)),
        );
    }
    if let (Result(ok_a, err_a), Result(ok_b, err_b)) = (left, right) {
        return Result(
            Box::new(merge_types(ok_a, ok_b)),
            Box::new(merge_types(err_a, err_b)),
        );
    }
    if let (Array(a, len_a), Array(b, len_b)) = (left, right) {
        if len_a == len_b {
            return Array(Box::new(merge_types(a, b)), *len_a);
        }
    }
    if matches!(left, I32 | I64 | F32 | F64) && matches!(right, I32 | I64 | F32 | F64) {
        return merge_numeric_types(left, right);
    }
    if matches!(left, Bool) && matches!(right, Bool) {
        return Bool;
    }
    if matches!(left, Str) && matches!(right, Str) {
        return Str;
    }
    if let (Named(a), Named(b)) = (left, right) {
        if a == b {
            return Named(a.clone());
        }
    }
    left.clone()
}

fn types_compatible_ast(expected: &ast::Type, actual: &ast::Type) -> bool {
    if expected == actual {
        return true;
    }
    if matches!(
        expected,
        ast::Type::I32 | ast::Type::I64 | ast::Type::F32 | ast::Type::F64
    ) && matches!(
        actual,
        ast::Type::I32 | ast::Type::I64 | ast::Type::F32 | ast::Type::F64
    ) {
        return true;
    }
    match (expected, actual) {
        (ast::Type::Option(e1), ast::Type::Option(e2)) => types_compatible_ast(e1, e2),
        (ast::Type::Vec(e1), ast::Type::Vec(e2)) => types_compatible_ast(e1, e2),
        (ast::Type::HashMap(key1, value1), ast::Type::HashMap(key2, value2)) => {
            types_compatible_ast(key1, key2) && types_compatible_ast(value1, value2)
        }
        (ast::Type::Result(ok1, err1), ast::Type::Result(ok2, err2)) => {
            types_compatible_ast(ok1, ok2) && types_compatible_ast(err1, err2)
        }
        (ast::Type::Array(e1, _), ast::Type::Array(e2, _)) => types_compatible_ast(e1, e2),
        _ => false,
    }
}

fn resolve_field(
    structs: &HashMap<String, StructLayout>,
    expr: &ast::Expr,
    field: &str,
    var_types: &HashMap<String, ast::Type>,
) -> Option<(u32, ast::Type)> {
    let base_ty = match expr {
        ast::Expr::Ident(name) => var_types.get(name).cloned(),
        ast::Expr::Field { expr, field } => {
            resolve_field(structs, expr, field, var_types).map(|(_, ty)| ty)
        }
        _ => None,
    };

    if let Some(ast::Type::Named(struct_name)) = base_ty {
        if let Some(layout) = structs.get(&struct_name) {
            for (name, offset, ty) in &layout.fields {
                if name == field {
                    return Some((*offset, ty.clone()));
                }
            }
        }
    }

    // Fallback: first matching field name.
    for layout in structs.values() {
        for (name, offset, ty) in &layout.fields {
            if name == field {
                return Some((*offset, ty.clone()));
            }
        }
    }

    None
}

fn declare_alloc_func(module: &mut ObjectModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // size
    sig.params.push(AbiParam::new(types::I64)); // align
    sig.returns.push(AbiParam::new(types::I64)); // ptr

    module
        .declare_function("bunker_alloc", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_alloc: {}", e))
}

fn emit_alloc(
    builder: &mut FunctionBuilder,
    module: &mut ObjectModule,
    alloc_func: FuncId,
    size: i64,
    align: i64,
) -> Result<Value> {
    if size == 0 {
        return Ok(builder.ins().iconst(types::I64, 0));
    }

    let func_ref = module.declare_func_in_func(alloc_func, builder.func);
    let size_val = builder.ins().iconst(types::I64, size);
    let align_val = builder.ins().iconst(types::I64, align);
    let call = builder.ins().call(func_ref, &[size_val, align_val]);
    Ok(builder.inst_results(call)[0])
}

/// Emit a byte-copy loop from src to dest for len bytes (for deep copy support)
fn emit_memcpy_loop(
    builder: &mut FunctionBuilder,
    dest: Value,
    src: Value,
    len: Value,
    var_idx: usize,
) -> Result<()> {
    // Create loop structure
    let loop_header = builder.create_block();
    let loop_body = builder.create_block();
    let loop_exit = builder.create_block();

    // Initialize loop counter with unique variable index
    let idx_var = Variable::new(var_idx);
    builder.declare_var(idx_var, types::I64);
    let zero = builder.ins().iconst(types::I64, 0);
    builder.def_var(idx_var, zero);

    // Jump to loop header
    builder.ins().jump(loop_header, &[]);

    // Loop header: check if idx < len
    builder.switch_to_block(loop_header);
    let idx = builder.use_var(idx_var);
    let cond = builder.ins().icmp(IntCC::UnsignedLessThan, idx, len);
    builder.ins().brif(cond, loop_body, &[], loop_exit, &[]);

    // Loop body: copy one byte
    builder.switch_to_block(loop_body);
    let idx = builder.use_var(idx_var);
    let src_addr = builder.ins().iadd(src, idx);
    let byte_val = builder.ins().load(types::I8, MemFlags::new(), src_addr, 0);
    let dest_addr = builder.ins().iadd(dest, idx);
    builder.ins().store(MemFlags::new(), byte_val, dest_addr, 0);

    // Increment idx and jump back to header
    let next_idx = builder.ins().iadd_imm(idx, 1);
    builder.def_var(idx_var, next_idx);
    builder.ins().jump(loop_header, &[]);

    // Seal blocks
    builder.seal_block(loop_header);
    builder.seal_block(loop_body);
    builder.seal_block(loop_exit);

    // Continue from exit block
    builder.switch_to_block(loop_exit);

    Ok(())
}
