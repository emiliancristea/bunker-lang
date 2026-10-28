# Bunker Recoverable Error Conventions and Standard Library Policy

**Authoritative Specification for Recoverable Error Handling, Sum Types, and Stdlib Conventions**  
**Document ID:** `BKR-SPEC-ERROR-001`  
**Tracker Reference:** Milestone `Q-239` / `C-007`  
**Status:** Approved & Enforced  

---

## 1. Scope & Core Architecture

Bunker operates under a strict **Dual-Track Failure Architecture**:
1. **Unrecoverable Failures (Track 2):** Invariant breaches, failed assertions (`assert`), contract violations, and explicit `panic(msg)`. These immediately terminate the process with exit code `101`, writing an uncatchable diagnostic to `stderr` (governed by [`docs/PANIC_POLICY.md`](PANIC_POLICY.md)).
2. **Recoverable Errors (Track 1):** Expected operational, environmental, or domain-level conditions (such as missing map keys, out-of-bounds collection lookups, file I/O failures, network timeouts, and data parsing errors). These **never abort the process**. Instead, they are represented explicitly in the static type system using algebraic sum types:
   - `Option<T>`: Represents the potential absence of a value.
   - `Result<T, E>`: Represents an operation that may succeed with `T` or fail with an error `E`.

---

## 2. Standard Types: `Option<T>` and `Result<T, E>`

### 2.1. `Option<T>`
Canonical sum type for optionality:
```bunker
enum Option<T> {
    Some(T),
    None,
}
```
- **Constructor syntax:** `Some(value)` or `Option.Some(value)`, `None` or `Option.None`.
- **Query & Extraction:** Evaluated via pattern matching (`match opt { Some(x) => ..., None => ... }`) or propagated via postfix `?`.

### 2.2. `Result<T, E>`
Canonical sum type for fallible computations:
```bunker
enum Result<T, E> {
    Ok(T),
    Err(E),
}
```
- **Constructor syntax:** `Ok(value)` or `Result.Ok(value)`, `Err(err)` or `Result.Err(err)`, or builtins `result_ok(v)` and `result_err(e)`.
- **Query & Extraction:** Evaluated via pattern matching (`match res { Ok(v) => ..., Err(e) => ... }`) or propagated via postfix `?`.

---

## 3. Propagation & Cleanup Guarantees (The `?` Operator)

When the postfix try operator `expr?` is applied:
1. **On Success (`Some(v)` or `Ok(v)`):**
   - The expression evaluates directly to `v`.
2. **On Failure (`None` or `Err(e)`):**
   - Execution of the enclosing function or kernel halts immediately.
   - **LIFO Defer Execution:** All active `defer` blocks registered up to the failure point execute in reverse order of declaration (Last-In, First-Out), ensuring zero leaked resources (open file handles, allocated arena regions, locks).
   - The function early-returns `None` (if returning `Option`) or `Err(e)` (if returning `Result`).

### Example:
```bunker
fn load_config_entry(map: HashMap<i32, str>, key: i32) -> Option<str> {
    defer bkr_log("cleaning up lookup context");
    let val: str = hashmap_get_opt(map, key)?;
    return Some(val);
}
```

---

## 4. Standard Library Recoverable API Catalogue

All standard library operations that may fail to find an item or encounter an environmental fault adhere to the following standard naming and signature conventions:

### 4.1. Collections & Lookup

| Function | Signature | Error Behavior |
|---|---|---|
| `hashmap_get_opt` | `(map: HashMap<K, V>, key: K) -> Option<V>` | Returns `Some(value)` if `key` exists; `None` if absent. |
| `vec_get_opt` | `(vec: Vec<T>, index: i64) -> Option<T>` | Returns `Some(element)` if `0 <= index < len`; `None` if out of bounds. |
| `vec_pop_opt` | `(vec: Vec<T>) -> Option<T>` | Returns `Some(element)` if `len > 0`; `None` if collection is empty. |

*(Note: legacy direct accessors like `hashmap_get` and `vec_get` return a fallback default `0` for bootstrap compatibility, while `*_opt` APIs provide strict type-safe presence guarantees).*

### 4.2. File System & I/O

| Function | Signature | Error Behavior |
|---|---|---|
| `read_file_result` | `(path: str) -> Result<str, str>` | Returns `Ok(content)` on success; `Err(diagnostic)` if missing or unreadable. |
| `write_file_result` | `(path: str, content: str) -> Result<bool, str>` | Returns `Ok(true)` on success; `Err(diagnostic)` if disk full or permission denied. |

### 4.3. Parsing & Conversion

| Function | Signature | Error Behavior |
|---|---|---|
| `parse_int_result` | `(s: str) -> Result<i64, str>` | Returns `Ok(parsed_int)` on valid ASCII digits; `Err(msg)` on malformed input. |

---

## 5. Architectural Invariants

1. **No Silent Zero Masking in New Code:** APIs that query collections or resources where zero is a valid domain value must return `Option<T>` rather than returning `0` on miss.
2. **Deterministic Unwinding:** Recoverable error returns through `?` or explicit `return` must execute active `defer` blocks before exiting the activation frame.
3. **Fail-Stop Separation:** Never convert unrecoverable invariant violations into `Result::Err` (e.g. corrupted internal pointers). Such defects must trigger fail-stop `panic(msg)` or `assert`.
