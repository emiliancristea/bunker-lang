use std::collections::{HashMap, HashSet};

use crate::ast::{
    self, Block, Expr, Function, KernelItem, Literal, MatchBody, Stmt, StructDef, Type,
};
use crate::diagnostic::{codes, Diagnostic, SourceLocation};

/// An instantiation request for a generic struct or function.
#[derive(Clone, Debug, PartialEq)]
pub enum Request {
    Struct(String, Vec<Type>),
    Function(String, Vec<Type>),
}

/// Produce a mangled suffix for a concrete type for monomorphization.
pub fn type_mangle_suffix(ty: &Type) -> String {
    match ty {
        Type::I32 => "i32".to_string(),
        Type::I64 => "i64".to_string(),
        Type::F32 => "f32".to_string(),
        Type::F64 => "f64".to_string(),
        Type::Bool => "bool".to_string(),
        Type::Str => "str".to_string(),
        Type::Unit => "unit".to_string(),
        Type::Never => "never".to_string(),
        Type::Vec2 => "vec2".to_string(),
        Type::Vec3 => "vec3".to_string(),
        Type::Option(inner) => format!("opt_{}", type_mangle_suffix(inner)),
        Type::Result(ok, err) => {
            format!("res_{}_{}", type_mangle_suffix(ok), type_mangle_suffix(err))
        }
        Type::Vec(elem) => format!("vec_{}", type_mangle_suffix(elem)),
        Type::HashMap(k, v) => {
            format!("map_{}_{}", type_mangle_suffix(k), type_mangle_suffix(v))
        }
        Type::Slice(elem) => format!("slice_{}", type_mangle_suffix(elem)),
        Type::Array(elem, len) => format!("arr_{}_{}", type_mangle_suffix(elem), len),
        Type::Tuple(elems) => {
            let s: Vec<_> = elems.iter().map(type_mangle_suffix).collect();
            format!("tup_{}", s.join("_"))
        }
        Type::Generic(name, args) => {
            let s: Vec<_> = args.iter().map(type_mangle_suffix).collect();
            format!("{}__{}", name.replace("::", "__"), s.join("_"))
        }
        Type::Named(name) => name.replace("::", "__"),
        Type::Ref { mutable, ty } => {
            if *mutable {
                format!("ref_mut_{}", type_mangle_suffix(ty))
            } else {
                format!("ref_{}", type_mangle_suffix(ty))
            }
        }
        Type::Fn(params, ret) => {
            let s: Vec<_> = params.iter().map(type_mangle_suffix).collect();
            format!("fn_{}_ret_{}", s.join("_"), type_mangle_suffix(ret))
        }
    }
}

/// Produce a mangled identifier for a generic base symbol and concrete type arguments.
pub fn mangle_name(base: &str, type_args: &[Type]) -> String {
    if type_args.is_empty() {
        return base.to_string();
    }
    let s: Vec<_> = type_args.iter().map(type_mangle_suffix).collect();
    if base.contains("::") {
        let parts: Vec<&str> = base.split("::").collect();
        format!("{}__{}::{}", parts[0], s.join("_"), parts[1..].join("::"))
    } else {
        format!("{}__{}", base, s.join("_"))
    }
}

/// Recursively substitute type parameters in `ty` according to `mapping`.
pub fn substitute_type(ty: &Type, mapping: &HashMap<String, Type>) -> Type {
    match ty {
        Type::Named(name) => {
            if let Some(sub) = mapping.get(name) {
                sub.clone()
            } else {
                ty.clone()
            }
        }
        Type::Generic(name, args) => {
            let new_args: Vec<_> = args.iter().map(|a| substitute_type(a, mapping)).collect();
            Type::Generic(name.clone(), new_args)
        }
        Type::Option(inner) => Type::Option(Box::new(substitute_type(inner, mapping))),
        Type::Result(ok, err) => Type::Result(
            Box::new(substitute_type(ok, mapping)),
            Box::new(substitute_type(err, mapping)),
        ),
        Type::Vec(elem) => Type::Vec(Box::new(substitute_type(elem, mapping))),
        Type::HashMap(k, v) => Type::HashMap(
            Box::new(substitute_type(k, mapping)),
            Box::new(substitute_type(v, mapping)),
        ),
        Type::Slice(elem) => Type::Slice(Box::new(substitute_type(elem, mapping))),
        Type::Array(elem, len) => Type::Array(Box::new(substitute_type(elem, mapping)), *len),
        Type::Tuple(elems) => {
            Type::Tuple(elems.iter().map(|e| substitute_type(e, mapping)).collect())
        }
        Type::Fn(params, ret) => Type::Fn(
            params.iter().map(|p| substitute_type(p, mapping)).collect(),
            Box::new(substitute_type(ret, mapping)),
        ),
        Type::Ref { mutable, ty } => Type::Ref {
            mutable: *mutable,
            ty: Box::new(substitute_type(ty, mapping)),
        },
        _ => ty.clone(),
    }
}

/// Unify a declared parameter pattern type against a concrete actual type to deduce type parameters.
pub fn unify_type_param(
    param_pattern: &Type,
    actual_ty: &Type,
    type_params: &[String],
    mapping: &mut HashMap<String, Type>,
) -> Result<(), String> {
    match (param_pattern, actual_ty) {
        (Type::Named(name), concrete) if type_params.contains(name) => {
            if let Some(existing) = mapping.get(name) {
                if existing != concrete {
                    return Err(format!(
                        "Inferred conflicting types for type parameter '{}': expected {}, found {}",
                        name, existing, concrete
                    ));
                }
            } else {
                mapping.insert(name.clone(), concrete.clone());
            }
        }
        (Type::Generic(n1, args1), Type::Generic(n2, args2))
            if n1 == n2 && args1.len() == args2.len() =>
        {
            for (a1, a2) in args1.iter().zip(args2.iter()) {
                unify_type_param(a1, a2, type_params, mapping)?;
            }
        }
        (Type::Option(e1), Type::Option(e2)) => unify_type_param(e1, e2, type_params, mapping)?,
        (Type::Result(o1, er1), Type::Result(o2, er2)) => {
            unify_type_param(o1, o2, type_params, mapping)?;
            unify_type_param(er1, er2, type_params, mapping)?;
        }
        (Type::Vec(e1), Type::Vec(e2)) => unify_type_param(e1, e2, type_params, mapping)?,
        (Type::Slice(e1), Type::Slice(e2)) => unify_type_param(e1, e2, type_params, mapping)?,
        (Type::Array(e1, _), Type::Array(e2, _)) => unify_type_param(e1, e2, type_params, mapping)?,
        (Type::Tuple(t1), Type::Tuple(t2)) if t1.len() == t2.len() => {
            for (a1, a2) in t1.iter().zip(t2.iter()) {
                unify_type_param(a1, a2, type_params, mapping)?;
            }
        }
        _ => {}
    }
    Ok(())
}

/// Lightweight expression type inference for deduction of type arguments.
pub fn infer_expr_type(
    expr: &Expr,
    env: &HashMap<String, Type>,
    structs: &HashMap<String, StructDef>,
    fns: &HashMap<String, Function>,
) -> Type {
    match expr {
        Expr::Literal(Literal::Int(_)) => Type::I32,
        Expr::Literal(Literal::Float(_)) => Type::F64,
        Expr::Literal(Literal::Bool(_)) => Type::Bool,
        Expr::Literal(Literal::String(_)) => Type::Str,
        Expr::Literal(Literal::Char(_)) => Type::I32,
        Expr::Literal(Literal::HexColor(_)) => Type::I32,
        Expr::Ident(name) => env.get(name).cloned().unwrap_or(Type::I32),
        Expr::Cast { target_type, .. } => target_type.clone(),
        Expr::Tuple(elems) => {
            let elem_types = elems
                .iter()
                .map(|e| infer_expr_type(e, env, structs, fns))
                .collect();
            Type::Tuple(elem_types)
        }
        Expr::Array(elems) => {
            if let Some(first) = elems.first() {
                Type::Array(
                    Box::new(infer_expr_type(first, env, structs, fns)),
                    elems.len(),
                )
            } else {
                Type::Array(Box::new(Type::I32), 0)
            }
        }
        Expr::Struct {
            name,
            type_args,
            fields,
            ..
        } => {
            if let Some(s) = structs.get(name) {
                if !s.type_params.is_empty() {
                    if !type_args.is_empty() {
                        return Type::Generic(name.clone(), type_args.clone());
                    }
                    // Try to deduce type_args from fields
                    let mut mapping = HashMap::new();
                    for (fname, fval) in fields {
                        let actual_val_ty = infer_expr_type(fval, env, structs, fns);
                        if let Some(sf) = s.fields.iter().find(|f| f.name == *fname) {
                            let _ = unify_type_param(
                                &sf.ty,
                                &actual_val_ty,
                                &s.type_params,
                                &mut mapping,
                            );
                        }
                    }
                    let deduced: Vec<Type> = s
                        .type_params
                        .iter()
                        .map(|p| mapping.get(p).cloned().unwrap_or(Type::I32))
                        .collect();
                    return Type::Generic(name.clone(), deduced);
                }
            }
            Type::Named(name.clone())
        }
        Expr::Call {
            func,
            type_args,
            args,
        } => {
            if let Expr::Ident(name) = func.as_ref() {
                // Check if it's a tuple struct constructor
                if let Some(s) = structs.get(name) {
                    if s.is_tuple && !s.type_params.is_empty() {
                        if !type_args.is_empty() {
                            return Type::Generic(name.clone(), type_args.clone());
                        }
                        let mut mapping = HashMap::new();
                        for (i, arg) in args.iter().enumerate() {
                            let actual_ty = infer_expr_type(arg, env, structs, fns);
                            if let Some(sf) = s.fields.get(i) {
                                let _ = unify_type_param(
                                    &sf.ty,
                                    &actual_ty,
                                    &s.type_params,
                                    &mut mapping,
                                );
                            }
                        }
                        let deduced: Vec<Type> = s
                            .type_params
                            .iter()
                            .map(|p| mapping.get(p).cloned().unwrap_or(Type::I32))
                            .collect();
                        return Type::Generic(name.clone(), deduced);
                    }
                }
                if let Some(f) = fns.get(name) {
                    if let Some(ret) = &f.return_type {
                        if !f.type_params.is_empty() {
                            let mut mapping = HashMap::new();
                            if !type_args.is_empty() && type_args.len() == f.type_params.len() {
                                for (p, a) in f.type_params.iter().zip(type_args.iter()) {
                                    mapping.insert(p.clone(), a.clone());
                                }
                            } else {
                                for (p_decl, a_expr) in f.params.iter().zip(args.iter()) {
                                    let arg_ty = infer_expr_type(a_expr, env, structs, fns);
                                    let _ = unify_type_param(
                                        &p_decl.ty,
                                        &arg_ty,
                                        &f.type_params,
                                        &mut mapping,
                                    );
                                }
                            }
                            return substitute_type(ret, &mapping);
                        }
                        return ret.clone();
                    }
                }
            }
            Type::I32
        }
        Expr::Field { expr, field } => {
            let base_ty = infer_expr_type(expr, env, structs, fns);
            match &base_ty {
                Type::Tuple(elems) => {
                    if let Ok(idx) = field.parse::<usize>() {
                        if let Some(t) = elems.get(idx) {
                            return t.clone();
                        }
                    }
                }
                Type::Named(sname) => {
                    if let Some(s) = structs.get(sname) {
                        if let Some(f) = s.fields.iter().find(|f| f.name == *field) {
                            return f.ty.clone();
                        }
                    }
                }
                Type::Generic(sname, targs) => {
                    if let Some(s) = structs.get(sname) {
                        let mut mapping = HashMap::new();
                        for (p, a) in s.type_params.iter().zip(targs.iter()) {
                            mapping.insert(p.clone(), a.clone());
                        }
                        if let Some(f) = s.fields.iter().find(|f| f.name == *field) {
                            return substitute_type(&f.ty, &mapping);
                        }
                    }
                }
                _ => {}
            }
            Type::I32
        }
        Expr::Binary { left, .. } => infer_expr_type(left, env, structs, fns),
        Expr::Unary { expr, .. } => infer_expr_type(expr, env, structs, fns),
        Expr::Block(block) => {
            let mut local_env = env.clone();
            let mut last_ty = Type::Unit;
            for stmt in &block.statements {
                match stmt {
                    Stmt::Let {
                        name, ty, value, ..
                    } => {
                        let vty = ty
                            .clone()
                            .unwrap_or_else(|| infer_expr_type(value, &local_env, structs, fns));
                        local_env.insert(name.clone(), vty);
                    }
                    Stmt::Expr(e) => {
                        last_ty = infer_expr_type(e, &local_env, structs, fns);
                    }
                    Stmt::Return(Some(e)) => {
                        return infer_expr_type(e, &local_env, structs, fns);
                    }
                    _ => {}
                }
            }
            last_ty
        }
        _ => Type::I32,
    }
}

/// Monomorphizes all generic structs and functions in the given AST file.
pub fn monomorphize_file(file: &mut ast::File, file_path: &str) -> Result<(), Vec<Diagnostic>> {
    let mut diagnostics = Vec::new();

    // Check if any generic structs or functions exist in any kernel
    let mut has_generics = false;
    for kernel in &file.kernels {
        for item in &kernel.items {
            match item {
                KernelItem::Function(f) | KernelItem::ComptimeFn(f)
                    if !f.type_params.is_empty() =>
                {
                    has_generics = true;
                }
                KernelItem::Struct(s) if !s.type_params.is_empty() => {
                    has_generics = true;
                }
                _ => {}
            }
        }
    }

    if !has_generics {
        return Ok(());
    }

    // Process each kernel
    for kernel in &mut file.kernels {
        let mut generic_structs: HashMap<String, StructDef> = HashMap::new();
        let mut generic_functions: HashMap<String, Function> = HashMap::new();
        let mut all_structs: HashMap<String, StructDef> = HashMap::new();
        let mut all_functions: HashMap<String, Function> = HashMap::new();

        // 1. Index declarations and validate type parameters
        for item in &kernel.items {
            match item {
                KernelItem::Struct(s) => {
                    all_structs.insert(s.name.clone(), s.clone());
                    if !s.type_params.is_empty() {
                        let mut seen = HashSet::new();
                        for p in &s.type_params {
                            if !seen.insert(p.clone()) {
                                diagnostics.push(Diagnostic::error(
                                    codes::GENERIC_UNKNOWN_TYPE_PARAM,
                                    format!(
                                        "Duplicate type parameter '{}' in struct '{}'",
                                        p, s.name
                                    ),
                                    SourceLocation::with_context(
                                        file_path,
                                        format!("struct {}", s.name),
                                    ),
                                ));
                            }
                        }
                        generic_structs.insert(s.name.clone(), s.clone());
                    }
                }
                KernelItem::Function(f) | KernelItem::ComptimeFn(f) => {
                    all_functions.insert(f.name.clone(), f.clone());
                    if !f.type_params.is_empty() {
                        let mut seen = HashSet::new();
                        for p in &f.type_params {
                            if !seen.insert(p.clone()) {
                                diagnostics.push(Diagnostic::error(
                                    codes::GENERIC_UNKNOWN_TYPE_PARAM,
                                    format!(
                                        "Duplicate type parameter '{}' in function '{}'",
                                        p, f.name
                                    ),
                                    SourceLocation::with_context(
                                        file_path,
                                        format!("fn {}", f.name),
                                    ),
                                ));
                            }
                        }
                        // Validate that parameters and return types don't reference unknown type variables
                        for p_decl in &f.params {
                            validate_type_vars(
                                &p_decl.ty,
                                &f.type_params,
                                &all_structs,
                                file_path,
                                &format!("fn {}", f.name),
                                &mut diagnostics,
                            );
                        }
                        if let Some(ret) = &f.return_type {
                            validate_type_vars(
                                ret,
                                &f.type_params,
                                &all_structs,
                                file_path,
                                &format!("fn {}", f.name),
                                &mut diagnostics,
                            );
                        }
                        generic_functions.insert(f.name.clone(), f.clone());
                    }
                }
                _ => {}
            }
        }

        if !diagnostics.is_empty() {
            return Err(diagnostics);
        }

        // 2. Discover and instantiate generic items
        let mut specialized_structs: HashMap<String, StructDef> = HashMap::new();
        let mut specialized_functions: HashMap<String, Function> = HashMap::new();

        let mut worklist: Vec<Request> = Vec::new();
        let mut seen_requests: HashSet<String> = HashSet::new();

        // Collect initial requests from non-generic functions
        for item in &mut kernel.items {
            match item {
                KernelItem::Function(f) | KernelItem::ComptimeFn(f) if f.type_params.is_empty() => {
                    for p in &f.params {
                        collect_requests_in_type(&p.ty, &generic_structs, &mut worklist);
                    }
                    if let Some(ret) = &f.return_type {
                        collect_requests_in_type(ret, &generic_structs, &mut worklist);
                    }
                    let mut env = HashMap::new();
                    for p in &f.params {
                        env.insert(p.name.clone(), p.ty.clone());
                    }
                    collect_requests_in_block(
                        &mut f.body,
                        &mut env,
                        &generic_structs,
                        &generic_functions,
                        &all_structs,
                        &all_functions,
                        file_path,
                        &f.name,
                        &mut worklist,
                        &mut diagnostics,
                    );
                }
                KernelItem::TypeAlias(a) => {
                    if let Type::Generic(name, args) = &a.target {
                        if generic_structs.contains_key(name) {
                            worklist.push(Request::Struct(name.clone(), args.clone()));
                        }
                    }
                }
                _ => {}
            }
        }

        if !diagnostics.is_empty() {
            return Err(diagnostics);
        }

        // Iteratively process worklist
        let mut iteration_count = 0;
        while let Some(req) = worklist.pop() {
            let req_key = match &req {
                Request::Struct(n, a) => format!("struct:{}", mangle_name(n, a)),
                Request::Function(n, a) => format!("fn:{}", mangle_name(n, a)),
            };
            if !seen_requests.insert(req_key) {
                continue;
            }
            iteration_count += 1;
            if iteration_count > 256 {
                diagnostics.push(Diagnostic::error(
                    codes::GENERIC_RECURSION_LIMIT,
                    "Monomorphization recursion limit exceeded".to_string(),
                    SourceLocation::with_context(file_path, "monomorphize"),
                ));
                return Err(diagnostics);
            }

            match req {
                Request::Struct(base_name, type_args) => {
                    if let Some(generic_def) = generic_structs.get(&base_name) {
                        if type_args.len() != generic_def.type_params.len() {
                            diagnostics.push(Diagnostic::error(
                                codes::GENERIC_ARG_COUNT,
                                format!(
                                    "Wrong number of type arguments for struct '{}': expected {}, found {}",
                                    base_name, generic_def.type_params.len(), type_args.len()
                                ),
                                SourceLocation::with_context(file_path, format!("struct {}", base_name)),
                            ));
                            continue;
                        }

                        let mangled = mangle_name(&base_name, &type_args);
                        if specialized_structs.contains_key(&mangled) {
                            continue;
                        }

                        let mut mapping = HashMap::new();
                        for (p, a) in generic_def.type_params.iter().zip(type_args.iter()) {
                            mapping.insert(p.clone(), a.clone());
                        }

                        let mut new_fields = Vec::new();
                        for f in &generic_def.fields {
                            let mut sub_ty = substitute_type(&f.ty, &mapping);
                            collect_requests_in_type(&sub_ty, &generic_structs, &mut worklist);
                            rewrite_type(&mut sub_ty);
                            new_fields.push(ast::StructField {
                                name: f.name.clone(),
                                ty: sub_ty,
                            });
                        }

                        let specialized = StructDef {
                            name: mangled.clone(),
                            is_pub: generic_def.is_pub,
                            type_params: vec![],
                            attributes: generic_def.attributes.clone(),
                            doc: generic_def.doc.clone(),
                            fields: new_fields,
                            is_tuple: generic_def.is_tuple,
                        };

                        all_structs.insert(mangled.clone(), specialized.clone());
                        specialized_structs.insert(mangled, specialized);
                    }
                }
                Request::Function(base_name, type_args) => {
                    if let Some(generic_def) = generic_functions.get(&base_name) {
                        if type_args.len() != generic_def.type_params.len() {
                            diagnostics.push(Diagnostic::error(
                                codes::GENERIC_ARG_COUNT,
                                format!(
                                    "Wrong number of type arguments for function '{}': expected {}, found {}",
                                    base_name, generic_def.type_params.len(), type_args.len()
                                ),
                                SourceLocation::with_context(file_path, format!("fn {}", base_name)),
                            ));
                            continue;
                        }

                        let mangled = mangle_name(&base_name, &type_args);
                        if specialized_functions.contains_key(&mangled) {
                            continue;
                        }

                        let mut mapping = HashMap::new();
                        for (p, a) in generic_def.type_params.iter().zip(type_args.iter()) {
                            mapping.insert(p.clone(), a.clone());
                        }

                        let mut new_params = Vec::new();
                        for p in &generic_def.params {
                            let mut sub_ty = substitute_type(&p.ty, &mapping);
                            collect_requests_in_type(&sub_ty, &generic_structs, &mut worklist);
                            rewrite_type(&mut sub_ty);
                            new_params.push(ast::Param {
                                name: p.name.clone(),
                                ty: sub_ty,
                            });
                        }

                        let new_ret = generic_def.return_type.as_ref().map(|r| {
                            let mut sub_ret = substitute_type(r, &mapping);
                            collect_requests_in_type(&sub_ret, &generic_structs, &mut worklist);
                            rewrite_type(&mut sub_ret);
                            sub_ret
                        });

                        let mut new_body = generic_def.body.clone();
                        // Substitute types in function body
                        substitute_body_types(&mut new_body, &mapping);

                        let mut env = HashMap::new();
                        for p in &new_params {
                            env.insert(p.name.clone(), p.ty.clone());
                        }

                        collect_requests_in_block(
                            &mut new_body,
                            &mut env,
                            &generic_structs,
                            &generic_functions,
                            &all_structs,
                            &all_functions,
                            file_path,
                            &mangled,
                            &mut worklist,
                            &mut diagnostics,
                        );

                        let specialized = Function {
                            name: mangled.clone(),
                            is_pub: generic_def.is_pub,
                            type_params: vec![],
                            attributes: generic_def.attributes.clone(),
                            doc: generic_def.doc.clone(),
                            params: new_params,
                            return_type: new_ret,
                            body: new_body,
                        };

                        all_functions.insert(mangled.clone(), specialized.clone());
                        specialized_functions.insert(mangled, specialized);
                    }
                }
            }
        }

        if !diagnostics.is_empty() {
            return Err(diagnostics);
        }

        // 3. Rewrite all expressions and types across all functions and types in the kernel
        for item in &mut kernel.items {
            match item {
                KernelItem::Function(f) | KernelItem::ComptimeFn(f) if f.type_params.is_empty() => {
                    rewrite_block(&mut f.body, &generic_structs, &generic_functions);
                    rewrite_type_in_params(&mut f.params);
                    if let Some(ret) = &mut f.return_type {
                        rewrite_type(ret);
                    }
                    if f.name.contains("::") {
                        let parts: Vec<&str> = f.name.split("::").collect();
                        if let Some(first_param) = f.params.first() {
                            let actual_ty = match &first_param.ty {
                                Type::Ref { ty: inner, .. } => inner.as_ref(),
                                other => other,
                            };
                            if let Type::Named(sname) = actual_ty {
                                if (sname.starts_with(&format!("{}_", parts[0]))
                                    || sname.starts_with(&format!("{}__", parts[0])))
                                    && sname != parts[0]
                                {
                                    f.name = format!("{}::{}", sname, parts[1..].join("::"));
                                }
                            }
                        }
                    }
                }
                KernelItem::Struct(s) if s.type_params.is_empty() => {
                    for f in &mut s.fields {
                        rewrite_type(&mut f.ty);
                    }
                }
                KernelItem::TypeAlias(a) => {
                    rewrite_type(&mut a.target);
                }
                _ => {}
            }
        }

        for specialized in specialized_functions.values_mut() {
            rewrite_block(&mut specialized.body, &generic_structs, &generic_functions);
            rewrite_type_in_params(&mut specialized.params);
            if let Some(ret) = &mut specialized.return_type {
                rewrite_type(ret);
            }
        }

        // 4. Remove original generic templates and append all specialized items
        kernel.items.retain(|item| match item {
            KernelItem::Struct(s) => s.type_params.is_empty(),
            KernelItem::Function(f) | KernelItem::ComptimeFn(f) => f.type_params.is_empty(),
            _ => true,
        });

        // Add specialized structs in sorted order for determinism
        let mut sorted_structs: Vec<_> = specialized_structs.into_values().collect();
        sorted_structs.sort_by(|a, b| a.name.cmp(&b.name));
        for s in sorted_structs {
            kernel.items.push(KernelItem::Struct(s));
        }

        // Add specialized functions in sorted order for determinism
        let mut sorted_functions: Vec<_> = specialized_functions.into_values().collect();
        sorted_functions.sort_by(|a, b| a.name.cmp(&b.name));
        for f in sorted_functions {
            kernel.items.push(KernelItem::Function(f));
        }
    }

    Ok(())
}

fn validate_type_vars(
    ty: &Type,
    allowed: &[String],
    structs: &HashMap<String, StructDef>,
    file_path: &str,
    context: &str,
    diagnostics: &mut Vec<Diagnostic>,
) {
    match ty {
        Type::Named(name) => {
            if !allowed.contains(name)
                && !structs.contains_key(name)
                && !is_builtin_or_primitive(name)
            {
                // If it looks like a single uppercase letter or type parameter (e.g. T, U, V, Item), emit unknown type param
                if name.len() == 1
                    || (name.chars().next().map_or(false, |c| c.is_uppercase())
                        && !structs.contains_key(name))
                {
                    diagnostics.push(Diagnostic::error(
                        codes::GENERIC_UNKNOWN_TYPE_PARAM,
                        format!("Unknown type parameter '{}' in {}", name, context),
                        SourceLocation::with_context(file_path, context),
                    ));
                }
            }
        }
        Type::Generic(name, args) => {
            if !allowed.contains(name)
                && !structs.contains_key(name)
                && !is_builtin_or_primitive(name)
            {
                diagnostics.push(Diagnostic::error(
                    codes::GENERIC_UNKNOWN_TYPE_PARAM,
                    format!("Unknown generic type '{}' in {}", name, context),
                    SourceLocation::with_context(file_path, context),
                ));
            }
            for a in args {
                validate_type_vars(a, allowed, structs, file_path, context, diagnostics);
            }
        }
        Type::Option(inner) | Type::Vec(inner) | Type::Slice(inner) | Type::Array(inner, _) => {
            validate_type_vars(inner, allowed, structs, file_path, context, diagnostics);
        }
        Type::Result(ok, err) | Type::HashMap(ok, err) => {
            validate_type_vars(ok, allowed, structs, file_path, context, diagnostics);
            validate_type_vars(err, allowed, structs, file_path, context, diagnostics);
        }
        Type::Tuple(elems) => {
            for e in elems {
                validate_type_vars(e, allowed, structs, file_path, context, diagnostics);
            }
        }
        Type::Fn(params, ret) => {
            for p in params {
                validate_type_vars(p, allowed, structs, file_path, context, diagnostics);
            }
            validate_type_vars(ret, allowed, structs, file_path, context, diagnostics);
        }
        _ => {}
    }
}

fn is_builtin_or_primitive(name: &str) -> bool {
    matches!(
        name,
        "i32"
            | "i64"
            | "f32"
            | "f64"
            | "bool"
            | "str"
            | "vec2"
            | "vec3"
            | "unit"
            | "never"
            | "Path"
    )
}

fn substitute_body_types(block: &mut Block, mapping: &HashMap<String, Type>) {
    for stmt in &mut block.statements {
        match stmt {
            Stmt::Let { ty, value, .. } => {
                if let Some(t) = ty {
                    *t = substitute_type(t, mapping);
                }
                substitute_expr_types(value, mapping);
            }
            Stmt::Expr(e) | Stmt::Return(Some(e)) => {
                substitute_expr_types(e, mapping);
            }
            Stmt::If {
                condition,
                then_block,
                else_block,
            } => {
                substitute_expr_types(condition, mapping);
                substitute_body_types(then_block, mapping);
                if let Some(eb) = else_block {
                    substitute_body_types(eb, mapping);
                }
            }
            Stmt::While {
                condition, body, ..
            } => {
                substitute_expr_types(condition, mapping);
                substitute_body_types(body, mapping);
            }
            Stmt::For { iter, body, .. } => {
                substitute_expr_types(iter, mapping);
                substitute_body_types(body, mapping);
            }
            Stmt::Loop { body, .. } => {
                substitute_body_types(body, mapping);
            }
            Stmt::Match { expr, arms } => {
                substitute_expr_types(expr, mapping);
                for arm in arms {
                    if let Some(g) = &mut arm.guard {
                        substitute_expr_types(g, mapping);
                    }
                    match &mut arm.body {
                        MatchBody::Expr(e) => substitute_expr_types(e, mapping),
                        MatchBody::Block(b) => substitute_body_types(b, mapping),
                    }
                }
            }
            Stmt::Defer(b) => {
                substitute_body_types(b, mapping);
            }
            _ => {}
        }
    }
}

fn substitute_expr_types(expr: &mut Expr, mapping: &HashMap<String, Type>) {
    match expr {
        Expr::Cast {
            target_type,
            expr: inner,
        } => {
            *target_type = substitute_type(target_type, mapping);
            substitute_expr_types(inner, mapping);
        }
        Expr::Binary { left, right, .. } => {
            substitute_expr_types(left, mapping);
            substitute_expr_types(right, mapping);
        }
        Expr::Unary { expr: inner, .. } => substitute_expr_types(inner, mapping),
        Expr::Call {
            func,
            type_args,
            args,
        } => {
            substitute_expr_types(func, mapping);
            for ta in type_args {
                *ta = substitute_type(ta, mapping);
            }
            for a in args {
                substitute_expr_types(a, mapping);
            }
        }
        Expr::Struct {
            type_args,
            fields,
            base,
            ..
        } => {
            for ta in type_args {
                *ta = substitute_type(ta, mapping);
            }
            for (_, fval) in fields {
                substitute_expr_types(fval, mapping);
            }
            if let Some(b) = base {
                substitute_expr_types(b, mapping);
            }
        }
        Expr::Index { expr: inner, index } => {
            substitute_expr_types(inner, mapping);
            substitute_expr_types(index, mapping);
        }
        Expr::Field { expr: inner, .. } => substitute_expr_types(inner, mapping),
        Expr::Array(elems) | Expr::Tuple(elems) => {
            for e in elems {
                substitute_expr_types(e, mapping);
            }
        }
        Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            substitute_expr_types(condition, mapping);
            substitute_expr_types(then_expr, mapping);
            substitute_expr_types(else_expr, mapping);
        }
        Expr::Block(b) => substitute_body_types(b, mapping),
        _ => {}
    }
}

fn collect_requests_in_block(
    block: &mut Block,
    env: &mut HashMap<String, Type>,
    generic_structs: &HashMap<String, StructDef>,
    generic_functions: &HashMap<String, Function>,
    all_structs: &HashMap<String, StructDef>,
    all_functions: &HashMap<String, Function>,
    file_path: &str,
    context: &str,
    worklist: &mut Vec<Request>,
    diagnostics: &mut Vec<Diagnostic>,
) {
    for stmt in &mut block.statements {
        match stmt {
            Stmt::Let {
                name, ty, value, ..
            } => {
                if let Some(t) = ty {
                    collect_requests_in_type(t, generic_structs, worklist);
                }
                collect_requests_in_expr(
                    value,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
                let vty = ty
                    .clone()
                    .unwrap_or_else(|| infer_expr_type(value, env, all_structs, all_functions));
                env.insert(name.clone(), vty);
            }
            Stmt::Expr(e) | Stmt::Return(Some(e)) => {
                collect_requests_in_expr(
                    e,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }
            Stmt::If {
                condition,
                then_block,
                else_block,
            } => {
                collect_requests_in_expr(
                    condition,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
                let mut then_env = env.clone();
                collect_requests_in_block(
                    then_block,
                    &mut then_env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
                if let Some(eb) = else_block {
                    let mut else_env = env.clone();
                    collect_requests_in_block(
                        eb,
                        &mut else_env,
                        generic_structs,
                        generic_functions,
                        all_structs,
                        all_functions,
                        file_path,
                        context,
                        worklist,
                        diagnostics,
                    );
                }
            }
            Stmt::While {
                condition, body, ..
            } => {
                collect_requests_in_expr(
                    condition,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
                let mut body_env = env.clone();
                collect_requests_in_block(
                    body,
                    &mut body_env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }
            Stmt::For { iter, body, .. } => {
                collect_requests_in_expr(
                    iter,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
                let mut body_env = env.clone();
                collect_requests_in_block(
                    body,
                    &mut body_env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }
            Stmt::Loop { body, .. } => {
                let mut body_env = env.clone();
                collect_requests_in_block(
                    body,
                    &mut body_env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }
            Stmt::Match { expr, arms } => {
                collect_requests_in_expr(
                    expr,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
                for arm in arms {
                    if let Some(g) = &mut arm.guard {
                        collect_requests_in_expr(
                            g,
                            env,
                            generic_structs,
                            generic_functions,
                            all_structs,
                            all_functions,
                            file_path,
                            context,
                            worklist,
                            diagnostics,
                        );
                    }
                    match &mut arm.body {
                        MatchBody::Expr(e) => {
                            collect_requests_in_expr(
                                e,
                                env,
                                generic_structs,
                                generic_functions,
                                all_structs,
                                all_functions,
                                file_path,
                                context,
                                worklist,
                                diagnostics,
                            );
                        }
                        MatchBody::Block(b) => {
                            let mut arm_env = env.clone();
                            collect_requests_in_block(
                                b,
                                &mut arm_env,
                                generic_structs,
                                generic_functions,
                                all_structs,
                                all_functions,
                                file_path,
                                context,
                                worklist,
                                diagnostics,
                            );
                        }
                    }
                }
            }
            Stmt::Defer(b) => {
                let mut defer_env = env.clone();
                collect_requests_in_block(
                    b,
                    &mut defer_env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }
            _ => {}
        }
    }
}

fn collect_requests_in_type(
    ty: &Type,
    generic_structs: &HashMap<String, StructDef>,
    worklist: &mut Vec<Request>,
) {
    match ty {
        Type::Generic(name, args) => {
            if generic_structs.contains_key(name) {
                worklist.push(Request::Struct(name.clone(), args.clone()));
            }
            for a in args {
                collect_requests_in_type(a, generic_structs, worklist);
            }
        }
        Type::Option(inner) | Type::Vec(inner) | Type::Slice(inner) | Type::Array(inner, _) => {
            collect_requests_in_type(inner, generic_structs, worklist);
        }
        Type::Result(ok, err) | Type::HashMap(ok, err) => {
            collect_requests_in_type(ok, generic_structs, worklist);
            collect_requests_in_type(err, generic_structs, worklist);
        }
        Type::Tuple(elems) => {
            for e in elems {
                collect_requests_in_type(e, generic_structs, worklist);
            }
        }
        Type::Fn(params, ret) => {
            for p in params {
                collect_requests_in_type(p, generic_structs, worklist);
            }
            collect_requests_in_type(ret, generic_structs, worklist);
        }
        _ => {}
    }
}

fn collect_requests_in_expr(
    expr: &mut Expr,
    env: &HashMap<String, Type>,
    generic_structs: &HashMap<String, StructDef>,
    generic_functions: &HashMap<String, Function>,
    all_structs: &HashMap<String, StructDef>,
    all_functions: &HashMap<String, Function>,
    file_path: &str,
    context: &str,
    worklist: &mut Vec<Request>,
    diagnostics: &mut Vec<Diagnostic>,
) {
    match expr {
        Expr::Cast {
            target_type,
            expr: inner,
        } => {
            collect_requests_in_type(target_type, generic_structs, worklist);
            collect_requests_in_expr(
                inner,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
        }
        Expr::Binary { left, right, .. } => {
            collect_requests_in_expr(
                left,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
            collect_requests_in_expr(
                right,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
        }
        Expr::Unary { expr: inner, .. } => {
            collect_requests_in_expr(
                inner,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
        }
        Expr::Struct {
            name,
            type_args,
            fields,
            base,
        } => {
            for (_, fval) in fields.iter_mut() {
                collect_requests_in_expr(
                    fval,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }
            if let Some(b) = base {
                collect_requests_in_expr(
                    b,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }

            if let Some(generic_def) = generic_structs.get(name) {
                if !type_args.is_empty() {
                    if type_args.len() != generic_def.type_params.len() {
                        diagnostics.push(Diagnostic::error(
                            codes::GENERIC_ARG_COUNT,
                            format!(
                                "Wrong number of type arguments for struct '{}': expected {}, found {}",
                                name, generic_def.type_params.len(), type_args.len()
                            ),
                            SourceLocation::with_context(file_path, context),
                        ));
                    } else {
                        worklist.push(Request::Struct(name.clone(), type_args.clone()));
                    }
                } else {
                    // Deduce type arguments from fields
                    let mut mapping = HashMap::new();
                    let mut had_conflict = false;
                    for (fname, fval) in fields.iter() {
                        let actual_val_ty = infer_expr_type(fval, env, all_structs, all_functions);
                        if let Some(sf) = generic_def.fields.iter().find(|f| f.name == *fname) {
                            if let Err(err_msg) = unify_type_param(
                                &sf.ty,
                                &actual_val_ty,
                                &generic_def.type_params,
                                &mut mapping,
                            ) {
                                diagnostics.push(Diagnostic::error(
                                    codes::GENERIC_INFERENCE_FAILED,
                                    err_msg,
                                    SourceLocation::with_context(file_path, context),
                                ));
                                had_conflict = true;
                                break;
                            }
                        }
                    }

                    if !had_conflict {
                        let mut resolved_args = Vec::new();
                        let mut all_resolved = true;
                        for p in &generic_def.type_params {
                            if let Some(t) = mapping.get(p) {
                                resolved_args.push(t.clone());
                            } else {
                                diagnostics.push(Diagnostic::error(
                                    codes::GENERIC_INFERENCE_FAILED,
                                    format!("Cannot infer type argument for type parameter '{}' in struct '{}'", p, name),
                                    SourceLocation::with_context(file_path, context),
                                ));
                                all_resolved = false;
                            }
                        }
                        if all_resolved {
                            *type_args = resolved_args.clone();
                            worklist.push(Request::Struct(name.clone(), resolved_args));
                        }
                    }
                }
            }
        }
        Expr::Call {
            func,
            type_args,
            args,
        } => {
            collect_requests_in_expr(
                func,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
            for a in args.iter_mut() {
                collect_requests_in_expr(
                    a,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }

            // Check if calling a generic function or tuple struct
            if let Expr::Ident(fn_name) = func.as_ref() {
                if let Some(generic_struct) = generic_structs.get(fn_name) {
                    if generic_struct.is_tuple {
                        if !type_args.is_empty() {
                            if type_args.len() != generic_struct.type_params.len() {
                                diagnostics.push(Diagnostic::error(
                                    codes::GENERIC_ARG_COUNT,
                                    format!(
                                        "Wrong number of type arguments for '{}': expected {}, found {}",
                                        fn_name, generic_struct.type_params.len(), type_args.len()
                                    ),
                                    SourceLocation::with_context(file_path, context),
                                ));
                            } else {
                                worklist.push(Request::Struct(fn_name.clone(), type_args.clone()));
                            }
                        } else {
                            let mut mapping = HashMap::new();
                            let mut had_conflict = false;
                            for (i, a_expr) in args.iter().enumerate() {
                                let actual_val_ty =
                                    infer_expr_type(a_expr, env, all_structs, all_functions);
                                if let Some(sf) = generic_struct.fields.get(i) {
                                    if let Err(err_msg) = unify_type_param(
                                        &sf.ty,
                                        &actual_val_ty,
                                        &generic_struct.type_params,
                                        &mut mapping,
                                    ) {
                                        diagnostics.push(Diagnostic::error(
                                            codes::GENERIC_INFERENCE_FAILED,
                                            err_msg,
                                            SourceLocation::with_context(file_path, context),
                                        ));
                                        had_conflict = true;
                                        break;
                                    }
                                }
                            }
                            if !had_conflict {
                                let mut resolved_args = Vec::new();
                                let mut all_resolved = true;
                                for p in &generic_struct.type_params {
                                    if let Some(t) = mapping.get(p) {
                                        resolved_args.push(t.clone());
                                    } else {
                                        diagnostics.push(Diagnostic::error(
                                            codes::GENERIC_INFERENCE_FAILED,
                                            format!("Cannot infer type argument for type parameter '{}' in '{}'", p, fn_name),
                                            SourceLocation::with_context(file_path, context),
                                        ));
                                        all_resolved = false;
                                    }
                                }
                                if all_resolved {
                                    *type_args = resolved_args.clone();
                                    worklist.push(Request::Struct(fn_name.clone(), resolved_args));
                                }
                            }
                        }
                    }
                } else if let Some(generic_fn) = generic_functions.get(fn_name) {
                    if !type_args.is_empty() {
                        if type_args.len() != generic_fn.type_params.len() {
                            diagnostics.push(Diagnostic::error(
                                codes::GENERIC_ARG_COUNT,
                                format!(
                                    "Wrong number of type arguments for '{}': expected {}, found {}",
                                    fn_name, generic_fn.type_params.len(), type_args.len()
                                ),
                                SourceLocation::with_context(file_path, context),
                            ));
                        } else {
                            worklist.push(Request::Function(fn_name.clone(), type_args.clone()));
                        }
                    } else {
                        // Infer from argument types
                        let mut mapping = HashMap::new();
                        let mut had_conflict = false;
                        for (p_decl, a_expr) in generic_fn.params.iter().zip(args.iter()) {
                            let actual_arg_ty =
                                infer_expr_type(a_expr, env, all_structs, all_functions);
                            if let Err(err_msg) = unify_type_param(
                                &p_decl.ty,
                                &actual_arg_ty,
                                &generic_fn.type_params,
                                &mut mapping,
                            ) {
                                diagnostics.push(Diagnostic::error(
                                    codes::GENERIC_INFERENCE_FAILED,
                                    err_msg,
                                    SourceLocation::with_context(file_path, context),
                                ));
                                had_conflict = true;
                                break;
                            }
                        }

                        if !had_conflict {
                            let mut resolved_args = Vec::new();
                            let mut all_resolved = true;
                            for p in &generic_fn.type_params {
                                if let Some(t) = mapping.get(p) {
                                    resolved_args.push(t.clone());
                                } else {
                                    diagnostics.push(Diagnostic::error(
                                        codes::GENERIC_INFERENCE_FAILED,
                                        format!("Cannot infer type argument for type parameter '{}' in call to '{}'", p, fn_name),
                                        SourceLocation::with_context(file_path, context),
                                    ));
                                    all_resolved = false;
                                }
                            }
                            if all_resolved {
                                *type_args = resolved_args.clone();
                                worklist.push(Request::Function(fn_name.clone(), resolved_args));
                            }
                        }
                    }
                }
            } else if let Expr::Field {
                expr: receiver,
                field,
            } = func.as_mut()
            {
                // Method call on struct: receiver.method(...)
                let receiver_ty = infer_expr_type(receiver, env, all_structs, all_functions);
                if let Type::Generic(struct_name, s_args) = &receiver_ty {
                    if generic_structs.contains_key(struct_name) {
                        worklist.push(Request::Struct(struct_name.clone(), s_args.clone()));
                    }
                    let full_method_name = format!("{}::{}", struct_name, field);
                    if let Some(generic_fn) = generic_functions.get(&full_method_name) {
                        let mut mapping = HashMap::new();
                        if let Some(generic_struct) = generic_structs.get(struct_name) {
                            for (p, a) in generic_struct.type_params.iter().zip(s_args.iter()) {
                                mapping.insert(p.clone(), a.clone());
                            }
                        }
                        for (p_decl, a_expr) in generic_fn.params.iter().skip(1).zip(args.iter()) {
                            let actual_arg_ty =
                                infer_expr_type(a_expr, env, all_structs, all_functions);
                            let _ = unify_type_param(
                                &p_decl.ty,
                                &actual_arg_ty,
                                &generic_fn.type_params,
                                &mut mapping,
                            );
                        }

                        let mut resolved_args = Vec::new();
                        for p in &generic_fn.type_params {
                            if let Some(t) = mapping.get(p) {
                                resolved_args.push(t.clone());
                            }
                        }
                        if resolved_args.len() == generic_fn.type_params.len() {
                            *type_args = resolved_args.clone();
                            worklist.push(Request::Function(full_method_name, resolved_args));
                        }
                    }
                }
            }
        }
        Expr::Index { expr: inner, index } => {
            collect_requests_in_expr(
                inner,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
            collect_requests_in_expr(
                index,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
        }
        Expr::Field { expr: inner, .. } => {
            collect_requests_in_expr(
                inner,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
            let inner_ty = infer_expr_type(inner, env, all_structs, all_functions);
            if let Type::Generic(struct_name, s_args) = &inner_ty {
                if generic_structs.contains_key(struct_name) {
                    worklist.push(Request::Struct(struct_name.clone(), s_args.clone()));
                }
            }
        }
        Expr::Array(elems) | Expr::Tuple(elems) => {
            for e in elems {
                collect_requests_in_expr(
                    e,
                    env,
                    generic_structs,
                    generic_functions,
                    all_structs,
                    all_functions,
                    file_path,
                    context,
                    worklist,
                    diagnostics,
                );
            }
        }
        Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            collect_requests_in_expr(
                condition,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
            collect_requests_in_expr(
                then_expr,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
            collect_requests_in_expr(
                else_expr,
                env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
        }
        Expr::Block(b) => {
            let mut local_env = env.clone();
            collect_requests_in_block(
                b,
                &mut local_env,
                generic_structs,
                generic_functions,
                all_structs,
                all_functions,
                file_path,
                context,
                worklist,
                diagnostics,
            );
        }
        _ => {}
    }
}

fn rewrite_block(
    block: &mut Block,
    generic_structs: &HashMap<String, StructDef>,
    generic_functions: &HashMap<String, Function>,
) {
    for stmt in &mut block.statements {
        match stmt {
            Stmt::Let { ty, value, .. } => {
                if let Some(t) = ty {
                    rewrite_type(t);
                }
                rewrite_expr(value, generic_structs, generic_functions);
            }
            Stmt::Expr(e) | Stmt::Return(Some(e)) => {
                rewrite_expr(e, generic_structs, generic_functions);
            }
            Stmt::If {
                condition,
                then_block,
                else_block,
            } => {
                rewrite_expr(condition, generic_structs, generic_functions);
                rewrite_block(then_block, generic_structs, generic_functions);
                if let Some(eb) = else_block {
                    rewrite_block(eb, generic_structs, generic_functions);
                }
            }
            Stmt::While {
                condition, body, ..
            } => {
                rewrite_expr(condition, generic_structs, generic_functions);
                rewrite_block(body, generic_structs, generic_functions);
            }
            Stmt::For { iter, body, .. } => {
                rewrite_expr(iter, generic_structs, generic_functions);
                rewrite_block(body, generic_structs, generic_functions);
            }
            Stmt::Loop { body, .. } => {
                rewrite_block(body, generic_structs, generic_functions);
            }
            Stmt::Match { expr, arms } => {
                rewrite_expr(expr, generic_structs, generic_functions);
                for arm in arms {
                    if let Some(g) = &mut arm.guard {
                        rewrite_expr(g, generic_structs, generic_functions);
                    }
                    match &mut arm.body {
                        MatchBody::Expr(e) => rewrite_expr(e, generic_structs, generic_functions),
                        MatchBody::Block(b) => rewrite_block(b, generic_structs, generic_functions),
                    }
                }
            }
            Stmt::Defer(b) => {
                rewrite_block(b, generic_structs, generic_functions);
            }
            _ => {}
        }
    }
}

fn rewrite_expr(
    expr: &mut Expr,
    generic_structs: &HashMap<String, StructDef>,
    generic_functions: &HashMap<String, Function>,
) {
    match expr {
        Expr::Cast {
            target_type,
            expr: inner,
        } => {
            rewrite_type(target_type);
            rewrite_expr(inner, generic_structs, generic_functions);
        }
        Expr::Binary { left, right, .. } => {
            rewrite_expr(left, generic_structs, generic_functions);
            rewrite_expr(right, generic_structs, generic_functions);
        }
        Expr::Unary { expr: inner, .. } => {
            rewrite_expr(inner, generic_structs, generic_functions);
        }
        Expr::Struct {
            name,
            type_args,
            fields,
            base,
        } => {
            for (_, fval) in fields.iter_mut() {
                rewrite_expr(fval, generic_structs, generic_functions);
            }
            if let Some(b) = base {
                rewrite_expr(b, generic_structs, generic_functions);
            }
            if generic_structs.contains_key(name) && !type_args.is_empty() {
                *name = mangle_name(name, type_args);
                type_args.clear();
            }
        }
        Expr::Call {
            func,
            type_args,
            args,
        } => {
            rewrite_expr(func, generic_structs, generic_functions);
            for a in args.iter_mut() {
                rewrite_expr(a, generic_structs, generic_functions);
            }

            if let Expr::Ident(fn_name) = func.as_mut() {
                if generic_structs.contains_key(fn_name) && !type_args.is_empty() {
                    *fn_name = mangle_name(fn_name, type_args);
                    type_args.clear();
                } else if generic_functions.contains_key(fn_name) && !type_args.is_empty() {
                    *fn_name = mangle_name(fn_name, type_args);
                    type_args.clear();
                }
            } else if let Expr::Field { .. } = func.as_mut() {
                type_args.clear();
            }
        }
        Expr::Index { expr: inner, index } => {
            rewrite_expr(inner, generic_structs, generic_functions);
            rewrite_expr(index, generic_structs, generic_functions);
        }
        Expr::Field { expr: inner, .. } => {
            rewrite_expr(inner, generic_structs, generic_functions);
        }
        Expr::Array(elems) | Expr::Tuple(elems) => {
            for e in elems {
                rewrite_expr(e, generic_structs, generic_functions);
            }
        }
        Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            rewrite_expr(condition, generic_structs, generic_functions);
            rewrite_expr(then_expr, generic_structs, generic_functions);
            rewrite_expr(else_expr, generic_structs, generic_functions);
        }
        Expr::Block(b) => rewrite_block(b, generic_structs, generic_functions),
        _ => {}
    }
}

fn rewrite_type_in_params(params: &mut [ast::Param]) {
    for p in params {
        rewrite_type(&mut p.ty);
    }
}

fn rewrite_type(ty: &mut Type) {
    match ty {
        Type::Generic(name, args) => {
            for a in args.iter_mut() {
                rewrite_type(a);
            }
            let mangled = mangle_name(name, args);
            *ty = Type::Named(mangled);
        }
        Type::Option(inner) | Type::Vec(inner) | Type::Slice(inner) | Type::Array(inner, _) => {
            rewrite_type(inner);
        }
        Type::Result(ok, err) | Type::HashMap(ok, err) => {
            rewrite_type(ok);
            rewrite_type(err);
        }
        Type::Tuple(elems) => {
            for e in elems {
                rewrite_type(e);
            }
        }
        Type::Fn(params, ret) => {
            for p in params {
                rewrite_type(p);
            }
            rewrite_type(ret);
        }
        Type::Ref { ty: inner, .. } => rewrite_type(inner),
        _ => {}
    }
}
