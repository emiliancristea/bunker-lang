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
    pub span_length: Option<u32>,
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
            span_length: None,
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
            span_length: None,
            context: None,
        }
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
            confidence: None,
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

/// Collection of diagnostics for JSON output
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct DiagnosticOutput {
    pub file: String,
    pub success: bool,
    pub diagnostics: Vec<Diagnostic>,
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

        Self {
            file: file.into(),
            success,
            diagnostics,
            summary: Some(DiagnosticSummary {
                total,
                errors,
                warnings,
            }),
        }
    }

    /// Convert to JSON string (pretty-printed)
    pub fn to_json(&self) -> String {
        serde_json::to_string_pretty(self)
            .unwrap_or_else(|e| format!("{{\"error\": \"Failed to serialize diagnostics: {}\"}}", e))
    }

    /// Convert to compact JSON (single line)
    #[allow(dead_code)]
    pub fn to_json_compact(&self) -> String {
        serde_json::to_string(self)
            .unwrap_or_else(|e| format!("{{\"error\": \"Failed to serialize diagnostics: {}\"}}", e))
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

/// Convert TypeError to Diagnostic
pub fn type_error_to_diagnostic(err: &TypeError, file: &str) -> Diagnostic {
    let (code, expected, found) = parse_type_error_message(&err.message);

    let mut diag = Diagnostic::error(code, &err.message, SourceLocation::with_context(file, &err.location));

    if let Some((exp_type, reason)) = expected {
        diag = diag.with_expected(exp_type, reason);
    }
    if let Some((found_type, source)) = found {
        diag = diag.with_found(found_type, source);
    }

    diag
}

/// Convert VerifyError to Diagnostic
pub fn verify_error_to_diagnostic(err: &VerifyError, file: &str) -> Diagnostic {
    let code = if err.message.contains("timeout") || err.message.contains("inconclusive") {
        codes::SMT_TIMEOUT
    } else if err.message.contains("not available") {
        codes::SMT_UNAVAILABLE
    } else if err.message.contains("Unsupported") {
        codes::UNSUPPORTED_POSTCONDITION
    } else if err.message.contains("postcondition") || err.message.contains("Contract") {
        codes::CONTRACT_VIOLATED
    } else {
        codes::CONTRACT_VIOLATED
    };

    Diagnostic::error(code, &err.message, SourceLocation::with_context(file, &err.location))
}

/// Parse type error messages to extract structured information
fn parse_type_error_message(
    msg: &str,
) -> (
    &str,
    Option<(String, Option<String>)>,
    Option<(String, Option<String>)>,
) {
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
                    .take_while(|c| !c.is_whitespace() && *c != ',' && *c != ')')
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
}
