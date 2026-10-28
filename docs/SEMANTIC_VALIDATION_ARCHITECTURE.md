# Bunker Semantic Validation Architecture Specification

- **Document ID:** `BKR-SPEC-SEM-001`
- **Track:** Compiler Frontend (`CF`)
- **Milestones Covered:** `CF-010` (P0: Semantic validation passes: loop controls, unreachable code detection, terminating return paths)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.self_host.semantic.v1`, `bunker.diagnostics.v1`

---

## 1. Executive Summary

This specification establishes the authoritative rules, invariants, and diagnostic representations for the semantic validation passes in the Bunker language compiler frontend.

While syntactic parsing validates phrase structure and the typechecker enforces representation compatibility, the **Semantic Validation Pass** analyzes control-flow topologies, lexical execution invariants, and value definitions to guarantee program soundness prior to intermediate representation lowering and code generation. Specifically, it enforces:

1. **Loop-Control Context Invariants:** `break` and `continue` statements are strictly confined to enclosing loop bodies (`for`, `while`, `loop`); any occurrence outside a loop is rejected with `E0207` / `BKR_SELF_CONTROL_FLOW`.
2. **Unreachable Statement Detection:** Statements appearing sequentially after unconditional control-flow terminators (`return`, `break`, `continue`, or fully-terminating branching constructs) are statically detected and rejected with `E0214` / `BKR_SELF_UNREACHABLE_CODE`.
3. **Return Path Exhaustiveness:** Functions with non-void return types must definitively execute a `return` statement on every control-flow path; fallthrough functions are rejected with `E0206` / `BKR_SELF_RETURN_PATH`.
4. **Assignment Target & Immutability Soundness:** Assignment destinations must be valid lvalues (identifiers, field projections, index operations); attempts to overwrite `const` items are rejected with `E0502` / `BKR_SELF_CONST_ASSIGNMENT`, and non-lvalue assignments emit `E0501` / `BKR_SELF_ASSIGNMENT_TARGET`.

---

## 2. Compiler Pipeline Integration

Semantic validation runs as an integral phase of the compiler frontend directly after name resolution and before backend C/Cranelift code generation:

```
[Source Text] 
      │
      ▼
 [Lexer & Parser] ──► AST (Typed AstNodeRef)
      │
      ▼
 [Name Resolver] ──► Scoped Symbol Resolution & Visibility Boundaries
      │
      ▼
 [Semantic Validation Pass]
      ├── 1. Loop-Control Scope Validation (loop_depth tracking)
      ├── 2. Control Flow Termination & Dead Code Scanning
      ├── 3. Return Path Exhaustiveness Analysis
      └── 4. Lvalue & Mutability Target Validation
      │
      ▼
 [Typechecker & Type Graph] ──► Bidirectional Type Inference & Checking
      │
      ▼
 [Backend Codegen] ──► C / Cranelift Lowering
```

---

## 3. Formal Invariants & Rules

### 3.1 Loop-Control Context Invariants

- **Invariant SEM-LOOP-01 (Lexical Loop Nesting):** `break` and `continue` statements are only syntactically and semantically valid when enclosed within an active loop construct (`for`, `while`, or `loop`).
- **Invariant SEM-LOOP-02 (Loop Depth Tracking):** The semantic scanner maintains a lexical loop depth counter $D_{loop} \ge 0$, initialized to $0$ at function boundary.
  - Traversing into `NODE_FOR`, `NODE_WHILE`, or `NODE_LOOP` increments $D_{loop} \leftarrow D_{loop} + 1$.
  - Traversing into child blocks of nested expressions (such as `NODE_IF` or block expressions) preserves the enclosing $D_{loop}$.
  - Exiting a loop decrements $D_{loop} \leftarrow D_{loop} - 1$.
- **Invariant SEM-LOOP-03 (Orphan Loop Control Rejection):** If a `NODE_BREAK` or `NODE_CONTINUE` is encountered when $D_{loop} = 0$, the compiler records an `invalid_loop_control` diagnostic emitting:
  - Numeric code: `E0207`
  - Rule ID: `BKR_SELF_CONTROL_FLOW`
  - Expected: `"inside for, while, or loop"`
  - Actual: `"outside loop"`
  - Repair Hint: `"Move this statement inside a for, while, or loop body."`
- **Invariant SEM-LOOP-04 (Labeled Loop Control):** When a label is attached to `break 'label` or `continue 'label`, the target label must exist on an active ancestor loop on the loop stack. Mismatched or non-existent labels emit an undefined label diagnostic.

---

### 3.2 Unreachable Statement Detection Invariants

- **Invariant SEM-DEAD-01 (Control Flow Termination):** A statement $S$ is defined as *terminating* ($Term(S) = \text{true}$) if control cannot sequentially pass to the immediately following statement in the same block:
  - $Term(\text{return } e) = \text{true}$
  - $Term(\text{break}) = \text{true}$
  - $Term(\text{continue}) = \text{true}$
  - $Term(\text{if } c \text{ } B_{then} \text{ else } B_{else}) = Term(B_{then}) \land Term(B_{else})$
  - A block $B = [S_1, S_2, \dots, S_n]$ terminates ($Term(B) = \text{true}$) if $\exists i \in \{1 \dots n\} \text{ s.t. } Term(S_i) = \text{true}$.
- **Invariant SEM-DEAD-02 (Sequential Dead Code Rejection):** For any block $B = [S_1, S_2, \dots, S_n]$, if statement $S_k$ terminates control flow ($Term(S_k) = \text{true}$ where $k < n$), every subsequent statement $S_m$ ($m > k$) is unreachable.
- **Invariant SEM-DEAD-03 (Dead Code Diagnostic):** Every unreachable statement in block $B$ emits an `unreachable_statement` diagnostic:
  - Numeric code: `E0214`
  - Rule ID: `BKR_SELF_UNREACHABLE_CODE`
  - Category: `"control_flow"`
  - Phase: `"typecheck"`
  - Expected: `"reachable statement"`
  - Actual: `ast_node_kind_name(kind)`
  - Repair Hint: `"Remove this statement or move it before the terminating control-flow statement."`

---

### 3.3 Return Path Exhaustiveness Invariants

- **Invariant SEM-RET-01 (Non-Void Function Return):** Any function $F$ with declared return type $T_{ret} \notin \{\text{void}, (), \text{never}\}$ must definitively return along all possible control-flow branches.
- **Invariant SEM-RET-02 (Definite Return Analysis):**
  - A `NODE_RETURN` statement definitely returns.
  - An `if-else` construct definitely returns if and only if:
    1. An `else` branch is explicitly present.
    2. Both the `then` block and the `else` block definitely return.
  - A sequence of statements definitely returns if any constituent statement definitely returns.
- **Invariant SEM-RET-03 (Missing Return Fallthrough Rejection):** If $T_{ret} \ne \text{void}$ and the function body block does not definitely return, the compiler records a `missing_return` diagnostic:
  - Numeric code: `E0206`
  - Rule ID: `BKR_SELF_RETURN_PATH`
  - Expected: `"return value on every path"`
  - Actual: `"function can fall through"`
  - Repair Hint: `"Add a return statement on every path or change the function return type to void."`

---

### 3.4 Assignment Target & Immutability Rules

- **Invariant SEM-MUT-01 (Lvalue Validity):** An assignment target must be one of:
  1. An identifier (`NODE_IDENT`).
  2. A field access projection (`NODE_FIELD_ACCESS`).
  3. An indexed element expression (`NODE_INDEX`).
  Any other expression (such as a call result, binary operator, or literal) emits `E0501` / `BKR_SELF_ASSIGNMENT_TARGET`.
- **Invariant SEM-MUT-02 (Constant Immutability):** Identifiers resolved to compile-time constant items (`const`) cannot be targeted by assignments. Violations emit `E0502` / `BKR_SELF_CONST_ASSIGNMENT`.
- **Invariant SEM-MUT-03 (Variable Mutability):** Local variable bindings declared with `let` are immutable by default. Modifying an immutable local requires the declaration to specify `let mut`.

---

## 4. Machine-Readable Semantic Validation Schema

The semantic validation pass generates structured JSON conforming to `bunker.self_host.semantic.v1`:

```json
{
  "schema_version": "bunker.self_host.semantic.v1",
  "representation": "semantic_validation_pass",
  "complete": true,
  "loop_control_validation": true,
  "unreachable_code_detection": true,
  "return_path_validation": true,
  "assignment_target_validation": true,
  "const_assignment_validation": true,
  "diagnostic_count": 0,
  "error_count": 0,
  "warning_count": 0,
  "diagnostics": []
}
```

---

## 5. Diagnostic Registry Parity Table

| Numeric Code | Symbolic Rule ID | Phase | Category | Description |
|---|---|---|---|---|
| `E0206` | `BKR_SELF_RETURN_PATH` | `typecheck` | `control_flow` | Return statement type mismatch or missing return on control path. |
| `E0207` | `BKR_SELF_CONTROL_FLOW` | `typecheck` | `control_flow` | Condition expression must be bool, or break/continue outside loop. |
| `E0214` | `BKR_SELF_UNREACHABLE_CODE` | `typecheck` | `control_flow` | Statement cannot execute because a previous statement terminates control. |
| `E0501` | `BKR_SELF_ASSIGNMENT_TARGET` | `typecheck` | `control_flow` | Assignment to non-assignable expression or immutable target. |
| `E0502` | `BKR_SELF_CONST_ASSIGNMENT` | `typecheck` | `control_flow` | Assignment attempts to modify a compile-time constant. |

---

## 6. Verification Matrix

The semantic validation passes are validated by automated fixtures:

1. `tests/133_labeled_loops.bkr`: Positive verification of nested while, loop, for with break and continue (returns 42).
2. `tests/258_semantic_validation_loop_unreachable.bkr`:
   - Positive execution of nested loops and control flow returning 42.
   - Negative semantic validation of `break` outside loop emitting `E0207` / `BKR_SELF_CONTROL_FLOW`.
   - Negative semantic validation of unreachable statement after `return` emitting `E0214` / `BKR_SELF_UNREACHABLE_CODE`.
3. `tests/259_semantic_validation_missing_return_paths.bkr`:
   - Positive verification of exhaustive branch returns across nested if-else structures.
   - Negative semantic validation of fallthrough non-void functions emitting `E0206` / `BKR_SELF_RETURN_PATH`.
   - Positive verification of `const` assignment rejection and invalid assignment targets.
