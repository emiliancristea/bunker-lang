# Contributing to Bunker Language

Thank you for your interest in contributing to Bunker! This document provides guidelines for contributing to the 100% self-hosted Bunker codebase.

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/bunker-lang.git`
3. Create a branch: `git checkout -b feature/your-feature-name`
4. Make your changes in `self-host/modules/` or `tests/`
5. Run tests: `./run_tests.ps1`
6. Commit: `git commit -m "Add your feature"`
7. Push: `git push origin feature/your-feature-name`
8. Open a Pull Request

## Development Setup

Bunker is 100% self-hosted in pure Bunker with zero external runtime dependencies. No Rust, Cargo, Node, or Python is required.

### Prerequisites
- A standard C11 compiler for bootstrapping:
  - **Linux / macOS**: GCC or Clang (`cc`, `gcc`, or `clang`)
  - **Windows**: MSVC (`cl.exe`), GCC (MinGW), or Clang

### Building the Native Compiler

To bootstrap the native compiler binary (`bkrc` / `bkrc.exe`) from the canonical C11 seed:

```bash
# POSIX (Linux, macOS)
bash bootstrap/build.sh

# Windows (Command Prompt or PowerShell)
bootstrap\build.bat
```

### Running Tests

```powershell
# Run full 320-test automated validation suite (Windows / PowerShell)
$env:GITHUB_ACTIONS = "true"
.\run_tests.ps1 -Verbose
```

```bash
# Check or run specific tests using bkrc directly
./bkrc check tests/01_basic_math.bkr
./bkrc run tests/01_basic_math.bkr
```

## Compiler Architecture & Project Structure

The entire production compiler is written in pure Bunker under `self-host/`:

| Module | Purpose |
|--------|---------|
| `self-host/bkrc.bkr` | Main compiler driver entry point |
| `self-host/modules/driver.bkr` | CLI arguments, subcommands (`check`, `compile`, `run`, `capability`, `parse`), driver pipeline |
| `self-host/modules/lexer.bkr` | Tokenizer, scan loops, token kind classifications |
| `self-host/modules/parser.bkr` | Recursive descent parser emitting typed AST records |
| `self-host/modules/ast.bkr` | AST record types, spans, node list abstractions |
| `self-host/modules/typecheck.bkr` | Semantic analyzer, type checking, inference, and error reporting |
| `self-host/modules/resolver.bkr` | Symbol resolution, scope tables, import path directory handling |
| `self-host/modules/c_codegen.bkr` | C11 emission & runtime ABI mapping |
| `self-host/modules/shell.bkr` | Shell actor runtime declarations, state scheduling, message channels |
| `self-host/modules/view.bkr` | View UI declarative trees and reactive bindings |
| `self-host/modules/verify.bkr` | Linear arithmetic contract solver and pre/postcondition verification |
| `bootstrap/` | Canonical C11 bootstrap compiler package and zero-diff fixpoint verification |
| `tests/` | Golden acceptance test suite |

## Modifying the Compiler (Self-Host Bootstrap Cycle)

When modifying compiler logic in `self-host/modules/*.bkr`:

1. **Implement changes** in the appropriate `self-host/modules/*.bkr` file.
2. **Recompile Stage 1**:
   ```bash
   ./bkrc compile self-host/bkrc.bkr -o bootstrap/bkrc-stage1.c
   ```
3. **Rebuild the compiler**:
   ```bash
   # POSIX:
   bash bootstrap/build.sh
   # Windows:
   bootstrap\build.bat
   ```
4. **Recompile Stage 2 (Fixpoint Verification)**:
   ```bash
   ./bkrc compile self-host/bkrc.bkr -o bootstrap/bkrc-stage2.c
   ```
5. **Verify zero-diff fixpoint**:
   ```bash
   diff -u bootstrap/bkrc-stage1.c bootstrap/bkrc-stage2.c
   ```
6. **Update checksums**:
   ```bash
   # POSIX:
   cd bootstrap && sha256sum bkrc-stage1.c bkrc-stage2.c runtime.h > SHA256SUMS
   # Windows (PowerShell):
   cd bootstrap; (Get-FileHash bkrc-stage1.c, bkrc-stage2.c, runtime.h -Algorithm SHA256) | ForEach-Object { "$($_.Hash.ToLower())  $($_.Path | Split-Path -Leaf)" } | Out-File -Encoding ascii SHA256SUMS
   ```
7. **Run tests**:
   Ensure all 320 tests pass cleanly with `./run_tests.ps1`.

## Code Style & Invariants

- **Pure LF Line Endings**: All repository files must use UNIX LF (`\n`, `0x0A`) line endings. Never commit CRLF.
- **Pure Bunker**: All compiler logic belongs in `self-host/modules/`.
- **Arena Memory**: Respect arena boundaries and move semantics; use `copy` only when explicit duplication is required.
- **Typed APIs**: Use enum-backed kinds (`NodeKind`, `TokenKind`, `PatternKind`, `TypeKind`) rather than raw magic integers.

## Commit Message Format

```
<type>: <short description>

<optional longer description>
```

Types:
- `feat`: New language or compiler feature
- `fix`: Bug fix
- `docs`: Documentation
- `refactor`: Code refactoring without behavior changes
- `test`: Adding or updating test cases
- `chore`: Maintenance, CI, or toolchain tasks

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
