# Self-Host Bootstrap Subset

The authoritative gate is the GitHub Actions `self-host-smoke` job. Local builds are intentionally avoided for this workflow.

## Current Stage1/Stage2 Fixture Families
- Basic arithmetic and branching
- Range `for`, `while`, `loop`, `break`, and `continue`
- Type casts, constants, early returns, recursion, and nested calls
- Strings, string concatenation, and `strlen`/`len`
- Bitwise operators, modulo, unary negation, comparisons, bool logic, and ternary expressions
- Fixed arrays, indexing, structs, struct literals, and field access
- `match` expressions with literal, wildcard, binding, `Some`, and `None` patterns
- Packed `Option<i32>`/`Option<i64>` values via `Some(value)` and `None`
- Runtime `Result<T,E>` handles via `result_ok`, `result_err`, status checks, tag/value access, and unwrap helpers
- Self-compilation from stage1 `bkrc` to stage2 `bkrc2`

## Bootstrap Representation Notes
- Generic handles such as `Vec<T>`, `Option<T>`, and `Result<T,E>` currently lower to integer handles in the self-host compiler.
- `Option` is represented as a packed integer: `None = 0`, `Some(v) = (v << 1) | 1`.
- `Result` is represented as a runtime handle with tag `0 = Ok`, tag `1 = Err`, and a raw integer payload.
- Match expressions lower to scoped C expression blocks so they can be used in `let`, `return`, and nested expressions.
