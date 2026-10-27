# Bunker C Codegen Temporaries and Portability Specification

- **Document ID:** `BKR-SPEC-CGEN-002`
- **Track:** Compiler Backend (`CB`)
- **Milestones Covered:** `CB-003` (P1: Temporary variable generation), `CB-004` (P1: Portable C output)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.capability.v1`, `bunker.self_host.cgen.v1`

---

## 1. Executive Summary

This specification formalizes temporary variable allocation hygiene (`CB-003`) and C dialect portability invariants (`CB-004`) for the Bunker self-host compiler C backend (`self-host/modules/c_codegen.bkr` and `self-host/modules/cgen_state.bkr`).

Bunker is an expression-oriented language where blocks, match statements, and error propagation (`?`) produce values in expression contexts. This document defines the monotonic allocation of hygienic identifiers for nested expressions and locks the GNU C dialect contract (`gnu99` / `gnu11`) enabling statement expressions `({ ...; expr; })` across GCC, Clang, and compatible toolchains.

With this specification and implementation, Track `CB` items `CB-003` (Temporary variable generation) and `CB-004` (Portable C output) transition to `DONE`.

---

## 2. Temporary Variable Generation & Hygiene (CB-003)

### 2.1 Monotonic Allocation Architecture

All synthetic temporary variables required during C lowering are generated through `cgen_next_hygienic_temp_ref(state, prefix)` in `self-host/modules/cgen_state.bkr`.

The state maintains an internal integer sequence (`temp_counter` in slot 16 of `CgenStateRef`) that increments monotonically for every temporary requested within a translation unit:

| Temporary Prefix | Purpose | Emitted Format |
|---|---|---|
| `_blk_res` | Result variable for expression-oriented blocks | `_blk_res_<id>` |
| `_match_val` | Evaluated scrutinee value for pattern matching | `_match_val_<id>` |
| `_match_res` | Yielded expression value for match arms | `_match_res_<id>` |
| `_matched` | Arm match flag ensuring first-arm-wins semantics | `_matched_<id>` |
| `_bkr_try` | Intermediate Result/Option value for `?` operator | `_bkr_try_<id>` |
| `_bkr_ret` | Preserved return value during LIFO defer execution | `_bkr_ret_<id>` |

### 2.2 Invariants for Nested Expressions

- **Invariant CGEN-TEMP-01 (Strict Hygiene):** Every temporary name within a generated C function is unique. No temporary variable shares a name with another temporary variable or user variable, even when identical expression structures are nested.
- **Invariant CGEN-TEMP-02 (Nested Block Stability):** In deeply nested block expressions (e.g. `{ let a = { 10 }; a + { 20 } }`), the outer and inner blocks receive distinct, non-overlapping result identifiers (`_blk_res_0`, `_blk_res_1`, `_blk_res_2`). Variable shadowing in statement expressions is eliminated.
- **Invariant CGEN-TEMP-03 (Nested Match Integrity):** A pattern match expression evaluated inside another match arm receives its own dedicated `_match_val_<id>`, `_match_res_<id>`, and `_matched_<id>`, guaranteeing that outer match arm flags cannot be mutated or corrupted by inner matching logic.

---

## 3. C Portability & Dialect Lock (CB-004)

### 3.1 Locked Dialect: GNU-C (`gnu99` / `gnu11`)

- **Invariant CGEN-PORT-01 (GNU Statement Expressions Locked):** Bunker lowers expression blocks, inline pattern matches, and `?` try-unwrapping into GNU statement expressions `({ ...; result; })`. This capability is explicitly locked and documented as a foundational compiler backend requirement.
- **Invariant CGEN-PORT-02 (Toolchain Conformance):** The generated C output is guaranteed to compile cleanly without warnings or errors under:
  - GCC 7.0+ (`gcc -std=gnu11 -O2`)
  - Clang 6.0+ (`clang -std=gnu11 -O2`)
  - MinGW-w64 (`x86_64-w64-mingw32-gcc -std=gnu11`)
  - Apple Clang (macOS default Xcode toolchain)
- **Invariant CGEN-PORT-03 (ISO C Standard Compatibility):** Outside statement expressions, all generated declarations, types, and statements conform strictly to ISO C99:
  - Exact-width integers: `int32_t` (`bkr_i32`), `int64_t` (`bkr_i64`), `uint8_t` (`bkr_bool`).
  - Floating-point: IEEE-754 `double` (`bkr_f64`).
  - Strings: null-terminated UTF-8 byte pointers `const char*` (`bkr_str`).
  - Standard headers: `<stdint.h>`, `<stdbool.h>`, `<stdlib.h>`, `<string.h>`, `<stdio.h>`.

---

## 4. Capability JSON Schema Integration

The self-host compiler driver (`self-host/modules/driver.bkr`) exposes these properties in `bunker.capability.v1`:

```json
{
  "modular_c_codegen": true,
  "typed_c_emission": true,
  "cgen_state_ref_routing": true,
  "hygienic_temporaries": true,
  "gnu_statement_expressions_locked": true,
  "c99_standard_portability": true
}
```

---

## 5. Verification Matrix

| Milestone | Feature | Test Fixture | Expected Result |
|---|---|---|---|
| `CB-003` | Hygienic Temporaries & Nested Expressions | `tests/264_codegen_hygienic_temporaries.bkr` | Returns 42 |
| `CB-004` | Statement Expressions & Portability | `tests/265_portable_c_statement_expressions.bkr` | Returns 42 |
| `CB-003/4`| Self-Host Full Compilation Subset | `run_tests.ps1` (`$selfHostSubset`) | 100% Pass Rate |
