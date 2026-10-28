# BKR-SPEC-PARSE-001: Bunker Compiler Frontend Parser Recovery and Parse Diagnostics Specification

**Document Identifier:** `BKR-SPEC-PARSE-001`  
**Initial Draft:** October 2026  
**Status:** Approved / Normative Standard  
**Target Subsystems:** `self-host/modules/parser_state.bkr`, `self-host/modules/parser.bkr`, `self-host/modules/driver.bkr`, `bunker-cli/src/diagnostic.rs`  
**Milestone Alignment:** `CF-001`, `CF-002`, `CF-005`, `CF-006`, `CF-011` (Milestone `Q-293`)

---

## 1. Executive Summary & Architectural Motivation

A world-class compiler cannot fail-fast on the first syntax error and abort compilation. When an AI agent or human software engineer modifies code, multiple syntax imperfections (missing semicolons, unclosed delimiters, unexpected tokens) frequently occur simultaneously. Stopping at error 1 forces an $O(N)$ compile-edit-retry cycle where each iteration uncovers only one defect.

This specification formalizes:
1. **Multi-Error Parser Recovery (`CF-005`)**: Deterministic panic-mode recovery with statement-level and item-level synchronization tokens, allowing the parser to report all independent syntax errors in a single compiler execution.
2. **Machine-Readable Parse Diagnostics (`CF-006`)**: Structural diagnostic envelope conforming to `bunker.self_host.diagnostic.v1` and `bunker.diagnostics.v1`, carrying exact byte spans, source line excerpts, line/column coordinates, expected/actual tokens, AI prompt repair hints, and machine-applicable `insert_text` replacement suggestions.
3. **Formal Close of Reusable Lexer (`CF-001`) and Parser (`CF-002`)**: Complete typed interface verification routing token streams through `LexerResultRef` and parser execution through `ParserStateRef`.
4. **Formal Close of Exhaustiveness Checker (`CF-011`)**: Full multi-variant ADT exhaustiveness verification across unit enums, payload enums, `Option<T>`, `Result<T, E>`, booleans, and scalars.

---

## 2. Synchronization Strategy & Invariants

### 2.1 Statement-Level Synchronization
When an unexpected token or missing delimiter is detected during statement parsing:
1. An error record is appended to the parser's error collection (`errors_pos`, `errors_expected`, `errors_actual`).
2. The parser scans forward until it encounters a synchronization token:
   - Semicolon `;` (advances past the semicolon to begin the next statement)
   - Closing brace `}` (stops before the brace, allowing the enclosing block to complete)
   - `TOK_EOF` (stops at end of file)
3. Control returns to the enclosing block loop (`parse_block_ref`), which proceeds to parse subsequent statements.

### 2.2 Item-Level Synchronization
When an unexpected token or malformed declaration is encountered at the kernel item level:
1. An error record is logged.
2. The parser advances past offending tokens until encountering any item start keyword:
   - `fn`, `struct`, `enum`, `const`, `type`, `pub`, or closing brace `}`
3. Control returns to `parse_kernel_ref`, which resumes parsing subsequent top-level declarations.

### 2.3 Deduping and Error Cascades
To prevent noisy cascading errors from the same fault:
- Error recording rejects duplicate reports at the identical token cursor position.
- Once an error is logged during statement recovery, subsequent tokens are skipped silently until the synchronization boundary is reached.

---

## 3. Data Structures & ABI

### 3.1 Parser State Layout (`ParserStateRef`)
The bootstrap parser state vector is extended while preserving $100\%$ backward compatibility with legacy 9-element readers:

```text
Index  0: tokens (Vec<i64>)
Index  1: names (Vec<str>)
Index  2: values (Vec<i64>)
Index  3: strings (Vec<str>)
Index  4: position (i64)
Index  5: error_flag (i64: 0 or 1)
Index  6: first_error_position (i64)
Index  7: first_expected_token (TokenKind)
Index  8: first_actual_token (TokenKind)
Index  9: error_positions (Vec<i64>)
Index 10: error_expecteds (Vec<i64>)
Index 11: error_actuals (Vec<i64>)
```

### 3.2 Public API (`parser_state.bkr` & `parser.bkr`)
```bkr
fn parser_error_count_ref(p: ParserStateRef) -> i64;
fn parser_error_position_at_ref(p: ParserStateRef, idx: i64) -> i64;
fn parser_error_expected_at_ref(p: ParserStateRef, idx: i64) -> TokenKind;
fn parser_error_actual_at_ref(p: ParserStateRef, idx: i64) -> TokenKind;
fn parser_error_span_at_ref(p: ParserStateRef, idx: i64) -> AstSpan;
fn parser_sync_stmt(p: ParserStateRef) -> bool;
fn parser_sync_item(p: ParserStateRef) -> bool;
```

---

## 4. Machine-Readable Diagnostic Envelope (`BUNKER_DIAGNOSTIC_JSON`)

When parse errors are present, the compiler driver emits a structured diagnostic envelope conforming to:

```json
{
  "schema_version": "bunker.self_host.diagnostic.v1",
  "phase": "parse",
  "category": "syntax",
  "error_code": "BKR_SELF_PARSE",
  "rule_id": "BKR_SELF_PARSE",
  "severity": "error",
  "error_count": 2,
  "message": "Parse error at token 5: expected semicolon, got ident",
  "source_start": 35,
  "source_end": 36,
  "source_line": 3,
  "source_column": 17,
  "source_excerpt": "        let a: i32 = 10",
  "expected": "semicolon",
  "actual": "ident",
  "suggested_action": "Inspect the construct before this token...",
  "fix_applicability": "manual_review",
  "fix_confidence": "medium",
  "safe_edit_available": true,
  "suggested_edits": [
    {
      "kind": "insert_text",
      "start": 35,
      "end": 35,
      "replacement": ";",
      "applicability": "manual_review",
      "confidence": "medium"
    }
  ],
  "repair_hint": "...",
  "diagnostics": [
    {
      "error_code": "BKR_SELF_PARSE",
      "rule_id": "BKR_SELF_PARSE",
      "severity": "error",
      "message": "Parse error at token 5: expected semicolon, got ident",
      "source_start": 35,
      "source_end": 36,
      "source_line": 3,
      "source_column": 17,
      "source_excerpt": "        let a: i32 = 10",
      "expected": "semicolon",
      "actual": "ident",
      "repair_hint": "...",
      "suggested_edits": [...]
    },
    {
      "error_code": "BKR_SELF_PARSE",
      "rule_id": "BKR_SELF_PARSE",
      "severity": "error",
      "message": "Parse error at token 12: expected semicolon, got return",
      "source_start": 62,
      "source_end": 68,
      "source_line": 4,
      "source_column": 9,
      "source_excerpt": "        return 42;",
      "expected": "semicolon",
      "actual": "return",
      "repair_hint": "...",
      "suggested_edits": [...]
    }
  ]
}
```

---

## 5. Verification Matrix & Gates

| Test | Objective | Target Outcome |
|---|---|---|
| `tests/252_parser_recovery_diagnostics.bkr` | Verify parser multi-error tracking, count, indexing, span extraction, and diagnostic serialization | Returns 42 |
| `tests/253_parse_recovery_multi_error.bkr` | Verify statement and item level recovery on multi-error programs | Returns 42 |
| `self-host-check` | Zero diagnostics across all 8 self-host compiler modules | 0 errors |
| `run_tests.ps1` | Full test suite across all 268 registered test fixtures | 100% PASS |
