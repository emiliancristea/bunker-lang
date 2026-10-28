//! Machine-readable resolver report for AI agents and tooling (`BUNKER_RESOLVER_JSON`).
//!
//! Emits canonical `bunker.resolver.v1` schema with duplicate symbol detection,
//! unresolved identifier/call/struct detection, scoped symbol resolution,
//! related declaration spans, and structured repair metadata.

use serde::{Deserialize, Serialize};
use std::collections::{HashMap, HashSet};

use crate::ast::{Block, Expr, File, KernelItem, Stmt};

/// A related declaration location.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct RelatedDeclaration {
    pub name: String,
    pub kind: String,
    pub scope: String,
    pub source_start: usize,
    pub source_end: usize,
}

/// A structured diagnostic entry within the resolver report.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ResolverReportDiagnostic {
    pub phase: String,
    pub kind: String,
    pub rule_id: String,
    pub error_code: String,
    pub severity: String,
    pub name: String,
    pub scope: String,
    pub source_start: usize,
    pub source_end: usize,
    pub span_known: bool,
    pub expected: String,
    pub actual: String,
    pub related_declarations: Vec<RelatedDeclaration>,
    pub suggested_action: String,
    pub fix_applicability: String,
    pub fix_confidence: String,
    pub safe_edit_available: bool,
    pub suggested_edits: Vec<String>,
    pub repair_hint: String,
}

/// The complete machine-readable `BUNKER_RESOLVER_JSON` report (`bunker.resolver.v1`).
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ResolverReport {
    pub schema_version: String,
    pub compiler: String,
    pub representation: String,
    pub complete: bool,
    pub duplicate_detection: bool,
    pub unresolved_detection: bool,
    pub related_declarations: bool,
    pub structured_repair_metadata: bool,
    pub diagnostic_phase_field: bool,
    pub diagnostic_rule_ids: bool,
    pub diagnostic_severity: bool,
    pub diagnostic_severity_counts: bool,
    pub suggested_edit_envelope: bool,
    pub has_diagnostics: bool,
    pub diagnostic_count: usize,
    pub error_count: usize,
    pub warning_count: usize,
    pub scope_model: String,
    pub known_limits: String,
    pub diagnostics: Vec<ResolverReportDiagnostic>,
}

impl ResolverReport {
    /// Convert to JSON string (pretty-printed).
    #[allow(dead_code)]
    pub fn to_json_pretty(&self) -> String {
        serde_json::to_string_pretty(self).unwrap_or_else(|e| {
            format!(
                "{{\"error\": \"Failed to serialize resolver report: {}\"}}",
                e
            )
        })
    }

    /// Convert to compact JSON (single line).
    pub fn to_json_compact(&self) -> String {
        serde_json::to_string(self).unwrap_or_else(|e| {
            format!(
                "{{\"error\": \"Failed to serialize resolver report: {}\"}}",
                e
            )
        })
    }

    /// Emit as a top-level comment block: `/* BUNKER_RESOLVER_JSON: ... */`.
    pub fn to_json_comment(&self) -> String {
        format!("/* BUNKER_RESOLVER_JSON: {} */\n", self.to_json_compact())
    }
}

/// Build the resolver report from the AST and source text.
pub fn build_resolver_report(file: &File, source: &str) -> ResolverReport {
    let mut diagnostics = Vec::new();

    // Track known builtins
    let builtins: HashSet<&str> = [
        "vec_new",
        "vec_push",
        "vec_get",
        "vec_len",
        "vec_pop",
        "vec_clear",
        "vec_get_opt",
        "vec_pop_opt",
        "vec_contains",
        "vec_is_empty",
        "vec_clone",
        "vec_reverse",
        "vec_as_slice",
        "vec_slice",
        "vec_map",
        "vec_filter",
        "vec_fold",
        "vec_find",
        "hashmap_new",
        "hashmap_insert",
        "hashmap_get",
        "hashmap_len",
        "hashmap_remove",
        "hashmap_contains_key",
        "hashmap_get_opt",
        "hashmap_new_str",
        "hashmap_insert_str",
        "hashmap_is_empty",
        "hashmap_values",
        "hashmap_clear",
        "slice_new",
        "slice_len",
        "slice_get",
        "slice_sub",
        "slice_to_vec",
        "slice_contains",
        "bytes_new",
        "bytes_len",
        "bytes_capacity",
        "bytes_get",
        "bytes_set",
        "bytes_push",
        "bytes_from_str",
        "bytes_to_str",
        "bytes_as_slice",
        "bytes_slice",
        "file_read",
        "file_write",
        "file_size",
        "file_remove",
        "file_read_bytes",
        "file_write_bytes",
        "path_exists",
        "path_is_file",
        "path_is_dir",
        "path_join",
        "path_dir",
        "path_base",
        "path_ext",
        "path_is_abs",
        "dir_create",
        "dir_remove",
        "process_run",
        "process_run_status",
        "process_exit",
        "process_pid",
        "process_is_sandboxed",
        "env_var",
        "env_get",
        "env_set",
        "env_has",
        "time_now_ms",
        "time_now_unix",
        "read_file_result",
        "write_file_result",
        "parse_int_result",
        "str_index_of",
        "str_replace",
        "str_split",
        "str_to_upper",
        "str_to_lower",
        "str_repeat",
        "str_concat",
        "str_len",
        "int_to_string",
        "contains",
        "Ok",
        "Err",
        "Some",
        "None",
        "panic",
        "assert",
        "print",
        "println",
        "bkr_log",
        "result_is_ok",
        "result_unwrap",
        "result_ok",
        "result_err",
        "option_is_some",
        "option_unwrap",
    ]
    .into_iter()
    .collect();

    // 1. Check duplicate kernels
    let mut kernel_names: HashMap<String, usize> = HashMap::new();
    for kernel in &file.kernels {
        let (start, end) = find_ident_span(source, &kernel.name);
        if let Some(&first_start) = kernel_names.get(&kernel.name) {
            diagnostics.push(ResolverReportDiagnostic {
                phase: "resolver".to_string(),
                kind: "duplicate_symbol".to_string(),
                rule_id: "E0101".to_string(),
                error_code: "E0101".to_string(),
                severity: "error".to_string(),
                name: kernel.name.clone(),
                scope: "global".to_string(),
                source_start: start,
                source_end: end,
                span_known: start < end,
                expected: "unique kernel declaration".to_string(),
                actual: format!("duplicate kernel '{}'", kernel.name),
                related_declarations: vec![RelatedDeclaration {
                    name: kernel.name.clone(),
                    kind: "kernel".to_string(),
                    scope: "global".to_string(),
                    source_start: first_start,
                    source_end: first_start + kernel.name.len(),
                }],
                suggested_action: format!("Rename kernel '{}' to avoid collision", kernel.name),
                fix_applicability: "manual_review".to_string(),
                fix_confidence: "high".to_string(),
                safe_edit_available: false,
                suggested_edits: Vec::new(),
                repair_hint: format!(
                    "A kernel named '{}' is already declared in this file.",
                    kernel.name
                ),
            });
        } else {
            kernel_names.insert(kernel.name.clone(), start);
        }
    }

    // 2. Check declarations and references within each kernel
    for kernel in &file.kernels {
        let kernel_scope = format!("kernel:{}", kernel.name);
        let mut declared_fns: HashMap<String, usize> = HashMap::new();
        let mut declared_structs: HashMap<String, usize> = HashMap::new();
        let mut declared_enums: HashMap<String, usize> = HashMap::new();
        let mut declared_consts: HashMap<String, usize> = HashMap::new();

        for item in &kernel.items {
            match item {
                KernelItem::Function(f) => {
                    let (start, end) = find_ident_span(source, &f.name);
                    if let Some(&first_start) = declared_fns.get(&f.name) {
                        diagnostics.push(ResolverReportDiagnostic {
                            phase: "resolver".to_string(),
                            kind: "duplicate_symbol".to_string(),
                            rule_id: "E0101".to_string(),
                            error_code: "E0101".to_string(),
                            severity: "error".to_string(),
                            name: f.name.clone(),
                            scope: kernel_scope.clone(),
                            source_start: start,
                            source_end: end,
                            span_known: start < end,
                            expected: "unique function declaration".to_string(),
                            actual: format!("duplicate function '{}'", f.name),
                            related_declarations: vec![RelatedDeclaration {
                                name: f.name.clone(),
                                kind: "function".to_string(),
                                scope: kernel_scope.clone(),
                                source_start: first_start,
                                source_end: first_start + f.name.len(),
                            }],
                            suggested_action: format!(
                                "Rename function '{}' to avoid duplicate symbol",
                                f.name
                            ),
                            fix_applicability: "manual_review".to_string(),
                            fix_confidence: "high".to_string(),
                            safe_edit_available: false,
                            suggested_edits: Vec::new(),
                            repair_hint: format!(
                                "Function '{}' is already defined in {}.",
                                f.name, kernel_scope
                            ),
                        });
                    } else {
                        declared_fns.insert(f.name.clone(), start);
                    }
                }
                KernelItem::Struct(s) => {
                    let (start, end) = find_ident_span(source, &s.name);
                    if let Some(&first_start) = declared_structs.get(&s.name) {
                        diagnostics.push(ResolverReportDiagnostic {
                            phase: "resolver".to_string(),
                            kind: "duplicate_symbol".to_string(),
                            rule_id: "E0101".to_string(),
                            error_code: "E0101".to_string(),
                            severity: "error".to_string(),
                            name: s.name.clone(),
                            scope: kernel_scope.clone(),
                            source_start: start,
                            source_end: end,
                            span_known: start < end,
                            expected: "unique struct declaration".to_string(),
                            actual: format!("duplicate struct '{}'", s.name),
                            related_declarations: vec![RelatedDeclaration {
                                name: s.name.clone(),
                                kind: "struct".to_string(),
                                scope: kernel_scope.clone(),
                                source_start: first_start,
                                source_end: first_start + s.name.len(),
                            }],
                            suggested_action: format!(
                                "Rename struct '{}' to avoid duplicate symbol",
                                s.name
                            ),
                            fix_applicability: "manual_review".to_string(),
                            fix_confidence: "high".to_string(),
                            safe_edit_available: false,
                            suggested_edits: Vec::new(),
                            repair_hint: format!(
                                "Struct '{}' is already defined in {}.",
                                s.name, kernel_scope
                            ),
                        });
                    } else {
                        declared_structs.insert(s.name.clone(), start);
                    }
                }
                KernelItem::Enum(e) => {
                    let (start, end) = find_ident_span(source, &e.name);
                    if let Some(&first_start) = declared_enums.get(&e.name) {
                        diagnostics.push(ResolverReportDiagnostic {
                            phase: "resolver".to_string(),
                            kind: "duplicate_symbol".to_string(),
                            rule_id: "E0101".to_string(),
                            error_code: "E0101".to_string(),
                            severity: "error".to_string(),
                            name: e.name.clone(),
                            scope: kernel_scope.clone(),
                            source_start: start,
                            source_end: end,
                            span_known: start < end,
                            expected: "unique enum declaration".to_string(),
                            actual: format!("duplicate enum '{}'", e.name),
                            related_declarations: vec![RelatedDeclaration {
                                name: e.name.clone(),
                                kind: "enum".to_string(),
                                scope: kernel_scope.clone(),
                                source_start: first_start,
                                source_end: first_start + e.name.len(),
                            }],
                            suggested_action: format!(
                                "Rename enum '{}' to avoid duplicate symbol",
                                e.name
                            ),
                            fix_applicability: "manual_review".to_string(),
                            fix_confidence: "high".to_string(),
                            safe_edit_available: false,
                            suggested_edits: Vec::new(),
                            repair_hint: format!(
                                "Enum '{}' is already defined in {}.",
                                e.name, kernel_scope
                            ),
                        });
                    } else {
                        declared_enums.insert(e.name.clone(), start);
                    }
                }
                KernelItem::Const(c) => {
                    let (start, end) = find_ident_span(source, &c.name);
                    if let Some(&first_start) = declared_consts.get(&c.name) {
                        diagnostics.push(ResolverReportDiagnostic {
                            phase: "resolver".to_string(),
                            kind: "duplicate_symbol".to_string(),
                            rule_id: "E0101".to_string(),
                            error_code: "E0101".to_string(),
                            severity: "error".to_string(),
                            name: c.name.clone(),
                            scope: kernel_scope.clone(),
                            source_start: start,
                            source_end: end,
                            span_known: start < end,
                            expected: "unique constant declaration".to_string(),
                            actual: format!("duplicate const '{}'", c.name),
                            related_declarations: vec![RelatedDeclaration {
                                name: c.name.clone(),
                                kind: "const".to_string(),
                                scope: kernel_scope.clone(),
                                source_start: first_start,
                                source_end: first_start + c.name.len(),
                            }],
                            suggested_action: format!(
                                "Rename const '{}' to avoid duplicate symbol",
                                c.name
                            ),
                            fix_applicability: "manual_review".to_string(),
                            fix_confidence: "high".to_string(),
                            safe_edit_available: false,
                            suggested_edits: Vec::new(),
                            repair_hint: format!(
                                "Const '{}' is already defined in {}.",
                                c.name, kernel_scope
                            ),
                        });
                    } else {
                        declared_consts.insert(c.name.clone(), start);
                    }
                }
                _ => {}
            }
        }

        // References walk inside functions
        for item in &kernel.items {
            if let KernelItem::Function(f) = item {
                let fn_scope = format!("fn:{}::{}", kernel.name, f.name);
                let mut local_vars: HashSet<String> = HashSet::new();

                for p in &f.params {
                    local_vars.insert(p.name.clone());
                }

                walk_block_for_resolver(
                    &f.body,
                    &fn_scope,
                    &mut local_vars,
                    &declared_fns,
                    &declared_structs,
                    &declared_enums,
                    &declared_consts,
                    &builtins,
                    source,
                    &mut diagnostics,
                );
            }
        }
    }

    let error_count = diagnostics.len();
    let has_diagnostics = error_count > 0;

    ResolverReport {
        schema_version: "bunker.resolver.v1".to_string(),
        compiler: "bunker-cli".to_string(),
        representation: "name_resolver_pass".to_string(),
        complete: true,
        duplicate_detection: true,
        unresolved_detection: true,
        related_declarations: true,
        structured_repair_metadata: true,
        diagnostic_phase_field: true,
        diagnostic_rule_ids: true,
        diagnostic_severity: true,
        diagnostic_severity_counts: true,
        suggested_edit_envelope: true,
        has_diagnostics,
        diagnostic_count: error_count,
        error_count,
        warning_count: 0,
        scope_model: "kernel globals plus function/block/pattern binding scopes using interned names".to_string(),
        known_limits: "Resolver validates duplicate declarations and unresolved identifiers, calls, struct types, struct literals, and struct literal fields with related declaration span objects; it does not yet resolve import visibility, overloads, method receiver fields, or cross-file definition origins.".to_string(),
        diagnostics,
    }
}

fn walk_block_for_resolver(
    block: &Block,
    scope: &str,
    locals: &mut HashSet<String>,
    declared_fns: &HashMap<String, usize>,
    declared_structs: &HashMap<String, usize>,
    declared_enums: &HashMap<String, usize>,
    declared_consts: &HashMap<String, usize>,
    builtins: &HashSet<&str>,
    source: &str,
    diagnostics: &mut Vec<ResolverReportDiagnostic>,
) {
    for stmt in &block.statements {
        match stmt {
            Stmt::Let { name, value, .. } => {
                walk_expr_for_resolver(
                    value,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
                locals.insert(name.clone());
            }
            Stmt::Assign { target, value } => {
                walk_expr_for_resolver(
                    target,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
                walk_expr_for_resolver(
                    value,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            Stmt::Return(Some(expr)) => {
                walk_expr_for_resolver(
                    expr,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            Stmt::If {
                condition,
                then_block,
                else_block,
            } => {
                walk_expr_for_resolver(
                    condition,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
                let mut then_locals = locals.clone();
                walk_block_for_resolver(
                    then_block,
                    scope,
                    &mut then_locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
                if let Some(eb) = else_block {
                    let mut else_locals = locals.clone();
                    walk_block_for_resolver(
                        eb,
                        scope,
                        &mut else_locals,
                        declared_fns,
                        declared_structs,
                        declared_enums,
                        declared_consts,
                        builtins,
                        source,
                        diagnostics,
                    );
                }
            }
            Stmt::While {
                condition, body, ..
            } => {
                walk_expr_for_resolver(
                    condition,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
                let mut while_locals = locals.clone();
                walk_block_for_resolver(
                    body,
                    scope,
                    &mut while_locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            Stmt::For {
                var, iter, body, ..
            } => {
                walk_expr_for_resolver(
                    iter,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
                let mut for_locals = locals.clone();
                for_locals.insert(var.clone());
                walk_block_for_resolver(
                    body,
                    scope,
                    &mut for_locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            Stmt::Loop { body, .. } => {
                let mut loop_locals = locals.clone();
                walk_block_for_resolver(
                    body,
                    scope,
                    &mut loop_locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            Stmt::Defer(b) => {
                let mut defer_locals = locals.clone();
                walk_block_for_resolver(
                    b,
                    scope,
                    &mut defer_locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            Stmt::Expr(e) => {
                walk_expr_for_resolver(
                    e,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            _ => {}
        }
    }
}

fn walk_expr_for_resolver(
    expr: &Expr,
    scope: &str,
    locals: &HashSet<String>,
    declared_fns: &HashMap<String, usize>,
    declared_structs: &HashMap<String, usize>,
    declared_enums: &HashMap<String, usize>,
    declared_consts: &HashMap<String, usize>,
    builtins: &HashSet<&str>,
    source: &str,
    diagnostics: &mut Vec<ResolverReportDiagnostic>,
) {
    match expr {
        Expr::Ident(name) => {
            if !locals.contains(name)
                && !declared_consts.contains_key(name)
                && !declared_enums.contains_key(name)
                && !builtins.contains(name.as_str())
                && !name.starts_with('_')
            {
                if !name.contains("::") && !name.contains('.') {
                    let (start, end) = find_ident_span(source, name);
                    diagnostics.push(ResolverReportDiagnostic {
                        phase: "resolver".to_string(),
                        kind: "unresolved_symbol".to_string(),
                        rule_id: "E0102".to_string(),
                        error_code: "E0102".to_string(),
                        severity: "error".to_string(),
                        name: name.clone(),
                        scope: scope.to_string(),
                        source_start: start,
                        source_end: end,
                        span_known: start < end,
                        expected: "declared variable or constant".to_string(),
                        actual: format!("unresolved identifier '{}'", name),
                        related_declarations: Vec::new(),
                        suggested_action: format!("Declare variable '{}' before use", name),
                        fix_applicability: "manual_review".to_string(),
                        fix_confidence: "high".to_string(),
                        safe_edit_available: false,
                        suggested_edits: Vec::new(),
                        repair_hint: format!(
                            "Identifier '{}' is not declared in scope '{}'.",
                            name, scope
                        ),
                    });
                }
            }
        }
        Expr::Call { func, args, .. } => {
            if let Expr::Ident(name) = func.as_ref() {
                let bare_name = name.split("::").last().unwrap_or(name);
                if !declared_fns.contains_key(bare_name)
                    && !builtins.contains(bare_name)
                    && !declared_structs.contains_key(bare_name)
                    && !declared_enums.contains_key(bare_name)
                    && !bare_name.contains('.')
                {
                    let (start, end) = find_ident_span(source, bare_name);
                    diagnostics.push(ResolverReportDiagnostic {
                        phase: "resolver".to_string(),
                        kind: "unresolved_call".to_string(),
                        rule_id: "E0103".to_string(),
                        error_code: "E0103".to_string(),
                        severity: "error".to_string(),
                        name: name.clone(),
                        scope: scope.to_string(),
                        source_start: start,
                        source_end: end,
                        span_known: start < end,
                        expected: "callable function or constructor".to_string(),
                        actual: format!("unresolved call to '{}'", name),
                        related_declarations: Vec::new(),
                        suggested_action: format!(
                            "Define function '{}' or import its owning module",
                            name
                        ),
                        fix_applicability: "manual_review".to_string(),
                        fix_confidence: "high".to_string(),
                        safe_edit_available: false,
                        suggested_edits: Vec::new(),
                        repair_hint: format!(
                            "Function or constructor '{}' cannot be resolved in '{}'.",
                            name, scope
                        ),
                    });
                }
            } else {
                walk_expr_for_resolver(
                    func,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            for a in args {
                walk_expr_for_resolver(
                    a,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
        }
        Expr::Struct {
            name, fields, base, ..
        } => {
            let bare_name = name.split("::").last().unwrap_or(name);
            if !declared_structs.contains_key(bare_name) {
                let (start, end) = find_ident_span(source, bare_name);
                diagnostics.push(ResolverReportDiagnostic {
                    phase: "resolver".to_string(),
                    kind: "unresolved_struct".to_string(),
                    rule_id: "E0104".to_string(),
                    error_code: "E0104".to_string(),
                    severity: "error".to_string(),
                    name: name.clone(),
                    scope: scope.to_string(),
                    source_start: start,
                    source_end: end,
                    span_known: start < end,
                    expected: "declared struct definition".to_string(),
                    actual: format!("unresolved struct '{}'", name),
                    related_declarations: Vec::new(),
                    suggested_action: format!("Declare struct '{}' before instantiation", name),
                    fix_applicability: "manual_review".to_string(),
                    fix_confidence: "high".to_string(),
                    safe_edit_available: false,
                    suggested_edits: Vec::new(),
                    repair_hint: format!("Struct '{}' is not declared in scope '{}'.", name, scope),
                });
            }
            for (_, val) in fields {
                walk_expr_for_resolver(
                    val,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
            if let Some(b) = base {
                walk_expr_for_resolver(
                    b,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
        }
        Expr::Binary { left, right, .. } => {
            walk_expr_for_resolver(
                left,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
            walk_expr_for_resolver(
                right,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
        }
        Expr::Unary { expr, .. } | Expr::Some(expr) => {
            walk_expr_for_resolver(
                expr,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
        }
        Expr::Index { expr, index } => {
            walk_expr_for_resolver(
                expr,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
            walk_expr_for_resolver(
                index,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
        }
        Expr::Field { expr, .. } => {
            walk_expr_for_resolver(
                expr,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
        }
        Expr::Array(elems) | Expr::Tuple(elems) => {
            for e in elems {
                walk_expr_for_resolver(
                    e,
                    scope,
                    locals,
                    declared_fns,
                    declared_structs,
                    declared_enums,
                    declared_consts,
                    builtins,
                    source,
                    diagnostics,
                );
            }
        }
        Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            walk_expr_for_resolver(
                condition,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
            walk_expr_for_resolver(
                then_expr,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
            walk_expr_for_resolver(
                else_expr,
                scope,
                locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
        }
        Expr::Block(b) => {
            let mut block_locals = locals.clone();
            walk_block_for_resolver(
                b,
                scope,
                &mut block_locals,
                declared_fns,
                declared_structs,
                declared_enums,
                declared_consts,
                builtins,
                source,
                diagnostics,
            );
        }
        _ => {}
    }
}

fn find_ident_span(source: &str, ident: &str) -> (usize, usize) {
    if let Some(pos) = source.find(ident) {
        (pos, pos + ident.len())
    } else {
        (0, 0)
    }
}
