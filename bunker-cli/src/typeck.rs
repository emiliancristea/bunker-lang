use std::collections::HashMap;
use anyhow::{anyhow, Result};
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
}

impl TypeChecker {
    pub fn new() -> Self {
        let mut tc = Self {
            variables: HashMap::new(),
            functions: HashMap::new(),
            structs: HashMap::new(),
            errors: Vec::new(),
            current_return_type: None,
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

        // Save current variable scope
        let saved_vars = self.variables.clone();

        // Add parameters to scope
        for param in &func.params {
            self.variables.insert(param.name.clone(), param.ty.clone());
        }

        // Check function body
        self.check_block(&func.body, &func.name)?;

        // Restore scope
        self.variables = saved_vars;
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
                let inferred = self.infer_expr(value, context)?;
                
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
                let iter_ty = self.infer_expr(iter, context)?;
                // For arrays, the element type goes to the loop variable
                let elem_ty = match &iter_ty {
                    Type::Array(elem, _) => (**elem).clone(),
                    _ => {
                        self.errors.push(TypeError {
                            message: format!("Cannot iterate over {:?}", iter_ty),
                            location: context.to_string(),
                        });
                        Type::I32 // fallback
                    }
                };
                
                let saved = self.variables.clone();
                self.variables.insert(var.clone(), elem_ty);
                self.check_block(body, context)?;
                self.variables = saved;
                Ok(None)
            }
            Stmt::Loop(body) => {
                self.check_block(body, context)?;
                Ok(None)
            }
            Stmt::Defer(inner) => {
                self.check_stmt(inner, context)?;
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

    fn binary_result_type(&mut self, op: BinaryOp, left: &Type, right: &Type, context: &str) -> Result<Type> {
        match op {
            BinaryOp::Add | BinaryOp::Sub | BinaryOp::Mul | BinaryOp::Div | BinaryOp::Mod => {
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
    
    Ok(all_errors)
}
