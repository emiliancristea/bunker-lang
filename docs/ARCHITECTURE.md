# Architecture

> **See also:**
> - [SPECIFICATION.md](SPECIFICATION.md) - The Definitive AI-Native Systems Programming Language Specification
> - [TECHNICAL_SPEC.md](TECHNICAL_SPEC.md) - Complete Technical Specification covering grammar-constrained decoding, type systems, ownership models, contracts, and agent runtime
> - [IMPLEMENTATION_TRACKER.md](IMPLEMENTATION_TRACKER.md) - Authoritative production/self-hosting backlog and completion gates
> - [BOOTSTRAP.md](BOOTSTRAP.md) - Standalone C11 bootstrap compiler package and zero-dependency build guide

The Bunker compiler is 100% self-hosted, written in pure Bunker (`self-host/`), and bootstraps from reproducible, portable C11 seeds (`bootstrap/`) with zero external programming language or package manager dependencies.

---

## 1. Compiler Pipeline (Pure Bunker)

The self-hosted compiler driver (`self-host/bkrc.bkr` and `self-host/modules/driver.bkr`) coordinates the compilation passes in modular dependency order:

1. **Introspection & Capability**:
   - `self_host_capability_json()` exports structured compiler capabilities (`bunker.self_host.capability.v1`) for AI agents and tooling.
2. **Import Resolution & Graph**:
   - `modules/driver.bkr` performs normalized relative import path resolution, cycle path detection, and duplicate suppression (`bunker.self_host.import_graph.v1`).
3. **Lexer & Tokenization**:
   - `modules/lexer.bkr` tokenizes source code into typed tokens (`enum TokenKind`) using `modules/lexer_result.bkr`.
4. **Parser & AST**:
   - `modules/parser.bkr` implements an AI-friendly LL(1) recursive descent parser creating typed AST nodes (`enum NodeKind`, `struct AstSpan`, `struct AstPattern`, `struct AstType`, etc.) from `modules/ast.bkr`.
5. **Symbol Table & Name Resolution**:
   - `modules/symbol_table.bkr` and `modules/resolver.bkr` build interned scope tables with visibility boundaries and cross-file definition tracking (`bunker.self_host.resolver.v1`).
6. **Type Checking & Semantic Validation**:
   - `modules/typecheck.bkr` validates declared annotations, return values, loop-control flow, unreachable code, and match exhaustiveness (`bunker.self_host.typecheck.v1`).
7. **Code Generation**:
   - `modules/c_codegen.bkr` emits clean, portable C11 code targeting the unified C runtime ABI (`bootstrap/runtime.h`).

---

## 2. Standalone Bootstrap Architecture

To break circular compiler dependencies without requiring Rust, Python, or external toolchains:

```
                    ┌───────────────────────────┐
                    │  bootstrap/bkrc-stage1.c  │ (Portable C11 Seed)
                    └─────────────┬─────────────┘
                                  │
                       Standard C Compiler
                       (GCC, Clang, MSVC)
                                  │
                                  ▼
                        ┌──────────────────┐
                        │     bkrc.exe     │ (Stage 1 Binary)
                        └─────────┬────────┘
                                  │
                       Compiles self-host/bkrc.bkr
                                  │
                                  ▼
                    ┌───────────────────────────┐
                    │  bootstrap/bkrc-stage2.c  │ (Stage 2 Seed)
                    └─────────────┬─────────────┘
                                  │
                   Zero-Diff Fixpoint Comparison
               (bkrc-stage1.c == bkrc-stage2.c)
```

- **Zero Third-Party Languages**: The bootstrap process requires only standard platform C compilers (`gcc`, `clang`, or MSVC `cl.exe`).
- **Fixpoint Proof**: Compiling `self-host/bkrc.bkr` with Stage 1 emits Stage 2 with identical byte-for-byte SHA-256 hashes (`bootstrap/SHA256SUMS`).

---

## 3. Runtime Layer

The runtime (`bootstrap/runtime.h`) implements the core Bunker execution model:

- **Arena Memory Allocator**: Watermark allocation pattern with deterministic O(1) scope-based reset and zero GC overhead.
- **Actor Model (Shell)**: Shared-nothing message-passing runtime with deterministic FIFO mailboxes (`bkr_actor_send`, `bkr_actor_pop`).
- **Declarative UI (View)**: Composable component trees with reactive state projections bound to Shell actors.
- **Contract Verification Engine**: Function contract pre/post-conditions (`#[requires]`, `#[ensures]`) with symbolic execution and counterexample synthesis.

---

## 4. Test Suite & Quality Gates

The test suite covers 320 acceptance tests executed via `run_tests.ps1`:

- **JIT / AOT Validations**: Math, memory, control flow, ADTs, collections, file I/O.
- **Negative Tests (`*_BAD`)**: Comprehensive diagnostic rejection for syntax, typing, exhaustiveness, and visibility errors.
- **Shell Actor Tests**: Concurrent ping-pong, state isolation, message queues.
- **View Layer Tests**: Declarative tree layouts, reactive bindings, click dispatch.
- **Verification Tests**: Pre/post-condition proofs and counterexample checks.
- **Self-Host Tests**: Multi-file compilation, CLI capability introspection, AST JSON emission, type graph, and resolver verification.

---

## 5. Historical Stage 0 Prototype

The original Rust-based bootstrap prototype has been permanently relocated to `archive/bootstrap/stage0-rust/`. It serves strictly as a historical reference and is excluded from active CI pipelines.
