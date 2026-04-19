use std::collections::{BTreeMap, HashMap, HashSet};

use anyhow::{anyhow, Result};

use crate::ast;
use crate::smt;

#[derive(Debug, Clone)]
pub struct VerifyError {
    pub message: String,
    pub location: String,
}

#[derive(Debug, Clone, PartialEq, Eq)]
struct LinExpr {
    terms: BTreeMap<String, i128>,
    constant: i128,
}

impl LinExpr {
    fn zero() -> Self {
        Self {
            terms: BTreeMap::new(),
            constant: 0,
        }
    }

    fn constant(n: i128) -> Self {
        Self {
            terms: BTreeMap::new(),
            constant: n,
        }
    }

    fn var(name: impl Into<String>) -> Self {
        let mut terms = BTreeMap::new();
        terms.insert(name.into(), 1);
        Self { terms, constant: 0 }
    }

    fn add(&self, other: &Self) -> Self {
        let mut out = self.clone();
        out.constant += other.constant;
        for (k, v) in &other.terms {
            *out.terms.entry(k.clone()).or_insert(0) += *v;
        }
        out.normalize();
        out
    }

    fn sub(&self, other: &Self) -> Self {
        let mut out = self.clone();
        out.constant -= other.constant;
        for (k, v) in &other.terms {
            *out.terms.entry(k.clone()).or_insert(0) -= *v;
        }
        out.normalize();
        out
    }

    fn neg(&self) -> Self {
        let mut out = Self {
            terms: self.terms.iter().map(|(k, v)| (k.clone(), -*v)).collect(),
            constant: -self.constant,
        };
        out.normalize();
        out
    }

    fn mul_const(&self, k: i128) -> Self {
        let mut out = Self {
            terms: self.terms.iter().map(|(n, c)| (n.clone(), c * k)).collect(),
            constant: self.constant * k,
        };
        out.normalize();
        out
    }

    fn normalize(&mut self) {
        self.terms.retain(|_, v| *v != 0);
    }

    fn eval_with_model(&self, model: &HashMap<String, i128>) -> i128 {
        let mut acc = self.constant;
        for (name, coeff) in &self.terms {
            let value = model.get(name).copied().unwrap_or(0);
            acc += coeff * value;
        }
        acc
    }
}

impl std::fmt::Display for LinExpr {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut first = true;

        for (name, coeff) in &self.terms {
            if *coeff == 0 {
                continue;
            }

            let (sign, abs) = if *coeff < 0 {
                ("-", -*coeff)
            } else {
                ("+", *coeff)
            };

            if first {
                if sign == "-" {
                    write!(f, "-")?;
                }
                first = false;
            } else {
                write!(f, " {sign} ")?;
            }

            if abs == 1 {
                write!(f, "{name}")?;
            } else {
                write!(f, "{abs}*{name}")?;
            }
        }

        if self.constant != 0 || first {
            if first {
                write!(f, "{}", self.constant)?;
            } else if self.constant < 0 {
                write!(f, " - {}", -self.constant)?;
            } else {
                write!(f, " + {}", self.constant)?;
            }
        }

        Ok(())
    }
}

#[derive(Debug, Clone)]
enum BoundRhs {
    Const(i128),
    Var(String),
}

#[derive(Debug, Clone)]
struct Bound {
    var: String,
    op: ast::BinaryOp,
    rhs: BoundRhs,
}

pub fn verify_file(file: &ast::File) -> Result<Vec<VerifyError>> {
    verify_file_with_output(file, false)
}

#[allow(dead_code)]
pub fn verify_file_verbose(file: &ast::File) -> Result<Vec<VerifyError>> {
    verify_file_with_output(file, true)
}

fn verify_file_with_output(file: &ast::File, verbose: bool) -> Result<Vec<VerifyError>> {
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
                println!("Verifying {}.{}...", kernel.name, func.name);
            }

            let mut err = verify_kernel_function_verbose(kernel, func, verbose)?;
            errors.append(&mut err);
        }
    }

    Ok(errors)
}

#[allow(dead_code)]
fn verify_kernel_function(kernel: &ast::Kernel, func: &ast::Function) -> Result<Vec<VerifyError>> {
    verify_kernel_function_verbose(kernel, func, false)
}

fn verify_kernel_function_verbose(
    kernel: &ast::Kernel,
    func: &ast::Function,
    verbose: bool,
) -> Result<Vec<VerifyError>> {
    let location = format!("{}.{}", kernel.name, func.name);

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

    // Print preconditions as assumed
    if verbose {
        for req in &requires {
            println!("  Precondition ({}): ASSUMED", format_expr_brief(req));
        }
    }

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

    let mut initial_env = HashMap::<String, LinExpr>::new();
    for name in places {
        initial_env.insert(name.clone(), LinExpr::var(name));
    }

    let mut current_env = initial_env.clone();
    symbolic_execute_block(&func.body, &mut current_env, &initial_env).map_err(|e| {
        anyhow!(
            "Contract verification only supports a small subset of Kernel statements today ({location}): {e}"
        )
    })?;

    let bounds = extract_bounds(&requires);

    let mut errors = Vec::new();
    for ens in ensures {
        let ens_desc = format_expr_brief(ens);
        match ens {
            ast::Expr::Binary {
                op: ast::BinaryOp::Eq,
                left,
                right,
            } => {
                let left = eval_lin(left, &current_env, &initial_env)?;
                let right = eval_lin(right, &current_env, &initial_env)?;
                let diff = left.sub(&right);
                if diff == LinExpr::zero() {
                    if verbose {
                        println!("  Postcondition ({}): VERIFIED", ens_desc);
                    }
                    continue;
                }

                let model = build_counterexample(&diff, &bounds);
                let details = if model.is_empty() {
                    format!("(could not synthesize a counterexample; non-zero diff: {diff})")
                } else {
                    let model_str = model
                        .iter()
                        .map(|(k, v)| format!("{k}={v}"))
                        .collect::<Vec<_>>()
                        .join(", ");
                    format!("counterexample: {model_str} (diff: {diff})")
                };

                if verbose {
                    println!("  Postcondition ({}): FAILED", ens_desc);
                    println!("    {}", details);
                }

                errors.push(VerifyError {
                    message: format!("Contract violated: postcondition not provable; {details}"),
                    location: location.clone(),
                });
            }
            other => {
                if verbose {
                    println!("  Postcondition ({}): SKIPPED (unsupported form)", ens_desc);
                }
                errors.push(VerifyError {
                    message: format!(
                        "Unsupported postcondition form for verification today: {other:?}"
                    ),
                    location: location.clone(),
                });
            }
        }
    }

    Ok(errors)
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
        ast::Stmt::Match { expr, arms } => {
            collect_places_in_expr(expr, out);
            for arm in arms {
                match &arm.body {
                    ast::MatchBody::Expr(expr) => collect_places_in_expr(expr, out),
                    ast::MatchBody::Block(block) => collect_places_in_block(block, out),
                }
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
                out.insert(format!("{base}.{field}"));
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
        ast::Expr::Index { expr, index } => {
            collect_places_in_expr(expr, out);
            collect_places_in_expr(index, out);
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
        ast::Expr::Match { expr, arms } => {
            collect_places_in_expr(expr, out);
            for arm in arms {
                match &arm.body {
                    ast::MatchBody::Expr(expr) => collect_places_in_expr(expr, out),
                    ast::MatchBody::Block(block) => collect_places_in_block(block, out),
                }
            }
        }
        ast::Expr::Block(block) => collect_places_in_block(block, out),
        ast::Expr::Some(expr) => collect_places_in_expr(expr, out),
        ast::Expr::None => {}
        ast::Expr::Array(items) => {
            for item in items {
                collect_places_in_expr(item, out);
            }
        }
        ast::Expr::Struct { fields, .. } => {
            for (_, value) in fields {
                collect_places_in_expr(value, out);
            }
        }
        ast::Expr::Use { args, .. } | ast::Expr::Send { args, .. } => {
            for (_, value) in args {
                collect_places_in_expr(value, out);
            }
        }
        ast::Expr::Copy(expr) => collect_places_in_expr(expr, out),
        ast::Expr::Range { start, end, .. } => {
            collect_places_in_expr(start, out);
            collect_places_in_expr(end, out);
        }
        ast::Expr::Cast { expr, .. } => collect_places_in_expr(expr, out),
        ast::Expr::Literal(_) | ast::Expr::Lambda { .. } => {}
    }
}

fn symbolic_execute_block(
    block: &ast::Block,
    env: &mut HashMap<String, LinExpr>,
    initial: &HashMap<String, LinExpr>,
) -> Result<()> {
    let mut defers: Vec<&ast::Block> = Vec::new();
    for stmt in &block.statements {
        match stmt {
            ast::Stmt::Defer(block) => defers.push(block),
            _ => symbolic_execute_stmt(stmt, env, initial)?,
        }
    }
    for deferred in defers.into_iter().rev() {
        symbolic_execute_block(deferred, env, initial)?;
    }
    Ok(())
}

fn symbolic_execute_stmt(
    stmt: &ast::Stmt,
    env: &mut HashMap<String, LinExpr>,
    initial: &HashMap<String, LinExpr>,
) -> Result<()> {
    match stmt {
        ast::Stmt::Let { name, value, .. } => {
            let val = eval_lin(value, env, initial)?;
            env.insert(name.clone(), val);
            Ok(())
        }
        ast::Stmt::Assign { target, value } => {
            let Some(place) = place_key(target) else {
                return Err(anyhow!("unsupported assignment target: {target:?}"));
            };
            let val = eval_lin(value, env, initial)?;
            env.insert(place, val);
            Ok(())
        }
        ast::Stmt::Return(_) => Ok(()),
        ast::Stmt::Expr(_) => Ok(()),
        ast::Stmt::Defer(_) => Err(anyhow!("internal error: defer handled at block scope")),
        other => Err(anyhow!("unsupported statement: {other:?}")),
    }
}

fn eval_lin(
    expr: &ast::Expr,
    env: &HashMap<String, LinExpr>,
    initial: &HashMap<String, LinExpr>,
) -> Result<LinExpr> {
    match expr {
        ast::Expr::Literal(ast::Literal::Int(n)) => Ok(LinExpr::constant(*n as i128)),
        ast::Expr::Literal(ast::Literal::Char(c)) => Ok(LinExpr::constant(*c as i128)),
        ast::Expr::Ident(name) => Ok(env
            .get(name)
            .cloned()
            .unwrap_or_else(|| LinExpr::var(name.clone()))),
        ast::Expr::Field { .. } => {
            let Some(place) = place_key(expr) else {
                return Err(anyhow!("unsupported field expression: {expr:?}"));
            };
            Ok(env
                .get(&place)
                .cloned()
                .unwrap_or_else(|| LinExpr::var(place)))
        }
        ast::Expr::Unary { op, expr } => {
            let inner = eval_lin(expr, env, initial)?;
            match op {
                ast::UnaryOp::Neg => Ok(inner.neg()),
                ast::UnaryOp::Not => Err(anyhow!("expected numeric expression, got logical not")),
            }
        }
        ast::Expr::Binary { op, left, right } => {
            let left = eval_lin(left, env, initial)?;
            let right = eval_lin(right, env, initial)?;
            match op {
                ast::BinaryOp::Add => Ok(left.add(&right)),
                ast::BinaryOp::Sub => Ok(left.sub(&right)),
                ast::BinaryOp::Mul => {
                    if right.terms.is_empty() {
                        return Ok(left.mul_const(right.constant));
                    }
                    if left.terms.is_empty() {
                        return Ok(right.mul_const(left.constant));
                    }
                    Err(anyhow!("unsupported multiplication of non-constants"))
                }
                _ => Err(anyhow!("unsupported numeric operator: {op:?}")),
            }
        }
        ast::Expr::Call { func, args } => {
            if let ast::Expr::Ident(name) = func.as_ref() {
                if name == "old" {
                    if args.len() != 1 {
                        return Err(anyhow!("old() expects 1 argument"));
                    }
                    return eval_lin(&args[0], initial, initial);
                }
            }
            Err(anyhow!(
                "unsupported call expression in contracts: {expr:?}"
            ))
        }
        other => Err(anyhow!("unsupported expression in contracts: {other:?}")),
    }
}

fn place_key(expr: &ast::Expr) -> Option<String> {
    match expr {
        ast::Expr::Ident(name) => Some(name.clone()),
        ast::Expr::Field { expr, field } => {
            place_key(expr.as_ref()).map(|base| format!("{base}.{field}"))
        }
        _ => None,
    }
}

fn extract_bounds(requires: &[&ast::Expr]) -> Vec<Bound> {
    let mut out = Vec::new();
    for expr in requires {
        extract_bounds_from_expr(expr, &mut out);
    }
    out
}

fn extract_bounds_from_expr(expr: &ast::Expr, out: &mut Vec<Bound>) {
    match expr {
        ast::Expr::Binary {
            op: ast::BinaryOp::And,
            left,
            right,
        } => {
            extract_bounds_from_expr(left, out);
            extract_bounds_from_expr(right, out);
        }
        ast::Expr::Binary { op, left, right } => {
            let Some(var) = place_key(left) else {
                return;
            };

            if let ast::Expr::Literal(ast::Literal::Int(n)) = right.as_ref() {
                out.push(Bound {
                    var,
                    op: *op,
                    rhs: BoundRhs::Const(*n as i128),
                });
                return;
            }

            let Some(rhs_var) = place_key(right) else {
                return;
            };

            out.push(Bound {
                var,
                op: *op,
                rhs: BoundRhs::Var(rhs_var),
            });
        }
        _ => {}
    }
}

fn build_counterexample(diff: &LinExpr, bounds: &[Bound]) -> BTreeMap<String, i128> {
    let mut vars: HashSet<String> = diff.terms.keys().cloned().collect();
    for bound in bounds {
        vars.insert(bound.var.clone());
        if let BoundRhs::Var(v) = &bound.rhs {
            vars.insert(v.clone());
        }
    }

    let mut model: HashMap<String, i128> = vars.iter().map(|v| (v.clone(), 0)).collect();

    // Best-effort satisfy bounds.
    for _ in 0..16 {
        let mut changed = false;
        for bound in bounds {
            let rhs_val = match &bound.rhs {
                BoundRhs::Const(c) => *c,
                BoundRhs::Var(v) => *model.get(v).unwrap_or(&0),
            };

            let entry = model.entry(bound.var.clone()).or_insert(0);
            match bound.op {
                ast::BinaryOp::Gt => {
                    let want = rhs_val + 1;
                    if *entry < want {
                        *entry = want;
                        changed = true;
                    }
                }
                ast::BinaryOp::Ge => {
                    let want = rhs_val;
                    if *entry < want {
                        *entry = want;
                        changed = true;
                    }
                }
                ast::BinaryOp::Eq => {
                    if *entry != rhs_val {
                        *entry = rhs_val;
                        changed = true;
                    }
                }
                _ => {}
            }
        }
        if !changed {
            break;
        }
    }

    let diff_value = diff.eval_with_model(&model);
    if diff_value == 0 {
        if let Some(var) = diff.terms.keys().next().cloned() {
            let entry = model.entry(var).or_insert(0);
            *entry += 1;
        }
    }

    let mut out = BTreeMap::new();
    for name in diff.terms.keys() {
        if let Some(v) = model.get(name).copied() {
            out.insert(name.clone(), v);
        }
    }
    for bound in bounds {
        if let Some(v) = model.get(&bound.var).copied() {
            out.entry(bound.var.clone()).or_insert(v);
        }
        if let BoundRhs::Var(rhs) = &bound.rhs {
            if let Some(v) = model.get(rhs).copied() {
                out.entry(rhs.clone()).or_insert(v);
            }
        }
    }
    out
}

// ============================================================================
// SMT Integration
// ============================================================================

/// Verify contracts in a file using the specified verification method.
///
/// If `use_smt` is true and Z3 is available, uses SMT solving.
/// Otherwise, falls back to lightweight linear expression verification.
pub fn verify_file_with_mode(
    file: &ast::File,
    use_smt: bool,
    verbose: bool,
) -> Result<Vec<VerifyError>> {
    if use_smt {
        if smt::smt_available() {
            let config = smt::SmtConfig::default();
            smt::verify_file_smt(file, &config, verbose)
        } else {
            if verbose {
                println!("Note: SMT verification requested but Z3 not available. Using lightweight verification.");
            }
            verify_file_with_output(file, verbose)
        }
    } else {
        verify_file_with_output(file, verbose)
    }
}
