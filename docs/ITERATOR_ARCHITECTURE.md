# Bunker Collection Iteration, For-Loop Protocols, and Bounds-Safe Traversal

**Document ID:** `BKR-SPEC-ITER-001`  
**Status:** `STABLE`  
**Language Version:** `1.0.0`  
**Track:** `F` (Functions and Functional Features), Item `F-005` (Iterators: Collections expose safe iteration without manual indexing)  
**Related Specs:** `docs/BORROW_MODEL.md` (`BKR-SPEC-BORROW-001`), `docs/RESOURCE_MODEL.md` (`BKR-SPEC-RES-001`), `docs/SAFETY_MODEL.md` (`BKR-SPEC-SAFE-001`)

---

## 1. Executive Summary & Design Invariants

In low-level and systems programming languages, manual index-based loops (`let mut i = 0; while i < len { ... i = i + 1; }`) are notoriously error-prone, introducing off-by-one errors, out-of-bounds indexing, and unnecessary index variable mutations.

Bunker standardizes **safe collection iteration without manual indexing (`F-005`)** through:
1. **First-Class For-In Loops:** Syntactic `for <ident> in <iterable> { <body> }` loops lowering directly to SSA control flow without exposing index counters or raw pointer math to user code.
2. **Bounds-Safe Element Traversal:** Automated bounding checks ensuring that iteration stops strictly at the collection's logical upper bound.
3. **Multi-Collection Polymorphism:** Uniform iteration syntax across integer ranges (`start..end`, `start..=end`), fixed-size arrays (`[T; N]`), borrowed dynamic slices (`[T]`), and heap-allocated vectors (`Vec<T>`).
4. **Structured Loop Flow Control:** Support for labeled break (`break 'label`) and labeled continue (`continue 'label`) jumping to enclosing loop boundaries with guaranteed LIFO `defer` cleanup execution.
5. **Functional Combinator Pipelines:** Zero-index functional iteration through standard combinators (`vec_map`, `vec_filter`, `vec_fold`, `vec_find`) using first-class typed function pointers.
6. **Compile-Time Non-Iterable Rejection:** Static typechecker verification preventing iteration over non-iterable scalar, struct, or tuple values with structured error diagnostics.

```
+-----------------------------------------------------------------------------------------+
|                                Bunker Collection Iteration                               |
+-----------------------------------------------------------------------------------------+
|                                                                                         |
|   Range Expressions          Fixed-Size Arrays           Borrowed Slices / Vectors      |
|   for i in 0..10             for x in arr                for s in slice                 |
|   for i in 0..=10            [T; N] contiguous           for v in vec                   |
|          |                          |                                  |                |
|          v                          v                                  v                |
|   +--------------+           +--------------+                   +--------------+        |
|   | Range Bounds |           | Base Ptr +   |                   | Base Ptr +   |        |
|   | start <= end |           | Static N Len |                   | Dynamic Len  |        |
|   +--------------+           +--------------+                   +--------------+        |
|          \                          |                                 /                 |
|           \                         |                                /                  |
|            +------------------------v-------------------------------+                   |
|            |    Cranelift SSA Loop Blocks: Header -> Body -> Inc    |                   |
|            |      - Automatic induction variable management         |                   |
|            |      - Labeled break / continue targets                |                   |
|            |      - Guaranteed LIFO defer unwinding                 |                   |
|            +--------------------------------------------------------+                   |
|                                                                                         |
+-----------------------------------------------------------------------------------------+
```

---

## 2. Iteration Protocols & Lowering Semantics

### 2.1 Range-Based Iteration (`start..end` & `start..=end`)
Integer ranges represent sequential values between lower and upper bounds without allocating heap memory or collections:
- **Exclusive Range (`start..end`):** Iterates over the interval `[start, end)`. Terminates when `index >= end`.
- **Inclusive Range (`start..=end`):** Iterates over the interval `[start, end]`. Terminates when `index > end`.

Both bounds are evaluated once before entering the loop. Lowering into Cranelift SSA introduces an induction variable `idx_var` initialized to `start`:
```text
Loop Header:
  cond = idx < end
  brif cond, BodyBB, ExitBB

Continue Block:
  next = idx + 1
  jump LoopBB
```

### 2.2 Fixed-Size Array Iteration (`[T; N]`)
Arrays allocated on the stack or in memory have their length `N` statically known at compile time:
```bkr
let arr: [i32; 4] = [10, 20, 30, 40];
for x in arr {
    // x is inferred as i32
}
```
Lowering loads each element from `arr_ptr + idx * sizeof(T)` over `0 <= idx < N`, preventing any possibility of out-of-bounds indexing.

### 2.3 Borrowed Slice Iteration (`[T]` / `Slice<T>`)
Slices represent dynamically sized views into contiguous memory buffers (arrays, vectors, or byte sequences):
```bkr
let s: [i32] = arr[1..3];
for x in s {
    // x is inferred as i32
}
```
At runtime, a slice header consists of:
- `offset 0`: `data` pointer (`i64`)
- `offset 8`: `len` element count (`i64`)
- `offset 16`: `elem_size` element byte stride (`i64`)

The loop header dynamically loads `len` and increments an index variable from `0` to `len - 1`, loading elements at `data + idx * elem_size`.

### 2.4 Dynamic Vector Iteration (`Vec<T>`)
Dynamic vectors manage heap-allocated storage with dynamic growth:
```bkr
let v: Vec<i32> = vec_new();
vec_push(v, 10);
vec_push(v, 20);

// Direct vector iteration
for x in v {
    // x is inferred as i32
}

// Explicit borrowed slice view
for x in vec_as_slice(v) {
    // zero-copy view iteration
}

// Sub-slice range view
for x in v[0..1] {
    // sub-slice iteration
}
```
Bunker's runtime vector layout (`BkrVec`) provides:
- `offset 0`: `cap` capacity (`i64`)
- `offset 8`: `len` current element count (`i64`)
- `offset 16`: `data` pointer (`i64*` buffer of 8-byte slots)

When iterating directly over `v`, the compiler loads `len` from offset 8, `data` from offset 16, and steps through the elements in 8-byte slots, narrowing values to `elem_ty` (e.g. `i32`) via Cranelift `ireduce` or native loading.

---

## 3. Labeled Loop Control & Early Termination

Bunker supports labeled loops across `for`, `while`, and `loop` constructs (`C-003`), allowing fine-grained control flow in nested loops without manual boolean flags:

```bkr
'search: for i in 0..10 {
    for j in 0..10 {
        if matrix_get(m, i, j) == target {
            found_i = i;
            found_j = j;
            break 'search;
        }
    }
}
```

### 3.1 Control Flow Guarantees
1. **Unlabeled `break` / `continue`:** Binds to the innermost enclosing loop header or exit block.
2. **Labeled `break 'label`:** Unwinds loop contexts until matching `'label` and branches directly to that loop's `exit_bb`.
3. **Labeled `continue 'label`:** Branches directly to the target loop's `continue_bb`, which advances the induction variable and re-evaluates the header condition.
4. **LIFO `defer` Execution (`C-005`, `M-005`):** Any `defer` statement declared inside the loop body executes in strict Last-In First-Out order before branching to `continue_bb` or `exit_bb`.

---

## 4. Functional Iteration Combinators (`F-006`)

For functional programming paradigms, Bunker provides zero-index functional combinators operating over `Vec<T>` with first-class function pointers:

| Combinator | Signature | Description |
|---|---|---|
| `vec_map` | `fn(Vec<T>, fn(T) -> U) -> Vec<U>` | Transforms each element into a new collection. |
| `vec_filter` | `fn(Vec<T>, fn(T) -> bool) -> Vec<T>` | Retains elements satisfying the predicate. |
| `vec_fold` | `fn(Vec<T>, U, fn(U, T) -> U) -> U` | Accumulates elements into a single aggregate value. |
| `vec_find` | `fn(Vec<T>, fn(T) -> bool) -> Option<T>` | Returns `Some(elem)` for first match, or `None`. |

```bkr
fn double_num(x: i32) -> i32 { return x * 2; }
fn is_even(x: i32) -> bool { return x % 2 == 0; }
fn sum_acc(acc: i32, x: i32) -> i32 { return acc + x; }

let v: Vec<i32> = vec_new();
vec_push(v, 1);
vec_push(v, 2);
vec_push(v, 3);

let doubled: Vec<i32> = vec_map(v, double_num);    // [2, 4, 6]
let evens: Vec<i32> = vec_filter(doubled, is_even); // [2, 4, 6]
let total: i32 = vec_fold(evens, 0, sum_acc);       // 12
```

---

## 5. Static Type Checking & Diagnostic Model

The typechecker verifies that the expression passed to `in <iter>` is validly iterable.

### 5.1 Type Deduction Rules
- If `iter` is `Expr::Range { start, .. }`, element type is inferred from `start`.
- If `iter` has type `Type::Array(elem, _)`, element type is `*elem`.
- If `iter` has type `Type::Slice(elem)`, element type is `*elem`.
- If `iter` has type `Type::Vec(elem)`, element type is `*elem`.
- Any other type triggers a fatal typecheck diagnostic:
  ```text
  TypeError: for-loop requires an array or range, got <ActualType> in <Function>
  ```

### 5.2 Negative Test Assurance
Attempting to iterate over non-collection types (e.g. `for x in 42` or `for x in struct_instance`) is statically rejected at compile time before any SSA generation or execution takes place.

---

## 6. Implementation & Verification Matrix

| Area | Implementation Source | Verification Fixture | Status |
|---|---|---|---|
| Range Loops | `bunker-cli/src/jit.rs`, `codegen.rs`, `typeck.rs` | `tests/32_kernel_for_range.bkr`, `tests/244_collection_iterators.bkr` | Verified |
| Array Iteration | `bunker-cli/src/jit.rs`, `codegen.rs`, `typeck.rs` | `tests/244_collection_iterators.bkr` | Verified |
| Slice Iteration | `bunker-cli/src/jit.rs`, `codegen.rs`, `runtime.h` | `tests/208_slices_and_typed_paths.bkr`, `tests/244_collection_iterators.bkr` | Verified |
| Vector Iteration | `bunker-cli/src/jit.rs`, `codegen.rs`, `runtime.h` | `tests/244_collection_iterators.bkr` | Verified |
| Labeled Breaks | `bunker-cli/src/jit.rs`, `codegen.rs`, `typeck.rs` | `tests/133_labeled_loops.bkr`, `tests/244_collection_iterators.bkr` | Verified |
| Functional Combinators | `bunker-cli/src/builtins.rs`, `jit.rs`, `runtime.h` | `tests/188_vec_hashmap_combinators.bkr`, `tests/244_collection_iterators.bkr` | Verified |
| Non-Iterable Rejection | `bunker-cli/src/typeck.rs` | `tests/245_for_loop_non_iterable_BAD.bkr` | Verified |
