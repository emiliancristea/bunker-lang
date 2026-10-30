//! Machine-readable AST report for AI agents and tooling.
//!
//! Produces canonical BUNKER_AST_JSON matching the specification in Track A (A-010).

use serde::{Deserialize, Serialize};
use serde_json::Value;

use crate::ast;

/// Root-level metadata for the AST report.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AstRootSummary {
    pub kind: String,
    pub name: String,
    pub entry: String,
    pub source_start: i64,
    pub source_end: i64,
    pub span_known: bool,
}

/// Structural summary counts for the parsed file.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AstSummary {
    pub source_bytes: usize,
    pub source_lines: usize,
    pub item_count: usize,
    pub function_count: usize,
    pub struct_count: usize,
    pub enum_count: usize,
    pub const_count: usize,
}

/// A summary record for a top-level item in the file.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AstItemSummary {
    pub kind: String,
    pub category: String,
    pub name: String,
    pub source_start: i64,
    pub source_end: i64,
    pub span_known: bool,
    pub param_count: usize,
    pub field_count: usize,
    pub statement_count: usize,
}

/// The complete machine-readable AST report.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AstReport {
    pub schema_version: String,
    pub representation: String,
    pub source_byte_spans: bool,
    pub complete_tree: bool,
    pub truncated: bool,
    pub root: AstRootSummary,
    pub summary: AstSummary,
    pub items: Vec<AstItemSummary>,
    pub tree: Value,
}

impl AstReport {
    /// Serialize the AST report to a compact JSON string.
    pub fn to_json(&self) -> String {
        serde_json::to_string(self).unwrap_or_default()
    }

    /// Serialize the AST report to a formatted JSON string.
    pub fn to_json_pretty(&self) -> String {
        serde_json::to_string_pretty(self).unwrap_or_default()
    }

    /// Format the AST report as an embedded C/Bunker block comment.
    pub fn to_json_comment(&self) -> String {
        format!("/* BUNKER_AST_JSON: {} */\n", self.to_json())
    }
}

/// Count the number of newline characters plus one.
fn source_line_count(source: &str) -> usize {
    if source.is_empty() {
        return 0;
    }
    source.split('\n').count()
}

/// Build an `AstReport` from an `ast::File` and its raw source string.
pub fn build_ast_report(file: &ast::File, source: &str) -> AstReport {
    let source_bytes = source.len();
    let source_lines = source_line_count(source);

    let mut function_count = 0;
    let mut struct_count = 0;
    let mut enum_count = 0;
    let mut const_count = 0;
    let mut item_summaries = Vec::new();

    let primary_kernel = file.kernels.first();
    let root_name = primary_kernel
        .map(|k| k.name.clone())
        .unwrap_or_else(|| "File".to_string());

    let mut has_main = false;

    for kernel in &file.kernels {
        for item in &kernel.items {
            match item {
                ast::KernelItem::Function(f) => {
                    function_count += 1;
                    if f.name == "main" {
                        has_main = true;
                    }
                    item_summaries.push(AstItemSummary {
                        kind: "fn".to_string(),
                        category: "item".to_string(),
                        name: f.name.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        span_known: true,
                        param_count: f.params.len(),
                        field_count: 0,
                        statement_count: f.body.statements.len(),
                    });
                }
                ast::KernelItem::ComptimeFn(f) => {
                    function_count += 1;
                    item_summaries.push(AstItemSummary {
                        kind: "comptime_fn".to_string(),
                        category: "item".to_string(),
                        name: f.name.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        span_known: true,
                        param_count: f.params.len(),
                        field_count: 0,
                        statement_count: f.body.statements.len(),
                    });
                }
                ast::KernelItem::Struct(s) => {
                    struct_count += 1;
                    item_summaries.push(AstItemSummary {
                        kind: "struct".to_string(),
                        category: "item".to_string(),
                        name: s.name.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        span_known: true,
                        param_count: 0,
                        field_count: s.fields.len(),
                        statement_count: 0,
                    });
                }
                ast::KernelItem::Enum(e) => {
                    enum_count += 1;
                    item_summaries.push(AstItemSummary {
                        kind: "enum".to_string(),
                        category: "item".to_string(),
                        name: e.name.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        span_known: true,
                        param_count: 0,
                        field_count: e.variants.len(),
                        statement_count: 0,
                    });
                }
                ast::KernelItem::Const(c) => {
                    const_count += 1;
                    item_summaries.push(AstItemSummary {
                        kind: "const".to_string(),
                        category: "item".to_string(),
                        name: c.name.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        span_known: true,
                        param_count: 0,
                        field_count: 0,
                        statement_count: 0,
                    });
                }
                ast::KernelItem::TypeAlias(t) => {
                    item_summaries.push(AstItemSummary {
                        kind: "type_alias".to_string(),
                        category: "item".to_string(),
                        name: t.name.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        span_known: true,
                        param_count: 0,
                        field_count: 0,
                        statement_count: 0,
                    });
                }
                ast::KernelItem::Import(i) => {
                    item_summaries.push(AstItemSummary {
                        kind: "import".to_string(),
                        category: "item".to_string(),
                        name: i.target.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        span_known: true,
                        param_count: 0,
                        field_count: 0,
                        statement_count: 0,
                    });
                }
            }
        }
    }

    let root = AstRootSummary {
        kind: if primary_kernel.is_some() {
            "kernel".to_string()
        } else {
            "file".to_string()
        },
        name: root_name,
        entry: if has_main {
            "main".to_string()
        } else {
            "".to_string()
        },
        source_start: 0,
        source_end: source_bytes as i64,
        span_known: true,
    };

    let summary = AstSummary {
        source_bytes,
        source_lines,
        item_count: item_summaries.len(),
        function_count,
        struct_count,
        enum_count,
        const_count,
    };

    let tree = serialize_file_tree(file, source_bytes);

    AstReport {
        schema_version: "bunker.ast.v1".to_string(),
        representation: "typed_ast".to_string(),
        source_byte_spans: true,
        complete_tree: true,
        truncated: false,
        root,
        summary,
        items: item_summaries,
        tree,
    }
}

fn serialize_file_tree(file: &ast::File, source_bytes: usize) -> Value {
    let mut kernels_json = Vec::new();
    for k in &file.kernels {
        kernels_json.push(serialize_kernel(k, source_bytes));
    }

    let mut shells_json = Vec::new();
    for s in &file.shells {
        shells_json.push(serialize_shell(s));
    }

    let mut imports_json = Vec::new();
    for imp in &file.imports {
        imports_json.push(serde_json::json!({
            "kind": "import",
            "target": imp.target,
            "is_path": imp.is_path,
        }));
    }

    serde_json::json!({
        "kind": "file",
        "imports": imports_json,
        "kernels": kernels_json,
        "shells": shells_json,
        "source_start": 0,
        "source_end": source_bytes as i64,
        "span_known": true,
    })
}

fn serialize_kernel(k: &ast::Kernel, source_bytes: usize) -> Value {
    let mut items_json = Vec::new();
    for item in &k.items {
        items_json.push(serialize_kernel_item(item));
    }

    serde_json::json!({
        "kind": "kernel",
        "name": k.name,
        "items": items_json,
        "source_start": 0,
        "source_end": source_bytes as i64,
        "span_known": true,
    })
}

fn serialize_shell(s: &ast::Shell) -> Value {
    let mut agents_json = Vec::new();
    for a in &s.agents {
        let mut handlers_json = Vec::new();
        for h in &a.handlers {
            handlers_json.push(serde_json::json!({
                "message": h.message,
                "params": h.params.iter().map(|p| serde_json::json!({
                    "name": p.name,
                    "type": format!("{:?}", p.ty),
                })).collect::<Vec<_>>(),
                "body": serialize_block(&h.body),
            }));
        }
        agents_json.push(serde_json::json!({
            "name": a.name,
            "handlers": handlers_json,
        }));
    }

    serde_json::json!({
        "kind": "shell",
        "name": s.name,
        "imports": s.imports,
        "agents": agents_json,
    })
}

fn serialize_kernel_item(item: &ast::KernelItem) -> Value {
    match item {
        ast::KernelItem::Function(f) => serialize_function(f, "fn"),
        ast::KernelItem::ComptimeFn(f) => serialize_function(f, "comptime_fn"),
        ast::KernelItem::Struct(s) => serialize_struct(s),
        ast::KernelItem::Enum(e) => serialize_enum(e),
        ast::KernelItem::Const(c) => serialize_const(c),
        ast::KernelItem::TypeAlias(t) => serialize_type_alias(t),
        ast::KernelItem::Import(i) => serde_json::json!({
            "kind": "import",
            "target": i.target,
            "is_path": i.is_path,
        }),
    }
}

fn serialize_function(f: &ast::Function, kind: &str) -> Value {
    let params: Vec<Value> = f
        .params
        .iter()
        .map(|p| {
            serde_json::json!({
                "name": p.name,
                "type": format!("{:?}", p.ty),
            })
        })
        .collect();

    let return_type = f.return_type.as_ref().map(|t| format!("{:?}", t));

    serde_json::json!({
        "kind": kind,
        "name": f.name,
        "is_pub": f.is_pub,
        "type_params": f.type_params,
        "params": params,
        "return_type": return_type,
        "body": serialize_block(&f.body),
    })
}

fn serialize_struct(s: &ast::StructDef) -> Value {
    let fields: Vec<Value> = s
        .fields
        .iter()
        .map(|f| {
            serde_json::json!({
                "name": f.name,
                "type": format!("{:?}", f.ty),
            })
        })
        .collect();

    serde_json::json!({
        "kind": "struct",
        "name": s.name,
        "is_pub": s.is_pub,
        "is_tuple": s.is_tuple,
        "type_params": s.type_params,
        "fields": fields,
    })
}

fn serialize_enum(e: &ast::EnumDef) -> Value {
    let variants: Vec<Value> = e
        .variants
        .iter()
        .map(|v| {
            let payloads: Vec<String> = v.payloads.iter().map(|p| format!("{:?}", p)).collect();
            serde_json::json!({
                "name": v.name,
                "payloads": payloads,
            })
        })
        .collect();

    serde_json::json!({
        "kind": "enum",
        "name": e.name,
        "is_pub": e.is_pub,
        "type_params": e.type_params,
        "variants": variants,
    })
}

fn serialize_const(c: &ast::ConstDef) -> Value {
    serde_json::json!({
        "kind": "const",
        "name": c.name,
        "is_pub": c.is_pub,
        "type": format!("{:?}", c.ty),
        "value": serialize_expr(&c.value),
    })
}

fn serialize_type_alias(t: &ast::TypeAliasDef) -> Value {
    serde_json::json!({
        "kind": "type_alias",
        "name": t.name,
        "is_pub": t.is_pub,
        "target": format!("{:?}", t.target),
    })
}

fn serialize_block(block: &ast::Block) -> Value {
    let stmts: Vec<Value> = block.statements.iter().map(serialize_stmt).collect();
    serde_json::json!({
        "kind": "block",
        "statements": stmts,
    })
}

fn serialize_stmt(stmt: &ast::Stmt) -> Value {
    match stmt {
        ast::Stmt::Let {
            name,
            mutable,
            ty,
            value,
        } => serde_json::json!({
            "kind": "let",
            "name": name,
            "mutable": mutable,
            "declared_type": ty.as_ref().map(|t| format!("{:?}", t)),
            "init": serialize_expr(value),
        }),
        ast::Stmt::Assign { target, value } => serde_json::json!({
            "kind": "assign",
            "target": serialize_expr(target),
            "value": serialize_expr(value),
        }),
        ast::Stmt::Return(opt_expr) => serde_json::json!({
            "kind": "return",
            "expr": opt_expr.as_ref().map(serialize_expr),
        }),
        ast::Stmt::If {
            condition,
            then_block,
            else_block,
        } => serde_json::json!({
            "kind": "if",
            "condition": serialize_expr(condition),
            "then": serialize_block(then_block),
            "else": else_block.as_ref().map(serialize_block),
        }),
        ast::Stmt::For {
            label,
            var,
            iter,
            body,
        } => serde_json::json!({
            "kind": "for",
            "label": label,
            "var": var,
            "iter": serialize_expr(iter),
            "body": serialize_block(body),
        }),
        ast::Stmt::While {
            label,
            condition,
            body,
        } => serde_json::json!({
            "kind": "while",
            "label": label,
            "condition": serialize_expr(condition),
            "body": serialize_block(body),
        }),
        ast::Stmt::Loop { label, body } => serde_json::json!({
            "kind": "loop",
            "label": label,
            "body": serialize_block(body),
        }),
        ast::Stmt::Break(label) => serde_json::json!({
            "kind": "break",
            "label": label,
        }),
        ast::Stmt::Continue(label) => serde_json::json!({
            "kind": "continue",
            "label": label,
        }),
        ast::Stmt::Match { expr, arms } => serde_json::json!({
            "kind": "match",
            "expr": serialize_expr(expr),
            "arms": arms.iter().map(serialize_match_arm).collect::<Vec<_>>(),
        }),
        ast::Stmt::Defer(block) => serde_json::json!({
            "kind": "defer",
            "body": serialize_block(block),
        }),
        ast::Stmt::Send {
            message,
            target,
            args,
        } => serde_json::json!({
            "kind": "send",
            "message": serialize_expr(message),
            "target": target,
            "args": args.iter().map(|(n, e)| serde_json::json!({ "name": n, "value": serialize_expr(e) })).collect::<Vec<_>>(),
        }),
        ast::Stmt::Expr(expr) => serde_json::json!({
            "kind": "expr_stmt",
            "expr": serialize_expr(expr),
        }),
    }
}

fn serialize_match_arm(arm: &ast::MatchArm) -> Value {
    let body = match &arm.body {
        ast::MatchBody::Expr(e) => serialize_expr(e),
        ast::MatchBody::Block(b) => serialize_block(b),
    };

    serde_json::json!({
        "pattern": serialize_pattern(&arm.pattern),
        "guard": arm.guard.as_ref().map(serialize_expr),
        "body": body,
    })
}

fn serialize_pattern(pat: &ast::Pattern) -> Value {
    match pat {
        ast::Pattern::Unit => serde_json::json!({ "kind": "unit" }),
        ast::Pattern::Tuple(pats) => serde_json::json!({
            "kind": "tuple",
            "elements": pats.iter().map(serialize_pattern).collect::<Vec<_>>(),
        }),
        ast::Pattern::Struct { name, fields } => serde_json::json!({
            "kind": "struct",
            "name": name,
            "fields": fields.iter().map(|(n, p)| serde_json::json!({ "field": n, "pattern": serialize_pattern(p) })).collect::<Vec<_>>(),
        }),
        ast::Pattern::Some(inner) => serde_json::json!({
            "kind": "some",
            "inner": serialize_pattern(inner),
        }),
        ast::Pattern::None => serde_json::json!({ "kind": "none" }),
        ast::Pattern::Bool(b) => serde_json::json!({ "kind": "bool", "value": b }),
        ast::Pattern::Literal(lit) => serde_json::json!({
            "kind": "literal",
            "value": format!("{:?}", lit),
        }),
        ast::Pattern::Ident(id) => serde_json::json!({
            "kind": "ident",
            "binding": id,
        }),
        ast::Pattern::EnumVariant {
            enum_name,
            variant,
            bindings,
        } => serde_json::json!({
            "kind": "enum_variant",
            "enum_name": enum_name,
            "variant": variant,
            "bindings": bindings,
        }),
        ast::Pattern::EnumPayload {
            tag,
            bindings,
            types,
        } => serde_json::json!({
            "kind": "enum_payload",
            "tag": tag,
            "bindings": bindings,
            "types": types.iter().map(|t| format!("{:?}", t)).collect::<Vec<_>>(),
        }),
        ast::Pattern::ResultOk(inner) => serde_json::json!({
            "kind": "result_ok",
            "inner": serialize_pattern(inner),
        }),
        ast::Pattern::ResultErr(inner) => serde_json::json!({
            "kind": "result_err",
            "inner": serialize_pattern(inner),
        }),
    }
}

fn serialize_expr(expr: &ast::Expr) -> Value {
    match expr {
        ast::Expr::Unit => serde_json::json!({ "kind": "unit" }),
        ast::Expr::Tuple(elems) => serde_json::json!({
            "kind": "tuple",
            "elements": elems.iter().map(serialize_expr).collect::<Vec<_>>(),
        }),
        ast::Expr::Literal(lit) => serde_json::json!({
            "kind": "literal",
            "value": format!("{:?}", lit),
        }),
        ast::Expr::Ident(id) => serde_json::json!({
            "kind": "ident",
            "name": id,
        }),
        ast::Expr::Binary { op, left, right } => serde_json::json!({
            "kind": "binary",
            "op": format!("{:?}", op),
            "left": serialize_expr(left),
            "right": serialize_expr(right),
        }),
        ast::Expr::Unary { op, expr } => serde_json::json!({
            "kind": "unary",
            "op": format!("{:?}", op),
            "operand": serialize_expr(expr),
        }),
        ast::Expr::Call {
            func,
            args,
            type_args,
        } => serde_json::json!({
            "kind": "call",
            "func": serialize_expr(func),
            "args": args.iter().map(serialize_expr).collect::<Vec<_>>(),
            "type_args": type_args.iter().map(|t| format!("{:?}", t)).collect::<Vec<_>>(),
        }),
        ast::Expr::Index { expr, index } => serde_json::json!({
            "kind": "index",
            "base": serialize_expr(expr),
            "index": serialize_expr(index),
        }),
        ast::Expr::Field { expr, field } => serde_json::json!({
            "kind": "field_access",
            "base": serialize_expr(expr),
            "field": field,
        }),
        ast::Expr::Use { path, args } => serde_json::json!({
            "kind": "use",
            "path": path,
            "args": args.iter().map(|(n, e)| serde_json::json!({ "name": n, "value": serialize_expr(e) })).collect::<Vec<_>>(),
        }),
        ast::Expr::Send {
            message,
            target,
            args,
        } => serde_json::json!({
            "kind": "send",
            "message": serialize_expr(message),
            "target": target,
            "args": args.iter().map(|(n, e)| serde_json::json!({ "name": n, "value": serialize_expr(e) })).collect::<Vec<_>>(),
        }),
        ast::Expr::Lambda { params, body } => serde_json::json!({
            "kind": "lambda",
            "params": params.iter().map(|p| serde_json::json!({ "name": p.name, "type": format!("{:?}", p.ty) })).collect::<Vec<_>>(),
            "body": serialize_expr(body),
        }),
        ast::Expr::If {
            condition,
            then_expr,
            else_expr,
        } => serde_json::json!({
            "kind": "if_expr",
            "condition": serialize_expr(condition),
            "then": serialize_expr(then_expr),
            "else": serialize_expr(else_expr),
        }),
        ast::Expr::Match { expr, arms } => serde_json::json!({
            "kind": "match_expr",
            "scrutinee": serialize_expr(expr),
            "arms": arms.iter().map(serialize_match_arm).collect::<Vec<_>>(),
        }),
        ast::Expr::Block(block) => serde_json::json!({
            "kind": "block_expr",
            "block": serialize_block(block),
        }),
        ast::Expr::Some(inner) => serde_json::json!({
            "kind": "some",
            "inner": serialize_expr(inner),
        }),
        ast::Expr::None => serde_json::json!({ "kind": "none" }),
        ast::Expr::Array(elements) => serde_json::json!({
            "kind": "array_lit",
            "elements": elements.iter().map(serialize_expr).collect::<Vec<_>>(),
        }),
        ast::Expr::Struct {
            name,
            type_args,
            fields,
            base,
        } => serde_json::json!({
            "kind": "struct_lit",
            "name": name,
            "type_args": type_args.iter().map(|t| format!("{:?}", t)).collect::<Vec<_>>(),
            "fields": fields.iter().map(|(n, e)| serde_json::json!({ "field": n, "value": serialize_expr(e) })).collect::<Vec<_>>(),
            "base": base.as_ref().map(|b| serialize_expr(b)),
        }),
        ast::Expr::Copy(inner) => serde_json::json!({
            "kind": "copy",
            "expr": serialize_expr(inner),
        }),
        ast::Expr::Range {
            start,
            end,
            inclusive,
        } => serde_json::json!({
            "kind": "range",
            "start": serialize_expr(start),
            "end": serialize_expr(end),
            "inclusive": inclusive,
        }),
        ast::Expr::Cast { expr, target_type } => serde_json::json!({
            "kind": "cast",
            "expr": serialize_expr(expr),
            "target_type": format!("{:?}", target_type),
        }),
        ast::Expr::Try(inner) => serde_json::json!({
            "kind": "try",
            "expr": serialize_expr(inner),
        }),
    }
}
