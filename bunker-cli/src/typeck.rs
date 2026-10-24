use crate::ast::{self, BinaryOp, Expr, Literal, Stmt, Type, UnaryOp};
use crate::builtins::{self, BuiltinArgRule};
use anyhow::Result;
use std::collections::{HashMap, HashSet};

#[derive(Debug, Clone)]
pub struct TypeError {
    pub message: String,
    pub location: String,
}

type AgentMessageParams = HashMap<String, Vec<(String, ast::Type)>>;
type ShellAgentMessages = HashMap<String, AgentMessageParams>;
type AgentStateFields = HashMap<String, ast::Type>;
type ShellAgentState = HashMap<String, AgentStateFields>;
type ViewAgentMessages = HashMap<String, ShellAgentMessages>;
type ViewAgentState = HashMap<String, ShellAgentState>;

pub struct TypeChecker {
    // Type environment: variable name -> type
    variables: HashMap<String, Type>,
    // Function signatures: name -> (params, return_type)
    functions: HashMap<String, (Vec<Type>, Option<Type>)>,
    // Struct definitions: name -> fields
    structs: HashMap<String, Vec<(String, Type)>>,
    // Unit enum definitions: name -> variant names in declaration order
    enums: HashMap<String, Vec<String>>,
    // Parallel payload types for each enum variant; None means a unit variant.
    enum_payloads: HashMap<String, Vec<Vec<Type>>>,
    // Type aliases: name -> target type
    type_aliases: HashMap<String, Type>,
    // Errors collected during type checking
    errors: Vec<TypeError>,
    // Current function return type (for checking return statements)
    current_return_type: Option<Type>,
    // Loop label stack for break/continue validation
    loop_labels: Vec<Option<String>>,
    // Move tracking: variables that have been moved
    moved_vars: HashSet<String>,
    // Where each variable was moved (for error messages)
    moved_locations: HashMap<String, String>,
}

fn pattern_is_irrefutable(pat: &ast::Pattern) -> bool {
    match pat {
        ast::Pattern::Ident(_) | ast::Pattern::Unit => true,
        ast::Pattern::Tuple(sub_pats) => sub_pats.iter().all(pattern_is_irrefutable),
        ast::Pattern::Struct { fields, .. } => fields.iter().all(|(_, p)| pattern_is_irrefutable(p)),
        _ => false,
    }
}

fn patterns_exhaust_type(
    patterns: &[&ast::Pattern],
    ty: &Type,
    enums: &HashMap<String, Vec<String>>,
) -> bool {
    if patterns.iter().any(|p| pattern_is_irrefutable(p)) {
        return true;
    }
    match ty {
        Type::Bool => {
            let mut seen_true = false;
            let mut seen_false = false;
            for p in patterns {
                match p {
                    ast::Pattern::Bool(b) | ast::Pattern::Literal(Literal::Bool(b)) => {
                        if *b {
                            seen_true = true;
                        } else {
                            seen_false = true;
                        }
                    }
                    _ => {}
                }
            }
            seen_true && seen_false
        }
        Type::Option(inner) => {
            let mut some_subpats = Vec::new();
            let mut seen_none = false;
            for p in patterns {
                match p {
                    ast::Pattern::Some(sub) => some_subpats.push(sub.as_ref()),
                    ast::Pattern::None => seen_none = true,
                    _ => {}
                }
            }
            seen_none && patterns_exhaust_type(&some_subpats, inner, enums)
        }
        Type::Result(ok_ty, err_ty) => {
            let mut ok_subpats = Vec::new();
            let mut err_subpats = Vec::new();
            for p in patterns {
                match p {
                    ast::Pattern::ResultOk(sub) => ok_subpats.push(sub.as_ref()),
                    ast::Pattern::ResultErr(sub) => err_subpats.push(sub.as_ref()),
                    _ => {}
                }
            }
            patterns_exhaust_type(&ok_subpats, ok_ty, enums)
                && patterns_exhaust_type(&err_subpats, err_ty, enums)
        }
        Type::Named(enum_name) => {
            if let Some(variants) = enums.get(enum_name) {
                let mut seen_variants = HashSet::new();
                for p in patterns {
                    if let ast::Pattern::EnumVariant {
                        enum_name: name,
                        variant,
                        ..
                    } = p
                    {
                        if name == enum_name {
                            seen_variants.insert(variant.as_str());
                        }
                    }
                }
                variants.iter().all(|v| seen_variants.contains(v.as_str()))
            } else {
                false
            }
        }
        _ => false,
    }
}

impl TypeChecker {
    pub fn new() -> Self {
        let mut tc = Self {
            variables: HashMap::new(),
            functions: HashMap::new(),
            structs: HashMap::new(),
            enums: HashMap::new(),
            enum_payloads: HashMap::new(),
            type_aliases: HashMap::new(),
            errors: Vec::new(),
            current_return_type: None,
            loop_labels: Vec::new(),
            moved_vars: HashSet::new(),
            moved_locations: HashMap::new(),
        };
        // Register built-in functions
        tc.functions
            .insert("log".to_string(), (vec![Type::Str], None));
        tc.functions
            .insert("print".to_string(), (vec![Type::Str], None));
        tc.functions
            .insert("println".to_string(), (vec![Type::Str], None));
        tc.functions
            .insert("panic".to_string(), (vec![Type::Str], None));
        tc.functions
            .insert("assert".to_string(), (vec![Type::Bool], None));
        tc
    }

    pub fn resolve_alias(&self, ty: &Type) -> Type {
        let mut current = ty.clone();
        let mut depth = 0;
        loop {
            match &current {
                Type::Named(name) => {
                    if let Some(target) = self.type_aliases.get(name) {
                        current = target.clone();
                        depth += 1;
                        if depth > 32 {
                            return current;
                        }
                    } else {
                        return current;
                    }
                }
                Type::Option(inner) => {
                    return Type::Option(Box::new(self.resolve_alias(inner)));
                }
                Type::Result(ok, err) => {
                    return Type::Result(
                        Box::new(self.resolve_alias(ok)),
                        Box::new(self.resolve_alias(err)),
                    );
                }
                Type::Vec(elem) => {
                    return Type::Vec(Box::new(self.resolve_alias(elem)));
                }
                Type::HashMap(k, v) => {
                    return Type::HashMap(
                        Box::new(self.resolve_alias(k)),
                        Box::new(self.resolve_alias(v)),
                    );
                }
                Type::Array(elem, len) => {
                    return Type::Array(Box::new(self.resolve_alias(elem)), *len);
                }
                Type::Tuple(elems) => {
                    return Type::Tuple(elems.iter().map(|e| self.resolve_alias(e)).collect());
                }
                Type::Ref { mutable, ty } => {
                    return Type::Ref {
                        mutable: *mutable,
                        ty: Box::new(self.resolve_alias(ty)),
                    };
                }
                _ => return current,
            }
        }
    }

    pub fn check_kernel(&mut self, kernel: &ast::Kernel) -> Result<Vec<TypeError>> {
        // Pre-pass: collect all type aliases and validate uniqueness
        for item in &kernel.items {
            if let ast::KernelItem::TypeAlias(a) = item {
                if self.type_aliases.contains_key(&a.name) {
                    self.errors.push(TypeError {
                        message: format!("Duplicate type alias '{}'", a.name),
                        location: a.name.clone(),
                    });
                }
                self.type_aliases.insert(a.name.clone(), a.target.clone());
            }
        }

        // Check for cyclic aliases
        for name in self.type_aliases.keys() {
            let mut visited = HashSet::new();
            let mut curr = name.clone();
            visited.insert(curr.clone());
            while let Some(Type::Named(next)) = self.type_aliases.get(&curr) {
                if visited.contains(next) {
                    self.errors.push(TypeError {
                        message: format!("Cyclic type alias detected involving '{}'", name),
                        location: name.clone(),
                    });
                    break;
                }
                visited.insert(next.clone());
                curr = next.clone();
            }
        }
        // First pass: collect all struct, enum, and function signatures
        for item in &kernel.items {
            match item {
                ast::KernelItem::TypeAlias(a) => {
                    if self.structs.contains_key(&a.name) {
                        self.errors.push(TypeError {
                            message: format!("Name '{}' is already declared as a struct", a.name),
                            location: a.name.clone(),
                        });
                    }
                    if self.enums.contains_key(&a.name) {
                        self.errors.push(TypeError {
                            message: format!("Name '{}' is already declared as an enum", a.name),
                            location: a.name.clone(),
                        });
                    }
                }
                ast::KernelItem::Struct(s) => {
                    let fields: Vec<(String, Type)> = s
                        .fields
                        .iter()
                        .map(|f| (f.name.clone(), self.resolve_alias(&f.ty)))
                        .collect();
                    if self.enums.contains_key(&s.name) {
                        self.errors.push(TypeError {
                            message: format!("Name '{}' is already declared as an enum", s.name),
                            location: s.name.clone(),
                        });
                    }
                    if self.type_aliases.contains_key(&s.name) {
                        self.errors.push(TypeError {
                            message: format!("Name '{}' is already declared as a type alias", s.name),
                            location: s.name.clone(),
                        });
                    }
                    self.structs.insert(s.name.clone(), fields);
                }
                ast::KernelItem::Enum(e) => {
                    if self.structs.contains_key(&e.name) {
                        self.errors.push(TypeError {
                            message: format!("Name '{}' is already declared as a struct", e.name),
                            location: e.name.clone(),
                        });
                    }
                    if self.type_aliases.contains_key(&e.name) {
                        self.errors.push(TypeError {
                            message: format!("Name '{}' is already declared as a type alias", e.name),
                            location: e.name.clone(),
                        });
                    }
                    if e.variants.is_empty() {
                        self.errors.push(TypeError {
                            message: format!("Enum '{}' must declare at least one variant", e.name),
                            location: e.name.clone(),
                        });
                    }
                    let mut seen = HashSet::new();
                    for variant in &e.variants {
                        if !seen.insert(variant.name.clone()) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Duplicate variant '{}' in enum '{}'",
                                    variant.name, e.name
                                ),
                                location: e.name.clone(),
                            });
                        }
                    }
                    self.enums.insert(e.name.clone(), e.variant_names());
                    self.enum_payloads.insert(
                        e.name.clone(),
                        e.variants
                            .iter()
                            .map(|variant| variant.payloads.iter().map(|p| self.resolve_alias(p)).collect())
                            .collect(),
                    );
                }
                ast::KernelItem::Function(f) | ast::KernelItem::ComptimeFn(f) => {
                    let param_types: Vec<Type> = f.params.iter().map(|p| self.resolve_alias(&p.ty)).collect();
                    self.functions
                        .insert(f.name.clone(), (param_types, f.return_type.as_ref().map(|t| self.resolve_alias(t))));
                }
                ast::KernelItem::Const(c) => {
                    self.variables.insert(c.name.clone(), self.resolve_alias(&c.ty));
                }
            }
        }

        // Second pass: type check constants and function bodies
        for item in &kernel.items {
            match item {
                ast::KernelItem::Const(c) => {
                    let actual = self.infer_expr(&c.value, &c.name)?;
                    if !self.types_compatible(&c.ty, &actual) {
                        self.errors.push(TypeError {
                            message: format!(
                                "Constant '{}' type mismatch: expected {:?}, got {:?}",
                                c.name, c.ty, actual
                            ),
                            location: c.name.clone(),
                        });
                    }
                }
                ast::KernelItem::Function(f) => {
                    self.check_function(f)?;
                }
                _ => {}
            }
        }

        Ok(self.errors.clone())
    }

    fn check_function(&mut self, func: &ast::Function) -> Result<()> {
        // Save and set return type context
        let prev_return = self.current_return_type.take();
        self.current_return_type = func.return_type.as_ref().map(|t| self.resolve_alias(t));

        // Save current variable scope and move tracking
        let saved_vars = self.variables.clone();
        let saved_moved = self.moved_vars.clone();
        let saved_moved_locations = self.moved_locations.clone();

        // Add parameters to scope
        for param in &func.params {
            self.variables.insert(param.name.clone(), self.resolve_alias(&param.ty));
        }

        // Check function body
        self.check_block(&func.body, &func.name)?;

        // Restore scope and move tracking
        self.variables = saved_vars;
        self.moved_vars = saved_moved;
        self.moved_locations = saved_moved_locations;
        self.current_return_type = prev_return;

        Ok(())
    }

    fn check_block(&mut self, block: &ast::Block, context: &str) -> Result<Option<Type>> {
        let mut last_type = None;
        for stmt in &block.statements {
            last_type = self.check_stmt(stmt, context)?;
        }
        Ok(last_type)
    }

    fn check_stmt(&mut self, stmt: &Stmt, context: &str) -> Result<Option<Type>> {
        match stmt {
            Stmt::Let { name, ty, value } => {
                // Check for None without type annotation
                if ty.is_none() && matches!(value, Expr::None) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Cannot infer type of '{}': None requires explicit Option<T> type annotation",
                            name
                        ),
                        location: context.to_string(),
                    });
                    self.variables
                        .insert(name.clone(), Type::Option(Box::new(Type::I32)));
                    return Ok(None);
                }

                // Check for empty array without type annotation
                if ty.is_none() && matches!(value, Expr::Array(elements) if elements.is_empty()) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Cannot infer type of '{}': empty array requires explicit [T; N] type annotation",
                            name
                        ),
                        location: context.to_string(),
                    });
                    self.variables
                        .insert(name.clone(), Type::Array(Box::new(Type::I32), 0));
                    return Ok(None);
                }

                // Check for Result constructor without type annotation
                if ty.is_none() {
                    let is_unannotated_result = match value {
                        Expr::Call { func, .. } => {
                            if let Expr::Ident(fname) = func.as_ref() {
                                fname == "result_ok" || fname == "result_err" || fname == "Ok" || fname == "Err"
                            } else {
                                false
                            }
                        }
                        _ => false,
                    };
                    if is_unannotated_result {
                        self.errors.push(TypeError {
                            message: format!(
                                "Cannot infer type of '{}': Result constructor requires explicit Result<T, E> type annotation or contextual type",
                                name
                            ),
                            location: context.to_string(),
                        });
                        self.variables.insert(
                            name.clone(),
                            Type::Result(Box::new(Type::I64), Box::new(Type::Str)),
                        );
                        return Ok(None);
                    }
                }

                // Check for collection constructor (vec_new, hashmap_new) without type annotation
                if ty.is_none() {
                    let is_vec = match value {
                        Expr::Call { func, .. } => {
                            if let Expr::Ident(fname) = func.as_ref() {
                                fname == "vec_new"
                            } else {
                                false
                            }
                        }
                        _ => false,
                    };
                    let is_map = match value {
                        Expr::Call { func, .. } => {
                            if let Expr::Ident(fname) = func.as_ref() {
                                fname == "hashmap_new"
                            } else {
                                false
                            }
                        }
                        _ => false,
                    };
                    if is_vec || is_map {
                        let cname = if is_vec { "Vec" } else { "HashMap" };
                        let annot = if is_vec { "Vec<T>" } else { "HashMap<K, V>" };
                        self.errors.push(TypeError {
                            message: format!(
                                "Cannot infer type of '{}': {} constructor requires explicit {} type annotation or contextual type",
                                name, cname, annot
                            ),
                            location: context.to_string(),
                        });
                        if is_vec {
                            self.variables.insert(
                                name.clone(),
                                Type::Vec(Box::new(Type::I64)),
                            );
                        } else {
                            self.variables.insert(
                                name.clone(),
                                Type::HashMap(Box::new(Type::Str), Box::new(Type::I64)),
                            );
                        }
                        return Ok(None);
                    }
                }

                let resolved_hint = ty.as_ref().map(|t| self.resolve_alias(t));
                let inferred = self.infer_expr_with_hint(value, context, resolved_hint.as_ref())?;

                // Move semantics: if value is a non-copy identifier (not wrapped in `copy`),
                // mark the source variable as moved
                if let Expr::Ident(source_name) = value {
                    if !self.is_copy_type(&inferred) {
                        self.moved_vars.insert(source_name.clone());
                        self.moved_locations.insert(
                            source_name.clone(),
                            format!("let {} = {} in {}", name, source_name, context),
                        );
                    }
                }

                if let Some(declared) = ty {
                    let resolved = self.resolve_alias(declared);
                    if !self.types_compatible(&resolved, &inferred) {
                        self.errors.push(TypeError {
                            message: format!(
                                "Type mismatch in let binding '{}': declared {:?}, got {:?}",
                                name, declared, inferred
                            ),
                            location: context.to_string(),
                        });
                    }
                    self.variables.insert(name.clone(), resolved);
                } else {
                    self.variables.insert(name.clone(), inferred);
                }
                Ok(None)
            }
            Stmt::Assign { target, value } => {
                let target_ty = self.infer_expr(target, context)?;
                let value_ty = self.infer_expr(value, context)?;

                if !self.types_compatible(&target_ty, &value_ty) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Type mismatch in assignment: expected {:?}, got {:?}",
                            target_ty, value_ty
                        ),
                        location: context.to_string(),
                    });
                }
                Ok(None)
            }
            Stmt::Return(expr) => {
                let expected_return = self.current_return_type.clone();
                let ret_ty = if let Some(e) = expr {
                    Some(self.infer_expr_with_hint(e, context, expected_return.as_ref())?)
                } else {
                    None
                };

                if let Some(expected) = &expected_return {
                    match &ret_ty {
                        Some(actual) if !self.types_compatible(expected, actual) => {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Return type mismatch: expected {:?}, got {:?}",
                                    expected, actual
                                ),
                                location: context.to_string(),
                            });
                        }
                        None => {
                            if *expected != Type::Unit {
                                self.errors.push(TypeError {
                                    message: format!("Missing return value: expected {:?}", expected),
                                    location: context.to_string(),
                                });
                            }
                        }
                        _ => {}
                    }
                } else if let Some(actual) = &ret_ty {
                    if *actual != Type::Unit {
                        self.errors.push(TypeError {
                            message: "Returning value from void function".to_string(),
                            location: context.to_string(),
                        });
                    }
                }
                Ok(ret_ty)
            }
            Stmt::If {
                condition,
                then_block,
                else_block,
            } => {
                let cond_ty = self.infer_expr(condition, context)?;
                if cond_ty != Type::Bool {
                    self.errors.push(TypeError {
                        message: format!("Condition must be bool, got {:?}", cond_ty),
                        location: context.to_string(),
                    });
                }
                self.check_block(then_block, context)?;
                if let Some(eb) = else_block {
                    self.check_block(eb, context)?;
                }
                Ok(None)
            }
            Stmt::For { label, var, iter, body } => {
                // Determine element type based on iterator expression
                let elem_ty = match iter {
                    // Range expressions: the element type is the range bound type
                    Expr::Range { start, .. } => self.infer_expr(start, context)?,
                    // For arrays, the element type is the array element type
                    other => {
                        let iter_ty = self.infer_expr(other, context)?;
                        match &iter_ty {
                            Type::Array(elem, _) => (**elem).clone(),
                            _ => {
                                self.errors.push(TypeError {
                                    message: format!(
                                        "for-loop requires an array or range, got {:?}",
                                        iter_ty
                                    ),
                                    location: context.to_string(),
                                });
                                Type::I32 // fallback
                            }
                        }
                    }
                };

                let saved = self.variables.clone();
                let saved_moved = self.moved_vars.clone();
                self.variables.insert(var.clone(), elem_ty);
                self.loop_labels.push(label.clone());
                self.check_block(body, context)?;
                self.loop_labels.pop();
                self.variables = saved;
                self.moved_vars = saved_moved;
                Ok(None)
            }
            Stmt::While { label, condition, body } => {
                let cond_ty = self.infer_expr(condition, context)?;
                if cond_ty != Type::Bool {
                    self.errors.push(TypeError {
                        message: format!("While condition must be bool, got {:?}", cond_ty),
                        location: context.to_string(),
                    });
                }
                self.loop_labels.push(label.clone());
                self.check_block(body, context)?;
                self.loop_labels.pop();
                Ok(None)
            }
            Stmt::Loop { label, body } => {
                self.loop_labels.push(label.clone());
                self.check_block(body, context)?;
                self.loop_labels.pop();
                Ok(None)
            }
            Stmt::Break(label) | Stmt::Continue(label) => {
                if self.loop_labels.is_empty() {
                    self.errors.push(TypeError {
                        message: "break or continue outside of loop".to_string(),
                        location: context.to_string(),
                    });
                } else if let Some(target) = label {
                    if !self.loop_labels.iter().any(|l| l.as_deref() == Some(target.as_str())) {
                        self.errors.push(TypeError {
                            message: format!("Undefined loop label: '{}'", target),
                            location: context.to_string(),
                        });
                    }
                }
                Ok(None)
            }
            Stmt::Defer(body) => {
                self.check_block(body, context)?;
                Ok(None)
            }
            Stmt::Expr(expr) => {
                let ty = self.infer_expr(expr, context)?;
                Ok(Some(ty))
            }
            Stmt::Match { expr, arms } => {
                let expr_ty = self.infer_expr(expr, context)?;
                for arm in arms {
                    self.check_pattern_type(&arm.pattern, &expr_ty, context);
                    let saved = self.variables.clone();
                    let saved_moved = self.moved_vars.clone();
                    self.bind_pattern(&arm.pattern, &expr_ty);
                    if let Some(guard) = &arm.guard {
                        let guard_ty = self.infer_expr(guard, context)?;
                        if guard_ty != Type::Bool {
                            self.errors.push(TypeError {
                                message: format!("Match guard must evaluate to bool, found {:?}", guard_ty),
                                location: context.to_string(),
                            });
                        }
                    }
                    match &arm.body {
                        ast::MatchBody::Expr(body_expr) => {
                            self.infer_expr(body_expr, context)?;
                        }
                        ast::MatchBody::Block(block) => {
                            self.check_block(block, context)?;
                        }
                    }
                    self.variables = saved;
                    self.moved_vars = saved_moved;
                }
                self.check_match_semantics(arms, context);
                self.check_enum_match(&expr_ty, arms, context);
                self.check_option_match(&expr_ty, arms, context);
                self.check_result_match(&expr_ty, arms, context);
                self.check_bool_match(&expr_ty, arms, context);
                self.check_scalar_match(&expr_ty, arms, context);
                Ok(None)
            }
            _ => Ok(None),
        }
    }

    fn infer_expr(&mut self, expr: &Expr, context: &str) -> Result<Type> {
        self.infer_expr_with_hint(expr, context, None)
    }

    fn infer_expr_with_hint(
        &mut self,
        expr: &Expr,
        context: &str,
        expected: Option<&Type>,
    ) -> Result<Type> {
        match expr {
            Expr::Unit => Ok(Type::Unit),
            Expr::Tuple(elements) => {
                let mut elem_types = Vec::new();
                for (i, elem) in elements.iter().enumerate() {
                    let hint = if let Some(Type::Tuple(expected_elems)) = expected {
                        expected_elems.get(i)
                    } else {
                        None
                    };
                    elem_types.push(self.infer_expr_with_hint(elem, context, hint)?);
                }
                Ok(Type::Tuple(elem_types))
            }
            Expr::Literal(lit) => Ok(self.literal_type(lit)),
            Expr::Ident(name) => {
                // Check for use-after-move
                if self.moved_vars.contains(name) {
                    let moved_at = self
                        .moved_locations
                        .get(name)
                        .cloned()
                        .unwrap_or_else(|| "unknown".to_string());
                    self.errors.push(TypeError {
                        message: format!("Use of moved value '{}' (moved at {})", name, moved_at),
                        location: context.to_string(),
                    });
                    // Still return the type for continued analysis
                    if let Some(ty) = self.variables.get(name) {
                        return Ok(ty.clone());
                    }
                    return Ok(Type::I32); // fallback
                }

                if let Some(ty) = self.variables.get(name) {
                    Ok(ty.clone())
                } else if self.enums.contains_key(name) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Cannot use enum type '{}' as a value; construct a variant like '{}.Variant'",
                            name, name
                        ),
                        location: context.to_string(),
                    });
                    Ok(Type::Named(name.clone()))
                } else {
                    self.errors.push(TypeError {
                        message: format!("Undefined variable: {}", name),
                        location: context.to_string(),
                    });
                    Ok(Type::I32) // fallback
                }
            }
            Expr::Binary { op, left, right } => {
                let left_ty = self.infer_expr(left, context)?;
                let right_ty = self.infer_expr(right, context)?;
                self.binary_result_type(*op, &left_ty, &right_ty, context)
            }
            Expr::Unary { op, expr } => {
                let ty = self.infer_expr(expr, context)?;
                self.unary_result_type(*op, &ty, context)
            }
            Expr::Call { func, args } => {
                if let Expr::Field { expr, field } = func.as_ref() {
                    if let Expr::Ident(type_name) = expr.as_ref() {
                        if self.enums.contains_key(type_name) {
                            return self
                                .check_enum_payload_constructor(type_name, field, args, context);
                        }
                    }
                    let base_ty = self.infer_expr(expr, context)?;
                    let struct_name = match &base_ty {
                        Type::Named(name) => Some(name.clone()),
                        _ => None,
                    };
                    if let Some(sname) = struct_name {
                        let method_name = format!("{}::{}", sname, field);
                        if let Some((param_types, ret_ty)) = self.functions.get(&method_name).cloned() {
                            let mut full_args = vec![expr.as_ref().clone()];
                            full_args.extend(args.iter().cloned());
                            if full_args.len() != param_types.len() {
                                self.errors.push(TypeError {
                                    message: format!(
                                        "Method {} on struct {} expects {} arguments (including self), got {}",
                                        field,
                                        sname,
                                        param_types.len() - 1,
                                        args.len()
                                    ),
                                    location: context.to_string(),
                                });
                            }
                            for (i, (arg, expected)) in full_args.iter().zip(param_types.iter()).enumerate() {
                                let actual = self.infer_expr_with_hint(arg, context, Some(expected))?;
                                if !self.types_compatible(expected, &actual) {
                                    self.errors.push(TypeError {
                                        message: format!(
                                            "Argument {} type mismatch: expected {:?}, got {:?}",
                                            if i == 0 { "receiver self".to_string() } else { (i - 1).to_string() },
                                            expected,
                                            actual
                                        ),
                                        location: context.to_string(),
                                    });
                                }
                            }
                            return Ok(ret_ty.unwrap_or(Type::Unit));
                        } else {
                            self.errors.push(TypeError {
                                message: format!("No method '{}' found on struct '{}'", field, sname),
                                location: context.to_string(),
                            });
                            return Ok(Type::I32);
                        }
                    } else {
                        self.errors.push(TypeError {
                            message: format!("Cannot call method '{}' on non-struct type {:?}", field, base_ty),
                            location: context.to_string(),
                        });
                        return Ok(Type::I32);
                    }
                }
                if let Expr::Ident(name) = func.as_ref() {
                    if let Some(ty) = self.check_builtin_call(name, args, context, expected)? {
                        return Ok(ty);
                    }

                    if let Some(struct_fields) = self.structs.get(name).cloned() {
                        if args.len() != struct_fields.len() {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Struct constructor {} expects {} arguments, got {}",
                                    name,
                                    struct_fields.len(),
                                    args.len()
                                ),
                                location: context.to_string(),
                            });
                        }
                        for (i, (arg, (_fname, expected_ty))) in args.iter().zip(struct_fields.iter()).enumerate() {
                            let actual = self.infer_expr_with_hint(arg, context, Some(expected_ty))?;
                            if !self.types_compatible(expected_ty, &actual) {
                                self.errors.push(TypeError {
                                    message: format!(
                                        "Argument {} type mismatch: expected {:?}, got {:?}",
                                        i, expected_ty, actual
                                    ),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Named(name.clone()));
                    }

                    if let Some((param_types, ret_ty)) = self.functions.get(name).cloned() {
                        // Check argument count
                        if args.len() != param_types.len() {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Function {} expects {} arguments, got {}",
                                    name,
                                    param_types.len(),
                                    args.len()
                                ),
                                location: context.to_string(),
                            });
                        }
                        // Check argument types
                        for (i, (arg, expected)) in args.iter().zip(param_types.iter()).enumerate()
                        {
                            let actual = self.infer_expr_with_hint(arg, context, Some(expected))?;
                            if !self.types_compatible(expected, &actual) {
                                self.errors.push(TypeError {
                                    message: format!(
                                        "Argument {} type mismatch: expected {:?}, got {:?}",
                                        i, expected, actual
                                    ),
                                    location: context.to_string(),
                                });
                            }
                        }
                        Ok(ret_ty.unwrap_or(Type::I32))
                    } else {
                        self.errors.push(TypeError {
                            message: format!("Undefined function: {}", name),
                            location: context.to_string(),
                        });
                        Ok(Type::I32)
                    }
                } else {
                    self.errors.push(TypeError {
                        message: "Invalid function call target".to_string(),
                        location: context.to_string(),
                    });
                    Ok(Type::I32)
                }
            }
            Expr::Index { expr, index } => {
                let expr_ty = self.infer_expr(expr, context)?;
                let index_ty = self.infer_expr(index, context)?;

                if !matches!(index_ty, Type::I32 | Type::I64) {
                    self.errors.push(TypeError {
                        message: format!("Index must be integer, got {:?}", index_ty),
                        location: context.to_string(),
                    });
                }

                match expr_ty {
                    Type::Array(elem, _) => Ok(*elem),
                    _ => {
                        self.errors.push(TypeError {
                            message: format!("Cannot index {:?}", expr_ty),
                            location: context.to_string(),
                        });
                        Ok(Type::I32)
                    }
                }
            }
            Expr::Field { expr, field } => {
                if let Expr::Ident(type_name) = expr.as_ref() {
                    if let Some(variants) = self.enums.get(type_name) {
                        if variants.iter().any(|variant| variant == field) {
                            if self.enum_variant_has_payload(type_name, field) {
                                self.errors.push(TypeError {
                                    message: format!(
                                        "Variant {}.{} expects a payload",
                                        type_name, field
                                    ),
                                    location: context.to_string(),
                                });
                            }
                            return Ok(Type::Named(type_name.clone()));
                        }
                        self.errors.push(TypeError {
                            message: format!("Unknown variant '{}' on enum {}", field, type_name),
                            location: context.to_string(),
                        });
                        return Ok(Type::Named(type_name.clone()));
                    }
                }

                let expr_ty = self.infer_expr(expr, context)?;
                // Auto-dereference references
                let base_ty = match &expr_ty {
                    Type::Ref { ty, .. } => ty.as_ref().clone(),
                    other => other.clone(),
                };
                match &base_ty {
                    Type::Tuple(elem_types) => {
                        if let Ok(idx) = field.parse::<usize>() {
                            if idx < elem_types.len() {
                                Ok(elem_types[idx].clone())
                            } else {
                                self.errors.push(TypeError {
                                    message: format!(
                                        "Tuple index out of bounds: {} for tuple of length {}",
                                        idx, elem_types.len()
                                    ),
                                    location: context.to_string(),
                                });
                                Ok(Type::I32)
                            }
                        } else {
                            self.errors.push(TypeError {
                                message: format!("Cannot access named field '{}' on tuple", field),
                                location: context.to_string(),
                            });
                            Ok(Type::I32)
                        }
                    }
                    Type::Named(struct_name) if self.enums.contains_key(struct_name) => {
                        self.errors.push(TypeError {
                            message: format!(
                                "Cannot access field '{}' on enum value {}",
                                field, struct_name
                            ),
                            location: context.to_string(),
                        });
                        Ok(Type::I32)
                    }
                    Type::Named(struct_name) => {
                        if let Some(fields) = self.structs.get(struct_name) {
                            if let Some((_, field_ty)) = fields.iter().find(|(n, _)| n == field) {
                                Ok(field_ty.clone())
                            } else {
                                self.errors.push(TypeError {
                                    message: format!(
                                        "No field '{}' on struct {}",
                                        field, struct_name
                                    ),
                                    location: context.to_string(),
                                });
                                Ok(Type::I32)
                            }
                        } else {
                            self.errors.push(TypeError {
                                message: format!("Unknown struct: {}", struct_name),
                                location: context.to_string(),
                            });
                            Ok(Type::I32)
                        }
                    }
                    _ => {
                        self.errors.push(TypeError {
                            message: format!("Cannot access field on {:?}", base_ty),
                            location: context.to_string(),
                        });
                        Ok(Type::I32)
                    }
                }
            }
            Expr::If {
                condition,
                then_expr,
                else_expr,
            } => {
                let cond_ty = self.infer_expr(condition, context)?;
                if cond_ty != Type::Bool {
                    self.errors.push(TypeError {
                        message: format!("Condition must be bool, got {:?}", cond_ty),
                        location: context.to_string(),
                    });
                }
                let then_ty = self.infer_expr_with_hint(then_expr, context, expected)?;
                let else_hint = expected.or(Some(&then_ty));
                let else_ty = self.infer_expr_with_hint(else_expr, context, else_hint)?;
                let (then_ty, else_ty) = if matches!(then_expr.as_ref(), Expr::None) && matches!(else_ty, Type::Option(_)) {
                    let re_then = self.infer_expr_with_hint(then_expr, context, Some(&else_ty))?;
                    (re_then, else_ty)
                } else if matches!(else_expr.as_ref(), Expr::None) && matches!(then_ty, Type::Option(_)) {
                    let re_else = self.infer_expr_with_hint(else_expr, context, Some(&then_ty))?;
                    (then_ty, re_else)
                } else if matches!(then_expr.as_ref(), Expr::Array(elements) if elements.is_empty()) && matches!(else_ty, Type::Array(_, _)) {
                    let re_then = self.infer_expr_with_hint(then_expr, context, Some(&else_ty))?;
                    (re_then, else_ty)
                } else if matches!(else_expr.as_ref(), Expr::Array(elements) if elements.is_empty()) && matches!(then_ty, Type::Array(_, _)) {
                    let re_else = self.infer_expr_with_hint(else_expr, context, Some(&then_ty))?;
                    (then_ty, re_else)
                } else if !self.types_compatible(&then_ty, &else_ty) {
                    if self.types_compatible(&else_ty, &then_ty) {
                        let re_then = self.infer_expr_with_hint(then_expr, context, Some(&else_ty))?;
                        (re_then, else_ty)
                    } else if let (Type::Result(ok_t, err_t), Type::Result(ok_e, err_e)) = (&then_ty, &else_ty) {
                        let unified_ok = if ok_t.as_ref() != &Type::I32 || ok_e.as_ref() == &Type::I32 { ok_t.clone() } else { ok_e.clone() };
                        let unified_err = if err_t.as_ref() != &Type::I32 || err_e.as_ref() == &Type::I32 { err_t.clone() } else { err_e.clone() };
                        let unified = Type::Result(unified_ok, unified_err);
                        let re_then = self.infer_expr_with_hint(then_expr, context, Some(&unified))?;
                        let re_else = self.infer_expr_with_hint(else_expr, context, Some(&unified))?;
                        (re_then, re_else)
                    } else {
                        (then_ty, else_ty)
                    }
                } else if let (Type::Result(ok_t, err_t), Type::Result(ok_e, err_e)) = (&then_ty, &else_ty) {
                    if err_t != err_e || ok_t != ok_e {
                        let unified_ok = if ok_t.as_ref() != &Type::I32 || ok_e.as_ref() == &Type::I32 { ok_t.clone() } else { ok_e.clone() };
                        let unified_err = if err_t.as_ref() != &Type::I32 || err_e.as_ref() == &Type::I32 { err_t.clone() } else { err_e.clone() };
                        let unified = Type::Result(unified_ok, unified_err);
                        let re_then = self.infer_expr_with_hint(then_expr, context, Some(&unified))?;
                        let re_else = self.infer_expr_with_hint(else_expr, context, Some(&unified))?;
                        (re_then, re_else)
                    } else {
                        (then_ty, else_ty)
                    }
                } else {
                    (then_ty, else_ty)
                };
                if !self.types_compatible(&then_ty, &else_ty) && !self.types_compatible(&else_ty, &then_ty) {
                    self.errors.push(TypeError {
                        message: format!(
                            "If branches have different types: {:?} vs {:?}",
                            then_ty, else_ty
                        ),
                        location: context.to_string(),
                    });
                }
                if then_ty == Type::Never {
                    Ok(else_ty)
                } else {
                    Ok(then_ty)
                }
            }
        Expr::Array(elements) => {
                if elements.is_empty() {
                    if let Some(Type::Array(elem_ty, _)) = expected {
                        Ok(Type::Array(elem_ty.clone(), 0))
                    } else {
                        self.errors.push(TypeError {
                            message: "Empty array requires explicit type annotation".to_string(),
                            location: context.to_string(),
                        });
                        Ok(Type::Array(Box::new(Type::I32), 0))
                    }
                } else {
                    let elem_ty = self.infer_expr(&elements[0], context)?;
                    for (i, elem) in elements.iter().skip(1).enumerate() {
                        let ty = self.infer_expr(elem, context)?;
                        if !self.types_compatible(&elem_ty, &ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Array element {} has type {:?}, expected {:?}",
                                    i + 1,
                                    ty,
                                    elem_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                    Ok(Type::Array(Box::new(elem_ty), elements.len()))
                }
            }
            Expr::Struct { name, fields, base } => {
                if let Some(struct_fields) = self.structs.get(name).cloned() {
                    for (field_name, field_expr) in fields {
                        let actual_ty = self.infer_expr(field_expr, context)?;
                        if let Some((_, expected_ty)) =
                            struct_fields.iter().find(|(n, _)| n == field_name)
                        {
                            if !self.types_compatible(expected_ty, &actual_ty) {
                                self.errors.push(TypeError {
                                    message: format!(
                                        "Field '{}' type mismatch: expected {:?}, got {:?}",
                                        field_name, expected_ty, actual_ty
                                    ),
                                    location: context.to_string(),
                                });
                            }
                        } else {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Unknown field '{}' in struct {}",
                                    field_name, name
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                    if let Some(base_expr) = base {
                        let base_ty = self.infer_expr(base_expr, context)?;
                        if base_ty != Type::Named(name.clone()) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Base expression in struct update must have type '{}', found {:?}",
                                    name, base_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                    Ok(Type::Named(name.clone()))
                } else {
                    self.errors.push(TypeError {
                        message: format!("Unknown struct: {}", name),
                        location: context.to_string(),
                    });
                    Ok(Type::Named(name.clone()))
                }
            }
            Expr::Try(inner) => {
                let inner_ty = self.infer_expr(inner, context)?;
                match inner_ty {
                    Type::Result(ok_ty, _err_ty) => Ok(*ok_ty),
                    Type::Option(val_ty) => Ok(*val_ty),
                    other => Err(anyhow::anyhow!("? operator can only be applied to Result or Option, found {:?}", other)),
                }
            }
            Expr::Copy(inner) => self.infer_expr(inner, context),
            Expr::Some(inner) => {
                let inner_hint = match expected {
                    Some(Type::Option(inner_ty)) => Some(inner_ty.as_ref()),
                    _ => None,
                };
                let inner_ty = self.infer_expr_with_hint(inner, context, inner_hint)?;
                Ok(Type::Option(Box::new(inner_ty)))
            }
            Expr::None => {
                // None with expected context
                if let Some(Type::Option(inner)) = expected {
                    Ok(Type::Option(inner.clone()))
                } else {
                    Ok(Type::Option(Box::new(Type::I32)))
                }
            }
            Expr::Match { expr, arms } => {
                let expr_ty = self.infer_expr(expr, context)?;

                // Check pattern types against expression type
                for arm in arms {
                    self.check_pattern_type(&arm.pattern, &expr_ty, context);
                    if let Some(guard) = &arm.guard {
                        let saved = self.variables.clone();
                        let saved_moved = self.moved_vars.clone();
                        self.bind_pattern(&arm.pattern, &expr_ty);
                        let guard_ty = self.infer_expr(guard, context)?;
                        if guard_ty != Type::Bool {
                            self.errors.push(TypeError {
                                message: format!("Match guard must evaluate to bool, found {:?}", guard_ty),
                                location: context.to_string(),
                            });
                        }
                        self.variables = saved;
                        self.moved_vars = saved_moved;
                    }
                }
                self.check_match_semantics(arms, context);
                self.check_enum_match(&expr_ty, arms, context);
                self.check_option_match(&expr_ty, arms, context);
                self.check_result_match(&expr_ty, arms, context);
                self.check_bool_match(&expr_ty, arms, context);
                self.check_scalar_match(&expr_ty, arms, context);

                // Infer result type across arms (propagating non-Never types)
                let mut match_result: Option<Type> = None;
                for arm in arms {
                    match &arm.body {
                        ast::MatchBody::Expr(e) => {
                            let saved = self.variables.clone();
                            let saved_moved = self.moved_vars.clone();
                            self.bind_pattern(&arm.pattern, &expr_ty);
                            let arm_hint = expected.or(match_result.as_ref());
                            let arm_ty = self.infer_expr_with_hint(e, context, arm_hint)?;
                            self.variables = saved;
                            self.moved_vars = saved_moved;
                            if arm_ty != Type::Never {
                                if let Some(existing) = &match_result {
                                    if !self.types_compatible(existing, &arm_ty) && !self.types_compatible(&arm_ty, existing) {
                                        if let (Type::Result(ok_t, err_t), Type::Result(ok_e, err_e)) = (existing, &arm_ty) {
                                            let unified_ok = if ok_t.as_ref() != &Type::I32 || ok_e.as_ref() == &Type::I32 { ok_t.clone() } else { ok_e.clone() };
                                            let unified_err = if err_t.as_ref() != &Type::I32 || err_e.as_ref() == &Type::I32 { err_t.clone() } else { err_e.clone() };
                                            match_result = Some(Type::Result(unified_ok, unified_err));
                                        } else {
                                            self.errors.push(TypeError {
                                                message: format!("Match arms have incompatible types: {:?} vs {:?}", existing, arm_ty),
                                                location: context.to_string(),
                                            });
                                        }
                                    }
                                } else {
                                    match_result = Some(arm_ty);
                                }
                            }
                        }
                        ast::MatchBody::Block(block) => {
                            let has_value = block
                                .statements
                                .last()
                                .is_some_and(|s| matches!(s, Stmt::Expr(_)));
                            if !has_value {
                                self.errors.push(TypeError {
                                    message: "Match arm block must end with an expression to produce a value".to_string(),
                                    location: context.to_string(),
                                });
                            }
                            self.check_block(block, context)?;
                            if match_result.is_none() {
                                match_result = Some(Type::I32);
                            }
                        }
                    }
                }
                Ok(match_result.unwrap_or(Type::Never))
            }
            Expr::Block(block) => {
                // Block expression - check all statements and return type of last expression
                let saved = self.variables.clone();
                let saved_moved = self.moved_vars.clone();
                let mut result_ty = Type::Unit;
                for (i, stmt) in block.statements.iter().enumerate() {
                    let is_last = i == block.statements.len() - 1;
                    if is_last {
                        if let Stmt::Expr(e) = stmt {
                            result_ty = self.infer_expr_with_hint(e, context, expected)?;
                            continue;
                        }
                    }
                    self.check_stmt(stmt, context)?;
                }
                self.variables = saved;
                self.moved_vars = saved_moved;
                Ok(result_ty)
            }
            Expr::Range { start, .. } => {
                // Range type is based on start type
                self.infer_expr(start, context)
            }
            Expr::Cast { expr, target_type } => {
                let source_ty = self.infer_expr(expr, context)?;
                if !self.can_cast(&source_ty, target_type) {
                    self.errors.push(TypeError {
                        message: format!("Cannot cast {:?} to {:?}", source_ty, target_type),
                        location: context.to_string(),
                    });
                }
                Ok(target_type.clone())
            }
            _ => Ok(Type::I32), // fallback for unhandled expressions
        }
    }

    fn literal_type(&self, lit: &Literal) -> Type {
        match lit {
            Literal::Int(_) => Type::I32,
            Literal::Float(_) => Type::F64,
            Literal::String(_) => Type::Str,
            Literal::Char(_) => Type::I32, // chars as i32 for now
            Literal::Bool(_) => Type::Bool,
            Literal::HexColor(_) => Type::I32, // colors as i32 for now
        }
    }

    fn binary_result_type(
        &mut self,
        op: BinaryOp,
        left: &Type,
        right: &Type,
        context: &str,
    ) -> Result<Type> {
        match op {
            BinaryOp::Add => {
                // String concatenation
                if *left == Type::Str && *right == Type::Str {
                    return Ok(Type::Str);
                }
                if !self.is_numeric(left) || !self.is_numeric(right) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Arithmetic on non-numeric types: {:?} and {:?}",
                            left, right
                        ),
                        location: context.to_string(),
                    });
                }
                // Return the wider type
                if *left == Type::F64 || *right == Type::F64 {
                    Ok(Type::F64)
                } else if *left == Type::I64 || *right == Type::I64 {
                    Ok(Type::I64)
                } else if *left == Type::F32 || *right == Type::F32 {
                    Ok(Type::F32)
                } else {
                    Ok(Type::I32)
                }
            }
            BinaryOp::Sub | BinaryOp::Mul | BinaryOp::Div | BinaryOp::Mod => {
                if !self.is_numeric(left) || !self.is_numeric(right) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Arithmetic on non-numeric types: {:?} and {:?}",
                            left, right
                        ),
                        location: context.to_string(),
                    });
                }
                // Return the wider type
                if *left == Type::F64 || *right == Type::F64 {
                    Ok(Type::F64)
                } else if *left == Type::I64 || *right == Type::I64 {
                    Ok(Type::I64)
                } else if *left == Type::F32 || *right == Type::F32 {
                    Ok(Type::F32)
                } else {
                    Ok(Type::I32)
                }
            }
            BinaryOp::Eq
            | BinaryOp::Ne
            | BinaryOp::Lt
            | BinaryOp::Le
            | BinaryOp::Gt
            | BinaryOp::Ge => {
                if !self.types_compatible(left, right) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Comparison of incompatible types: {:?} and {:?}",
                            left, right
                        ),
                        location: context.to_string(),
                    });
                }
                Ok(Type::Bool)
            }
            BinaryOp::And | BinaryOp::Or => {
                if *left != Type::Bool || *right != Type::Bool {
                    self.errors.push(TypeError {
                        message: format!(
                            "Logical operators require bool: {:?} and {:?}",
                            left, right
                        ),
                        location: context.to_string(),
                    });
                }
                Ok(Type::Bool)
            }
            BinaryOp::As => {
                // Type cast - right should be a type, but in our AST it's an expr
                // For now, just return the left type
                Ok(left.clone())
            }
            BinaryOp::BitAnd
            | BinaryOp::BitOr
            | BinaryOp::BitXor
            | BinaryOp::Shl
            | BinaryOp::Shr => {
                // Bitwise operators require integers
                if !self.is_integer(left) || !self.is_integer(right) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Bitwise operators require integers: {:?} and {:?}",
                            left, right
                        ),
                        location: context.to_string(),
                    });
                }
                // Return the wider integer type
                if *left == Type::I64 || *right == Type::I64 {
                    Ok(Type::I64)
                } else {
                    Ok(Type::I32)
                }
            }
        }
    }

    fn unary_result_type(&mut self, op: UnaryOp, ty: &Type, context: &str) -> Result<Type> {
        match op {
            UnaryOp::Neg => {
                if !self.is_numeric(ty) {
                    self.errors.push(TypeError {
                        message: format!("Negation of non-numeric type: {:?}", ty),
                        location: context.to_string(),
                    });
                }
                Ok(ty.clone())
            }
            UnaryOp::Not => {
                if *ty != Type::Bool {
                    self.errors.push(TypeError {
                        message: format!("Logical not requires bool: {:?}", ty),
                        location: context.to_string(),
                    });
                }
                Ok(Type::Bool)
            }
        }
    }

    fn check_builtin_call(
        &mut self,
        name: &str,
        args: &[Expr],
        context: &str,
        expected: Option<&Type>,
    ) -> Result<Option<Type>> {
        if let Some(ty) = self.check_special_builtin_call(name, args, context, expected)? {
            return Ok(Some(ty));
        }

        let Some(spec) = builtins::lookup_typecheck_builtin(name) else {
            return Ok(None);
        };

        if args.len() != spec.params.len() {
            self.errors.push(TypeError {
                message: format!("{}, got {}", spec.arity_error, args.len()),
                location: context.to_string(),
            });
        }

        for (arg, param) in args.iter().zip(spec.params.iter()) {
            if matches!(param.rule, BuiltinArgRule::Any) {
                continue;
            }

            let arg_ty = self.infer_expr(arg, context)?;
            if !self.matches_builtin_arg_rule(param.rule, &arg_ty) {
                self.errors.push(TypeError {
                    message: format!("{}, got {:?}", param.type_error, arg_ty),
                    location: context.to_string(),
                });
            }
        }

        Ok(Some(spec.return_type.to_ast_type()))
    }

    fn check_special_builtin_call(
        &mut self,
        name: &str,
        args: &[Expr],
        context: &str,
        expected: Option<&Type>,
    ) -> Result<Option<Type>> {
        match name {
            "panic" => {
                self.check_builtin_arity("panic expects 1 argument (message)", args, 1, context);
                if let Some(arg) = args.first() {
                    let ty = self.infer_expr(arg, context)?;
                    if ty != Type::Str {
                        self.errors.push(TypeError {
                            message: format!("panic expects a string message, got {:?}", ty),
                            location: context.to_string(),
                        });
                    }
                }
                return Ok(Some(Type::Never));
            }
            "assert" => {
                if args.is_empty() || args.len() > 2 {
                    self.errors.push(TypeError {
                        message: format!(
                            "assert expects 1 or 2 arguments (condition, optional message), got {}",
                            args.len()
                        ),
                        location: context.to_string(),
                    });
                } else {
                    let cond_ty = self.infer_expr(&args[0], context)?;
                    if cond_ty != Type::Bool {
                        self.errors.push(TypeError {
                            message: format!("assert condition must be bool, got {:?}", cond_ty),
                            location: context.to_string(),
                        });
                    }
                    if args.len() == 2 {
                        let msg_ty = self.infer_expr(&args[1], context)?;
                        if msg_ty != Type::Str {
                            self.errors.push(TypeError {
                                message: format!("assert message must be str, got {:?}", msg_ty),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                return Ok(Some(Type::Unit));
            }
            "vec_new" => {
                self.check_builtin_arity("vec_new expects 0 arguments", args, 0, context);
                match expected {
                    Some(Type::Vec(_)) => Ok(expected.cloned()),
                    _ => {
                        self.errors.push(TypeError {
                            message: "vec_new requires explicit Vec<T> type context".to_string(),
                            location: context.to_string(),
                        });
                        Ok(Some(Type::Vec(Box::new(Type::I32))))
                    }
                }
            }
            "vec_push" => {
                self.check_builtin_arity(
                    "vec_push expects 2 arguments (vec, value)",
                    args,
                    2,
                    context,
                );
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_push", vec_ty, context);
                    if let (Type::Vec(elem), Some(value_ty)) = (vec_ty, arg_types.get(1)) {
                        if !self.types_compatible(elem, value_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "vec_push value type mismatch: expected {:?}, got {:?}",
                                    elem, value_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                Ok(Some(Type::I64))
            }
            "vec_pop" => {
                self.check_builtin_arity("vec_pop expects 1 argument (vec)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_pop", vec_ty, context);
                }
                Ok(builtins::infer_special_builtin_call_type(
                    name, &arg_types, expected,
                ))
            }
            "vec_len" => {
                self.check_builtin_arity("vec_len expects 1 argument (vec)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_len", vec_ty, context);
                }
                Ok(Some(Type::I64))
            }
            "vec_capacity" => {
                self.check_builtin_arity("vec_capacity expects 1 argument (vec)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_capacity", vec_ty, context);
                }
                Ok(Some(Type::I64))
            }
            "vec_get" => {
                self.check_builtin_arity(
                    "vec_get expects 2 arguments (vec, index)",
                    args,
                    2,
                    context,
                );
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_get", vec_ty, context);
                }
                if let Some(index_ty) = arg_types.get(1) {
                    self.check_vec_index_type("vec_get", index_ty, context);
                }
                Ok(builtins::infer_special_builtin_call_type(
                    name, &arg_types, expected,
                ))
            }
            "vec_set" => {
                self.check_builtin_arity(
                    "vec_set expects 3 arguments (vec, index, value)",
                    args,
                    3,
                    context,
                );
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_set", vec_ty, context);
                    if let Some(index_ty) = arg_types.get(1) {
                        self.check_vec_index_type("vec_set", index_ty, context);
                    }
                    if let (Type::Vec(elem), Some(value_ty)) = (vec_ty, arg_types.get(2)) {
                        if !self.types_compatible(elem, value_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "vec_set value type mismatch: expected {:?}, got {:?}",
                                    elem, value_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                Ok(Some(Type::Bool))
            }
            "vec_clear" => {
                self.check_builtin_arity("vec_clear expects 1 argument (vec)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_clear", vec_ty, context);
                }
                Ok(Some(Type::I32))
            }
            "hashmap_new" => {
                self.check_builtin_arity("hashmap_new expects 0 arguments", args, 0, context);
                match expected {
                    Some(Type::HashMap(_, _)) => Ok(expected.cloned()),
                    _ => {
                        self.errors.push(TypeError {
                            message: "hashmap_new requires explicit HashMap<K, V> type context"
                                .to_string(),
                            location: context.to_string(),
                        });
                        Ok(Some(Type::HashMap(
                            Box::new(Type::I32),
                            Box::new(Type::I32),
                        )))
                    }
                }
            }
            "hashmap_insert" => {
                self.check_builtin_arity(
                    "hashmap_insert expects 3 arguments (map, key, value)",
                    args,
                    3,
                    context,
                );
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(map_ty) = arg_types.first() {
                    self.check_hashmap_handle_type("hashmap_insert", map_ty, context);
                    if let (Type::HashMap(key, value), Some(key_ty), Some(value_ty)) =
                        (map_ty, arg_types.get(1), arg_types.get(2))
                    {
                        if !self.types_compatible(key, key_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "hashmap_insert key type mismatch: expected {:?}, got {:?}",
                                    key, key_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                        if !self.types_compatible(value, value_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "hashmap_insert value type mismatch: expected {:?}, got {:?}",
                                    value, value_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                Ok(Some(Type::Bool))
            }
            "hashmap_get" => {
                self.check_builtin_arity(
                    "hashmap_get expects 2 arguments (map, key)",
                    args,
                    2,
                    context,
                );
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(map_ty) = arg_types.first() {
                    self.check_hashmap_handle_type("hashmap_get", map_ty, context);
                    if let (Type::HashMap(key, _), Some(key_ty)) = (map_ty, arg_types.get(1)) {
                        if !self.types_compatible(key, key_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "hashmap_get key type mismatch: expected {:?}, got {:?}",
                                    key, key_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                Ok(builtins::infer_special_builtin_call_type(
                    name, &arg_types, expected,
                ))
            }
            "hashmap_contains" | "hashmap_remove" => {
                let arity_error = if name == "hashmap_contains" {
                    "hashmap_contains expects 2 arguments (map, key)"
                } else {
                    "hashmap_remove expects 2 arguments (map, key)"
                };
                self.check_builtin_arity(arity_error, args, 2, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(map_ty) = arg_types.first() {
                    self.check_hashmap_handle_type(name, map_ty, context);
                    if let (Type::HashMap(key, _), Some(key_ty)) = (map_ty, arg_types.get(1)) {
                        if !self.types_compatible(key, key_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "{} key type mismatch: expected {:?}, got {:?}",
                                    name, key, key_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                Ok(Some(Type::Bool))
            }
            "hashmap_len" => {
                self.check_builtin_arity("hashmap_len expects 1 argument (map)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(map_ty) = arg_types.first() {
                    self.check_hashmap_handle_type("hashmap_len", map_ty, context);
                }
                Ok(Some(Type::I64))
            }
            "hashmap_clear" => {
                self.check_builtin_arity(
                    "hashmap_clear expects 1 argument (map)",
                    args,
                    1,
                    context,
                );
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(map_ty) = arg_types.first() {
                    self.check_hashmap_handle_type("hashmap_clear", map_ty, context);
                }
                Ok(Some(Type::I32))
            }
            "hashmap_keys" => {
                self.check_builtin_arity("hashmap_keys expects 1 argument (map)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(map_ty) = arg_types.first() {
                    self.check_hashmap_handle_type("hashmap_keys", map_ty, context);
                }
                Ok(builtins::infer_special_builtin_call_type(
                    name, &arg_types, expected,
                ))
            }
            "result_ok" | "Ok" => {
                self.check_builtin_arity("result_ok expects 1 argument (value)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let (Some(Type::Result(ok_ty, _)), Some(value_ty)) =
                    (expected, arg_types.first())
                {
                    if !self.types_compatible(ok_ty, value_ty) {
                        self.errors.push(TypeError {
                            message: format!(
                                "result_ok value type mismatch: expected {:?}, got {:?}",
                                ok_ty, value_ty
                            ),
                            location: context.to_string(),
                        });
                    }
                }
                Ok(builtins::infer_special_builtin_call_type(
                    name, &arg_types, expected,
                ))
            }
            "result_err" | "Err" => {
                self.check_builtin_arity("result_err expects 1 argument (error)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let (Some(Type::Result(_, err_ty)), Some(value_ty)) =
                    (expected, arg_types.first())
                {
                    if !self.types_compatible(err_ty, value_ty) {
                        self.errors.push(TypeError {
                            message: format!(
                                "result_err value type mismatch: expected {:?}, got {:?}",
                                err_ty, value_ty
                            ),
                            location: context.to_string(),
                        });
                    }
                }
                Ok(builtins::infer_special_builtin_call_type(
                    name, &arg_types, expected,
                ))
            }
            "hashmap_get_opt" => {
                self.check_builtin_arity("hashmap_get_opt expects 2 arguments (map, key)", args, 2, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(map_ty) = arg_types.first() {
                    self.check_hashmap_handle_type("hashmap_get_opt", map_ty, context);
                    if let (Type::HashMap(key, _), Some(key_ty)) = (map_ty, arg_types.get(1)) {
                        if !self.types_compatible(key, key_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "hashmap_get_opt key type mismatch: expected {:?}, got {:?}",
                                    key, key_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                Ok(builtins::infer_special_builtin_call_type(name, &arg_types, expected))
            }
            "vec_get_opt" => {
                self.check_builtin_arity("vec_get_opt expects 2 arguments (vec, index)", args, 2, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_get_opt", vec_ty, context);
                }
                if let Some(index_ty) = arg_types.get(1) {
                    self.check_vec_index_type("vec_get_opt", index_ty, context);
                }
                Ok(builtins::infer_special_builtin_call_type(name, &arg_types, expected))
            }
            "vec_pop_opt" => {
                self.check_builtin_arity("vec_pop_opt expects 1 argument (vec)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(vec_ty) = arg_types.first() {
                    self.check_vec_handle_type("vec_pop_opt", vec_ty, context);
                }
                Ok(builtins::infer_special_builtin_call_type(name, &arg_types, expected))
            }
            "read_file_result" => {
                self.check_builtin_arity("read_file_result expects 1 argument (path)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                Ok(builtins::infer_special_builtin_call_type(name, &arg_types, expected))
            }
            "write_file_result" => {
                self.check_builtin_arity("write_file_result expects 2 arguments (path, content)", args, 2, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                Ok(builtins::infer_special_builtin_call_type(name, &arg_types, expected))
            }
            "parse_int_result" => {
                self.check_builtin_arity("parse_int_result expects 1 argument (string)", args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                Ok(builtins::infer_special_builtin_call_type(name, &arg_types, expected))
            }
            "result_is_ok" | "result_is_err" | "result_unwrap" | "result_unwrap_err"
            | "result_tag" | "result_value" => {
                let arity_error = match name {
                    "result_is_ok" => "result_is_ok expects 1 argument (result)",
                    "result_is_err" => "result_is_err expects 1 argument (result)",
                    "result_unwrap" => "result_unwrap expects 1 argument (result)",
                    "result_unwrap_err" => "result_unwrap_err expects 1 argument (result)",
                    "result_tag" => "result_tag expects 1 argument (result)",
                    _ => "result_value expects 1 argument (result)",
                };
                self.check_builtin_arity(arity_error, args, 1, context);
                let arg_types = self.infer_builtin_arg_types(args, context)?;
                if let Some(result_ty) = arg_types.first() {
                    self.check_result_handle_type(name, result_ty, context);
                    if let ("result_value", Type::Result(ok_ty, err_ty)) = (name, result_ty) {
                        if ok_ty != err_ty {
                            self.errors.push(TypeError {
                                message: format!(
                                    "result_value requires Result<T, T>, got Result<{:?}, {:?}>",
                                    ok_ty, err_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                Ok(
                    builtins::infer_special_builtin_call_type(name, &arg_types, expected).or_else(
                        || {
                            builtins::lookup_typecheck_builtin(name)
                                .map(|spec| spec.return_type.to_ast_type())
                        },
                    ),
                )
            }
            _ => Ok(None),
        }
    }

    fn infer_builtin_arg_types(&mut self, args: &[Expr], context: &str) -> Result<Vec<Type>> {
        args.iter()
            .map(|arg| self.infer_expr(arg, context))
            .collect::<Result<Vec<_>>>()
    }

    fn check_builtin_arity(
        &mut self,
        message: &str,
        args: &[Expr],
        expected_len: usize,
        context: &str,
    ) {
        if args.len() != expected_len {
            self.errors.push(TypeError {
                message: format!("{}, got {}", message, args.len()),
                location: context.to_string(),
            });
        }
    }

    fn check_vec_handle_type(&mut self, builtin: &str, ty: &Type, context: &str) {
        if !matches!(ty, Type::Vec(_)) {
            self.errors.push(TypeError {
                message: format!("{} expects Vec<T>, got {:?}", builtin, ty),
                location: context.to_string(),
            });
        }
    }

    fn check_vec_index_type(&mut self, builtin: &str, ty: &Type, context: &str) {
        if !self.is_integer(ty) {
            self.errors.push(TypeError {
                message: format!("{} expects integer index, got {:?}", builtin, ty),
                location: context.to_string(),
            });
        }
    }

    fn check_result_handle_type(&mut self, builtin: &str, ty: &Type, context: &str) {
        if !matches!(ty, Type::Result(_, _)) {
            self.errors.push(TypeError {
                message: format!("{} expects Result<T, E>, got {:?}", builtin, ty),
                location: context.to_string(),
            });
        }
    }

    fn check_hashmap_handle_type(&mut self, builtin: &str, ty: &Type, context: &str) {
        if !matches!(ty, Type::HashMap(_, _)) {
            self.errors.push(TypeError {
                message: format!("{} expects HashMap<K, V>, got {:?}", builtin, ty),
                location: context.to_string(),
            });
        }
    }

    fn can_cast(&self, source: &Type, target: &Type) -> bool {
        if source == target {
            return true;
        }
        if (self.is_numeric(source) || *source == Type::Bool)
            && (self.is_numeric(target) || *target == Type::Bool)
        {
            return true;
        }
        if (*source == Type::I64 && self.is_handle_type(target))
            || (self.is_handle_type(source) && *target == Type::I64)
        {
            return true;
        }
        self.is_handle_type(source) && self.is_handle_type(target)
    }

    fn is_handle_type(&self, ty: &Type) -> bool {
        matches!(
            ty,
            Type::Str
                | Type::Option(_)
                | Type::Result(_, _)
                | Type::Vec(_)
                | Type::HashMap(_, _)
                | Type::Array(_, _)
                | Type::Ref { .. }
                | Type::Named(_)
        )
    }

    fn is_numeric(&self, ty: &Type) -> bool {
        matches!(ty, Type::I32 | Type::I64 | Type::F32 | Type::F64)
    }

    /// Check if a type is implicitly copyable (primitives).
    /// Non-copy types (structs, arrays, strings) require explicit `copy` to avoid moving.
    fn is_copy_type(&self, ty: &Type) -> bool {
        match ty {
            Type::Tuple(elem_types) => elem_types.iter().all(|t| self.is_copy_type(t)),
            Type::Never | Type::Unit | Type::I32 | Type::I64 | Type::F32 | Type::F64 | Type::Bool => true,
            Type::Named(name) => self.enums.contains_key(name),
            _ => false,
        }
    }

    fn check_enum_match(&mut self, expr_ty: &Type, arms: &[ast::MatchArm], context: &str) {
        let Type::Named(enum_name) = expr_ty else {
            return;
        };
        let Some(variants) = self.enums.get(enum_name).cloned() else {
            return;
        };

        let mut seen = HashSet::new();
        let mut has_wildcard = false;
        let mut exhausted = false;
        for arm in arms {
            if exhausted {
                self.errors.push(TypeError {
                    message: format!(
                        "Unreachable match arm: previous enum patterns already cover every declared variant of '{}'",
                        enum_name
                    ),
                    location: context.to_string(),
                });
            }
            if arm.guard.is_some() {
                continue;
            }
            match &arm.pattern {
                ast::Pattern::EnumVariant {
                    enum_name: pat_enum,
                    variant,
                    bindings: _,
                } => {
                    if pat_enum != enum_name {
                        continue;
                    }
                    if !seen.insert(variant.clone()) {
                        self.errors.push(TypeError {
                            message: format!("Duplicate match pattern '{}.{}'", pat_enum, variant),
                            location: context.to_string(),
                        });
                    }
                }
                ast::Pattern::Ident(_) => {
                    has_wildcard = true;
                    exhausted = true;
                }
                _ => {}
            }
            if variants.iter().all(|v| seen.contains(v)) {
                exhausted = true;
            }
        }

        if has_wildcard {
            return;
        }

        let missing: Vec<String> = variants
            .iter()
            .filter(|variant| !seen.contains(*variant))
            .map(|variant| format!("{}.{}", enum_name, variant))
            .collect();
        if !missing.is_empty() {
            self.errors.push(TypeError {
                message: format!(
                    "Non-exhaustive match on enum '{}'; missing {}",
                    enum_name,
                    missing.join(", ")
                ),
                location: context.to_string(),
            });
        }
    }

    fn check_result_match(&mut self, expr_ty: &Type, arms: &[ast::MatchArm], context: &str) {
        let Type::Result(ok_ty, err_ty) = expr_ty else {
            return;
        };
        let mut ok_patterns = Vec::new();
        let mut err_patterns = Vec::new();
        let mut seen_irrefutable_ok = false;
        let mut seen_irrefutable_err = false;
        let mut has_wildcard = false;
        let mut exhausted = false;
        for arm in arms {
            if exhausted {
                self.errors.push(TypeError {
                    message: "Unreachable match arm: previous Result patterns already cover Ok and Err".to_string(),
                    location: context.to_string(),
                });
            }
            if arm.guard.is_some() {
                continue;
            }
            match &arm.pattern {
                ast::Pattern::ResultOk(sub_pat) => {
                    if seen_irrefutable_ok {
                        self.errors.push(TypeError {
                            message: "Duplicate match pattern 'Result.Ok'".to_string(),
                            location: context.to_string(),
                        });
                    }
                    if pattern_is_irrefutable(sub_pat) {
                        seen_irrefutable_ok = true;
                    }
                    ok_patterns.push(sub_pat.as_ref());
                }
                ast::Pattern::ResultErr(sub_pat) => {
                    if seen_irrefutable_err {
                        self.errors.push(TypeError {
                            message: "Duplicate match pattern 'Result.Err'".to_string(),
                            location: context.to_string(),
                        });
                    }
                    if pattern_is_irrefutable(sub_pat) {
                        seen_irrefutable_err = true;
                    }
                    err_patterns.push(sub_pat.as_ref());
                }
                ast::Pattern::Ident(_) => {
                    has_wildcard = true;
                    exhausted = true;
                }
                _ => {}
            }
            if seen_irrefutable_ok && seen_irrefutable_err {
                exhausted = true;
            }
        }
        if has_wildcard {
            return;
        }
        let covers_ok = patterns_exhaust_type(&ok_patterns, ok_ty, &self.enums);
        let covers_err = patterns_exhaust_type(&err_patterns, err_ty, &self.enums);
        let mut missing = Vec::new();
        if !covers_ok {
            missing.push("Result.Ok");
        }
        if !covers_err {
            missing.push("Result.Err");
        }
        if !missing.is_empty() {
            self.errors.push(TypeError {
                message: format!(
                    "Non-exhaustive match on Result; missing {}",
                    missing.join(", ")
                ),
                location: context.to_string(),
            });
        }
    }

    fn check_option_match(&mut self, expr_ty: &Type, arms: &[ast::MatchArm], context: &str) {
        let Type::Option(inner) = expr_ty else {
            return;
        };
        let mut some_patterns = Vec::new();
        let mut seen_none = false;
        let mut seen_irrefutable_some = false;
        let mut has_wildcard = false;
        let mut exhausted = false;
        for arm in arms {
            if exhausted {
                self.errors.push(TypeError {
                    message: "Unreachable match arm: previous Option patterns already cover Some and None".to_string(),
                    location: context.to_string(),
                });
            }
            if arm.guard.is_some() {
                continue;
            }
            match &arm.pattern {
                ast::Pattern::Some(sub_pat) => {
                    if seen_irrefutable_some {
                        self.errors.push(TypeError {
                            message: "Duplicate match pattern 'Some'".to_string(),
                            location: context.to_string(),
                        });
                    }
                    if pattern_is_irrefutable(sub_pat) {
                        seen_irrefutable_some = true;
                    }
                    some_patterns.push(sub_pat.as_ref());
                }
                ast::Pattern::None => {
                    if seen_none {
                        self.errors.push(TypeError {
                            message: "Duplicate match pattern 'None'".to_string(),
                            location: context.to_string(),
                        });
                    }
                    seen_none = true;
                }
                ast::Pattern::Ident(_) => {
                    has_wildcard = true;
                    exhausted = true;
                }
                _ => {}
            }
            if seen_irrefutable_some && seen_none {
                exhausted = true;
            }
        }
        if has_wildcard {
            return;
        }
        let covers_some = patterns_exhaust_type(&some_patterns, inner, &self.enums);
        let mut missing = Vec::new();
        if !covers_some {
            missing.push("Some");
        }
        if !seen_none {
            missing.push("None");
        }
        if !missing.is_empty() {
            self.errors.push(TypeError {
                message: format!(
                    "Non-exhaustive match on Option; missing {}",
                    missing.join(", ")
                ),
                location: context.to_string(),
            });
        }
    }

    fn check_bool_match(&mut self, expr_ty: &Type, arms: &[ast::MatchArm], context: &str) {
        if *expr_ty != Type::Bool {
            return;
        }
        let mut seen_true = false;
        let mut seen_false = false;
        let mut has_wildcard = false;
        let mut exhausted = false;
        for arm in arms {
            if exhausted {
                self.errors.push(TypeError {
                    message: "Unreachable match arm: previous boolean patterns already cover true and false".to_string(),
                    location: context.to_string(),
                });
            }
            if arm.guard.is_some() {
                continue;
            }
            match &arm.pattern {
                ast::Pattern::Bool(b) => {
                    if *b {
                        if seen_true {
                            self.errors.push(TypeError {
                                message: "Duplicate match pattern 'true'".to_string(),
                                location: context.to_string(),
                            });
                        }
                        seen_true = true;
                    } else {
                        if seen_false {
                            self.errors.push(TypeError {
                                message: "Duplicate match pattern 'false'".to_string(),
                                location: context.to_string(),
                            });
                        }
                        seen_false = true;
                    }
                }
                ast::Pattern::Literal(Literal::Bool(b)) => {
                    if *b {
                        if seen_true {
                            self.errors.push(TypeError {
                                message: "Duplicate match pattern 'true'".to_string(),
                                location: context.to_string(),
                            });
                        }
                        seen_true = true;
                    } else {
                        if seen_false {
                            self.errors.push(TypeError {
                                message: "Duplicate match pattern 'false'".to_string(),
                                location: context.to_string(),
                            });
                        }
                        seen_false = true;
                    }
                }
                ast::Pattern::Ident(_) => {
                    has_wildcard = true;
                    exhausted = true;
                }
                _ => {}
            }
            if seen_true && seen_false {
                exhausted = true;
            }
        }
        if has_wildcard {
            return;
        }
        let mut missing = Vec::new();
        if !seen_true {
            missing.push("true");
        }
        if !seen_false {
            missing.push("false");
        }
        if !missing.is_empty() {
            self.errors.push(TypeError {
                message: format!(
                    "Non-exhaustive match on bool; missing {}",
                    missing.join(", ")
                ),
                location: context.to_string(),
            });
        }
    }

    fn check_scalar_match(&mut self, expr_ty: &Type, arms: &[ast::MatchArm], context: &str) {
        if !self.is_integer(expr_ty) && *expr_ty != Type::Str && *expr_ty != Type::F32 && *expr_ty != Type::F64 {
            return;
        }
        let mut has_catchall = false;
        for arm in arms {
            if arm.guard.is_none() && matches!(arm.pattern, ast::Pattern::Ident(_)) {
                has_catchall = true;
                break;
            }
        }
        if !has_catchall {
            self.errors.push(TypeError {
                message: format!(
                    "Non-exhaustive match on {:?}; missing catch-all pattern or wildcard '_'",
                    expr_ty
                ),
                location: context.to_string(),
            });
        }
    }

    fn check_match_semantics(&mut self, arms: &[ast::MatchArm], context: &str) {
        let mut catch_all_seen = false;
        let mut seen_int_literals: Vec<i64> = Vec::new();
        let mut seen_str_literals: Vec<String> = Vec::new();
        for arm in arms {
            if catch_all_seen {
                self.errors.push(TypeError {
                    message: "Unreachable match arm: previous catch-all pattern already matches all values".to_string(),
                    location: context.to_string(),
                });
            } else if arm.guard.is_none() {
                match &arm.pattern {
                    ast::Pattern::Literal(Literal::Int(n)) => {
                        if seen_int_literals.contains(n) {
                            self.errors.push(TypeError {
                                message: format!("Duplicate match pattern '{}'", n),
                                location: context.to_string(),
                            });
                        } else {
                            seen_int_literals.push(*n);
                        }
                    }
                    ast::Pattern::Literal(Literal::String(s)) => {
                        if seen_str_literals.contains(s) {
                            self.errors.push(TypeError {
                                message: format!("Duplicate match pattern '\"{}\"'", s),
                                location: context.to_string(),
                            });
                        } else {
                            seen_str_literals.push(s.clone());
                        }
                    }
                    ast::Pattern::Ident(_) => {
                        catch_all_seen = true;
                    }
                    _ => {}
                }
            }
        }
    }

    fn is_integer(&self, ty: &Type) -> bool {
        matches!(ty, Type::I32 | Type::I64)
    }

    fn enum_variant_payloads(&self, enum_name: &str, variant: &str) -> Option<&[Type]> {
        let names = self.enums.get(enum_name)?;
        let index = names.iter().position(|name| name == variant)?;
        self.enum_payloads
            .get(enum_name)?
            .get(index)
            .map(|types| types.as_slice())
    }

    fn enum_variant_has_payload(&self, enum_name: &str, variant: &str) -> bool {
        self.enum_variant_payloads(enum_name, variant)
            .is_some_and(|types| !types.is_empty())
    }

    fn bind_pattern(&mut self, pattern: &ast::Pattern, expr_ty: &Type) {
        match pattern {
            ast::Pattern::Ident(name) if name != "_" => {
                self.variables.insert(name.clone(), expr_ty.clone());
            }
            ast::Pattern::Tuple(sub_pats) => {
                if let Type::Tuple(elem_types) = expr_ty {
                    for (sub_pat, elem_ty) in sub_pats.iter().zip(elem_types.iter()) {
                        self.bind_pattern(sub_pat, elem_ty);
                    }
                }
            }
            ast::Pattern::Struct { name, fields } => {
                if let Some(decl_fields) = self.structs.get(name).cloned() {
                    for (field_name, sub_pat) in fields {
                        if let Some((_, field_ty)) = decl_fields.iter().find(|(n, _)| n == field_name) {
                            self.bind_pattern(sub_pat, field_ty);
                        }
                    }
                }
            }
            ast::Pattern::Some(sub_pat) => {
                if let Type::Option(inner) = expr_ty {
                    self.bind_pattern(sub_pat, inner);
                }
            }
            ast::Pattern::EnumVariant {
                enum_name,
                variant,
                bindings,
            } => {
                let types = self
                    .enum_variant_payloads(enum_name, variant)
                    .map(|types| types.to_vec())
                    .unwrap_or_default();
                for (name, payload) in bindings.iter().zip(types.iter()) {
                    if name != "_" {
                        self.variables.insert(name.clone(), payload.clone());
                    }
                }
            }
            ast::Pattern::ResultOk(sub_pat) => {
                if let Type::Result(ok_ty, _) = expr_ty {
                    self.bind_pattern(sub_pat, ok_ty);
                }
            }
            ast::Pattern::ResultErr(sub_pat) => {
                if let Type::Result(_, err_ty) = expr_ty {
                    self.bind_pattern(sub_pat, err_ty);
                }
            }
            _ => {}
        }
    }

    fn check_enum_payload_constructor(
        &mut self,
        enum_name: &str,
        variant: &str,
        args: &[Expr],
        context: &str,
    ) -> Result<Type> {
        let named = Type::Named(enum_name.to_string());
        let payloads = self
            .enum_variant_payloads(enum_name, variant)
            .map(|types| types.to_vec());
        match payloads.as_deref() {
            None => {
                self.errors.push(TypeError {
                    message: format!("Unknown variant '{}' on enum {}", variant, enum_name),
                    location: context.to_string(),
                });
                Ok(named)
            }
            Some([]) => {
                if !args.is_empty() {
                    self.errors.push(TypeError {
                        message: format!(
                            "Unit variant {}.{} does not take a payload",
                            enum_name, variant
                        ),
                        location: context.to_string(),
                    });
                }
                Ok(named)
            }
            Some(types) if types.len() == 1 || types.len() == 2 => {
                if args.len() != types.len() {
                    self.errors.push(TypeError {
                        message: format!(
                            "Variant {}.{} expects {} payload argument{}, got {}",
                            enum_name,
                            variant,
                            types.len(),
                            if types.len() == 1 { "" } else { "s" },
                            args.len()
                        ),
                        location: context.to_string(),
                    });
                } else {
                    for (index, expected) in types.iter().enumerate() {
                        let expected = expected.clone();
                        let actual = self.infer_expr_with_hint(&args[index], context, Some(&expected))?;
                        if !self.types_compatible(&expected, &actual) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Payload type mismatch for {}.{} argument {}: expected {:?}, got {:?}",
                                    enum_name,
                                    variant,
                                    index + 1,
                                    expected,
                                    actual
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
                Ok(named)
            }
            Some(types) => {
                self.errors.push(TypeError {
                    message: format!(
                        "Multi-field payload construction for {}.{} is not supported yet ({} fields)",
                        enum_name,
                        variant,
                        types.len()
                    ),
                    location: context.to_string(),
                });
                Ok(named)
            }
        }
    }

    fn is_unit_enum(&self, ty: &Type) -> bool {
        match ty {
            Type::Named(name) => self.enums.contains_key(name),
            _ => false,
        }
    }

    fn matches_builtin_arg_rule(&self, rule: BuiltinArgRule, ty: &Type) -> bool {
        match rule {
            BuiltinArgRule::Any => true,
            BuiltinArgRule::Str => matches!(ty, Type::Str),
            BuiltinArgRule::Integer => self.is_integer(ty) || self.is_unit_enum(ty),
            BuiltinArgRule::StrOrArray => matches!(ty, Type::Str | Type::Array(_, _)),
        }
    }

    fn check_pattern_type(&mut self, pattern: &ast::Pattern, expr_ty: &Type, context: &str) {
        match pattern {
            ast::Pattern::Unit => {
                if *expr_ty != Type::Unit {
                    self.errors.push(TypeError {
                        message: format!("Unit pattern cannot match expression of type {:?}", expr_ty),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::Tuple(sub_pats) => {
                if let Type::Tuple(elem_types) = expr_ty {
                    if sub_pats.len() != elem_types.len() {
                        self.errors.push(TypeError {
                            message: format!(
                                "Tuple pattern arity mismatch: expected {}, got {}",
                                elem_types.len(),
                                sub_pats.len()
                            ),
                            location: context.to_string(),
                        });
                    } else {
                        for (sub_pat, elem_ty) in sub_pats.iter().zip(elem_types.iter()) {
                            self.check_pattern_type(sub_pat, elem_ty, context);
                        }
                    }
                } else {
                    self.errors.push(TypeError {
                        message: format!("Tuple pattern cannot match expression of type {:?}", expr_ty),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::Struct { name, fields } => {
                if let Type::Named(struct_name) = expr_ty {
                    if struct_name != name {
                        self.errors.push(TypeError {
                            message: format!("Struct pattern for '{}' cannot match expression of type '{}'", name, struct_name),
                            location: context.to_string(),
                        });
                    } else if let Some(decl_fields) = self.structs.get(name).cloned() {
                        for (field_name, sub_pat) in fields {
                            if let Some((_, field_ty)) = decl_fields.iter().find(|(n, _)| n == field_name) {
                                self.check_pattern_type(sub_pat, field_ty, context);
                            } else {
                                self.errors.push(TypeError {
                                    message: format!("Unknown field '{}' in struct pattern for '{}'", field_name, name),
                                    location: context.to_string(),
                                });
                            }
                        }
                    } else {
                        self.errors.push(TypeError {
                            message: format!("Unknown struct '{}' in pattern", name),
                            location: context.to_string(),
                        });
                    }
                } else {
                    self.errors.push(TypeError {
                        message: format!("Struct pattern '{}' cannot match non-struct expression of type {:?}", name, expr_ty),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::Literal(lit) => {
                let pat_ty = self.literal_type(lit);
                match lit {
                    Literal::Bool(_) => {
                        if *expr_ty != Type::Bool {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Boolean pattern cannot match expression of type {:?}",
                                    expr_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                    Literal::Int(_) => {
                        if !self.is_integer(expr_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Integer pattern cannot match expression of type {:?}",
                                    expr_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                    Literal::String(_) => {
                        if *expr_ty != Type::Str {
                            self.errors.push(TypeError {
                                message: format!(
                                    "String pattern cannot match expression of type {:?}",
                                    expr_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                    _ => {
                        // For other literal types, check compatibility
                        if !self.types_compatible(&pat_ty, expr_ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Pattern type {:?} cannot match expression type {:?}",
                                    pat_ty, expr_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                }
            }
            ast::Pattern::Some(sub_pat) => {
                if let Type::Option(inner) = expr_ty {
                    self.check_pattern_type(sub_pat, inner, context);
                } else {
                    self.errors.push(TypeError {
                        message: format!("Some pattern cannot match non-Option type {:?}", expr_ty),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::None => {
                if !matches!(expr_ty, Type::Option(_)) {
                    self.errors.push(TypeError {
                        message: format!("None pattern cannot match non-Option type {:?}", expr_ty),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::Ident(_) => {
                // Identifier patterns (including wildcard "_") match any type
            }
            ast::Pattern::EnumVariant {
                enum_name,
                variant,
                bindings,
            } => match expr_ty {
                Type::Named(name) if name == enum_name => {
                    if let Some(variants) = self.enums.get(enum_name) {
                        if !variants.iter().any(|item| item == variant) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Unknown variant '{}' on enum {}",
                                    variant, enum_name
                                ),
                                location: context.to_string(),
                            });
                        } else {
                            let expected = self
                                .enum_variant_payloads(enum_name, variant)
                                .map(|types| types.len())
                                .unwrap_or(0);
                            if bindings.len() != expected {
                                if expected == 0 {
                                    self.errors.push(TypeError {
                                        message: format!(
                                            "Unit variant {}.{} does not take a payload binding",
                                            enum_name, variant
                                        ),
                                        location: context.to_string(),
                                    });
                                } else {
                                    self.errors.push(TypeError {
                                        message: format!(
                                            "Variant {}.{} expects {} payload binding{}, got {}",
                                            enum_name,
                                            variant,
                                            expected,
                                            if expected == 1 { "" } else { "s" },
                                            bindings.len()
                                        ),
                                        location: context.to_string(),
                                    });
                                }
                            }
                        }
                    } else {
                        self.errors.push(TypeError {
                            message: format!("Unknown enum '{}'", enum_name),
                            location: context.to_string(),
                        });
                    }
                }
                Type::Named(name) => {
                    self.errors.push(TypeError {
                        message: format!(
                            "Pattern '{}.{}' cannot match enum {}",
                            enum_name, variant, name
                        ),
                        location: context.to_string(),
                    });
                }
                other => {
                    self.errors.push(TypeError {
                        message: format!(
                            "Enum pattern '{}.{}' cannot match expression of type {:?}",
                            enum_name, variant, other
                        ),
                        location: context.to_string(),
                    });
                }
            },
            ast::Pattern::Bool(b) => {
                if *expr_ty != Type::Bool {
                    self.errors.push(TypeError {
                        message: format!(
                            "Boolean pattern '{}' cannot match expression of type {:?}",
                            b, expr_ty
                        ),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::EnumPayload { .. } => {}
            ast::Pattern::ResultOk(sub_pat) => {
                if let Type::Result(ok_ty, _) = expr_ty {
                    self.check_pattern_type(sub_pat, ok_ty, context);
                } else {
                    self.errors.push(TypeError {
                        message: format!(
                            "Result pattern cannot match expression of non-Result type {:?}",
                            expr_ty
                        ),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::ResultErr(sub_pat) => {
                if let Type::Result(_, err_ty) = expr_ty {
                    self.check_pattern_type(sub_pat, err_ty, context);
                } else {
                    self.errors.push(TypeError {
                        message: format!(
                            "Result pattern cannot match expression of non-Result type {:?}",
                            expr_ty
                        ),
                        location: context.to_string(),
                    });
                }
            }
        }
    }

    fn types_compatible(&self, expected: &Type, actual: &Type) -> bool {
        let expected_res = self.resolve_alias(expected);
        let actual_res = self.resolve_alias(actual);
        let expected = &expected_res;
        let actual = &actual_res;
        if expected == actual {
            return true;
        }
        if *actual == Type::Never {
            return true;
        }
        if let (Type::Tuple(t1), Type::Tuple(t2)) = (expected, actual) {
            if t1.len() == t2.len() {
                return t1.iter().zip(t2.iter()).all(|(a, b)| self.types_compatible(a, b));
            }
        }
        // Unit enums lower to integer tags.
        if (self.is_integer(expected) && self.is_unit_enum(actual))
            || (self.is_unit_enum(expected) && self.is_integer(actual))
        {
            return true;
        }
        // Allow numeric coercions
        if self.is_numeric(expected) && self.is_numeric(actual) {
            return true;
        }
        // Arrays with same element type
        if let (Type::Array(e1, _), Type::Array(e2, _)) = (expected, actual) {
            return self.types_compatible(e1, e2);
        }
        // Option types with compatible inner types
        if let (Type::Option(e1), Type::Option(e2)) = (expected, actual) {
            return self.types_compatible(e1, e2);
        }
        // Vec types with compatible element types
        if let (Type::Vec(e1), Type::Vec(e2)) = (expected, actual) {
            return self.types_compatible(e1, e2);
        }
        // Result types with compatible Ok/Err types
        if let (Type::Result(ok1, err1), Type::Result(ok2, err2)) = (expected, actual) {
            return self.types_compatible(ok1, ok2) && self.types_compatible(err1, err2);
        }
        // HashMap types with compatible key/value types
        if let (Type::HashMap(key1, value1), Type::HashMap(key2, value2)) = (expected, actual) {
            return self.types_compatible(key1, key2) && self.types_compatible(value1, value2);
        }
        false
    }
}

fn collect_unit_enums(file: &ast::File) -> HashMap<String, Vec<(String, Vec<Type>)>> {
    let mut enums = HashMap::new();
    for kernel in &file.kernels {
        for item in &kernel.items {
            if let ast::KernelItem::Enum(def) = item {
                enums.insert(
                    def.name.clone(),
                    def.variants
                        .iter()
                        .map(|v| (v.name.clone(), v.payloads.clone()))
                        .collect(),
                );
            }
        }
    }
    enums
}

fn unit_enum_tag(
    enums: &HashMap<String, Vec<(String, Vec<Type>)>>,
    enum_name: &str,
    variant: &str,
) -> Option<i64> {
    enums.get(enum_name).and_then(|variants| {
        variants
            .iter()
            .position(|(item, _)| item == variant)
            .map(|index| index as i64)
    })
}

fn unit_enum_payload_types(
    enums: &HashMap<String, Vec<(String, Vec<Type>)>>,
    enum_name: &str,
    variant: &str,
) -> Vec<Type> {
    enums
        .get(enum_name)
        .and_then(|variants| {
            variants
                .iter()
                .find(|(item, _)| item == variant)
                .map(|(_, types)| types.clone())
        })
        .unwrap_or_default()
}

fn lower_pattern(
    pattern: &mut ast::Pattern,
    enums: &HashMap<String, Vec<(String, Vec<Type>)>>,
) {
    if let ast::Pattern::Tuple(sub_pats) = pattern {
        for sub in sub_pats {
            lower_pattern(sub, enums);
        }
        return;
    }
    if let ast::Pattern::Struct { fields, .. } = pattern {
        for (_, sub_pat) in fields {
            lower_pattern(sub_pat, enums);
        }
        return;
    }
    if let ast::Pattern::Some(sub_pat) = pattern {
        lower_pattern(sub_pat, enums);
        return;
    }
    if let ast::Pattern::ResultOk(sub_pat) = pattern {
        lower_pattern(sub_pat, enums);
        return;
    }
    if let ast::Pattern::ResultErr(sub_pat) = pattern {
        lower_pattern(sub_pat, enums);
        return;
    }
    let ast::Pattern::EnumVariant {
        enum_name,
        variant,
        bindings,
    } = pattern.clone()
    else {
        return;
    };
    if let Some(tag) = unit_enum_tag(enums, &enum_name, &variant) {
        if bindings.is_empty() {
            *pattern = ast::Pattern::Literal(Literal::Int(tag));
        } else {
            let types = unit_enum_payload_types(enums, &enum_name, &variant);
            *pattern = ast::Pattern::EnumPayload {
                tag,
                bindings,
                types,
            };
        }
    }
}

fn pack_enum_payload(value: Expr, shift: i64, rest: Expr) -> Expr {
    Expr::Binary {
        op: BinaryOp::BitOr,
        left: Box::new(Expr::Binary {
            op: BinaryOp::Shl,
            left: Box::new(value),
            right: Box::new(Expr::Literal(Literal::Int(shift))),
        }),
        right: Box::new(rest),
    }
}

fn lower_expr(expr: &mut Expr, enums: &HashMap<String, Vec<(String, Vec<Type>)>>) {
    match expr {
        Expr::Field {
            expr: object,
            field,
        } => {
            if let Expr::Ident(type_name) = object.as_ref() {
                if let Some(tag) = unit_enum_tag(enums, type_name, field) {
                    *expr = Expr::Literal(Literal::Int(tag));
                    return;
                }
            }
            lower_expr(object, enums);
        }
        Expr::Binary { left, right, .. } => {
            lower_expr(left, enums);
            lower_expr(right, enums);
        }
        Expr::Unary { expr: inner, .. } => lower_expr(inner, enums),
        Expr::Call { func, args } => {
            // Pack payload constructors as (payload << 8) | tag.
            // Pack two-field payload constructors as (a << 20) | (b << 8) | tag.
            if let Expr::Field {
                expr: object,
                field,
            } = func.as_ref()
            {
                if let Expr::Ident(type_name) = object.as_ref() {
                    if let Some(tag) = unit_enum_tag(enums, type_name, field) {
                        if args.len() == 1 {
                            let mut payload = args[0].clone();
                            lower_expr(&mut payload, enums);
                            *expr = pack_enum_payload(payload, 8, Expr::Literal(Literal::Int(tag)));
                            return;
                        }
                        if args.len() == 2 {
                            let mut first = args[0].clone();
                            let mut second = args[1].clone();
                            lower_expr(&mut first, enums);
                            lower_expr(&mut second, enums);
                            *expr = pack_enum_payload(
                                first,
                                20,
                                pack_enum_payload(second, 8, Expr::Literal(Literal::Int(tag))),
                            );
                            return;
                        }
                    }
                }
            }
            lower_expr(func, enums);
            for arg in args {
                lower_expr(arg, enums);
            }
        }
        Expr::Index { expr: inner, index } => {
            lower_expr(inner, enums);
            lower_expr(index, enums);
        }
        Expr::Use { args, .. } => {
            for (_, value) in args {
                lower_expr(value, enums);
            }
        }
        Expr::Send { message, args, .. } => {
            lower_expr(message, enums);
            for (_, value) in args {
                lower_expr(value, enums);
            }
        }
        Expr::Lambda { body, .. } => lower_expr(body, enums),
        Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            lower_expr(condition, enums);
            lower_expr(then_expr, enums);
            lower_expr(else_expr, enums);
        }
        Expr::Match {
            expr: scrutinee,
            arms,
        } => {
            lower_expr(scrutinee, enums);
            for arm in arms {
                lower_pattern(&mut arm.pattern, enums);
                if let Some(guard) = &mut arm.guard {
                    lower_expr(guard, enums);
                }
                match &mut arm.body {
                    ast::MatchBody::Expr(body) => lower_expr(body, enums),
                    ast::MatchBody::Block(block) => lower_block(block, enums),
                }
            }
        }
        Expr::Block(block) => lower_block(block, enums),
        Expr::Some(inner) => lower_expr(inner, enums),
        Expr::Tuple(elements) => {
            for element in elements {
                lower_expr(element, enums);
            }
        }
        Expr::Array(elements) => {
            for element in elements {
                lower_expr(element, enums);
            }
        }
        Expr::Struct { fields, .. } => {
            for (_, value) in fields {
                lower_expr(value, enums);
            }
        }
        Expr::Try(inner) => lower_expr(inner, enums),
        Expr::Copy(inner) => lower_expr(inner, enums),
        Expr::Range { start, end, .. } => {
            lower_expr(start, enums);
            lower_expr(end, enums);
        }
        Expr::Cast { expr: inner, .. } => lower_expr(inner, enums),
        Expr::Unit | Expr::Literal(_) | Expr::Ident(_) | Expr::None => {}
    }
}

fn lower_stmt(stmt: &mut Stmt, enums: &HashMap<String, Vec<(String, Vec<Type>)>>) {
    match stmt {
        Stmt::Let { value, .. } => lower_expr(value, enums),
        Stmt::Assign { target, value } => {
            lower_expr(target, enums);
            lower_expr(value, enums);
        }
        Stmt::Return(Some(value)) => lower_expr(value, enums),
        Stmt::Return(None) | Stmt::Break(_) | Stmt::Continue(_) => {}
        Stmt::If {
            condition,
            then_block,
            else_block,
        } => {
            lower_expr(condition, enums);
            lower_block(then_block, enums);
            if let Some(block) = else_block {
                lower_block(block, enums);
            }
        }
        Stmt::For { iter, body, .. } => {
            lower_expr(iter, enums);
            lower_block(body, enums);
        }
        Stmt::While { condition, body, .. } => {
            lower_expr(condition, enums);
            lower_block(body, enums);
        }
        Stmt::Loop { body, .. } | Stmt::Defer(body) => lower_block(body, enums),
        Stmt::Match { expr, arms } => {
            lower_expr(expr, enums);
            for arm in arms {
                lower_pattern(&mut arm.pattern, enums);
                if let Some(guard) = &mut arm.guard {
                    lower_expr(guard, enums);
                }
                match &mut arm.body {
                    ast::MatchBody::Expr(body) => lower_expr(body, enums),
                    ast::MatchBody::Block(block) => lower_block(block, enums),
                }
            }
        }
        Stmt::Send { message, args, .. } => {
            lower_expr(message, enums);
            for (_, value) in args {
                lower_expr(value, enums);
            }
        }
        Stmt::Expr(expr) => lower_expr(expr, enums),
    }
}

fn lower_block(block: &mut ast::Block, enums: &HashMap<String, Vec<(String, Vec<Type>)>>) {
    for stmt in &mut block.statements {
        lower_stmt(stmt, enums);
    }
}

/// Replace unit-enum constructors and patterns with integer tags for codegen/JIT.
pub fn lower_type_aliases(file: &mut ast::File) {
    let mut aliases = HashMap::new();
    for kernel in &file.kernels {
        for item in &kernel.items {
            if let ast::KernelItem::TypeAlias(a) = item {
                aliases.insert(a.name.clone(), a.target.clone());
            }
        }
    }
    if aliases.is_empty() {
        return;
    }

    fn resolve_ty(ty: &mut ast::Type, aliases: &HashMap<String, ast::Type>) {
        let mut depth = 0;
        while let ast::Type::Named(name) = ty {
            if let Some(target) = aliases.get(name) {
                *ty = target.clone();
                depth += 1;
                if depth > 32 {
                    break;
                }
            } else {
                break;
            }
        }
        match ty {
            ast::Type::Option(inner) => resolve_ty(inner, aliases),
            ast::Type::Result(ok, err) => {
                resolve_ty(ok, aliases);
                resolve_ty(err, aliases);
            }
            ast::Type::Vec(elem) => resolve_ty(elem, aliases),
            ast::Type::HashMap(k, v) => {
                resolve_ty(k, aliases);
                resolve_ty(v, aliases);
            }
            ast::Type::Array(elem, _) => resolve_ty(elem, aliases),
            ast::Type::Tuple(elems) => {
                for elem in elems {
                    resolve_ty(elem, aliases);
                }
            }
            ast::Type::Ref { ty: inner, .. } => resolve_ty(inner, aliases),
            _ => {}
        }
    }

    fn lower_block_types(block: &mut ast::Block, aliases: &HashMap<String, ast::Type>) {
        for stmt in &mut block.statements {
            match stmt {
                ast::Stmt::Let { ty, value, .. } => {
                    if let Some(t) = ty {
                        resolve_ty(t, aliases);
                    }
                    lower_expr_types(value, aliases);
                }
                ast::Stmt::Assign { target, value } => {
                    lower_expr_types(target, aliases);
                    lower_expr_types(value, aliases);
                }
                ast::Stmt::Expr(expr) => lower_expr_types(expr, aliases),
                ast::Stmt::Return(Some(expr)) => lower_expr_types(expr, aliases),
                ast::Stmt::If { condition, then_block, else_block } => {
                    lower_expr_types(condition, aliases);
                    lower_block_types(then_block, aliases);
                    if let Some(b) = else_block {
                        lower_block_types(b, aliases);
                    }
                }
                ast::Stmt::While { condition, body, .. } => {
                    lower_expr_types(condition, aliases);
                    lower_block_types(body, aliases);
                }
                ast::Stmt::For { iter, body, .. } => {
                    lower_expr_types(iter, aliases);
                    lower_block_types(body, aliases);
                }
                ast::Stmt::Loop { body, .. } => {
                    lower_block_types(body, aliases);
                }
                ast::Stmt::Defer(block) => {
                    lower_block_types(block, aliases);
                }
                _ => {}
            }
        }
    }

    fn lower_expr_types(expr: &mut ast::Expr, aliases: &HashMap<String, ast::Type>) {
        match expr {
            ast::Expr::Cast { expr: inner, target_type } => {
                lower_expr_types(inner, aliases);
                resolve_ty(target_type, aliases);
            }
            ast::Expr::Binary { left, right, .. } => {
                lower_expr_types(left, aliases);
                lower_expr_types(right, aliases);
            }
            ast::Expr::Unary { expr: inner, .. } => lower_expr_types(inner, aliases),
            ast::Expr::Call { func, args } => {
                lower_expr_types(func, aliases);
                for arg in args {
                    lower_expr_types(arg, aliases);
                }
            }
            ast::Expr::Index { expr: inner, index } => {
                lower_expr_types(inner, aliases);
                lower_expr_types(index, aliases);
            }
            ast::Expr::Field { expr: inner, .. } => lower_expr_types(inner, aliases),
            ast::Expr::If { condition, then_expr, else_expr } => {
                lower_expr_types(condition, aliases);
                lower_expr_types(then_expr, aliases);
                lower_expr_types(else_expr, aliases);
            }
            ast::Expr::Match { expr: inner, arms } => {
                lower_expr_types(inner, aliases);
                for arm in arms {
                    if let Some(guard) = &mut arm.guard {
                        lower_expr_types(guard, aliases);
                    }
                    match &mut arm.body {
                        ast::MatchBody::Expr(e) => lower_expr_types(e, aliases),
                        ast::MatchBody::Block(b) => lower_block_types(b, aliases),
                    }
                }
            }
            ast::Expr::Block(block) => lower_block_types(block, aliases),
            ast::Expr::Some(inner) | ast::Expr::Copy(inner) | ast::Expr::Try(inner) => {
                lower_expr_types(inner, aliases);
            }
            ast::Expr::Array(elements) | ast::Expr::Tuple(elements) => {
                for el in elements {
                    lower_expr_types(el, aliases);
                }
            }
            ast::Expr::Struct { fields, .. } => {
                for (_, val) in fields {
                    lower_expr_types(val, aliases);
                }
            }
            _ => {}
        }
    }

    for kernel in &mut file.kernels {
        for item in &mut kernel.items {
            match item {
                ast::KernelItem::Function(func) | ast::KernelItem::ComptimeFn(func) => {
                    for param in &mut func.params {
                        resolve_ty(&mut param.ty, &aliases);
                    }
                    if let Some(ret) = &mut func.return_type {
                        resolve_ty(ret, &aliases);
                    }
                    lower_block_types(&mut func.body, &aliases);
                }
                ast::KernelItem::Struct(s) => {
                    for field in &mut s.fields {
                        resolve_ty(&mut field.ty, &aliases);
                    }
                }
                ast::KernelItem::Enum(e) => {
                    for variant in &mut e.variants {
                        for payload in &mut variant.payloads {
                            resolve_ty(payload, &aliases);
                        }
                    }
                }
                ast::KernelItem::Const(c) => {
                    resolve_ty(&mut c.ty, &aliases);
                    lower_expr_types(&mut c.value, &aliases);
                }
                ast::KernelItem::TypeAlias(_) => {}
            }
        }
    }
}

pub fn lower_unit_enums(file: &mut ast::File) {
    lower_type_aliases(file);
    let enums = collect_unit_enums(file);
    if enums.is_empty() {
        return;
    }

    for kernel in &mut file.kernels {
        for item in &mut kernel.items {
            match item {
                ast::KernelItem::Function(func) | ast::KernelItem::ComptimeFn(func) => {
                    lower_block(&mut func.body, &enums);
                }
                ast::KernelItem::Const(def) => lower_expr(&mut def.value, &enums),
                ast::KernelItem::Struct(_) | ast::KernelItem::Enum(_) | ast::KernelItem::TypeAlias(_) => {}
            }
        }
    }
}

pub fn check_file(file: &ast::File) -> Result<Vec<TypeError>> {
    let mut all_errors = Vec::new();
    let mut checker = TypeChecker::new();

    for kernel in &file.kernels {
        let before = checker.errors.len();
        checker.check_kernel(kernel)?;
        all_errors.extend(checker.errors[before..].iter().cloned());
    }

    // Check shells
    for shell in &file.shells {
        let errors = check_shell(shell, file)?;
        all_errors.extend(errors);
    }

    // Check views
    for view in &file.views {
        let errors = check_view(view, file)?;
        all_errors.extend(errors);
    }

    Ok(all_errors)
}

/// Collect all message signatures from a shell
fn collect_message_signatures(shell: &ast::Shell) -> ShellAgentMessages {
    let mut agent_messages: ShellAgentMessages = HashMap::new();

    for agent in &shell.agents {
        let mut messages: HashMap<String, Vec<(String, ast::Type)>> = HashMap::new();
        for handler in &agent.handlers {
            let params: Vec<(String, ast::Type)> = handler
                .params
                .iter()
                .map(|p| (p.name.clone(), p.ty.clone()))
                .collect();
            messages.insert(handler.message.clone(), params);
        }
        agent_messages.insert(agent.name.clone(), messages);
    }

    agent_messages
}

/// Collect agent state fields
fn collect_agent_state(shell: &ast::Shell) -> ShellAgentState {
    let mut agent_state: ShellAgentState = HashMap::new();

    for agent in &shell.agents {
        let mut state: HashMap<String, ast::Type> = HashMap::new();
        for decl in &agent.state {
            // Infer type from the initial value
            let ty = infer_literal_type(&decl.value);
            state.insert(decl.name.clone(), ty);
        }
        agent_state.insert(agent.name.clone(), state);
    }

    agent_state
}

/// Infer type from a literal expression (for state initialization)
fn infer_literal_type(expr: &ast::Expr) -> ast::Type {
    match expr {
        ast::Expr::Literal(lit) => match lit {
            ast::Literal::Int(_) => ast::Type::I32,
            ast::Literal::Float(_) => ast::Type::F64,
            ast::Literal::Bool(_) => ast::Type::Bool,
            ast::Literal::String(_) => ast::Type::Str,
            ast::Literal::Char(_) => ast::Type::I32,
            ast::Literal::HexColor(_) => ast::Type::I32,
        },
        _ => ast::Type::I32, // fallback
    }
}

/// Check a shell for type errors
fn check_shell(shell: &ast::Shell, _file: &ast::File) -> Result<Vec<TypeError>> {
    let mut errors = Vec::new();

    // Collect message signatures from all agents
    let agent_messages = collect_message_signatures(shell);

    // Check each agent's message handlers
    for agent in &shell.agents {
        for handler in &agent.handlers {
            // Check send statements in handler body
            check_shell_block(&handler.body, &agent_messages, &shell.name, &mut errors);
        }
    }

    Ok(errors)
}

/// Check a block for send statement validation
fn check_shell_block(
    block: &ast::Block,
    agent_messages: &ShellAgentMessages,
    shell_name: &str,
    errors: &mut Vec<TypeError>,
) {
    for stmt in &block.statements {
        check_shell_stmt(stmt, agent_messages, shell_name, errors);
    }
}

/// Check a statement for send validation
fn check_shell_stmt(
    stmt: &ast::Stmt,
    agent_messages: &ShellAgentMessages,
    shell_name: &str,
    errors: &mut Vec<TypeError>,
) {
    match stmt {
        ast::Stmt::Send {
            message,
            target,
            args,
        } => {
            // Get message name from expression
            let msg_name = match message {
                ast::Expr::Literal(ast::Literal::String(s)) => s.trim_matches('"').to_string(),
                _ => return, // Skip non-literal message names
            };

            // Skip system messages
            if target == "System" {
                return;
            }

            // Find the target agent's message signature
            if let Some(agent_msgs) = agent_messages.get(target) {
                if let Some(expected_params) = agent_msgs.get(&msg_name) {
                    // Check argument count
                    if args.len() != expected_params.len() {
                        errors.push(TypeError {
                            message: format!(
                                "Message '{}' to {} expects {} argument(s), got {}",
                                msg_name,
                                target,
                                expected_params.len(),
                                args.len()
                            ),
                            location: shell_name.to_string(),
                        });
                    }

                    // Check argument names and types
                    for (expected_name, expected_ty) in expected_params {
                        if let Some((_, arg_expr)) = args.iter().find(|(n, _)| n == expected_name) {
                            let actual_ty = infer_literal_type(arg_expr);
                            if !types_are_compatible(expected_ty, &actual_ty) {
                                errors.push(TypeError {
                                    message: format!(
                                        "Message '{}' argument '{}' expects {:?}, got {:?}",
                                        msg_name, expected_name, expected_ty, actual_ty
                                    ),
                                    location: shell_name.to_string(),
                                });
                            }
                        } else if !args.is_empty() {
                            // Argument name not found
                            errors.push(TypeError {
                                message: format!(
                                    "Message '{}' missing required argument '{}'",
                                    msg_name, expected_name
                                ),
                                location: shell_name.to_string(),
                            });
                        }
                    }
                } else {
                    errors.push(TypeError {
                        message: format!(
                            "Agent {} has no handler for message '{}'",
                            target, msg_name
                        ),
                        location: shell_name.to_string(),
                    });
                }
            } else {
                errors.push(TypeError {
                    message: format!("Unknown agent: {}", target),
                    location: shell_name.to_string(),
                });
            }
        }
        ast::Stmt::If {
            then_block,
            else_block,
            ..
        } => {
            check_shell_block(then_block, agent_messages, shell_name, errors);
            if let Some(eb) = else_block {
                check_shell_block(eb, agent_messages, shell_name, errors);
            }
        }
        ast::Stmt::For { body, .. } | ast::Stmt::While { body, .. } | ast::Stmt::Loop { body, .. } => {
            check_shell_block(body, agent_messages, shell_name, errors);
        }
        ast::Stmt::Match { arms, .. } => {
            for arm in arms {
                if let ast::MatchBody::Block(b) = &arm.body {
                    check_shell_block(b, agent_messages, shell_name, errors);
                }
            }
        }
        ast::Stmt::Defer(body) => {
            check_shell_block(body, agent_messages, shell_name, errors);
        }
        _ => {}
    }
}

/// Check types are compatible (standalone function for shell checking)
fn types_are_compatible(expected: &ast::Type, actual: &ast::Type) -> bool {
    if expected == actual {
        return true;
    }
    // Allow numeric coercions
    let is_numeric = |t: &ast::Type| {
        matches!(
            t,
            ast::Type::I32 | ast::Type::I64 | ast::Type::F32 | ast::Type::F64
        )
    };
    if is_numeric(expected) && is_numeric(actual) {
        return true;
    }
    false
}

/// Check a view for type errors
fn check_view(view: &ast::View, file: &ast::File) -> Result<Vec<TypeError>> {
    let mut errors = Vec::new();

    // Collect all shell information
    let mut all_agent_messages: ViewAgentMessages = HashMap::new();
    let mut all_agent_state: ViewAgentState = HashMap::new();

    for shell in &file.shells {
        all_agent_messages.insert(shell.name.clone(), collect_message_signatures(shell));
        all_agent_state.insert(shell.name.clone(), collect_agent_state(shell));
    }

    // Check each component
    for component in &view.components {
        check_view_component(
            component,
            &all_agent_messages,
            &all_agent_state,
            &view.name,
            &mut errors,
        );
    }

    Ok(errors)
}

/// Check a view component for type errors
fn check_view_component(
    component: &ast::Component,
    all_agent_messages: &ViewAgentMessages,
    all_agent_state: &ViewAgentState,
    view_name: &str,
    errors: &mut Vec<TypeError>,
) {
    // Check properties
    for prop in &component.properties {
        check_view_expr(
            &prop.value,
            all_agent_messages,
            all_agent_state,
            view_name,
            errors,
        );
    }

    // Check children recursively
    for child in &component.children {
        check_view_component(
            child,
            all_agent_messages,
            all_agent_state,
            view_name,
            errors,
        );
    }
}

/// Check a view expression for type errors
fn check_view_expr(
    expr: &ast::Expr,
    all_agent_messages: &ViewAgentMessages,
    all_agent_state: &ViewAgentState,
    view_name: &str,
    errors: &mut Vec<TypeError>,
) {
    match expr {
        ast::Expr::Send {
            message,
            target,
            args,
        } if target.len() >= 2 => {
            // Validate send expression against shell message signatures
            // target is Vec<String> like ["App", "Worker"]
            let shell_name = &target[0];
            let agent_name = &target[1];

            // Get message name
            let msg_name = match message.as_ref() {
                ast::Expr::Literal(ast::Literal::String(s)) => s.trim_matches('"').to_string(),
                _ => return,
            };

            if let Some(shell_agents) = all_agent_messages.get(shell_name) {
                if let Some(agent_msgs) = shell_agents.get(agent_name) {
                    if let Some(expected_params) = agent_msgs.get(&msg_name) {
                        // Check argument count
                        if args.len() != expected_params.len() {
                            errors.push(TypeError {
                                message: format!(
                                    "Send '{}' to {}.{} expects {} argument(s), got {}",
                                    msg_name,
                                    shell_name,
                                    agent_name,
                                    expected_params.len(),
                                    args.len()
                                ),
                                location: view_name.to_string(),
                            });
                        }

                        // Check argument types
                        for (expected_name, expected_ty) in expected_params {
                            if let Some((_, arg_expr)) =
                                args.iter().find(|(n, _)| n == expected_name)
                            {
                                let actual_ty = infer_literal_type(arg_expr);
                                if !types_are_compatible(expected_ty, &actual_ty) {
                                    errors.push(TypeError {
                                        message: format!(
                                            "Send '{}' argument '{}' expects {:?}, got {:?}",
                                            msg_name, expected_name, expected_ty, actual_ty
                                        ),
                                        location: view_name.to_string(),
                                    });
                                }
                            }
                        }
                    }
                }
            }
        }
        ast::Expr::Field { expr: inner, field } => {
            // Check for Shell.Agent.field bindings
            if let ast::Expr::Field {
                expr: inner2,
                field: agent_name,
            } = inner.as_ref()
            {
                if let ast::Expr::Ident(shell_name) = inner2.as_ref() {
                    // This is a Shell.Agent.field access
                    if let Some(shell_state) = all_agent_state.get(shell_name) {
                        if let Some(agent_fields) = shell_state.get(agent_name) {
                            if !agent_fields.contains_key(field) {
                                errors.push(TypeError {
                                    message: format!(
                                        "Unknown state field '{}.{}.{}'",
                                        shell_name, agent_name, field
                                    ),
                                    location: view_name.to_string(),
                                });
                            }
                        } else {
                            errors.push(TypeError {
                                message: format!("Unknown agent '{}.{}'", shell_name, agent_name),
                                location: view_name.to_string(),
                            });
                        }
                    }
                }
            }
            // Recurse into inner expression
            check_view_expr(
                inner,
                all_agent_messages,
                all_agent_state,
                view_name,
                errors,
            );
        }
        ast::Expr::Binary { left, right, .. } => {
            check_view_expr(left, all_agent_messages, all_agent_state, view_name, errors);
            check_view_expr(
                right,
                all_agent_messages,
                all_agent_state,
                view_name,
                errors,
            );
        }
        ast::Expr::Unary { expr: inner, .. } => {
            check_view_expr(
                inner,
                all_agent_messages,
                all_agent_state,
                view_name,
                errors,
            );
        }
        ast::Expr::Call { args, .. } => {
            for arg in args {
                check_view_expr(arg, all_agent_messages, all_agent_state, view_name, errors);
            }
        }
        _ => {}
    }
}
