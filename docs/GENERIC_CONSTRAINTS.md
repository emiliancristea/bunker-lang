# BKR-SPEC-GEN-002: Bunker Generic Constraints and Structural Bounded Polymorphism

- **Status**: CANONICAL / LOCKED (2026-10-26)
- **Document ID**: `BKR-SPEC-GEN-002`
- **Track**: Type System (`T`), Generics
- **Items Addressed**:
  - `T-004`: Generic constraints (generic operations require explicit structural capability bounds)
  - `T-001`: Real generics representation in AST and typechecker
  - `T-002`: Generic functions and monomorphization
  - `T-003`: Generic structs and tuple structs
  - `T-019`: Shared behavior expressed without OOP inheritance
- **Conformance Test Fixtures**:
  - `tests/216_generics_basic.bkr` (Basic generic structs, functions, and tuple structs)
  - `tests/217_generic_arg_count_BAD.bkr` (Generic argument arity mismatch)
  - `tests/218_generic_conflict_BAD.bkr` (Conflicting type parameter deduction)
  - `tests/219_generic_unknown_type_param_BAD.bkr` (Duplicate/unknown type parameter)
  - `tests/220_generic_recursion_limit_BAD.bkr` (Infinite generic instantiation recursion limit)
  - `tests/238_generic_constraint_missing_method_BAD.bkr` (Rejection of types violating structural method constraints)
  - `tests/239_generic_structural_constraints.bkr` (Multi-type generic structural constraints and validation)

---

## 1. Executive Summary & Epistemic Foundations

In modern systems programming languages, unconstrained generics (such as pre-C++20 templates) cause disastrous compiler output: instantiating a generic template with an incompatible type produces pages of incomprehensible compiler error cascades deep inside nested implementation headers.

Conversely, overly rigid nominal trait bounds (as in Rust: `where T: Clone + Send + Sync + 'static + PartialEq<U>`) introduce severe engineering bottlenecks:
1. **Compilation Slowdowns**: Global trait solvers compute complex recursive trait dependency graphs.
2. **AI Failure Vector**: Studies show that trait bound resolution errors (`E0277: the trait bound is not satisfied`) represent one of the highest error categories for LLM code generators due to non-local type relationships.
3. **Boilerplate Explosion**: Types must explicitly declare nominal compliance for every trait (`impl Trait for Type`), preventing modular interoperation between independently authored libraries.

### The Bunker Principle: Structural Bounded Polymorphism (Zero-Cost Concepts)
Bunker solves this dilemma through **Structural Bounded Polymorphism**:
1. **Capability-Driven Constraints**: A generic function or struct that performs operations on a type parameter `T` (such as calling `.area()`, `.len()`, or performing comparisons `<`) establishes a compile-time structural capability constraint on `T`.
2. **Structural Conformance**: Any concrete type that implements the required method signatures (`fn Type::method(self, ...)`) satisfies the constraint automatically. No nominal `impl Trait for Struct` declaration is required.
3. **Monomorphization Verification**: During compiler monomorphization (`monomorphize.rs`), instantiations are specialized into concrete AST nodes (`fn__Type`) and verified by the typechecker (`typeck.rs`). Incompatible types are rejected with exact, localized diagnostics at the instantiation site.
4. **Zero Runtime Overhead**: Bounded generic functions compile to specialized, unboxed machine code with zero vtable indirection, zero interface fat pointers, and full inlining potential.

---

## 2. Structural Method Constraints

When a generic function invokes a method on a generic parameter `item: T`:

```bunker
fn measure_area<T>(item: T) -> i32 {
    return item.area();
}
```

The function body establishes a **structural method constraint**:
$$\forall T, \quad T \text{ satisfies } \text{measure\_area} \iff \exists (\text{fn } T\text{::area}(self: T) \to \text{i32})$$

### 2.1 Multi-Type Structural Conformance
Multiple distinct struct types satisfy this constraint without sharing an ancestor class or nominal interface:

```bunker
struct Rect { w: i32, h: i32 }
struct Square { side: i32 }

fn Rect::area(self) -> i32 { return self.w * self.h; }
fn Square::area(self) -> i32 { return self.side * self.side; }

// Both types satisfy measure_area<T>:
let r_area = measure_area::<Rect>(r);
let s_area = measure_area(s);
```

### 2.2 Rejection of Violating Types
If a type `Tag` lacking the `.area()` method is passed to `measure_area`:

```bunker
struct Tag { id: i32 }
let a = measure_area(Tag { id: 1 });
```

The compiler immediately rejects the instantiation with a localized structured diagnostic:
```text
Error: 1 error(s) found:
  No method 'area' found on struct 'Tag' in measure_area__Tag
```
Verified by `tests/238_generic_constraint_missing_method_BAD.bkr`.

---

## 3. Operator Constraints on Generic Parameters

Generic functions that apply primitive operators to type parameters constrain those parameters to supported primitive scalar types:

```bunker
fn find_min<T>(a: T, b: T) -> T {
    if a < b {
        return a;
    }
    return b;
}
```

Because operator overloading is rejected by policy (`BKR-SPEC-OP-001`, `T-021`), the `<` comparison operator is valid only for primitive ordered types (`i32`, `i64`, `f64`).

### 3.1 Operator Constraint Rejection
If a user attempts to call `find_min` with a struct type:
```bunker
let m = find_min(Rect { w: 1, h: 2 }, Rect { w: 3, h: 4 });
```
Monomorphization produces `find_min__Rect`, which typecheck immediately rejects:
```text
Error: Comparison of incompatible types: Named("Rect") and Named("Rect") in find_min__Rect
```

---

## 4. Monomorphization Pipeline & Validation Architecture

Generic constraint enforcement is performed by the two-phase monomorphization engine:

```
[Generic Source AST]
        │
        ▼
[Monomorphization Pass (monomorphize.rs)]
  ├── Scan AST for Generic Instantiations (Call / Struct / Turbofish)
  ├── Deduce Inferred Type Parameters from Arguments
  ├── Verify Type Parameter Arity (tests/217_generic_arg_count_BAD.bkr)
  ├── Verify Consistent Inferred Types (tests/218_generic_conflict_BAD.bkr)
  ├── Check Recursion Depth Limit <= 64 (tests/220_generic_recursion_limit_BAD.bkr)
  └── Synthesize Specialized Monomorphic AST Nodes:
        fn_name<Type1, Type2> ──► fn_name__Type1__Type2
        Struct<Type1>         ──► Struct__Type1
        │
        ▼
[Typecheck Verification (typeck.rs)]
  ├── Verify Specialized Method Calls on Concrete Receivers
  ├── Verify Operator Type Validity on Specialized Operands
  └── Emit Structured Error if Structural Constraint is Violated
```

---

## 5. Formal Verification Matrix

| Test Fixture | Purpose | Expected Result |
|---|---|---|
| `tests/216_generics_basic.bkr` | Baseline generic functions, structs, and tuple structs | JIT returns `42`, CI green |
| `tests/217_generic_arg_count_BAD.bkr` | Type argument count mismatch rejection | Compilation fails with arity diagnostic |
| `tests/218_generic_conflict_BAD.bkr` | Conflicting inferred type parameters rejection | Compilation fails with conflict diagnostic |
| `tests/219_generic_unknown_type_param_BAD.bkr` | Duplicate/unknown type parameters rejection | Compilation fails with parameter diagnostic |
| `tests/220_generic_recursion_limit_BAD.bkr` | Infinite generic recursion rejection | Compilation fails with recursion limit `E0803` |
| `tests/238_generic_constraint_missing_method_BAD.bkr` | Structural method constraint violation rejection | Compilation fails with `No method found on struct` |
| `tests/239_generic_structural_constraints.bkr` | Multi-struct generic structural constraints execution | JIT returns `42`, 100% pass |
