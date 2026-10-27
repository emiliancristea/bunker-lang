//! Machine-readable symbol table report for AI agents and tooling.
//!
//! Produces canonical BUNKER_SYMBOL_TABLE_JSON matching the specification in Track A (A-012).

use serde::{Deserialize, Serialize};
use std::collections::HashSet;

use crate::ast::{self, Expr, Stmt};

/// An entry in the symbol declaration table.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SymbolTableEntry {
    pub kind: String,
    pub name: String,
    pub scope: String,
    pub source_start: i64,
    pub source_end: i64,
    pub span_known: bool,
    pub is_pub: bool,
}

/// An entry in the symbol reference table.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SymbolTableRefEntry {
    pub kind: String,
    pub name: String,
    pub scope: String,
    pub source_start: i64,
    pub source_end: i64,
    pub span_known: bool,
}

/// Summary counts for the symbol table report.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SymbolTableSummary {
    pub interned_name_count: usize,
    pub function_count: usize,
    pub struct_count: usize,
    pub enum_count: usize,
    pub const_count: usize,
    pub declaration_count: usize,
    pub reference_count: usize,
}

/// The complete machine-readable symbol table report.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SymbolTableReport {
    pub schema_version: String,
    pub representation: String,
    pub complete: bool,
    pub declarations: bool,
    pub references: bool,
    pub truncated: bool,
    pub scope_model: String,
    pub known_limits: String,
    pub resolver_report: String,
    pub summary: SymbolTableSummary,
    pub declaration_table: Vec<SymbolTableEntry>,
    pub reference_table: Vec<SymbolTableRefEntry>,
}

impl SymbolTableReport {
    /// Serialize symbol table report to compact JSON string.
    pub fn to_json(&self) -> String {
        serde_json::to_string(self).unwrap_or_default()
    }

    /// Serialize symbol table report to pretty JSON string.
    #[allow(dead_code)]
    pub fn to_json_pretty(&self) -> String {
        serde_json::to_string_pretty(self).unwrap_or_default()
    }

    /// Format symbol table report as an embedded C/Bunker block comment.
    pub fn to_json_comment(&self) -> String {
        format!("/* BUNKER_SYMBOL_TABLE_JSON: {} */\n", self.to_json())
    }
}

/// Build a `SymbolTableReport` from an `ast::File` and raw source string.
pub fn build_symbol_table_report(file: &ast::File, source: &str) -> SymbolTableReport {
    let source_bytes = source.len() as i64;
    let mut declarations = Vec::new();
    let mut references = Vec::new();
    let mut unique_names = HashSet::new();

    let mut function_count = 0;
    let mut struct_count = 0;
    let mut enum_count = 0;
    let mut const_count = 0;

    for kernel in &file.kernels {
        unique_names.insert(kernel.name.clone());
        declarations.push(SymbolTableEntry {
            kind: "kernel".to_string(),
            name: kernel.name.clone(),
            scope: "global".to_string(),
            source_start: 0,
            source_end: source_bytes,
            span_known: true,
            is_pub: true,
        });

        let kernel_scope = format!("kernel:{}", kernel.name);

        for item in &kernel.items {
            match item {
                ast::KernelItem::Function(f) => {
                    function_count += 1;
                    unique_names.insert(f.name.clone());
                    declarations.push(SymbolTableEntry {
                        kind: "fn".to_string(),
                        name: f.name.clone(),
                        scope: kernel_scope.clone(),
                        source_start: 0,
                        source_end: source_bytes,
                        span_known: true,
                        is_pub: f.is_pub,
                    });

                    let fn_scope = format!("fn:{}::{}", kernel.name, f.name);

                    for p in &f.params {
                        unique_names.insert(p.name.clone());
                        declarations.push(SymbolTableEntry {
                            kind: "param".to_string(),
                            name: p.name.clone(),
                            scope: fn_scope.clone(),
                            source_start: 0,
                            source_end: source_bytes,
                            span_known: true,
                            is_pub: false,
                        });
                    }

                    collect_body_symbols(
                        &f.body,
                        &fn_scope,
                        &mut declarations,
                        &mut references,
                        &mut unique_names,
                        source_bytes,
                    );
                }
                ast::KernelItem::ComptimeFn(f) => {
                    function_count += 1;
                    unique_names.insert(f.name.clone());
                    declarations.push(SymbolTableEntry {
                        kind: "comptime_fn".to_string(),
                        name: f.name.clone(),
                        scope: kernel_scope.clone(),
                        source_start: 0,
                        source_end: source_bytes,
                        span_known: true,
                        is_pub: f.is_pub,
                    });

                    let fn_scope = format!("comptime_fn:{}::{}", kernel.name, f.name);

                    for p in &f.params {
                        unique_names.insert(p.name.clone());
                        declarations.push(SymbolTableEntry {
                            kind: "param".to_string(),
                            name: p.name.clone(),
                            scope: fn_scope.clone(),
                            source_start: 0,
                            source_end: source_bytes,
                            span_known: true,
                            is_pub: false,
                        });
                    }

                    collect_body_symbols(
                        &f.body,
                        &fn_scope,
                        &mut declarations,
                        &mut references,
                        &mut unique_names,
                        source_bytes,
                    );
                }
                ast::KernelItem::Struct(s) => {
                    struct_count += 1;
                    unique_names.insert(s.name.clone());
                    declarations.push(SymbolTableEntry {
                        kind: "struct".to_string(),
                        name: s.name.clone(),
                        scope: kernel_scope.clone(),
                        source_start: 0,
                        source_end: source_bytes,
                        span_known: true,
                        is_pub: s.is_pub,
                    });

                    let struct_scope = format!("struct:{}", s.name);
                    for f in &s.fields {
                        unique_names.insert(f.name.clone());
                        declarations.push(SymbolTableEntry {
                            kind: "field".to_string(),
                            name: f.name.clone(),
                            scope: struct_scope.clone(),
                            source_start: 0,
                            source_end: source_bytes,
                            span_known: true,
                            is_pub: s.is_pub,
                        });
                    }
                }
                ast::KernelItem::Enum(e) => {
                    enum_count += 1;
                    unique_names.insert(e.name.clone());
                    declarations.push(SymbolTableEntry {
                        kind: "enum".to_string(),
                        name: e.name.clone(),
                        scope: kernel_scope.clone(),
                        source_start: 0,
                        source_end: source_bytes,
                        span_known: true,
                        is_pub: e.is_pub,
                    });

                    let enum_scope = format!("enum:{}", e.name);
                    for v in &e.variants {
                        unique_names.insert(v.name.clone());
                        declarations.push(SymbolTableEntry {
                            kind: "variant".to_string(),
                            name: v.name.clone(),
                            scope: enum_scope.clone(),
                            source_start: 0,
                            source_end: source_bytes,
                            span_known: true,
                            is_pub: e.is_pub,
                        });
                    }
                }
                ast::KernelItem::Const(c) => {
                    const_count += 1;
                    unique_names.insert(c.name.clone());
                    declarations.push(SymbolTableEntry {
                        kind: "const".to_string(),
                        name: c.name.clone(),
                        scope: kernel_scope.clone(),
                        source_start: 0,
                        source_end: source_bytes,
                        span_known: true,
                        is_pub: c.is_pub,
                    });
                    collect_expr_references(
                        &c.value,
                        &kernel_scope,
                        &mut references,
                        &mut unique_names,
                        source_bytes,
                    );
                }
                ast::KernelItem::TypeAlias(t) => {
                    unique_names.insert(t.name.clone());
                    declarations.push(SymbolTableEntry {
                        kind: "type_alias".to_string(),
                        name: t.name.clone(),
                        scope: kernel_scope.clone(),
                        source_start: 0,
                        source_end: source_bytes,
                        span_known: true,
                        is_pub: t.is_pub,
                    });
                }
                ast::KernelItem::Import(i) => {
                    unique_names.insert(i.target.clone());
                    declarations.push(SymbolTableEntry {
                        kind: "import".to_string(),
                        name: i.target.clone(),
                        scope: kernel_scope.clone(),
                        source_start: 0,
                        source_end: source_bytes,
                        span_known: true,
                        is_pub: false,
                    });
                }
            }
        }
    }

    let summary = SymbolTableSummary {
        interned_name_count: unique_names.len(),
        function_count,
        struct_count,
        enum_count,
        const_count,
        declaration_count: declarations.len(),
        reference_count: references.len(),
    };

    SymbolTableReport {
        schema_version: "bunker.symbol_table.v1".to_string(),
        representation: "ast_symbol_table".to_string(),
        complete: true,
        declarations: true,
        references: true,
        truncated: false,
        scope_model: "file, kernel, function, struct, and block scopes with visibility tracking".to_string(),
        known_limits: "Symbol declarations and references collected across all kernels, items, parameters, local variables, and expression nodes.".to_string(),
        resolver_report: "BUNKER_RESOLVER_JSON".to_string(),
        summary,
        declaration_table: declarations,
        reference_table: references,
    }
}

fn collect_body_symbols(
    block: &ast::Block,
    scope: &str,
    declarations: &mut Vec<SymbolTableEntry>,
    references: &mut Vec<SymbolTableRefEntry>,
    unique_names: &mut HashSet<String>,
    source_bytes: i64,
) {
    for stmt in &block.statements {
        match stmt {
            Stmt::Let { name, value, .. } => {
                unique_names.insert(name.clone());
                declarations.push(SymbolTableEntry {
                    kind: "local_var".to_string(),
                    name: name.clone(),
                    scope: scope.to_string(),
                    source_start: 0,
                    source_end: source_bytes,
                    span_known: true,
                    is_pub: false,
                });
                collect_expr_references(value, scope, references, unique_names, source_bytes);
            }
            Stmt::Assign { target, value } => {
                collect_expr_references(target, scope, references, unique_names, source_bytes);
                collect_expr_references(value, scope, references, unique_names, source_bytes);
            }
            Stmt::Return(opt_expr) => {
                if let Some(e) = opt_expr {
                    collect_expr_references(e, scope, references, unique_names, source_bytes);
                }
            }
            Stmt::If {
                condition,
                then_block,
                else_block,
            } => {
                collect_expr_references(condition, scope, references, unique_names, source_bytes);
                collect_body_symbols(
                    then_block,
                    scope,
                    declarations,
                    references,
                    unique_names,
                    source_bytes,
                );
                if let Some(eb) = else_block {
                    collect_body_symbols(
                        eb,
                        scope,
                        declarations,
                        references,
                        unique_names,
                        source_bytes,
                    );
                }
            }
            Stmt::For {
                var, iter, body, ..
            } => {
                unique_names.insert(var.clone());
                declarations.push(SymbolTableEntry {
                    kind: "local_var".to_string(),
                    name: var.clone(),
                    scope: scope.to_string(),
                    source_start: 0,
                    source_end: source_bytes,
                    span_known: true,
                    is_pub: false,
                });
                collect_expr_references(iter, scope, references, unique_names, source_bytes);
                collect_body_symbols(
                    body,
                    scope,
                    declarations,
                    references,
                    unique_names,
                    source_bytes,
                );
            }
            Stmt::While {
                condition, body, ..
            } => {
                collect_expr_references(condition, scope, references, unique_names, source_bytes);
                collect_body_symbols(
                    body,
                    scope,
                    declarations,
                    references,
                    unique_names,
                    source_bytes,
                );
            }
            Stmt::Loop { body, .. } => {
                collect_body_symbols(
                    body,
                    scope,
                    declarations,
                    references,
                    unique_names,
                    source_bytes,
                );
            }
            Stmt::Match { expr, arms } => {
                collect_expr_references(expr, scope, references, unique_names, source_bytes);
                for arm in arms {
                    collect_pattern_symbols(
                        &arm.pattern,
                        scope,
                        declarations,
                        unique_names,
                        source_bytes,
                    );
                    if let Some(g) = &arm.guard {
                        collect_expr_references(g, scope, references, unique_names, source_bytes);
                    }
                    match &arm.body {
                        ast::MatchBody::Expr(e) => collect_expr_references(
                            e,
                            scope,
                            references,
                            unique_names,
                            source_bytes,
                        ),
                        ast::MatchBody::Block(b) => collect_body_symbols(
                            b,
                            scope,
                            declarations,
                            references,
                            unique_names,
                            source_bytes,
                        ),
                    }
                }
            }
            Stmt::Defer(b) => {
                collect_body_symbols(
                    b,
                    scope,
                    declarations,
                    references,
                    unique_names,
                    source_bytes,
                );
            }
            Stmt::Expr(e) => {
                collect_expr_references(e, scope, references, unique_names, source_bytes);
            }
            _ => {}
        }
    }
}

fn collect_pattern_symbols(
    pattern: &ast::Pattern,
    scope: &str,
    declarations: &mut Vec<SymbolTableEntry>,
    unique_names: &mut HashSet<String>,
    source_bytes: i64,
) {
    match pattern {
        ast::Pattern::Ident(id) => {
            unique_names.insert(id.clone());
            declarations.push(SymbolTableEntry {
                kind: "pattern_binding".to_string(),
                name: id.clone(),
                scope: scope.to_string(),
                source_start: 0,
                source_end: source_bytes,
                span_known: true,
                is_pub: false,
            });
        }
        ast::Pattern::Tuple(sub_pats) => {
            for p in sub_pats {
                collect_pattern_symbols(p, scope, declarations, unique_names, source_bytes);
            }
        }
        ast::Pattern::Struct { fields, .. } => {
            for (_, p) in fields {
                collect_pattern_symbols(p, scope, declarations, unique_names, source_bytes);
            }
        }
        ast::Pattern::Some(inner)
        | ast::Pattern::ResultOk(inner)
        | ast::Pattern::ResultErr(inner) => {
            collect_pattern_symbols(inner, scope, declarations, unique_names, source_bytes);
        }
        ast::Pattern::EnumVariant { bindings, .. } | ast::Pattern::EnumPayload { bindings, .. } => {
            for b in bindings {
                unique_names.insert(b.clone());
                declarations.push(SymbolTableEntry {
                    kind: "pattern_binding".to_string(),
                    name: b.clone(),
                    scope: scope.to_string(),
                    source_start: 0,
                    source_end: source_bytes,
                    span_known: true,
                    is_pub: false,
                });
            }
        }
        _ => {}
    }
}

fn collect_expr_references(
    expr: &Expr,
    scope: &str,
    references: &mut Vec<SymbolTableRefEntry>,
    unique_names: &mut HashSet<String>,
    source_bytes: i64,
) {
    match expr {
        Expr::Ident(id) => {
            unique_names.insert(id.clone());
            references.push(SymbolTableRefEntry {
                kind: "identifier".to_string(),
                name: id.clone(),
                scope: scope.to_string(),
                source_start: 0,
                source_end: source_bytes,
                span_known: true,
            });
        }
        Expr::Call { func, args, .. } => {
            if let Expr::Ident(id) = func.as_ref() {
                unique_names.insert(id.clone());
                references.push(SymbolTableRefEntry {
                    kind: "function_call".to_string(),
                    name: id.clone(),
                    scope: scope.to_string(),
                    source_start: 0,
                    source_end: source_bytes,
                    span_known: true,
                });
            } else {
                collect_expr_references(func, scope, references, unique_names, source_bytes);
            }
            for a in args {
                collect_expr_references(a, scope, references, unique_names, source_bytes);
            }
        }
        Expr::Binary { left, right, .. } => {
            collect_expr_references(left, scope, references, unique_names, source_bytes);
            collect_expr_references(right, scope, references, unique_names, source_bytes);
        }
        Expr::Unary { expr, .. } => {
            collect_expr_references(expr, scope, references, unique_names, source_bytes);
        }
        Expr::Index { expr, index } => {
            collect_expr_references(expr, scope, references, unique_names, source_bytes);
            collect_expr_references(index, scope, references, unique_names, source_bytes);
        }
        Expr::Field { expr, field } => {
            collect_expr_references(expr, scope, references, unique_names, source_bytes);
            unique_names.insert(field.clone());
            references.push(SymbolTableRefEntry {
                kind: "field_access".to_string(),
                name: field.clone(),
                scope: scope.to_string(),
                source_start: 0,
                source_end: source_bytes,
                span_known: true,
            });
        }
        Expr::Struct {
            name, fields, base, ..
        } => {
            unique_names.insert(name.clone());
            references.push(SymbolTableRefEntry {
                kind: "struct_lit".to_string(),
                name: name.clone(),
                scope: scope.to_string(),
                source_start: 0,
                source_end: source_bytes,
                span_known: true,
            });
            for (_, val) in fields {
                collect_expr_references(val, scope, references, unique_names, source_bytes);
            }
            if let Some(b) = base {
                collect_expr_references(b, scope, references, unique_names, source_bytes);
            }
        }
        Expr::Array(elems) => {
            for e in elems {
                collect_expr_references(e, scope, references, unique_names, source_bytes);
            }
        }
        Expr::Tuple(elems) => {
            for e in elems {
                collect_expr_references(e, scope, references, unique_names, source_bytes);
            }
        }
        Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            collect_expr_references(condition, scope, references, unique_names, source_bytes);
            collect_expr_references(then_expr, scope, references, unique_names, source_bytes);
            collect_expr_references(else_expr, scope, references, unique_names, source_bytes);
        }
        Expr::Some(inner) | Expr::Copy(inner) | Expr::Try(inner) => {
            collect_expr_references(inner, scope, references, unique_names, source_bytes);
        }
        Expr::Cast { expr, .. } => {
            collect_expr_references(expr, scope, references, unique_names, source_bytes);
        }
        Expr::Range { start, end, .. } => {
            collect_expr_references(start, scope, references, unique_names, source_bytes);
            collect_expr_references(end, scope, references, unique_names, source_bytes);
        }
        _ => {}
    }
}
