//! Machine-readable typecheck report for AI agents and tooling (`BUNKER_TYPECHECK_JSON`).
//!
//! Emits canonical `bunker.typecheck.v1` schema with full semantic validation capability
//! flags, diagnostic counts, and structured diagnostics with exact source spans,
//! expected/found type objects, and actionable repair hints.

use serde::{Deserialize, Serialize};

use crate::ast::File;
use crate::diagnostic::{type_error_to_diagnostic_with_source, Diagnostic};
use crate::typeck::TypeError;

/// A structured diagnostic entry within the typecheck report.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct TypecheckReportDiagnostic {
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
    pub found: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub expected_type: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub found_type: Option<String>,
    pub suggested_action: String,
    pub fix_applicability: String,
    pub fix_confidence: String,
    pub safe_edit_available: bool,
    pub suggested_edits: Vec<String>,
    pub repair_hint: String,
}

/// The complete machine-readable `BUNKER_TYPECHECK_JSON` report (`bunker.typecheck.v1`).
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct TypecheckReport {
    pub schema_version: String,
    pub compiler: String,
    pub representation: String,
    pub complete: bool,
    pub annotation_checks: bool,
    pub return_checks: bool,
    pub condition_checks: bool,
    pub call_argument_checks: bool,
    pub call_arity_checks: bool,
    pub call_target_checks: bool,
    pub builtin_arity_checks: bool,
    pub builtin_argument_type_checks: bool,
    pub entry_point_checks: bool,
    pub entry_signature_checks: bool,
    pub assignment_target_checks: bool,
    pub const_assignment_checks: bool,
    pub struct_field_value_checks: bool,
    pub struct_field_shape_checks: bool,
    pub ambiguous_empty_array_checks: bool,
    pub ambiguous_none_checks: bool,
    pub ambiguous_result_constructor_checks: bool,
    pub ambiguous_collection_constructor_checks: bool,
    pub index_base_type_checks: bool,
    pub index_type_checks: bool,
    pub binary_operand_checks: bool,
    pub unary_operand_checks: bool,
    pub field_access_base_checks: bool,
    pub ternary_branch_checks: bool,
    pub match_arm_type_checks: bool,
    pub match_pattern_type_checks: bool,
    pub match_pattern_semantic_checks: bool,
    pub bool_match_exhaustiveness_checks: bool,
    pub option_match_exhaustiveness_checks: bool,
    pub result_match_exhaustiveness_checks: bool,
    pub enum_match_exhaustiveness_checks: bool,
    pub scalar_match_exhaustiveness_checks: bool,
    pub finite_match_redundancy_checks: bool,
    pub array_element_type_checks: bool,
    pub loop_control_checks: bool,
    pub return_path_checks: bool,
    pub unreachable_code_checks: bool,
    pub void_value_checks: bool,
    pub compound_void_value_checks: bool,
    pub full_value_context_void_checks: bool,
    pub typed_diagnostic_context: bool,
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
    pub known_limits: String,
    pub diagnostics: Vec<TypecheckReportDiagnostic>,
}

impl TypecheckReport {
    /// Convert to JSON string (pretty-printed).
    #[allow(dead_code)]
    pub fn to_json_pretty(&self) -> String {
        serde_json::to_string_pretty(self).unwrap_or_else(|e| {
            format!(
                "{{\"error\": \"Failed to serialize typecheck report: {}\"}}",
                e
            )
        })
    }

    /// Convert to compact JSON (single line).
    pub fn to_json_compact(&self) -> String {
        serde_json::to_string(self).unwrap_or_else(|e| {
            format!(
                "{{\"error\": \"Failed to serialize typecheck report: {}\"}}",
                e
            )
        })
    }

    /// Emit as a top-level comment block: `/* BUNKER_TYPECHECK_JSON: ... */`.
    pub fn to_json_comment(&self) -> String {
        format!("/* BUNKER_TYPECHECK_JSON: {} */\n", self.to_json_compact())
    }
}

/// Build the typecheck report from the AST and collected type errors.
pub fn build_typecheck_report(
    _file: &File,
    source: &str,
    type_errors: &[TypeError],
) -> TypecheckReport {
    let mut diagnostics = Vec::new();

    for err in type_errors {
        let diag: Diagnostic =
            type_error_to_diagnostic_with_source(err, "source.bkr", Some(source));

        let (source_start, source_end, span_known) =
            if let (Some(line), Some(col)) = (diag.location.line, diag.location.column) {
                let offset = line_col_to_byte_offset(source, line, col);
                let len = diag.location.span_length.unwrap_or(1) as usize;
                (offset, offset + len, true)
            } else {
                (0, 0, false)
            };

        let kind = if diag.error_code == "E0201" {
            "type_mismatch".to_string()
        } else if diag.error_code == "E0202" {
            "undefined_variable".to_string()
        } else if diag.error_code == "E0203" {
            "undefined_function".to_string()
        } else if diag.error_code == "E0204" {
            "arity_mismatch".to_string()
        } else {
            diag.error_code.to_lowercase()
        };

        let expected_desc = diag
            .expected
            .as_ref()
            .map(|e| e.type_name.clone())
            .unwrap_or_else(|| "valid type".to_string());

        let found_desc = diag
            .found
            .as_ref()
            .map(|f| f.type_name.clone())
            .unwrap_or_else(|| "mismatched type".to_string());

        let repair_hint = diag
            .ai_prompt_hint
            .clone()
            .unwrap_or_else(|| err.message.clone());

        diagnostics.push(TypecheckReportDiagnostic {
            phase: "typecheck".to_string(),
            kind,
            rule_id: diag.error_code.clone(),
            error_code: diag.error_code.clone(),
            severity: "error".to_string(),
            name: err.location.clone(),
            scope: format!("function:{}", err.location),
            source_start,
            source_end,
            span_known,
            expected: expected_desc,
            found: found_desc,
            expected_type: diag.expected.map(|e| e.type_name),
            found_type: diag.found.map(|f| f.type_name),
            suggested_action: repair_hint.clone(),
            fix_applicability: "manual_review".to_string(),
            fix_confidence: "medium".to_string(),
            safe_edit_available: false,
            suggested_edits: Vec::new(),
            repair_hint,
        });
    }

    let error_count = diagnostics.len();
    let has_diagnostics = error_count > 0;

    TypecheckReport {
        schema_version: "bunker.typecheck.v1".to_string(),
        compiler: "bunker-cli".to_string(),
        representation: "typecheck_diagnostics_pass".to_string(),
        complete: true,
        annotation_checks: true,
        return_checks: true,
        condition_checks: true,
        call_argument_checks: true,
        call_arity_checks: true,
        call_target_checks: true,
        builtin_arity_checks: true,
        builtin_argument_type_checks: true,
        entry_point_checks: true,
        entry_signature_checks: true,
        assignment_target_checks: true,
        const_assignment_checks: true,
        struct_field_value_checks: true,
        struct_field_shape_checks: true,
        ambiguous_empty_array_checks: true,
        ambiguous_none_checks: true,
        ambiguous_result_constructor_checks: true,
        ambiguous_collection_constructor_checks: true,
        index_base_type_checks: true,
        index_type_checks: true,
        binary_operand_checks: true,
        unary_operand_checks: true,
        field_access_base_checks: true,
        ternary_branch_checks: true,
        match_arm_type_checks: true,
        match_pattern_type_checks: true,
        match_pattern_semantic_checks: true,
        bool_match_exhaustiveness_checks: true,
        option_match_exhaustiveness_checks: true,
        result_match_exhaustiveness_checks: true,
        enum_match_exhaustiveness_checks: true,
        scalar_match_exhaustiveness_checks: true,
        finite_match_redundancy_checks: true,
        array_element_type_checks: true,
        loop_control_checks: true,
        return_path_checks: true,
        unreachable_code_checks: true,
        void_value_checks: true,
        compound_void_value_checks: true,
        full_value_context_void_checks: true,
        typed_diagnostic_context: true,
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
        known_limits: "Typecheck report validates declared annotations, return values and return paths, conditions, ternary branches, match patterns and arm values, array elements, loop-control context, unreachable statements, assignments, index bases/expressions, field-access bases, unary/binary operands, call arguments, call targets, builtin argument types, entry-point presence/signature, and struct literal field values/shapes.".to_string(),
        diagnostics,
    }
}

fn line_col_to_byte_offset(source: &str, target_line: u32, target_col: u32) -> usize {
    let mut current_line = 1;
    let mut current_col = 1;
    for (offset, ch) in source.char_indices() {
        if current_line == target_line && current_col == target_col {
            return offset;
        }
        if ch == '\n' {
            current_line += 1;
            current_col = 1;
        } else {
            current_col += 1;
        }
    }
    source.len()
}
