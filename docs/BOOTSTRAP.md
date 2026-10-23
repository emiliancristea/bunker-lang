# Bunker Compiler Bootstrap Specification

This document defines the canonical 3-stage bootstrap architecture, fixpoint verification protocol, and standalone CLI driver contract for the self-hosted Bunker language compiler (`bkrc`).

---

## 1. Overview & Architectural Goal

The ultimate objective of the Bunker compiler project is complete independence from the initial Rust implementation (`bunker-cli`). While `bunker-cli` (built with Cranelift, Pest, and Z3) provides an immediate JIT and native code execution environment for rapid language experimentation, the production compiler is written in pure Bunker (`self-host/bkrc.bkr` and `self-host/modules/*.bkr`) and targets ISO C11.

By compiling Bunker sources to clean, portable C11 that links against `self-host/runtime.h`, Bunker can be compiled and executed on any platform with a standard C compiler (GCC, Clang, MSVC) without requiring the Rust toolchain.

---

## 2. The 3-Stage Bootstrap Lifecycle

The bootstrap chain progresses through three distinct stages to achieve a verified self-hosted fixpoint:

```
  [ Rust Host Compiler: bunker-cli ]
                 │
                 │  Stage 0: bunker-cli self-host-compile self-host/bkrc.bkr -o bkrc-stage1.c
                 ▼
      [ C Source: bkrc-stage1.c ]
                 │
                 │  Stage 1: cc -std=c11 bkrc-stage1.c -o bkrc-stage1
                 ▼
  [ Stage 1 Binary: bkrc-stage1 ]  (Pure C executable derived from Bunker sources)
                 │
                 │  Stage 2: bkrc-stage1 self-host/bkrc.bkr -o bkrc-stage2.c
                 ▼
      [ C Source: bkrc-stage2.c ]
                 │
                 ├──► FIXPOINT VERIFICATION: diff -u bkrc-stage1.c bkrc-stage2.c == 0
                 │
                 │  cc -std=c11 bkrc-stage2.c -o bkrc-stage2
                 ▼
  [ Stage 2 Binary: bkrc-stage2 ]  (Self-compiled compiler)
                 │
                 │  Stage 3: bkrc-stage2 <user.bkr> -o <user.c>
                 ▼
     [ Standalone User Binary ]    (Completely independent of Rust!)
```

### Stage 0: Rust Host Bootstrap
- **Actor:** `bunker-cli` (Rust bootstrap compiler).
- **Command:**
  ```bash
  bunker-cli self-host-compile self-host/bkrc.bkr -o bkrc-stage1.c
  ```
- **Role:** Parses the modular Bunker compiler sources, resolves relative imports, typechecks, and emits the initial Stage 1 C translation (`bkrc-stage1.c`).

### Stage 1: Pure-C Compiler Binary
- **Actor:** System C11 compiler (GCC / Clang / MSVC).
- **Command:**
  ```bash
  cc -std=c11 bkrc-stage1.c -o bkrc
  ```
- **Role:** Produces the first executable Bunker compiler binary (`bkrc`). At this point, the compiler logic is executing entirely from C native machine code with zero Rust dependencies.

### Stage 2: Self-Compiled Compiler & Fixpoint Check
- **Actor:** Stage 1 binary (`bkrc`).
- **Command:**
  ```bash
  ./bkrc self-host/bkrc.bkr -o bkrc-stage2.c
  ```
- **Fixpoint Invariant:**
  ```bash
  diff -u bkrc-stage1.c bkrc-stage2.c
  ```
  The C code emitted by Stage 1 when compiling itself must be byte-exact identical to the C code emitted by the Stage 0 Rust compiler. A clean `diff` (exit status 0) mathematically proves that:
  1. The self-hosted compiler reproduces its own code generation deterministically.
  2. The Bunker-written lexer, parser, resolver, typechecker, and C codegen preserve semantic equivalence with the bootstrap compiler.
- **Stage 2 Build:**
  ```bash
  cc -std=c11 bkrc-stage2.c -o bkrc2
  ```

### Stage 3: Standalone Toolchain
- **Actor:** Stage 2 binary (`bkrc2`).
- **Command:**
  ```bash
  ./bkrc2 my_program.bkr -o my_program.c
  cc -std=c11 my_program.c -o my_program
  ./my_program
  ```
- **Role:** The compiler operates completely stand-alone, compiling user programs without the Rust toolchain installed.

---

## 3. Standalone CLI Driver Specification

The self-host compiler driver (`self-host/modules/driver.bkr`) exposes a standard POSIX-compatible command-line interface:

### Synopsis
```
bkrc [<input-file.bkr>] [-o <output-file.c>]
```

### Arguments & Options
- `<input-file.bkr>` (Positional): Path to the root Bunker source file.
  - Relative imports within the source file (`import "path/to/module.bkr";`) are resolved relative to the directory containing the root input file (`import_path_dir(input_file)`).
- `-o <output-file.c>` (Option): Path where the generated C11 code will be written.
  - If omitted but an input file is provided, defaults to `<input-file.bkr>.c`.
- **Zero-Argument Invocation (Backward Compatibility):**
  - If invoked with no arguments (`argc == 1`), `bkrc` defaults to:
    - Input: `self_host_input.bkr`
    - Output: `self_host_output.c`
  - If `self_host_input.bkr` does not exist, a minimal default kernel is provisioned.

### Exit Codes
- `42`: **Success.** The source file was parsed, resolved, typechecked, and emitted to C successfully.
- `1`: **File I/O or Configuration Error.** Input file not found, or output file could not be written.
- `2`: **Verification Failure.** Output file generation was interrupted.

### Embedded Metadata Manifests
On successful compilation, `bkrc` embeds structured diagnostic and capability JSON comments directly into the emitted C file:
- `/* BUNKER_CAPABILITY_JSON: { ... } */` — Supported language compiler capabilities and versioning.
- `/* BUNKER_AST_JSON: { ... } */` — Structural AST representation.
- `/* BUNKER_TYPE_GRAPH_JSON: { ... } */` — Declared types and inference graph.
- `/* BUNKER_SYMBOL_TABLE_JSON: { ... } */` — Interned symbols and scope resolutions.
- `/* BUNKER_RESOLVER_JSON: { ... } */` — Semantic resolution report.
- `/* BUNKER_TYPECHECK_JSON: { ... } */` — Static typechecking and exhaustiveness diagnostics.

---

## 4. Runtime & Memory Architecture

The self-hosted compiler links against `self-host/runtime.h`, which provides:
1. **Arena Allocator:** 64KB chunked bump-pointer arena for AST nodes, tokens, and temporary compiler strings, avoiding heap fragmentation and costly fine-grained `free` calls.
2. **Fast ASCII Table:** Zero-allocation pre-computed lookup tables for ASCII character codes (0..127) used heavily in lexing.
3. **Tagged Boxed Unions (`BkrEnumBox`):** 64-bit pointer-safe representation for enum payloads carrying strings or heap pointers without bit truncation.
4. **Vector & HashMap Collections:** High-performance, arena-backed dynamic arrays (`Vec<T>`) and associative maps (`HashMap<K, V>`).
5. **Process Argument Ingestion:** `bkr_init_args(argc, argv)`, `bkr_args_count()`, and `bkr_arg_at(index)` providing safe CLI parameter access.

---

## 5. Automated CI Verification Protocol

Every commit is gated by the GitHub Actions `self-host-smoke` pipeline:
1. Compiles `self-host/bkrc.bkr` using `bunker-cli self-host-compile` into `/tmp/bkrc.c`.
2. Builds Stage 1 `/tmp/bkrc` with `cc -std=c11`.
3. Verifies direct CLI compilation of fixtures (`/tmp/bkrc tests/01_basic_math.bkr -o /tmp/output.c`).
4. Compiles Stage 2 `bkrc2` using Stage 1 `/tmp/bkrc` via direct CLI invocation.
5. Executes Stage 1 and Stage 2 across the entire golden test suite.
6. Asserts `diff -u stage1_output.c stage2_output.c` produces 0 changes across golden test fixtures.
7. Publishes Stage 1 and Stage 2 build artifacts (`bkrc-stage1.c`, `bkrc-stage1`, `bkrc-stage2.c`, `bkrc-stage2`, `runtime.h`).
