# Bunker Ownership, Move Semantics, and Copy Architecture

**Document ID:** `BKR-SPEC-OWNER-001`  
**Status:** Canonical Standard  
**Revision:** 1.0.0 (2026-10-25)  
**Applies to:** `bunker-cli`, pure Bunker self-host compiler, and language runtime  

---

## 1. Executive Summary

Bunker enforces deterministic, single-owner resource management without a tracing garbage collector, reference-counting overhead, or complex lifetime annotations. The memory architecture is built on three core pillars:

1. **Affine / Linear Move Semantics:** Every non-copy value has exactly one owning variable binding. When passed by value, bound to a new identifier, or packed into an aggregate, ownership transfers (moves), rendering the source variable unusable until reinitialized.
2. **Explicit Deep Copy:** To preserve source variables across assignments or call sites, the language provides an explicit `copy` prefix operator (`let b = copy a;`) which performs a deep duplicate of structs, arrays, and heap-backed handles.
3. **Compile-Time Static Verification:** The typechecker tracks moved variable sets and locations across every basic block, ensuring use-after-move defects are caught with structured, machine-actionable diagnostics (`BKR_SELF_USE_AFTER_MOVE` / `E0301`).

---

## 2. Type Classification: Copy vs. Move

In Bunker, types are partitioned into two strict categories:

### 2.1 Copy Types

Copy types are values whose bitwise representation or handle can be replicated without invalidating the source:

| Type Family | Bunker Syntax | Semantics |
|---|---|---|
| Scalar Integers | `i32`, `i64` | Register value copied by value |
| Floating Point | `f32`, `f64` | Register value copied by value |
| Booleans | `bool` | Single-byte boolean copied by value |
| Unit & Bottom | `()`, `!`, `never` | Zero-sized tokens copied by value |
| Function Types | `fn(T1, T2) -> R` | Function pointer copied by value |
| Enumerations / ADTs | `enum Color { ... }` | Packed tagged union representation copied by value |
| Homogeneous Copy Tuples | `(i32, bool, f64)` | Tuples where all constituent elements satisfy `is_copy_type` |

```bunker
let x: i32 = 42;
let y: i32 = x; // Copy: both x and y are valid and independent
let sum: i32 = x + y; // Valid: x was copied, not moved
```

### 2.2 Move Types

Move types represent composite aggregates or resources where aliasing would introduce ambiguous ownership, double-frees, or uncontrolled mutation:

| Type Family | Bunker Syntax | Semantics |
|---|---|---|
| Structs | `struct Point { x: i32, y: i32 }` | Owned record; moved on assignment |
| Tuple Structs | `struct Pair(i32, i32);` | Owned positional record; moved on assignment |
| Fixed Arrays | `[T; N]`, `[1, 2, 3]` | Fixed-size array; moved on assignment |
| Slices & Slices of T | `Slice<T>`, `[T]` | Borrowed view; linear ownership |
| Strings | `str` | Immutable string buffer handle |
| Dynamic Vectors | `Vec<T>` | Arena/heap collection; linear ownership |
| Hash Tables | `HashMap<K, V>` | Hash table collection; linear ownership |
| Byte Buffers | `bytes` | Raw byte buffer; linear ownership |

```bunker
let p1 = Point { x: 10, y: 20 };
let p2 = p1; // Move: ownership of Point transfers to p2
// p1 is now in the MOVED state and cannot be read!
```

---

## 3. Ownership Transfer Sites (Moves)

Ownership of a move-type value is transferred at the following semantic boundaries:

### 3.1 Let Binding Transfer
When a variable initializer references an existing identifier without `copy`:
```bunker
let original = Resource { id: 1 };
let target = original; // 'original' moved to 'target'
```

### 3.2 Variable Reassignment
When an existing mutable variable is assigned an existing move-type identifier:
```bunker
let mut slot = Resource { id: 1 };
let incoming = Resource { id: 2 };
slot = incoming; // 'incoming' moved into 'slot'; old 'slot' resource dropped
```

### 3.3 Function and Method Calls
Passing a move-type variable into a function or method consumes the argument:
```bunker
fn consume_resource(r: Resource) -> i32 {
    return r.id;
}

let res = Resource { id: 42 };
let code: i32 = consume_resource(res); // 'res' moved into function
// 'res' is now moved and cannot be accessed
```

### 3.4 Aggregate Construction
Packing move-type identifiers into struct fields or array elements moves them:
```bunker
let pt = Point { x: 5, y: 10 };
let rect = Rectangle { origin: pt, width: 20, height: 30 }; // 'pt' moved into 'rect'
```

### 3.5 Return Expressions
Returning a local resource moves it out of the local function scope to the caller:
```bunker
fn make_point() -> Point {
    let p = Point { x: 1, y: 2 };
    return p; // 'p' moved to caller
}
```

---

## 4. Explicit Deep Copy Operator (`copy`)

When a developer intends to retain access to a source aggregate while creating an independent duplicate, Bunker provides the first-class `copy` prefix operator:

```bunker
let p1 = Point { x: 10, y: 20 };
let p2 = copy p1; // Deep copy: p1 remains valid!

p2.x = 99; // Modifying p2 does NOT affect p1
let total: i32 = p1.x + p2.x; // Valid: 10 + 99 = 109
```

### 4.1 Copy Semantics on Arrays
For fixed arrays, `copy arr` creates a distinct buffer with duplicate elements:
```bunker
let arr1 = [1, 2, 3];
let arr2 = copy arr1;
arr2[0] = 100;
// arr1[0] remains 1
```

### 4.2 Copy Semantics on Structs with Aggregates
If a struct contains nested structs or arrays, `copy` recursively clones all fields, ensuring zero shared mutable aliasing.

---

## 5. Reinitialization of Moved Variables

A variable that has been moved is not permanently destroyed; it may be reinitialized by assigning a new, valid value:

```bunker
let mut p = Point { x: 10, y: 20 };
let consumer = p; // p moved

// At this point, accessing p is an error:
// let x = p.x; -> ERROR: Use of moved value 'p'

// Reinitializing p with a new value restores it to valid state:
p = Point { x: 30, y: 40 };
let valid_x = p.x; // Valid: p is no longer moved!
```

---

## 6. Static Verification and Diagnostics

The Bunker compiler performs static move analysis during typechecking:
1. `moved_vars: HashSet<String>` tracks variables currently in the moved state.
2. `moved_locations: HashMap<String, String>` records the exact program statement where the move occurred.
3. When an identifier is referenced in an expression:
   - If `name` is in `moved_vars`, a structured diagnostic is raised:
     ```text
     Error: Use of moved value 'p1' (moved at let p2 = p1 in main)
     ```
   - In JSON diagnostics mode (`--json` or `--typecheck-json`), the error is reported with code `E0301`, exact byte offsets, and an actionable repair suggestion recommending `copy <var>`.

---

## 7. Compliance and Verification Gates

| Invariant | Test Fixture | Verified Behavior |
|---|---|---|
| Struct Move by Default | `tests/58_move_semantics.bkr` | Non-copy aggregates transfer ownership on `let b = a` |
| Use After Move Rejection | `tests/59_use_after_move_BAD.bkr` | Compiler cleanly rejects reading moved identifiers |
| Explicit Copy Prevents Move | `tests/60_copy_prevents_move.bkr` | `copy a` leaves `a` in valid state |
| Deep Struct Copy Independence | `tests/61_copy_deep_struct.bkr` | Modifying copied struct does not mutate original |
| Deep Array Copy Independence | `tests/62_copy_deep_array.bkr` | Modifying copied array does not mutate original |
| Reassignment Move & Reinit | `tests/227_ownership_move_semantics.bkr` | Reassignment moves source and reinitializes target |
