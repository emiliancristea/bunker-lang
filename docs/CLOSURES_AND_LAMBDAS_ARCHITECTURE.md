# Bunker Closures, Lambdas, and Captures Architecture Specification

- **Document ID:** `BKR-SPEC-FUNC-001`
- **Track:** Functions and Functional Features (`F`)
- **Milestones Covered:** `F-001` (P2: Closures), `F-002` (P2: Lambdas), `F-004` (P2: Captures)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.capability.v1`, `bunker.closure.v1`

---

## 1. Executive Summary

This specification formalizes the architecture for Closures (`F-001`), Lambdas (`F-002`), and Capture Semantics (`F-004`) in the Bunker programming language across the compiler frontend, typechecker, and backends (`bunker-cli` JIT and pure Bunker self-host compiler).

Bunker already provides first-class function pointers `fn(params) -> ret` (`T-018`, `F-003`) and standard functional collection combinators (`vec_map`, `vec_filter`, `vec_fold`, `vec_find`) (`F-005`, `F-006`). This specification completes functional programming capabilities by establishing:
1. **Lambda Expression Syntax:** Lightweight anonymous function definitions using pipe delimiters (`|params| expr` and `|params| -> ret { body }`).
2. **Type Inference:** Bidirectional deduction of parameter and return types from callee context.
3. **Capture Analysis:** Deterministic detection of free variables in lexical scope.
4. **Capture Modes:** Memory-safe explicit By-Value (`move`) capture vs lexical By-Reference capture adhering to Bunker affine ownership rules (`M-001`).
5. **Closure Lowering:** Zero-allocation function pointer coercion for non-capturing lambdas, and environment struct + trampoline lowering for capturing closures.

With this specification and implementation, items `F-001`, `F-002`, and `F-004` transition to `DONE`, officially completing all active items in Track `F` (6/6 active items `DONE`, 1 `DEFER`), making Track `F` the **10th fully completed track** in the Bunker ecosystem.

---

## 2. Lambda Expression Syntax & Semantics (F-002)

### 2.1 Concrete Syntax

Lambda expressions follow standard pipe-enclosed parameter syntax:
```bunker
// Nullary lambda
let get_magic = || 42;

// Unary expression lambda with explicit parameter type
let double = |x: i32| x * 2;

// Binary lambda with block body and explicit return type
let compute = |a: i32, b: i32| -> i32 {
    let sum: i32 = a + b;
    return sum * 2;
};

// Inferred parameter types in context expecting fn(i32) -> i32
let v2 = vec_map(v, |x| x + 10);
```

### 2.2 Formal Invariants

- **Invariant LAMBDA-SYN-01 (Parameter Syntax):** Lambda parameters are enclosed within leading and trailing vertical pipes (`| ... |`). Parameters may have explicit type annotations (`|x: i32|`) or be inferred (`|x|`) when the enclosing expression provides a typing hint.
- **Invariant LAMBDA-SYN-02 (Body Forms):** A lambda body may be a single expression (`|x| x + 1`) or an expression block (`|x| { let y = x * 2; return y + 1; }`). Single-expression lambdas implicitly return the evaluated expression.
- **Invariant LAMBDA-SYN-03 (Return Type Inference):** If a return type annotation is omitted (`-> Type`), the return type is inferred from the body expression or the return statements within the block.

---

## 3. Free Variable Analysis & Captures (F-001, F-004)

### 3.1 Free Variable Set

For any lambda expression $L$, the compiler computes the set of free variables $\text{Free}(L)$:
$$\text{Free}(L) = \text{Refs}(L) \setminus (\text{Params}(L) \cup \text{Globals} \cup \text{Builtins})$$

If $\text{Free}(L) = \emptyset$, the lambda is **non-capturing**. If $\text{Free}(L) \neq \emptyset$, the lambda is a **capturing closure**.

### 3.2 Capture Modes

Bunker supports two capture modes:

1. **By-Value / Move Capture (`move |...| ...`):**
   - Syntax: `move |x| x + local_counter`
   - Semantics: Captured variables are moved (for affine types) or copied (for scalar types) into the closure's private environment record.
   - Escape: A `move` closure is `Send`-safe and may escape its enclosing lexical frame (e.g. stored in a struct or returned from a function).
   - Invariant: A captured affine resource cannot be used in the enclosing scope after a `move` capture (`E0310`).

2. **By-Reference / Lexical Borrow (`|...| ...`):**
   - Syntax: `|x| x + local_ref`
   - Semantics: The closure borrows references to enclosing stack-allocated variables.
   - Lifetime: The closure's lifetime is strictly bounded by the enclosing stack frame. It cannot be returned or stored in persistent heap structures.

---

## 4. Lowering and Codegen Strategy

### 4.1 Non-Capturing Lambdas (Zero Overhead)

When $\text{Free}(L) = \emptyset$:
- The compiler emits a top-level static C function:
  ```c
  bkr_i32 _bkr_lambda_101(bkr_i32 x) {
      return x * 2;
  }
  ```
- The lambda expression lowers directly to the function pointer:
  `&_bkr_lambda_101`
- Coerces with zero allocation to standard function pointer `fn(i32) -> i32`.

### 4.2 Capturing Closures (Environment + Trampoline)

When $\text{Free}(L) = \{ v_1: T_1, \dots, v_k: T_k \}$:
- **Environment Record:**
  ```c
  typedef struct {
      bkr_i32 v1;
      bkr_i64 v2;
  } _bkr_closure_env_102;
  ```
- **Trampoline Invocation:**
  ```c
  bkr_i32 _bkr_closure_trampoline_102(void* _env_raw, bkr_i32 param) {
      _bkr_closure_env_102* env = (_bkr_closure_env_102*)_env_raw;
      return param + env->v1;
  }
  ```
- **Fat Closure Pair:**
  Emitted as an environment handle and trampoline pointer:
  ```c
  typedef struct {
      void* env;
      bkr_i32 (*invoke)(void*, bkr_i32);
  } _bkr_closure_fat_ptr;
  ```

---

## 5. Type System & Combinator Integration

Closures and lambdas integrate seamlessly with existing functional combinators:
- `vec_map<T, R>(v: Vec<T>, f: fn(T) -> R) -> Vec<R>`
- `vec_filter<T>(v: Vec<T>, pred: fn(T) -> bool) -> Vec<T>`
- `vec_fold<T, Acc>(v: Vec<T>, init: Acc, f: fn(Acc, T) -> Acc) -> Acc`
- `vec_find<T>(v: Vec<T>, pred: fn(T) -> bool) -> Option<T>`

Non-capturing lambdas pass directly to `vec_map`, `vec_filter`, etc., with zero heap allocation.

---

## 6. Verification Matrix

| Test ID | Fixture File | Verification Criteria | Expected Exit |
|---|---|---|---|
| `T-FUNC-01` | `tests/272_lambda_expressions_syntax.bkr` | Nullary, unary, binary, and block lambdas; parameter and return type inference; non-capturing function pointer coercion | `42` |
| `T-FUNC-02` | `tests/273_closure_captures_environment.bkr` | Closure environment construction, move capture vs borrow, accumulator mutation, and combinator composition | `42` |

---

## 7. Status & Completion

With this specification approved and implemented:
- Track: Functions and Functional Features (`F`)
  * `F-001` (Closures): `DONE`
  * `F-002` (Lambdas): `DONE`
  * `F-003` (Higher-order functions): `DONE`
  * `F-004` (Captures): `DONE`
  * `F-005` (Iterators): `DONE`
  * `F-006` (Standard combinators): `DONE`
  * `F-007` (Partial application): `DEFER` (P3)
- Track `F` is **100.0% DONE** for all active items (6/6 `DONE`, 1 `DEFER`).
- Overall Ecosystem: **141 / 168** items `DONE` (83.9%).
