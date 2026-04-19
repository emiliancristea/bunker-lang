//! Structured diagnostic output for AI feedback loops.
//!
//! This module provides serializable error types that can be output as JSON
//! for machine consumption, enabling AI self-correction workflows.

use serde::{Deserialize, Serialize};

use crate::typeck::TypeError;
use crate::verify::VerifyError;

/// Source location information
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SourceLocation {
    pub file: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub line: Option<u32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub column: Option<u32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub end_line: Option<u32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub end_column: Option<u32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub span_length: Option<u32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub source_line: Option<String>,
    /// Fallback context when precise location unavailable (e.g., "function add")
    #[serde(skip_serializing_if = "Option::is_none")]
    pub context: Option<String>,
}

impl SourceLocation {
    /// Create location with just context (no line/column yet)
    pub fn with_context(file: impl Into<String>, context: impl Into<String>) -> Self {
        Self {
            file: file.into(),
            line: None,
            column: None,
            end_line: None,
            end_column: None,
            span_length: None,
            source_line: None,
            context: Some(context.into()),
        }
    }

    /// Create location with full position information
    #[allow(dead_code)]
    pub fn with_position(file: impl Into<String>, line: u32, column: u32) -> Self {
        Self {
            file: file.into(),
            line: Some(line),
            column: Some(column),
            end_line: None,
            end_column: None,
            span_length: None,
            source_line: None,
            context: None,
        }
    }

    /// Create location with full span information.
    pub fn with_span(
        file: impl Into<String>,
        start_line: u32,
        start_column: u32,
        end_line: u32,
        end_column: u32,
    ) -> Self {
        Self {
            file: file.into(),
            line: Some(start_line),
            column: Some(start_column),
            end_line: Some(end_line),
            end_column: Some(end_column),
            span_length: Some(end_column.saturating_sub(start_column).max(1)),
            source_line: None,
            context: None,
        }
    }

    /// Attach a source line excerpt.
    pub fn with_source_line(mut self, source_line: impl Into<String>) -> Self {
        self.source_line = Some(source_line.into());
        self
    }

    /// Attach fallback semantic context.
    pub fn with_context_value(mut self, context: impl Into<String>) -> Self {
        self.context = Some(context.into());
        self
    }
}

/// Severity level for diagnostics
#[derive(Debug, Clone, Copy, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "lowercase")]
pub enum Severity {
    Error,
    Warning,
    #[allow(dead_code)]
    Info,
    #[allow(dead_code)]
    Hint,
}

/// Type information for expected/found reporting
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct TypeInfo {
    #[serde(rename = "type")]
    pub type_name: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub reason: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub source: Option<String>,
}

/// Suggested fix for an error
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Suggestion {
    pub message: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub kind: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub applicability: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub confidence: Option<f32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub replacement: Option<Replacement>,
}

/// Code replacement for machine-applicable fixes
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Replacement {
    pub start_line: u32,
    pub start_column: u32,
    pub end_line: u32,
    pub end_column: u32,
    pub text: String,
}

/// Related diagnostic information
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct RelatedInfo {
    pub location: SourceLocation,
    pub message: String,
}

/// A single diagnostic (error, warning, etc.)
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Diagnostic {
    pub error_code: String,
    pub severity: Severity,
    pub message: String,
    pub location: SourceLocation,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub ai_prompt_hint: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub expected: Option<TypeInfo>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub found: Option<TypeInfo>,
    #[serde(skip_serializing_if = "Vec::is_empty")]
    pub suggestions: Vec<Suggestion>,
    #[serde(skip_serializing_if = "Vec::is_empty")]
    pub related: Vec<RelatedInfo>,
}

impl Diagnostic {
    /// Create a simple error diagnostic
    pub fn error(code: &str, message: impl Into<String>, location: SourceLocation) -> Self {
        Self {
            error_code: code.to_string(),
            severity: Severity::Error,
            message: message.into(),
            location,
            ai_prompt_hint: None,
            expected: None,
            found: None,
            suggestions: Vec::new(),
            related: Vec::new(),
        }
    }

    /// Add expected type information
    pub fn with_expected(mut self, type_name: impl Into<String>, reason: Option<String>) -> Self {
        self.expected = Some(TypeInfo {
            type_name: type_name.into(),
            reason,
            source: None,
        });
        self
    }

    /// Add found type information
    pub fn with_found(mut self, type_name: impl Into<String>, source: Option<String>) -> Self {
        self.found = Some(TypeInfo {
            type_name: type_name.into(),
            reason: None,
            source,
        });
        self
    }

    /// Add a suggestion
    #[allow(dead_code)]
    pub fn with_suggestion(mut self, message: impl Into<String>) -> Self {
        self.suggestions.push(Suggestion {
            message: message.into(),
            kind: None,
            applicability: None,
            confidence: None,
            replacement: None,
        });
        self
    }

    /// Add an AI-facing repair hint.
    pub fn with_ai_prompt_hint(mut self, hint: impl Into<String>) -> Self {
        self.ai_prompt_hint = Some(hint.into());
        self
    }

    /// Add a structured suggestion with a known action kind.
    pub fn with_structured_suggestion(
        mut self,
        message: impl Into<String>,
        kind: impl Into<String>,
        applicability: impl Into<String>,
        confidence: f32,
    ) -> Self {
        self.suggestions.push(Suggestion {
            message: message.into(),
            kind: Some(kind.into()),
            applicability: Some(applicability.into()),
            confidence: Some(confidence),
            replacement: None,
        });
        self
    }
}

/// Summary statistics for diagnostics
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct DiagnosticSummary {
    pub total: usize,
    pub errors: usize,
    pub warnings: usize,
}

/// Prompt-ready compiler context for agent repair loops.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AiPromptContext {
    pub purpose: String,
    pub summary: String,
    pub instructions: Vec<String>,
    pub prompt_addition: String,
}

/// Collection of diagnostics for JSON output
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct DiagnosticOutput {
    pub schema_version: String,
    pub file: String,
    pub success: bool,
    pub diagnostics: Vec<Diagnostic>,
    pub ai_prompt_context: AiPromptContext,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub summary: Option<DiagnosticSummary>,
}

impl DiagnosticOutput {
    pub fn new(file: impl Into<String>, diagnostics: Vec<Diagnostic>) -> Self {
        let errors = diagnostics
            .iter()
            .filter(|d| d.severity == Severity::Error)
            .count();
        let warnings = diagnostics
            .iter()
            .filter(|d| d.severity == Severity::Warning)
            .count();
        let success = errors == 0;
        let total = diagnostics.len();
        let ai_prompt_context = build_ai_prompt_context(success, errors, warnings, &diagnostics);

        Self {
            schema_version: "bunker.diagnostics.v1".to_string(),
            file: file.into(),
            success,
            diagnostics,
            ai_prompt_context,
            summary: Some(DiagnosticSummary {
                total,
                errors,
                warnings,
            }),
        }
    }

    /// Convert to JSON string (pretty-printed)
    pub fn to_json(&self) -> String {
        serde_json::to_string_pretty(self).unwrap_or_else(|e| {
            format!("{{\"error\": \"Failed to serialize diagnostics: {}\"}}", e)
        })
    }

    /// Convert to compact JSON (single line)
    #[allow(dead_code)]
    pub fn to_json_compact(&self) -> String {
        serde_json::to_string(self).unwrap_or_else(|e| {
            format!("{{\"error\": \"Failed to serialize diagnostics: {}\"}}", e)
        })
    }
}

fn build_ai_prompt_context(
    success: bool,
    errors: usize,
    warnings: usize,
    diagnostics: &[Diagnostic],
) -> AiPromptContext {
    let summary = if success {
        format!("Bunker check succeeded with {warnings} warning(s).")
    } else {
        format!("Bunker check failed with {errors} error(s) and {warnings} warning(s).")
    };
    let mut prompt_lines = vec![summary.clone()];

    if !success {
        prompt_lines.push(
            "Repair the source while preserving the user's intent. Prefer the smallest code change that satisfies the compiler.".to_string(),
        );
        let prompt_limit = 20;
        for (idx, diag) in diagnostics.iter().take(prompt_limit).enumerate() {
            let location = match (diag.location.line, diag.location.column) {
                (Some(line), Some(column)) => format!("{}:{}:{}", diag.location.file, line, column),
                _ => format!(
                    "{}:{}",
                    diag.location.file,
                    diag.location
                        .context
                        .as_deref()
                        .unwrap_or("unknown context")
                ),
            };
            prompt_lines.push(format!(
                "{}. [{}] {} at {}",
                idx + 1,
                diag.error_code,
                diag.message,
                location
            ));
            if let Some(hint) = &diag.ai_prompt_hint {
                prompt_lines.push(format!("   Hint: {hint}"));
            }
            if let Some(expected) = &diag.expected {
                prompt_lines.push(format!("   Expected: {}", expected.type_name));
            }
            if let Some(found) = &diag.found {
                prompt_lines.push(format!("   Found: {}", found.type_name));
            }
        }
        if diagnostics.len() > prompt_limit {
            prompt_lines.push(format!(
                "Only the first {prompt_limit} diagnostic(s) are included here. Use the full diagnostics array for the remaining {} item(s).",
                diagnostics.len() - prompt_limit
            ));
        }
    }

    AiPromptContext {
        purpose: "Compiler feedback for AI repair loops".to_string(),
        summary,
        instructions: vec![
            "Use diagnostics as authoritative constraints.".to_string(),
            "Do not silence errors with raw i64 handle casts unless a diagnostic explicitly recommends an explicit typed roundtrip.".to_string(),
            "Prefer adding explicit type annotations over relying on inference when the compiler asks for context.".to_string(),
            "After editing, rerun bunker check with --format=json and use the new diagnostics as the next prompt addition.".to_string(),
        ],
        prompt_addition: prompt_lines.join("\n"),
    }
}

// ============================================================================
// Error Code Definitions
// ============================================================================

pub mod codes {
    // Syntax errors (E01xx)
    pub const PARSE_ERROR: &str = "E0101";

    // Type errors (E02xx)
    pub const TYPE_MISMATCH: &str = "E0201";
    pub const UNDEFINED_VARIABLE: &str = "E0202";
    pub const UNDEFINED_FUNCTION: &str = "E0203";
    pub const ARGUMENT_COUNT: &str = "E0204";
    pub const ARGUMENT_TYPE: &str = "E0205";
    pub const RETURN_TYPE: &str = "E0206";
    pub const CONDITION_NOT_BOOL: &str = "E0207";
    pub const CANNOT_INDEX: &str = "E0208";
    pub const NO_SUCH_FIELD: &str = "E0209";
    pub const UNKNOWN_STRUCT: &str = "E0210";
    pub const NONE_REQUIRES_TYPE: &str = "E0211";
    pub const MATCH_PATTERN_TYPE: &str = "E0212";
    pub const MATCH_BLOCK_NO_VALUE: &str = "E0213";

    // Verification errors (E03xx)
    pub const CONTRACT_VIOLATED: &str = "E0301";
    pub const UNSUPPORTED_POSTCONDITION: &str = "E0302";
    pub const SMT_TIMEOUT: &str = "E0303";
    pub const SMT_UNAVAILABLE: &str = "E0304";

    // Ownership errors (E04xx)
    pub const USE_AFTER_MOVE: &str = "E0401";

    // Shell errors (E05xx)
    pub const UNKNOWN_AGENT: &str = "E0501";
    pub const UNKNOWN_MESSAGE: &str = "E0502";
    pub const MESSAGE_ARG_COUNT: &str = "E0503";
    #[allow(dead_code)]
    pub const MESSAGE_ARG_TYPE: &str = "E0504";
    pub const MESSAGE_MISSING_ARG: &str = "E0505";

    // View errors (E06xx)
    pub const UNKNOWN_STATE_FIELD: &str = "E0601";
    pub const UNKNOWN_VIEW_AGENT: &str = "E0602";
}

// ============================================================================
// Conversions from existing error types
// ============================================================================

/// Convert TypeError to Diagnostic, using source text for best-effort locations.
pub fn type_error_to_diagnostic_with_source(
    err: &TypeError,
    file: &str,
    source: Option<&str>,
) -> Diagnostic {
    let (code, expected, found) = parse_type_error_message(&err.message);
    let location = match source {
        Some(source) => source_location_for_type_error(file, source, &err.location, &err.message),
        None => SourceLocation::with_context(file, &err.location),
    };

    let mut diag = Diagnostic::error(code, &err.message, location);

    if let Some((exp_type, reason)) = expected {
        diag = diag.with_expected(exp_type, reason);
    }
    if let Some((found_type, source)) = found {
        diag = diag.with_found(found_type, source);
    }

    enrich_for_ai(diag)
}

/// Convert VerifyError to Diagnostic, using source text for best-effort locations.
pub fn verify_error_to_diagnostic_with_source(
    err: &VerifyError,
    file: &str,
    source: Option<&str>,
) -> Diagnostic {
    let code = if err.message.contains("timeout") || err.message.contains("inconclusive") {
        codes::SMT_TIMEOUT
    } else if err.message.contains("not available") {
        codes::SMT_UNAVAILABLE
    } else if err.message.contains("Unsupported") {
        codes::UNSUPPORTED_POSTCONDITION
    } else {
        codes::CONTRACT_VIOLATED
    };

    let location = match source {
        Some(source) => source_location_for_context(file, source, &err.location),
        None => SourceLocation::with_context(file, &err.location),
    };

    enrich_for_ai(Diagnostic::error(code, &err.message, location))
}

/// Convert a parser error to a source-located Diagnostic.
pub fn parse_error_to_diagnostic<Rule: pest::RuleType>(
    err: &pest::error::Error<Rule>,
    file: &str,
    source: &str,
) -> Diagnostic {
    use pest::error::LineColLocation;

    let location = match err.line_col {
        LineColLocation::Pos((line, column)) => SourceLocation::with_span(
            file,
            line as u32,
            column as u32,
            line as u32,
            (column as u32).saturating_add(1),
        ),
        LineColLocation::Span((start_line, start_col), (end_line, end_col)) => {
            SourceLocation::with_span(
                file,
                start_line as u32,
                start_col as u32,
                end_line as u32,
                end_col as u32,
            )
        }
    };

    let location = attach_source_line(location, source).with_context_value("parsing");
    enrich_for_ai(Diagnostic::error(
        codes::PARSE_ERROR,
        format!("Parse error: {err}"),
        location,
    ))
}

fn source_location_for_type_error(
    file: &str,
    source: &str,
    context: &str,
    message: &str,
) -> SourceLocation {
    let needles = type_error_search_needles(message);
    if !needles.is_empty() {
        if let Some(location) = source_location_for_needles(file, source, context, &needles) {
            return location;
        }
    }

    source_location_for_context(file, source, context)
}

fn type_error_search_needles(message: &str) -> Vec<String> {
    let mut needles = Vec::new();
    for builtin in [
        "vec_new",
        "vec_push",
        "vec_pop",
        "vec_len",
        "vec_capacity",
        "vec_get",
        "vec_set",
        "hashmap_new",
        "hashmap_insert",
        "hashmap_get",
        "hashmap_contains",
        "hashmap_remove",
        "hashmap_len",
        "hashmap_clear",
        "hashmap_keys",
        "result_ok",
        "result_err",
        "result_is_ok",
        "result_is_err",
        "result_unwrap",
        "result_unwrap_err",
        "result_tag",
        "result_value",
    ] {
        if message.contains(builtin) {
            needles.push(format!("{builtin}("));
        }
    }

    if let Some(name) = extract_quoted_name_after(message, "let binding") {
        needles.push(format!("let {name}"));
    }
    if let Some(name) = message.strip_prefix("Undefined variable: ") {
        needles.push(name.trim().to_string());
    }
    if let Some(name) = message.strip_prefix("Undefined function: ") {
        needles.push(format!("{}(", name.trim()));
    }
    if message.contains("Return type mismatch") || message.contains("Missing return value") {
        needles.push("return".to_string());
    }
    if message.contains("Condition must be bool") {
        needles.push("if ".to_string());
        needles.push("while ".to_string());
    }

    needles
}

fn extract_quoted_name_after(message: &str, prefix: &str) -> Option<String> {
    let start = message.find(prefix)?;
    let after_prefix = &message[start + prefix.len()..];
    let first_quote = after_prefix.find('\'')?;
    let after_first = &after_prefix[first_quote + 1..];
    let second_quote = after_first.find('\'')?;
    Some(after_first[..second_quote].to_string())
}

fn source_location_for_needles(
    file: &str,
    source: &str,
    context: &str,
    needles: &[String],
) -> Option<SourceLocation> {
    let lines: Vec<&str> = source.lines().collect();
    let (start_idx, end_idx) = context_line_range(&lines, context);

    for (line_idx, line) in lines
        .iter()
        .enumerate()
        .skip(start_idx)
        .take(end_idx.saturating_sub(start_idx))
    {
        for needle in needles {
            if let Some(col_idx) = line.find(needle) {
                return Some(SourceLocation {
                    file: file.to_string(),
                    line: Some((line_idx + 1) as u32),
                    column: Some((col_idx + 1) as u32),
                    end_line: Some((line_idx + 1) as u32),
                    end_column: Some((col_idx + needle.len() + 1) as u32),
                    span_length: Some(needle.len() as u32),
                    source_line: Some((*line).to_string()),
                    context: Some(context.to_string()),
                });
            }
        }
    }

    None
}

fn context_line_range(lines: &[&str], context: &str) -> (usize, usize) {
    let context_needles = [
        format!("fn {context}("),
        format!("comptime fn {context}("),
        format!("kernel {context}"),
        format!("shell {context}"),
        format!("view {context}"),
        format!("agent {context}"),
    ];

    let start_idx = lines
        .iter()
        .position(|line| context_needles.iter().any(|needle| line.contains(needle)))
        .unwrap_or(0);
    let end_idx = lines
        .iter()
        .enumerate()
        .skip(start_idx + 1)
        .find(|(_, line)| {
            let trimmed = line.trim_start();
            trimmed.starts_with("fn ")
                || trimmed.starts_with("comptime fn ")
                || trimmed.starts_with("kernel ")
                || trimmed.starts_with("shell ")
                || trimmed.starts_with("view ")
                || trimmed.starts_with("agent ")
        })
        .map(|(idx, _)| idx)
        .unwrap_or(lines.len());

    (start_idx, end_idx)
}

fn source_location_for_context(file: &str, source: &str, context: &str) -> SourceLocation {
    if context.is_empty() {
        return SourceLocation::with_context(file, "unknown");
    }

    let needles = [
        format!("fn {context}("),
        format!("comptime fn {context}("),
        format!("kernel {context}"),
        format!("shell {context}"),
        format!("view {context}"),
        format!("agent {context}"),
        context.to_string(),
    ];

    for (line_idx, line) in source.lines().enumerate() {
        for needle in &needles {
            if let Some(col_idx) = line.find(needle) {
                return SourceLocation {
                    file: file.to_string(),
                    line: Some((line_idx + 1) as u32),
                    column: Some((col_idx + 1) as u32),
                    end_line: Some((line_idx + 1) as u32),
                    end_column: Some((col_idx + needle.len() + 1) as u32),
                    span_length: Some(needle.len() as u32),
                    source_line: Some(line.to_string()),
                    context: Some(context.to_string()),
                };
            }
        }
    }

    SourceLocation::with_context(file, context)
}

fn attach_source_line(mut location: SourceLocation, source: &str) -> SourceLocation {
    if let Some(line) = location.line {
        if let Some(source_line) = source.lines().nth(line.saturating_sub(1) as usize) {
            location = location.with_source_line(source_line);
        }
    }
    location
}

fn enrich_for_ai(diag: Diagnostic) -> Diagnostic {
    let msg = diag.message.as_str();

    if msg.contains("requires explicit Vec<T> type context") {
        return diag
            .with_ai_prompt_hint(
                "Add an explicit Vec<T> annotation at the binding site, for example `let values: Vec<i32> = vec_new();`.",
            )
            .with_structured_suggestion(
                "Add an explicit Vec<T> type annotation to the `vec_new()` binding.",
                "add_type_annotation",
                "machine_applicable_when_binding_span_known",
                0.94,
            );
    }
    if msg.contains("requires explicit HashMap<K, V> type context") {
        return diag
            .with_ai_prompt_hint(
                "Add an explicit HashMap<K, V> annotation at the binding site, for example `let map: HashMap<i32, str> = hashmap_new();`.",
            )
            .with_structured_suggestion(
                "Add an explicit HashMap<K, V> type annotation to the `hashmap_new()` binding.",
                "add_type_annotation",
                "machine_applicable_when_binding_span_known",
                0.94,
            );
    }
    if msg.contains("expects Vec<T>, got I64")
        || msg.contains("expects HashMap<K, V>, got I64")
        || msg.contains("expects Result<T, E>, got I64")
    {
        return diag
            .with_ai_prompt_hint(
                "Do not pass a raw i64 handle directly. Keep the value typed, or explicitly cast the raw handle back to the correct typed handle before calling the builtin.",
            )
            .with_structured_suggestion(
                "Insert an explicit cast from i64 to the required typed handle before the builtin call.",
                "insert_explicit_cast",
                "machine_applicable_when_target_type_known",
                0.88,
            );
    }
    if msg.contains("result_value requires Result<T, T>") {
        return diag
            .with_ai_prompt_hint(
                "Use result_unwrap/result_unwrap_err for Result<T, E>. Use result_value only when Ok and Err have the same type.",
            )
            .with_structured_suggestion(
                "Replace result_value with result_unwrap or result_unwrap_err based on the branch being handled.",
                "replace_builtin_call",
                "requires_semantic_choice",
                0.75,
            );
    }
    if msg.contains("Undefined variable") {
        return diag
            .with_ai_prompt_hint(
                "Declare the variable before use, pass it as a parameter, or correct the identifier spelling.",
            )
            .with_structured_suggestion(
                "Introduce a local binding or rename the identifier to an in-scope variable.",
                "declare_or_rename_symbol",
                "requires_symbol_context",
                0.7,
            );
    }
    if msg.contains("Undefined function") {
        return diag
            .with_ai_prompt_hint(
                "Define the function in the current kernel or call an existing function with the correct name.",
            )
            .with_structured_suggestion(
                "Add a function definition or rename the call target.",
                "define_or_rename_function",
                "requires_symbol_context",
                0.7,
            );
    }
    if msg.contains("Use of moved value") {
        return diag
            .with_ai_prompt_hint(
                "The value was moved earlier. Use `copy` at the move site if both variables must remain valid, or stop using the moved source.",
            )
            .with_structured_suggestion(
                "Insert `copy` before the moved value or rewrite later uses to use the new owner.",
                "fix_move_semantics",
                "requires_ownership_context",
                0.82,
            );
    }
    if msg.contains("None requires explicit") {
        return diag
            .with_ai_prompt_hint(
                "Annotate the binding with Option<T> so the compiler knows which None type is intended.",
            )
            .with_structured_suggestion(
                "Add an explicit Option<T> annotation.",
                "add_type_annotation",
                "machine_applicable_when_inner_type_known",
                0.9,
            );
    }
    if msg.contains("type mismatch") || msg.contains("Type mismatch") {
        return diag
            .with_ai_prompt_hint(
                "Make the expression type match the expected type. Prefer changing the expression or adding an explicit annotation over broad casts.",
            )
            .with_structured_suggestion(
                "Adjust the expression, annotation, or function signature so expected and found types match.",
                "fix_type_mismatch",
                "requires_semantic_choice",
                0.72,
            );
    }

    diag.with_ai_prompt_hint(
        "Use the error code, expected/found fields, and source context as constraints for the next repair attempt.",
    )
}

type ParsedTypeInfo = Option<(String, Option<String>)>;

/// Parse type error messages to extract structured information
fn parse_type_error_message(msg: &str) -> (&'static str, ParsedTypeInfo, ParsedTypeInfo) {
    // Pattern matching on common error message formats
    if msg.contains("Use of moved value") {
        return (codes::USE_AFTER_MOVE, None, None);
    }
    if msg.contains("type mismatch") || msg.contains("Type mismatch") {
        // Try to extract expected and found types
        if let Some(caps) = extract_type_mismatch(msg) {
            return (
                codes::TYPE_MISMATCH,
                Some((caps.0, Some("declared type".to_string()))),
                Some((caps.1, None)),
            );
        }
        return (codes::TYPE_MISMATCH, None, None);
    }
    if msg.contains("Undefined variable") {
        return (codes::UNDEFINED_VARIABLE, None, None);
    }
    if msg.contains("Undefined function") {
        return (codes::UNDEFINED_FUNCTION, None, None);
    }
    if msg.contains("expects") && msg.contains("argument") {
        return (codes::ARGUMENT_COUNT, None, None);
    }
    if msg.contains("Argument") && msg.contains("type mismatch") {
        if let Some(caps) = extract_type_mismatch(msg) {
            return (
                codes::ARGUMENT_TYPE,
                Some((caps.0, Some("expected argument type".to_string()))),
                Some((caps.1, None)),
            );
        }
        return (codes::ARGUMENT_TYPE, None, None);
    }
    if msg.contains("Return type mismatch") {
        if let Some(caps) = extract_type_mismatch(msg) {
            return (
                codes::RETURN_TYPE,
                Some((caps.0, Some("declared return type".to_string()))),
                Some((caps.1, None)),
            );
        }
        return (codes::RETURN_TYPE, None, None);
    }
    if msg.contains("Condition must be bool") {
        return (codes::CONDITION_NOT_BOOL, None, None);
    }
    if msg.contains("Cannot index") {
        return (codes::CANNOT_INDEX, None, None);
    }
    if msg.contains("No field") {
        return (codes::NO_SUCH_FIELD, None, None);
    }
    if msg.contains("Unknown struct") {
        return (codes::UNKNOWN_STRUCT, None, None);
    }
    if msg.contains("None requires explicit") {
        return (codes::NONE_REQUIRES_TYPE, None, None);
    }
    if msg.contains("pattern cannot match") {
        return (codes::MATCH_PATTERN_TYPE, None, None);
    }
    if msg.contains("block must end with an expression") {
        return (codes::MATCH_BLOCK_NO_VALUE, None, None);
    }
    if msg.contains("Unknown agent") {
        return (codes::UNKNOWN_AGENT, None, None);
    }
    if msg.contains("has no handler") {
        return (codes::UNKNOWN_MESSAGE, None, None);
    }
    if msg.contains("missing required argument") {
        return (codes::MESSAGE_MISSING_ARG, None, None);
    }
    if msg.contains("Message") && msg.contains("expects") && msg.contains("argument(s)") {
        return (codes::MESSAGE_ARG_COUNT, None, None);
    }
    if msg.contains("Unknown state field") {
        return (codes::UNKNOWN_STATE_FIELD, None, None);
    }
    if msg.contains("Unknown agent") && msg.contains("view") {
        return (codes::UNKNOWN_VIEW_AGENT, None, None);
    }

    // Default
    (codes::TYPE_MISMATCH, None, None)
}

fn extract_type_mismatch(msg: &str) -> Option<(String, String)> {
    // Try to extract "expected X, got Y" or "declared X, got Y"
    let patterns = [
        ("declared ", ", got "),
        ("expected ", ", got "),
        ("expected ", ", found "),
    ];

    for (prefix, sep) in patterns {
        if let Some(start) = msg.find(prefix) {
            let after_prefix = &msg[start + prefix.len()..];
            if let Some(sep_pos) = after_prefix.find(sep) {
                let expected = after_prefix[..sep_pos].trim();
                let after_sep = &after_prefix[sep_pos + sep.len()..];
                // Take until end of word or punctuation
                let found: String = after_sep
                    .chars()
                    .take_while(|c| !c.is_whitespace() && *c != ',')
                    .collect();
                return Some((expected.to_string(), found));
            }
        }
    }
    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_diagnostic_serialization() {
        let diag = Diagnostic::error(
            codes::TYPE_MISMATCH,
            "Type mismatch: expected i32, got String",
            SourceLocation::with_context("test.bkr", "function add"),
        )
        .with_expected("i32", Some("declared return type".to_string()))
        .with_found("String", None);

        let output = DiagnosticOutput::new("test.bkr", vec![diag]);
        let json = output.to_json();

        assert!(json.contains("\"error_code\": \"E0201\""));
        assert!(json.contains("\"success\": false"));
        assert!(json.contains("\"errors\": 1"));
    }

    #[test]
    fn test_extract_type_mismatch() {
        let msg = "Type mismatch in let binding 'x': declared i32, got f64";
        let result = extract_type_mismatch(msg);
        assert_eq!(result, Some(("i32".to_string(), "f64".to_string())));
    }

    #[test]
    fn test_success_output() {
        let output = DiagnosticOutput::new("test.bkr", vec![]);
        assert!(output.success);
        assert_eq!(output.summary.as_ref().unwrap().errors, 0);
    }

    #[test]
    fn test_ai_prompt_context_caps_large_diagnostic_sets() {
        let diagnostics: Vec<_> = (0..25)
            .map(|idx| {
                Diagnostic::error(
                    codes::TYPE_MISMATCH,
                    format!("diagnostic {}", idx),
                    SourceLocation::with_context("test.bkr", "main"),
                )
            })
            .collect();

        let output = DiagnosticOutput::new("test.bkr", diagnostics);
        assert!(output
            .ai_prompt_context
            .prompt_addition
            .contains("Only the first 20 diagnostic(s)"));
    }

    #[test]
    fn test_type_error_uses_offending_call_location() {
        let source = r#"kernel Demo {
    fn main() -> i32 {
        let values: Vec<i32> = vec_new();
        vec_push(values, "oops");
        return 0;
    }
}
"#;
        let err = TypeError {
            message: "vec_push value type mismatch: expected I32, got Str".to_string(),
            location: "main".to_string(),
        };

        let diag = type_error_to_diagnostic_with_source(&err, "test.bkr", Some(source));
        assert_eq!(diag.location.line, Some(4));
        assert_eq!(diag.location.column, Some(9));
        assert_eq!(
            diag.location.source_line.as_deref(),
            Some("        vec_push(values, \"oops\");")
        );
    }
}
