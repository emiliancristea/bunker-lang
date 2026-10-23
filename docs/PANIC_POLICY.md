# Bunker Panic and Abort Runtime Failure Policy

**Authoritative Specification for Unrecoverable Failures and Safety Policies in Bunker**  
**Document ID:** `BKR-SPEC-PANIC-001`  
**Tracker Reference:** Milestone `Q-238` / `C-006`  
**Status:** Approved & Enforced

---

## 1. Executive Summary & Design Invariants

Bunker enforces a strict **Dual-Track Failure Architecture** inspired by verified mission-critical systems and modern systems languages (Rust, Zig, Go):

1. **Recoverable Errors (Track 1):**
   - Must use algebraic sum types: `Result<T, E>` and `Option<T>`.
   - Propagated through expressions using the postfix `?` (try) operator.
   - Preserves deterministic LIFO execution of active `defer` blocks on early return.
   - Non-fatal; execution flow unwinds to the caller without process interruption.

2. **Unrecoverable Failures & Invariant Violations (Track 2):**
   - Triggered by explicit `panic(msg: str)`, assertion failures `assert(cond: bool, msg: str)`, bounds check violations, or unrecoverable resource exhaustion.
   - Executed through an **immediate fail-stop abort policy**.
   - **Non-catchable:** Bunker kernel execution explicitly prohibits catching, masking, or recovering from panics within the execution boundary, preventing corrupted memory states from propagating.
   - **Diagnostic Guarantee:** Panic messages are formatted and flushed immediately to standard error (`stderr`) before process termination.
   - **Deterministic Exit Code:** Process terminates with exit code `101` across JIT, ahead-of-time binary targets, and self-hosted C backends.

---

## 2. Failure Classification Matrix

| Failure Category | Mechanism | Return / Value Flow | Process Exit Code | Diagnostics Emitted |
|---|---|---|:---:|---|
| **I/O / Network Fault** | `Result<T, E>` | Propagated via `?` | N/A (normal 0) | Caller-managed error value |
| **Missing Lookup / Key** | `Option<T>` | Propagated via `?` | N/A (normal 0) | None / caller-managed |
| **Parsing / User Input** | `Result<T, ParseError>` | Propagated via `?` | N/A (normal 0) | Machine-readable error report |
| **Contract Breach / Panic** | `panic(msg: str)` | Fail-stop / no return | `101` | `bunker runtime panic: <msg>` to stderr |
| **Assertion Failure** | `assert(cond, [msg])` | Fail-stop / no return | `101` | `bunker runtime assertion failed: <msg>` to stderr |
| **Out of Memory (OOM)** | `bkr_alloc` failure | Fail-stop / abort | `101` | `bunker runtime panic: out of memory` to stderr |

---

## 3. Builtin Functions Specification

### 3.1. `panic(msg: str) -> ()`

```bunker
fn panic(message: str) -> ()
```

- **Semantics:** Immediately halts execution of the running kernel.
- **Side Effects:** Formats and writes `bunker runtime panic: <message>\n` to `stderr`, flushes all open stdio streams, and terminates the process with exit code `101`.
- **Typing:** Returns unit `()` or functions as a diverging expression in expression context.

#### Example:
```bunker
if state == INVALID_STATE {
    panic("internal invariant violated: state cannot be negative");
}
```

---

### 3.2. `assert(cond: bool, msg: str = "assertion failed") -> ()`

```bunker
fn assert(condition: bool) -> ()
fn assert(condition: bool, message: str) -> ()
```

- **Semantics:** Evaluates `condition`. If `condition == true`, execution proceeds normally with no overhead. If `condition == false`, triggers an assertion failure.
- **Side Effects on Failure:** Formats and writes `bunker runtime assertion failed: <message>\n` to `stderr` and terminates the process with exit code `101`.
- **Overloads:** Accepts either 1 argument (`condition: bool`) with default message `"assertion failed"`, or 2 arguments (`condition: bool, message: str`).

#### Example:
```bunker
let count = vec_len(v);
assert(count > 0, "collection must not be empty before pop");
```

---

## 4. Compiler Lowering & Runtime ABI

### 4.1. Cranelift JIT SSA Lowering (`bunker-cli`)
- `panic` lowers to an extern C call: `bunker_panic(msg_ptr: i64)`.
- `assert` lowers to condition check: if zero, invokes `bunker_assert(0, msg_ptr: i64)`.
- Symbol registration:
  ```rust
  builder.symbol("bunker_panic", bunker_panic as *const u8);
  builder.symbol("bunker_assert", bunker_assert as *const u8);
  ```

### 4.2. Portable C Codegen (`self-host/runtime.h`)
- Defined as inline C11 runtime primitives:
  ```c
  static inline void bkr_panic(bkr_str s) {
      fprintf(stderr, "bunker runtime panic: %s\n", s ? s : "<no message>");
      fflush(stderr);
      exit(101);
  }

  static inline void bkr_assert(bkr_bool cond, bkr_str msg) {
      if (!cond) {
          fprintf(stderr, "bunker runtime assertion failed: %s\n", msg ? msg : "assertion failed");
          fflush(stderr);
          exit(101);
      }
  }
  ```

---

## 5. Verification & Testing Standards

1. **Successful Execution Smoke:** Programs without panics and with passing assertions run to completion without runtime overhead.
2. **Deterministic Termination Smoke:** Intentionally failing panics and assertions terminate with exit code `101`.
3. **Diagnostic Verification:** `stderr` output matches canonical prefixes `bunker runtime panic:` and `bunker runtime assertion failed:`.
4. **Acceptance Test:** Validated by `tests/134_panic_abort_policy.bkr`.
