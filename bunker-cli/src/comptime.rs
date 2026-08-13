//! Compile-time function evaluation for Bunker's `comptime fn` feature.
//!
//! This module provides a simple interpreter that evaluates `comptime fn` calls
//! when all arguments are compile-time constants. Results are folded back into
//! the AST as literal values.

use crate::ast::{self, BinaryOp, Block, Expr, Function, Literal, Stmt, UnaryOp};
use anyhow::{anyhow, Result};
use std::collections::HashMap;

/// Control flow result from evaluating a block or statement.
enum ControlFlow {
    /// Normal execution, continue to next statement.
    Continue(ComptimeValue),
    /// Early return from function with this value.
    Return(ComptimeValue),
    /// Break out of the nearest loop.
    Break,
    /// Continue to next iteration of the nearest loop.
    LoopContinue,
}

/// A compile-time value that can be computed by the interpreter.
#[derive(Debug, Clone, PartialEq)]
pub enum ComptimeValue {
    Int(i64),
    Float(f64),
    Bool(bool),
    Char(char),
    None,
    Some(Box<ComptimeValue>),
}

impl ComptimeValue {
    /// Convert to an AST expression for constant folding.
    pub fn to_expr(&self) -> Expr {
        match self {
            ComptimeValue::Int(n) => Expr::Literal(Literal::Int(*n)),
            ComptimeValue::Float(f) => Expr::Literal(Literal::Float(*f)),
            ComptimeValue::Bool(b) => Expr::Literal(Literal::Bool(*b)),
            ComptimeValue::Char(c) => Expr::Literal(Literal::Char(*c)),
            ComptimeValue::None => Expr::None,
            ComptimeValue::Some(inner) => Expr::Some(Box::new(inner.to_expr())),
        }
    }
}

/// Compile-time function evaluator.
pub struct ComptimeEvaluator {
    /// All comptime functions indexed by name.
    functions: HashMap<String, Function>,
    /// Maximum recursion depth to prevent infinite loops.
    max_depth: usize,
}

impl ComptimeEvaluator {
    pub fn new() -> Self {
        Self {
            functions: HashMap::new(),
            max_depth: 100,
        }
    }

    /// Register comptime functions from a kernel.
    pub fn register_kernel(&mut self, kernel: &ast::Kernel) {
        for item in &kernel.items {
            if let ast::KernelItem::ComptimeFn(func) = item {
                self.functions.insert(func.name.clone(), func.clone());
            }
        }
    }

    /// Check if a function name is a registered comptime function.
    pub fn is_comptime_fn(&self, name: &str) -> bool {
        self.functions.contains_key(name)
    }

    /// Try to evaluate a comptime function call with the given arguments.
    /// Returns None if arguments aren't all constants or evaluation fails.
    pub fn try_eval(&self, name: &str, args: &[Expr]) -> Option<ComptimeValue> {
        let func = self.functions.get(name)?;

        // Check that all arguments are compile-time constants
        let mut arg_values = Vec::new();
        for arg in args {
            let val = expr_to_comptime_value(arg)?;
            arg_values.push(val);
        }

        // Check argument count
        if arg_values.len() != func.params.len() {
            return None;
        }

        // Build initial environment with parameter bindings
        let mut env: HashMap<String, ComptimeValue> = HashMap::new();
        for (param, value) in func.params.iter().zip(arg_values) {
            env.insert(param.name.clone(), value);
        }

        // Evaluate the function body
        self.eval_block(&func.body, &mut env, 0).ok()
    }

    fn eval_block(
        &self,
        block: &Block,
        env: &mut HashMap<String, ComptimeValue>,
        depth: usize,
    ) -> Result<ComptimeValue> {
        match self.eval_block_cf(block, env, depth)? {
            ControlFlow::Continue(val) | ControlFlow::Return(val) => Ok(val),
            ControlFlow::Break => Err(anyhow!("comptime: break outside of loop")),
            ControlFlow::LoopContinue => Err(anyhow!("comptime: continue outside of loop")),
        }
    }

    /// Evaluate a block with control flow tracking.
    fn eval_block_cf(
        &self,
        block: &Block,
        env: &mut HashMap<String, ComptimeValue>,
        depth: usize,
    ) -> Result<ControlFlow> {
        if depth > self.max_depth {
            return Err(anyhow!("comptime evaluation exceeded max depth"));
        }

        let mut result = ComptimeValue::Int(0); // Default return value

        for stmt in &block.statements {
            match stmt {
                Stmt::Let { name, value, .. } => {
                    let val = self.eval_expr(value, env, depth)?;
                    env.insert(name.clone(), val);
                }
                Stmt::Assign { target, value } => {
                    if let Expr::Ident(name) = target {
                        let val = self.eval_expr(value, env, depth)?;
                        env.insert(name.clone(), val);
                    } else {
                        return Err(anyhow!("comptime: unsupported assignment target"));
                    }
                }
                Stmt::Return(Some(expr)) => {
                    let val = self.eval_expr(expr, env, depth)?;
                    return Ok(ControlFlow::Return(val));
                }
                Stmt::Return(None) => {
                    return Ok(ControlFlow::Return(ComptimeValue::Int(0)));
                }
                Stmt::If {
                    condition,
                    then_block,
                    else_block,
                } => {
                    let cond = self.eval_expr(condition, env, depth)?;
                    let ComptimeValue::Bool(b) = cond else {
                        return Err(anyhow!("comptime: if condition must be bool"));
                    };
                    if b {
                        match self.eval_block_cf(then_block, env, depth + 1)? {
                            ControlFlow::Return(val) => return Ok(ControlFlow::Return(val)),
                            ControlFlow::Break => return Ok(ControlFlow::Break),
                            ControlFlow::LoopContinue => return Ok(ControlFlow::LoopContinue),
                            ControlFlow::Continue(val) => result = val,
                        }
                    } else if let Some(else_b) = else_block {
                        match self.eval_block_cf(else_b, env, depth + 1)? {
                            ControlFlow::Return(val) => return Ok(ControlFlow::Return(val)),
                            ControlFlow::Break => return Ok(ControlFlow::Break),
                            ControlFlow::LoopContinue => return Ok(ControlFlow::LoopContinue),
                            ControlFlow::Continue(val) => result = val,
                        }
                    }
                }
                Stmt::Match { expr, arms } => {
                    let value = self.eval_expr(expr, env, depth)?;
                    for arm in arms {
                        if let Some(bindings) = self.match_pattern(&arm.pattern, &value) {
                            let mut arm_env = env.clone();
                            for (name, val) in bindings {
                                arm_env.insert(name, val);
                            }
                            match &arm.body {
                                ast::MatchBody::Expr(e) => {
                                    result = self.eval_expr(e, &arm_env, depth)?;
                                }
                                ast::MatchBody::Block(b) => {
                                    match self.eval_block_cf(b, &mut arm_env, depth + 1)? {
                                        ControlFlow::Return(val) => {
                                            return Ok(ControlFlow::Return(val))
                                        }
                                        ControlFlow::Break => return Ok(ControlFlow::Break),
                                        ControlFlow::LoopContinue => {
                                            return Ok(ControlFlow::LoopContinue)
                                        }
                                        ControlFlow::Continue(val) => result = val,
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                Stmt::Expr(expr) => {
                    result = self.eval_expr(expr, env, depth)?;
                }
                Stmt::For { var, iter, body } => {
                    // Extract range bounds (iterator must be a range expression)
                    let (start, end, inclusive) = match iter {
                        Expr::Range {
                            start,
                            end,
                            inclusive,
                        } => {
                            let start_val = self.eval_expr(start, env, depth)?;
                            let end_val = self.eval_expr(end, env, depth)?;
                            match (start_val, end_val) {
                                (ComptimeValue::Int(s), ComptimeValue::Int(e)) => {
                                    (s, e, *inclusive)
                                }
                                _ => {
                                    return Err(anyhow!(
                                        "comptime: for loop range must be integer bounds"
                                    ))
                                }
                            }
                        }
                        _ => {
                            return Err(anyhow!(
                                "comptime: for loop iterator must be a range expression"
                            ))
                        }
                    };

                    let end_val = if inclusive { end + 1 } else { end };

                    'for_loop: for i in start..end_val {
                        env.insert(var.clone(), ComptimeValue::Int(i));
                        match self.eval_block_cf(body, env, depth + 1)? {
                            ControlFlow::Return(val) => return Ok(ControlFlow::Return(val)),
                            ControlFlow::Break => break 'for_loop,
                            ControlFlow::LoopContinue => continue 'for_loop,
                            ControlFlow::Continue(val) => result = val,
                        }
                    }
                }
                Stmt::Loop(body) => {
                    const MAX_ITERATIONS: usize = 100_000;
                    let mut iterations = 0;

                    'infinite_loop: loop {
                        iterations += 1;
                        if iterations > MAX_ITERATIONS {
                            return Err(anyhow!(
                                "comptime: loop exceeded {} iterations",
                                MAX_ITERATIONS
                            ));
                        }

                        match self.eval_block_cf(body, env, depth + 1)? {
                            ControlFlow::Return(val) => return Ok(ControlFlow::Return(val)),
                            ControlFlow::Break => break 'infinite_loop,
                            ControlFlow::LoopContinue => continue 'infinite_loop,
                            ControlFlow::Continue(val) => result = val,
                        }
                    }
                }
                Stmt::While { condition, body } => {
                    const MAX_ITERATIONS: usize = 100_000;
                    let mut iterations = 0;

                    'while_loop: loop {
                        iterations += 1;
                        if iterations > MAX_ITERATIONS {
                            return Err(anyhow!(
                                "comptime: while loop exceeded {} iterations",
                                MAX_ITERATIONS
                            ));
                        }

                        // Evaluate condition
                        let cond_val = self.eval_expr(condition, env, depth)?;
                        let should_continue = match cond_val {
                            ComptimeValue::Bool(b) => b,
                            ComptimeValue::Int(n) => n != 0,
                            _ => {
                                return Err(anyhow!(
                                    "comptime: while condition must be bool or int"
                                ))
                            }
                        };

                        if !should_continue {
                            break 'while_loop;
                        }

                        match self.eval_block_cf(body, env, depth + 1)? {
                            ControlFlow::Return(val) => return Ok(ControlFlow::Return(val)),
                            ControlFlow::Break => break 'while_loop,
                            ControlFlow::LoopContinue => continue 'while_loop,
                            ControlFlow::Continue(val) => result = val,
                        }
                    }
                }
                Stmt::Break => {
                    return Ok(ControlFlow::Break);
                }
                Stmt::Continue => {
                    return Ok(ControlFlow::LoopContinue);
                }
                Stmt::Defer(_) | Stmt::Send { .. } => {
                    // Defer and Send are not supported in comptime
                    return Err(anyhow!("comptime: defer and send are not supported"));
                }
            }
        }

        Ok(ControlFlow::Continue(result))
    }

    fn eval_expr(
        &self,
        expr: &Expr,
        env: &HashMap<String, ComptimeValue>,
        depth: usize,
    ) -> Result<ComptimeValue> {
        match expr {
            Expr::Literal(lit) => Ok(match lit {
                Literal::Int(n) => ComptimeValue::Int(*n),
                Literal::Float(f) => ComptimeValue::Float(*f),
                Literal::Bool(b) => ComptimeValue::Bool(*b),
                Literal::Char(c) => ComptimeValue::Char(*c),
                _ => return Err(anyhow!("comptime: unsupported literal type")),
            }),
            Expr::Ident(name) => env
                .get(name)
                .cloned()
                .ok_or_else(|| anyhow!("comptime: undefined variable '{}'", name)),
            Expr::Binary { op, left, right } => {
                let l = self.eval_expr(left, env, depth)?;
                let r = self.eval_expr(right, env, depth)?;
                self.eval_binary(*op, l, r)
            }
            Expr::Unary { op, expr } => {
                let val = self.eval_expr(expr, env, depth)?;
                self.eval_unary(*op, val)
            }
            Expr::If {
                condition,
                then_expr,
                else_expr,
            } => {
                let cond = self.eval_expr(condition, env, depth)?;
                let ComptimeValue::Bool(b) = cond else {
                    return Err(anyhow!("comptime: if condition must be bool"));
                };
                if b {
                    self.eval_expr(then_expr, env, depth)
                } else {
                    self.eval_expr(else_expr, env, depth)
                }
            }
            Expr::Block(block) => {
                let mut local_env = env.clone();
                self.eval_block(block, &mut local_env, depth + 1)
            }
            Expr::Call { func, args } => {
                if let Expr::Ident(name) = func.as_ref() {
                    if self.is_comptime_fn(name) {
                        let mut arg_values = Vec::new();
                        for arg in args {
                            arg_values.push(self.eval_expr(arg, env, depth)?);
                        }
                        return self.call_comptime_fn(name, &arg_values, depth);
                    }
                }
                Err(anyhow!("comptime: non-comptime function calls not allowed"))
            }
            Expr::Some(inner) => {
                let val = self.eval_expr(inner, env, depth)?;
                Ok(ComptimeValue::Some(Box::new(val)))
            }
            Expr::None => Ok(ComptimeValue::None),
            Expr::Match { expr, arms } => {
                let value = self.eval_expr(expr, env, depth)?;
                for arm in arms {
                    if let Some(bindings) = self.match_pattern(&arm.pattern, &value) {
                        let mut arm_env = env.clone();
                        for (name, val) in bindings {
                            arm_env.insert(name, val);
                        }
                        return match &arm.body {
                            ast::MatchBody::Expr(e) => self.eval_expr(e, &arm_env, depth),
                            ast::MatchBody::Block(b) => {
                                let mut local = arm_env;
                                self.eval_block(b, &mut local, depth + 1)
                            }
                        };
                    }
                }
                Ok(ComptimeValue::Int(0))
            }
            _ => Err(anyhow!("comptime: unsupported expression type")),
        }
    }

    fn call_comptime_fn(
        &self,
        name: &str,
        args: &[ComptimeValue],
        depth: usize,
    ) -> Result<ComptimeValue> {
        let func = self
            .functions
            .get(name)
            .ok_or_else(|| anyhow!("comptime: unknown function '{}'", name))?;

        if args.len() != func.params.len() {
            return Err(anyhow!(
                "comptime: {} expects {} args, got {}",
                name,
                func.params.len(),
                args.len()
            ));
        }

        let mut env: HashMap<String, ComptimeValue> = HashMap::new();
        for (param, value) in func.params.iter().zip(args.iter()) {
            env.insert(param.name.clone(), value.clone());
        }

        self.eval_block(&func.body, &mut env, depth + 1)
    }

    fn eval_binary(
        &self,
        op: BinaryOp,
        left: ComptimeValue,
        right: ComptimeValue,
    ) -> Result<ComptimeValue> {
        use BinaryOp::*;
        use ComptimeValue::*;

        match (op, left, right) {
            // Integer arithmetic
            (Add, Int(a), Int(b)) => Ok(Int(a.wrapping_add(b))),
            (Sub, Int(a), Int(b)) => Ok(Int(a.wrapping_sub(b))),
            (Mul, Int(a), Int(b)) => Ok(Int(a.wrapping_mul(b))),
            (Div, Int(a), Int(b)) => {
                if b == 0 {
                    Err(anyhow!("comptime: division by zero"))
                } else {
                    Ok(Int(a / b))
                }
            }
            (Mod, Int(a), Int(b)) => {
                if b == 0 {
                    Err(anyhow!("comptime: modulo by zero"))
                } else {
                    Ok(Int(a % b))
                }
            }

            // Float arithmetic
            (Add, Float(a), Float(b)) => Ok(Float(a + b)),
            (Sub, Float(a), Float(b)) => Ok(Float(a - b)),
            (Mul, Float(a), Float(b)) => Ok(Float(a * b)),
            (Div, Float(a), Float(b)) => Ok(Float(a / b)),

            // Integer comparisons
            (Eq, Int(a), Int(b)) => Ok(Bool(a == b)),
            (Ne, Int(a), Int(b)) => Ok(Bool(a != b)),
            (Lt, Int(a), Int(b)) => Ok(Bool(a < b)),
            (Le, Int(a), Int(b)) => Ok(Bool(a <= b)),
            (Gt, Int(a), Int(b)) => Ok(Bool(a > b)),
            (Ge, Int(a), Int(b)) => Ok(Bool(a >= b)),

            // Float comparisons
            (Eq, Float(a), Float(b)) => Ok(Bool(a == b)),
            (Ne, Float(a), Float(b)) => Ok(Bool(a != b)),
            (Lt, Float(a), Float(b)) => Ok(Bool(a < b)),
            (Le, Float(a), Float(b)) => Ok(Bool(a <= b)),
            (Gt, Float(a), Float(b)) => Ok(Bool(a > b)),
            (Ge, Float(a), Float(b)) => Ok(Bool(a >= b)),

            // Bool comparisons
            (Eq, Bool(a), Bool(b)) => Ok(Bool(a == b)),
            (Ne, Bool(a), Bool(b)) => Ok(Bool(a != b)),

            // Bool logic
            (And, Bool(a), Bool(b)) => Ok(Bool(a && b)),
            (Or, Bool(a), Bool(b)) => Ok(Bool(a || b)),

            _ => Err(anyhow!("comptime: unsupported binary operation")),
        }
    }

    fn eval_unary(&self, op: UnaryOp, val: ComptimeValue) -> Result<ComptimeValue> {
        use ComptimeValue::*;
        match (op, val) {
            (UnaryOp::Neg, Int(n)) => Ok(Int(-n)),
            (UnaryOp::Neg, Float(f)) => Ok(Float(-f)),
            (UnaryOp::Not, Bool(b)) => Ok(Bool(!b)),
            _ => Err(anyhow!("comptime: unsupported unary operation")),
        }
    }

    fn match_pattern(
        &self,
        pattern: &ast::Pattern,
        value: &ComptimeValue,
    ) -> Option<HashMap<String, ComptimeValue>> {
        let mut bindings = HashMap::new();
        match (pattern, value) {
            (ast::Pattern::Literal(lit), val) => {
                let pat_val = match lit {
                    Literal::Int(n) => ComptimeValue::Int(*n),
                    Literal::Float(f) => ComptimeValue::Float(*f),
                    Literal::Bool(b) => ComptimeValue::Bool(*b),
                    Literal::Char(c) => ComptimeValue::Char(*c),
                    _ => return None,
                };
                if &pat_val == val {
                    Some(bindings)
                } else {
                    None
                }
            }
            (ast::Pattern::Bool(b), ComptimeValue::Bool(v)) if b == v => Some(bindings),
            (ast::Pattern::Ident(name), val) => {
                if name != "_" {
                    bindings.insert(name.clone(), val.clone());
                }
                Some(bindings)
            }
            (ast::Pattern::Some(name), ComptimeValue::Some(inner)) => {
                if name != "_" {
                    bindings.insert(name.clone(), inner.as_ref().clone());
                }
                Some(bindings)
            }
            (ast::Pattern::None, ComptimeValue::None) => Some(bindings),
            (ast::Pattern::EnumVariant { .. }, _) => None,
            _ => None,
        }
    }
}

/// Try to convert an AST expression to a comptime value (for constant arguments).
fn expr_to_comptime_value(expr: &Expr) -> Option<ComptimeValue> {
    match expr {
        Expr::Literal(lit) => match lit {
            Literal::Int(n) => Some(ComptimeValue::Int(*n)),
            Literal::Float(f) => Some(ComptimeValue::Float(*f)),
            Literal::Bool(b) => Some(ComptimeValue::Bool(*b)),
            Literal::Char(c) => Some(ComptimeValue::Char(*c)),
            _ => None,
        },
        Expr::Some(inner) => {
            let val = expr_to_comptime_value(inner)?;
            Some(ComptimeValue::Some(Box::new(val)))
        }
        Expr::None => Some(ComptimeValue::None),
        Expr::Unary {
            op: UnaryOp::Neg,
            expr,
        } => {
            let val = expr_to_comptime_value(expr)?;
            match val {
                ComptimeValue::Int(n) => Some(ComptimeValue::Int(-n)),
                ComptimeValue::Float(f) => Some(ComptimeValue::Float(-f)),
                _ => None,
            }
        }
        _ => None,
    }
}

// ============================================================================
// AST Transformation Pass: Constant Folding for comptime fn calls
// ============================================================================

/// Statistics from the comptime folding pass.
#[derive(Debug, Default)]
pub struct ComptimeFoldStats {
    pub calls_folded: usize,
    pub calls_skipped: usize,
}

/// Run the comptime constant folding pass on an entire file.
/// This mutates the AST in-place, replacing comptime fn calls with their evaluated results.
pub fn fold_comptime_calls(file: &mut ast::File) -> ComptimeFoldStats {
    let mut stats = ComptimeFoldStats::default();

    // Build the evaluator with all comptime functions from all kernels
    let mut evaluator = ComptimeEvaluator::new();
    for kernel in &file.kernels {
        evaluator.register_kernel(kernel);
    }

    // If no comptime functions, skip the pass
    if evaluator.functions.is_empty() {
        return stats;
    }

    // Transform each kernel
    for kernel in &mut file.kernels {
        fold_kernel(kernel, &evaluator, &mut stats);
    }

    stats
}

fn fold_kernel(kernel: &mut ast::Kernel, eval: &ComptimeEvaluator, stats: &mut ComptimeFoldStats) {
    for item in &mut kernel.items {
        match item {
            ast::KernelItem::Function(func) | ast::KernelItem::ComptimeFn(func) => {
                fold_block(&mut func.body, eval, stats);
            }
            ast::KernelItem::Const(c) => {
                fold_expr(&mut c.value, eval, stats);
            }
            ast::KernelItem::Struct(_) | ast::KernelItem::Enum(_) => {}
        }
    }
}

fn fold_block(block: &mut Block, eval: &ComptimeEvaluator, stats: &mut ComptimeFoldStats) {
    for stmt in &mut block.statements {
        fold_stmt(stmt, eval, stats);
    }
}

fn fold_stmt(stmt: &mut Stmt, eval: &ComptimeEvaluator, stats: &mut ComptimeFoldStats) {
    match stmt {
        Stmt::Let { value, .. } => {
            fold_expr(value, eval, stats);
        }
        Stmt::Assign { target, value } => {
            fold_expr(target, eval, stats);
            fold_expr(value, eval, stats);
        }
        Stmt::Return(Some(expr)) => {
            fold_expr(expr, eval, stats);
        }
        Stmt::Return(None) => {}
        Stmt::Expr(expr) => {
            fold_expr(expr, eval, stats);
        }
        Stmt::If {
            condition,
            then_block,
            else_block,
        } => {
            fold_expr(condition, eval, stats);
            fold_block(then_block, eval, stats);
            if let Some(else_b) = else_block {
                fold_block(else_b, eval, stats);
            }
        }
        Stmt::Match { expr, arms } => {
            fold_expr(expr, eval, stats);
            for arm in arms {
                match &mut arm.body {
                    ast::MatchBody::Expr(e) => fold_expr(e, eval, stats),
                    ast::MatchBody::Block(b) => fold_block(b, eval, stats),
                }
            }
        }
        Stmt::Defer(block) => {
            fold_block(block, eval, stats);
        }
        Stmt::Send { message, args, .. } => {
            fold_expr(message, eval, stats);
            for (_, arg) in args {
                fold_expr(arg, eval, stats);
            }
        }
        Stmt::For { iter, body, .. } => {
            fold_expr(iter, eval, stats);
            fold_block(body, eval, stats);
        }
        Stmt::Loop(block) => {
            fold_block(block, eval, stats);
        }
        Stmt::While { condition, body } => {
            fold_expr(condition, eval, stats);
            fold_block(body, eval, stats);
        }
        Stmt::Break | Stmt::Continue => {
            // These don't contain expressions to fold
        }
    }
}

fn fold_expr(expr: &mut Expr, eval: &ComptimeEvaluator, stats: &mut ComptimeFoldStats) {
    // First, recursively fold children
    match expr {
        Expr::Binary { left, right, .. } => {
            fold_expr(left, eval, stats);
            fold_expr(right, eval, stats);
        }
        Expr::Unary { expr: inner, .. } => {
            fold_expr(inner, eval, stats);
        }
        Expr::Call { func, args } => {
            fold_expr(func, eval, stats);
            for arg in args {
                fold_expr(arg, eval, stats);
            }
        }
        Expr::Index { expr: inner, index } => {
            fold_expr(inner, eval, stats);
            fold_expr(index, eval, stats);
        }
        Expr::Field { expr: inner, .. } => {
            fold_expr(inner, eval, stats);
        }
        Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            fold_expr(condition, eval, stats);
            fold_expr(then_expr, eval, stats);
            fold_expr(else_expr, eval, stats);
        }
        Expr::Match { expr: inner, arms } => {
            fold_expr(inner, eval, stats);
            for arm in arms {
                match &mut arm.body {
                    ast::MatchBody::Expr(e) => fold_expr(e, eval, stats),
                    ast::MatchBody::Block(b) => fold_block(b, eval, stats),
                }
            }
        }
        Expr::Block(block) => {
            fold_block(block, eval, stats);
        }
        Expr::Array(items) => {
            for item in items {
                fold_expr(item, eval, stats);
            }
        }
        Expr::Struct { fields, .. } => {
            for (_, value) in fields {
                fold_expr(value, eval, stats);
            }
        }
        Expr::Some(inner) => {
            fold_expr(inner, eval, stats);
        }
        Expr::Copy(inner) => {
            fold_expr(inner, eval, stats);
        }
        Expr::Use { args, .. } => {
            for (_, arg) in args {
                fold_expr(arg, eval, stats);
            }
        }
        Expr::Send { message, args, .. } => {
            fold_expr(message, eval, stats);
            for (_, arg) in args {
                fold_expr(arg, eval, stats);
            }
        }
        Expr::Lambda { body, .. } => {
            fold_expr(body, eval, stats);
        }
        Expr::Range { start, end, .. } => {
            fold_expr(start, eval, stats);
            fold_expr(end, eval, stats);
        }
        Expr::Cast { expr: inner, .. } => {
            fold_expr(inner, eval, stats);
        }
        // Terminals - no children to fold
        Expr::Literal(_) | Expr::Ident(_) | Expr::None => {}
    }

    // Now try to fold this expression if it's a comptime fn call
    if let Expr::Call { func, args } = expr {
        if let Expr::Ident(name) = func.as_ref() {
            if eval.is_comptime_fn(name) {
                // Try to evaluate
                if let Some(result) = eval.try_eval(name, args) {
                    // Replace the entire Call expression with the result
                    *expr = result.to_expr();
                    stats.calls_folded += 1;
                } else {
                    stats.calls_skipped += 1;
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::ast::Type;

    #[test]
    fn test_simple_addition() {
        let mut eval = ComptimeEvaluator::new();

        // Create a simple comptime fn: comptime fn add(x: i32, y: i32) -> i32 { return x + y; }
        let func = Function {
            name: "add".to_string(),
            params: vec![
                ast::Param {
                    name: "x".to_string(),
                    ty: Type::I32,
                },
                ast::Param {
                    name: "y".to_string(),
                    ty: Type::I32,
                },
            ],
            return_type: Some(Type::I32),
            body: Block {
                statements: vec![Stmt::Return(Some(Expr::Binary {
                    op: BinaryOp::Add,
                    left: Box::new(Expr::Ident("x".to_string())),
                    right: Box::new(Expr::Ident("y".to_string())),
                }))],
            },
            attributes: vec![],
        };

        eval.functions.insert("add".to_string(), func);

        let result = eval.try_eval(
            "add",
            &[
                Expr::Literal(Literal::Int(10)),
                Expr::Literal(Literal::Int(32)),
            ],
        );

        assert_eq!(result, Some(ComptimeValue::Int(42)));
    }

    #[test]
    fn test_recursive_comptime() {
        let mut eval = ComptimeEvaluator::new();

        // comptime fn factorial(n: i32) -> i32 {
        //     if n <= 1 { return 1; }
        //     return n * factorial(n - 1);
        // }
        let func = Function {
            name: "factorial".to_string(),
            params: vec![ast::Param {
                name: "n".to_string(),
                ty: Type::I32,
            }],
            return_type: Some(Type::I32),
            body: Block {
                statements: vec![
                    Stmt::If {
                        condition: Expr::Binary {
                            op: BinaryOp::Le,
                            left: Box::new(Expr::Ident("n".to_string())),
                            right: Box::new(Expr::Literal(Literal::Int(1))),
                        },
                        then_block: Block {
                            statements: vec![Stmt::Return(Some(Expr::Literal(Literal::Int(1))))],
                        },
                        else_block: None,
                    },
                    Stmt::Return(Some(Expr::Binary {
                        op: BinaryOp::Mul,
                        left: Box::new(Expr::Ident("n".to_string())),
                        right: Box::new(Expr::Call {
                            func: Box::new(Expr::Ident("factorial".to_string())),
                            args: vec![Expr::Binary {
                                op: BinaryOp::Sub,
                                left: Box::new(Expr::Ident("n".to_string())),
                                right: Box::new(Expr::Literal(Literal::Int(1))),
                            }],
                        }),
                    })),
                ],
            },
            attributes: vec![],
        };

        eval.functions.insert("factorial".to_string(), func);

        let result = eval.try_eval("factorial", &[Expr::Literal(Literal::Int(5))]);

        assert_eq!(result, Some(ComptimeValue::Int(120)));
    }
}
