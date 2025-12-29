use std::collections::HashMap;
use anyhow::{anyhow, Result};
use cranelift::prelude::*;
use cranelift_module::{FuncId, Linkage, Module};
use cranelift_object::ObjectModule;

use crate::ast::{self, Shell, Agent, MessageHandler, Stmt, Expr, Literal};

// Agent state layout
#[derive(Clone, Debug)]
#[allow(dead_code)]
pub struct AgentLayout {
    pub name: String,
    pub size: u32,
    pub fields: Vec<(String, u32, types::Type)>, // (name, offset, type)
}

// Compute agent state layout from state declarations
fn compute_agent_layout(agent: &Agent) -> AgentLayout {
    let mut offset = 0u32;
    let mut fields = Vec::new();
    
    for state in &agent.state {
        // Infer type from initial value
        let ty = match &state.value {
            Expr::Literal(Literal::Int(_)) => types::I32,
            Expr::Literal(Literal::Float(_)) => types::F64,
            Expr::Literal(Literal::Bool(_)) => types::I8,
            _ => types::I64,
        };
        
        let size = match ty {
            types::I32 => 4,
            types::I64 => 8,
            types::F64 => 8,
            types::I8 => 1,
            _ => 8,
        };
        
        // Align to type size
        let align = size.min(8);
        offset = (offset + align - 1) & !(align - 1);
        
        fields.push((state.name.clone(), offset, ty));
        offset += size;
    }
    
    // Align total to 8 bytes
    let size = (offset + 7) & !7;
    if size == 0 { 
        AgentLayout { name: agent.name.clone(), size: 8, fields }
    } else {
        AgentLayout { name: agent.name.clone(), size, fields }
    }
}

pub struct ShellCompiler<'a> {
    module: &'a mut ObjectModule,
    ctx: &'a mut codegen::Context,
    #[allow(dead_code)]
    kernel_functions: &'a HashMap<String, FuncId>,
    agent_layouts: HashMap<String, AgentLayout>,
    agent_dispatch_funcs: HashMap<String, FuncId>,
    message_ids: HashMap<String, i32>,
}

impl<'a> ShellCompiler<'a> {
    pub fn new(
        module: &'a mut ObjectModule,
        ctx: &'a mut codegen::Context,
        kernel_functions: &'a HashMap<String, FuncId>,
    ) -> Self {
        Self {
            module,
            ctx,
            kernel_functions,
            agent_layouts: HashMap::new(),
            agent_dispatch_funcs: HashMap::new(),
            message_ids: HashMap::new(),
        }
    }

    pub fn compile_shell(&mut self, shell: &Shell) -> Result<()> {
        // First pass: compute all agent layouts
        for agent in &shell.agents {
            let layout = compute_agent_layout(agent);
            self.agent_layouts.insert(agent.name.clone(), layout);
        }

        // Collect all message types and assign IDs
        let mut msg_id = 0i32;
        for agent in &shell.agents {
            for handler in &agent.handlers {
                if !self.message_ids.contains_key(&handler.message) {
                    self.message_ids.insert(handler.message.clone(), msg_id);
                    msg_id += 1;
                }
            }
        }

        // Declare and compile dispatch functions
        for agent in &shell.agents {
            self.declare_agent_dispatch(agent)?;
        }

        for agent in &shell.agents {
            self.compile_agent_dispatch(agent)?;
        }

        // Generate agent initialization functions
        for agent in &shell.agents {
            self.compile_agent_init(agent)?;
        }

        Ok(())
    }

    fn declare_agent_dispatch(&mut self, agent: &Agent) -> Result<FuncId> {
        let mut sig = self.module.make_signature();
        
        // dispatch(agent_state_ptr: i64, message_id: i32, param_ptr: i64) -> i32
        sig.params.push(AbiParam::new(types::I64));
        sig.params.push(AbiParam::new(types::I32));
        sig.params.push(AbiParam::new(types::I64));
        sig.returns.push(AbiParam::new(types::I32));
        
        let func_name = format!("{}_dispatch", agent.name);
        let func_id = self.module
            .declare_function(&func_name, Linkage::Export, &sig)
            .map_err(|e| anyhow!("Failed to declare {}: {}", func_name, e))?;
        
        self.agent_dispatch_funcs.insert(agent.name.clone(), func_id);
        Ok(func_id)
    }

    fn compile_agent_dispatch(&mut self, agent: &Agent) -> Result<()> {
        let func_id = *self.agent_dispatch_funcs.get(&agent.name)
            .ok_or_else(|| anyhow!("Agent {} dispatch not declared", agent.name))?;

        self.ctx.func.signature = self.module.declarations()
            .get_function_decl(func_id).signature.clone();

        // Clone data we need before borrowing ctx
        let layout = self.agent_layouts.get(&agent.name).cloned();
        let message_ids = self.message_ids.clone();
        let handlers = agent.handlers.clone();

        let mut builder_ctx = FunctionBuilderContext::new();
        {
            let mut builder = FunctionBuilder::new(&mut self.ctx.func, &mut builder_ctx);
            
            let entry_block = builder.create_block();
            builder.append_block_params_for_function_params(entry_block);
            builder.switch_to_block(entry_block);
            
            let state_ptr = builder.block_params(entry_block)[0];
            let msg_id = builder.block_params(entry_block)[1];
            let _param_ptr = builder.block_params(entry_block)[2];
            
            // Create blocks for each handler + default
            let mut handler_blocks = Vec::new();
            for handler in &handlers {
                let block = builder.create_block();
                handler_blocks.push((handler.clone(), block));
            }
            let default_block = builder.create_block();
            let exit_block = builder.create_block();
            builder.append_block_param(exit_block, types::I32);
            
            // Build dispatch chain
            if handler_blocks.is_empty() {
                builder.ins().jump(default_block, &[]);
            } else {
                for (i, (handler, target_block)) in handler_blocks.iter().enumerate() {
                    let expected_id = *message_ids.get(&handler.message).unwrap_or(&-1);
                    let expected = builder.ins().iconst(types::I32, expected_id as i64);
                    let cmp = builder.ins().icmp(IntCC::Equal, msg_id, expected);
                    
                    if i < handler_blocks.len() - 1 {
                        let next_check = builder.create_block();
                        builder.ins().brif(cmp, *target_block, &[], next_check, &[]);
                        builder.switch_to_block(next_check);
                        builder.seal_block(next_check);
                    } else {
                        builder.ins().brif(cmp, *target_block, &[], default_block, &[]);
                    }
                }
            }
            
            // Compile each handler block
            let mut var_base = 0u32;
            for (handler, block) in &handler_blocks {
                builder.switch_to_block(*block);
                builder.seal_block(*block);
                
                let vars_used = compile_handler_body(&mut builder, state_ptr, handler, &layout, var_base);
                var_base += vars_used;
                
                let success = builder.ins().iconst(types::I32, 1);
                builder.ins().jump(exit_block, &[success]);
            }
            
            // Default block
            builder.switch_to_block(default_block);
            builder.seal_block(default_block);
            let fail = builder.ins().iconst(types::I32, 0);
            builder.ins().jump(exit_block, &[fail]);
            
            // Exit block
            builder.switch_to_block(exit_block);
            builder.seal_block(exit_block);
            let result = builder.block_params(exit_block)[0];
            builder.ins().return_(&[result]);
            
            builder.seal_all_blocks();
            builder.finalize();
        }

        self.module
            .define_function(func_id, self.ctx)
            .map_err(|e| anyhow!("Failed to define {}_dispatch: {:?}", agent.name, e))?;
        
        self.module.clear_context(self.ctx);
        Ok(())
    }

    fn compile_agent_init(&mut self, agent: &Agent) -> Result<()> {
        let mut sig = self.module.make_signature();
        sig.params.push(AbiParam::new(types::I64));
        
        let func_name = format!("{}_init", agent.name);
        let func_id = self.module
            .declare_function(&func_name, Linkage::Export, &sig)
            .map_err(|e| anyhow!("Failed to declare {}: {}", func_name, e))?;

        self.ctx.func.signature = self.module.declarations()
            .get_function_decl(func_id).signature.clone();

        let layout = self.agent_layouts.get(&agent.name).cloned();
        let state_inits = agent.state.clone();

        let mut builder_ctx = FunctionBuilderContext::new();
        {
            let mut builder = FunctionBuilder::new(&mut self.ctx.func, &mut builder_ctx);
            
            let entry_block = builder.create_block();
            builder.append_block_params_for_function_params(entry_block);
            builder.switch_to_block(entry_block);
            builder.seal_block(entry_block);
            
            let state_ptr = builder.block_params(entry_block)[0];
            
            if let Some(ref layout) = layout {
                for (i, state_decl) in state_inits.iter().enumerate() {
                    if i < layout.fields.len() {
                        let (_, offset, ty) = &layout.fields[i];
                        let val = match &state_decl.value {
                            Expr::Literal(Literal::Int(n)) => {
                                builder.ins().iconst(*ty, *n)
                            }
                            Expr::Literal(Literal::Bool(b)) => {
                                builder.ins().iconst(*ty, if *b { 1 } else { 0 })
                            }
                            _ => builder.ins().iconst(*ty, 0),
                        };
                        builder.ins().store(MemFlags::new(), val, state_ptr, *offset as i32);
                    }
                }
            }
            
            builder.ins().return_(&[]);
            builder.finalize();
        }

        self.module
            .define_function(func_id, self.ctx)
            .map_err(|e| anyhow!("Failed to define {}_init: {:?}", agent.name, e))?;
        
        self.module.clear_context(self.ctx);
        Ok(())
    }
}

// Free function to compile handler body
// Returns number of variables used
fn compile_handler_body(
    builder: &mut FunctionBuilder,
    state_ptr: Value,
    handler: &MessageHandler,
    layout: &Option<AgentLayout>,
    var_base: u32,
) -> u32 {
    let mut variables: HashMap<String, Variable> = HashMap::new();
    let mut var_index = var_base;
    
    // Load state variables
    if let Some(layout) = layout {
        for (name, offset, ty) in &layout.fields {
            let var = Variable::new(var_index as usize);
            var_index += 1;
            builder.declare_var(var, *ty);
            let val = builder.ins().load(*ty, MemFlags::new(), state_ptr, *offset as i32);
            builder.def_var(var, val);
            variables.insert(name.clone(), var);
        }
    }
    
    // Compile statements
    for stmt in &handler.body.statements {
        compile_shell_stmt(builder, stmt, &mut variables);
    }
    
    // Write back state
    if let Some(layout) = layout {
        for (name, offset, _ty) in &layout.fields {
            if let Some(&var) = variables.get(name) {
                let val = builder.use_var(var);
                builder.ins().store(MemFlags::new(), val, state_ptr, *offset as i32);
            }
        }
    }
    
    var_index - var_base
}

fn compile_shell_stmt(
    builder: &mut FunctionBuilder,
    stmt: &Stmt,
    variables: &mut HashMap<String, Variable>,
) {
    match stmt {
        Stmt::Assign {
            target: Expr::Ident(name),
            value,
        } => {
            if let Some(&var) = variables.get(name) {
                let val = compile_shell_expr(builder, value, variables);
                builder.def_var(var, val);
            }
        }
        Stmt::If { condition, then_block, else_block } => {
            let cond = compile_shell_expr(builder, condition, variables);
            
            let then_bb = builder.create_block();
            let else_bb = builder.create_block();
            let merge_bb = builder.create_block();
            
            builder.ins().brif(cond, then_bb, &[], else_bb, &[]);
            
            builder.switch_to_block(then_bb);
            builder.seal_block(then_bb);
            for s in &then_block.statements {
                compile_shell_stmt(builder, s, variables);
            }
            builder.ins().jump(merge_bb, &[]);
            
            builder.switch_to_block(else_bb);
            builder.seal_block(else_bb);
            if let Some(eb) = else_block {
                for s in &eb.statements {
                    compile_shell_stmt(builder, s, variables);
                }
            }
            builder.ins().jump(merge_bb, &[]);
            
            builder.switch_to_block(merge_bb);
            builder.seal_block(merge_bb);
        }
        Stmt::Send { .. } => {
            // Send is a runtime operation - skip for now
        }
        _ => {}
    }
}

fn compile_shell_expr(
    builder: &mut FunctionBuilder,
    expr: &Expr,
    variables: &HashMap<String, Variable>,
) -> Value {
    match expr {
        Expr::Literal(lit) => {
            match lit {
                Literal::Int(n) => builder.ins().iconst(types::I32, *n),
                Literal::Float(f) => builder.ins().f64const(*f),
                Literal::Bool(b) => builder.ins().iconst(types::I8, if *b { 1 } else { 0 }),
                _ => builder.ins().iconst(types::I32, 0),
            }
        }
        Expr::Ident(name) => {
            if let Some(&var) = variables.get(name) {
                builder.use_var(var)
            } else {
                builder.ins().iconst(types::I32, 0)
            }
        }
        Expr::Binary { op, left, right } => {
            let lhs = compile_shell_expr(builder, left, variables);
            let rhs = compile_shell_expr(builder, right, variables);
            
            match op {
                ast::BinaryOp::Add => builder.ins().iadd(lhs, rhs),
                ast::BinaryOp::Sub => builder.ins().isub(lhs, rhs),
                ast::BinaryOp::Mul => builder.ins().imul(lhs, rhs),
                ast::BinaryOp::Div => builder.ins().sdiv(lhs, rhs),
                ast::BinaryOp::Lt => builder.ins().icmp(IntCC::SignedLessThan, lhs, rhs),
                ast::BinaryOp::Le => builder.ins().icmp(IntCC::SignedLessThanOrEqual, lhs, rhs),
                ast::BinaryOp::Gt => builder.ins().icmp(IntCC::SignedGreaterThan, lhs, rhs),
                ast::BinaryOp::Ge => builder.ins().icmp(IntCC::SignedGreaterThanOrEqual, lhs, rhs),
                ast::BinaryOp::Eq => builder.ins().icmp(IntCC::Equal, lhs, rhs),
                ast::BinaryOp::Ne => builder.ins().icmp(IntCC::NotEqual, lhs, rhs),
                _ => lhs,
            }
        }
        _ => builder.ins().iconst(types::I32, 0),
    }
}
