# Bunker Deterministic Formatter and Static Linter Architecture Specification

- **Document ID:** `BKR-SPEC-TOOL-001`
- **Track:** Tooling (`TL`)
- **Milestones Covered:** `G-001` (P1: Formatter), `G-002` (P1: Linter)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.capability.v1`, `bunker.fmt.v1`, `bunker.lint.v1`

---

## 1. Executive Summary

This specification formalizes the architecture for the Bunker Deterministic Code Formatter (`G-001`, `bunker fmt`) and Static Analysis Linter (`G-002`, `bunker lint`) across the toolchain.

High-velocity systems programming and autonomous AI-agent pair programming require absolute determinism in code representation and automated static code quality gates. Style disagreements, whitespace diff noise, and undetected dead bindings create friction and degrade AI patch reliability.

This architecture establishes:
1. **Deterministic AST-Driven Formatting (`G-001`):** Canonical 4-space indentation, standardized delimiter spacing, line-ending normalization (pure LF `\n`), and strict mathematical idempotency ($F(F(x)) = F(x)$).
2. **Static Analysis Linting Engine (`G-002`):** Compile-time detection of unused variables (`W001`), dead statements (`W002`), redundant casts (`W003`), variable shadowing (`W004`), and naming convention deviations (`W005`).
3. **Unified Diagnostics Integration:** Linter warnings emit through the canonical `bunker.diagnostics.v1` envelope with exact byte spans and machine-applicable suggested fixes.

With this specification and implementation, items `G-001` and `G-002` transition to `DONE`, officially launching Track `TL` (Tooling).

---

## 2. Deterministic Code Formatter (G-001)

### 2.1 Formatting Pipeline

The formatter operates through AST parsing and structured pretty-printing:
$$\text{Source Code} \xrightarrow{\text{Parse}} \text{AST} \xrightarrow{\text{PrettyPrint}} \text{Canonical Source}$$

### 2.2 Formal Invariants

- **Invariant FMT-01 (Semantic Equivalence):** The AST generated from formatting source $S$ is structurally identical to the AST of $S$. The formatter alters layout, whitespace, and comment placement, but never syntax or program semantics.
- **Invariant FMT-02 (Canonical Indentation):** Indentation is strictly 4 spaces per nesting level. Tab characters (`\t`) are converted to 4 spaces or rejected. No trailing whitespace is permitted on any line.
- **Invariant FMT-03 (Delimiter & Operator Spacing):**
  - Binary arithmetic, logical, and relational operators (`+`, `-`, `*`, `/`, `==`, `!=`, `<`, `>`, `&&`, `||`) are padded with exactly one space on each side.
  - Colons (`:`) in type annotations and map pairs have no leading space and one trailing space (`x: i32`).
  - Commas (`,`) and semicolons (`;`) have no leading space and one trailing space (or newline).
  - Arrow operators (`->`) have one leading and one trailing space (`fn main() -> i32`).
  - Braces (`{`, `}`) follow one-true-brace-style (1TBS): opening brace on the same line preceded by a space, closing brace on its own line matching block indentation.
- **Invariant FMT-04 (Mathematical Idempotency):**
  $$F(F(S)) = F(S) \quad \forall S \in \text{ValidBunkerPrograms}$$
  Formatting an already formatted file produces a zero-byte diff.
- **Invariant FMT-05 (Pure LF Line Endings):** All newline sequences are normalized to `0x0A` (LF). Carriage returns (`\r`, `0x0D`) are stripped unconditionally.

### 2.3 Formatter Manifest Schema (`bunker.fmt.v1`)

When executed in check or machine mode (`bunker fmt --check --json <file>`):
```json
{
  "schema_version": "bunker.fmt.v1",
  "file": "src/main.bkr",
  "is_formatted": true,
  "lines_formatted": 142,
  "bytes_changed": 0,
  "diff_summary": "clean"
}
```

---

## 3. Static Analysis Linter (G-002)

### 3.1 Architecture & Analysis Passes

The linter runs AST-walking and symbol-table analysis passes without requiring machine code generation:
1. **Declaration vs Reference Pass:** Compares declared symbols against reference counts in lexical scopes.
2. **Control Flow Reachability Pass:** Inspects block statement sequences for statements appearing after terminating flow.
3. **Type Consistency Pass:** Identifies identity casts and redundant type assertions.

### 3.2 Lint Rule Catalog

| Rule ID | Code | Category | Description | Default Action |
|---|---|---|---|---|
| `W001` | `BKR_LINT_UNUSED_VAR` | `safety` | Variable declared with `let` but never read in its lexical scope. | Prefix with `_` or remove binding. |
| `W002` | `BKR_LINT_DEAD_CODE` | `correctness` | Statement appears after an unconditional `return`, `break`, or `continue`. | Delete unreachable statement. |
| `W003` | `BKR_LINT_REDUNDANT_CAST` | `style` | Value cast to its own existing type (`x as i32` where `x: i32`). | Remove redundant `as Type`. |
| `W004` | `BKR_LINT_VARIABLE_SHADOW` | `safety` | Inner block declaration shadows an identically named outer variable. | Rename inner variable. |
| `W005` | `BKR_LINT_NAMING_CONVENTION` | `style` | Top-level Kernel/Struct should be `UpperCamelCase`; functions and variables should be `snake_case`. | Normalize identifier casing. |

### 3.3 Diagnostic Output Schema (`bunker.lint.v1`)

Linter diagnostics integrate with `bunker.diagnostics.v1`:
```json
{
  "schema_version": "bunker.lint.v1",
  "file": "src/kernel.bkr",
  "rule_id": "BKR_LINT_UNUSED_VAR",
  "code": "W001",
  "severity": "warning",
  "message": "Variable 'unused_counter' is declared but never used",
  "source_start": 412,
  "source_end": 426,
  "source_line": 15,
  "source_column": 9,
  "suggested_fix": {
    "kind": "replace",
    "range": [412, 426],
    "replacement": "_unused_counter"
  }
}
```

---

## 4. Verification Matrix

| Test ID | Fixture File | Verification Criteria | Expected Exit |
|---|---|---|---|
| `T-TOOL-01` | `tests/274_code_formatter_deterministic.bkr` | Canonical 4-space indentation, operator spacing, brace placement, line-ending normalization, idempotency $F(F(x)) = F(x)$ | `42` |
| `T-TOOL-02` | `tests/275_static_linter_safety_rules.bkr` | Detection of unused variables (`W001`), dead code (`W002`), redundant casts (`W003`), shadow warnings (`W004`), and structured suggested fixes | `42` |

---

## 5. Status & Completion

With this specification approved and implemented:
- Track: Tooling (`TL`)
  * `G-001` (Formatter): `DONE`
  * `G-002` (Linter): `DONE`
  * Track `TL` progress: `2 / 12` items `DONE` (16.7%).
- Overall Ecosystem: **143 / 168** items `DONE` (85.1%).
