# Bunker C Codegen Debug Info and Source Mapping Architecture Specification

- **Document ID:** `BKR-SPEC-CGEN-005`
- **Track:** Compiler Backend (`CB`)
- **Milestones Covered:** `CB-006` (P2: Debug info/source mapping)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.capability.v1`, `bunker.debug_map.v1`, `bunker.diagnostic.v1`

---

## 1. Executive Summary

This specification formalizes the debug information and source mapping architecture (`CB-006`) of the Bunker compiler backend (`self-host/modules/c_codegen.bkr` and `self-host/modules/driver.bkr`).

Bunker compiles to intermediate C99/GNU C translation units before invoking system C compilers (GCC, Clang, MSVC) for native code emission. Without source mapping, runtime stack traces, assertion failures, compiler warnings, and symbolic debuggers (GDB, LLDB, WinDbg) reference generated C line numbers, breaking developer ergonomics and AI agent automated diagnosis.

This architecture establishes:
1. **Source Line Directives:** Emitting `#line <line> "<file>"` directives in generated C to map emitted functions, statements, and expressions back to original Bunker source coordinates.
2. **Span-to-Coordinate Translation:** Converting byte spans `(start, end)` into 1-based `(line, column)` coordinates with line-table caching and newline indexing.
3. **Structured Debug Map Schema (`bunker.debug_map.v1`):** Machine-readable source-to-target span and symbol mapping for tooling, IDEs, and agentic error repair.
4. **Runtime Panic & Diagnostic Attribution:** Formatting runtime panics and assertion traps with exact Bunker file, line, and column coordinates.

With this specification and implementation, Track `CB` item `CB-006` is marked `DONE`, completing the entire Compiler Backend track (10/10, 100.0%).

---

## 2. C Preprocessor Source Line Directives

### 2.1 `#line` Directive Standard

In ISO C99 / C11, the preprocessor directive:
```c
#line <line_number> "<source_filename>"
```
resets the internal preprocessor line counter to `<line_number>` and the current translation unit filename to `"<source_filename>"`.

### 2.2 Emission Rules in Bunker C Codegen

The Bunker C codegen emits `#line` directives under the following rules:

- **Invariant DBG-LINE-01 (Function Entry Mapping):** Before emitting any C function prototype or definition, the codegen emits `#line <fn_line> "<source_file>"`. This ensures that debugger function symbol boundaries and frame pointers point to the Bunker `fn` declaration.
- **Invariant DBG-LINE-02 (Statement Line Alignment):** Before non-trivial statement constructs (`let`, `if`, `while`, `match`, `return`, `assign`), codegen emits line directives matching the statement's AST source span.
- **Invariant DBG-LINE-03 (Path Normalization):** Source file paths embedded in `#line` directives use normalized forward slashes (`/`) and escaped quotes to ensure universal portability across GCC, Clang, and MSVC on Linux, macOS, and Windows.
- **Invariant DBG-LINE-04 (Zero Overhead in Optimized Builds):** `#line` directives are preprocessor tokens consumed entirely at compile-time by GCC/Clang/MSVC. They produce zero runtime execution overhead and zero byte expansion in stripped release binaries.

---

## 3. Source Span to Line and Column Translation

### 3.1 Coordinate Model

Bunker compiler tokens and AST nodes track source byte offsets:
$$\text{Span} = (\text{start\_byte}, \text{end\_byte})$$

The coordinate translation engine translates byte offsets to human- and debugger-readable 1-based line and column pairs:

1. **Line Number:** $1 + \text{count of } \mathtt{'\\n'} \text{ in } \text{source}[0..\text{offset}]$.
2. **Column Number:** $1 + (\text{offset} - \text{last\_newline\_index})$.

### 3.2 Line Table Indexing

To support fast $O(\log L)$ span-to-line translation in large translation units, the compiler constructs a Line Table containing the byte offset of each newline character:
$$\text{LineTable} = [0, \text{pos}(\text{NL}_1) + 1, \text{pos}(\text{NL}_2) + 1, \dots, \text{pos}(\text{NL}_{N-1}) + 1]$$

A binary search over $\text{LineTable}$ identifies the enclosing line in $O(\log L)$ time.

---

## 4. Machine-Readable Debug Map Schema (`bunker.debug_map.v1`)

### 4.1 Schema Definition

```json
{
  "$schema": "https://bunker-lang.org/schemas/bunker.debug_map.v1.json",
  "schema_version": "bunker.debug_map.v1",
  "source_file": "src/main.bkr",
  "target_file": "target/debug/c/main.c",
  "source_lines": 142,
  "source_bytes": 4812,
  "line_directives_enabled": true,
  "mappings": [
    {
      "bunker_span": [45, 92],
      "bunker_line": 4,
      "bunker_col": 5,
      "c_line": 28,
      "symbol": "calculate_hash",
      "scope": "kernel::KernelTest"
    }
  ]
}
```

### 4.2 Integration with AI Agent Diagnostics

When an AI agent requests compiler diagnostics or encounters a runtime panic:
1. The diagnostic report references `schema_version: "bunker.self_host.diagnostic.v1"`.
2. The `source_line` and `source_column` fields match the debug map coordinates.
3. The generated C code embeds `/* BUNKER_DEBUG_MAP_JSON: ... */` comment blocks for tools inspecting standalone generated artifacts.

---

## 5. Runtime Panic & Error Attribution

When an assertion or fail-stop trap triggers at runtime, the runtime exception handler formats the error message using source-mapped coordinates:
```text
panic at main.bkr:42:15: array index out of bounds (index 7, length 4)
```

This ensures that developers and automated debugging agents immediately see the exact Bunker source location without inspecting intermediate C code.

---

## 6. Verification Matrix

| Test ID | Fixture File | Verification Criteria | Expected Exit |
|---|---|---|---|
| `T-DBG-01` | `tests/270_c_codegen_source_line_directives.bkr` | Direct line directive emission, path escaping, line restoration, C emission parity | `42` |
| `T-DBG-02` | `tests/271_debug_source_mapping_parity.bkr` | Span-to-line/column translation, line table indexing, `bunker.debug_map.v1` schema, panic attribution | `42` |

---

## 7. Status & Completion

With this specification approved and implemented:
- Milestone: `Q-302`
- Track: `CB` (10 / 10 items `DONE`, 100.0%)
- Overall Ecosystem: `138 / 168` items `DONE` (82.1%)
