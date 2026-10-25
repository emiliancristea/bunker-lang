# Bunker Region/Arena Memory Rules, Deterministic Teardown, and Resource Management

**Authoritative Specification for Region Allocation, Arena Watermarks, LIFO Defer Semantics, and Resource Lifecycles**  
**Document ID:** `BKR-SPEC-RES-001`  
**Tracker Reference:** Milestone `Q-280` / `M-004`, `M-005`, `M-010`  
**Status:** Approved & Enforced  
**Revision:** 1.0.0 (2026-10-25)  
**Applies to:** `bunker-cli`, pure Bunker self-host compiler, and language runtime  

---

## 1. Executive Summary & Foundational Resource Axioms

Bunker delivers predictable, high-performance systems programming and compiler workloads without a tracing Garbage Collector (GC) or manual pointer free hazards (`free()` / `delete`). Resource management in Bunker is governed by two complementary mechanisms:

1. **Region/Arena Memory Allocation (`M-004`):** Dynamic memory (strings, slices, vectors, hashmaps, AST nodes, and diagnostic envelopes) is allocated into region-scoped bump arenas. Blocks and loops maintain watermark positions; exiting a scope or loop iteration restores the watermark, reclaiming memory in $O(1)$ time without memory fragmentation or allocation overhead.
2. **Deterministic Destructor & Drop Semantics (`M-005`):** Custom teardown logic, state resets, and resource cleanup are executed via lexical `defer` statements. Defers execute in strict Last-In, First-Out (LIFO) order upon block exit, early returns, or error propagation (`?`), executing before the arena watermark is restored.
3. **Deterministic Resource Types (`M-010`):** External operating system resources—including open file handles, child process spawns, sockets, and temporary directories—are encapsulated and deterministically released via explicit defer patterns, guaranteeing leak-free operation.

---

## 2. Region & Arena Allocation Rules (`M-004`)

### 2.1 Chunked Bump Allocator Architecture
Both the Cranelift JIT runtime (`bunker-cli/src/jit.rs`) and the pure Bunker C runtime (`self-host/runtime.h`) implement chunked bump arena allocators:
- **Block Size:** Standard blocks are sized at $64\text{ KB}$ (`ARENA_BLOCK_SIZE` / `BKR_ARENA_BLOCK_SIZE`). Oversized single allocations receive dedicated contiguous blocks.
- **Fast Path:** Allocation within an active block is an $O(1)$ pointer increment aligned to word or pointer boundaries ($8$ bytes on 64-bit systems).
- **Zero Free Overhead:** Individual allocations do not maintain free lists, reference counts, or block headers.

### 2.2 Lexical Scope Watermarking
To support nested block execution without unbounded memory growth, the runtime maintains a watermark stack:
```
[Block Entry]   ──> Push watermark (current block + offset) onto Watermark Stack
                      │
                      ├─ Allocations bump forward in active arena block
                      │
[Block Exit]    ──> Pop watermark from Watermark Stack
                ──> Restore arena pointer to saved offset (freeing all block allocations)
```

1. **At Block Entry:** The runtime calls `bunker_arena_push()`. The current block pointer and byte offset are pushed onto `WATERMARK_STACK`.
2. **Within Block:** Values allocated inside the block (e.g. temporary structs, strings, or collections) consume arena space.
3. **At Block Exit:** The runtime calls `bunker_arena_pop()`. All memory allocated since the matching push is instantly reclaimed.

### 2.3 Loop Iteration Memory Reuse
Loops that construct temporary objects on each iteration (e.g., parsing tokens, processing AST children, or evaluating compiler passes) reuse arena memory:
- At the start of each loop iteration, a watermark is recorded.
- At the end of the iteration, the watermark is restored.
- **Guarantee:** A loop executing $N$ iterations consumes memory proportional to the maximum allocation of a *single* iteration, not $O(N)$ cumulative memory.

### 2.4 Compiler Workload Arena Reset
For large-scale compiler pipelines, whole-compilation units operate within a top-level compilation arena:
- Self-host stages (`bkrc.bkr`) and CLI runs allocate all AST nodes, symbols, and type graphs within the compilation arena.
- Upon completion of a compilation unit or shell command, the entire arena is reclaimed via `reset_jit_arena()` (or `bkr_arena_free_all()`), eliminating pointer-chasing traversal during compiler teardown.

---

## 3. Deterministic Destructor & Drop Semantics (`M-005`)

### 3.1 Lexical Defer Statements
Bunker provides `defer <stmt>` and `defer { <block> }` for deterministic cleanup. Defer statements register cleanup actions associated with the innermost enclosing lexical block:

```bunker
fn process_file(path: str) -> Result<i32, str> {
    let handle = open_resource(path)?;
    defer close_resource(handle);

    let data = read_data(handle)?;
    return Ok(parse_data(data));
}
```

### 3.2 Strict LIFO Execution Invariant
When a scope contains multiple `defer` registrations, they execute in reverse order of appearance:
$$\text{Registration Order: } D_1, D_2, \dots, D_k \implies \text{Execution Order: } D_k, D_{k-1}, \dots, D_1$$

This ensures that resources depending on previously acquired states are finalized before their dependencies are torn down.

### 3.3 Defer Precedence over Arena Reclamation
A critical safety requirement of region memory is that deferred blocks can read and flush structured data allocated within their owning block before that memory is invalidated:

$$\text{Block Execution} \longrightarrow \mathbf{Execute\ Defers\ (LIFO)} \longrightarrow \mathbf{Restore\ Arena\ Watermark} \longrightarrow \text{Exit Scope}$$

1. First, all registered defers for the scope execute.
2. Second, the arena watermark is restored, freeing temporary memory.

### 3.4 Unwinding on Early Returns and the Try Operator `?`
Defers are guaranteed to execute across all non-panicking control flow exits:
- **Normal Fallthrough:** Defers for the block execute at closing brace `}`.
- **Explicit `return`:** All defers from all active enclosing lexical blocks up to the function root execute in LIFO order before the function returns to its caller. The return expression value is evaluated *before* defers execute, ensuring defers do not mutate the returned value.
- **Try Operator `?`:** When an expression `expr?` encounters `Result.Err` or `Option.None`, all active enclosing defers execute before the error or none value is propagated.

### 3.5 Restrictions on Control Flow Inside Defer
To preserve deterministic unwinding semantics, control flow statements that escape a `defer` block (`return`, `break`, `continue`) are strictly prohibited and rejected at compile time.

---

## 4. Resource Types & Encapsulation Patterns (`M-010`)

### 4.1 Encapsulation of OS Resources
Operating system resources cannot rely solely on memory reclamation; OS file descriptors, process handles, and network sockets require explicit OS syscalls for disposal. Bunker enforces deterministic resource closure through the RAII-defer pattern:

```bunker
struct ScopedFile {
    path: str,
    is_open: bool,
}

fn write_config(path: str, data: str) -> Result<bool, str> {
    let res = file_write(path, data);
    defer {
        // Enforce synchronization or cleanup
        log("File write completed");
    }
    return res;
}
```

### 4.2 Temporary Files and Directories
Operations requiring temporary scratch space (e.g., self-host compiler stages, code generation, intermediate artifacts) must pair creation with deferred deletion:

```bunker
fn run_sandboxed_job(temp_dir: str) -> Result<i64, str> {
    dir_create(temp_dir)?;
    defer dir_remove(temp_dir);

    // Job logic...
    return Ok(42);
}
```
Even if an intermediate operation fails with `?`, `dir_remove(temp_dir)` is guaranteed to run.

---

## 5. Conformance Assays & Verification Mapping

The invariants specified in `BKR-SPEC-RES-001` are verified continuously across the automated test suite:

| Capability | Specification Clause | Test Assay | Verified Invariant |
|---|---|---|---|
| Region Arena Scoping | `M-004` §2.2 | `tests/02_arena_memory.bkr` | Allocates buffer, executes defer, arena frees on return |
| Nested Arena Scoping | `M-004` §2.2 | `tests/64_arena_nested_blocks.bkr` | Inner allocations reclaimed; outer persist |
| Branch Arena Scoping | `M-004` §2.2 | `tests/65_arena_if_branches.bkr` | Each branch reclaims its own arena allocations |
| Loop Watermark Reuse | `M-004` §2.3 | `tests/63_arena_loop_reuse.bkr` | Loop iterations reuse arena memory without leakage |
| Defer Return Evaluation | `M-005` §3.4 | `tests/15_kernel_defer_return.bkr` | Return value computed before deferred mutation runs |
| Shell Agent Defer | `M-005` §3.1 | `tests/26_shell_defer.bkr` | Defer cleanup in shell agent handlers |
| Try Operator Defer Unwind| `M-005` §3.4 | `tests/132_try_operator.bkr` | Active defers execute when `?` unwraps `Err` |
| Multi-Defer LIFO Order | `M-005` §3.2 | `tests/232_arena_resource_drop.bkr` | Verifies 3 nested defers execute in strict reverse order |
| Defer On Try Error | `M-005` §3.4 | `tests/232_arena_resource_drop.bkr` | Verifies cleanup flag sets when `?` propagates error |
| Deterministic Resource Drop| `M-010` §4.1 | `tests/232_arena_resource_drop.bkr` | Verifies resource teardown on block exit |

---

## 6. Summary of Resource Guarantees

Under `BKR-SPEC-RES-001`:
1. **$O(1)$ Region Allocation:** Zero pointer-chasing GC sweeps; instantaneous bump allocation.
2. **Bounded Memory:** Loop watermarks ensure iterative algorithms run with $O(1)$ memory overhead.
3. **Deterministic Cleanup:** Defers execute deterministically in LIFO order across all exit paths.
4. **Leak-Free Systems:** File descriptors, directories, and memory are guaranteed to release on schedule.
