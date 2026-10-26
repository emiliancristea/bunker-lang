# BKR-SPEC-DISPATCH-001: Bunker Method Dispatch, UFCS, and Trait/Interface Architecture

- **Status**: CANONICAL / LOCKED (2026-10-26)
- **Document ID**: `BKR-SPEC-DISPATCH-001`
- **Track**: Type System (`T`), Data Model (`D`)
- **Items Addressed**:
  - `T-019`: Trait/interface system (shared behavior expressed without inheritance)
  - `T-020`: Method resolution rules and precedence
  - `D-004`: Struct method declarations, associated functions, and receiver inference
- **Conformance Test Fixtures**:
  - `tests/173_struct_methods.bkr` (Struct methods baseline)
  - `tests/174_method_call_on_non_struct_BAD.bkr` (Rejection of non-struct method calls)
  - `tests/175_method_not_found_BAD.bkr` (Rejection of undefined struct methods)
  - `tests/235_method_dispatch_rules.bkr` (Multi-type shared behavior, UFCS, constructors, self inference)

---

## 1. Executive Summary & Epistemic Foundations

In object-oriented paradigms, shared behavior has historically relied on class inheritance hierarchies (`class Dog extends Animal`), dynamic dispatch, and virtual method tables (vtables). This model introduces severe defects in critical systems:
1. **Memory Bloat**: Every object instance incurs hidden vtable pointer overhead (8 bytes per instance).
2. **Cache Pollution & Branch Mispredictions**: Virtual calls require indirect pointer dereferences (`obj->vtable[index]()`), preventing aggressive inlining and optimization.
3. **Fragile Base Class & Diamond Pathologies**: Hierarchy changes inadvertently break subclasses; multiple inheritance creates ambiguous state layout.
4. **Cognitive Complexity**: Deep inheritance chains obscure concrete behavior and data layouts.

Bunker permanently rejects class inheritance and dynamic runtime vtables. Instead, Bunker implements a **zero-cost static method dispatch system** inspired by MoonBit and Go, coupled with **Uniform Function Call Syntax (UFCS)** and **monomorphized structural polymorphism**.

---

## 2. Syntax and Declarations

Methods in Bunker are not nested within struct bodies. Struct definitions remain pure data aggregates, while methods are declared as top-level namespace-qualified functions.

### 2.1 Flat Method Declarations
A method associated with a struct `Type` is declared with a double-colon qualifier:

```bunker
struct Rect {
    w: i32,
    h: i32
}

fn Rect::area(self) -> i32 {
    return self.w * self.h;
}
```

### 2.2 Receiver Self-Type Inference
If the first parameter of a qualified function `Type::method` is named `self` and lacks an explicit type annotation, the compiler automatically infers its type as `Type::Named("Type")`:

$$\text{param.name} = \text{"self"} \land \text{param.ty} = \text{Unspecified} \implies \text{param.ty} := \text{Named}(\text{StructName})$$

Explicit type annotations are also supported:
```bunker
fn Rect::perimeter(self: Rect) -> i32 {
    return (self.w + self.h) * 2;
}
```

### 2.3 Associated Static Constructors
Functions qualified with a type namespace that do **not** take a `self` receiver operate as associated static constructors:

```bunker
fn Rect::new(w: i32, h: i32) -> Rect {
    return Rect { w: w, h: h };
}
```

These functions are invoked via namespace path syntax: `let r: Rect = Rect::new(10, 20);`.

---

## 3. Uniform Function Call Syntax (UFCS)

Bunker enforces Uniform Function Call Syntax for all methods. Any method declared as `Type::method(self, ...)` can be invoked through two interchangeable syntaxes:

| Call Form | Syntax | Lowering Target |
|---|---|---|
| **Receiver Call Syntax** | `r.area()` | `Rect::area(r)` |
| **Path Call Syntax (UFCS)** | `Rect::area(r)` | `Rect::area(r)` |

Both syntactic forms produce identical compiler intermediate representations and machine code. There is zero runtime performance difference between `r.perimeter()` and `Rect::perimeter(r)`.

---

## 4. Method Resolution Precedence Algorithm

When resolving call expressions `expr(args...)`, the compiler applies a deterministic 4-stage resolution pipeline:

```
[Call Expression: func(args...)]
               │
               ▼
   Is func an Expr::Field with
   receiver Ident matching Enum? ──YES──► [Check Enum Payload Constructor]
               │ NO                                (e.g. Option::Some(val))
               ▼
   Is func an Expr::Field with
   receiver typed as Struct S?   ──YES──► [Resolve Method S::method(recv, args...)]
               │ NO
               ▼
   Is func an Ident with "::"?   ──YES──► [Resolve Associated Function Struct::fn]
               │ NO
               ▼
   [Resolve Direct Function / Builtin in Scope]
```

### 4.1 Step 1: Enum Payload Constructor Disambiguation
If `func` is a field access `expr.field` where `expr` is an identifier matching a known enum name (e.g., `Option::Some` or `Result::Ok`), the call is resolved as an enum variant payload constructor.

### 4.2 Step 2: Receiver Method Resolution
If `func` is a field access `expr.field` where `expr` has a concrete struct type `Named(S)` or monomorphized generic struct `Generic(S, [...])`:
1. The compiler constructs the mangled method name `S::field`.
2. The compiler checks whether `S::field` is registered in the function symbol table.
3. If present:
   - Prepends `expr` as the receiver argument (`full_args = [expr] + args`).
   - Validates that `full_args.len() == param_types.len()`.
   - Checks type compatibility for all arguments including receiver `self`.
   - Lowering succeeds with the declared return type.
4. If absent:
   - Emits structured error: `No method '<field>' found on struct '<S>'`.
   - Rejection verified by `tests/175_method_not_found_BAD.bkr`.

### 4.3 Step 3: Non-Struct Receiver Guard
If `func` is a field access `expr.field` on a non-struct type (e.g., `i32`, `bool`, array, or function pointer):
- Emits structured error: `Cannot call method '<field>' on non-struct type <type>`.
- Rejection verified by `tests/174_method_call_on_non_struct_BAD.bkr`.

### 4.4 Step 4: Associated Path Calls
If `func` is an identifier containing `::` (e.g. `Rect::new`), it is resolved directly in the symbol table with standard arity and type checks.

---

## 5. Expressing Shared Behavior Without Inheritance (`T-019`)

Bunker achieves polymorphic shared behavior without class inheritance through three complementary pillars:

### 5.1 Structural Method Conformance
Different concrete struct types can implement identical method signatures without sharing a common ancestor:

```bunker
struct Rect { w: i32, h: i32 }
struct Square { side: i32 }

fn Rect::area(self) -> i32 { return self.w * self.h; }
fn Square::area(self) -> i32 { return self.side * self.side; }

fn Rect::perimeter(self: Rect) -> i32 { return (self.w + self.h) * 2; }
fn Square::perimeter(self: Square) -> i32 { return self.side * 4; }
```

Both `Rect` and `Square` satisfy the structural concept of a 2D geometric shape. They provide:
- `.area() -> i32`
- `.perimeter() -> i32`
- `.scale(factor: i32) -> Self`

### 5.2 Zero-Cost Static Dispatch
Unlike dynamic interfaces in Go (`interface{}`) or trait objects in Rust (`dyn Trait`), Bunker resolves method calls statically at compile time:
- In Cranelift JIT: Every receiver call lowers to a direct `builder.ins().call(func_ref, &[receiver, ...])`.
- In C Codegen: Every method lowers to a flat C function call `Rect_area(r)` or `Square_area(s)`.
- No virtual tables, no indirection tables, and no interface boxing.

### 5.3 Monomorphized Generic Algorithms
Shared generic algorithms operate over any type that provides the required methods:

```bunker
fn double_area<T>(shape: T) -> i32 {
    return shape.area() * 2;
}
```

During monomorphization (`monomorphize.rs`), `double_area` generates specialized concrete functions `double_area__Rect` and `double_area__Square`. Each specialized function directly calls `Rect::area` or `Square::area`, achieving maximum compiler optimization and inlining.

---

## 6. Parity Across Compilers

| Feature | `bunker-cli` (Rust + Cranelift) | Pure Bunker Self-Host Compiler | Conformance Fixture |
|---|---|---|---|
| Flat Method Decl (`fn Type::method`) | Supported (`ast_builder.rs:236`) | Supported (`parser.bkr:1334`) | `tests/173_struct_methods.bkr` |
| Receiver Call (`x.method()`) | Supported (`typeck.rs:1064`, `jit.rs:5701`) | Supported (`parser.bkr:937`, `c_codegen.bkr:1573`) | `tests/235_method_dispatch_rules.bkr` |
| Path Call UFCS (`Type::method(x)`) | Supported (`typeck.rs:1109`, `jit.rs:5690`) | Supported (`c_codegen.bkr:1832`) | `tests/235_method_dispatch_rules.bkr` |
| Implicit `self` Inference | Supported (`ast_builder.rs:240`) | Supported (`parser.bkr:1347`) | `tests/235_method_dispatch_rules.bkr` |
| Associated Constructors (`Type::new`) | Supported (`typeck.rs:1109`) | Supported (`c_codegen.bkr:1832`) | `tests/235_method_dispatch_rules.bkr` |
| Non-Struct Method Rejection | Error `Cannot call method` | Error `TYPE_CHECK_FAIL` | `tests/174_method_call_on_non_struct_BAD.bkr` |
| Missing Method Rejection | Error `No method found on struct` | Error `TYPE_CHECK_FAIL` | `tests/175_method_not_found_BAD.bkr` |

---

## 7. Verification and Traceability

Method dispatch rules are certified by the following test suite:
1. `tests/173_struct_methods.bkr`: Baseline struct method declarations, receiver calls, and associated functions.
2. `tests/174_method_call_on_non_struct_BAD.bkr`: Rejection when invoking methods on primitive scalar receivers.
3. `tests/175_method_not_found_BAD.bkr`: Rejection when invoking non-existent methods on structs.
4. `tests/235_method_dispatch_rules.bkr`: Multi-struct shared behavior (`Rect` and `Square`), dual UFCS call paths, multi-argument methods, state transformation methods, and deterministic calculation returning 42.

Both JIT execution and self-host compiler compilation produce identical validated outcomes.
