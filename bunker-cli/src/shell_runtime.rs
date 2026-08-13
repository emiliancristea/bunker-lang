use std::collections::{HashMap, VecDeque};

use anyhow::{anyhow, Result};

use crate::ast;
use crate::jit;

#[derive(Debug, Clone)]
pub struct RunOptions {
    pub entry_agent: Option<String>,
    pub entry_message: String,
    pub entry_args: HashMap<String, String>,
    pub max_steps: usize,
}

impl Default for RunOptions {
    fn default() -> Self {
        Self {
            entry_agent: None,
            entry_message: "start".to_string(),
            entry_args: HashMap::new(),
            max_steps: 50_000,
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub(crate) enum Value {
    Int(i64),
    Float(f64),
    Bool(bool),
    Str(String),
    Option(Option<Box<Value>>),
    Array(Vec<Value>),
    Struct(HashMap<String, Value>),
    Unit,
}

/// Control flow signals for loops
#[derive(Debug, Clone, PartialEq)]
enum ControlFlow {
    Normal,
    Break,
    Continue,
}

impl Value {
    pub(crate) fn as_bool(&self) -> Result<bool> {
        match self {
            Value::Bool(b) => Ok(*b),
            other => Err(anyhow!("Expected bool, got {other:?}")),
        }
    }

    pub(crate) fn to_display_string(&self) -> String {
        match self {
            Value::Int(n) => n.to_string(),
            Value::Float(f) => f.to_string(),
            Value::Bool(b) => b.to_string(),
            Value::Str(s) => s.clone(),
            Value::Option(Some(inner)) => format!("Some({})", inner.to_display_string()),
            Value::Option(None) => "None".to_string(),
            Value::Array(arr) => {
                let items: Vec<_> = arr.iter().map(|v| v.to_display_string()).collect();
                format!("[{}]", items.join(", "))
            }
            Value::Struct(fields) => {
                let items: Vec<_> = fields
                    .iter()
                    .map(|(k, v)| format!("{}: {}", k, v.to_display_string()))
                    .collect();
                format!("{{ {} }}", items.join(", "))
            }
            Value::Unit => "()".to_string(),
        }
    }

    /// Get array length
    pub(crate) fn len(&self) -> Option<usize> {
        match self {
            Value::Array(arr) => Some(arr.len()),
            Value::Str(s) => Some(s.len()),
            _ => None,
        }
    }

    /// Get array element by index
    pub(crate) fn get_index(&self, idx: i64) -> Option<Value> {
        match self {
            Value::Array(arr) => {
                if idx >= 0 && (idx as usize) < arr.len() {
                    Some(arr[idx as usize].clone())
                } else {
                    None
                }
            }
            _ => None,
        }
    }

    /// Set array element by index
    pub(crate) fn set_index(&mut self, idx: i64, val: Value) -> Result<()> {
        match self {
            Value::Array(arr) => {
                if idx >= 0 && (idx as usize) < arr.len() {
                    arr[idx as usize] = val;
                    Ok(())
                } else {
                    Err(anyhow!("Array index out of bounds: {}", idx))
                }
            }
            _ => Err(anyhow!("Cannot index non-array value")),
        }
    }

    /// Get struct field
    pub(crate) fn get_field(&self, name: &str) -> Option<Value> {
        match self {
            Value::Struct(fields) => fields.get(name).cloned(),
            _ => None,
        }
    }

    /// Set struct field
    pub(crate) fn set_field(&mut self, name: &str, val: Value) {
        if let Value::Struct(fields) = self {
            fields.insert(name.to_string(), val);
        }
    }
}

/// Steps in an lvalue path for nested assignment
#[derive(Debug)]
enum LValueStep {
    Index(i64),
    Field(String),
}

pub(crate) struct ShellVm<'a> {
    shell: &'a ast::Shell,
    agents: HashMap<String, AgentRuntime>,
    queue: VecDeque<Event>,
    steps: usize,
    max_steps: usize,
    terminated: bool,
    exec: Executor<'a>,
}

impl<'a> ShellVm<'a> {
    pub(crate) fn new(file: &'a ast::File, max_steps: usize) -> Result<Self> {
        let shell = file
            .shells
            .first()
            .ok_or_else(|| anyhow!("No Shell blocks found"))?;

        let mut exec = Executor::new(file);
        let mut init_queue = VecDeque::new();

        let mut agents: HashMap<String, AgentRuntime> = HashMap::new();
        for agent in &shell.agents {
            let mut state = HashMap::new();
            let mut state_keys = Vec::new();

            for decl in &agent.state {
                let val = exec.eval_expr(&decl.value, &state, &mut init_queue)?;
                state.insert(decl.name.clone(), val);
                state_keys.push(decl.name.clone());
            }

            let mut handlers = HashMap::new();
            for handler in &agent.handlers {
                handlers.insert(handler.message.clone(), handler.clone());
            }

            agents.insert(
                agent.name.clone(),
                AgentRuntime {
                    state,
                    state_keys,
                    handlers,
                },
            );
        }

        Ok(Self {
            shell,
            agents,
            queue: init_queue,
            steps: 0,
            max_steps,
            terminated: false,
            exec,
        })
    }

    pub(crate) fn shell_name(&self) -> &str {
        &self.shell.name
    }

    pub(crate) fn steps(&self) -> usize {
        self.steps
    }

    pub(crate) fn enqueue_message(
        &mut self,
        target: &str,
        message: &str,
        args: HashMap<String, Value>,
    ) {
        self.queue.push_back(Event {
            target: target.to_string(),
            message: message.to_string(),
            args,
        });
    }

    pub(crate) fn enqueue_entry(&mut self, options: &RunOptions, strict: bool) -> Result<bool> {
        let entry_agent = match resolve_entry_agent(self.shell, &self.agents, options) {
            Ok(name) => name,
            Err(e) => {
                if strict {
                    return Err(e);
                }
                return Ok(false);
            }
        };

        let entry_handler = self
            .agents
            .get(&entry_agent)
            .and_then(|rt| rt.handlers.get(&options.entry_message))
            .cloned();

        let Some(entry_handler) = entry_handler else {
            if strict {
                return Err(anyhow!(
                    "Shell entrypoint not found: {}.{}",
                    entry_agent,
                    options.entry_message
                ));
            }
            return Ok(false);
        };

        let entry_args = build_entry_args(&entry_handler.params, &options.entry_args)?;
        self.queue.push_back(Event {
            target: entry_agent,
            message: options.entry_message.clone(),
            args: entry_args,
        });
        Ok(true)
    }

    pub(crate) fn run_until_idle(&mut self) -> Result<usize> {
        let mut processed = 0usize;
        while self.step()? {
            processed += 1;
        }
        Ok(processed)
    }

    pub(crate) fn step(&mut self) -> Result<bool> {
        if self.terminated {
            return Ok(false);
        }
        let Some(event) = self.queue.pop_front() else {
            return Ok(false);
        };

        self.steps += 1;
        if self.steps > self.max_steps {
            return Err(anyhow!(
                "Shell run exceeded step limit ({})",
                self.max_steps
            ));
        }

        // Minimal convention: messages sent to `System` are treated as sink/termination.
        if event.target == "System" {
            if event.message == "done" {
                self.terminated = true;
            }
            return Ok(true);
        }

        let Some(agent) = self.agents.get_mut(&event.target) else {
            return Err(anyhow!("Unknown agent target: {}", event.target));
        };

        let Some(handler) = agent.handlers.get(&event.message).cloned() else {
            // Unknown message for this agent: ignore for now.
            return Ok(true);
        };

        // Load state into an execution environment.
        let mut env = agent.state.clone();

        // Bind handler parameters from the message args.
        for param in &handler.params {
            let Some(val) = event.args.get(&param.name).cloned() else {
                return Err(anyhow!(
                    "Missing message arg '{}' for handler '{}' on agent '{}'",
                    param.name,
                    handler.message,
                    event.target
                ));
            };
            env.insert(param.name.clone(), val);
        }

        self.exec
            .exec_block(&handler.body, &mut env, &mut self.queue)?;

        // Write back state variables.
        for key in &agent.state_keys {
            if let Some(val) = env.get(key).cloned() {
                agent.state.insert(key.clone(), val);
            }
        }

        Ok(true)
    }

    pub(crate) fn get_agent_state_value(&self, agent: &str, key: &str) -> Option<Value> {
        self.agents
            .get(agent)
            .and_then(|rt| rt.state.get(key))
            .cloned()
    }
}

#[derive(Debug, Clone)]
struct Event {
    target: String,
    message: String,
    args: HashMap<String, Value>,
}

#[derive(Debug, Clone)]
struct AgentRuntime {
    state: HashMap<String, Value>,
    state_keys: Vec<String>,
    handlers: HashMap<String, ast::MessageHandler>,
}

#[derive(Debug, Clone)]
struct KernelSig {
    kernel: String,
    func: String,
    params: Vec<(String, ast::Type)>,
    return_type: Option<ast::Type>,
}

struct KernelBridge {
    jit: jit::KernelJit,
    sigs: HashMap<(String, String), KernelSig>,
}

impl KernelBridge {
    fn new(file: &ast::File) -> Result<Self> {
        let mut sigs = HashMap::new();
        for kernel in &file.kernels {
            for item in &kernel.items {
                match item {
                    ast::KernelItem::Function(func) | ast::KernelItem::ComptimeFn(func) => {
                        let params = func
                            .params
                            .iter()
                            .map(|p| (p.name.clone(), p.ty.clone()))
                            .collect();
                        sigs.insert(
                            (kernel.name.clone(), func.name.clone()),
                            KernelSig {
                                kernel: kernel.name.clone(),
                                func: func.name.clone(),
                                params,
                                return_type: func.return_type.clone(),
                            },
                        );
                    }
                    _ => {}
                }
            }
        }

        let jit = jit::KernelJit::from_file(file)?;
        Ok(Self { jit, sigs })
    }
}

struct Executor<'a> {
    file: &'a ast::File,
    kernel: Option<KernelBridge>,
}

impl<'a> Executor<'a> {
    fn new(file: &'a ast::File) -> Self {
        Self { file, kernel: None }
    }

    fn ensure_kernel(&mut self) -> Result<&mut KernelBridge> {
        if self.kernel.is_none() {
            if self.file.kernels.is_empty() {
                return Err(anyhow!("Kernel `use` requires at least one kernel block"));
            }
            self.kernel = Some(KernelBridge::new(self.file)?);
        }
        Ok(self.kernel.as_mut().expect("kernel bridge initialized"))
    }

    fn exec_block(
        &mut self,
        block: &ast::Block,
        env: &mut HashMap<String, Value>,
        queue: &mut VecDeque<Event>,
    ) -> Result<()> {
        let mut defers: Vec<&ast::Block> = Vec::new();

        for stmt in &block.statements {
            if let ast::Stmt::Defer(deferred_block) = stmt {
                // Collect defers to execute later
                defers.push(deferred_block);
            } else {
                // Ignore control flow at top level (handler execution)
                let cf = self.exec_stmt(stmt, env, queue)?;
                if cf == ControlFlow::Break {
                    // Return statement - stop handler execution
                    break;
                }
            }
        }

        // Execute deferred blocks in reverse order (LIFO)
        for deferred in defers.into_iter().rev() {
            self.exec_block(deferred, env, queue)?;
        }

        Ok(())
    }

    fn exec_stmt(
        &mut self,
        stmt: &ast::Stmt,
        env: &mut HashMap<String, Value>,
        queue: &mut VecDeque<Event>,
    ) -> Result<ControlFlow> {
        match stmt {
            ast::Stmt::Let { name, value, .. } => {
                let val = self.eval_expr(value, env, queue)?;
                env.insert(name.clone(), val);
                Ok(ControlFlow::Normal)
            }
            ast::Stmt::Assign { target, value } => {
                let val = self.eval_expr(value, env, queue)?;
                self.assign_target(target, val, env, queue)?;
                Ok(ControlFlow::Normal)
            }
            ast::Stmt::If {
                condition,
                then_block,
                else_block,
            } => {
                let cond = self.eval_expr(condition, env, queue)?.as_bool()?;
                if cond {
                    let cf = self.exec_block_cf(then_block, env, queue)?;
                    if cf != ControlFlow::Normal {
                        return Ok(cf);
                    }
                } else if let Some(else_block) = else_block {
                    let cf = self.exec_block_cf(else_block, env, queue)?;
                    if cf != ControlFlow::Normal {
                        return Ok(cf);
                    }
                }
                Ok(ControlFlow::Normal)
            }
            ast::Stmt::Match { expr, arms } => {
                let value = self.eval_expr(expr, env, queue)?;
                for arm in arms {
                    if let Some(bindings) = match_bindings(&arm.pattern, &value) {
                        let mut restore = Vec::new();
                        for (name, val) in bindings {
                            restore.push((name.clone(), env.get(&name).cloned()));
                            env.insert(name, val);
                        }
                        let cf = match &arm.body {
                            ast::MatchBody::Expr(expr) => {
                                let _ = self.eval_expr(expr, env, queue)?;
                                ControlFlow::Normal
                            }
                            ast::MatchBody::Block(block) => {
                                self.exec_block_cf(block, env, queue)?
                            }
                        };
                        for (name, previous) in restore {
                            if let Some(prev) = previous {
                                env.insert(name, prev);
                            } else {
                                env.remove(&name);
                            }
                        }
                        return Ok(cf);
                    }
                }
                Ok(ControlFlow::Normal)
            }
            ast::Stmt::For { var, iter, body } => {
                // Evaluate the iterator expression
                match iter {
                    ast::Expr::Range {
                        start,
                        end,
                        inclusive,
                    } => {
                        let start_val = self.eval_expr(start, env, queue)?;
                        let end_val = self.eval_expr(end, env, queue)?;

                        let Value::Int(start_n) = start_val else {
                            return Err(anyhow!("Range start must be integer"));
                        };
                        let Value::Int(end_n) = end_val else {
                            return Err(anyhow!("Range end must be integer"));
                        };

                        let end_n = if *inclusive { end_n + 1 } else { end_n };

                        // Save old value if any
                        let old_val = env.get(var).cloned();

                        for i in start_n..end_n {
                            env.insert(var.clone(), Value::Int(i));
                            let cf = self.exec_block_cf(body, env, queue)?;
                            match cf {
                                ControlFlow::Break => break,
                                ControlFlow::Continue => continue,
                                ControlFlow::Normal => {}
                            }
                        }

                        // Restore old value
                        if let Some(old) = old_val {
                            env.insert(var.clone(), old);
                        } else {
                            env.remove(var);
                        }
                    }
                    _ => {
                        // Try to evaluate as an array
                        let iter_val = self.eval_expr(iter, env, queue)?;
                        match iter_val {
                            Value::Array(elements) => {
                                let old_val = env.get(var).cloned();

                                for elem in elements {
                                    env.insert(var.clone(), elem);
                                    let cf = self.exec_block_cf(body, env, queue)?;
                                    match cf {
                                        ControlFlow::Break => break,
                                        ControlFlow::Continue => continue,
                                        ControlFlow::Normal => {}
                                    }
                                }

                                if let Some(old) = old_val {
                                    env.insert(var.clone(), old);
                                } else {
                                    env.remove(var);
                                }
                            }
                            other => {
                                return Err(anyhow!("Cannot iterate over {:?}", other));
                            }
                        }
                    }
                }
                Ok(ControlFlow::Normal)
            }
            ast::Stmt::While { condition, body } => {
                loop {
                    let cond = self.eval_expr(condition, env, queue)?.as_bool()?;
                    if !cond {
                        break;
                    }
                    let cf = self.exec_block_cf(body, env, queue)?;
                    match cf {
                        ControlFlow::Break => break,
                        ControlFlow::Continue => continue,
                        ControlFlow::Normal => {}
                    }
                }
                Ok(ControlFlow::Normal)
            }
            ast::Stmt::Loop(body) => {
                loop {
                    let cf = self.exec_block_cf(body, env, queue)?;
                    match cf {
                        ControlFlow::Break => break,
                        ControlFlow::Continue => continue,
                        ControlFlow::Normal => {}
                    }
                }
                Ok(ControlFlow::Normal)
            }
            ast::Stmt::Break => Ok(ControlFlow::Break),
            ast::Stmt::Continue => Ok(ControlFlow::Continue),
            ast::Stmt::Return(_) => {
                // Return in shell agent handler - just stop the handler
                Ok(ControlFlow::Break)
            }
            ast::Stmt::Send {
                message,
                target,
                args,
            } => {
                let msg_val = self.eval_expr(message, env, queue)?;
                let Value::Str(message) = msg_val else {
                    return Err(anyhow!(
                        "Shell send message must be a string, got {msg_val:?}"
                    ));
                };

                let mut evaluated_args = HashMap::new();
                for (name, expr) in args {
                    evaluated_args.insert(name.clone(), self.eval_expr(expr, env, queue)?);
                }

                queue.push_back(Event {
                    target: target.clone(),
                    message,
                    args: evaluated_args,
                });
                Ok(ControlFlow::Normal)
            }
            ast::Stmt::Defer(_) => Ok(ControlFlow::Normal), // Handled at block level in exec_block
            ast::Stmt::Expr(expr) => {
                let _ = self.eval_expr(expr, env, queue)?;
                Ok(ControlFlow::Normal)
            }
        }
    }

    /// Execute block and return control flow signal
    fn exec_block_cf(
        &mut self,
        block: &ast::Block,
        env: &mut HashMap<String, Value>,
        queue: &mut VecDeque<Event>,
    ) -> Result<ControlFlow> {
        let mut defers: Vec<&ast::Block> = Vec::new();
        let mut cf = ControlFlow::Normal;

        for stmt in &block.statements {
            if let ast::Stmt::Defer(deferred_block) = stmt {
                defers.push(deferred_block);
            } else {
                cf = self.exec_stmt(stmt, env, queue)?;
                if cf != ControlFlow::Normal {
                    break;
                }
            }
        }

        // Execute deferred blocks in reverse order (LIFO)
        for deferred in defers.into_iter().rev() {
            self.exec_block(deferred, env, queue)?;
        }

        Ok(cf)
    }

    fn eval_expr(
        &mut self,
        expr: &ast::Expr,
        env: &HashMap<String, Value>,
        queue: &mut VecDeque<Event>,
    ) -> Result<Value> {
        match expr {
            ast::Expr::Literal(lit) => Ok(match lit {
                ast::Literal::Int(n) => Value::Int(*n),
                ast::Literal::Float(f) => Value::Float(*f),
                ast::Literal::String(s) => Value::Str(s.clone()),
                ast::Literal::Bool(b) => Value::Bool(*b),
                ast::Literal::Char(c) => Value::Int(*c as i64),
                ast::Literal::HexColor(s) => Value::Str(s.clone()),
            }),
            ast::Expr::Some(inner) => {
                let val = self.eval_expr(inner, env, queue)?;
                Ok(Value::Option(Some(Box::new(val))))
            }
            ast::Expr::None => Ok(Value::Option(None)),
            ast::Expr::Ident(name) => env
                .get(name)
                .cloned()
                .ok_or_else(|| anyhow!("Undefined variable: {}", name)),
            ast::Expr::Binary { op, left, right } => {
                let left_val = self.eval_expr(left, env, queue)?;
                let right_val = self.eval_expr(right, env, queue)?;
                eval_binary(*op, left_val, right_val)
            }
            ast::Expr::Unary { op, expr } => {
                let val = self.eval_expr(expr, env, queue)?;
                eval_unary(*op, val)
            }
            ast::Expr::If {
                condition,
                then_expr,
                else_expr,
            } => {
                let cond = self.eval_expr(condition, env, queue)?.as_bool()?;
                if cond {
                    self.eval_expr(then_expr, env, queue)
                } else {
                    self.eval_expr(else_expr, env, queue)
                }
            }
            ast::Expr::Block(block) => self.eval_block_expr(block, env, queue),
            ast::Expr::Use { path, args } => self.eval_use(path, args, env, queue),
            ast::Expr::Send {
                message,
                target,
                args,
            } => {
                let msg_val = self.eval_expr(message, env, queue)?;
                let Value::Str(message) = msg_val else {
                    return Err(anyhow!(
                        "Shell send message must be a string, got {msg_val:?}"
                    ));
                };

                let Some(target_name) = target.last().cloned() else {
                    return Err(anyhow!("Shell send target cannot be empty"));
                };

                let mut evaluated_args = HashMap::new();
                for (name, expr) in args {
                    evaluated_args.insert(name.clone(), self.eval_expr(expr, env, queue)?);
                }

                queue.push_back(Event {
                    target: target_name,
                    message,
                    args: evaluated_args,
                });
                Ok(Value::Unit)
            }
            ast::Expr::Match { expr, arms } => {
                let value = self.eval_expr(expr, env, queue)?;
                for arm in arms {
                    if let Some(bindings) = match_bindings(&arm.pattern, &value) {
                        return match &arm.body {
                            ast::MatchBody::Expr(expr) => {
                                let mut arm_env = env.clone();
                                for (name, val) in bindings {
                                    arm_env.insert(name, val);
                                }
                                self.eval_expr(expr, &arm_env, queue)
                            }
                            ast::MatchBody::Block(block) => {
                                let mut scoped_env = env.clone();
                                for (name, val) in bindings {
                                    scoped_env.insert(name, val);
                                }
                                self.exec_block(block, &mut scoped_env, queue)?;
                                Ok(Value::Unit)
                            }
                        };
                    }
                }
                Ok(Value::Unit)
            }
            // Array literal: [1, 2, 3]
            ast::Expr::Array(elements) => {
                let mut values = Vec::with_capacity(elements.len());
                for elem in elements {
                    values.push(self.eval_expr(elem, env, queue)?);
                }
                Ok(Value::Array(values))
            }
            // Struct literal: Point { x: 1, y: 2 }
            ast::Expr::Struct { name: _, fields } => {
                let mut field_values = HashMap::new();
                for (field_name, field_expr) in fields {
                    field_values
                        .insert(field_name.clone(), self.eval_expr(field_expr, env, queue)?);
                }
                Ok(Value::Struct(field_values))
            }
            // Array/string indexing: arr[i]
            ast::Expr::Index { expr, index } => {
                let arr_val = self.eval_expr(expr, env, queue)?;
                let idx_val = self.eval_expr(index, env, queue)?;
                let Value::Int(idx) = idx_val else {
                    return Err(anyhow!("Array index must be integer, got {idx_val:?}"));
                };
                arr_val
                    .get_index(idx)
                    .ok_or_else(|| anyhow!("Index {} out of bounds", idx))
            }
            // Field access: point.x
            ast::Expr::Field { expr, field } => {
                let struct_val = self.eval_expr(expr, env, queue)?;
                struct_val
                    .get_field(field)
                    .ok_or_else(|| anyhow!("No field '{}' on value {:?}", field, struct_val))
            }
            // Function call: len(arr)
            ast::Expr::Call { func, args } => {
                // Handle built-in functions
                if let ast::Expr::Ident(name) = func.as_ref() {
                    match name.as_str() {
                        "len" => {
                            if args.len() != 1 {
                                return Err(anyhow!("len() takes exactly 1 argument"));
                            }
                            let val = self.eval_expr(&args[0], env, queue)?;
                            val.len()
                                .map(|n| Value::Int(n as i64))
                                .ok_or_else(|| anyhow!("len() not supported for {:?}", val))
                        }
                        other => Err(anyhow!("Unknown function: {}", other)),
                    }
                } else {
                    Err(anyhow!("Shell does not support dynamic function calls"))
                }
            }
            // Range expression (for iteration, not direct eval)
            ast::Expr::Range { .. } => Err(anyhow!(
                "Range expressions cannot be evaluated directly in shell"
            )),
            // Lambda (not supported in shell runtime)
            ast::Expr::Lambda { .. } => {
                Err(anyhow!("Lambda expressions not supported in shell runtime"))
            }
            // Copy: in shell runtime, all values are already copy-by-value
            ast::Expr::Copy(inner) => self.eval_expr(inner, env, queue),
            // Cast: shell runtime doesn't enforce strict typing, just evaluate
            ast::Expr::Cast { expr, .. } => self.eval_expr(expr, env, queue),
        }
    }

    /// Assign a value to a target expression (variable, index, or field)
    fn assign_target(
        &mut self,
        target: &ast::Expr,
        value: Value,
        env: &mut HashMap<String, Value>,
        queue: &mut VecDeque<Event>,
    ) -> Result<()> {
        match target {
            // Simple variable: x = value
            ast::Expr::Ident(name) => {
                env.insert(name.clone(), value);
                Ok(())
            }
            // Array index: arr[i] = value
            ast::Expr::Index { expr, index } => {
                let idx_val = self.eval_expr(index, env, queue)?;
                let Value::Int(idx) = idx_val else {
                    return Err(anyhow!("Array index must be integer, got {idx_val:?}"));
                };

                // Get the root variable name and path
                let (root_name, path) = self.resolve_lvalue_path(expr)?;

                // Get mutable reference to root value
                let root = env
                    .get_mut(&root_name)
                    .ok_or_else(|| anyhow!("Undefined variable: {}", root_name))?;

                // Navigate to the target through the path
                let target_val = self.navigate_path_mut(root, &path)?;

                // Set the index
                target_val.set_index(idx, value)
            }
            // Struct field: point.x = value
            ast::Expr::Field { expr, field } => {
                // Get the root variable name and path
                let (root_name, mut path) = self.resolve_lvalue_path(expr)?;
                path.push(LValueStep::Field(field.clone()));

                // Get mutable reference to root value
                let root = env
                    .get_mut(&root_name)
                    .ok_or_else(|| anyhow!("Undefined variable: {}", root_name))?;

                // Navigate to parent and set field
                if path.len() == 1 {
                    // Direct field access on root
                    root.set_field(field, value);
                } else {
                    // Navigate to parent, then set field
                    let parent_path = &path[..path.len() - 1];
                    let parent = self.navigate_path_mut(root, parent_path)?;
                    parent.set_field(field, value);
                }
                Ok(())
            }
            _ => Err(anyhow!("Unsupported assignment target: {target:?}")),
        }
    }

    /// Resolve an lvalue expression to (root_variable_name, path_of_steps)
    fn resolve_lvalue_path(&self, expr: &ast::Expr) -> Result<(String, Vec<LValueStep>)> {
        match expr {
            ast::Expr::Ident(name) => Ok((name.clone(), Vec::new())),
            ast::Expr::Index { expr, index } => {
                let (root, mut path) = self.resolve_lvalue_path(expr)?;
                // For lvalue resolution, we need the index to be a constant
                // This is a simplification - we'd need env access for full support
                if let ast::Expr::Literal(ast::Literal::Int(idx)) = index.as_ref() {
                    path.push(LValueStep::Index(*idx));
                    Ok((root, path))
                } else {
                    Err(anyhow!(
                        "Complex index expressions in lvalue not yet supported"
                    ))
                }
            }
            ast::Expr::Field { expr, field } => {
                let (root, mut path) = self.resolve_lvalue_path(expr)?;
                path.push(LValueStep::Field(field.clone()));
                Ok((root, path))
            }
            _ => Err(anyhow!("Invalid lvalue expression: {expr:?}")),
        }
    }

    /// Navigate a path of steps to get a mutable reference
    fn navigate_path_mut<'v>(
        &self,
        root: &'v mut Value,
        path: &[LValueStep],
    ) -> Result<&'v mut Value> {
        let mut current = root;
        for step in path {
            current = match step {
                LValueStep::Index(idx) => {
                    if let Value::Array(arr) = current {
                        if *idx >= 0 && (*idx as usize) < arr.len() {
                            &mut arr[*idx as usize]
                        } else {
                            return Err(anyhow!("Index {} out of bounds", idx));
                        }
                    } else {
                        return Err(anyhow!("Cannot index non-array value"));
                    }
                }
                LValueStep::Field(name) => {
                    if let Value::Struct(fields) = current {
                        fields
                            .get_mut(name)
                            .ok_or_else(|| anyhow!("No field '{}' on struct", name))?
                    } else {
                        return Err(anyhow!("Cannot access field on non-struct value"));
                    }
                }
            };
        }
        Ok(current)
    }

    fn eval_block_expr(
        &mut self,
        block: &ast::Block,
        env: &HashMap<String, Value>,
        queue: &mut VecDeque<Event>,
    ) -> Result<Value> {
        let mut local_env = env.clone();
        let mut last = Value::Unit;

        for stmt in &block.statements {
            match stmt {
                ast::Stmt::Expr(expr) => {
                    last = self.eval_expr(expr, &local_env, queue)?;
                }
                _ => {
                    self.exec_stmt(stmt, &mut local_env, queue)?;
                }
            }
        }

        Ok(last)
    }

    fn eval_use(
        &mut self,
        path: &[String],
        args: &[(String, ast::Expr)],
        env: &HashMap<String, Value>,
        queue: &mut VecDeque<Event>,
    ) -> Result<Value> {
        if path.is_empty() {
            return Err(anyhow!("Invalid `use` path"));
        }

        let (kernel_name, func_name) = if path.len() >= 2 {
            (Some(path[0].clone()), path[path.len() - 1].clone())
        } else {
            (None, path[0].clone())
        };

        // Initialize the Kernel bridge before resolving signatures or executing argument expressions.
        let _ = self.ensure_kernel()?;

        let sig = {
            let bridge = self
                .kernel
                .as_ref()
                .expect("kernel bridge initialized by ensure_kernel");

            if let Some(kernel_name) = kernel_name {
                bridge
                    .sigs
                    .get(&(kernel_name.clone(), func_name.clone()))
                    .cloned()
                    .ok_or_else(|| {
                        anyhow!("Unknown Kernel function: {}.{}", kernel_name, func_name)
                    })?
            } else {
                let matches: Vec<_> = bridge
                    .sigs
                    .values()
                    .filter(|s| s.func == func_name)
                    .cloned()
                    .collect();
                match matches.len() {
                    0 => return Err(anyhow!("Unknown Kernel function: {}", func_name)),
                    1 => matches[0].clone(),
                    _ => {
                        return Err(anyhow!(
                            "Ambiguous Kernel function `{}` (specify kernel name)",
                            func_name
                        ))
                    }
                }
            }
        };

        for (arg_name, _expr) in args {
            if !sig.params.iter().any(|(p, _)| p == arg_name) {
                return Err(anyhow!(
                    "Unknown argument '{}' for Kernel function {}.{}",
                    arg_name,
                    sig.kernel,
                    sig.func
                ));
            }
        }

        match sig.return_type.as_ref() {
            Some(ast::Type::I32) => {
                let mut values_i32: Vec<i32> = Vec::new();
                for (param_name, param_ty) in &sig.params {
                    if *param_ty != ast::Type::I32 {
                        return Err(anyhow!(
                            "Shell runtime only supports i32 parameters for Kernel `use` returning i32 ({}.{})",
                            sig.kernel,
                            sig.func
                        ));
                    }

                    let Some((_name, expr)) = args.iter().find(|(n, _)| n == param_name) else {
                        return Err(anyhow!(
                            "Missing argument '{}' for Kernel function {}.{}",
                            param_name,
                            sig.kernel,
                            sig.func
                        ));
                    };

                    let val = self.eval_expr(expr, env, queue)?;
                    let Value::Int(n) = val else {
                        return Err(anyhow!(
                            "Kernel argument '{}' must be an integer, got {val:?}",
                            param_name
                        ));
                    };
                    let Ok(n_i32) = i32::try_from(n) else {
                        return Err(anyhow!("Kernel argument '{}' out of range: {}", param_name, n));
                    };
                    values_i32.push(n_i32);
                }

                let result = self
                    .kernel
                    .as_mut()
                    .expect("kernel bridge initialized by ensure_kernel")
                    .jit
                    .call_i32(&func_name, &values_i32)?;
                Ok(Value::Int(result as i64))
            }
            Some(ast::Type::I64) => {
                let mut values_i64: Vec<i64> = Vec::new();
                for (param_name, param_ty) in &sig.params {
                    if *param_ty != ast::Type::I64 {
                        return Err(anyhow!(
                            "Shell runtime only supports i64 parameters for Kernel `use` returning i64 ({}.{})",
                            sig.kernel,
                            sig.func
                        ));
                    }

                    let Some((_name, expr)) = args.iter().find(|(n, _)| n == param_name) else {
                        return Err(anyhow!(
                            "Missing argument '{}' for Kernel function {}.{}",
                            param_name,
                            sig.kernel,
                            sig.func
                        ));
                    };

                    let val = self.eval_expr(expr, env, queue)?;
                    let Value::Int(n) = val else {
                        return Err(anyhow!(
                            "Kernel argument '{}' must be an integer, got {val:?}",
                            param_name
                        ));
                    };
                    values_i64.push(n);
                }

                let result = self
                    .kernel
                    .as_mut()
                    .expect("kernel bridge initialized by ensure_kernel")
                    .jit
                    .call_i64(&func_name, &values_i64)?;
                Ok(Value::Int(result))
            }
            Some(ast::Type::F64) => {
                let mut values_f64: Vec<f64> = Vec::new();
                for (param_name, param_ty) in &sig.params {
                    if *param_ty != ast::Type::F64 {
                        return Err(anyhow!(
                            "Shell runtime only supports f64 parameters for Kernel `use` returning f64 ({}.{})",
                            sig.kernel,
                            sig.func
                        ));
                    }

                    let Some((_name, expr)) = args.iter().find(|(n, _)| n == param_name) else {
                        return Err(anyhow!(
                            "Missing argument '{}' for Kernel function {}.{}",
                            param_name,
                            sig.kernel,
                            sig.func
                        ));
                    };

                    let val = self.eval_expr(expr, env, queue)?;
                    let n = match val {
                        Value::Float(f) => f,
                        Value::Int(i) => i as f64,
                        other => {
                            return Err(anyhow!(
                                "Kernel argument '{}' must be a number, got {other:?}",
                                param_name
                            ))
                        }
                    };
                    values_f64.push(n);
                }

                let result = self
                    .kernel
                    .as_mut()
                    .expect("kernel bridge initialized by ensure_kernel")
                    .jit
                    .call_f64(&func_name, &values_f64)?;
                Ok(Value::Float(result))
            }
            Some(ast::Type::Option(inner)) => {
                let inner_ty = inner.as_ref();
                if !matches!(inner_ty, ast::Type::I32 | ast::Type::I64 | ast::Type::F64) {
                    return Err(anyhow!(
                        "Shell runtime only supports Option<i32>, Option<i64>, or Option<f64> returns for Kernel `use` ({}.{}, got Option<{inner_ty:?}>)",
                        sig.kernel,
                        sig.func
                    ));
                }

                let option_ty = ast::Type::Option(inner.clone());
                let mut values_i64: Vec<i64> = Vec::new();
                for (param_name, param_ty) in &sig.params {
                    if *param_ty != option_ty {
                        return Err(anyhow!(
                            "Shell runtime only supports {:?} parameters for Kernel `use` returning {:?} ({}.{})",
                            option_ty,
                            option_ty,
                            sig.kernel,
                            sig.func
                        ));
                    }

                    let Some((_name, expr)) = args.iter().find(|(n, _)| n == param_name) else {
                        return Err(anyhow!(
                            "Missing argument '{}' for Kernel function {}.{}",
                            param_name,
                            sig.kernel,
                            sig.func
                        ));
                    };

                    let val = self.eval_expr(expr, env, queue)?;
                    let ptr = self.option_arg_ptr(inner_ty, val).map_err(|e| {
                        anyhow!("Kernel argument '{}' invalid for Option use: {e}", param_name)
                    })?;
                    values_i64.push(ptr);
                }

                let result_ptr = self
                    .kernel
                    .as_mut()
                    .expect("kernel bridge initialized by ensure_kernel")
                    .jit
                    .call_i64(&func_name, &values_i64)?;

                self.read_option_ptr(inner_ty, result_ptr)
            }
            other => Err(anyhow!(
                "Shell runtime only supports `use` of Kernel functions returning i32, i64, f64, or Option<...> of those types ({}.{}, got {other:?})",
                sig.kernel,
                sig.func
            )),
        }
    }

    fn option_arg_ptr(&self, inner_ty: &ast::Type, val: Value) -> Result<i64> {
        match val {
            Value::Option(None) => Ok(0),
            Value::Option(Some(inner)) => {
                let inner_val = inner.as_ref();
                match inner_ty {
                    ast::Type::I32 => {
                        let Value::Int(n) = inner_val else {
                            return Err(anyhow!("expected i32 inner value, got {inner_val:?}"));
                        };
                        let n_i32 = i32::try_from(*n)
                            .map_err(|_| anyhow!("i32 inner value out of range: {n}"))?;
                        let boxed = Box::new(n_i32);
                        Ok(Box::into_raw(boxed) as i64)
                    }
                    ast::Type::I64 => {
                        let Value::Int(n) = inner_val else {
                            return Err(anyhow!("expected i64 inner value, got {inner_val:?}"));
                        };
                        let boxed = Box::new(*n);
                        Ok(Box::into_raw(boxed) as i64)
                    }
                    ast::Type::F64 => {
                        let n = match inner_val {
                            Value::Float(f) => *f,
                            Value::Int(i) => *i as f64,
                            other => {
                                return Err(anyhow!("expected f64 inner value, got {other:?}"));
                            }
                        };
                        let boxed = Box::new(n);
                        Ok(Box::into_raw(boxed) as i64)
                    }
                    other => Err(anyhow!("unsupported Option inner type: {other:?}")),
                }
            }
            other => Err(anyhow!("expected Option value, got {other:?}")),
        }
    }

    fn read_option_ptr(&self, inner_ty: &ast::Type, ptr: i64) -> Result<Value> {
        if ptr == 0 {
            return Ok(Value::Option(None));
        }

        unsafe {
            match inner_ty {
                ast::Type::I32 => {
                    let val = *(ptr as *const i32);
                    Ok(Value::Option(Some(Box::new(Value::Int(val as i64)))))
                }
                ast::Type::I64 => {
                    let val = *(ptr as *const i64);
                    Ok(Value::Option(Some(Box::new(Value::Int(val)))))
                }
                ast::Type::F64 => {
                    let val = *(ptr as *const f64);
                    Ok(Value::Option(Some(Box::new(Value::Float(val)))))
                }
                other => Err(anyhow!("unsupported Option inner type: {other:?}")),
            }
        }
    }
}

#[allow(dead_code)]
pub fn run_default(file: &ast::File) -> Result<()> {
    run(file, &RunOptions::default())
}

pub fn run(file: &ast::File, options: &RunOptions) -> Result<()> {
    let mut vm = ShellVm::new(file, options.max_steps)?;
    let _ = vm.enqueue_entry(options, true)?;
    let _ = vm.run_until_idle()?;
    println!("Shell completed in {} step(s)", vm.steps());
    Ok(())
}

fn resolve_entry_agent(
    shell: &ast::Shell,
    agents: &HashMap<String, AgentRuntime>,
    options: &RunOptions,
) -> Result<String> {
    if let Some(agent) = &options.entry_agent {
        let name = agent.rsplit('.').next().unwrap_or(agent).to_string();
        if agents.contains_key(&name) {
            return Ok(name);
        }
        return Err(anyhow!("Unknown entry agent: {}", agent));
    }

    // Default: first agent with a handler for the entry message (in source order).
    for agent in &shell.agents {
        if let Some(rt) = agents.get(&agent.name) {
            if rt.handlers.contains_key(&options.entry_message) {
                return Ok(agent.name.clone());
            }
        }
    }

    Err(anyhow!(
        "No default Shell entrypoint found (expected an `on receive \"{}\"` handler)",
        options.entry_message
    ))
}

fn build_entry_args(
    params: &[ast::Param],
    raw: &HashMap<String, String>,
) -> Result<HashMap<String, Value>> {
    // Guard against typos: reject unknown args.
    for key in raw.keys() {
        if !params.iter().any(|p| &p.name == key) {
            return Err(anyhow!("Unknown message arg '{}' for entry handler", key));
        }
    }

    let mut args = HashMap::new();
    for param in params {
        let Some(text) = raw.get(&param.name) else {
            return Err(anyhow!(
                "Missing message arg '{}' for entry handler",
                param.name
            ));
        };
        let value = parse_value_for_type(&param.ty, text)?;
        args.insert(param.name.clone(), value);
    }
    Ok(args)
}

fn parse_value_for_type(ty: &ast::Type, text: &str) -> Result<Value> {
    match ty {
        ast::Type::I32 | ast::Type::I64 => {
            Ok(Value::Int(text.parse::<i64>().map_err(|e| {
                anyhow!("Failed to parse integer '{text}': {e}")
            })?))
        }
        ast::Type::Bool => Ok(Value::Bool(match text {
            "true" => true,
            "false" => false,
            _ => {
                return Err(anyhow!(
                    "Failed to parse bool '{text}' (expected true/false)"
                ))
            }
        })),
        ast::Type::F32 | ast::Type::F64 => {
            Ok(Value::Float(text.parse::<f64>().map_err(|e| {
                anyhow!("Failed to parse float '{text}': {e}")
            })?))
        }
        ast::Type::Str => Ok(Value::Str(text.to_string())),
        ast::Type::Option(inner) => {
            if text == "None" {
                return Ok(Value::Option(None));
            }
            let Some(rest) = text.strip_prefix("Some(") else {
                return Err(anyhow!(
                    "Failed to parse Option '{text}' (expected None or Some(...))"
                ));
            };
            let Some(inner_text) = rest.strip_suffix(')') else {
                return Err(anyhow!(
                    "Failed to parse Option '{text}' (expected None or Some(...))"
                ));
            };
            let inner_val = parse_value_for_type(inner, inner_text.trim())?;
            Ok(Value::Option(Some(Box::new(inner_val))))
        }
        other => Err(anyhow!("Unsupported entry arg type: {other:?}")),
    }
}

fn match_bindings(pattern: &ast::Pattern, value: &Value) -> Option<HashMap<String, Value>> {
    let mut bindings = HashMap::new();
    match pattern {
        ast::Pattern::Bool(b) => {
            if matches!(value, Value::Bool(v) if v == b) {
                Some(bindings)
            } else {
                None
            }
        }
        ast::Pattern::Literal(lit) => match (lit, value) {
            (ast::Literal::Int(a), Value::Int(b)) if a == b => Some(bindings),
            (ast::Literal::Float(a), Value::Float(b)) if a == b => Some(bindings),
            (ast::Literal::String(a), Value::Str(b)) if a == b => Some(bindings),
            (ast::Literal::Bool(a), Value::Bool(b)) if a == b => Some(bindings),
            (ast::Literal::Char(a), Value::Int(b)) if (*a as i64) == *b => Some(bindings),
            _ => None,
        },
        ast::Pattern::Ident(name) => {
            if name != "_" {
                bindings.insert(name.clone(), value.clone());
            }
            Some(bindings)
        }
        ast::Pattern::Some(name) => match value {
            Value::Option(Some(inner)) => {
                if name != "_" {
                    bindings.insert(name.clone(), inner.as_ref().clone());
                }
                Some(bindings)
            }
            _ => None,
        },
        ast::Pattern::None => match value {
            Value::Option(None) => Some(bindings),
            _ => None,
        },
        ast::Pattern::EnumVariant { .. } => None,
    }
}

fn eval_unary(op: ast::UnaryOp, val: Value) -> Result<Value> {
    match op {
        ast::UnaryOp::Neg => match val {
            Value::Int(n) => Ok(Value::Int(-n)),
            Value::Float(f) => Ok(Value::Float(-f)),
            other => Err(anyhow!("Cannot negate {other:?}")),
        },
        ast::UnaryOp::Not => Ok(Value::Bool(!val.as_bool()?)),
    }
}

fn eval_binary(op: ast::BinaryOp, left: Value, right: Value) -> Result<Value> {
    use ast::BinaryOp as Op;

    match op {
        Op::Add => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a + b)),
            (Value::Float(a), Value::Float(b)) => Ok(Value::Float(a + b)),
            (Value::Str(a), Value::Str(b)) => Ok(Value::Str(a + &b)),
            (Value::Str(a), b) => Ok(Value::Str(a + &b.to_display_string())),
            (a, Value::Str(b)) => Ok(Value::Str(a.to_display_string() + &b)),
            (a, b) => Err(anyhow!("Cannot add {a:?} and {b:?}")),
        },
        Op::Sub => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a - b)),
            (Value::Float(a), Value::Float(b)) => Ok(Value::Float(a - b)),
            (a, b) => Err(anyhow!("Cannot subtract {a:?} and {b:?}")),
        },
        Op::Mul => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a * b)),
            (Value::Float(a), Value::Float(b)) => Ok(Value::Float(a * b)),
            (a, b) => Err(anyhow!("Cannot multiply {a:?} and {b:?}")),
        },
        Op::Div => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a / b)),
            (Value::Float(a), Value::Float(b)) => Ok(Value::Float(a / b)),
            (a, b) => Err(anyhow!("Cannot divide {a:?} and {b:?}")),
        },
        Op::Mod => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a % b)),
            (a, b) => Err(anyhow!("Cannot mod {a:?} and {b:?}")),
        },
        Op::Eq => Ok(Value::Bool(left == right)),
        Op::Ne => Ok(Value::Bool(left != right)),
        Op::Lt | Op::Le | Op::Gt | Op::Ge => {
            let (a, b) = match (left, right) {
                (Value::Int(a), Value::Int(b)) => (a as f64, b as f64),
                (Value::Float(a), Value::Float(b)) => (a, b),
                (a, b) => return Err(anyhow!("Cannot compare {a:?} and {b:?}")),
            };
            Ok(Value::Bool(match op {
                Op::Lt => a < b,
                Op::Le => a <= b,
                Op::Gt => a > b,
                Op::Ge => a >= b,
                _ => false,
            }))
        }
        Op::And => Ok(Value::Bool(left.as_bool()? && right.as_bool()?)),
        Op::Or => Ok(Value::Bool(left.as_bool()? || right.as_bool()?)),
        Op::BitAnd => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a & b)),
            (a, b) => Err(anyhow!("Cannot bitwise AND {a:?} and {b:?}")),
        },
        Op::BitOr => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a | b)),
            (a, b) => Err(anyhow!("Cannot bitwise OR {a:?} and {b:?}")),
        },
        Op::BitXor => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a ^ b)),
            (a, b) => Err(anyhow!("Cannot bitwise XOR {a:?} and {b:?}")),
        },
        Op::Shl => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a << b)),
            (a, b) => Err(anyhow!("Cannot shift left {a:?} by {b:?}")),
        },
        Op::Shr => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a >> b)),
            (a, b) => Err(anyhow!("Cannot shift right {a:?} by {b:?}")),
        },
        Op::As => Ok(left),
    }
}
