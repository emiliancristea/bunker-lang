# Bunker C Code Generator Backend Architecture Specification

- **Document ID:** `BKR-SPEC-CGEN-001`
- **Track:** Compiler Backend (`CB`)
- **Milestones Covered:** `CB-001` (P0: Bunker-written C codegen), `CB-002` (P0: Typed C emission)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.capability.v1`, `bunker.self_host.codegen.v1`

---

## 1. Executive Summary

This specification formalizes the architecture, state management, and typed emission rules of the pure Bunker C code generator backend (`self-host/modules/c_codegen.bkr` and `self-host/modules/cgen_state.bkr`).

The C backend translates high-level Bunker Abstract Syntax Tree structures (`AstKernelRef`, `AstItemRef`, `AstStmtRef`, `AstExprRef`, `AstTypeRef`) into clean, deterministic, and highly portable C code linked against `runtime.h`. 

With this specification, Track `CB` items `CB-001` (Bunker-written C codegen) and `CB-002` (Typed C emission) transition to `DONE`, establishing an entirely self-hosted, type-driven C generation pipeline decoupled from raw heuristics.

---

## 2. Compiler Pipeline & Subsystem Roles

```
[Typed AST (modules/ast.bkr)]
           │
           ▼
[Name Resolver (modules/resolver.bkr)]
           │
           ▼
[Typechecker Engine (modules/typecheck.bkr)]
           │
           ▼
[Codegen State Allocator (modules/cgen_state.bkr)]
  ├── Symbol & Identifier Table Interning (cgen_intern_name_ref)
  ├── Output Buffer & Indentation Stack (cgen_emit_ref, cgen_indent_ref)
  ├── Local & Global Typing Environment (cgen_add_local_type_ref, cgen_lookup_name_type_ref)
  ├── Struct & Field Layout Metadata (cgen_lookup_struct_field_type_info_ref)
  └── Defers & Temporary Variable Manager (cgen_push_defer_ref, cgen_temp_counter)
           │
           ▼
[C Code Generator Engine (modules/c_codegen.bkr)]
  ├── Type Translation (type_node_to_c_ref, type_to_c)
  ├── Struct, Tuple Struct & Enum Definitions (gen_c_kernel_structs_ref)
  ├── Function Type & Prototype Forward Declarations (gen_c_kernel_prototypes_ref)
  ├── Function & Method Implementations (gen_c_fn_ref)
  ├── Statement Lowering (let, assign, if, while, for, loop, defer, return)
  ├── Expression Lowering & Type Inference (infer_c_expr_ref_type, gen_c_expr_ref)
  └── Main Process Entrypoint & Runtime ABI Envelope
```

---

## 3. Formal Invariants & Rules

### 3.1 Modular State Invariants (CB-001)

- **Invariant CGEN-STATE-01 (Opaque State Reference):** Codegen state is encapsulated behind the typed handle wrapper `CgenStateRef`. Direct array unpacking is forbidden in compiler passes; all operations must traverse accessor functions in `cgen_state.bkr`.
- **Invariant CGEN-STATE-02 (Lexical Variable Scoping):** Function parameters and local `let` bindings are tracked in scoped tables (`local_names`, `local_types`, `local_struct_names`). Nested functions reset local scope cleanly without polluting kernel-level symbol environments.
- **Invariant CGEN-STATE-03 (Deterministic Identifier Mangling):** Bunker identifiers are converted to deterministic C symbols via `name_to_c_ref`:
  - Builtin runtime routines map directly to their C equivalents (`len` -> `bkr_len`, `println` -> `bkr_println`, etc.).
  - User identifiers map deterministically to index-based identifiers (`_v<idx>`), guaranteeing immunity from C reserved keyword collisions (`int`, `switch`, `goto`, `volatile`).

### 3.2 Typed C Emission Invariants (CB-002)

- **Invariant CGEN-TYPE-01 (Type-Driven Declaration):** Variable, parameter, and return type emission is strictly driven by `AstTypeRef` and `TypeKind`, never by untyped `void*` or ambiguous heuristics.
  - `TYPE_I32` emits `bkr_i32` (`int32_t`).
  - `TYPE_I64` emits `bkr_i64` (`int64_t`).
  - `TYPE_F64` emits `bkr_f64` (`double`).
  - `TYPE_BOOL` emits `bkr_bool` (`uint8_t`).
  - `TYPE_STR` emits `bkr_str` (`const char*`).
  - `TYPE_VOID` / `TYPE_NEVER` emits `void`.
  - User structs emit their mangled struct name identifier.
  - Complex handles (`Vec<T>`, `HashMap<K, V>`, `Option<T>`, `Result<T, E>`) emit `bkr_i64` handle pointers.
- **Invariant CGEN-TYPE-02 (Expression Type Soundness):** The backend maintains an expression type inference oracle (`infer_c_expr_ref_type`) mirroring frontend semantics:
  - Binary arithmetic resolves to operand type.
  - Relational and logical operators resolve to `TYPE_BOOL`.
  - String concatenation (`+`) automatically lowers to `str_concat` helper invocations.
  - Struct field accesses resolve directly from the struct's declared member types in `cgen_lookup_struct_field_type_info_ref`.
  - Explicit casts (`expr as Type`) emit typed C conversions `(TargetType)(expr)`.

### 3.3 Statement & Block Lowering

- **Invariant CGEN-STMT-01 (Expression Blocks):** In statement positions, block expressions emit standard C statement sequences. In expression positions, blocks lower cleanly into GNU statement expressions `({ ...; _blk_res; })` or hoisted temporary assignments.
- **Invariant CGEN-STMT-02 (Deterministic Defer Execution):** `defer` blocks registered in a function are tracked in `cgen_defers_ref`. When a function terminates via `return` or falls through to its exit block, deferred statements are emitted in strict Last-In, First-Out (LIFO) order.
- **Invariant CGEN-STMT-03 (Exhaustive Match Lowering):** Pattern matches lower to structured `switch-case` dispatch for integers, enums, and boolean conditions, with default fallbacks enforcing runtime trap integrity.

### 3.4 Runtime ABI & Process Entrypoint (CB-005)

Every generated C translation unit complies with the canonical Runtime ABI contract:
```c
/* Generated by Bunker Compiler */
#define BKR_REQUIRED_RUNTIME_ABI_MAJOR 1
#include "runtime.h"

// Forward declarations and typedefs
...

// Functions
...

// Entrypoint wrapper
int main(int argc, char** argv) {
    bkr_init_args(argc, argv);
    return (int)_vEntry();
}
```

---

## 4. Verification & Conformance Matrix

| Specification Item | Module Location | Verification Test Fixture | Expected Result |
|---|---|---|---|
| Modular State & Buffering | `self-host/modules/cgen_state.bkr` | `tests/262_pure_bunker_c_codegen_modular.bkr` | Returns 42 |
| Typed C Emission & Struct Layout | `self-host/modules/c_codegen.bkr` | `tests/263_typed_c_emission_matrix.bkr` | Returns 42 |
| Self-Host Full Compilation | `self-host/bkrc.bkr` | `run_tests.ps1` (`$selfHostSubset`) | 100% Pass Rate |
| ABI Version Compatibility | `self-host/modules/c_codegen.bkr` | `tests/243_c_runtime_abi_versioning.bkr` | Returns 42 |
