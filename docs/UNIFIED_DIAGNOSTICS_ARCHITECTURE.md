# BKR-SPEC-DIAG-003: Unified Diagnostic Envelope, Stable Code Registry, and AI-Agent Parity Architecture

- **Status**: CANONICAL / LOCKED (2026-10-27)
- **Document ID**: `BKR-SPEC-DIAG-003`
- **Track**: AI-Agent Diagnostics (`A`)
- **Items Addressed**:
  - `A-001` (P0): JSON diagnostics — Every compiler phase shares the unified `bunker.diagnostics.v1` envelope.
  - `A-002` (P0): Stable diagnostic codes — Shared canonical registry across Rust (`bunker-cli`) and self-host (`bkrc.bkr`) compilers.
  - `A-003` (P0): Exact spans — Character-precise byte bounds, line/col, and excerpts across all compiler phases.
  - `A-004` (P0): Expected/found details — Structured expected/actual tokens, types, and symbols.
  - `A-005` (P0): Suggested fix edits — Machine-applicable text replacements (`Replacement` / `suggested_edits`).
  - `A-006` (P1): Confidence levels — Calibrated applicability and confidence ratings (`high`, `medium`, `low`).
  - `A-007` (P1): Related spans — Cross-referenced declaration, definition, and move locations.
  - `A-008` (P0): Prompt-ready explanations — Phase-wide actionable repair hints and agent guidance.
  - Officially closes Track `A` (AI-Agent Diagnostics) at 100.0% completion (14 / 14 DONE).
- **Conformance Test Fixtures**:
  - `tests/254_unified_diagnostic_envelope.bkr` (returns 42)
  - `tests/255_diagnostic_code_registry_parity.bkr` (returns 42)

---

## 1. Executive Summary & Epistemic Foundations

In an AI-agent native programming ecosystem, compiler diagnostics cannot be transient terminal text, ad-hoc string formatting, or unversioned printouts. In autonomous workflows, compiler errors are not merely human alerts—they are the **primary control input** to an agentic repair feedback loop.

### 1.1 The Fragility of Terminal Prose
Traditional compilers (such as GCC, Clang, or rustc) format diagnostic messages for human terminal consumption:
- ASCII art squiggles (`^^^^`) and colorized ANSI sequences require complex regex scraping that easily breaks on format changes.
- Textual error descriptions collapse semantic domain models (e.g. `Type`, `Token`, `Symbol`) into unstructured prose.
- Secondary diagnostics and cascaded errors frequently bury the primary defect.
- Code suggestions are often prose suggestions ("consider adding a semicolon") rather than byte-accurate diff operations that automated agents can apply without guessing.

### 1.2 The Bunker Principle: Diagnostics as a Structured Contract
Bunker treats diagnostic generation as a formal, version-governed API:
1. **Unified Schema (`bunker.diagnostics.v1`)**: Every phase of the compiler—lexing, parsing, import resolution, name resolution, typechecking, verification, borrow/ownership tracking, and C code generation—emits diagnostics conforming strictly to one shared envelope.
2. **Dual-Compiler Identity**: Both the reference Rust CLI (`bunker-cli`) and the self-hosting compiler (`bkrc.bkr`) evaluate identical semantic rules and emit interchangeable diagnostic records.
3. **Machine-Applicable Edits**: Every diagnostic that has an unambiguous syntactic or semantic repair emits a structured text edit (`Replacement` / `suggested_edits`) with byte-exact boundaries, allowing agents to apply fixes with zero syntax guessing.
4. **Calibrated Confidence**: Fixes explicitly declare their applicability (`machine-applicable`, `maybe-applicable`, `manual_review`) and calibrated confidence (`high`, `medium`, `low`), preventing agents from blindly applying speculative refactorings.

```
+---------------------------------------------------------------------------------------------------+
|                        Bunker Unified Diagnostics Architecture (BKR-SPEC-DIAG-003)                 |
+---------------------------------------------------------------------------------------------------+
|                                                                                                   |
|  Compiler Pipeline:                                                                               |
|  [Lexer] -> [Parser] -> [Importer] -> [Resolver] -> [Typechecker] -> [Verifier] -> [Codegen]      |
|     |           |            |             |               |              |             |         |
|     +-----------+------------+-------------+---------------+--------------+-------------+         |
|                                            |                                                      |
|                                            v                                                      |
|                   +--------------------------------------------------+                            |
|                   |       Diagnostic Builder & Code Registry         |                            |
|                   |  - Standard E-codes <-> Symbolic BKR_SELF rules  |                            |
|                   |  - Byte spans & line/column coordinates          |                            |
|                   |  - Expected / found type & token models          |                            |
|                   |  - Related secondary locations (declarations)    |                            |
|                   |  - Machine-applicable replacement edits          |                            |
|                   |  - Calibrated confidence & applicability         |                            |
|                   |  - Prompt-ready LLM repair guidance              |                            |
|                   +--------------------------------------------------+                            |
|                                            |                                                      |
|                                            v                                                      |
|                   +--------------------------------------------------+                            |
|                   |       Unified Envelope: bunker.diagnostics.v1    |                            |
|                   |  {                                               |                            |
|                   |    "schema_version": "bunker.diagnostics.v1",    |                            |
|                   |    "file": "src/main.bkr",                       |                            |
|                   |    "success": false,                             |                            |
|                   |    "diagnostics": [ { ... } ],                   |                            |
|                   |    "ai_prompt_context": { ... },                 |                            |
|                   |    "summary": { "total": 1, "errors": 1 }        |                            |
|                   |  }                                               |                            |
|                   +--------------------------------------------------+                            |
|                                                                                                   |
+---------------------------------------------------------------------------------------------------+
```

---

## 2. Canonical Unified Envelope Schema (`bunker.diagnostics.v1`)

The canonical envelope encapsulates compiler diagnostic sessions across all phases.

### 2.1 Root Envelope Specification
```json
{
  "schema_version": "bunker.diagnostics.v1",
  "file": "string",
  "success": "boolean",
  "summary": {
    "total": "integer",
    "errors": "integer",
    "warnings": "integer"
  },
  "diagnostics": [
    {
      "error_code": "string",
      "rule_id": "string",
      "severity": "error | warning | info | hint",
      "phase": "lex | parse | import | resolver | typecheck | verify | ownership | codegen | runtime",
      "message": "string",
      "location": {
        "file": "string",
        "line": "integer",
        "column": "integer",
        "source_start": "integer",
        "source_end": "integer",
        "source_line": "string",
        "context": "string"
      },
      "ai_prompt_hint": "string",
      "expected": {
        "type": "string",
        "reason": "string (optional)"
      },
      "found": {
        "type": "string",
        "source": "string (optional)"
      },
      "suggestions": [
        {
          "message": "string",
          "kind": "insert | replace | delete",
          "source_start": "integer",
          "source_end": "integer",
          "replacement": "string",
          "applicability": "machine-applicable | maybe-applicable | manual_review",
          "confidence": "high | medium | low"
        }
      ],
      "related": [
        {
          "location": {
            "file": "string",
            "line": "integer",
            "column": "integer",
            "source_start": "integer",
            "source_end": "integer"
          },
          "message": "string"
        }
      ]
    }
  ],
  "ai_prompt_context": {
    "purpose": "Compiler feedback for AI repair loops",
    "summary": "string",
    "instructions": [ "string" ],
    "prompt_addition": "string"
  }
}
```

---

## 3. Stable Diagnostic Code Registry Parity (`A-002`)

To ensure deterministic agent reasoning across the Rust compiler (`bunker-cli`) and the self-host compiler (`bkrc.bkr`), all diagnostic codes share a 1:1 bidirectional mapping between the standard numeric `E0xxx` codes and symbolic `BKR_SELF_xxx` rule identifiers.

### 3.1 Master Code & Rule ID Registry Table

| Standard Code | Symbolic Rule ID | Phase | Category | Description |
|---|---|---|---|---|
| `E0101` | `BKR_SELF_PARSE` | `parse` | `syntax` | Parse error with expected/actual token details |
| `E0201` | `BKR_SELF_TYPE_MISMATCH` | `typecheck` | `type_system` | Expression or statement type mismatch |
| `E0202` | `BKR_SELF_UNRESOLVED_SYMBOL` | `resolver` | `name_resolution` | Undefined variable or symbol in scope |
| `E0203` | `BKR_SELF_UNRESOLVED_SYMBOL` | `resolver` | `name_resolution` | Undefined function in current scope |
| `E0204` | `BKR_SELF_ARITY_MISMATCH` | `typecheck` | `type_system` | Function call argument count mismatch |
| `E0205` | `BKR_SELF_TYPE_MISMATCH` | `typecheck` | `type_system` | Function call argument type mismatch |
| `E0206` | `BKR_SELF_RETURN_PATH` | `typecheck` | `control_flow` | Return statement type mismatch or missing return |
| `E0207` | `BKR_SELF_CONTROL_FLOW` | `typecheck` | `control_flow` | Condition expression must evaluate to boolean |
| `E0208` | `BKR_SELF_TYPE_MISMATCH` | `typecheck` | `type_system` | Cannot index non-indexable type |
| `E0209` | `BKR_SELF_STRUCT_LITERAL` | `typecheck` | `type_system` | No such field on struct or type |
| `E0210` | `BKR_SELF_STRUCT_LITERAL` | `typecheck` | `type_system` | Unknown struct type in literal or declaration |
| `E0211` | `BKR_SELF_AMBIGUOUS_TYPE` | `typecheck` | `type_system` | `None` requires explicit `Option<T>` type annotation |
| `E0212` | `BKR_SELF_MATCH_PATTERN` | `typecheck` | `pattern_matching` | Match arm pattern type incompatible with scrutinee |
| `E0213` | `BKR_SELF_VOID_VALUE` | `typecheck` | `type_system` | Match block expression does not produce a value |
| `E0301` | `BKR_SELF_CONTRACT` | `verify` | `contract` | Contract precondition or postcondition violated |
| `E0302` | `BKR_SELF_CONTRACT` | `verify` | `contract` | Unsupported postcondition in verification mode |
| `E0303` | `BKR_SELF_SMT_TIMEOUT` | `verify` | `contract` | SMT solver query timed out |
| `E0304` | `BKR_SELF_SMT_UNAVAILABLE` | `verify` | `contract` | SMT solver unavailable or disabled |
| `E0401` | `BKR_SELF_USE_AFTER_MOVE` | `ownership` | `linear_types` | Use of value after linear ownership transfer |
| `E0501` | `BKR_SELF_ASSIGNMENT_TARGET` | `typecheck` | `control_flow` | Assignment to non-assignable expression |
| `E0502` | `BKR_SELF_CONST_ASSIGNMENT` | `typecheck` | `control_flow` | Assignment attempts to modify a constant |
| `E0601` | `BKR_SELF_VIEW_BINDING` | `view` | `reactive_state` | Unknown state field in view component binding |
| `E0602` | `BKR_SELF_VIEW_BINDING` | `view` | `reactive_state` | Unknown view agent binding |
| `E0701` | `BKR_SELF_IMPORT` | `import` | `module` | Missing imported module |
| `E0702` | `BKR_SELF_IMPORT_CYCLE` | `import` | `module` | Circular import dependency detected |
| `E0703` | `BKR_SELF_IMPORT_PATH` | `import` | `module` | Invalid normalized relative import path |
| `E0801` | `BKR_SELF_GENERIC_ARITY` | `typecheck` | `generics` | Generic type argument count mismatch |
| `E0802` | `BKR_SELF_GENERIC_INFERENCE` | `typecheck` | `generics` | Generic type parameter inference failed |
| `E0803` | `BKR_SELF_GENERIC_LIMIT` | `typecheck` | `generics` | Generic monomorphization recursion limit exceeded |
| `E0804` | `BKR_SELF_GENERIC_PARAM` | `typecheck` | `generics` | Unknown generic type parameter |

---

## 4. Exact Source Spans & Excerpts (`A-003`)

Bunker requires exact span tracking across all compiler phases:
1. **Byte Bounds (`source_start`, `source_end`)**: 0-based character offsets into the source file UTF-8 buffer.
2. **Line & Column Coordinates (`line`, `column`)**: 1-based human-readable text editor coordinates.
3. **Source Excerpt (`source_line`)**: Verbatim slice of the source line containing the error.
4. **Context Descriptor (`context`)**: Semantic container identifier (e.g. `fn calculate_total`, `struct Point`, `module driver`).

```json
"location": {
  "file": "src/math.bkr",
  "line": 42,
  "column": 13,
  "source_start": 845,
  "source_end": 857,
  "source_line": "    let x: i64 = \"hello\";",
  "context": "fn calculate_total"
}
```

---

## 5. Expected / Found Details (`A-004`)

Diagnostics specify exact expected vs. actual artifacts using structured objects rather than vague strings:
- **Parse Phase**: Expected token kinds (e.g. `TOK_SEMICOLON`, `TOK_RBRACE`) vs actual token encountered.
- **Typecheck Phase**: Expected type name and reason (e.g. `expected: { "type": "i64", "reason": "variable annotation" }`) vs found type name and source (e.g. `found: { "type": "str", "source": "literal" }`).
- **Resolver Phase**: Expected declaration kind vs actual symbol resolution state.
- **Arity Phase**: Expected parameter count vs provided argument count.

---

## 6. Suggested Fix Edits (`A-005`)

Whenever the compiler has sufficient information to deduce a deterministic repair, it attaches a `suggestions` array with machine-applicable edit records:
```json
"suggestions": [
  {
    "message": "Insert missing semicolon ';'",
    "kind": "insert",
    "source_start": 857,
    "source_end": 857,
    "replacement": ";",
    "applicability": "machine-applicable",
    "confidence": "high"
  }
]
```

### 6.1 Supported Edit Kinds
- `insert`: Insert `replacement` text at `source_start` (where `source_start == source_end`).
- `replace`: Replace text range `[source_start..source_end]` with `replacement`.
- `delete`: Remove text range `[source_start..source_end]` (where `len(replacement) == 0`).

---

## 7. Calibrated Confidence Levels (`A-006`)

To prevent autonomous agents from hallucinating destructive fixes, every suggestion carries a calibrated confidence and applicability rating:

| Level | Confidence String | Numerical Weight | Applicability String | Policy / Semantics |
|---|---|---|---|---|
| **High** | `"high"` | `0.95` | `"machine-applicable"` | Safe to apply automatically without human/LLM review (e.g. missing semicolon, obvious typo with unique match). |
| **Medium** | `"medium"` | `0.75` | `"maybe-applicable"` | Likely intended fix, but semantic review recommended (e.g. type cast, mutability declaration, missing return). |
| **Low** | `"low"` | `0.40` | `"manual_review"` | Heuristic suggestion or architectural alternative; agent should re-evaluate program structure. |

---

## 8. Related Spans (`A-007`)

Compiler diagnostics frequently involve multiple source locations. For example:
- **Duplicate Symbol**: Points to the re-declaration site, with `related` pointing to the first declaration site.
- **Use After Move**: Points to the illegal use site, with `related` pointing to the prior transfer site.
- **Type Mismatch on Return**: Points to the return statement, with `related` pointing to the function signature declaration.

```json
"related": [
  {
    "location": {
      "file": "src/math.bkr",
      "line": 15,
      "column": 5,
      "source_start": 210,
      "source_end": 225
    },
    "message": "Previous declaration of symbol 'calculate_total' was here"
  }
]
```

---

## 9. Prompt-Ready Explanations & LLM Context (`A-008`)

To maximize AI self-correction success, the diagnostic output contains a top-level `ai_prompt_context` object designed for direct injection into subsequent LLM completion turns:

```json
"ai_prompt_context": {
  "purpose": "Compiler feedback for AI repair loops",
  "summary": "Bunker check failed with 1 error(s) and 0 warning(s).",
  "instructions": [
    "Use diagnostics as authoritative constraints.",
    "Do not silence errors with raw i64 handle casts unless a diagnostic explicitly recommends an explicit typed roundtrip.",
    "Prefer adding explicit type annotations over relying on inference when the compiler asks for context.",
    "After editing, rerun bunker check with --format=json and use the new diagnostics as the next prompt addition."
  ],
  "prompt_addition": "Bunker check failed with 1 error(s) and 0 warning(s).\nRepair the source while preserving the user's intent. Prefer the smallest code change that satisfies the compiler.\n1. [E0201] Type mismatch: expected i64, found str at src/math.bkr:42:13\n   Hint: Expression evaluates to str but context requires i64; verify numeric literal or conversion function\n   Expected: i64\n   Found: str"
}
```

---

## 10. Conformance & Verification Matrix

| Track Item | Name | Module Implementation | Verification Fixture | Status |
|---|---|---|---|---|
| `A-001` | JSON Diagnostics Envelope | `self-host/modules/diagnostic.bkr` | `tests/254_unified_diagnostic_envelope.bkr` | DONE |
| `A-002` | Stable Diagnostic Codes | `self-host/modules/diagnostic.bkr` | `tests/255_diagnostic_code_registry_parity.bkr` | DONE |
| `A-003` | Exact Spans & Excerpts | `self-host/modules/diagnostic.bkr` | `tests/254_unified_diagnostic_envelope.bkr` | DONE |
| `A-004` | Expected / Found Details | `self-host/modules/diagnostic.bkr` | `tests/254_unified_diagnostic_envelope.bkr` | DONE |
| `A-005` | Suggested Fix Edits | `self-host/modules/diagnostic.bkr` | `tests/254_unified_diagnostic_envelope.bkr` | DONE |
| `A-006` | Calibrated Confidence Levels | `self-host/modules/diagnostic.bkr` | `tests/254_unified_diagnostic_envelope.bkr` | DONE |
| `A-007` | Related Spans | `self-host/modules/diagnostic.bkr` | `tests/254_unified_diagnostic_envelope.bkr` | DONE |
| `A-008` | Prompt-Ready Explanations | `self-host/modules/diagnostic.bkr` | `tests/255_diagnostic_code_registry_parity.bkr` | DONE |
| `A-009` | Multi-Error Recovery | `self-host/modules/parser.bkr` | `tests/253_parse_recovery_multi_error.bkr` | DONE |
| `A-010` | Machine-Readable AST Dump | `bunker-cli` & `self-host` | `tests/222_typed_ast_report.bkr` | DONE |
| `A-011` | Machine-Readable Type Graph | `bunker-cli` & `self-host` | `tests/224_type_graph_report.bkr` | DONE |
| `A-012` | Machine-Readable Symbol Table | `bunker-cli` & `self-host` | `tests/225_symbol_table_report.bkr` | DONE |
| `A-013` | Capability Report | `bunker-cli` & `self-host` | `tests/226_typecheck_resolver_reports.bkr` | DONE |
| `A-014` | Typecheck Diagnostics | `bunker-cli` & `self-host` | `tests/240_type_diagnostics_parity.bkr` | DONE |
