# Contributing to Bunker Language

Thank you for your interest in contributing to Bunker! This document provides guidelines for contributing.

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/bunker-lang.git`
3. Create a branch: `git checkout -b feature/your-feature-name`
4. Make your changes
5. Run tests: `cargo test` (in bunker-cli directory)
6. Commit: `git commit -m "Add your feature"`
7. Push: `git push origin feature/your-feature-name`
8. Open a Pull Request

## Development Setup

### Prerequisites
- Rust 1.70 or later
- Cargo

### Building
```bash
cd bunker-cli
cargo build
```

### Running Tests
```bash
# Run all Rust tests
cargo test

# Test compilation of all .bkr files
cd ..
for f in tests/*.bkr; do
    ./bunker-cli/target/debug/bunker-cli check "$f"
done
```

## Code Style

- Follow standard Rust formatting (`cargo fmt`)
- Run clippy: `cargo clippy`
- Keep functions focused and small
- Add comments for complex logic
- Use meaningful variable names

## Project Structure

| Directory | Purpose |
|-----------|---------|
| `bunker-cli/src/grammar/` | PEG grammar (bunker.pest) |
| `bunker-cli/src/ast.rs` | AST type definitions |
| `bunker-cli/src/ast_builder.rs` | Parse tree to AST conversion |
| `bunker-cli/src/typeck.rs` | Type checking |
| `bunker-cli/src/codegen.rs` | Cranelift code generation |
| `bunker-cli/src/shell_codegen.rs` | Shell layer compilation |
| `tests/` | Golden test files |

## Areas for Contribution

### High Priority
- Z3 verification integration
- View layer code generation
- Runtime library implementation
- Error message improvements

### Medium Priority
- Additional type inference
- Optimization passes
- Standard library functions
- Documentation

### Good First Issues
- Add more test cases
- Improve error messages
- Fix compiler warnings
- Add code comments

## Adding a New Feature

1. **Grammar changes**: Edit `bunker.pest`, then update `ast.rs` and `ast_builder.rs`
2. **Type checking**: Add cases to `typeck.rs`
3. **Code generation**: Update `codegen.rs` or `shell_codegen.rs`
4. **Tests**: Add a new `.bkr` file in `tests/`

## Commit Message Format

```
<type>: <short description>

<optional longer description>
```

Types:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `refactor`: Code refactoring
- `test`: Adding tests
- `chore`: Maintenance

Examples:
```
feat: add support for match expressions
fix: correct type inference for array literals
docs: update README with new examples
```

## Pull Request Process

1. Ensure all tests pass
2. Update documentation if needed
3. Add tests for new features
4. Keep PRs focused (one feature per PR)
5. Respond to review feedback

## Questions?

Open an issue with the "question" label.

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
