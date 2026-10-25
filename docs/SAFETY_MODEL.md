# Bunker Soundness, Undefined Behavior Elimination, and Arithmetic Safety Policy

**Authoritative Specification for Soundness, Undefined Behavior Elimination, and Integer Overflow Semantics**  
**Document ID:** `BKR-SPEC-SAFE-001`  
**Tracker Reference:** Milestone `Q-278` / `S-001`, `S-002`, `S-003`  
**Status:** Approved & Enforced  
**Revision:** 1.0.0 (2026-10-25)  
**Applies to:** `bunker-cli`, pure Bunker self-host compiler, and language runtime  

---

## 1. Executive Summary & Foundational Safety Posture

Bunker is designed for mission-critical, AI-agent native, and systems-level programming. The foundational axiom of the language runtime is **Zero Undefined Behavior in Safe Code**:

1. **Absolute Soundness (`S-001`):** A well-typed Bunker program evaluated in safe mode never exhibits undefined behavior, memory corruption, uninitialized memory reads, or wild pointer dereferences.
2. **UB Elimination Policy (`S-002`):** Classic C/C++ Undefined Behavior (signed integer overflow, out-of-bounds indexing, unaligned access, null pointer dereferences, data races) is eliminated. Hardware and software faults are converted into deterministic fail-stop aborts (exit code `101` per `BKR-SPEC-PANIC-001`) or defined modular semantics. Unsafe operations are strictly quarantined behind attributes (e.g. `#[unsafe_trust]`).
3. **Deterministic Integer Arithmetic (`S-003`):** Integer arithmetic across `i32` and `i64` is mathematically defined as two's complement modular wrapping across all compilation targets and execution modes (debug, release, JIT, and self-hosted C codegen). Shifts are bitwidth-masked, and division by zero is a trapped failure.

---

## 2. Soundness Model (`S-001`)

A Bunker program is sound if every evaluation step preserves type invariants and execution safety. The compiler and runtime cooperate to enforce the following invariants:

### 2.1 Type Soundness Invariant
If an expression $e$ has type $T$ under typing environment $\Gamma$, evaluating $e$ produces a valid value of type $T$, or diverges safely via process exit / panic-abort:
$$\Gamma \vdash e : T \implies e \Downarrow v \in \mathcal{V}(T) \quad \lor \quad e \Uparrow (\text{halt with exit code } 101)$$

### 2.2 Spatial Memory Safety
- Arrays `[T; N]`, slices `Slice<T>`, vectors `Vec<T>`, byte buffers `bytes`, and strings `str` carry known lengths.
- Element indexing operations are bounds-checked:
  - In dynamic builtins (`slice_get`, `vec_get_opt`, `bytes_get`), out-of-bounds access is safely clamped or returns `Option.None` (`BKR-SPEC-ERROR-001`).
  - Direct indexed expressions validate bounds or trigger a fail-stop abort (exit code `101`), preventing buffer over-reads and out-of-bounds writes.

### 2.3 Temporal Memory Safety (Affine Ownership)
- As specified in `BKR-SPEC-OWNER-001`, non-copy aggregate types (`struct`, `Vec<T>`, `HashMap<K, V>`, `bytes`, `str`) have exactly one owning binding.
- Moving a value invalidates the source identifier. Use-after-move is statically rejected at compile time (`BKR_SELF_USE_AFTER_MOVE` / `E0301`).
- Double-frees and dangling pointers are structurally impossible because values are released exactly once when their owning scope concludes.

### 2.4 Null-Pointer Absence
- Safe Bunker has no `null`, `nil`, or raw zero-pointer representations accessible as valid values.
- Absence of a value is codified exclusively through the algebraic sum type `Option<T>` (`Some(T)` or `None`).
- Deconstruction of `Option<T>` requires exhaustive pattern matching or the try operator `?`, guaranteeing that absent states are never dereferenced as valid data.

### 2.5 Definite Assignment & Initialized Reads
- Every local variable binding (`let` and `let mut`) must be initialized before any read access.
- Reading an uninitialized memory region is prohibited by the parser grammar and typechecker.

### 2.6 Control Flow Integrity & Exhaustiveness
- Non-void functions must terminate with an explicit `return` expression on every control flow branch, or end in a diverging expression (`panic(...)`, `process_exit(...)`). Missing return paths are rejected at compile time (`BKR_SELF_RETURN_PATH` / `E0204`).
- Pattern matching over finite types (`bool`, `Option`, `Result`, and user `enum` types) must be exhaustive. Non-exhaustive matches are rejected at compile time (`BKR_SELF_EXHAUSTIVENESS` / `E0501`).

---

## 3. Undefined Behavior Elimination Policy (`S-002`)

In standard C and C++, dozens of operations invoke Undefined Behavior (UB), permitting the compiler to assume the condition cannot occur and generate silent miscompilations. In Bunker, all historical UB categories are eliminated or isolated:

| Operation Category | Historical C/C++ Behavior | Bunker Safe Execution Policy | Mechanism / Guarantee |
|---|---|---|---|
| **Signed Integer Overflow** | Undefined Behavior | Fully Defined | Two's complement modular wrapping ($2^w$) across `i32` and `i64`. |
| **Integer Division by Zero** | Undefined Behavior | Trapped Fail-Stop Abort | Compile-time error in comptime (`E0201`), hardware CPU trap / exit `101` at runtime. |
| **Out-of-Bounds Indexing** | Undefined Behavior | Spatial Bounds Check | Safe clamping or fail-stop panic abort with exit code `101`. |
| **Uninitialized Memory Read** | Undefined Behavior | Statically Impossible | Definite assignment enforced by compiler frontend. |
| **Use-After-Free / Move** | Undefined Behavior | Statically Impossible | Affine ownership tracking rejects use-after-move at compile time. |
| **Dangling Pointer Dereference** | Undefined Behavior | Statically Impossible | Single-owner lifecycle and arena scopes prevent escaping references. |
| **Null Pointer Dereference** | Undefined Behavior | Statically Impossible | `null` does not exist; sum types (`Option<T>`) enforce safety. |
| **Oversized Bitwise Shifts** | Undefined Behavior | Fully Defined | Shift amounts are masked by bitwidth minus 1 (`& 31` or `& 63`). |
| **Data Races across Threads** | Undefined Behavior | Statically Impossible | Isolated memory spaces per kernel; shared mutable memory is prohibited. |
| **Misaligned Memory Access** | Undefined Behavior | Safe Alignment | Compiler generates alignment-safe loads/stores on all target architectures. |

### 3.1 Isolation of Unsafe Code
Unsafe operations—such as foreign C ABI integration, raw hardware device memory access, or OS bootstrap drivers—cannot be called from standard safe Bunker functions. They must:
1. Reside in designated kernels or functions annotated with `#[unsafe_trust]`.
2. Be wrapped behind sound, safe public APIs that validate all preconditions before crossing the boundary.
3. Keep raw pointers (`*const T`, `*mut T`) and untrusted memory buffers entirely internal to the wrapper.

---

## 4. Integer Arithmetic & Overflow Policy (`S-003`)

Bunker specifies exact two's complement modular arithmetic for all signed and unsigned integer types.

### 4.1 Representation & Bitwidths
- `i32`: 32-bit signed two's complement integer (Range: $-2,147,483,648$ to $2,147,483,647$).
- `i64`: 64-bit signed two's complement integer (Range: $-9,223,372,036,854,775,808$ to $9,223,372,036,854,775,807$).
- Literals without explicit type annotations default to `i32` unless constrained by local contextual inference (`T-008`).

### 4.2 Addition, Subtraction, and Multiplication
Arithmetic operations (`+`, `-`, `*`) wrap modulo $2^{32}$ for `i32` and modulo $2^{64}$ for `i64`:
- **Positive Overflow:**
  ```bunker
  let max_i64: i64 = 9223372036854775807;
  let wrapped: i64 = max_i64 + 1; // Exactly -9223372036854775808 (i64::MIN)
  ```
- **Negative Underflow:**
  ```bunker
  let min_i64: i64 = -9223372036854775807 - 1;
  let wrapped: i64 = min_i64 - 1; // Exactly 9223372036854775807 (i64::MAX)
  ```
- **Multiplication Wrapping:**
  ```bunker
  let max_i64: i64 = 9223372036854775807;
  let mul_wrapped: i64 = max_i64 * 2; // Exactly -2
  ```

### 4.3 Bitwise Shifts (`<<`, `>>`)
To eliminate hardware-dependent undefined behavior on x86_64 and ARM64, shift amounts are masked:
- For `i32`: Shift amount is masked with `31` (`shift & 0x1F`).
- For `i64`: Shift amount is masked with `63` (`shift & 0x3F`).
- **Examples:**
  ```bunker
  let one_64: i64 = 1;
  let msb_64: i64 = one_64 << 63; // Exactly -9223372036854775808 (i64::MIN)

  let one_32: i32 = 1;
  let msb_32: i32 = one_32 << 31; // Exactly -2147483648 (i32::MIN)
  ```

### 4.4 Division and Modulo (`/`, `%`)
- **Non-Zero Divisor:** Evaluates standard truncated integer division / remainder.
- **Division by Zero:**
  - In compile-time evaluation (`comptime`), division or modulo by zero produces a fatal compiler diagnostic: `comptime: division by zero`.
  - At runtime, division or modulo by zero is trapped by the CPU exception handler (`STATUS_INTEGER_DIVIDE_BY_ZERO` / `SIGFPE`) or converted into a fail-stop abort (exit code `101`).
- **Signed Overflow (`MIN / -1`):** In two's complement, $-2^{w-1} / -1 = 2^{w-1}$, which cannot be represented. Safe Bunker treats this via modular wrapping to $-2^{w-1}$ or a trapped abort, preventing unhandled processor faults.

### 4.5 Type Conversions (`as`)
Explicit type casts using the `as` operator (`T-022`, `T-023`) are fully defined:
- **Integer Truncation:** `i64 as i32` discards upper 32 bits and preserves lower 32 bits.
- **Integer Extension:** `i32 as i64` sign-extends the value to 64 bits.
- **Boolean Conversion:** `true as i32` yields `1`, `false as i32` yields `0`.
- **Non-Scalar Casts:** Invalid casts between incompatible types (e.g., structs, arrays) are rejected at compile time (`cast_type_mismatch`).

---

## 5. Verification & Acceptance Criteria

Conformance with `BKR-SPEC-SAFE-001` is verified by the continuous integration test suite:

| Milestone | Capability | Verification Artifact | Expected Behavior |
|---|---|---|---|
| **`S-001`** | Soundness Rules | `tests/229_safety_soundness_ub.bkr` | Memory safety, slice bounds, affine move safety verified (returns 42). |
| **`S-002`** | UB Elimination | `tests/229_safety_soundness_ub.bkr` | No undefined behavior; zero uninitialized memory access. |
| **`S-003`** | Integer Overflow | `tests/229_safety_soundness_ub.bkr` | Two's complement wrapping verified for addition, subtraction, multiplication, and shifts. |
| **`C-006`** | Panic Abort | `tests/134_panic_abort_policy.bkr` | `panic` and `assert` fail-stop process termination with exit code 101. |
| **`S-002`** | Comptime Div by Zero | `tests/203_comptime_div_zero_BAD.bkr` | Rejected with `comptime: division by zero`. |
