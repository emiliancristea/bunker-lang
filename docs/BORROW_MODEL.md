# Bunker Borrowing Model, Slice Views, and Safe Handle Architecture

**Authoritative Specification for the Borrow/Reference Alternative, Slices, and Safe Typed Handles**  
**Document ID:** `BKR-SPEC-BORROW-001`  
**Tracker Reference:** Milestone `Q-281` / `M-003`, `M-007`  
**Status:** Approved & Enforced  
**Revision:** 1.0.0 (2026-10-25)  
**Applies to:** `bunker-cli`, pure Bunker self-host compiler, and language runtime  

---

## 1. Executive Summary & Design Rationale

Modern systems languages often introduce complex borrow checkers with explicit lifetime parameters (`'a`, `'b`), variance rules, and non-lexical lifetime puzzles that create friction for autonomous AI coding agents and human engineers alike. Bunker takes a radically cleaner, mathematically sound approach to memory and resource safety:

1. **The "Simpler Alternative" to Complex Lifetimes (`M-003`):** Rather than subjecting developers to lifetime annotation puzzles, Bunker combines **single-owner affine move semantics** (`BKR-SPEC-OWNER-001`), **explicit deep copy** (`copy x`), **borrowed slice views** (`Slice<T>`), and **region-scoped bump arenas** (`BKR-SPEC-RES-001`). This combination guarantees zero data races, zero dangling references, and zero use-after-free defects without complex borrow-checker friction.
2. **First-Class Borrowed Views via Slices (`M-003`):** When read-only access to a contiguous sequence is required without copying or moving ownership, Bunker provides slices (`Slice<T>`, `[T]`). Slices act as borrowed window views over fixed arrays, dynamic vectors, or byte buffers, carrying length and element-size metadata without allocating memory.
3. **Safe Handle Rules & Phasing Out Raw Handles (`M-007`):** Bunker strictly rejects untyped integer handles in safe code. Builtins for vectors, hashmaps, results, and options refuse raw `i64` handles at compile time. All resources are encapsulated in strongly-typed wrappers (`Vec<T>`, `HashMap<K, V>`, `Result<T, E>`, `Option<T>`, `Slice<T>`, and typed compiler refs `AstStmtRef`, `LexerResultRef`, `ParserStateRef`, `CgenStateRef`), requiring explicit checked `as` casts when bridging to foreign ABIs.

---

## 2. The Borrow/Reference Alternative Model (`M-003`)

### 2.1 The Friction of Classical Borrow Checkers
Classical borrow checkers introduce severe architectural overhead:
- Complex lifetime syntax that impedes automated code generation and refactoring.
- Inability to model cyclic or graph-structured compiler data structures (ASTs, symbol tables, type graphs) without resorting to complex pointer gymnastics or runtime reference counting.
- False positive rejections where disjoint field borrows conflict with whole-struct access.

### 2.2 Bunker's Four-Pillar Alternative
Bunker achieves 100% memory safety through four cohesive primitives:

```
                  Bunker Safe Resource Architecture
                                 │
     ┌───────────────────────────┼───────────────────────────┐
     ▼                           ▼                           ▼
[Single Ownership]      [Borrowed Slice Views]      [Region Arenas]
• Affine move-by-default • Zero-allocation views     • Lexical watermarks
• Explicit `copy`        • Bounds-clamped indexing   • O(1) bulk teardown
• Zero aliased mutation  • Sub-slice truncation      • Bounded loop memory
```

1. **Single Ownership by Default:** Values are affine. Assigning or passing an aggregate transfers ownership, preventing aliasing and race conditions.
2. **Explicit Deep Copy:** When the caller must retain access across a call or binding, `copy x` produces an independent duplicate.
3. **Borrowed Slice Views:** Contiguous buffers are borrowed via `Slice<T>`, providing zero-copy view access.
4. **Arena Scoping:** Temporary structures live in region arenas whose lifetimes match the enclosing block or loop iteration, eliminating dangling pointer escape paths.

### 2.3 Slices as Borrowed Window Views
A slice `Slice<T>` (or syntax `[T]`) represents a non-owning, borrowed view into contiguous memory:
- **Creation from Arrays:** `let sl: Slice<i32> = arr[start..end];` borrows a sub-range from a fixed array without copying data.
- **Creation from Vectors:** `let sl: Slice<T> = vec_as_slice(v);` borrows the active elements of a dynamic vector.
- **Creation from Byte Buffers:** `let sl: Slice<i32> = bytes_as_slice(b);` borrows raw bytes as an integer slice.
- **Sub-slicing:** `let sub = slice_sub(sl, offset, len);` constructs a nested sub-slice whose length is automatically clamped to available bounds.
- **Bounds Safety:** Indexing a slice (`slice_get(sl, idx)`) never faults; out-of-bounds or negative indices safely evaluate to default/zero fallbacks (`BKR-SPEC-SEC-001`).

---

## 3. Safe Handle Rules & Typed Wrappers (`M-007`)

### 3.1 Rejection of Raw Integer Handles
In early bootstrap interpreters, dynamic collections were tracked via raw pointer or integer handles (`i64`). In production Bunker, passing raw integer handles to collection builtins is strictly forbidden:

```bunker
// FORBIDDEN - REJECTED AT COMPILE TIME (tests/83_raw_vec_handle_BAD.bkr)
let values: Vec<i32> = vec_new();
let raw: i64 = values as i64;
let len = vec_len(raw); // Compile error: vec_len expects Vec<T>, got i64

// FORBIDDEN - REJECTED AT COMPILE TIME (tests/84_raw_hashmap_handle_BAD.bkr)
let map: HashMap<i32, i32> = hashmap_new();
let raw: i64 = map as i64;
let ok = hashmap_contains(raw, 1); // Compile error: hashmap_contains expects HashMap<K, V>, got i64

// FORBIDDEN - REJECTED AT COMPILE TIME (tests/86_raw_result_handle_BAD.bkr)
let ok: Result<i32, i32> = result_ok(7);
let raw: i64 = ok as i64;
let val = result_unwrap(raw); // Compile error: result_unwrap expects Result<T, E>, got i64
```

### 3.2 Checked Explicit Casts
When low-level ABI boundaries (such as foreign C calls or serialization) require conversions between raw integer pointers and typed collections, explicit `as` casting is mandatory:

```bunker
// Explicit roundtrip cast (tests/85_result_handle_roundtrip.bkr)
let ok: Result<i32, str> = result_ok(42);
let raw: i64 = ok as i64;                           // Explicit export
let typed: Result<i32, str> = raw as Result<i32, str>; // Explicit re-validation
let val = result_unwrap(typed);                    // Valid: returns 42
```

### 3.3 Strongly-Typed Wrappers in Pure Self-Host Compiler
In the pure Bunker self-host compiler (`self-host/modules/`), all compiler structures wrap raw internal representations in strong, typed interfaces:
- **`AstStmtRef`:** Strongly-typed handle wrapping statement AST nodes.
- **`AstExprRef`:** Strongly-typed handle wrapping expression AST nodes.
- **`AstTypeRef`:** Strongly-typed handle wrapping type AST nodes.
- **`AstPatternRef`:** Strongly-typed handle wrapping pattern AST nodes.
- **`LexerResultRef`:** Strongly-typed record encapsulating lexer output tables.
- **`ParserStateRef`:** Strongly-typed record encapsulating parser tokens, cursor, and error state.
- **`CgenStateRef`:** Strongly-typed record encapsulating C codegen indentation and type-state.

Compiler passes (`resolver.bkr`, `typecheck.bkr`, `c_codegen.bkr`, `symbol_table.bkr`) interact exclusively through these typed refs, eliminating raw vector access.

---

## 4. Invariant Matrix

| Concern | Classical Approach | Bunker Production Approach | Guarantee |
|---|---|---|---|
| **Aliasing & Data Races** | Lifetime annotations & borrow checker | Affine move-by-default + explicit `copy` | Zero aliased mutation |
| **Non-Owning Buffer Access** | Borrowed references (`&[T]`) | Borrowed slice views (`Slice<T>`, `[T]`) | Zero allocation, bounds-clamped |
| **Object Lifetime Scoping** | Lifetimes (`'a`) / tracing GC | Region arena watermarks | Bounded memory, O(1) bulk reset |
| **Handle Type Safety** | Untyped `void*` or integer IDs | Strongly-typed wrappers (`Vec<T>`, `AstStmtRef`)| Compile-time rejection of raw handles |
| **Foreign ABI Crossing** | Raw pointer casts | Checked `as` cast operator | Explicit, auditable conversion |

---

## 5. Conformance Assays & Verification Mapping

| Invariant | Clause | Test Assay | Verified Invariant |
|---|---|---|---|
| Reject Raw Vec Handle | `M-007` §3.1 | `tests/83_raw_vec_handle_BAD.bkr` | `vec_len(raw)` rejected by typechecker |
| Reject Raw HashMap Handle| `M-007` §3.1 | `tests/84_raw_hashmap_handle_BAD.bkr` | `hashmap_contains(raw, ...)` rejected |
| Result Cast Roundtrip | `M-007` §3.2 | `tests/85_result_handle_roundtrip.bkr` | Explicit `as` cast roundtrip works |
| Reject Raw Result Handle | `M-007` §3.1 | `tests/86_raw_result_handle_BAD.bkr` | `result_unwrap(raw)` rejected |
| Cast Safety Rules | `M-007` §3.2 | `tests/161_cast_safety_rules.bkr` | Verified type casting across handles |
| Borrowed Slice Slicing | `M-003` §2.3 | `tests/208_slices_and_typed_paths.bkr` | Slices over arrays and vectors |
| Value Copy Alternative | `M-003` §2.2 | `tests/233_borrow_handle_wrappers.bkr` | `copy` preserves caller ownership |
| Slice Sub-View Safety | `M-003` §2.3 | `tests/233_borrow_handle_wrappers.bkr` | Sub-slicing with clamped lengths |
| Typed Handle Wrappers | `M-007` §3.3 | `tests/233_borrow_handle_wrappers.bkr` | Wrapped node handles preserve invariants |

---

## 6. Summary

Under `BKR-SPEC-BORROW-001`, Bunker achieves total safety without borrow checker complexity:
- **No Lifetimes:** Developers and AI agents write safe code without complex lifetime notation.
- **Slice Borrowing:** Zero-allocation borrowed views provide efficient buffer access.
- **Strong Typing:** Raw integer handles are eliminated; all collections and AST nodes use strongly-typed wrappers.
