# BKR-SPEC-OP-001: Bunker Operator Overloading Policy and Primitive Operator Semantics

- **Status**: CANONICAL / LOCKED (2026-10-26)
- **Document ID**: `BKR-SPEC-OP-001`
- **Track**: Type System (`T`), Safety & Language Integrity (`S`)
- **Items Addressed**:
  - `T-021`: Operator overloading policy (explicitly rejected by design with structured diagnostics)
  - `T-022`: Numeric promotion and scalar arithmetic rules
  - `T-023`: Cast safety rules and explicit `as` conversions
- **Conformance Test Fixtures**:
  - `tests/236_struct_operator_overload_BAD.bkr` (Rejection of struct arithmetic/operator overloading)
  - `tests/237_operator_policy_rules.bkr` (Comprehensive primitive operator rules, precedence, and named method idiomatic pattern)

---

## 1. Executive Summary & Epistemic Foundations

In systems programming and AI-assisted software generation, **operator overloading** is a frequent source of catastrophic defects, hidden performance traps, and semantic ambiguity:
1. **Hidden Computational Costs**: In languages with operator overloading (C++, Python, Rust), an innocent-looking expression like `matrix_a * matrix_b` or `vec1 + vec2` may allocate megabytes of heap memory, trigger unbounded loops, or block on locks.
2. **Hidden Control Flow & Panics**: Overloaded operators can throw exceptions, abort processes, or execute non-obvious side-effects without syntactic indicators at the call site.
3. **Cognitive Overhead for Humans and AI**: AI models trained on diverse code frequently mispredict the complexity or side-effects of overloaded operators, hallucinating $O(1)$ scalar additions where expensive graph traversals occur.
4. **Tooling & Analysis Degradation**: SMT solvers, symbolic execution engines, and formal verifiers require complex alias graphs and trait dispatch resolution just to reason about `a + b`.

### The Bunker Principle: Zero Hidden Work
Bunker adopts the hard design rule of **Go, Zig, and MoonBit**:
> **Operators are closed, non-overloadable primitives.**
> The syntax `a + b` **guarantees** a primitive CPU instruction (or a single documented string concatenation). Complex aggregate operations must use explicit named methods (`v1.add(v2)`, `Matrix::multiply(m1, m2)`).

Any attempt to overload operators or apply them to structs, tuples, enums, or arrays is **strictly rejected at compile-time with structured type diagnostics**.

---

## 2. Complete Primitive Operator Specification

Bunker provides a closed set of 20 primitive operators across 14 precedence levels, evaluated deterministically across Cranelift JIT and C backends.

### 2.1 Operator Inventory and Type Constraints

| Category | Operator | Allowed Operand Types | Result Type | Semantic Guarantee |
|---|---|---|---|---|
| **Arithmetic** | `+` | `(i32, i32)`, `(i64, i64)`, `(f64, f64)`, `(str, str)` | Wider operand type or `str` | Single CPU add instruction or arena string append |
| | `-` | `(i32, i32)`, `(i64, i64)`, `(f64, f64)` | Wider operand type | Single CPU sub instruction |
| | `*` | `(i32, i32)`, `(i64, i64)`, `(f64, f64)` | Wider operand type | Single CPU mul instruction |
| | `/` | `(i32, i32)`, `(i64, i64)`, `(f64, f64)` | Wider operand type | Single CPU div instruction (div-by-zero panics cleanly) |
| | `%` | `(i32, i32)`, `(i64, i64)` | Wider operand type | Single CPU rem instruction |
| **Bitwise** | `&` | `(i32, i32)`, `(i64, i64)` | Wider integer type | Single CPU bitwise AND |
| | `\|` | `(i32, i32)`, `(i64, i64)` | Wider integer type | Single CPU bitwise OR |
| | `^` | `(i32, i32)`, `(i64, i64)` | Wider integer type | Single CPU bitwise XOR |
| | `<<` | `(i32, i32)`, `(i64, i64)` | Left operand type | Logical left shift (masked by bitwidth) |
| | `>>` | `(i32, i32)`, `(i64, i64)` | Left operand type | Arithmetic right shift (sign-extended) |
| **Comparison** | `==` | Identical compatible types | `bool` | Value equality check |
| | `!=` | Identical compatible types | `bool` | Value inequality check |
| | `<` | `(i32, i32)`, `(i64, i64)`, `(f64, f64)` | `bool` | Numeric ordered comparison |
| | `<=` | `(i32, i32)`, `(i64, i64)`, `(f64, f64)` | `bool` | Numeric ordered comparison |
| | `>` | `(i32, i32)`, `(i64, i64)`, `(f64, f64)` | `bool` | Numeric ordered comparison |
| | `>=` | `(i32, i32)`, `(i64, i64)`, `(f64, f64)` | `bool` | Numeric ordered comparison |
| **Logical** | `&&` | `(bool, bool)` | `bool` | Short-circuiting logical AND |
| | `\|\|` | `(bool, bool)` | `bool` | Short-circuiting logical OR |
| **Unary** | `-` | `i32`, `i64`, `f64` | Operand type | Two's complement numeric negation |
| | `!` | `bool` | `bool` | Boolean logical negation |
| | `copy` | Any type | Same type | Explicit deep clone of aggregate |
| **Postfix** | `?` | `Result<T, E>`, `Option<T>` | Inner `T` | Unwraps value or early-returns error |
| | `as` | Scalar/Handle to Target | Target Type | Checked explicit type conversion |
| **Ternary** | `? :` | `(bool, T, T)` | `T` | Branching expression |

---

## 3. Strict Compile-Time Rejection Policy

Bunker compilers (`bunker-cli` and pure Bunker self-host compiler) implement hard guards that detect and immediately reject any non-primitive operator application.

### 3.1 Error Diagnostic Mapping

| Invalid Operator Application | Compiler Check | Diagnostic Code / Message |
|---|---|---|
| `struct + struct` | `typeck.rs:1740` / `typecheck.bkr:1086` | `Arithmetic on non-numeric types: Named("...") and Named("...")` |
| `struct - struct` | `typeck.rs:1762` / `typecheck.bkr:1086` | `Arithmetic on non-numeric types: Named("...") and Named("...")` |
| `struct * struct` | `typeck.rs:1762` / `typecheck.bkr:1086` | `Arithmetic on non-numeric types: Named("...") and Named("...")` |
| `struct / struct` | `typeck.rs:1762` / `typecheck.bkr:1086` | `Arithmetic on non-numeric types: Named("...") and Named("...")` |
| `struct & struct` | `typeck.rs:1821` / `typecheck.bkr:1074` | `Bitwise operators require integers: Named("...") and Named("...")` |
| `struct && struct` | `typeck.rs:1800` / `typecheck.bkr:1065` | `Logical operators require bool: Named("...") and Named("...")` |
| `-struct` | `typeck.rs:1843` / `typecheck.bkr:1086` | `Negation of non-numeric type: Named("...")` |
| `!struct` | `typeck.rs:1852` / `typecheck.bkr:1065` | `Logical not requires bool: Named("...")` |

### 3.2 Formal Rejection Test
This behavior is permanently certified by `tests/236_struct_operator_overload_BAD.bkr`:
```bunker
kernel StructOperatorOverloadBad {
    struct Vector { x: i32, y: i32 }
    fn main() -> i32 {
        let v1: Vector = Vector { x: 1, y: 2 };
        let v2: Vector = Vector { x: 3, y: 4 };
        let v3 = v1 + v2; // REJECTED: Arithmetic on non-numeric types
        return 0;
    }
}
```

---

## 4. Idiomatic Pattern: Explicit Named Methods

When mathematical or aggregate operations are required on user-defined structs, Bunker mandates explicit named methods:

```bunker
struct Vec2 {
    x: i32,
    y: i32
}

// Associated constructor
fn Vec2::new(x: i32, y: i32) -> Vec2 {
    return Vec2 { x: x, y: y };
}

// Explicit addition method
fn Vec2::add(self, other: Vec2) -> Vec2 {
    return Vec2 { x: self.x + other.x, y: self.y + other.y };
}

// Explicit dot product
fn Vec2::dot(self, other: Vec2) -> i32 {
    return self.x * other.x + self.y * other.y;
}

// Explicit scaling
fn Vec2::scale(self, factor: i32) -> Vec2 {
    return Vec2 { x: self.x * factor, y: self.y * factor };
}
```

### Call-Site Transparency
At the call site:
- `v1.add(v2)` makes it immediately obvious that a method is being dispatched.
- `Vec2::add(v1, v2)` provides clear Uniform Function Call Syntax (UFCS).
- Code reviewers and static analysis tools can audit allocation boundaries and instruction complexity without inspecting operator trait resolution tables.

---

## 5. Verification Matrix and Traceability

| Artifact | Purpose | Expected Result |
|---|---|---|
| `docs/OPERATOR_OVERLOADING_POLICY.md` | Formal specification (`BKR-SPEC-OP-001`) | Canonical & Locked |
| `tests/236_struct_operator_overload_BAD.bkr` | Negative typecheck rejection fixture | Compilation fails (`exit code != 0`) |
| `tests/237_operator_policy_rules.bkr` | Positive comprehensive operator test | JIT returns `42`, self-host compiles |
| `run_tests.ps1` | Continuous automated gate | All suites PASS (100%) |
