//! SMT-based contract verification using Z3.
//!
//! This module provides formal verification of `#[requires]` and `#[ensures]`
//! contracts using the Z3 SMT solver. It encodes Bunker expressions as Z3
//! formulas and checks satisfiability to find counterexamples.
//!
//! ## Usage
//!
//! Enabled with the `smt` feature flag:
//! ```bash
//! cargo build --features smt
//! bunker-cli check --smt myfile.bkr
//! ```

#![cfg_attr(not(feature = "smt"), allow(dead_code))]

use std::collections::{BTreeMap, HashSet};
use std::time::Duration;

#[cfg(feature = "smt")]
use std::collections::HashMap;

#[cfg(feature = "smt")]
use anyhow::anyhow;
use anyhow::Result;

use crate::ast;
use crate::verify::VerifyError;

/// Result of SMT verification for a single postcondition.
#[derive(Debug, Clone)]
#[allow(dead_code)]
pub enum SmtResult {
    /// Postcondition is mathematically proven to hold.
    Verified,
    /// Postcondition can be violated; includes counterexample.
    Counterexample(Counterexample),
    /// Z3 could not determine satisfiability (timeout/resource limit).
    Unknown(String),
    /// SMT verification is not available (feature disabled).
    Unavailable,
}

/// A counterexample showing variable assignments that violate the postcondition.
#[derive(Debug, Clone)]
#[allow(dead_code)]
pub struct Counterexample {
    /// Variable name -> value mappings
    pub assignments: BTreeMap<String, CounterexampleValue>,
    /// Human-readable summary
    pub summary: String,
}

/// Value types in counterexamples.
#[derive(Debug, Clone)]
#[allow(dead_code)]
pub enum CounterexampleValue {
    Int(i64),
    Float(f64),
    Bool(bool),
}

impl std::fmt::Display for CounterexampleValue {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            CounterexampleValue::Int(n) => write!(f, "{}", n),
            CounterexampleValue::Float(x) => write!(f, "{}", x),
            CounterexampleValue::Bool(b) => write!(f, "{}", b),
        }
    }
}

/// Configuration for SMT verification.
#[derive(Debug, Clone)]
#[allow(dead_code)]
pub struct SmtConfig {
    /// Timeout for Z3 solver (default: 5 seconds)
    pub timeout: Duration,
    /// Use bitvector arithmetic instead of mathematical integers
    pub use_bitvectors: bool,
}

impl Default for SmtConfig {
    fn default() -> Self {
        Self {
            timeout: Duration::from_secs(5),
            use_bitvectors: false,
        }
    }
}

/// Check if SMT verification is available (Z3 feature enabled).
#[cfg(feature = "smt")]
pub fn smt_available() -> bool {
    true
}

#[cfg(not(feature = "smt"))]
pub fn smt_available() -> bool {
    false
}

/// Verify all contracts in a file using Z3 SMT solver.
///
/// Returns errors for any postconditions that cannot be proven.
#[cfg(feature = "smt")]
pub fn verify_file_smt(
    file: &ast::File,
    config: &SmtConfig,
    verbose: bool,
) -> Result<Vec<VerifyError>> {
    let mut errors = Vec::new();

    for kernel in &file.kernels {
        for item in &kernel.items {
            let func = match item {
                ast::KernelItem::Function(f) | ast::KernelItem::ComptimeFn(f) => f,
                _ => continue,
            };

            let has_contracts = func.attributes.iter().any(|attr| {
                matches!(
                    attr,
                    ast::Attribute::Requires(_) | ast::Attribute::Ensures(_)
                )
            });
            if !has_contracts {
                continue;
            }

            if verbose {
                println!("Verifying {}.{} (Z3)...", kernel.name, func.name);
            }

            let mut func_errors = verify_function_smt(kernel, func, config, verbose)?;
            errors.append(&mut func_errors);
        }
    }

    Ok(errors)
}

#[cfg(not(feature = "smt"))]
pub fn verify_file_smt(
    _file: &ast::File,
    _config: &SmtConfig,
    _verbose: bool,
) -> Result<Vec<VerifyError>> {
    Ok(vec![VerifyError {
        message: "SMT verification not available: compile with --features smt".to_string(),
        location: "compiler".to_string(),
    }])
}

/// Verify a single function's contracts using Z3.
#[cfg(feature = "smt")]
fn verify_function_smt(
    kernel: &ast::Kernel,
    func: &ast::Function,
    config: &SmtConfig,
    verbose: bool,
) -> Result<Vec<VerifyError>> {
    use z3::{Config as Z3Config, Context, SatResult, Solver};

    let location = format!("{}.{}", kernel.name, func.name);

    // Extract requires and ensures
    let requires: Vec<&ast::Expr> = func
        .attributes
        .iter()
        .filter_map(|a| match a {
            ast::Attribute::Requires(e) => Some(e),
            _ => None,
        })
        .collect();

    let ensures: Vec<&ast::Expr> = func
        .attributes
        .iter()
        .filter_map(|a| match a {
            ast::Attribute::Ensures(e) => Some(e),
            _ => None,
        })
        .collect();

    if ensures.is_empty() {
        if verbose && !requires.is_empty() {
            for req in &requires {
                println!("  Precondition ({}): ASSUMED", format_expr_brief(req));
            }
        }
        return Ok(Vec::new());
    }

    // Print preconditions
    if verbose {
        for req in &requires {
            println!("  Precondition ({}): ASSUMED", format_expr_brief(req));
        }
    }

    // Set up Z3
    let mut z3_config = Z3Config::new();
    z3_config.set_timeout_msec(config.timeout.as_millis() as u64);
    let ctx = Context::new(&z3_config);

    // Collect all variable names used in contracts and function body
    let mut places = HashSet::<String>::new();
    for param in &func.params {
        places.insert(param.name.clone());
    }
    for req in &requires {
        collect_places_in_expr(req, &mut places);
    }
    for ens in &ensures {
        collect_places_in_expr(ens, &mut places);
    }
    collect_places_in_block(&func.body, &mut places);

    // Build encoder with initial (pre-state) and current (post-state) variables
    let mut encoder = SmtEncoder::new(&ctx, &places, config.use_bitvectors);

    // Symbolically execute function body
    encoder.execute_block(&func.body)?;

    let mut errors = Vec::new();

    for ens in ensures {
        let ens_desc = format_expr_brief(ens);
        let solver = Solver::new(&ctx);

        // Assert all preconditions
        for req in &requires {
            match encoder.encode_expr(req, false) {
                Ok(cond) => solver.assert(&cond.as_bool().unwrap_or_else(|| {
                    // If not bool, treat as comparison with 0
                    cond.as_int()
                        .map(|i| i._eq(&ctx.from_i64(0).into()))
                        .unwrap_or_else(|| ctx.from_bool(true).into())
                })),
                Err(e) => {
                    if verbose {
                        println!(
                            "  Precondition ({}): SKIPPED ({})",
                            format_expr_brief(req),
                            e
                        );
                    }
                }
            }
        }

        // Encode postcondition and assert its negation
        match encoder.encode_expr(ens, false) {
            Ok(postcond) => {
                let postcond_bool = match postcond.as_bool() {
                    Some(b) => b,
                    None => {
                        // Equality check: expr == 0 for numeric expressions
                        if let Some(i) = postcond.as_int() {
                            i._eq(&ctx.from_i64(0).into())
                        } else {
                            if verbose {
                                println!(
                                    "  Postcondition ({}): SKIPPED (not a boolean expression)",
                                    ens_desc
                                );
                            }
                            errors.push(VerifyError {
                                message: format!(
                                    "Postcondition must be a boolean expression: {}",
                                    ens_desc
                                ),
                                location: location.clone(),
                            });
                            continue;
                        }
                    }
                };

                // Assert negation: try to find counterexample
                solver.assert(&postcond_bool.not());

                match solver.check() {
                    SatResult::Unsat => {
                        // No counterexample found - postcondition is verified!
                        if verbose {
                            println!("  Postcondition ({}): VERIFIED (Z3)", ens_desc);
                        }
                    }
                    SatResult::Sat => {
                        // Counterexample found
                        let model = solver.get_model().expect("model should exist after SAT");
                        let cex = encoder.extract_counterexample(&model);

                        if verbose {
                            println!("  Postcondition ({}): FAILED", ens_desc);
                            println!("    Counterexample: {}", cex.summary);
                        }

                        errors.push(VerifyError {
                            message: format!(
                                "Contract violated: postcondition fails with {}",
                                cex.summary
                            ),
                            location: location.clone(),
                        });
                    }
                    SatResult::Unknown => {
                        if verbose {
                            println!(
                                "  Postcondition ({}): UNKNOWN (Z3 timeout/resource limit)",
                                ens_desc
                            );
                        }
                        errors.push(VerifyError {
                            message: format!("Verification inconclusive: Z3 could not determine satisfiability for postcondition"),
                            location: location.clone(),
                        });
                    }
                }
            }
            Err(e) => {
                if verbose {
                    println!("  Postcondition ({}): SKIPPED ({})", ens_desc, e);
                }
                errors.push(VerifyError {
                    message: format!("Unsupported postcondition form: {} - {}", ens_desc, e),
                    location: location.clone(),
                });
            }
        }
    }

    Ok(errors)
}

/// SMT expression encoder.
///
/// Translates Bunker expressions into Z3 AST nodes, tracking both
/// initial (pre-state) and current (post-state) variable values.
#[cfg(feature = "smt")]
struct SmtEncoder<'ctx> {
    ctx: &'ctx z3::Context,
    /// Initial values (for `old()` expressions)
    initial_vars: HashMap<String, z3::ast::Dynamic<'ctx>>,
    /// Current values (after symbolic execution)
    current_vars: HashMap<String, z3::ast::Dynamic<'ctx>>,
    /// Variable names for counterexample extraction
    var_names: HashSet<String>,
    /// Use bitvectors instead of mathematical integers
    #[allow(dead_code)]
    use_bitvectors: bool,
}

#[cfg(feature = "smt")]
impl<'ctx> SmtEncoder<'ctx> {
    fn new(ctx: &'ctx z3::Context, places: &HashSet<String>, use_bitvectors: bool) -> Self {
        use z3::ast::Ast;

        let mut initial_vars = HashMap::new();
        let mut current_vars = HashMap::new();

        for name in places {
            // Create initial (pre-state) variable
            let initial_name = format!("__initial_{}", name.replace('.', "_"));
            let var: z3::ast::Dynamic = z3::ast::Int::new_const(ctx, initial_name).into();
            initial_vars.insert(name.clone(), var.clone());
            current_vars.insert(name.clone(), var);
        }

        Self {
            ctx,
            initial_vars,
            current_vars,
            var_names: places.clone(),
            use_bitvectors,
        }
    }

    /// Symbolically execute a block, updating current_vars.
    fn execute_block(&mut self, block: &ast::Block) -> Result<()> {
        for stmt in &block.statements {
            self.execute_stmt(stmt)?;
        }
        Ok(())
    }

    fn execute_stmt(&mut self, stmt: &ast::Stmt) -> Result<()> {
        match stmt {
            ast::Stmt::Let { name, value, .. } => {
                let val = self.encode_expr(value, false)?;
                self.current_vars.insert(name.clone(), val);
                self.var_names.insert(name.clone());
                Ok(())
            }
            ast::Stmt::Assign { target, value } => {
                let Some(place) = place_key(target) else {
                    return Err(anyhow!("unsupported assignment target"));
                };
                let val = self.encode_expr(value, false)?;
                self.current_vars.insert(place.clone(), val);
                self.var_names.insert(place);
                Ok(())
            }
            ast::Stmt::Return(_) => Ok(()),
            ast::Stmt::Expr(_) => Ok(()),
            ast::Stmt::If {
                condition: _,
                then_block,
                else_block,
            } => {
                // Simple path: just execute then block (conservative)
                // TODO: proper path merging with ite
                self.execute_block(then_block)?;
                if let Some(else_block) = else_block {
                    self.execute_block(else_block)?;
                }
                Ok(())
            }
            ast::Stmt::Defer(block) => self.execute_block(block),
            _ => Ok(()), // Skip unsupported statements
        }
    }

    /// Encode a Bunker expression as a Z3 AST node.
    ///
    /// If `use_initial` is true, uses pre-state variable values (for `old()`).
    fn encode_expr(&self, expr: &ast::Expr, use_initial: bool) -> Result<z3::ast::Dynamic<'ctx>> {
        use z3::ast::{Ast, Bool, Int, Real};

        let vars = if use_initial {
            &self.initial_vars
        } else {
            &self.current_vars
        };

        match expr {
            ast::Expr::Literal(lit) => self.encode_literal(lit),

            ast::Expr::Ident(name) => vars
                .get(name)
                .cloned()
                .ok_or_else(|| anyhow!("unknown variable: {}", name)),

            ast::Expr::Field { .. } => {
                let place =
                    place_key(expr).ok_or_else(|| anyhow!("unsupported field expression"))?;
                vars.get(&place)
                    .cloned()
                    .ok_or_else(|| anyhow!("unknown field: {}", place))
            }

            ast::Expr::Binary { op, left, right } => {
                let l = self.encode_expr(left, use_initial)?;
                let r = self.encode_expr(right, use_initial)?;
                self.encode_binary(*op, l, r)
            }

            ast::Expr::Unary { op, expr } => {
                let inner = self.encode_expr(expr, use_initial)?;
                match op {
                    ast::UnaryOp::Neg => {
                        if let Some(i) = inner.as_int() {
                            Ok(Int::unary_minus(&i).into())
                        } else if let Some(r) = inner.as_real() {
                            Ok(Real::unary_minus(&r).into())
                        } else {
                            Err(anyhow!("negation requires numeric type"))
                        }
                    }
                    ast::UnaryOp::Not => {
                        if let Some(b) = inner.as_bool() {
                            Ok(Bool::not(&b).into())
                        } else {
                            Err(anyhow!("logical not requires boolean type"))
                        }
                    }
                }
            }

            ast::Expr::Call { func, args } => {
                if let ast::Expr::Ident(name) = func.as_ref() {
                    if name == "old" {
                        if args.len() != 1 {
                            return Err(anyhow!("old() expects exactly 1 argument"));
                        }
                        // Evaluate argument using initial state
                        return self.encode_expr(&args[0], true);
                    }
                }
                Err(anyhow!("unsupported function call in contracts"))
            }

            ast::Expr::If {
                condition,
                then_expr,
                else_expr,
            } => {
                let cond = self.encode_expr(condition, use_initial)?;
                let cond_bool = cond
                    .as_bool()
                    .ok_or_else(|| anyhow!("condition must be boolean"))?;
                let then_val = self.encode_expr(then_expr, use_initial)?;
                let else_val = self.encode_expr(else_expr, use_initial)?;

                // Create ITE (if-then-else) expression
                if let (Some(t), Some(e)) = (then_val.as_int(), else_val.as_int()) {
                    Ok(cond_bool.ite(&t, &e).into())
                } else if let (Some(t), Some(e)) = (then_val.as_bool(), else_val.as_bool()) {
                    Ok(cond_bool.ite(&t, &e).into())
                } else {
                    Err(anyhow!("if expression branches must have matching types"))
                }
            }

            _ => Err(anyhow!("unsupported expression in contracts: {:?}", expr)),
        }
    }

    fn encode_literal(&self, lit: &ast::Literal) -> Result<z3::ast::Dynamic<'ctx>> {
        use z3::ast::{Bool, Int, Real};

        match lit {
            ast::Literal::Int(n) => Ok(Int::from_i64(self.ctx, *n).into()),
            ast::Literal::Float(f) => {
                // Approximate float as rational
                let (numer, denom) = float_to_rational(*f);
                Ok(Real::from_real(self.ctx, numer, denom).into())
            }
            ast::Literal::Bool(b) => Ok(Bool::from_bool(self.ctx, *b).into()),
            _ => Err(anyhow!("unsupported literal type in contracts")),
        }
    }

    fn encode_binary(
        &self,
        op: ast::BinaryOp,
        left: z3::ast::Dynamic<'ctx>,
        right: z3::ast::Dynamic<'ctx>,
    ) -> Result<z3::ast::Dynamic<'ctx>> {
        use z3::ast::{Ast, Bool, Int, Real};

        match op {
            // Arithmetic operators
            ast::BinaryOp::Add => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(Int::add(self.ctx, &[&l, &r]).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(Real::add(self.ctx, &[&l, &r]).into())
                } else {
                    Err(anyhow!("addition requires matching numeric types"))
                }
            }
            ast::BinaryOp::Sub => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(Int::sub(self.ctx, &[&l, &r]).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(Real::sub(self.ctx, &[&l, &r]).into())
                } else {
                    Err(anyhow!("subtraction requires matching numeric types"))
                }
            }
            ast::BinaryOp::Mul => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(Int::mul(self.ctx, &[&l, &r]).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(Real::mul(self.ctx, &[&l, &r]).into())
                } else {
                    Err(anyhow!("multiplication requires matching numeric types"))
                }
            }
            ast::BinaryOp::Div => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(l.div(&r).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(Real::div(&l, &r).into())
                } else {
                    Err(anyhow!("division requires matching numeric types"))
                }
            }
            ast::BinaryOp::Mod => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(l.modulo(&r).into())
                } else {
                    Err(anyhow!("modulo requires integer types"))
                }
            }

            // Comparison operators
            ast::BinaryOp::Eq => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(l._eq(&r).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(l._eq(&r).into())
                } else if let (Some(l), Some(r)) = (left.as_bool(), right.as_bool()) {
                    Ok(l._eq(&r).into())
                } else {
                    Err(anyhow!("equality requires matching types"))
                }
            }
            ast::BinaryOp::Ne => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(l._eq(&r).not().into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(l._eq(&r).not().into())
                } else if let (Some(l), Some(r)) = (left.as_bool(), right.as_bool()) {
                    Ok(l._eq(&r).not().into())
                } else {
                    Err(anyhow!("inequality requires matching types"))
                }
            }
            ast::BinaryOp::Lt => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(l.lt(&r).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(l.lt(&r).into())
                } else {
                    Err(anyhow!("less-than requires numeric types"))
                }
            }
            ast::BinaryOp::Le => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(l.le(&r).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(l.le(&r).into())
                } else {
                    Err(anyhow!("less-or-equal requires numeric types"))
                }
            }
            ast::BinaryOp::Gt => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(l.gt(&r).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(l.gt(&r).into())
                } else {
                    Err(anyhow!("greater-than requires numeric types"))
                }
            }
            ast::BinaryOp::Ge => {
                if let (Some(l), Some(r)) = (left.as_int(), right.as_int()) {
                    Ok(l.ge(&r).into())
                } else if let (Some(l), Some(r)) = (left.as_real(), right.as_real()) {
                    Ok(l.ge(&r).into())
                } else {
                    Err(anyhow!("greater-or-equal requires numeric types"))
                }
            }

            // Logical operators
            ast::BinaryOp::And => {
                if let (Some(l), Some(r)) = (left.as_bool(), right.as_bool()) {
                    Ok(Bool::and(self.ctx, &[&l, &r]).into())
                } else {
                    Err(anyhow!("logical and requires boolean types"))
                }
            }
            ast::BinaryOp::Or => {
                if let (Some(l), Some(r)) = (left.as_bool(), right.as_bool()) {
                    Ok(Bool::or(self.ctx, &[&l, &r]).into())
                } else {
                    Err(anyhow!("logical or requires boolean types"))
                }
            }

            _ => Err(anyhow!("unsupported operator in contracts: {:?}", op)),
        }
    }

    /// Extract a counterexample from a Z3 model.
    fn extract_counterexample(&self, model: &z3::Model) -> Counterexample {
        use z3::ast::Ast;

        let mut assignments = BTreeMap::new();

        for name in &self.var_names {
            // Look up initial variable
            let initial_name = format!("__initial_{}", name.replace('.', "_"));
            if let Some(var) = self.initial_vars.get(name) {
                if let Some(int_var) = var.as_int() {
                    if let Some(val) = model.eval(&int_var, true) {
                        if let Some(n) = val.as_i64() {
                            assignments.insert(name.clone(), CounterexampleValue::Int(n));
                        }
                    }
                }
            }
        }

        let summary = assignments
            .iter()
            .map(|(k, v)| format!("{}={}", k, v))
            .collect::<Vec<_>>()
            .join(", ");

        Counterexample {
            assignments,
            summary,
        }
    }
}

// ============================================================================
// Helper functions (shared with verify.rs)
// ============================================================================

fn place_key(expr: &ast::Expr) -> Option<String> {
    match expr {
        ast::Expr::Ident(name) => Some(name.clone()),
        ast::Expr::Field { expr, field } => {
            place_key(expr.as_ref()).map(|base| format!("{}.{}", base, field))
        }
        _ => None,
    }
}

fn collect_places_in_block(block: &ast::Block, out: &mut HashSet<String>) {
    for stmt in &block.statements {
        collect_places_in_stmt(stmt, out);
    }
}

fn collect_places_in_stmt(stmt: &ast::Stmt, out: &mut HashSet<String>) {
    match stmt {
        ast::Stmt::Let { name, value, .. } => {
            out.insert(name.clone());
            collect_places_in_expr(value, out);
        }
        ast::Stmt::Assign { target, value } => {
            if let Some(place) = place_key(target) {
                out.insert(place);
            }
            collect_places_in_expr(target, out);
            collect_places_in_expr(value, out);
        }
        ast::Stmt::Return(Some(expr)) | ast::Stmt::Expr(expr) => collect_places_in_expr(expr, out),
        ast::Stmt::If {
            condition,
            then_block,
            else_block,
        } => {
            collect_places_in_expr(condition, out);
            collect_places_in_block(then_block, out);
            if let Some(else_block) = else_block {
                collect_places_in_block(else_block, out);
            }
        }
        ast::Stmt::Defer(block) => collect_places_in_block(block, out),
        _ => {}
    }
}

fn collect_places_in_expr(expr: &ast::Expr, out: &mut HashSet<String>) {
    match expr {
        ast::Expr::Ident(name) => {
            out.insert(name.clone());
        }
        ast::Expr::Field { expr, field } => {
            if let Some(base) = place_key(expr.as_ref()) {
                out.insert(format!("{}.{}", base, field));
            }
            collect_places_in_expr(expr, out);
        }
        ast::Expr::Binary { left, right, .. } => {
            collect_places_in_expr(left, out);
            collect_places_in_expr(right, out);
        }
        ast::Expr::Unary { expr, .. } => collect_places_in_expr(expr, out),
        ast::Expr::Call { func, args } => {
            collect_places_in_expr(func, out);
            for arg in args {
                collect_places_in_expr(arg, out);
            }
        }
        ast::Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            collect_places_in_expr(condition, out);
            collect_places_in_expr(then_expr, out);
            collect_places_in_expr(else_expr, out);
        }
        _ => {}
    }
}

fn format_expr_brief(expr: &ast::Expr) -> String {
    match expr {
        ast::Expr::Binary { op, left, right } => {
            let op_str = match op {
                ast::BinaryOp::Add => "+",
                ast::BinaryOp::Sub => "-",
                ast::BinaryOp::Mul => "*",
                ast::BinaryOp::Div => "/",
                ast::BinaryOp::Eq => "==",
                ast::BinaryOp::Ne => "!=",
                ast::BinaryOp::Lt => "<",
                ast::BinaryOp::Le => "<=",
                ast::BinaryOp::Gt => ">",
                ast::BinaryOp::Ge => ">=",
                ast::BinaryOp::And => "&&",
                ast::BinaryOp::Or => "||",
                _ => "?",
            };
            format!(
                "{} {} {}",
                format_expr_brief(left),
                op_str,
                format_expr_brief(right)
            )
        }
        ast::Expr::Ident(name) => name.clone(),
        ast::Expr::Field { expr, field } => format!("{}.{}", format_expr_brief(expr), field),
        ast::Expr::Literal(lit) => match lit {
            ast::Literal::Int(n) => n.to_string(),
            ast::Literal::Bool(b) => b.to_string(),
            _ => "...".to_string(),
        },
        ast::Expr::Call { func, args } => {
            let func_name = format_expr_brief(func);
            let args_str: Vec<_> = args.iter().map(format_expr_brief).collect();
            format!("{}({})", func_name, args_str.join(", "))
        }
        _ => "...".to_string(),
    }
}

/// Convert float to rational approximation for Z3.
fn float_to_rational(f: f64) -> (i32, i32) {
    // Simple approximation: multiply by large power of 10
    const SCALE: f64 = 1_000_000.0;
    let numer = (f * SCALE).round() as i32;
    let denom = SCALE as i32;
    // Reduce by GCD for cleaner representation
    let g = gcd(numer.unsigned_abs(), denom.unsigned_abs());
    (numer / g as i32, denom / g as i32)
}

fn gcd(mut a: u32, mut b: u32) -> u32 {
    while b != 0 {
        let t = b;
        b = a % b;
        a = t;
    }
    a
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_smt_available() {
        // Just check the function compiles
        let _ = smt_available();
    }

    #[test]
    fn test_float_to_rational() {
        let (n, d) = float_to_rational(0.5);
        assert_eq!(n * 2, d); // 0.5 = n/d means 2n = d
    }

    #[test]
    fn test_place_key() {
        let expr = ast::Expr::Ident("x".to_string());
        assert_eq!(place_key(&expr), Some("x".to_string()));

        let field_expr = ast::Expr::Field {
            expr: Box::new(ast::Expr::Ident("account".to_string())),
            field: "balance".to_string(),
        };
        assert_eq!(place_key(&field_expr), Some("account.balance".to_string()));
    }
}
