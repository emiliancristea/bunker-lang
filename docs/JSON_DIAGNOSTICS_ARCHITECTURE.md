# Bunker JSON Serialization, Deserialization, and Diagnostic Builder Architecture

**Document ID:** `BKR-SPEC-JSON-001`  
**Status:** `STABLE`  
**Language Version:** `1.0.0`  
**Track:** `R` (Runtime and Standard Library), Items `R-009` (JSON parser/writer) & `R-012` (Diagnostics builder library)  
**Related Specs:** `docs/TYPE_DIAGNOSTICS.md` (`BKR-SPEC-DIAG-002`), `docs/C_RUNTIME_ABI.md` (`BKR-SPEC-ABI-001`), `docs/UNICODE_POLICY.md` (`BKR-SPEC-STR-002`)

---

## 1. Executive Summary & Design Invariants

In an AI-agent native programming language, machine-readable compiler outputs and runtime diagnostics cannot be second-class string concatenations or ad-hoc error printouts. Every compiler phase (lexing, parsing, name resolution, typechecking, and code generation) must be capable of:
1. **Emitting Valid JSON Without External Dependencies:** Constructing and serializing structured data directly within the Bunker standard library and self-host compiler modules.
2. **Parsing & Querying Machine Data:** Reading, tokenizing, and querying JSON configuration, agent tool parameters, and compiler metadata without heavy external runtimes.
3. **Producing Standardized Diagnostic Envelopes:** Constructing rich, structured error records adhering strictly to the canonical `bunker.diagnostics.v1` schema with exact source spans, expected/found type models, and actionable code repair hints.

```
+-----------------------------------------------------------------------------------------+
|                    Bunker JSON & Diagnostic Builder Architecture                         |
+-----------------------------------------------------------------------------------------+
|                                                                                         |
|   Compiler Phases: Lexer -> Parser -> Resolver -> Typechecker -> Codegen                |
|                                |                                                        |
|                                v                                                        |
|   +---------------------------------------------------------------------------------+   |
|   |                  Diagnostic Builder (self-host/modules/diagnostic.bkr)           |   |
|   |  - diag_error() / diag_warning()                                                |   |
|   |  - diag_with_span(start, end) / diag_with_source(line_str, context)              |   |
|   |  - diag_with_types(expected, found) / diag_with_hint(ai_hint)                    |   |
|   |  - diag_with_fix(action, replacement, applicability, confidence)                |   |
|   +---------------------------------------------------------------------------------+   |
|                                |                                                        |
|                                v                                                        |
|   +---------------------------------------------------------------------------------+   |
|   |                     JSON Writer (self-host/modules/json.bkr)                    |   |
|   |  - json_escape_str() / json_val_str() / json_val_i64() / json_val_bool()        |   |
|   |  - JsonObject: key-value builder / JsonArray: element list builder              |   |
|   +---------------------------------------------------------------------------------+   |
|                                |                                                        |
|                                v                                                        |
|   +---------------------------------------------------------------------------------+   |
|   |                     Canonical Envelope: bunker.diagnostics.v1                   |   |
|   |  - Top-level schema version, file target, success boolean, summary counters     |   |
|   |  - Structured diagnostic array with machine-applicable repair edits             |   |
|   +---------------------------------------------------------------------------------+   |
|                                                                                         |
+-----------------------------------------------------------------------------------------+
```

---

## 2. JSON Serialization & Writing (`R-009`)

### 2.1 Control Character & Escape Discipline
The JSON standard requires escaping of control characters and literal quotation marks. Bunker's serializer enforces RFC 8259 compliance:
- ASCII control characters (`0x00` through `0x1F`):
  * `0x0A` (LF) -> `\n`
  * `0x0D` (CR) -> `\r`
  * `0x09` (TAB) -> `\t`
- Reverse solidus (`0x5C`): `\` -> `\\`
- Quotation mark (`0x22`): `"` -> `\"`
- Multi-line block comment sequences (`*/`): escaped as `*\/` in emitted compiler comments to prevent comment injection or premature termination.

### 2.2 Core Serializer API
```bkr
fn json_escape_str(raw: str) -> str;
fn json_val_str(val: str) -> str;
fn json_val_i64(val: i64) -> str;
fn json_val_bool(val: bool) -> str;
fn json_val_null() -> str;

fn json_field_str(key: str, val: str) -> str;
fn json_field_i64(key: str, val: i64) -> str;
fn json_field_bool(key: str, val: bool) -> str;
fn json_field_raw(key: str, raw_json: str) -> str;
```

### 2.3 Object & Array Builders
To ensure clean formatting without manual delimiter tracking:
```bkr
struct JsonObject {
    keys: Vec<str>,
    values: Vec<str>
}

struct JsonArray {
    items: Vec<str>
}

fn json_object_new() -> JsonObject;
fn json_object_set_str(obj: JsonObject, key: str, val: str);
fn json_object_set_i64(obj: JsonObject, key: str, val: i64);
fn json_object_set_bool(obj: JsonObject, key: str, val: bool);
fn json_object_set_raw(obj: JsonObject, key: str, raw_json: str);
fn json_object_to_json(obj: JsonObject) -> str;

fn json_array_new() -> JsonArray;
fn json_array_push_str(arr: JsonArray, val: str);
fn json_array_push_i64(arr: JsonArray, val: i64);
fn json_array_push_bool(arr: JsonArray, val: bool);
fn json_array_push_raw(arr: JsonArray, raw_json: str);
fn json_array_to_json(arr: JsonArray) -> str;
```

---

## 3. JSON Deserialization & Query Engine (`R-009`)

For reading and querying JSON data in self-host modules and test harnesses, Bunker implements a zero-dependency lexical query scanner:

### 3.1 Lexical Scanning Primitives
- `json_skip_whitespace(src: str, start: i64) -> i64`: Skips spaces, tabs, linefeeds, and carriage returns.
- `json_extract_field(src: str, key: str) -> str`: Scans for quoted field name `"key"`, finds trailing `:`, advances past whitespace, and extracts the literal value slice (string, integer, boolean, or sub-object/array).

### 3.2 Typed Query Helpers
```bkr
fn json_query_str(src: str, key: str) -> str;
fn json_query_i64(src: str, key: str) -> i64;
fn json_query_bool(src: str, key: str) -> bool;
fn json_query_has(src: str, key: str) -> bool;
fn json_array_elements(raw_array: str) -> Vec<str>;
```

---

## 4. Diagnostic Builder Library (`R-012`)

The diagnostic builder provides strongly typed records for error creation, ensuring that diagnostic records across Rust and Bunker compilers produce identical serialized JSON matching `bunker.diagnostics.v1`.

### 4.1 Data Structures
```bkr
struct DiagnosticTextEdit {
    kind: str,                  // "insert", "replace", "delete"
    source_start: i64,
    source_end: i64,
    replacement: str,
    applicability: str,         // "machine-applicable", "maybe-applicable"
    confidence: str             // "high", "medium", "low"
}

struct Diagnostic {
    error_code: str,            // "E0101", "E0201", "E0301", "E0701", etc.
    severity: str,              // "error", "warning", "info", "hint"
    phase: str,                 // "parse", "resolver", "typecheck", "codegen"
    message: str,
    file: str,
    line: i64,
    column: i64,
    source_start: i64,
    source_end: i64,
    context: str,
    source_line: str,
    ai_prompt_hint: str,
    expected_type: str,
    found_type: str,
    has_suggestion: bool,
    suggestion_msg: str,
    suggestion_edit: DiagnosticTextEdit
}

struct DiagnosticReport {
    schema_version: str,        // "bunker.diagnostics.v1"
    file: str,
    diagnostics: Vec<Diagnostic>,
    error_count: i64,
    warning_count: i64
}
```

### 4.2 Fluent Builder Interface
```bkr
fn diag_error(code: str, phase: str, msg: str, file: str, line: i64, col: i64) -> Diagnostic;
fn diag_warning(code: str, phase: str, msg: str, file: str, line: i64, col: i64) -> Diagnostic;
fn diag_with_span(diag: Diagnostic, start: i64, end: i64) -> Diagnostic;
fn diag_with_source(diag: Diagnostic, source_line: str, context: str) -> Diagnostic;
fn diag_with_types(diag: Diagnostic, expected: str, found: str) -> Diagnostic;
fn diag_with_hint(diag: Diagnostic, hint: str) -> Diagnostic;
fn diag_with_suggestion(diag: Diagnostic, msg: str, kind: str, start: i64, end: i64,
                        replacement: str, applicability: str, confidence: str) -> Diagnostic;

fn diag_report_new(file: str) -> DiagnosticReport;
fn diag_report_add(report: DiagnosticReport, diag: Diagnostic);
fn diag_report_has_errors(report: DiagnosticReport) -> bool;
fn diag_report_to_json(report: DiagnosticReport) -> str;
```

---

## 5. Canonical JSON Diagnostic Schema (`bunker.diagnostics.v1`)

```json
{
  "schema_version": "bunker.diagnostics.v1",
  "file": "src/main.bkr",
  "success": false,
  "summary": {
    "total": 1,
    "errors": 1,
    "warnings": 0
  },
  "diagnostics": [
    {
      "error_code": "E0301",
      "severity": "error",
      "phase": "typecheck",
      "message": "Use of moved variable 'payload'",
      "location": {
        "file": "src/main.bkr",
        "line": 42,
        "column": 16,
        "source_start": 1045,
        "source_end": 1052,
        "context": "fn process_data",
        "source_line": "    send_message(payload);"
      },
      "ai_prompt_hint": "Variable was moved at line 38; consider using 'copy payload' at the earlier call site",
      "expected": {
        "type": "MessagePayload"
      },
      "found": {
        "type": "<moved>"
      },
      "suggestions": [
        {
          "message": "Clone variable prior to transfer",
          "kind": "replace",
          "source_start": 920,
          "source_end": 927,
          "replacement": "copy payload",
          "applicability": "machine-applicable",
          "confidence": "high"
        }
      ]
    }
  ]
}
```

---

## 6. Implementation & Verification Matrix

| Capability | Module File | Test Fixture | Status |
|---|---|---|---|
| JSON Escaping & Primitives | `self-host/modules/json.bkr` | `tests/246_json_parser_writer.bkr` | Verified |
| JSON Object & Array Builders | `self-host/modules/json.bkr` | `tests/246_json_parser_writer.bkr` | Verified |
| JSON Scanning & Extraction | `self-host/modules/json.bkr` | `tests/246_json_parser_writer.bkr` | Verified |
| Diagnostic Record Creation | `self-host/modules/diagnostic.bkr` | `tests/247_diagnostics_builder.bkr` | Verified |
| Expected/Found & Span Tracking | `self-host/modules/diagnostic.bkr` | `tests/247_diagnostics_builder.bkr` | Verified |
| AI Prompt Hints & Suggestions | `self-host/modules/diagnostic.bkr` | `tests/247_diagnostics_builder.bkr` | Verified |
| Diagnostic Report Aggregation | `self-host/modules/diagnostic.bkr` | `tests/247_diagnostics_builder.bkr` | Verified |
| Self-Host Readiness & Determinism | `self-host/bkrc.bkr` | `self-host-check`, `run_tests.ps1` | Verified |
