# Bunker Arena Allocator & Serialization Architecture

**Document ID:** `BKR-SPEC-ARENA-001`  
**Status:** Canonical & Locked  
**Scope:** Runtime & Standard Library (`R-013`, `R-014`)  
**Ecosystem Milestone:** `Q-292`  

---

## 1. Executive Summary & Architectural Motivation

Large-scale compilers and agentic workflows require bounded, predictable memory consumption and structured data exchange. Uncontrolled individual heap allocations introduce fragmentation and memory leaks, while unstructured outputs hinder tooling and AI-repair workflows.

This specification formalizes two critical, zero-dependency standard library modules authored in pure Bunker:

1. **`self-host/modules/arena.bkr` (`R-013`)**: A chunked bump-allocator library with watermark snapshots, peak utilization tracking, and deterministic $O(1)$ bulk resets that ensure compiler phase allocations remain strictly bounded.
2. **`self-host/modules/serializer.bkr` (`R-014`)**: A serialization engine providing round-trip encoding and decoding abstractions for compiler ASTs, diagnostics, symbol tables, and type graphs conforming to the canonical `bunker.*.v1` schema ecosystem.

With the completion of these modules, Track `R` (Runtime and Standard Library) reaches **100.0% completion (16/16 DONE)**, officially closing the track as the 7th fully completed track in the Bunker platform.

---

## 2. Arena Allocator Library Architecture (`R-013`)

### 2.1 Chunked Bump Allocation Model

The pure Bunker arena allocator operates on a linked list of uniform memory chunks (`Vec<Bytes>`). When an allocation request exceeds the remaining capacity of the active chunk, a new chunk is provisioned without resizing or relocating existing memory blocks.

```bunker
struct ArenaStats {
    total_allocated: i64,
    active_bytes: i64,
    peak_bytes: i64,
    block_count: i64,
    reset_count: i64
}

struct ArenaWatermark {
    block_index: i64,
    offset: i64
}

struct Arena {
    chunk_size: i64,
    blocks: Vec<Bytes>,
    current_block: i64,
    current_offset: i64,
    stats: ArenaStats
}
```

### 2.2 Watermark & Bulk Deallocation

- **`arena_watermark(arena: Arena) -> ArenaWatermark`**: Captures a snapshot of the current chunk index and offset.
- **`arena_reset_to(arena: Arena, mark: ArenaWatermark)`**: Rolls back the allocation pointer to the recorded watermark, instantly reclaiming all intermediate memory without traversal overhead.
- **`arena_reset_all(arena: Arena)`**: Resets the allocation head to index 0, offset 0 while retaining allocated chunk capacity for subsequent compiler passes.
- **`arena_stats(arena: Arena) -> ArenaStats`**: Queries memory metrics, including total bytes allocated across time, currently active bytes, peak high-watermark, and reset invocations.

---

## 3. Serialization Engine Architecture (`R-014`)

### 3.1 Schema-Tagged Serialization

The serialization engine standardizes encoding and decoding of compiler representations into canonical, machine-readable representations:

| Artifact Type | Schema Identifier | Primary Encoder |
|---|---|---|
| **AST Summary** | `bunker.ast.v1` | `serialize_ast_summary(item_count, root_name, has_entry)` |
| **Diagnostics Report** | `bunker.diagnostics.v1` | `serialize_diagnostic_report(report)` |
| **Symbol Table Entry** | `bunker.symbol_table.v1` | `serialize_symbol_table_entry(name, kind, scope, line, col)` |
| **Type Info** | `bunker.type_graph.v1` | `serialize_type_info(type_name, size_bytes, c_abi)` |

### 3.2 Deserialization & Extraction Primitives

Building upon the lexical scanner in `modules/json.bkr`, `modules/serializer.bkr` exposes strongly-typed decoding helpers:
- `serializer_extract_str(payload: str, field: str) -> str`
- `serializer_extract_i64(payload: str, field: str) -> i64`
- `serializer_extract_bool(payload: str, field: str) -> bool`
- `serializer_extract_object(payload: str, field: str) -> str`

---

## 4. Verification & Conformance Matrix

| Test Identifier | Coverage / Verification Target | Expected Result |
|---|---|---|
| `tests/250_arena_allocator_lib.bkr` | Chunk allocation, overflow across blocks, watermark rollbacks, full resets, and metrics tracking | Returns 42 |
| `tests/251_serialization_engine.bkr` | Schema-tagged AST, diagnostic, symbol table serialization and typed deserialization | Returns 42 |
| `bunker self-host-check` | Clean self-host compiler check with 0 diagnostics | 8/8 files PASS |
| `bunker self-host-compile` | Compilation of test fixtures through self-host compiler | Generated C accepted |
| `run_tests.ps1` | Full test suite execution across all 266 fixtures | 100% pass rate |

---

## 5. Track R Completion Status

With Milestone `Q-292`:
- Track `R` reaches **16 / 16 (100.0%)** completion.
- Total ecosystem completion advances to **112 / 168 (66.7%)**.
