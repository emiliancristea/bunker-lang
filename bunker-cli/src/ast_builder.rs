use crate::ast::*;
use crate::parser::Rule;
use pest::iterators::Pair;

pub fn build_ast(pair: Pair<Rule>) -> Result<File, String> {
    let mut file = File {
        kernels: vec![],
        shells: vec![],
        views: vec![],
    };

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::kernel_block => {
                file.kernels.push(build_kernel(inner)?);
            }
            Rule::shell_block => {
                file.shells.push(build_shell(inner)?);
            }
            Rule::view_block => {
                file.views.push(build_view(inner)?);
            }
            Rule::EOI => {}
            _ => {}
        }
    }

    Ok(file)
}

fn build_kernel(pair: Pair<Rule>) -> Result<Kernel, String> {
    let mut name = String::new();
    let mut items = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::kernel_item => {
                if let Some(item) = build_kernel_item(inner)? {
                    items.push(item);
                }
            }
            _ => {}
        }
    }

    Ok(Kernel { name, items })
}

fn build_kernel_item(pair: Pair<Rule>) -> Result<Option<KernelItem>, String> {
    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::function => {
                return Ok(Some(KernelItem::Function(build_function(inner)?)));
            }
            Rule::comptime_fn => {
                return Ok(Some(KernelItem::ComptimeFn(build_function(inner)?)));
            }
            Rule::struct_def => {
                return Ok(Some(KernelItem::Struct(build_struct(inner)?)));
            }
            Rule::const_def => {
                return Ok(Some(KernelItem::Const(build_const(inner)?)));
            }
            _ => {}
        }
    }
    Ok(None)
}

fn build_function(pair: Pair<Rule>) -> Result<Function, String> {
    let mut name = String::new();
    let mut attributes = vec![];
    let mut params = vec![];
    let mut return_type = None;
    let mut body = Block { statements: vec![] };

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::attribute => {
                attributes.push(build_attribute(inner)?);
            }
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::param_list => {
                params = build_param_list(inner)?;
            }
            Rule::type_expr => {
                return_type = Some(build_type(inner)?);
            }
            Rule::block => {
                body = build_block(inner)?;
            }
            _ => {}
        }
    }

    Ok(Function {
        name,
        attributes,
        params,
        return_type,
        body,
    })
}

fn build_attribute(pair: Pair<Rule>) -> Result<Attribute, String> {
    for inner in pair.into_inner() {
        if inner.as_rule() != Rule::attribute_inner {
            continue;
        }

        let text = inner.as_str();
        if text == "verified" {
            return Ok(Attribute::Verified);
        } else if text == "unsafe_trust" {
            return Ok(Attribute::UnsafeTrust);
        } else {
            for attr_inner in inner.into_inner() {
                match attr_inner.as_rule() {
                    Rule::requires_attr => {
                        for expr_pair in attr_inner.into_inner() {
                            if expr_pair.as_rule() == Rule::expr {
                                return Ok(Attribute::Requires(build_expr(expr_pair)?));
                            }
                        }
                    }
                    Rule::ensures_attr => {
                        for expr_pair in attr_inner.into_inner() {
                            if expr_pair.as_rule() == Rule::expr {
                                return Ok(Attribute::Ensures(build_expr(expr_pair)?));
                            }
                        }
                    }
                    _ => {}
                }
            }
        }
    }
    Err("Unknown attribute".to_string())
}

fn build_param_list(pair: Pair<Rule>) -> Result<Vec<Param>, String> {
    let mut params = vec![];
    for inner in pair.into_inner() {
        if inner.as_rule() == Rule::param {
            params.push(build_param(inner)?);
        }
    }
    Ok(params)
}

fn build_param(pair: Pair<Rule>) -> Result<Param, String> {
    let mut name = String::new();
    let mut ty = Type::I32;

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::type_expr => {
                ty = build_type(inner)?;
            }
            _ => {}
        }
    }

    Ok(Param { name, ty })
}

fn build_type(pair: Pair<Rule>) -> Result<Type, String> {
    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::option_type => {
                for type_inner in inner.into_inner() {
                    if type_inner.as_rule() == Rule::type_expr {
                        return Ok(Type::Option(Box::new(build_type(type_inner)?)));
                    }
                }
            }
            Rule::result_type => {
                let mut types = Vec::new();
                for type_inner in inner.into_inner() {
                    if type_inner.as_rule() == Rule::type_expr {
                        types.push(build_type(type_inner)?);
                    }
                }
                if types.len() == 2 {
                    return Ok(Type::Result(
                        Box::new(types.remove(0)),
                        Box::new(types.remove(0)),
                    ));
                }
            }
            Rule::vec_type => {
                for type_inner in inner.into_inner() {
                    if type_inner.as_rule() == Rule::type_expr {
                        return Ok(Type::Vec(Box::new(build_type(type_inner)?)));
                    }
                }
            }
            Rule::hashmap_type => {
                let mut types = Vec::new();
                for type_inner in inner.into_inner() {
                    if type_inner.as_rule() == Rule::type_expr {
                        types.push(build_type(type_inner)?);
                    }
                }
                if types.len() == 2 {
                    return Ok(Type::HashMap(
                        Box::new(types.remove(0)),
                        Box::new(types.remove(0)),
                    ));
                }
            }
            Rule::array_type => {
                let mut elem_type = Type::I32;
                let mut size = 0usize;
                for arr_inner in inner.into_inner() {
                    match arr_inner.as_rule() {
                        Rule::type_expr => {
                            elem_type = build_type(arr_inner)?;
                        }
                        Rule::integer => {
                            size = arr_inner.as_str().parse().unwrap_or(0);
                        }
                        _ => {}
                    }
                }
                return Ok(Type::Array(Box::new(elem_type), size));
            }
            Rule::ref_type => {
                let mut inner_type = Type::I32;
                let text = inner.as_str();
                let mutable = text.contains("mut");
                for ref_inner in inner.into_inner() {
                    if ref_inner.as_rule() == Rule::type_expr {
                        inner_type = build_type(ref_inner)?;
                    }
                }
                return Ok(Type::Ref {
                    mutable,
                    ty: Box::new(inner_type),
                });
            }
            Rule::base_type => {
                let text = inner.as_str();
                return Ok(match text {
                    "i32" => Type::I32,
                    "i64" => Type::I64,
                    "f32" => Type::F32,
                    "f64" => Type::F64,
                    "bool" => Type::Bool,
                    "str" => Type::Str,
                    "vec2" => Type::Vec2,
                    "vec3" => Type::Vec3,
                    _ => Type::Named(text.to_string()),
                });
            }
            _ => {}
        }
    }
    Ok(Type::I32)
}

fn build_struct(pair: Pair<Rule>) -> Result<StructDef, String> {
    let mut name = String::new();
    let mut fields = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::struct_field => {
                fields.push(build_struct_field(inner)?);
            }
            _ => {}
        }
    }

    Ok(StructDef { name, fields })
}

fn build_struct_field(pair: Pair<Rule>) -> Result<StructField, String> {
    let mut name = String::new();
    let mut ty = Type::I32;

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::type_expr => {
                ty = build_type(inner)?;
            }
            _ => {}
        }
    }

    Ok(StructField { name, ty })
}

fn build_const(pair: Pair<Rule>) -> Result<ConstDef, String> {
    let mut name = String::new();
    let mut ty = Type::I32;
    let mut value = Expr::Literal(Literal::Int(0));

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::type_expr => {
                ty = build_type(inner)?;
            }
            Rule::expr => {
                value = build_expr(inner)?;
            }
            _ => {}
        }
    }

    Ok(ConstDef { name, ty, value })
}

fn build_block(pair: Pair<Rule>) -> Result<Block, String> {
    let mut statements = vec![];

    for inner in pair.into_inner() {
        if inner.as_rule() == Rule::statement {
            statements.push(build_statement(inner)?);
        }
    }

    Ok(Block { statements })
}

fn build_statement(pair: Pair<Rule>) -> Result<Stmt, String> {
    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::let_stmt => {
                return build_let_stmt(inner);
            }
            Rule::return_stmt => {
                return build_return_stmt(inner);
            }
            Rule::if_stmt => {
                return build_if_stmt(inner);
            }
            Rule::for_stmt => {
                return build_for_stmt(inner);
            }
            Rule::while_stmt => {
                return build_while_stmt(inner);
            }
            Rule::loop_stmt => {
                return build_loop_stmt(inner);
            }
            Rule::break_stmt => {
                return Ok(Stmt::Break);
            }
            Rule::continue_stmt => {
                return Ok(Stmt::Continue);
            }
            Rule::match_stmt => {
                return build_match_stmt(inner);
            }
            Rule::defer_stmt => {
                return build_defer_stmt(inner);
            }
            Rule::send_stmt => {
                return build_send_stmt(inner);
            }
            Rule::assign_stmt => {
                return build_assign_stmt(inner);
            }
            Rule::expr_stmt => {
                for expr_inner in inner.into_inner() {
                    if expr_inner.as_rule() == Rule::expr {
                        return Ok(Stmt::Expr(build_expr(expr_inner)?));
                    }
                }
            }
            _ => {}
        }
    }
    Err("Unknown statement".to_string())
}

fn build_let_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    let mut name = String::new();
    let mut ty = None;
    let mut value = Expr::Literal(Literal::Int(0));

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::type_expr => {
                ty = Some(build_type(inner)?);
            }
            Rule::expr => {
                value = build_expr(inner)?;
            }
            _ => {}
        }
    }

    Ok(Stmt::Let { name, ty, value })
}

fn build_return_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    for inner in pair.into_inner() {
        if inner.as_rule() == Rule::expr {
            return Ok(Stmt::Return(Some(build_expr(inner)?)));
        }
    }
    Ok(Stmt::Return(None))
}

fn build_if_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    let mut condition = Expr::Literal(Literal::Bool(true));
    let mut then_block = Block { statements: vec![] };
    let mut else_block = None;
    let mut found_condition = false;
    let mut found_then = false;

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr if !found_condition => {
                condition = build_expr(inner)?;
                found_condition = true;
            }
            Rule::block if !found_then => {
                then_block = build_block(inner)?;
                found_then = true;
            }
            Rule::block => {
                else_block = Some(build_block(inner)?);
            }
            Rule::if_stmt => {
                let nested_if = build_if_stmt(inner)?;
                else_block = Some(Block {
                    statements: vec![nested_if],
                });
            }
            _ => {}
        }
    }

    Ok(Stmt::If {
        condition,
        then_block,
        else_block,
    })
}

fn build_for_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    let mut var = String::new();
    let mut iter = Expr::Literal(Literal::Int(0));
    let mut body = Block { statements: vec![] };

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                var = inner.as_str().to_string();
            }
            Rule::expr => {
                iter = build_expr(inner)?;
            }
            Rule::block => {
                body = build_block(inner)?;
            }
            _ => {}
        }
    }

    Ok(Stmt::For { var, iter, body })
}

fn build_while_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    let mut condition = Expr::Literal(Literal::Bool(true));
    let mut body = Block { statements: vec![] };

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr => {
                condition = build_expr(inner)?;
            }
            Rule::block => {
                body = build_block(inner)?;
            }
            _ => {}
        }
    }

    Ok(Stmt::While { condition, body })
}

fn build_loop_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    for inner in pair.into_inner() {
        if inner.as_rule() == Rule::block {
            return Ok(Stmt::Loop(build_block(inner)?));
        }
    }
    Ok(Stmt::Loop(Block { statements: vec![] }))
}

fn build_match_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    let mut expr = Expr::Literal(Literal::Int(0));
    let mut arms = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr => {
                expr = build_expr(inner)?;
            }
            Rule::match_arm => {
                arms.push(build_match_arm(inner)?);
            }
            _ => {}
        }
    }

    Ok(Stmt::Match { expr, arms })
}

fn build_match_arm(pair: Pair<Rule>) -> Result<MatchArm, String> {
    let mut pattern = Pattern::Ident("_".to_string());
    let mut body = MatchBody::Expr(Expr::Literal(Literal::Int(0)));

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::pattern => {
                pattern = build_pattern(inner)?;
            }
            Rule::expr => {
                body = MatchBody::Expr(build_expr(inner)?);
            }
            Rule::block => {
                let block = build_block(inner)?;
                body = MatchBody::Block(block);
            }
            _ => {}
        }
    }

    Ok(MatchArm { pattern, body })
}

fn build_pattern(pair: Pair<Rule>) -> Result<Pattern, String> {
    let text = pair.as_str().trim().to_string();

    if text.starts_with("Some(") && text.ends_with(')') {
        let inner = &text[5..text.len() - 1];
        return Ok(Pattern::Some(inner.to_string()));
    }
    if text == "None" {
        return Ok(Pattern::None);
    }
    if text == "true" {
        return Ok(Pattern::Bool(true));
    }
    if text == "false" {
        return Ok(Pattern::Bool(false));
    }

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::literal => {
                let expr = build_literal(inner)?;
                if let Expr::Literal(lit) = expr {
                    return Ok(Pattern::Literal(lit));
                }
            }
            Rule::identifier => return Ok(Pattern::Ident(inner.as_str().to_string())),
            _ => {}
        }
    }

    Ok(Pattern::Ident(text))
}

fn build_defer_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr => {
                let expr = build_expr(inner)?;
                return Ok(Stmt::Defer(Block {
                    statements: vec![Stmt::Expr(expr)],
                }));
            }
            Rule::block => {
                let block = build_block(inner)?;
                return Ok(Stmt::Defer(block));
            }
            _ => {}
        }
    }
    Err("Invalid defer statement".to_string())
}

fn build_send_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    let mut message = Expr::Literal(Literal::String(String::new()));
    let mut target = String::new();
    let mut args = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr => {
                message = build_expr(inner)?;
            }
            Rule::identifier => {
                target = inner.as_str().to_string();
            }
            Rule::named_args => {
                args = build_named_args(inner)?;
            }
            _ => {}
        }
    }

    Ok(Stmt::Send {
        message,
        target,
        args,
    })
}

fn build_assign_stmt(pair: Pair<Rule>) -> Result<Stmt, String> {
    let mut target = Expr::Ident(String::new());
    let mut value = Expr::Literal(Literal::Int(0));

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::assign_target => {
                target = build_assign_target(inner)?;
            }
            Rule::expr => {
                value = build_expr(inner)?;
            }
            _ => {}
        }
    }

    Ok(Stmt::Assign { target, value })
}

fn build_assign_target(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut result = Expr::Ident(String::new());
    let mut first = true;

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                if first {
                    result = Expr::Ident(inner.as_str().to_string());
                    first = false;
                } else {
                    result = Expr::Field {
                        expr: Box::new(result),
                        field: inner.as_str().to_string(),
                    };
                }
            }
            Rule::expr => {
                result = Expr::Index {
                    expr: Box::new(result),
                    index: Box::new(build_expr(inner)?),
                };
            }
            _ => {}
        }
    }

    Ok(result)
}

fn build_named_args(pair: Pair<Rule>) -> Result<Vec<(String, Expr)>, String> {
    let mut args = vec![];
    for inner in pair.into_inner() {
        if inner.as_rule() == Rule::named_arg {
            let mut name = String::new();
            let mut value = Expr::Literal(Literal::Int(0));
            for arg_inner in inner.into_inner() {
                match arg_inner.as_rule() {
                    Rule::identifier => {
                        name = arg_inner.as_str().to_string();
                    }
                    Rule::expr => {
                        value = build_expr(arg_inner)?;
                    }
                    _ => {}
                }
            }
            args.push((name, value));
        }
    }
    Ok(args)
}

fn build_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    for inner in pair.into_inner() {
        if inner.as_rule() == Rule::ternary_expr {
            return build_ternary_expr(inner);
        }
    }
    Err("Invalid expression".to_string())
}

fn build_ternary_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut parts: Vec<Expr> = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::range_expr => {
                parts.push(build_range_expr(inner)?);
            }
            Rule::expr => {
                parts.push(build_expr(inner)?);
            }
            _ => {}
        }
    }

    if parts.len() == 3 {
        Ok(Expr::If {
            condition: Box::new(parts.remove(0)),
            then_expr: Box::new(parts.remove(0)),
            else_expr: Box::new(parts.remove(0)),
        })
    } else if parts.len() == 1 {
        Ok(parts.remove(0))
    } else {
        Err("Invalid ternary expression".to_string())
    }
}

fn build_range_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut start: Option<Expr> = None;
    let mut end: Option<Expr> = None;
    let mut inclusive = false;

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::or_expr => {
                if start.is_none() {
                    start = Some(build_or_expr(inner)?);
                } else {
                    end = Some(build_or_expr(inner)?);
                }
            }
            Rule::range_op => {
                inclusive = inner.as_str() == "..=";
            }
            _ => {}
        }
    }

    match (start, end) {
        (Some(s), Some(e)) => Ok(Expr::Range {
            start: Box::new(s),
            end: Box::new(e),
            inclusive,
        }),
        (Some(expr), None) => Ok(expr),
        _ => Err("Invalid range expression".to_string()),
    }
}

fn build_or_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut exprs: Vec<Expr> = vec![];
    let mut ops: Vec<BinaryOp> = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::prefix_expr => {
                exprs.push(build_prefix_expr(inner)?);
            }
            Rule::binary_op => {
                ops.push(build_binary_op(inner)?);
            }
            _ => {}
        }
    }

    if exprs.is_empty() {
        return Err("Empty expression".to_string());
    }

    fn precedence(op: BinaryOp) -> u8 {
        match op {
            BinaryOp::Or => 1,
            BinaryOp::And => 2,
            BinaryOp::BitOr => 3,
            BinaryOp::BitXor => 4,
            BinaryOp::BitAnd => 5,
            BinaryOp::Eq
            | BinaryOp::Ne
            | BinaryOp::Lt
            | BinaryOp::Le
            | BinaryOp::Gt
            | BinaryOp::Ge => 6,
            BinaryOp::Shl | BinaryOp::Shr => 7,
            BinaryOp::Add | BinaryOp::Sub => 8,
            BinaryOp::Mul | BinaryOp::Div | BinaryOp::Mod => 9,
            BinaryOp::As => 10,
        }
    }

    fn reduce_once(expr_stack: &mut Vec<Expr>, op: BinaryOp) -> Result<(), String> {
        let right = expr_stack
            .pop()
            .ok_or_else(|| "Missing RHS expression".to_string())?;
        let left = expr_stack
            .pop()
            .ok_or_else(|| "Missing LHS expression".to_string())?;
        expr_stack.push(Expr::Binary {
            op,
            left: Box::new(left),
            right: Box::new(right),
        });
        Ok(())
    }

    let mut expr_stack: Vec<Expr> = Vec::new();
    let mut op_stack: Vec<BinaryOp> = Vec::new();

    let mut expr_iter = exprs.into_iter();
    let Some(first) = expr_iter.next() else {
        return Err("Empty expression".to_string());
    };
    expr_stack.push(first);

    for (op, rhs) in ops.into_iter().zip(expr_iter) {
        while let Some(&top) = op_stack.last() {
            if precedence(top) >= precedence(op) {
                let top = op_stack.pop().expect("peeked above");
                reduce_once(&mut expr_stack, top)?;
            } else {
                break;
            }
        }
        op_stack.push(op);
        expr_stack.push(rhs);
    }

    while let Some(op) = op_stack.pop() {
        reduce_once(&mut expr_stack, op)?;
    }

    let result = match expr_stack.len() {
        1 => expr_stack.pop().expect("len checked above"),
        _ => return Err("Invalid expression".to_string()),
    };

    Ok(result)
}

fn build_prefix_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut op: Option<UnaryOp> = None;
    let mut expr = Expr::Literal(Literal::Int(0));
    let mut is_copy = false;

    let inners: Vec<_> = pair.into_inner().collect();

    for inner in &inners {
        match inner.as_rule() {
            Rule::prefix_op => {
                let text = inner.as_str();
                match text {
                    "!" => op = Some(UnaryOp::Not),
                    "-" => op = Some(UnaryOp::Neg),
                    "copy" => is_copy = true,
                    _ => op = Some(UnaryOp::Not),
                }
            }
            Rule::postfix_expr => {
                expr = build_postfix_expr(inner.clone())?;
            }
            _ => {}
        }
    }

    if is_copy {
        return Ok(Expr::Copy(Box::new(expr)));
    }

    if let Some(op) = op {
        Ok(Expr::Unary {
            op,
            expr: Box::new(expr),
        })
    } else {
        Ok(expr)
    }
}

fn build_postfix_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut result = Expr::Literal(Literal::Int(0));

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::primary_expr => {
                result = build_primary_expr(inner)?;
            }
            Rule::postfix_op => {
                result = build_postfix_op(inner, result)?;
            }
            _ => {}
        }
    }

    Ok(result)
}

fn build_postfix_op(pair: Pair<Rule>, base: Expr) -> Result<Expr, String> {
    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::call_op => {
                let mut args = vec![];
                for call_inner in inner.into_inner() {
                    if call_inner.as_rule() == Rule::arg_list {
                        for arg in call_inner.into_inner() {
                            if arg.as_rule() == Rule::expr {
                                args.push(build_expr(arg)?);
                            }
                        }
                    }
                }
                return Ok(Expr::Call {
                    func: Box::new(base),
                    args,
                });
            }
            Rule::index_op => {
                for idx_inner in inner.into_inner() {
                    if idx_inner.as_rule() == Rule::expr {
                        return Ok(Expr::Index {
                            expr: Box::new(base),
                            index: Box::new(build_expr(idx_inner)?),
                        });
                    }
                }
            }
            Rule::field_op => {
                for field_inner in inner.into_inner() {
                    if field_inner.as_rule() == Rule::identifier {
                        return Ok(Expr::Field {
                            expr: Box::new(base),
                            field: field_inner.as_str().to_string(),
                        });
                    }
                }
            }
            Rule::cast_op => {
                for cast_inner in inner.into_inner() {
                    if cast_inner.as_rule() == Rule::type_expr {
                        return Ok(Expr::Cast {
                            expr: Box::new(base),
                            target_type: build_type(cast_inner)?,
                        });
                    }
                }
            }
            _ => {}
        }
    }
    Ok(base)
}

fn build_primary_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr => {
                return build_expr(inner);
            }
            Rule::use_expr => {
                return build_use_expr(inner);
            }
            Rule::send_expr => {
                return build_send_expr(inner);
            }
            Rule::lambda_expr => {
                return build_lambda_expr(inner);
            }
            Rule::if_expr => {
                return build_if_expr(inner);
            }
            Rule::match_expr => {
                return build_match_expr(inner);
            }
            Rule::option_expr => {
                return build_option_expr(inner);
            }
            Rule::array_literal => {
                return build_array_literal(inner);
            }
            Rule::struct_literal => {
                return build_struct_literal(inner);
            }
            Rule::literal => {
                return build_literal(inner);
            }
            Rule::identifier => {
                return Ok(Expr::Ident(inner.as_str().to_string()));
            }
            _ => {}
        }
    }
    Err("Invalid primary expression".to_string())
}

fn build_option_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut inner_expr = None;
    for inner in pair.into_inner() {
        if inner.as_rule() == Rule::expr {
            inner_expr = Some(build_expr(inner)?);
        }
    }

    if let Some(expr) = inner_expr {
        Ok(Expr::Some(Box::new(expr)))
    } else {
        Ok(Expr::None)
    }
}

fn build_use_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut path = vec![];
    let mut args = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::qualified_name => {
                for name_inner in inner.into_inner() {
                    if name_inner.as_rule() == Rule::identifier {
                        path.push(name_inner.as_str().to_string());
                    }
                }
            }
            Rule::named_args => {
                args = build_named_args(inner)?;
            }
            _ => {}
        }
    }

    Ok(Expr::Use { path, args })
}

fn build_send_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut message = Expr::Literal(Literal::String(String::new()));
    let mut target = vec![];
    let mut args = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr => {
                message = build_expr(inner)?;
            }
            Rule::qualified_name => {
                for name_inner in inner.into_inner() {
                    if name_inner.as_rule() == Rule::identifier {
                        target.push(name_inner.as_str().to_string());
                    }
                }
            }
            Rule::named_args => {
                args = build_named_args(inner)?;
            }
            _ => {}
        }
    }

    Ok(Expr::Send {
        message: Box::new(message),
        target,
        args,
    })
}

fn build_lambda_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut params = vec![];
    let mut body = Expr::Literal(Literal::Int(0));

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::param_list => {
                params = build_param_list(inner)?;
            }
            Rule::expr => {
                body = build_expr(inner)?;
            }
            Rule::block => {
                // Simplified: just use a placeholder for block lambdas
                body = Expr::Literal(Literal::Int(0));
            }
            _ => {}
        }
    }

    Ok(Expr::Lambda {
        params,
        body: Box::new(body),
    })
}

fn build_if_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut condition = Expr::Literal(Literal::Bool(true));
    let mut found_cond = false;
    let mut blocks: Vec<Block> = Vec::new();

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr if !found_cond => {
                condition = build_expr(inner)?;
                found_cond = true;
            }
            Rule::block => {
                blocks.push(build_block(inner)?);
            }
            _ => {}
        }
    }

    let then_block = blocks
        .first()
        .cloned()
        .unwrap_or_else(|| Block { statements: vec![] });
    let else_block = blocks
        .get(1)
        .cloned()
        .unwrap_or_else(|| Block { statements: vec![] });

    Ok(Expr::If {
        condition: Box::new(condition),
        then_expr: Box::new(Expr::Block(then_block)),
        else_expr: Box::new(Expr::Block(else_block)),
    })
}

fn build_match_expr(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut expr = Expr::Literal(Literal::Int(0));
    let mut arms = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::expr => {
                expr = build_expr(inner)?;
            }
            Rule::match_arm => {
                arms.push(build_match_arm(inner)?);
            }
            _ => {}
        }
    }

    Ok(Expr::Match {
        expr: Box::new(expr),
        arms,
    })
}

fn build_array_literal(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut elements = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::array_repeat => {
                // Handle [value; count] syntax
                let mut value = Expr::Literal(Literal::Int(0));
                let mut count = 0usize;
                for rep_inner in inner.into_inner() {
                    match rep_inner.as_rule() {
                        Rule::expr => {
                            value = build_expr(rep_inner)?;
                        }
                        Rule::integer => {
                            count = rep_inner.as_str().parse().unwrap_or(0);
                        }
                        _ => {}
                    }
                }
                for _ in 0..count {
                    elements.push(value.clone());
                }
            }
            Rule::expr => {
                elements.push(build_expr(inner)?);
            }
            _ => {}
        }
    }

    Ok(Expr::Array(elements))
}

fn build_struct_literal(pair: Pair<Rule>) -> Result<Expr, String> {
    let mut name = String::new();
    let mut fields = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::struct_init => {
                let mut field_name = String::new();
                let mut field_value = Expr::Literal(Literal::Int(0));
                for init_inner in inner.into_inner() {
                    match init_inner.as_rule() {
                        Rule::identifier => {
                            field_name = init_inner.as_str().to_string();
                        }
                        Rule::expr => {
                            field_value = build_expr(init_inner)?;
                        }
                        _ => {}
                    }
                }
                fields.push((field_name, field_value));
            }
            _ => {}
        }
    }

    Ok(Expr::Struct { name, fields })
}

fn build_literal(pair: Pair<Rule>) -> Result<Expr, String> {
    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::integer => {
                let val: i64 = inner.as_str().parse().unwrap_or(0);
                return Ok(Expr::Literal(Literal::Int(val)));
            }
            Rule::float => {
                let val: f64 = inner.as_str().parse().unwrap_or(0.0);
                return Ok(Expr::Literal(Literal::Float(val)));
            }
            Rule::string_literal => {
                let s = inner.as_str();
                let s = &s[1..s.len() - 1]; // Remove quotes
                return Ok(Expr::Literal(Literal::String(s.to_string())));
            }
            Rule::char_literal => {
                let s = inner.as_str();
                let c = s.chars().nth(1).unwrap_or(' ');
                return Ok(Expr::Literal(Literal::Char(c)));
            }
            Rule::bool_literal => {
                let val = inner.as_str() == "true";
                return Ok(Expr::Literal(Literal::Bool(val)));
            }
            Rule::hex_color => {
                return Ok(Expr::Literal(Literal::HexColor(inner.as_str().to_string())));
            }
            _ => {}
        }
    }
    Err("Invalid literal".to_string())
}

fn build_binary_op(pair: Pair<Rule>) -> Result<BinaryOp, String> {
    let op = pair.as_str();
    Ok(match op {
        "+" => BinaryOp::Add,
        "-" => BinaryOp::Sub,
        "*" => BinaryOp::Mul,
        "/" => BinaryOp::Div,
        "%" => BinaryOp::Mod,
        "==" => BinaryOp::Eq,
        "!=" => BinaryOp::Ne,
        "<" => BinaryOp::Lt,
        "<=" => BinaryOp::Le,
        ">" => BinaryOp::Gt,
        ">=" => BinaryOp::Ge,
        "&&" => BinaryOp::And,
        "||" => BinaryOp::Or,
        "&" => BinaryOp::BitAnd,
        "|" => BinaryOp::BitOr,
        "^" => BinaryOp::BitXor,
        "<<" => BinaryOp::Shl,
        ">>" => BinaryOp::Shr,
        "as" => BinaryOp::As,
        _ => return Err(format!("Unknown operator: {}", op)),
    })
}

// Shell building

fn build_shell(pair: Pair<Rule>) -> Result<Shell, String> {
    let mut name = String::new();
    let mut imports = vec![];
    let mut agents = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::shell_item => {
                for item_inner in inner.into_inner() {
                    match item_inner.as_rule() {
                        Rule::import_stmt => {
                            for imp_inner in item_inner.into_inner() {
                                if imp_inner.as_rule() == Rule::identifier {
                                    imports.push(imp_inner.as_str().to_string());
                                }
                            }
                        }
                        Rule::agent_def => {
                            agents.push(build_agent(item_inner)?);
                        }
                        _ => {}
                    }
                }
            }
            _ => {}
        }
    }

    Ok(Shell {
        name,
        imports,
        agents,
    })
}

fn build_agent(pair: Pair<Rule>) -> Result<Agent, String> {
    let mut name = String::new();
    let mut state = vec![];
    let mut handlers = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::agent_item => {
                for item_inner in inner.into_inner() {
                    match item_inner.as_rule() {
                        Rule::state_decl => {
                            state.push(build_state_decl(item_inner)?);
                        }
                        Rule::message_handler => {
                            handlers.push(build_message_handler(item_inner)?);
                        }
                        _ => {}
                    }
                }
            }
            _ => {}
        }
    }

    Ok(Agent {
        name,
        state,
        handlers,
    })
}

fn build_state_decl(pair: Pair<Rule>) -> Result<StateDecl, String> {
    let mut name = String::new();
    let mut value = Expr::Literal(Literal::Int(0));

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::expr => {
                value = build_expr(inner)?;
            }
            _ => {}
        }
    }

    Ok(StateDecl { name, value })
}

fn build_message_handler(pair: Pair<Rule>) -> Result<MessageHandler, String> {
    let mut message = String::new();
    let mut params = vec![];
    let mut body = Block { statements: vec![] };

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::string_literal => {
                let s = inner.as_str();
                message = s[1..s.len() - 1].to_string();
            }
            Rule::param_list => {
                params = build_param_list(inner)?;
            }
            Rule::block => {
                body = build_block(inner)?;
            }
            _ => {}
        }
    }

    Ok(MessageHandler {
        message,
        params,
        body,
    })
}

// View building

fn build_view(pair: Pair<Rule>) -> Result<View, String> {
    let mut name = String::new();
    let mut components = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::view_item => {
                for item_inner in inner.into_inner() {
                    if item_inner.as_rule() == Rule::component {
                        components.push(build_component(item_inner)?);
                    }
                }
            }
            _ => {}
        }
    }

    Ok(View { name, components })
}

fn build_component(pair: Pair<Rule>) -> Result<Component, String> {
    let mut target = None;
    let mut name = String::new();
    let mut properties = vec![];
    let mut children = vec![];

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::target_attr => {
                let text = inner.as_str();
                if text.contains("graphics") {
                    target = Some(Target::Graphics);
                } else if text.contains("embedded") {
                    target = Some(Target::Embedded);
                }
            }
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::component_body => {
                for body_inner in inner.into_inner() {
                    match body_inner.as_rule() {
                        Rule::property => {
                            properties.push(build_property(body_inner)?);
                        }
                        Rule::component => {
                            children.push(build_component(body_inner)?);
                        }
                        _ => {}
                    }
                }
            }
            _ => {}
        }
    }

    Ok(Component {
        target,
        name,
        properties,
        children,
    })
}

fn build_property(pair: Pair<Rule>) -> Result<Property, String> {
    let mut name = String::new();
    let mut value = Expr::Literal(Literal::Int(0));

    for inner in pair.into_inner() {
        match inner.as_rule() {
            Rule::identifier => {
                name = inner.as_str().to_string();
            }
            Rule::expr => {
                value = build_expr(inner)?;
            }
            _ => {}
        }
    }

    Ok(Property { name, value })
}
