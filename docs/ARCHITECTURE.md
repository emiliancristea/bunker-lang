# Architecture

> **See also:**
> - [SPECIFICATION.md](SPECIFICATION.md) - The Definitive AI-Native Systems Programming Language Specification
> - [TECHNICAL_SPEC.md](TECHNICAL_SPEC.md) - Complete Technical Specification covering grammar-constrained decoding, type systems, ownership models, contracts, and agent runtime

This repo currently contains a single Rust crate (`bunker-cli`) implementing the compiler front-end plus a bootstrap runtime (`run`) for Kernel/Shell/View.

## Compiler Pipeline (Current)

1. **Parse**: Pest PEG grammar (`bunker-cli/src/grammar/bunker.pest`) parses `.bkr` into a parse tree.
2. **AST build**: `bunker-cli/src/ast_builder.rs` lowers the parse tree into `bunker-cli/src/ast.rs`.
3. **Type checking**: `bunker-cli/src/typeck.rs` fully validates Kernel blocks and performs lighter Shell/View validation.
4. **Code generation**:
   - Kernel codegen via Cranelift (`bunker-cli/src/codegen.rs`) emits an object file.
   - Shell codegen (`bunker-cli/src/shell_codegen.rs`) emits VM bytecode structures used by the runtime.
5. **Execution (bootstrap)**:
   - Kernel JIT runner for `fn main() -> i32` (`bunker-cli/src/jit.rs`).
   - Shell VM (`bunker-cli/src/shell_runtime.rs`) and View runtime (`bunker-cli/src/view_runtime.rs`).
6. **CLI**: `bunker-cli/src/main.rs` wires `check`, `parse`, `build`, `run`, `self-host-check`, and `self-host-compile`. Local policy allows only `check`, `parse`, and `self-host-check`; `build`, `run`, and `self-host-compile` are CI-only.

## Compiler Pipeline (Intended Evolution)

To scale features cleanly, the next architectural step is usually to introduce explicit intermediate forms:

- **AST**: faithful to syntax (already exists).
- **HIR**: name-resolved, desugared, validation-ready (suggested next).
- **Typed IR**: makes codegen and verification easier (Kernel vs Shell vs View can lower to different IRs).

This enables better diagnostics, cross-layer checking (`use` calls, view bindings), and Z3 encoding from a normalized Kernel IR.

## Runtime (Exists Today, Still Growing)

To run Shell and View, the project includes a small runtime implementation (Rust):

- **Messaging**: queues, scheduling policy, deterministic stepping for tests.
- **State storage**: agent state layout + accessors for view bindings.
- **Kernel↔Shell bridge**: call convention for invoking compiled Kernel functions.
- **View backend(s)**: text backend + Windows `#[target(graphics)]` backend (Win32) today.

## Testing Strategy (Suggested)

- Keep `tests/*.bkr` as language-level acceptance tests.
- Add compiler-level tests only where valuable (parser/type checker/codegen units).
- Add a `run`-based CI job once a minimal runtime exists (start with Kernel-only).

## Current Test Coverage

- **Total Tests:** 98 passing
- **JIT-Enabled:** 61 tests (validated by `run_tests.ps1`)
- **Negative Tests:** 18 tests (type errors, move errors)
- **Shell-Bearing Files:** 14 tests
- **View-Bearing Files:** 7 tests

## Implementation Status

See the Implementation Status Tracking sections in:
- [SPECIFICATION.md](SPECIFICATION.md#implementation-status-tracking)
- [TECHNICAL_SPEC.md](TECHNICAL_SPEC.md#implementation-status-tracking)

These sections provide detailed checklists tracking progress against each specification area.

> **Tip:** Run `/check-update-status` to get a full implementation status report with specification compliance analysis.
