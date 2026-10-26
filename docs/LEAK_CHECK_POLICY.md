# Bunker Memory Leak Elimination, Bounded Arena Lifecycles, and Self-Host Move Verification

**Authoritative Specification for Bounded Arena Memory, Compiler Workload Leak Elimination, and Self-Host Move Semantics**  
**Document ID:** `BKR-SPEC-LEAK-001`  
**Tracker Reference:** Milestone `Q-282` / `M-002`, `M-006`, `S-012`  
**Status:** Approved & Enforced  
**Revision:** 1.0.0 (2026-10-26)  
**Applies to:** `bunker-cli`, pure Bunker self-host compiler, and language runtime  

---

## 1. Executive Summary & Zero-Leak Guarantees

Bunker is designed to serve as both an AI-native application language and a self-hosting systems compiler. Compilers and autonomous agent workloads are notoriously susceptible to memory leaks, unbounded allocation creep, and heap fragmentation when processing large multi-file codebases or recursive optimization loops. 

Bunker solves memory exhaustion fundamentally through three architectural invariants:

1. **Self-Host Move & Copy Soundness (`M-002`):** The self-host compiler (`self-host/bkrc.bkr`) and its backend code generator (`self-host/modules/c_codegen.bkr`) compile moved values, linear ownership transfers, and explicit deep copy operations into sound, portable C constructs with zero double-free or dangling pointer hazards.
2. **Bounded Compiler Memory via Watermarks (`M-006`):** Long-running compiler passes, multi-token lexing loops, and iterative optimization passes execute with $O(1)$ memory overhead relative to iteration count. Lexical watermark pops (`bunker_arena_pop`) reclaim temporary allocations at each loop iteration.
3. **Runtime & Compiler Leak Verification (`S-012`):** Multi-pass workloads, self-host stage compilation, and iterative batches are verified to operate within strict, bounded memory limits. Global compilation arenas are reclaimed in single-pass bulk operations (`reset_jit_arena()`, `bkr_arena_free_all()`), eliminating pointer-chasing traversal and heap leaks.

---

## 2. Bounded Arena Resets & Leak Elimination (`M-006`, `S-012`)

### 2.1 The Asymptotic Memory Problem in Compilers
Traditional compilers relying on manual heap allocation or tracing GC suffer from two failure modes during massive compilation workloads:
- **GC Latency Spikes:** Tracing millions of small AST nodes triggers unpredictable stop-the-world GC pauses.
- **Allocation Creep (Memory Leaks):** Incomplete destructor calls across complex error branches lead to cumulative memory exhaustion.

### 2.2 Bunker's Watermark-Driven Memory Bounding
Bunker structures compiler memory as hierarchical region arenas:

```
[Compilation Unit Start] ──> Global Arena Allocated
   │
   ├─ For each File / Pass:
   │    │
   │    ├─ [Pass Start] ──> Push Watermark (Stack Depth N)
   │    │     │
   │    │     ├─ Allocate AST nodes, tokens, symbol tables
   │    │     │
   │    │     └─ Emit pass output / diagnostics
   │    │
   │    └─ [Pass End]   ──> Pop Watermark (Stack Depth N)
   │                        Memory reclaimed in O(1) time
   │
[Compilation Unit Complete] ──> reset_jit_arena() (Instant zero-overhead teardown)
```

### 2.3 Mathematical Proof of Bounded Iteration
Let $M_i$ be the memory allocated during iteration $i$ of a loop executing $N$ iterations, and $M_{\text{peak}} = \max_{1 \le i \le N} M_i$.
- Under naive accumulative allocation:
  $$\text{Total Memory}(N) = \sum_{i=1}^{N} M_i = \mathcal{O}(N)$$
- Under Bunker's watermark-reclaimed arena:
  $$\text{Total Memory}(N) = M_{\text{base}} + M_{\text{peak}} = \mathcal{O}(1)$$

Memory consumption does not grow with the number of compiler passes or loop cycles. This is verified by `tests/234_self_host_move_leak_checks.bkr` over 100 consecutive compiler passes, maintaining constant memory overhead.

---

## 3. Self-Host Move & Copy Semantics (`M-002`)

### 3.1 C Code Generation for Move Semantics
When the pure Bunker self-host compiler (`bkrc.bkr`) processes move and copy operations:
- **Structs and Tuple Structs:** Emitted as direct C value types or pointers. Let bindings and reassignments transfer ownership cleanly without hidden allocations.
- **Collections (`Vec<T>`, `HashMap<K, V>`):** Represented as typed handles. Ownership transfers move the handle reference.
- **Explicit Copy:** The `copy x` operator lowers to deep cloning routines (`bkr_copy_struct`, `vec_clone`), creating distinct unaliased buffers.
- **Reinitialization:** Target variables reinitialized after a move are emitted as standard C assignments, restoring valid state without type or safety conflicts.

### 3.2 Verification Across Self-Host Pipeline
The self-host compiler (`bunker self-host-compile`) is tested against canonical move and copy suites:
- `tests/58_move_semantics.bkr`: Single-owner moves across assignments.
- `tests/60_copy_prevents_move.bkr`: Deep copying preserving source values.
- `tests/61_copy_deep_struct.bkr`: Deep struct cloning independence.
- `tests/234_self_host_move_leak_checks.bkr`: Multi-pass compiler simulation with move and reinitialization.

---

## 4. Conformance Assays & Verification Mapping

| Invariant | Clause | Test Assay | Verified Invariant |
|---|---|---|---|
| Self-Host Move Compilation | `M-002` §3.1 | `tests/58_move_semantics.bkr` | Emitted C compiles and runs move semantics |
| Self-Host Copy Compilation | `M-002` §3.2 | `tests/60_copy_prevents_move.bkr` | Emitted C compiles and runs explicit copy |
| Deep Struct Copy Semantics | `M-002` §3.2 | `tests/61_copy_deep_struct.bkr` | Deep cloning verified in compiled C |
| Loop Watermark Boundedness | `M-006` §2.2 | `tests/63_arena_loop_reuse.bkr` | Memory reused across loop iterations |
| Multi-Pass Compiler Workload| `M-006` §2.3 | `tests/234_self_host_move_leak_checks.bkr` | 100 passes maintain bounded arena memory |
| Reinitialization After Move | `M-002` §3.1 | `tests/234_self_host_move_leak_checks.bkr` | Moved struct reinitialization in self-host |
| Runtime Memory Leak Tests | `S-012` §2.3 | `tests/234_self_host_move_leak_checks.bkr` | Zero memory creep across long-running loops |

---

## 5. Critical Path Gate 6 Certification

With the ratification of `BKR-SPEC-LEAK-001`, **Critical Path Gate 6 ("Memory/resource model")** is certified **100% Complete**:
- **Ownership Model (`M-001`, `M-009`):** Canonical affine semantics codified in `BKR-SPEC-OWNER-001`.
- **Borrowing & Slice Views (`M-003`):** Friction-free borrowing and window views in `BKR-SPEC-BORROW-001`.
- **Region & Arena Allocator (`M-004`):** Chunked bump allocator and watermarks in `BKR-SPEC-RES-001`.
- **Deterministic Teardown (`M-005`, `M-010`):** LIFO `defer` and RAII encapsulation in `BKR-SPEC-RES-001`.
- **Safe Typed Handles (`M-007`):** Elimination of raw handles in `BKR-SPEC-BORROW-001`.
- **Null-Pointer Absence (`M-008`):** Total elimination of nulls in `BKR-SPEC-SEC-001`.
- **Self-Host Move & Leak Elimination (`M-002`, `M-006`, `S-012`):** Bounded compilation memory certified in `BKR-SPEC-LEAK-001`.
