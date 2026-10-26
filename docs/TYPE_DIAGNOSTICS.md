# BKR-SPEC-DIAG-002: Bunker Type Diagnostics, Origin Tracking, and Dual-Compiler Parity Architecture

- **Status**: CANONICAL / LOCKED (2026-10-26)
- **Document ID**: `BKR-SPEC-DIAG-002`
- **Track**: Type System (`T`), Diagnostics & AI-Agent Interface
- **Items Addressed**:
  - `T-024`: Type diagnostics (expected/found type models, byte spans, origin tracking, actionable repair hints, dual-compiler parity)
  - `A-001` / `A-014`: Machine-readable `BUNKER_TYPECHECK_JSON` schema (`bunker.typecheck.v1` and `bunker.self_host.typecheck.v1`)
  - Officially closes Track `T` (Type System) at 100.0% completion (24 / 24 DONE)
- **Conformance Test Fixtures**:
  - `tests/226_typecheck_resolver_reports.bkr` (CLI report flags validation)
  - `tests/240_type_diagnostics_parity.bkr` (Type diagnostics parity, clean report verification, negative diagnostic structure)
  - Canonical negative test suite verifying diagnostic codes:
    - `tests/141_match_bool_nonexhaustive_BAD.bkr` (`BKR_SELF_EXHAUSTIVENESS`)
    - `tests/145_pattern_duplicate_literal_BAD.bkr` (`BKR_SELF_MATCH_PATTERN`)
    - `tests/151_builtin_arity_mismatch_BAD.bkr` (`BKR_SELF_ARITY_MISMATCH`)
    - `tests/156_ambiguous_empty_array_BAD.bkr` (`BKR_SELF_AMBIGUOUS_TYPE`)
    - `tests/162_cast_struct_to_int_BAD.bkr` (`BKR_SELF_TYPE_MISMATCH`)
    - `tests/174_method_non_struct_BAD.bkr` (`BKR_SELF_TYPE_MISMATCH`)
    - `tests/177_struct_update_wrong_base_BAD.bkr` (`BKR_SELF_TYPE_MISMATCH`)
    - `tests/180_block_expr_type_mismatch_BAD.bkr` (`BKR_SELF_TYPE_MISMATCH`)
    - `tests/186_higher_order_fn_arity_mismatch_BAD.bkr` (`BKR_SELF_ARITY_MISMATCH`)
    - `tests/191_private_kernel_call_BAD.bkr` (`BKR_SELF_CALL_TARGET`)
    - `tests/206_string_escape_hex_invalid_BAD.bkr` (Lexer/Parser diagnostic)
    - `tests/209_slice_type_mismatch_BAD.bkr` (`BKR_SELF_TYPE_MISMATCH`)
    - `tests/212_module_cycle_BAD.bkr` (`E0702`)
    - `tests/217_generic_arg_count_BAD.bkr` (`E0801`)
    - `tests/236_struct_operator_overload_BAD.bkr` (`E0201` / `BKR_SELF_TYPE_MISMATCH`)
    - `tests/238_generic_constraint_missing_method_BAD.bkr` (`E0201` / `BKR_SELF_TYPE_MISMATCH`)

---

## 1. Executive Summary & Epistemic Foundations

In traditional compiler engineering (e.g. GCC, Clang, rustc), diagnostics are rendered primarily as stylized terminal prose (colorized ANSI text, ASCII art squiggles, and terminal line wraps). While visually helpful for human developers reading a terminal, this format presents severe failure modes for modern automated workflows:
1. **Fragile Regex Scraping**: IDE language servers and AI agents must parse non-standardized multi-line text strings to guess where an error occurred and what type was expected.
2. **Ambiguous Error Cascades**: A single root cause often triggers dozens of downstream secondary errors, burying the actual defect.
3. **Loss of Semantic Type Context**: Text diagnostics display pretty-printed display strings (`"&mut std::vec::Vec<T>"`) rather than structured type model representations that automated tools can programmatically inspect and reason about.
4. **Drift Between Compilers**: In bootstrapping language environments, the production compiler (e.g. Rust CLI) and the self-host compiler (pure Bunker `bkrc.bkr`) frequently diverge in error messages, capability sets, and reporting schemas, creating split-brain debugging scenarios.

### The Bunker Principle: Dual-Compiler Structured Type Diagnostics
Bunker treats compiler diagnostics as a first-class, machine-readable API:
1. **Canonical Schema (`bunker.typecheck.v1`)**: All typecheck validation results are emitted in a standardized, machine-readable JSON envelope containing explicit capability flags, summary counts, and structured diagnostic arrays.
2. **Exact Origin Tracking**: Diagnostics carry exact source byte offsets (`source_start`, `source_end`, `span_known`) and lexical scopes (`scope`, `name`) enabling single-character precision in IDE markers and automated code repair agents.
3. **Structured Expected / Found Models**: Diagnostics report both textual descriptors (`expected`, `found`) and formal type objects (`expected_type`, `found_type`), allowing automated reasoning engines to perform precise type unification and constraint checking.
4. **Actionable Repair Metadata**: Every diagnostic contains a structured repair envelope (`repair_hint`, `suggested_action`, `fix_applicability`, `fix_confidence`, `safe_edit_available`, `suggested_edits`) directly consumable by autonomous coding agents.
5. **Dual-Compiler Parity**: Both `bunker-cli` (Rust) and the pure Bunker self-host compiler (`self-host/modules/typecheck.bkr`) evaluate identical semantic rules and report matching capability flag matrices.

---

## 2. Schema Architecture (`bunker.typecheck.v1`)

The typecheck report is emitted either via CLI flag (`bunker check --typecheck-json <file>`) or as a top-level comment block prepended to generated artifacts (`/* BUNKER_TYPECHECK_JSON: { ... } */`).

### 2.1 Top-Level Report Envelope

```json
{
  "schema_version": "bunker.typecheck.v1",
  "compiler": "bunker-cli",
  "representation": "typecheck_diagnostics_pass",
  "complete": true,
  "annotation_checks": true,
  "return_checks": true,
  "condition_checks": true,
  "call_argument_checks": true,
  "call_arity_checks": true,
  "call_target_checks": true,
  "builtin_arity_checks": true,
  "builtin_argument_type_checks": true,
  "entry_point_checks": true,
  "entry_signature_checks": true,
  "assignment_target_checks": true,
  "const_assignment_checks": true,
  "struct_field_value_checks": true,
  "struct_field_shape_checks": true,
  "ambiguous_empty_array_checks": true,
  "ambiguous_none_checks": true,
  "ambiguous_result_constructor_checks": true,
  "ambiguous_collection_constructor_checks": true,
  "index_base_type_checks": true,
  "index_type_checks": true,
  "binary_operand_checks": true,
  "unary_operand_checks": true,
  "field_access_base_checks": true,
  "ternary_branch_checks": true,
  "match_arm_type_checks": true,
  "match_pattern_type_checks": true,
  "match_pattern_semantic_checks": true,
  "bool_match_exhaustiveness_checks": true,
  "option_match_exhaustiveness_checks": true,
  "result_match_exhaustiveness_checks": true,
  "enum_match_exhaustiveness_checks": true,
  "scalar_match_exhaustiveness_checks": true,
  "finite_match_redundancy_checks": true,
  "array_element_type_checks": true,
  "loop_control_checks": true,
  "return_path_checks": true,
  "unreachable_code_checks": true,
  "void_value_checks": true,
  "compound_void_value_checks": true,
  "full_value_context_void_checks": true,
  "typed_diagnostic_context": true,
  "structured_repair_metadata": true,
  "diagnostic_phase_field": true,
  "diagnostic_rule_ids": true,
  "diagnostic_severity": true,
  "diagnostic_severity_counts": true,
  "suggested_edit_envelope": true,
  "has_diagnostics": false,
  "diagnostic_count": 0,
  "error_count": 0,
  "warning_count": 0,
  "known_limits": "Typecheck report validates declared annotations, return values and return paths, conditions, ternary branches, match patterns and arm values, array elements, loop-control context, unreachable statements, assignments, index bases/expressions, field-access bases, unary/binary operands, call arguments, call targets, builtin argument types, entry-point presence/signature, and struct literal field values/shapes.",
  "diagnostics": []
}
```

### 2.2 Structured Diagnostic Object

When typecheck errors are detected, `diagnostics` contains detailed diagnostic records:

```json
{
  "phase": "typecheck",
  "kind": "type_mismatch",
  "rule_id": "E0201",
  "error_code": "E0201",
  "severity": "error",
  "name": "main",
  "scope": "function:main",
  "source_start": 580,
  "source_end": 586,
  "span_known": true,
  "expected": "Named(\"Vector\")",
  "found": "I32",
  "expected_type": "Named(\"Vector\")",
  "found_type": "I32",
  "suggested_action": "Make the expression type match the expected type. Prefer changing the expression or adding an explicit annotation over broad casts.",
  "fix_applicability": "manual_review",
  "fix_confidence": "medium",
  "safe_edit_available": false,
  "suggested_edits": [],
  "repair_hint": "Make the expression type match the expected type. Prefer changing the expression or adding an explicit annotation over broad casts."
}
```

---

## 3. The 45 Semantic Check Capability Flags

The schema exposes exactly 45 boolean capability flags detailing every semantic domain verified by the typechecker:

| # | Capability Flag | Semantic Domain | Verified Invariant |
|---|---|---|---|
| 1 | `annotation_checks` | Local Bindings | Let binding initializer types match explicit type annotations. |
| 2 | `return_checks` | Functions | Return expression values match declared function return types. |
| 3 | `condition_checks` | Control Flow | `if`, `while`, and ternary condition expressions evaluate to `bool`. |
| 4 | `call_argument_checks` | Invocations | Argument expressions match declared function parameter types. |
| 5 | `call_arity_checks` | Invocations | Call argument counts match declared parameter arities. |
| 6 | `call_target_checks` | Invocations | Invocations target valid callable functions, methods, or function pointers. |
| 7 | `builtin_arity_checks` | Standard Library | Builtin function calls supply the exact required argument count. |
| 8 | `builtin_argument_type_checks` | Standard Library | Builtin function arguments conform to strict builtin type signatures. |
| 9 | `entry_point_checks` | Program Structure | Kernel contains an accessible entry point (`main` or callable export). |
| 10 | `entry_signature_checks` | Program Structure | Entry point `main` has a valid signature (`() -> i32` or `() -> void`). |
| 11 | `assignment_target_checks` | Mutability | Assignment targets are mutable lvalues (`let mut` bindings, struct fields, array slots). |
| 12 | `const_assignment_checks` | Constants | Top-level constants (`const`) and immutable bindings cannot be reassigned. |
| 13 | `struct_field_value_checks` | Structs | Struct literal field expressions match declared struct field types. |
| 14 | `struct_field_shape_checks` | Structs | Struct literals provide all required fields without duplicates or unknown fields. |
| 15 | `ambiguous_empty_array_checks` | Inference | Empty array literals `[]` without contextual type annotations are diagnosed. |
| 16 | `ambiguous_none_checks` | Inference | `None` literals without contextual `Option<T>` annotations are diagnosed. |
| 17 | `ambiguous_result_constructor_checks` | Inference | `Ok(...)` / `Err(...)` without contextual `Result<T, E>` types are diagnosed. |
| 18 | `ambiguous_collection_constructor_checks` | Inference | `vec_new()` / `hashmap_new()` without contextual types are diagnosed. |
| 19 | `index_base_type_checks` | Projections | Index operations target valid indexable bases (arrays, slices, vectors). |
| 20 | `index_type_checks` | Projections | Array/slice/vector index expressions evaluate to integer types (`i32`, `i64`). |
| 21 | `binary_operand_checks` | Operators | Binary operator operands conform to closed primitive types (+, -, *, /, etc.). |
| 22 | `unary_operand_checks` | Operators | Unary operator operands conform to valid types (`!` requires `bool`, `-` requires numeric). |
| 23 | `field_access_base_checks` | Projections | Field projections `base.field` target valid struct types containing `field`. |
| 24 | `ternary_branch_checks` | Branching | Ternary `cond ? then_val : else_val` branches unify to a common type. |
| 25 | `match_arm_type_checks` | Pattern Matching | All match arm body expressions evaluate to a unified return type. |
| 26 | `match_pattern_type_checks` | Pattern Matching | Match patterns match the type of the scrutinee expression. |
| 27 | `match_pattern_semantic_checks` | Pattern Matching | Pattern bindings and guards satisfy variable scoping and mutability rules. |
| 28 | `bool_match_exhaustiveness_checks` | Exhaustiveness | Boolean matches cover both `true` and `false` or supply a catch-all. |
| 29 | `option_match_exhaustiveness_checks` | Exhaustiveness | Option matches cover `Some` and `None` or supply a catch-all. |
| 30 | `result_match_exhaustiveness_checks` | Exhaustiveness | Result matches cover `Ok` and `Err` or supply a catch-all. |
| 31 | `enum_match_exhaustiveness_checks` | Exhaustiveness | Enum matches cover all declared variants or supply a catch-all. |
| 32 | `scalar_match_exhaustiveness_checks` | Exhaustiveness | Scalar integer and string matches require a catch-all pattern (`_` or identifier). |
| 33 | `finite_match_redundancy_checks` | Pattern Matching | Duplicate patterns or unreachable arms following exhaustive patterns are rejected. |
| 34 | `array_element_type_checks` | Collections | Array literal elements evaluate to a homogeneous element type. |
| 35 | `loop_control_checks` | Control Flow | `break` and `continue` only appear within enclosing loop bodies. |
| 36 | `return_path_checks` | Control Flow | Non-void functions guarantee that all execution paths return a value. |
| 37 | `unreachable_code_checks` | Control Flow | Statements following unconditional `return`, `panic`, or `break` are diagnosed. |
| 38 | `void_value_checks` | Type System | Void expressions `()` are not used where a concrete value is required. |
| 39 | `compound_void_value_checks` | Type System | Void expressions cannot be elements of arrays or struct fields. |
| 40 | `full_value_context_void_checks` | Type System | Void values are rejected in call arguments, operators, and return values. |
| 41 | `typed_diagnostic_context` | Metadata | Diagnostics include structured expected and found type descriptors. |
| 42 | `structured_repair_metadata` | AI Tooling | Diagnostics carry actionable repair hints, applicability, and confidence. |
| 43 | `diagnostic_phase_field` | Schema | Diagnostics identify the originating compiler phase (`"typecheck"`). |
| 44 | `diagnostic_rule_ids` | Schema | Diagnostics identify the specific compiler rule ID (`"E0201"`, etc.). |
| 45 | `diagnostic_severity` | Schema | Diagnostics carry standard severity levels (`"error"`, `"warning"`). |

---

## 4. Origin Tracking & Byte Spans

Every diagnostic record provides exact source location metrics:
- **`source_start`**: Zero-based byte offset in the source file marking the start of the offending token or AST node.
- **`source_end`**: Zero-based byte offset marking the end of the offending token or AST node.
- **`span_known`**: Boolean indicating whether source coordinate mapping was successful (`true` for all valid syntax).
- **`scope`**: Lexical container (`"function:main"`, `"kernel:KernelName"`, `"struct:Point"`).
- **`name`**: Symbol or enclosing item name.

Byte spans eliminate ambiguities introduced by line breaks, tab stops, and CRLF vs LF line endings, enabling automated tools to perform precise in-place source replacements without line-wrapping recomputation.

---

## 5. Expected vs Found Typed Context Model

Type mismatches (`E0201`) provide structured type descriptors:
- **`expected`**: Human-readable description of the constraint (e.g. `"Named(\"Vector\")"`, `"i32"`, `"bool"`).
- **`found`**: Human-readable description of the actual type evaluated (e.g. `"I32"`, `"str"`).
- **`expected_type`**: Optional serialized type object for programmatic unifier comparison.
- **`found_type`**: Optional serialized type object for programmatic unifier comparison.

This bidirectional context enables automated solvers to differentiate between:
- Swapped arguments in function calls
- Missing dereferences or field projections
- Unintended scalar casts
- Missing structural method implementations

---

## 6. Structured Repair Metadata & Agent Guidance

Diagnostics include an actionable repair envelope designed for AI coding agents:
- **`repair_hint`**: Direct instructions on how to resolve the mismatch without introducing subtle architectural bugs.
- **`suggested_action`**: Actionable repair strategy (e.g. `"Make the expression type match the expected type. Prefer changing the expression or adding an explicit annotation over broad casts."`).
- **`fix_applicability`**: Assessment of fix autonomy (`"machine_applicable"`, `"has_alternatives"`, `"manual_review"`).
- **`fix_confidence`**: Confidence rating (`"high"`, `"medium"`, `"low"`).
- **`safe_edit_available`**: Boolean indicating whether an automated AST refactor is provably semantic-preserving.
- **`suggested_edits`**: List of concrete replacement strings or patch instructions.

---

## 7. Dual-Compiler Parity

Bunker maintains 100% semantic parity across both active compilers:

| Subsystem / Metric | `bunker-cli` (Rust Production Compiler) | `bkrc.bkr` (Pure Bunker Self-Host Compiler) |
|---|---|---|
| **Diagnostic Envelope** | `TypecheckReport` (`bunker.typecheck.v1`) | `self_host_typecheck_json` (`bunker.self_host.typecheck.v1`) |
| **Capability Flags** | All 45 boolean capability flags active | All 45 boolean capability flags active |
| **Origin Tracking** | Exact byte offsets via `line_col_to_byte_offset` | Source byte start/end via `AstSpan` and token spans |
| **Expected / Found** | Populated in `Diagnostic` and `TypecheckReportDiagnostic` | Populated via `resolver_state_json` and semantic accessors |
| **Top-Level Comment** | `/* BUNKER_TYPECHECK_JSON: ... */` via CLI flag | `/* BUNKER_TYPECHECK_JSON: ... */` prepended to generated C |
| **Verification Gate** | `tests/240_type_diagnostics_parity.bkr` | `self-host-check` (8/8 modules, 0 diagnostics) |

---

## 8. Officially Closing Track T (Type System) at 100.0%

With the completion of `T-024` (Type Diagnostics Parity and Canonical Reporting), **Track `T` (Type System) is officially CLOSED at 100.0% completion (24 / 24 DONE)**.

Track `T` represents the 6th fully completed track in the Bunker language ecosystem, joining:
1. Track `C` (Control Flow & Errors): 100.0% (7 / 7 DONE)
2. Track `SH` (Self-Hosting): 100.0% (10 / 10 DONE)
3. Track `D` (Data Model & Standard Types): 100.0% (13 / 13 DONE)
4. Track `L` (Language Core): 100.0% (12 / 12 DONE)
5. Track `M` (Memory and Resource Model): 100.0% (10 / 10 DONE)
6. **Track `T` (Type System): 100.0% (24 / 24 DONE)**

### Track T Comprehensive Audit:

| Item | Status | Priority | Description | Verification Milestone |
|---|---|---:|---|---|
| `T-001` | DONE | P0 | Real generics in AST and typechecker (`Type::Generic`) | `Q-271`, `tests/216_generics_basic.bkr` |
| `T-002` | DONE | P0 | Generic functions and comptime functions | `Q-271`, `tests/216_generics_basic.bkr` |
| `T-003` | DONE | P0 | Generic structs and tuple structs | `Q-271`, `tests/216_generics_basic.bkr` |
| `T-004` | DONE | P1 | Generic structural constraints & bounded polymorphism | `Q-285`, `BKR-SPEC-GEN-002`, `tests/239_generic_structural_constraints.bkr` |
| `T-005` | DONE | P1 | Kernel-level type aliases (`type Name = Target;`) | `Q-245`, `tests/137_type_aliases.bkr` |
| `T-006` | DONE | P0 | Local type inference for let bindings | `Q-250`, `tests/148_local_type_inference.bkr` |
| `T-007` | DONE | P0 | Call-result type inference for builtins and user functions | `Q-251`, `tests/150_call_result_inference.bkr` |
| `T-008` | DONE | P0 | Contextual inference for None, empty arrays, collections, Ok/Err | `Q-252`, `tests/155_inference_constructors.bkr` |
| `T-009` | DONE | P0 | User-defined enums and pointer-safe boxed ADTs | `Q-253`, `tests/160_user_defined_enums_adt.bkr` |
| `T-010` | DONE | P0 | Comprehensive exhaustive match checking | `Q-248`, `tests/140_exhaustive_matches.bkr` |
| `T-011` | DONE | P0 | Pattern type checking and unreachable/duplicate rejection | `Q-249`, `tests/144_pattern_type_checking.bkr` |
| `T-012` | DONE | P1 | Destructuring patterns for structs, tuples, and enums | `Q-233`, `tests/131_struct_destructuring.bkr` |
| `T-013` | DONE | P1 | Arbitrary nested patterns and variable bindings | `Q-247`, `tests/139_nested_patterns.bkr` |
| `T-014` | DONE | P1 | Match guards (`pattern if condition => body`) | `Q-228`, `tests/128_match_guard.bkr` |
| `T-015` | DONE | P1 | Tuple types (`(T1, T2)`), indexing, and destructuring | `Q-233`, `tests/130_tuple_types.bkr` |
| `T-016` | DONE | P1 | Unit type (`()`) in let bindings, returns, and ADTs | `Q-229`, `tests/129_unit_type.bkr` |
| `T-017` | DONE | P1 | Never/bottom type (`!`, `never`) and bottom-type unification | `Q-246`, `tests/138_never_type.bkr` |
| `T-018` | DONE | P2 | Function types (`fn(T1, T2) -> Ret`) and higher-order calls | `Q-262`, `tests/185_higher_order_functions.bkr` |
| `T-019` | DONE | P0 | Trait/interface architecture without OOP inheritance (UFCS) | `Q-283`, `BKR-SPEC-DISPATCH-001`, `tests/235_method_dispatch_rules.bkr` |
| `T-020` | DONE | P1 | Method resolution and member lookup rules | `Q-258`, `tests/173_struct_methods.bkr` |
| `T-021` | DONE | P2 | Operator overloading policy (closed primitive operators) | `Q-284`, `BKR-SPEC-OP-001`, `tests/237_operator_policy_rules.bkr` |
| `T-022` | DONE | P1 | Explicit numeric promotion rules via `as` casting | `tests/36_kernel_type_cast.bkr`, `tests/161_cast_safety_rules.bkr` |
| `T-023` | DONE | P1 | Cast safety validation and structured rejection | `Q-254`, `tests/161_cast_safety_rules.bkr` |
| `T-024` | DONE | P0 | Type diagnostics parity, origin tracking, and structured repair | `Q-286`, `BKR-SPEC-DIAG-002`, `tests/240_type_diagnostics_parity.bkr` |

Total ecosystem pure completion advances to **102 / 168 pure DONE (60.7%)** across all 14 tracks.
