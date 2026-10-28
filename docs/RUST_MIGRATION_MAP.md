# Bunker Rust Compiler Subsystem Migration Map

**Authoritative Architecture Specification & Module Migration Ledger**  
**Document ID:** `BKR-SPEC-MIGRATE-001`  
**Tracker Reference:** Milestone `Q-240` / `SH-008`  
**Status:** Approved & Living Document  

---

## 1. Executive Summary & Migration Objective

The primary architectural goal of the Bunker language project is **complete independence from the initial Rust host implementation (`bunker-cli`)**.

While the Rust compiler provided an initial execution platform (via Cranelift, Pest, and Z3) for fast iteration and bootstrapping, the production Bunker toolchain is written entirely in Bunker itself (`self-host/bkrc.bkr` and `self-host/modules/*.bkr`), emitting portable ISO C11 that links against [`self-host/runtime.h`](../self-host/runtime.h).

This document provides the authoritative **1:1 migration map** tracking every Rust compiler subsystem in `bunker-cli/src/` to its pure-Bunker replacement target in `self-host/modules/`, defining parity criteria, current status, remaining gaps, and the formal deprecation gates for sunsetting Stage 0.

---

## 2. 1:1 Subsystem Migration Ledger

| Rust Subsystem (`bunker-cli/src/`) | Bunker Replacement Target (`self-host/modules/`) | Core Responsibility | Status | Parity |
|---|---|---|:---:|:---:|
| [`main.rs`](../bunker-cli/src/main.rs) | [`driver.bkr`](../self-host/modules/driver.bkr) & [`bkrc.bkr`](../self-host/bkrc.bkr) | CLI argument ingestion (`bkrc <in> -o <out>`), driver pipeline orchestration, exit codes. | **DONE** | 90% |
| [`parser.rs`](../bunker-cli/src/parser.rs) + `bunker.pest` | [`lexer.bkr`](../self-host/modules/lexer.bkr) & [`parser.bkr`](../self-host/modules/parser.bkr) | Pure-Bunker lexer and recursive descent parser without external grammar generators. | **DONE** | 95% |
| [`ast.rs`](../bunker-cli/src/ast.rs) & [`ast_builder.rs`](../bunker-cli/src/ast_builder.rs) | [`ast.bkr`](../self-host/modules/ast.bkr), [`kind_model.bkr`](../self-host/modules/kind_model.bkr), [`constants.bkr`](../self-host/modules/constants.bkr) | AST construction, node kinds, typed AST wrappers, spans, and pattern definitions. | **DONE** | 90% |
| [`typeck.rs`](../bunker-cli/src/typeck.rs) | [`typecheck.bkr`](../self-host/modules/typecheck.bkr), [`resolver.bkr`](../self-host/modules/resolver.bkr), [`symbol_table.bkr`](../self-host/modules/symbol_table.bkr), [`type_graph.bkr`](../self-host/modules/type_graph.bkr) | Lexical scoping, name resolution, type inference, return checking, exhaustiveness. | **PARTIAL** | 75% |
| [`builtins.rs`](../bunker-cli/src/builtins.rs) | [`runtime.h`](../self-host/runtime.h) & stdlib builtins in [`typecheck.bkr`](../self-host/modules/typecheck.bkr) | Standard library signatures, runtime builtin dispatch, arithmetic/string/collection methods. | **DONE** | 90% |
| [`codegen.rs`](../bunker-cli/src/codegen.rs) | [`c_codegen.bkr`](../self-host/modules/c_codegen.bkr) & [`cgen_state.bkr`](../self-host/modules/cgen_state.bkr) | C11 source emission, statement expressions, LIFO defer unwinding, expression lowering. | **DONE** | 85% |
| [`jit.rs`](../bunker-cli/src/jit.rs) | [`runtime.h`](../self-host/runtime.h) + System C Compiler (GCC / Clang / MSVC) | In-memory execution; replaced in self-host architecture by compiling emitted C directly. | **DONE** | 95% |
| [`comptime.rs`](../bunker-cli/src/comptime.rs) | [`c_codegen.bkr`](../self-host/modules/c_codegen.bkr) (const folding) + future `comptime.bkr` | Compile-time constant evaluation and static reduction. | **PARTIAL** | 60% |
| [`diagnostic.rs`](../bunker-cli/src/diagnostic.rs) | [`ast_report.bkr`](../self-host/modules/ast_report.bkr) & [`report_support.bkr`](../self-host/modules/report_support.bkr) | ANSI colored error formatting and machine-readable JSON reports (`BUNKER_*_JSON`). | **DONE** | 80% |
| [`verify.rs`](../bunker-cli/src/verify.rs) & [`smt.rs`](../bunker-cli/src/smt.rs) | `self-host/modules/verify.bkr` (planned) | SMT-backed contract and refinement type verification via solver integration. | **TODO** | 20% |
| [`shell_codegen.rs`](../bunker-cli/src/shell_codegen.rs) & [`shell_runtime.rs`](../bunker-cli/src/shell_runtime.rs) | `self-host/modules/shell.bkr` (planned) + `runtime.h` actor hooks | Shell actor declarations, message passing channels, reactive state scheduling. | **TODO** | 30% |
| [`view_runtime.rs`](../bunker-cli/src/view_runtime.rs) | `self-host/modules/view.bkr` (planned) | Reactive UI view graph rendering and incremental component updates. | **TODO** | 10% |

---

## 3. Subsystem Deep Dives & Replacement Specifications

### 3.1. Front-End: Parser & Grammar (`parser.rs` -> `lexer.bkr`, `parser.bkr`)
- **Rust Host Design:** Uses Pest parser generator (`bunker.pest`) with packrat parsing and AST builder visitor.
- **Bunker Target Design:** Hand-written recursive descent lexer and parser in pure Bunker. Tokens are interned into flat arrays and cursor state is managed through `ParserStateRef`.
- **Parity Criteria:** Accepts all grammar constructs: kernels, structs, functions, pattern matching, enum payloads, tuples, labeled loops, destructuring, and postfix operators.
- **Current Status:** Fully operational in Stage 1 and Stage 2. Verified by self-compilation of `bkrc.bkr` (over 7,500 lines).

### 3.2. AST & Kind Models (`ast.rs` -> `ast.bkr`, `kind_model.bkr`, `constants.bkr`)
- **Rust Host Design:** Rust algebraic sum types (`enum Expr`, `enum Stmt`, `enum Pattern`, `enum Type`).
- **Bunker Target Design:** Flat node vector representation (`Vec<i64>`) with strongly-typed wrapper references (`AstNodeRef`, `AstExprRef`, `AstStmtRef`, `AstTypeRef`, `AstPatternRef`).
- **Parity Criteria:** Centralized constructors, tag extraction, child handle traversal, and source span attachment.
- **Current Status:** Pure Bunker AST bridges fully implemented; typed struct representation migration in progress (`SH-003`).

### 3.3. Semantic Analysis & Typechecking (`typeck.rs` -> `typecheck.bkr`, `resolver.bkr`, `symbol_table.bkr`)
- **Rust Host Design:** Scoped symbol tables, multi-pass type inferencing, pattern exhaustiveness checking, bounds analysis.
- **Bunker Target Design:** Separated into 4 modular self-host passes:
  1. `resolver.bkr`: Resolves identifier scopes, detects shadowing and undeclared symbols.
  2. `symbol_table.bkr`: Tracks variable allocations, function signatures, and struct field offsets.
  3. `type_graph.bkr`: Resolves recursive types and detects circular definitions.
  4. `typecheck.bkr`: Validates types, enforces return signatures, and ensures type compatibility.
- **Parity Criteria:** Diagnostic equivalence with Rust host for all test fixtures.

### 3.4. Code Generation & Execution (`codegen.rs`, `jit.rs` -> `c_codegen.bkr`, `runtime.h`)
- **Rust Host Design:** Generates Cranelift IR in-memory, lowering directly to machine code via Cranelift SSA or emitting object files.
- **Bunker Target Design:** Emits standard ISO C11 that compiles with any C compiler. Memory management utilizes arena allocators and reference semantics defined in [`self-host/runtime.h`](../self-host/runtime.h).
- **Parity Criteria:**
  - Full support for statements, control flow, functions, structs, arrays, tuples, enums, labeled loops, and try operators.
  - Fixpoint equivalence: `bkrc` compiling itself yields identical C code across consecutive generations (`diff -u bkrc-stage1.c bkrc-stage2.c` passes with zero differences).

---

## 4. Migration Phasing & Stage 0 Sunsetting Ladder

```
[Phase 1: Core Pipeline]  ==>  [Phase 2: Full Semantics]  ==>  [Phase 3: AI Diagnostics]  ==>  [Phase 4: Verification]  ==>  [Phase 5: Sunsetting]
     (COMPLETED)                     (IN FLIGHT)                    (QUEUED)                     (PLANNED)                 (FINAL CUTOVER)
```

### Phase 1: Core Compiler Pipeline (Completed ✅)
- Self-host lexer, parser, C codegen, and CLI driver.
- 3-stage bootstrap lifecycle documented in [`docs/BOOTSTRAP.md`](BOOTSTRAP.md).
- Stage 1 and Stage 2 compiler execution automated in CI.

### Phase 2: Full Semantic & Standard Library Parity (Current Target)
- Complete generic collection types in self-host (`SH-005`).
- Complete typed AST structs in self-host (`SH-003`).
- Full type inference across nested expressions.

### Phase 3: Diagnostic & Machine-Readable Parity
- Rich ANSI diagnostics with caret pointers.
- Unified JSON diagnostic outputs matching `bunker-cli --format json`.
- Reproducible self-host artifact generation in CI (`SH-010`).

### Phase 4: Verification & Advanced Runtime Subsystems
- Self-host SMT solver bridge for contract checking (`verify.rs` / `smt.rs`).
- Native shell actor runtime and message bus implementation.

### Phase 5: Stage 0 Deprecation & Toolchain Independence
1. Replace `bunker-cli` in root build scripts and CI workflows with `bkrc`.
2. Move `bunker-cli/` to `archive/bootstrap/stage0-rust/`.
3. Standalone distributions ship as single C source (`bkrc.c`) + runtime headers (`runtime.h`), bootstrappable anywhere via `cc -O3 bkrc.c -o bkrc`.
