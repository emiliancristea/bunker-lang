//! Compiler capability report for AI agents and tooling.
//!
//! Produces machine-readable BUNKER_CAPABILITY_JSON describing supported language
//! constructs, compiler versioning, diagnostic codes, and bootstrap limits.

use serde::{Deserialize, Serialize};

use crate::diagnostic::codes;

/// A registered compiler diagnostic code with phase and category metadata.
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq)]
pub struct DiagnosticCodeEntry {
    pub code: String,
    pub phase: String,
    pub category: String,
    pub description: String,
}

/// The complete machine-readable compiler capability report.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct CapabilityReport {
    pub schema_version: String,
    pub compiler: String,
    pub agent_contract_version: String,
    pub self_hosting_stage: String,
    pub ai_agent_native_diagnostics: bool,
    pub production_language_ready: bool,
    pub requires_ci_validation: bool,
    pub source_byte_spans: bool,
    pub source_excerpts: bool,
    pub structured_repair_metadata: bool,
    pub structured_parse_diagnostics: bool,
    pub diagnostic_code_registry: bool,
    pub diagnostic_phase_field: bool,
    pub diagnostic_rule_ids: bool,
    pub diagnostic_severity: bool,
    pub diagnostic_severity_counts: bool,
    pub suggested_edit_envelope: bool,
    pub import_expansion: bool,
    pub import_graph_report: bool,
    pub import_duplicate_or_cycle_summary: bool,
    pub stage1_stage2_ci_gate: bool,
    pub type_graph_report: bool,
    pub symbol_table_report: bool,
    pub name_resolver_report: bool,
    pub typecheck_report: bool,
    pub typed_ast: bool,
    pub real_module_resolver: bool,
    pub real_generics: bool,
    pub user_defined_adts: bool,
    pub multi_error_recovery: bool,
    pub diagnostic_codes: Vec<DiagnosticCodeEntry>,
    pub supported_constructs: String,
    pub known_limits: String,
    pub agent_guidance: String,
}

impl CapabilityReport {
    /// Generate the current capability report for `bunker-cli`.
    pub fn current() -> Self {
        Self {
            schema_version: "bunker.capability.v1".to_string(),
            compiler: "bunker-cli".to_string(),
            agent_contract_version: "bunker.agent.diagnostics.v1".to_string(),
            self_hosting_stage: "production-rust-bootstrap".to_string(),
            ai_agent_native_diagnostics: true,
            production_language_ready: false,
            requires_ci_validation: true,
            source_byte_spans: true,
            source_excerpts: true,
            structured_repair_metadata: true,
            structured_parse_diagnostics: true,
            diagnostic_code_registry: true,
            diagnostic_phase_field: true,
            diagnostic_rule_ids: true,
            diagnostic_severity: true,
            diagnostic_severity_counts: true,
            suggested_edit_envelope: true,
            import_expansion: true,
            import_graph_report: true,
            import_duplicate_or_cycle_summary: true,
            stage1_stage2_ci_gate: true,
            type_graph_report: true,
            symbol_table_report: true,
            name_resolver_report: true,
            typecheck_report: true,
            typed_ast: true,
            real_module_resolver: true,
            real_generics: true,
            user_defined_adts: true,
            multi_error_recovery: true,
            diagnostic_codes: vec![
                DiagnosticCodeEntry {
                    code: codes::PARSE_ERROR.to_string(),
                    phase: "parse".to_string(),
                    category: "syntax".to_string(),
                    description: "Parse error with expected and actual token details.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::TYPE_MISMATCH.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Type mismatch in expression or statement.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::UNDEFINED_VARIABLE.to_string(),
                    phase: "typecheck".to_string(),
                    category: "name_resolution".to_string(),
                    description: "Undefined variable in current scope.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::UNDEFINED_FUNCTION.to_string(),
                    phase: "typecheck".to_string(),
                    category: "name_resolution".to_string(),
                    description: "Undefined function in current scope.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::ARGUMENT_COUNT.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Function call argument count mismatch.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::ARGUMENT_TYPE.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Function call argument type mismatch.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::RETURN_TYPE.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Return statement type mismatch with function signature.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::CONDITION_NOT_BOOL.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Condition expression must evaluate to boolean.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::CANNOT_INDEX.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Cannot index non-indexable type.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::NO_SUCH_FIELD.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "No such field on struct or type.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::UNKNOWN_STRUCT.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Unknown struct type in literal or declaration.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::NONE_REQUIRES_TYPE.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "None requires explicit Option<T> type annotation.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::MATCH_PATTERN_TYPE.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Match arm pattern type incompatible with scrutinee.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::MATCH_BLOCK_NO_VALUE.to_string(),
                    phase: "typecheck".to_string(),
                    category: "type_system".to_string(),
                    description: "Match block expression does not produce a value.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::CONTRACT_VIOLATED.to_string(),
                    phase: "verify".to_string(),
                    category: "contract".to_string(),
                    description: "Contract precondition or postcondition violated.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::UNSUPPORTED_POSTCONDITION.to_string(),
                    phase: "verify".to_string(),
                    category: "contract".to_string(),
                    description: "Unsupported postcondition in verification mode.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::SMT_TIMEOUT.to_string(),
                    phase: "verify".to_string(),
                    category: "contract".to_string(),
                    description: "SMT solver query timed out.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::SMT_UNAVAILABLE.to_string(),
                    phase: "verify".to_string(),
                    category: "contract".to_string(),
                    description: "Z3 SMT solver unavailable or disabled.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::USE_AFTER_MOVE.to_string(),
                    phase: "ownership".to_string(),
                    category: "linear_types".to_string(),
                    description: "Use of value after ownership transfer.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::UNKNOWN_AGENT.to_string(),
                    phase: "shell".to_string(),
                    category: "actor_system".to_string(),
                    description: "Unknown agent in shell definition or message.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::UNKNOWN_MESSAGE.to_string(),
                    phase: "shell".to_string(),
                    category: "actor_system".to_string(),
                    description: "Unknown message handler for target agent.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::MESSAGE_ARG_COUNT.to_string(),
                    phase: "shell".to_string(),
                    category: "actor_system".to_string(),
                    description: "Message handler argument count mismatch.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::MESSAGE_ARG_TYPE.to_string(),
                    phase: "shell".to_string(),
                    category: "actor_system".to_string(),
                    description: "Message handler argument type mismatch.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::MESSAGE_MISSING_ARG.to_string(),
                    phase: "shell".to_string(),
                    category: "actor_system".to_string(),
                    description: "Missing required argument in message send.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::UNKNOWN_STATE_FIELD.to_string(),
                    phase: "view".to_string(),
                    category: "reactive_state".to_string(),
                    description: "Unknown state field in view component binding.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::UNKNOWN_VIEW_AGENT.to_string(),
                    phase: "view".to_string(),
                    category: "reactive_state".to_string(),
                    description: "Unknown view agent binding.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::IMPORT_ERROR.to_string(),
                    phase: "import".to_string(),
                    category: "module".to_string(),
                    description: "Missing imported module or file.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::IMPORT_CYCLE.to_string(),
                    phase: "import".to_string(),
                    category: "module".to_string(),
                    description: "Circular module import cycle detected.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::IMPORT_INVALID_PATH.to_string(),
                    phase: "import".to_string(),
                    category: "module".to_string(),
                    description: "Invalid import path (forbidden traversal or backslash).".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::GENERIC_ARG_COUNT.to_string(),
                    phase: "monomorphize".to_string(),
                    category: "generics".to_string(),
                    description: "Generic type or function argument count mismatch.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::GENERIC_INFERENCE_FAILED.to_string(),
                    phase: "monomorphize".to_string(),
                    category: "generics".to_string(),
                    description: "Generic type parameter inference failed or conflicting.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::GENERIC_RECURSION_LIMIT.to_string(),
                    phase: "monomorphize".to_string(),
                    category: "generics".to_string(),
                    description: "Generic monomorphization recursion limit exceeded.".to_string(),
                },
                DiagnosticCodeEntry {
                    code: codes::GENERIC_UNKNOWN_TYPE_PARAM.to_string(),
                    phase: "monomorphize".to_string(),
                    category: "generics".to_string(),
                    description: "Unknown or duplicate generic type parameter.".to_string(),
                },
            ],
            supported_constructs: "kernel, shell, view, agent, struct, tuple_struct, enum, adt, fn, comptime_fn, const, type_alias, import, let, fixed arrays, repeat arrays, slices, field access, if, else, match, match guards, Option, Result, Vec<T>, HashMap<K,V>, bytes, for in ranges, for in slices, while, loop, break, continue, return, primitive types, calls, turbofish calls, casts, ternary, bitwise operators, string literals, escape sequences, float literals, verify contracts, process execution".to_string(),
            known_limits: "Rust bootstrap compiler; Cranelift JIT / C codegen targets; self-hosting compilation progressing through 8 critical path gates; SMT verification requires libz3 feature".to_string(),
            agent_guidance: "Use BUNKER_CAPABILITY_JSON before generating Bunker code. Use BUNKER_DIAGNOSTIC_JSON, BUNKER_AST_JSON, and BUNKER_IMPORT_GRAPH_JSON for repair tasks. Treat production_language_ready=false as requiring CI validation before release.".to_string(),
        }
    }

    /// Serialize capability report to compact JSON string.
    pub fn to_json(&self) -> String {
        serde_json::to_string(self).unwrap_or_default()
    }

    /// Serialize capability report to pretty-printed JSON string.
    pub fn to_json_pretty(&self) -> String {
        serde_json::to_string_pretty(self).unwrap_or_default()
    }

    /// Format capability report as an embedded C/Bunker block comment.
    pub fn to_json_comment(&self) -> String {
        format!("/* BUNKER_CAPABILITY_JSON: {} */\n", self.to_json())
    }
}
