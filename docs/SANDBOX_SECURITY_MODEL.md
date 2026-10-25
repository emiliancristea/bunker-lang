# Bunker Sandbox Security Model, Bounds Checking, Runtime Failure Policy, and Null Absence

**Authoritative Specification for API Security, Agent Sandboxing, Bounds Checking, Failure Guarantees, and Null Absence**  
**Document ID:** `BKR-SPEC-SEC-001`  
**Tracker Reference:** Milestone `Q-279` / `S-004`, `S-005`, `S-006`, `S-007`, `M-008`  
**Status:** Approved & Enforced  
**Revision:** 1.0.0 (2026-10-25)  
**Applies to:** `bunker-cli`, pure Bunker self-host compiler, and language runtime  

---

## 1. Executive Summary & Security Posture

Bunker is engineered from first principles as an AI-native systems language. Code executed in Bunker often originates from autonomous agents, untrusted network payloads, or sandboxed execution environments. Consequently, the language runtime rejects traditional ambient-authority execution models in favor of a **strict capability-gated, fail-safe sandboxed posture**:

1. **API Security Model (`S-006`):** Dangerous host operations—such as process creation, arbitrary system commands, socket manipulation, and unvetted filesystem operations—are governed by capability gates. Runtime builtins query environment sandboxing state (`process_is_sandboxed()`) and refuse unauthorized invocation with structured error returns.
2. **Agent-Generated Code Sandboxing (`S-007`):** Autonomous agent code runs within an isolated execution boundary. Untrusted code cannot break out of memory arenas, execute unsanctioned system binaries, or access host secrets. Sandboxed mode is enforced by default in local workstations and multi-tenant environments.
3. **Bounds Checking Consistency (`S-004`):** Memory access across arrays `[T; N]`, slices `Slice<T>`, vectors `Vec<T>`, hashmaps `HashMap<K, V>`, and byte buffers `bytes` is uniformly safe. Access is governed by explicit option lookups (`vec_get_opt`, `hashmap_get_opt`) or safe clamped fallbacks (`vec_get`, `slice_get`, `slice_sub`), guaranteeing that no spatial indexing operation corrupts memory or reads past allocated bounds.
4. **Runtime Failure Policy (`S-005`):** Runtime failures follow a strict, non-negotiable two-tier taxonomy:
   - **Unrecoverable Invariant Violations (Panics):** Immediately terminate the process via a fail-stop abort (exit code `101`, non-unwinding) per `BKR-SPEC-PANIC-001`.
   - **Expected Operational Failures:** Modeled exclusively through algebraic sum types `Result<T, E>` and `Option<T>` per `BKR-SPEC-ERROR-001`.
5. **Null-Pointer Absence (`M-008`):** The language completely eliminates `null`, `nil`, or raw nullable references. Non-existence of values must be represented algebraically via `Option<T>`, enforcing exhaustive checkability at compile time.

---

## 2. API Security Model (`S-006`)

### 2.1 Principle of Least Privilege & Ambient Authority Elimination
Traditional systems run with ambient authority, granting any executed function full access to the user's filesystem, network, and process table. Bunker enforces capability containment:
- **Capability Gating:** Host capabilities (Process Execution, Network, Filesystem Mutation, Environment Secrets) must be granted through explicit policy.
- **Environment Policy Discovery:** The runtime provides introspectable builtins (`process_is_sandboxed()`) enabling code to inspect its privilege tier without raising unhandled faults.

### 2.2 Process Execution Sandboxing
Process execution primitives (`process_run`, `process_run_capture`, `process_spawn`) are sandboxed at the runtime boundary:
- When the sandbox policy is active (signaled via `BUNKER_DISABLE_PROCESS=1` or `BUNKER_SANDBOX=1`):
  - Any call to `process_run(...)` immediately returns `Result.Err("process execution is disabled by sandbox policy")`.
  - Process spawn attempts do not touch the OS process table or invoke shell interpreters.
- In unconstrained environments, process operations return structured `Result<str, str>` containing standard output on success or stderr diagnostics on failure.

### 2.3 Filesystem & Path Sanitization
- Filesystem APIs operate through canonicalized paths.
- Traversals exceeding the designated working directory or sandbox root are intercepted and return `Result.Err` before issuing OS syscalls.
- Sensitive environment directories (e.g. system binaries, secret keystores) are write-protected under sandboxed profiles.

---

## 3. Agent-Generated Code Sandboxing (`S-007`)

### 3.1 Autonomous Agent Threat Model
Autonomous coding agents generate and execute code dynamically. The Bunker execution sandbox neutralizes four primary agent hazard categories:
1. **Host Workstation Compromise:** Agent code attempting to spawn arbitrary shell commands (`cmd.exe`, `powershell`, `/bin/sh`) or modify user configuration.
2. **Infinite Loops & Resource Exhaustion:** Runaway recursive calls or unbounded allocation loops exhausting system memory or CPU threads.
3. **Information Disclosure:** Probing host environment variables, SSH keys, or cloud credentials.
4. **Memory Exploitation:** Exploiting memory corruption or buffer overflows to achieve arbitrary code execution.

### 3.2 Multi-Layered Defense Invariants
Sandboxed execution is enforced through compile-time and runtime cooperation:
- **Compile-Time Rejection of Unsafe Constructs:**
  - Sandboxed compilation profiles statically reject `#[unsafe_trust]` attributes.
  - Raw pointer manipulation and direct C ABI foreign imports are forbidden in agent kernels.
- **Memory Isolation via Arenas:**
  - Each agent kernel executes in an isolated memory space.
  - Kernel memory allocations are bounded by arena quotas; exceeding the quota triggers an instantaneous fail-stop termination rather than memory thrashing.
- **Execution Guard Rails:**
  - Local CLI execution requires explicit authorization (e.g., CI runners or authorized workstations). Unsanctioned local runs are blocked with:
    `"Local test execution is disabled. Run Bunker builds/tests through GitHub Actions to protect this workstation."`

---

## 4. Bounds Checking Consistency Policy (`S-004`)

Bunker guarantees that memory is never accessed out-of-bounds across any collection type:

### 4.1 Collection Bounds Matrix

| Collection Type | Access Primitive | In-Bounds Behavior | Out-of-Bounds Behavior | Failure Mode |
|---|---|---|---|---|
| **Array `[T; N]`** | `arr[i]` | Evaluates to element | Compile error if `i >= N` in comptime; runtime bounds check | Fail-stop exit `101` |
| **Slice `Slice<T>`** | `slice_get(s, i)` | Returns element | Clamped fallback (returns `0` / default) | Defined safe fallback |
| **Slice `Slice<T>`** | `slice_sub(s, o, len)` | Returns sub-slice | Length clamped to available range `[offset..total_len]` | Safe truncation |
| **Vector `Vec<T>`** | `vec_get_opt(v, i)` | Returns `Option.Some(val)` | Returns `Option.None` | Algebraic check |
| **Vector `Vec<T>`** | `vec_get(v, i)` | Returns element | Clamped fallback (returns `0` / default) | Defined safe fallback |
| **Vector `Vec<T>`** | `vec_set(v, i, x)` | Overwrites index `i` | Out-of-bounds write is safely ignored or clamped | No memory corruption |
| **HashMap<K, V>** | `hashmap_get_opt(m, k)`| Returns `Option.Some(val)` | Returns `Option.None` | Algebraic check |
| **Bytes `bytes`** | `bytes_get(b, i)` | Returns `i32` byte value | Out-of-bounds returns `-1` or `0` | Safe boundary |

### 4.2 Negative Index Protection
All dynamic indexing builtins (`vec_get`, `vec_get_opt`, `slice_get`, `slice_sub`) treat negative indices as out-of-bounds rather than performing Python-style backward wrapping or C-style underflow arithmetic. Negative indices safely return `Option.None` or clamped default values.

---

## 5. Runtime Failure Policy (`S-005`)

Bunker enforces a strict separation between unrecoverable bugs and recoverable business errors, codified in `BKR-SPEC-PANIC-001` and `BKR-SPEC-ERROR-001`:

```
                       [Runtime Event]
                              │
               Is it an invariant violation?
                              │
               ┌──────────────┴──────────────┐
              YES                            NO
               ▼                             ▼
       [Fail-Stop Abort]             [Recoverable Error]
       • Exit code 101               • Returns Result<T, E>
       • Instant non-unwinding       • Returns Option<T>
       • Zero memory corruption      • Handled via match / ?
```

### 5.1 Unrecoverable Invariant Violations (Panics)
- **Definition:** An event indicating internal logic failure, corrupted memory state, impossible branch reachability (`never` / `!`), or explicit `panic(msg)` invocation.
- **Runtime Policy:**
  - Standard error message emitted to stderr: `fatal runtime panic: <reason>`.
  - Immediate process termination with exit code `101`.
  - No stack unwinding, no destructor execution that could trigger secondary faults, and no silent recovery.

### 5.2 Recoverable Errors
- **Definition:** Expected environmental or operational failures (file not found, network timeout, process sandbox restriction, missing hashmap key).
- **Runtime Policy:**
  - Modeled exclusively through `Result<T, E>` and `Option<T>`.
  - Syntactic propagation via the try operator `?`.
  - Compile-time exhaustiveness checking prevents ignoring errors.

---

## 6. Null-Pointer and Undefined State Absence (`M-008`)

### 6.1 Total Absence of Null Values
Bunker eliminates the "billion-dollar mistake" of null references:
- There is no keyword `null`, `nil`, `None` (as a raw pointer), or `undefined` in the value grammar.
- Reference and primitive types (`i32`, `i64`, `f64`, `bool`, `str`, `struct`, `Vec<T>`) cannot be instantiated in a null state.
- Zero-initialized pointers cannot be passed or cast to safe object references.

### 6.2 Canonical Algebraic Representation
Optionality is exclusively represented by the canonical sum type:
```bunker
enum Option<T> {
    Some(T),
    None,
}
```
Accessing the underlying value requires deconstruction:
```bunker
let opt: Option<i64> = vec_get_opt(my_vec, 0);
let val = match opt {
    Some(v) => v;
    None => 0; // Explicit, intentional fallback
};
```

### 6.3 Definite Assignment Guarantee
Variables must be explicitly assigned at declaration (`let x: T = val;`) or guaranteed to be assigned before every potential use branch. Uninitialized stack reads are impossible.

---

## 7. Conformance Assays & Verification Mapping

Every invariant defined in this specification is continuously verified by deterministic automated assays:

| Invariant | Clause | Verification Assay | Verification Mechanism |
|---|---|---|---|
| API Sandboxing | `S-006` | `tests/231_sandbox_security_bounds.bkr` | Tests `process_is_sandboxed()`, verifies `process_run` error behavior |
| Agent Code Containment | `S-007` | `tests/221_process_execution.bkr` | Asserts capability bounds under sandbox policies |
| Vector Bounds Check | `S-004` | `tests/231_sandbox_security_bounds.bkr` | Asserts `vec_get_opt` returns `None` for positive OOB and negative indices |
| Slice Bounds Clamping | `S-004` | `tests/231_sandbox_security_bounds.bkr` | Asserts `slice_get` clamps out-of-bounds and `slice_sub` safely truncates |
| HashMap Bounds Safety | `S-004` | `tests/231_sandbox_security_bounds.bkr` | Asserts `hashmap_get_opt` returns `None` on missing keys |
| Fail-Stop Panic Policy | `S-005` | `tests/134_panic_abort_policy.bkr` | Verifies exit code `101` on unrecoverable panic |
| Recoverable Errors | `S-005` | `tests/135_recoverable_error_conventions.bkr`| Verifies `Result<T, E>` and `?` propagation |
| Null Absence Guarantee | `M-008` | `tests/231_sandbox_security_bounds.bkr` | Verifies `Option<T>` and `Result<T, E>` absence handling without nulls |
| Bad Slice Cast Rejection| `S-001` | `tests/230_soundness_slice_cast_BAD.bkr`| Verifies typechecker static rejection of invalid slice casts |

---

## 8. Summary of Guarantees

Under `BKR-SPEC-SEC-001`, Bunker delivers verifiable mathematical safety:
- **Sandbox Security:** Agents and untrusted scripts cannot compromise the host environment.
- **Spatial Bounds:** Out-of-bounds memory accesses are caught or safely clamped; zero buffer overruns.
- **Predictable Failures:** Panics fail-stop cleanly with exit code `101`; recoverable issues propagate cleanly.
- **Null Safety:** 100% absence of null pointer dereferences by construction.
