# Bunker Typechecker Frontend Architecture Specification

- **Document ID:** `BKR-SPEC-TYPECK-001`
- **Track:** Compiler Frontend (`CF`)
- **Milestones Covered:** `CF-007` (P0: Typechecker in Bunker)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.self_host.typecheck.v1`, `bunker.diagnostics.v1`

---

## 1. Executive Summary

This specification formalizes the architecture, semantic rules, and diagnostic interfaces of the self-host typechecker implemented in pure Bunker (`self-host/modules/typecheck.bkr`).

The Bunker typechecker performs complete static analysis over the typed Abstract Syntax Tree (`AstNodeRef`, `AstExprRef`, `AstStmtRef`, `AstItemRef`). It bridges AST construction with code generation by enforcing static type soundness, resolving expression kinds, checking exhaustive pattern matching, validating function and builtin call signatures, and producing canonical machine-readable diagnostics conforming to `bunker.diagnostics.v1`.

With this specification and implementation, Track `CF` item `CF-007` transitions from `PARTIAL` to `DONE`, establishing full language subset enforcement and decoupling frontend semantic analysis from raw codegen heuristics.

---

## 2. Compiler Pipeline & Subsystem Roles

```
[Typed AST (modules/ast.bkr)]
           │
           ▼
[Name Resolver (modules/resolver.bkr)]
           │
           ▼
[Type Graph Builder (modules/type_graph.bkr)]
  ├── Seed State Construction (cgen_new_ref, globals, function signatures)
  ├── Parameter & Local Environment (cgen_add_local_type_ref)
  └── Return Type Context (typecheck_return_ref_kind_with_kernel)
           │
           ▼
[Typechecker Engine (modules/typecheck.bkr)]
  ├── Expression Typing (infer_c_expr_ref_type, typecheck_expr_ref_kind)
  ├── Compatibility & Cast Matrix (typecheck_kinds_compatible, typecheck_can_cast)
  ├── Statement Diagnostics (let, return, if, while, for, loop, assign, match)
  ├── Call & Arity Validation (user functions, struct ctors, builtins)
  ├── Struct Literal Shape & Field Validation (missing & duplicate fields)
  ├── Pattern Exhaustiveness & Redundancy (bool, Option, Result, enum, scalar)
  ├── Semantic Validation (loop controls, dead code, return paths, const writes)
  └── Structured Diagnostics Construction (bunker.self_host.typecheck.v1)
```

---

## 3. Formal Invariants & Rules

### 3.1 Type Representation & Classification

- **Invariant TCK-REP-01 (Type Classification):** Every expression resolves to a discrete type kind encoded via `TypeKind` / `TYPE_*` constants:
  - Primitive scalars: `TYPE_I32` (1), `TYPE_I64` (2), `TYPE_F64` (3), `TYPE_BOOL` (4)
  - String & byte buffers: `TYPE_STR` (5), `TYPE_BYTES`
  - Collections: `TYPE_ARRAY` (6), `TYPE_VEC` (7), `TYPE_MAP` (8), `TYPE_SLICE`
  - ADTs: `TYPE_OPTION` (9), `TYPE_RESULT` (10), `TYPE_STRUCT` (11), `TYPE_ENUM`
  - Function pointers: `TYPE_FN`
  - Special kinds: `TYPE_VOID` (0), `TYPE_NEVER`, `TYPE_UNKNOWN` (-1)

### 3.2 Compatibility & Subtyping Rules

- **Invariant TCK-COMPAT-01 (Identity & Unknown Compatibility):** Two types are unconditionally compatible if either is `TYPE_UNKNOWN`, or if `expected == found`.
- **Invariant TCK-COMPAT-02 (Bottom Type Never):** If an expression yields `TYPE_NEVER` (e.g. from an infinite loop or terminating statement), it is compatible with any expected return or variable type.
- **Invariant TCK-COMPAT-03 (Integer Cross-Compatibility):** `TYPE_I32` and `TYPE_I64` are cross-compatible across scalar operations and assignments in the bootstrap compiler.
- **Invariant TCK-COMPAT-04 (Handle ABI Subsumption):** Heap collection handles (`TYPE_VEC`, `TYPE_MAP`, `TYPE_OPTION`, `TYPE_RESULT`) are pointer-represented and compatible with `TYPE_I64` in untyped bridge contexts.

### 3.3 Expression Typing Rules

1. **Literals:**
   - Integer literals (`NODE_INT_LIT`) infer `TYPE_I64`.
   - Float literals (`NODE_FLOAT_LIT`) infer `TYPE_F64`.
   - Boolean literals (`NODE_BOOL_LIT`) infer `TYPE_BOOL`.
   - String literals (`NODE_STR_LIT`) infer `TYPE_STR`.
2. **Binary Expressions:**
   - Arithmetic (`+`, `-`, `*`, `/`, `%`): operands must be numeric; yields operand type.
   - Bitwise (`&`, `|`, `^`, `<<`, `>>`): operands must be integer; yields integer.
   - Relational (`<`, `<=`, `>`, `>=`): operands must be numeric; yields `TYPE_BOOL`.
   - Equality (`==`, `!=`): operands must be compatible; yields `TYPE_BOOL`.
   - Logical (`&&`, `||`): operands must be boolean; yields `TYPE_BOOL`.
3. **Calls & Method Calls:**
   - Parameter counts must strictly match function or constructor arity (`E0204` on mismatch).
   - Each argument expression type must be compatible with the parameter type (`E0205` on mismatch).
   - Builtin functions (`len`, `vec_len`, `vec_get`, `vec_push`, `str_index_of`, etc.) are recognized and checked against their formal arity and argument types.
4. **Projections & Indexing:**
   - Indexing (`NODE_INDEX`): base must be indexable (`TYPE_ARRAY`, `TYPE_VEC`, `TYPE_STR`, `TYPE_BYTES`); index expression must be integer-compatible (`E0208`).
   - Field Access (`NODE_FIELD_ACCESS`): base must be a struct or compound type; field must exist on the target declaration (`E0209`).
5. **Struct Literals:**
   - Struct type must be declared in scope (`E0210`).
   - All declared fields must be provided; missing fields emit structured repair hints.
   - Duplicate field initializers in the same literal are detected and rejected.
   - Field values must match declared field types (`E0201`).
6. **Cast Expressions:**
   - Explicit `as` casts validate source and target compatibility via `typecheck_can_cast`.
   - Invalid casts (e.g. struct to primitive array) emit `cast_type_mismatch`.

### 3.4 Pattern Matching & Exhaustiveness

- **Scrutinee Compatibility:** Pattern arms must be type-compatible with the scrutinee expression.
- **Exhaustive Matching:**
  - Boolean matches must cover `true` and `false` or include a wildcard.
  - Option matches must cover `Some` and `None` or include a wildcard.
  - Result matches must cover `Ok` and `Err` or include a wildcard.
  - Enum matches must cover all declared variants of the target enum.
  - Scalar matches must include a catch-all / wildcard pattern.
- **Redundancy & Dead Arms:** Unreachable arms occurring after catch-alls or complete finite variant sets are rejected.

---

## 4. Machine-Readable Diagnostic Envelope & Capability

The typechecker produces structured JSON conforming to `bunker.self_host.typecheck.v1`:

```json
{
  "schema_version": "bunker.self_host.typecheck.v1",
  "representation": "typecheck_pass",
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
  "semantic_validation_passes": true,
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
  "known_limits": "Typecheck pass enforces declared annotations, return values and return paths, void value use, conditions, ternary branches, match patterns and arm values, array elements, loop-control context, unreachable statements, assignments, index bases, field-access bases, operands, calls, and struct literal shapes; full language subset semantic checking active.",
  "diagnostics": []
}
```

---

## 5. Verification Matrix

The pure Bunker typechecker is verified by comprehensive test suites:

1. `tests/226_typecheck_resolver_reports.bkr`: Verifies capability flags and typecheck report envelope.
2. `tests/240_type_diagnostics_parity.bkr`: Verifies parity of all 45 semantic check capability flags.
3. `tests/258_semantic_validation_loop_unreachable.bkr`: Verifies loop controls and dead code detection.
4. `tests/259_semantic_validation_missing_return_paths.bkr`: Verifies return path exhaustiveness and immutability.
5. `tests/260_pure_bunker_typechecker_complete.bkr`: Comprehensive verification of typechecker completeness, expression typing, compatibility rules, and complete: true status.
6. `tests/261_typechecker_expression_statement_matrix.bkr`: Exhaustive semantic coverage across all statement and expression forms.
