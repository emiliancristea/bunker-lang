# Bunker Cross-Language Migration Guides (Rust, Python, TypeScript)

- **Specification ID**: `BKR-SPEC-MIGRATE-002`
- **Target Subsystems**: Ecosystem, Documentation, Standard Library, Tooling
- **Status**: `LOCKED`
- **Related Documents**: `BKR-SPEC-SAFE-001` (`docs/SAFETY_MODEL.md`), `BKR-SPEC-OWNER-001` (`docs/OWNERSHIP_MODEL.md`), `BKR-SPEC-ERROR-001` (`docs/ERROR_CONVENTIONS.md`), `docs/EXAMPLES.md`

---

## 1. Executive Summary

This guide provides definitive migration pathways from the three most common modern programming languages (**Rust**, **Python**, and **TypeScript**) to **Bunker**. It addresses conceptual shifts in memory models, type systems, error handling, and concurrency to allow developers and autonomous AI agents to translate existing codebases into idiomatic Bunker without friction.

---

## 2. Rust-to-Bunker Migration Guide

### 2.1 Mental Model Shift

Rust relies on a compile-time borrow checker with explicit lifetime annotations (`'a`) to guarantee memory safety without a garbage collector. Bunker simplifies this while retaining memory safety through **affine move semantics**, **explicit deep copy**, and **region-based arena allocation**:

| Concept | Rust | Bunker | Key Difference |
|---|---|---|---|
| **Lifetimes** | Explicit lifetime annotations (`&'a T`, `&'static str`) | **Zero lifetimes**. Values are either moved or copied. | Eliminates borrow checker fighting; long-lived structures reside in arenas. |
| **Pointers & References** | Shared (`&T`) and mutable (`&mut T`) borrows | Pass-by-value with affine moves or primitive value copies | No dangling references or alias-xor-mutability restrictions. |
| **Heap Memory** | `Box<T>`, `Rc<T>`, `Arc<Mutex<T>>` | Arena allocators (`arena_alloc`), handles (`Vec<T>`, `HashMap<K,V>`) | Memory is freed en-masse via arenas or managed sequentially. |
| **Sum Types** | `enum Option<T> { Some(T), None }`, `Result<T, E>` | First-class `Option<T>` (`Some(v)`, `None`) and `Result<T, E>` (`Ok(v)`, `Err(e)`) | Full parity with `?` operator and pattern matching. |
| **Concurrency** | Threads, `Send`/`Sync`, `Mutex<T>`, `Channel` | Isolated **Kernels** communicating via asynchronous typed messages | Zero shared mutable state across actor boundaries. |

### 2.2 Syntax Mapping Examples

#### Error Handling and `?` Propagation
```rust
// --- Rust ---
fn read_config(path: &str) -> Result<Config, io::Error> {
    let raw = std::fs::read_to_string(path)?;
    parse_config(&raw)
}
```

```bunker
// --- Bunker ---
fn read_config(path: str) -> Result<Config, str> {
    let raw: str = read_file_result(path)?;
    return parse_config(raw);
}
```

#### Structs and Methods
```rust
// --- Rust ---
struct Point { x: i64, y: i64 }
impl Point {
    fn distance_squared(&self) -> i64 { self.x * self.x + self.y * self.y }
}
```

```bunker
// --- Bunker ---
struct Point { x: i64, y: i64 }
fn Point::distance_squared(self: Point) -> i64 {
    return self.x * self.x + self.y * self.y;
}
```

---

## 3. Python-to-Bunker Migration Guide

### 3.1 Mental Model Shift

Python is dynamically typed, interpreted, and garbage-collected. Bunker provides **nominal static typing**, **ahead-of-time C codegen or instant Cranelift JIT compilation**, and **predictable low-latency memory**:

| Concept | Python | Bunker | Key Difference |
|---|---|---|---|
| **Typing** | Dynamic duck typing (`Any`, runtime exceptions) | Static nominal typing (`i32`, `i64`, `f64`, `str`, `bool`, `struct`) | Type errors are caught at compile-time with structured diagnostics. |
| **Collections** | Heterogeneous lists `[1, "two"]` and dicts `{"k": 1}` | Homogeneous `Vec<T>` and `HashMap<K, V>` | Zero runtime boxing overhead; cache-friendly sequential storage. |
| **Syntax** | Significant indentation / whitespace | Explicit brace delimiters `{ ... }` and semicolons `;` | Deterministic parsing and immune to copy-paste indentation bugs. |
| **Exceptions** | `try: ... except Exception as e: ...` | Dual-track: fail-stop `panic` vs recoverable `Result<T, E>` | Errors are explicit return values; no hidden control flow jumps. |

### 3.2 Syntax Mapping Examples

#### Data Transformation & Iteration
```python
# --- Python ---
def filter_squares(numbers: list[int]) -> list[int]:
    return [x * x for x in numbers if x % 2 == 0]
```

```bunker
// --- Bunker ---
fn filter_squares(numbers: Vec<i64>) -> Vec<i64> {
    let result: Vec<i64> = vec_new();
    let count: i64 = vec_len(numbers);
    let mut i: i64 = 0;
    while (i < count) {
        let x: i64 = vec_get(numbers, i);
        if (x % 2 == 0) {
            vec_push(result, x * x);
        }
        i = i + 1;
    }
    return result;
}
```

---

## 4. TypeScript-to-Bunker Migration Guide

### 4.1 Mental Model Shift

TypeScript layers structural typing over a single-threaded JavaScript event loop. Bunker introduces **nominal static types**, **distinct integer and float representations**, and **kernel-level isolation**:

| Concept | TypeScript | Bunker | Key Difference |
|---|---|---|---|
| **Type System** | Structural typing (shapes match if fields match) | Nominal typing (`struct A` != `struct B` even with identical fields) | Eliminates accidental shape compatibility; guarantees intentionality. |
| **Numbers** | Single IEEE-754 double precision `number` | Precise machine types: `i32`, `i64`, `f64` | Native 64-bit integer arithmetic without BigInt performance penalties. |
| **Null / Undefined** | `null`, `undefined`, optional chaining `?.` | No null. Explicit sum type `Option<T>` (`Some`, `None`) | Complete null absence eliminates `NullPointerException` class bugs. |
| **Async Model** | `async` / `await` over single-threaded Promise microtask queue | Actor-style asynchronous message passing between kernels | Scalable multi-core parallelism without event-loop starvation. |

### 4.2 Syntax Mapping Examples

#### Discriminated Unions vs Bunker Enums
```typescript
// --- TypeScript ---
type Shape = 
  | { kind: "circle"; radius: number }
  | { kind: "rectangle"; width: number; height: number };

function area(s: Shape): number {
  switch (s.kind) {
    case "circle": return 3.14159 * s.radius * s.radius;
    case "rectangle": return s.width * s.height;
  }
}
```

```bunker
// --- Bunker ---
enum Shape {
    Circle(f64),
    Rectangle(f64, f64)
}

fn area(s: Shape) -> f64 {
    return match s {
        Shape::Circle(r) => 3.14159 * r * r,
        Shape::Rectangle(w, h) => w * h
    };
}
```

---

## 5. Migration Cheat Sheet & Rosette Stone

```
Construct            Rust                   Python                 TypeScript             Bunker
---------------------------------------------------------------------------------------------------------
Immutable Var        let x = 5;             x = 5                  const x = 5;           let x: i64 = 5;
Mutable Var          let mut x = 5;         x = 5                  let x = 5;             let mut x: i64 = 5;
Array / Vector       Vec<T>                 list                   Array<T>               Vec<T>
Hash Map             HashMap<K, V>          dict                   Map<K, V>              HashMap<K, V>
Optional Value       Option<T>              Optional[T]            T | null | undefined   Option<T>
Result / Error       Result<T, E>           tuple / Exception      Result<T, E>           Result<T, E>
Early Error Exit     ?                      raise                  throw                  ?
String Substring     &s[start..end]         s[start:end]           s.substring(start,end) substring(s, start, end)
Lambda Expression    |x| x + 1              lambda x: x + 1        (x) => x + 1           |x: i64| -> i64 { x + 1 }
Actor Model          Actix / Tokio channel  multiprocessing.Queue  Worker postMessage     kernel / shell message
```

---

## 6. Tooling & Driver Integration

- **Capability Reflection**: `self_host_capability_json()` in `self-host/modules/driver.bkr` exposes:
  ```json
  "construct_examples": true,
  "migration_guides": true
  ```
- **CLI Commands**:
  - `bunker doc --migration`: Outputs migration reference and syntax comparisons.
  - `bunker doc --examples`: Validates that all construct examples parse and typecheck.
- **Self-Host Verification**: Zero diagnostics under `bunker self-host-check`.
