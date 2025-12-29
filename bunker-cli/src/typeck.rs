use std::collections::{HashMap, HashSet};
use anyhow::Result;
use crate::ast::{self, Type, Expr, Stmt, BinaryOp, UnaryOp, Literal};

#[derive(Debug, Clone)]
pub struct TypeError {
    pub message: String,
    pub location: String,
}

pub struct TypeChecker {
    // Type environment: variable name -> type
    variables: HashMap<String, Type>,
    // Function signatures: name -> (params, return_type)
    functions: HashMap<String, (Vec<Type>, Option<Type>)>,
    // Struct definitions: name -> fields
    structs: HashMap<String, Vec<(String, Type)>>,
    // Errors collected during type checking
    errors: Vec<TypeError>,
    // Current function return type (for checking return statements)
    current_return_type: Option<Type>,
    // Move tracking: variables that have been moved
    moved_vars: HashSet<String>,
    // Where each variable was moved (for error messages)
    moved_locations: HashMap<String, String>,
}

impl TypeChecker {
    pub fn new() -> Self {
        let mut tc = Self {
            variables: HashMap::new(),
            functions: HashMap::new(),
            structs: HashMap::new(),
            errors: Vec::new(),
            current_return_type: None,
            moved_vars: HashSet::new(),
            moved_locations: HashMap::new(),
        };
        // Register built-in functions
        tc.functions.insert("log".to_string(), (vec![Type::Str], None));
        tc.functions.insert("print".to_string(), (vec![Type::Str], None));
        tc.functions.insert("println".to_string(), (vec![Type::Str], None));
        tc.functions.insert("panic".to_string(), (vec![Type::Str], None));
        tc.functions.insert("assert".to_string(), (vec![Type::Bool], None));
        tc
    }

    pub fn check_kernel(&mut self, kernel: &ast::Kernel) -> Result<Vec<TypeError>> {
        // First pass: collect all struct and function signatures
        for item in &kernel.items {
            match item {
                ast::KernelItem::Struct(s) => {
                    let fields: Vec<(String, Type)> = s.fields.iter()
                        .map(|f| (f.name.clone(), f.ty.clone()))
                        .collect();
                    self.structs.insert(s.name.clone(), fields);
                }
                ast::KernelItem::Function(f) | ast::KernelItem::ComptimeFn(f) => {
                    let param_types: Vec<Type> = f.params.iter()
                        .map(|p| p.ty.clone())
                        .collect();
                    self.functions.insert(f.name.clone(), (param_types, f.return_type.clone()));
                }
                ast::KernelItem::Const(c) => {
                    self.variables.insert(c.name.clone(), c.ty.clone());
                }
            }
        }

        // Second pass: type check function bodies
        for item in &kernel.items {
            if let ast::KernelItem::Function(f) = item {
                self.check_function(f)?;
            }
        }

        Ok(self.errors.clone())
    }

    fn check_function(&mut self, func: &ast::Function) -> Result<()> {
        // Save and set return type context
        let prev_return = self.current_return_type.take();
        self.current_return_type = func.return_type.clone();

        // Save current variable scope and move tracking
        let saved_vars = self.variables.clone();
        let saved_moved = self.moved_vars.clone();
        let saved_moved_locations = self.moved_locations.clone();

        // Add parameters to scope
        for param in &func.params {
            self.variables.insert(param.name.clone(), param.ty.clone());
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
                    self.variables.insert(name.clone(), Type::Option(Box::new(Type::I32)));
                    return Ok(None);
                }

                let inferred = self.infer_expr(value, context)?;

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
                    if !self.types_compatible(declared, &inferred) {
                        self.errors.push(TypeError {
                            message: format!(
                                "Type mismatch in let binding '{}': declared {:?}, got {:?}",
                                name, declared, inferred
                            ),
                            location: context.to_string(),
                        });
                    }
                    self.variables.insert(name.clone(), declared.clone());
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
                let ret_ty = if let Some(e) = expr {
                    Some(self.infer_expr(e, context)?)
                } else {
                    None
                };

                if let Some(expected) = &self.current_return_type {
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
                            self.errors.push(TypeError {
                                message: format!(
                                    "Missing return value: expected {:?}",
                                    expected
                                ),
                                location: context.to_string(),
                            });
                        }
                        _ => {}
                    }
                } else if ret_ty.is_some() {
                    self.errors.push(TypeError {
                        message: "Returning value from void function".to_string(),
                        location: context.to_string(),
                    });
                }
                Ok(ret_ty)
            }
            Stmt::If { condition, then_block, else_block } => {
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
            Stmt::For { var, iter, body } => {
                // Determine element type based on iterator expression
                let elem_ty = match iter {
                    // Range expressions: the element type is the range bound type
                    Expr::Range { start, .. } => {
                        self.infer_expr(start, context)?
                    }
                    // For arrays, the element type is the array element type
                    other => {
                        let iter_ty = self.infer_expr(other, context)?;
                        match &iter_ty {
                            Type::Array(elem, _) => (**elem).clone(),
                            _ => {
                                self.errors.push(TypeError {
                                    message: format!("for-loop requires an array or range, got {:?}", iter_ty),
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
                self.check_block(body, context)?;
                self.variables = saved;
                self.moved_vars = saved_moved;
                Ok(None)
            }
            Stmt::Loop(body) => {
                self.check_block(body, context)?;
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
            _ => Ok(None),
        }
    }

    fn infer_expr(&mut self, expr: &Expr, context: &str) -> Result<Type> {
        match expr {
            Expr::Literal(lit) => Ok(self.literal_type(lit)),
            Expr::Ident(name) => {
                // Check for use-after-move
                if self.moved_vars.contains(name) {
                    let moved_at = self.moved_locations.get(name)
                        .cloned()
                        .unwrap_or_else(|| "unknown".to_string());
                    self.errors.push(TypeError {
                        message: format!(
                            "Use of moved value '{}' (moved at {})",
                            name, moved_at
                        ),
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
                if let Expr::Ident(name) = func.as_ref() {
                    // strlen builtin: string length
                    if name == "strlen" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("strlen expects 1 argument, got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("strlen expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::I32);
                    }
                    // len builtin: works on arrays and strings
                    if name == "len" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("len expects 1 argument, got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str | Type::Array(_, _)) {
                                self.errors.push(TypeError {
                                    message: format!("len expects array or str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::I32);
                    }
                    // read_file builtin: reads file content as string
                    if name == "read_file" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("read_file expects 1 argument, got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("read_file expects str path, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Str);
                    }
                    // write_file builtin: writes content to file
                    if name == "write_file" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("write_file expects 2 arguments, got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if args.len() >= 1 {
                            let path_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(path_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("write_file path must be str, got {:?}", path_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        if args.len() >= 2 {
                            let content_ty = self.infer_expr(&args[1], context)?;
                            if !matches!(content_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("write_file content must be str, got {:?}", content_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Bool);
                    }
                    // file_exists builtin: checks if file exists
                    if name == "file_exists" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("file_exists expects 1 argument, got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("file_exists expects str path, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Bool);
                    }

                    // String operation builtins
                    if name == "char_at" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("char_at expects 2 arguments (string, index), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if args.len() >= 1 {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("char_at expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        if args.len() >= 2 {
                            let arg_ty = self.infer_expr(&args[1], context)?;
                            if !matches!(arg_ty, Type::I64 | Type::I32) {
                                self.errors.push(TypeError {
                                    message: format!("char_at expects i64 index, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Str);
                    }

                    if name == "substring" {
                        if args.len() != 3 {
                            self.errors.push(TypeError {
                                message: format!("substring expects 3 arguments (string, start, end), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if args.len() >= 1 {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("substring expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Str);
                    }

                    if name == "contains" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("contains expects 2 arguments (string, substring), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if args.len() >= 1 {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("contains expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        if args.len() >= 2 {
                            let arg_ty = self.infer_expr(&args[1], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("contains expects str substring, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "starts_with" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("starts_with expects 2 arguments (string, prefix), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if args.len() >= 1 {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("starts_with expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        if args.len() >= 2 {
                            let arg_ty = self.infer_expr(&args[1], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("starts_with expects str prefix, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "ends_with" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("ends_with expects 2 arguments (string, suffix), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if args.len() >= 1 {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("ends_with expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        if args.len() >= 2 {
                            let arg_ty = self.infer_expr(&args[1], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("ends_with expects str suffix, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "trim" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("trim expects 1 argument (string), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("trim expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Str);
                    }

                    if name == "parse_int" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("parse_int expects 1 argument (string), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("parse_int expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::I64);
                    }

                    if name == "int_to_string" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("int_to_string expects 1 argument (integer), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::I64 | Type::I32) {
                                self.errors.push(TypeError {
                                    message: format!("int_to_string expects i64 or i32, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Str);
                    }

                    if name == "char_code" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("char_code expects 1 argument (string), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::Str) {
                                self.errors.push(TypeError {
                                    message: format!("char_code expects str, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::I64);
                    }

                    if name == "from_char_code" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("from_char_code expects 1 argument (integer), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        if !args.is_empty() {
                            let arg_ty = self.infer_expr(&args[0], context)?;
                            if !matches!(arg_ty, Type::I64 | Type::I32) {
                                self.errors.push(TypeError {
                                    message: format!("from_char_code expects i64 or i32, got {:?}", arg_ty),
                                    location: context.to_string(),
                                });
                            }
                        }
                        return Ok(Type::Str);
                    }

                    // Vec operation builtins
                    if name == "vec_new" {
                        if !args.is_empty() {
                            self.errors.push(TypeError {
                                message: format!("vec_new expects 0 arguments, got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        // Return I64 - Vec is represented as a pointer (i64) at runtime
                        return Ok(Type::I64);
                    }

                    if name == "vec_push" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("vec_push expects 2 arguments (vec, value), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        // Vec is represented as i64 pointer at runtime
                        return Ok(Type::I64);
                    }

                    if name == "vec_pop" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("vec_pop expects 1 argument (vec), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "vec_len" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("vec_len expects 1 argument (vec), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "vec_capacity" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("vec_capacity expects 1 argument (vec), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "vec_get" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("vec_get expects 2 arguments (vec, index), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "vec_set" {
                        if args.len() != 3 {
                            self.errors.push(TypeError {
                                message: format!("vec_set expects 3 arguments (vec, index, value), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "vec_clear" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("vec_clear expects 1 argument (vec), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I32); // void-like return
                    }

                    // Result operation builtins
                    if name == "result_ok" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("result_ok expects 1 argument (value), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::Result(Box::new(Type::I64), Box::new(Type::I64)));
                    }

                    if name == "result_err" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("result_err expects 1 argument (error), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::Result(Box::new(Type::I64), Box::new(Type::I64)));
                    }

                    if name == "result_is_ok" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("result_is_ok expects 1 argument (result), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "result_is_err" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("result_is_err expects 1 argument (result), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "result_unwrap" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("result_unwrap expects 1 argument (result), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "result_unwrap_err" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("result_unwrap_err expects 1 argument (result), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "result_tag" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("result_tag expects 1 argument (result), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "result_value" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("result_value expects 1 argument (result), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    // HashMap operation builtins
                    if name == "hashmap_new" {
                        if !args.is_empty() {
                            self.errors.push(TypeError {
                                message: format!("hashmap_new expects 0 arguments, got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64); // HashMap is represented as i64 pointer
                    }

                    if name == "hashmap_insert" {
                        if args.len() != 3 {
                            self.errors.push(TypeError {
                                message: format!("hashmap_insert expects 3 arguments (map, key, value), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "hashmap_get" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("hashmap_get expects 2 arguments (map, key), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "hashmap_contains" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("hashmap_contains expects 2 arguments (map, key), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "hashmap_remove" {
                        if args.len() != 2 {
                            self.errors.push(TypeError {
                                message: format!("hashmap_remove expects 2 arguments (map, key), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::Bool);
                    }

                    if name == "hashmap_len" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("hashmap_len expects 1 argument (map), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64);
                    }

                    if name == "hashmap_clear" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("hashmap_clear expects 1 argument (map), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I32); // void-like return
                    }

                    if name == "hashmap_keys" {
                        if args.len() != 1 {
                            self.errors.push(TypeError {
                                message: format!("hashmap_keys expects 1 argument (map), got {}", args.len()),
                                location: context.to_string(),
                            });
                        }
                        return Ok(Type::I64); // Returns Vec ptr
                    }

                    if let Some((param_types, ret_ty)) = self.functions.get(name).cloned() {
                        // Check argument count
                        if args.len() != param_types.len() {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Function {} expects {} arguments, got {}",
                                    name, param_types.len(), args.len()
                                ),
                                location: context.to_string(),
                            });
                        }
                        // Check argument types
                        for (i, (arg, expected)) in args.iter().zip(param_types.iter()).enumerate() {
                            let actual = self.infer_expr(arg, context)?;
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
                let expr_ty = self.infer_expr(expr, context)?;
                // Auto-dereference references
                let base_ty = match &expr_ty {
                    Type::Ref { ty, .. } => ty.as_ref().clone(),
                    other => other.clone(),
                };
                match &base_ty {
                    Type::Named(struct_name) => {
                        if let Some(fields) = self.structs.get(struct_name) {
                            if let Some((_, field_ty)) = fields.iter().find(|(n, _)| n == field) {
                                Ok(field_ty.clone())
                            } else {
                                self.errors.push(TypeError {
                                    message: format!("No field '{}' on struct {}", field, struct_name),
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
            Expr::If { condition, then_expr, else_expr } => {
                let cond_ty = self.infer_expr(condition, context)?;
                if cond_ty != Type::Bool {
                    self.errors.push(TypeError {
                        message: format!("Condition must be bool, got {:?}", cond_ty),
                        location: context.to_string(),
                    });
                }
                let then_ty = self.infer_expr(then_expr, context)?;
                let else_ty = self.infer_expr(else_expr, context)?;
                if !self.types_compatible(&then_ty, &else_ty) {
                    self.errors.push(TypeError {
                        message: format!(
                            "If branches have different types: {:?} vs {:?}",
                            then_ty, else_ty
                        ),
                        location: context.to_string(),
                    });
                }
                Ok(then_ty)
            }
            Expr::Array(elements) => {
                if elements.is_empty() {
                    Ok(Type::Array(Box::new(Type::I32), 0))
                } else {
                    let elem_ty = self.infer_expr(&elements[0], context)?;
                    for (i, elem) in elements.iter().skip(1).enumerate() {
                        let ty = self.infer_expr(elem, context)?;
                        if !self.types_compatible(&elem_ty, &ty) {
                            self.errors.push(TypeError {
                                message: format!(
                                    "Array element {} has type {:?}, expected {:?}",
                                    i + 1, ty, elem_ty
                                ),
                                location: context.to_string(),
                            });
                        }
                    }
                    Ok(Type::Array(Box::new(elem_ty), elements.len()))
                }
            }
            Expr::Struct { name, fields } => {
                if let Some(struct_fields) = self.structs.get(name).cloned() {
                    for (field_name, field_expr) in fields {
                        let actual_ty = self.infer_expr(field_expr, context)?;
                        if let Some((_, expected_ty)) = struct_fields.iter().find(|(n, _)| n == field_name) {
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
                                message: format!("Unknown field '{}' in struct {}", field_name, name),
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
            Expr::Copy(inner) => self.infer_expr(inner, context),
            Expr::Some(inner) => {
                let inner_ty = self.infer_expr(inner, context)?;
                Ok(Type::Option(Box::new(inner_ty)))
            }
            Expr::None => {
                // None without context - will be inferred from declared type
                Ok(Type::Option(Box::new(Type::I32)))
            }
            Expr::Match { expr, arms } => {
                let expr_ty = self.infer_expr(expr, context)?;

                // Check pattern types against expression type
                for arm in arms {
                    self.check_pattern_type(&arm.pattern, &expr_ty, context);
                }

                // Infer result type from first arm
                if let Some(first_arm) = arms.first() {
                    match &first_arm.body {
                        ast::MatchBody::Expr(e) => {
                            let saved = self.variables.clone();
                            let saved_moved = self.moved_vars.clone();
                            // Bind pattern variable
                            match &first_arm.pattern {
                                ast::Pattern::Ident(name) if name != "_" => {
                                    self.variables.insert(name.clone(), expr_ty.clone());
                                }
                                ast::Pattern::Some(name) if name != "_" => {
                                    if let Type::Option(inner) = &expr_ty {
                                        self.variables.insert(name.clone(), inner.as_ref().clone());
                                    }
                                }
                                _ => {}
                            }
                            let result = self.infer_expr(e, context)?;
                            self.variables = saved;
                            self.moved_vars = saved_moved;
                            Ok(result)
                        }
                        ast::MatchBody::Block(block) => {
                            // Block must end with an expression to produce a value
                            let has_value = block.statements.last().map_or(false, |s| matches!(s, Stmt::Expr(_)));
                            if !has_value {
                                self.errors.push(TypeError {
                                    message: "Match arm block must end with an expression to produce a value".to_string(),
                                    location: context.to_string(),
                                });
                            }
                            self.check_block(block, context)?;
                            Ok(Type::I32)
                        }
                    }
                } else {
                    Ok(Type::I32)
                }
            }
            Expr::Block(block) => {
                // Block expression - check all statements and return type of last expression
                let saved = self.variables.clone();
                let saved_moved = self.moved_vars.clone();
                let mut result_ty = Type::I32;
                for stmt in &block.statements {
                    match stmt {
                        Stmt::Let { name, ty, value } => {
                            let inferred = self.infer_expr(value, context)?;
                            if let Some(declared) = ty {
                                self.variables.insert(name.clone(), declared.clone());
                            } else {
                                self.variables.insert(name.clone(), inferred);
                            }
                        }
                        Stmt::Expr(e) => {
                            result_ty = self.infer_expr(e, context)?;
                        }
                        _ => {
                            self.check_stmt(stmt, context)?;
                        }
                    }
                }
                self.variables = saved;
                self.moved_vars = saved_moved;
                Ok(result_ty)
            }
            Expr::Range { start, .. } => {
                // Range type is based on start type
                self.infer_expr(start, context)
            }
            _ => Ok(Type::I32) // fallback for unhandled expressions
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

    fn binary_result_type(&mut self, op: BinaryOp, left: &Type, right: &Type, context: &str) -> Result<Type> {
        match op {
            BinaryOp::Add => {
                // String concatenation
                if *left == Type::Str && *right == Type::Str {
                    return Ok(Type::Str);
                }
                if !self.is_numeric(left) || !self.is_numeric(right) {
                    self.errors.push(TypeError {
                        message: format!("Arithmetic on non-numeric types: {:?} and {:?}", left, right),
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
                        message: format!("Arithmetic on non-numeric types: {:?} and {:?}", left, right),
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
            BinaryOp::Eq | BinaryOp::Ne | BinaryOp::Lt | BinaryOp::Le | BinaryOp::Gt | BinaryOp::Ge => {
                if !self.types_compatible(left, right) {
                    self.errors.push(TypeError {
                        message: format!("Comparison of incompatible types: {:?} and {:?}", left, right),
                        location: context.to_string(),
                    });
                }
                Ok(Type::Bool)
            }
            BinaryOp::And | BinaryOp::Or => {
                if *left != Type::Bool || *right != Type::Bool {
                    self.errors.push(TypeError {
                        message: format!("Logical operators require bool: {:?} and {:?}", left, right),
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
            BinaryOp::BitAnd | BinaryOp::BitOr | BinaryOp::BitXor | BinaryOp::Shl | BinaryOp::Shr => {
                // Bitwise operators require integers
                if !self.is_integer(left) || !self.is_integer(right) {
                    self.errors.push(TypeError {
                        message: format!("Bitwise operators require integers: {:?} and {:?}", left, right),
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

    fn is_numeric(&self, ty: &Type) -> bool {
        matches!(ty, Type::I32 | Type::I64 | Type::F32 | Type::F64)
    }

    /// Check if a type is implicitly copyable (primitives).
    /// Non-copy types (structs, arrays, strings) require explicit `copy` to avoid moving.
    fn is_copy_type(&self, ty: &Type) -> bool {
        matches!(ty, Type::I32 | Type::I64 | Type::F32 | Type::F64 | Type::Bool)
    }

    fn is_integer(&self, ty: &Type) -> bool {
        matches!(ty, Type::I32 | Type::I64)
    }

    fn check_pattern_type(&mut self, pattern: &ast::Pattern, expr_ty: &Type, context: &str) {
        match pattern {
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
            ast::Pattern::Some(_) => {
                if !matches!(expr_ty, Type::Option(_)) {
                    self.errors.push(TypeError {
                        message: format!(
                            "Some pattern cannot match non-Option type {:?}",
                            expr_ty
                        ),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::None => {
                if !matches!(expr_ty, Type::Option(_)) {
                    self.errors.push(TypeError {
                        message: format!(
                            "None pattern cannot match non-Option type {:?}",
                            expr_ty
                        ),
                        location: context.to_string(),
                    });
                }
            }
            ast::Pattern::Ident(_) => {
                // Identifier patterns (including wildcard "_") match any type
            }
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
        }
    }

    fn types_compatible(&self, expected: &Type, actual: &Type) -> bool {
        if expected == actual {
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
        false
    }
}

pub fn check_file(file: &ast::File) -> Result<Vec<TypeError>> {
    let mut all_errors = Vec::new();

    for kernel in &file.kernels {
        let mut checker = TypeChecker::new();
        let errors = checker.check_kernel(kernel)?;
        all_errors.extend(errors);
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

/// Message signature: (message_name, parameters)
type MessageSignature = (String, Vec<(String, ast::Type)>);

/// Collect all message signatures from a shell
fn collect_message_signatures(shell: &ast::Shell) -> HashMap<String, HashMap<String, Vec<(String, ast::Type)>>> {
    let mut agent_messages: HashMap<String, HashMap<String, Vec<(String, ast::Type)>>> = HashMap::new();

    for agent in &shell.agents {
        let mut messages: HashMap<String, Vec<(String, ast::Type)>> = HashMap::new();
        for handler in &agent.handlers {
            let params: Vec<(String, ast::Type)> = handler.params
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
fn collect_agent_state(shell: &ast::Shell) -> HashMap<String, HashMap<String, ast::Type>> {
    let mut agent_state: HashMap<String, HashMap<String, ast::Type>> = HashMap::new();

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
    agent_messages: &HashMap<String, HashMap<String, Vec<(String, ast::Type)>>>,
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
    agent_messages: &HashMap<String, HashMap<String, Vec<(String, ast::Type)>>>,
    shell_name: &str,
    errors: &mut Vec<TypeError>,
) {
    match stmt {
        ast::Stmt::Send { message, target, args } => {
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
                                msg_name, target, expected_params.len(), args.len()
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
                        message: format!("Agent {} has no handler for message '{}'", target, msg_name),
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
        ast::Stmt::If { then_block, else_block, .. } => {
            check_shell_block(then_block, agent_messages, shell_name, errors);
            if let Some(eb) = else_block {
                check_shell_block(eb, agent_messages, shell_name, errors);
            }
        }
        ast::Stmt::For { body, .. } | ast::Stmt::While { body, .. } | ast::Stmt::Loop(body) => {
            check_shell_block(body, agent_messages, shell_name, errors);
        }
        ast::Stmt::Match { arms, .. } => {
            for arm in arms {
                match &arm.body {
                    ast::MatchBody::Block(b) => check_shell_block(b, agent_messages, shell_name, errors),
                    _ => {}
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
    let is_numeric = |t: &ast::Type| matches!(t, ast::Type::I32 | ast::Type::I64 | ast::Type::F32 | ast::Type::F64);
    if is_numeric(expected) && is_numeric(actual) {
        return true;
    }
    false
}

/// Check a view for type errors
fn check_view(view: &ast::View, file: &ast::File) -> Result<Vec<TypeError>> {
    let mut errors = Vec::new();

    // Collect all shell information
    let mut all_agent_messages: HashMap<String, HashMap<String, HashMap<String, Vec<(String, ast::Type)>>>> = HashMap::new();
    let mut all_agent_state: HashMap<String, HashMap<String, HashMap<String, ast::Type>>> = HashMap::new();

    for shell in &file.shells {
        all_agent_messages.insert(shell.name.clone(), collect_message_signatures(shell));
        all_agent_state.insert(shell.name.clone(), collect_agent_state(shell));
    }

    // Check each component
    for component in &view.components {
        check_view_component(component, &all_agent_messages, &all_agent_state, &view.name, &mut errors);
    }

    Ok(errors)
}

/// Check a view component for type errors
fn check_view_component(
    component: &ast::Component,
    all_agent_messages: &HashMap<String, HashMap<String, HashMap<String, Vec<(String, ast::Type)>>>>,
    all_agent_state: &HashMap<String, HashMap<String, HashMap<String, ast::Type>>>,
    view_name: &str,
    errors: &mut Vec<TypeError>,
) {
    // Check properties
    for prop in &component.properties {
        check_view_expr(&prop.value, all_agent_messages, all_agent_state, view_name, errors);
    }

    // Check children recursively
    for child in &component.children {
        check_view_component(child, all_agent_messages, all_agent_state, view_name, errors);
    }
}

/// Check a view expression for type errors
fn check_view_expr(
    expr: &ast::Expr,
    all_agent_messages: &HashMap<String, HashMap<String, HashMap<String, Vec<(String, ast::Type)>>>>,
    all_agent_state: &HashMap<String, HashMap<String, HashMap<String, ast::Type>>>,
    view_name: &str,
    errors: &mut Vec<TypeError>,
) {
    match expr {
        ast::Expr::Send { message, target, args } => {
            // Validate send expression against shell message signatures
            // target is Vec<String> like ["App", "Worker"]
            if target.len() >= 2 {
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
                                        msg_name, shell_name, agent_name, expected_params.len(), args.len()
                                    ),
                                    location: view_name.to_string(),
                                });
                            }

                            // Check argument types
                            for (expected_name, expected_ty) in expected_params {
                                if let Some((_, arg_expr)) = args.iter().find(|(n, _)| n == expected_name) {
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
        }
        ast::Expr::Field { expr: inner, field } => {
            // Check for Shell.Agent.field bindings
            if let ast::Expr::Field { expr: inner2, field: agent_name } = inner.as_ref() {
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
            check_view_expr(inner, all_agent_messages, all_agent_state, view_name, errors);
        }
        ast::Expr::Binary { left, right, .. } => {
            check_view_expr(left, all_agent_messages, all_agent_state, view_name, errors);
            check_view_expr(right, all_agent_messages, all_agent_state, view_name, errors);
        }
        ast::Expr::Unary { expr: inner, .. } => {
            check_view_expr(inner, all_agent_messages, all_agent_state, view_name, errors);
        }
        ast::Expr::Call { args, .. } => {
            for arg in args {
                check_view_expr(arg, all_agent_messages, all_agent_state, view_name, errors);
            }
        }
        _ => {}
    }
}
