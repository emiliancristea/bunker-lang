# Self-Host Bootstrap Subset

The authoritative gate is the GitHub Actions `self-host-smoke` job. Local builds are intentionally avoided for this workflow.

## Current Stage1/Stage2 Fixture Families
- Basic arithmetic and branching
- Range `for`, `while`, `loop`, `break`, and `continue`
- Type casts, constants, early returns, recursion, and nested calls
- Strings, string concatenation, `strlen`/`len`, and core string helpers (`char_at`, `char_code_at`, `substring`, `contains`, `starts_with`, `ends_with`, `trim`, `parse_int`, `int_to_string`)
- Bitwise operators, modulo, unary negation, comparisons, bool logic, and ternary expressions
- Fixed arrays, indexing, structs, struct literals, and field access
- Runtime `Vec<T>` handles via `vec_new`, `vec_push`, `vec_get`, `vec_set`, `vec_pop`, and `vec_len`
- Runtime `HashMap<i32,V>` handles via insert/get/contains/remove/keys helpers
- File I/O helpers via `read_file`, `write_file`, and `file_exists`
- `match` expressions with literal, wildcard, binding, `Some`, and `None` patterns
- Packed `Option<i32>`/`Option<i64>` values via `Some(value)` and `None`
- Runtime `Result<T,E>` handles via `result_ok`, `result_err`, status checks, tag/value access, and unwrap helpers
- Self-compilation from stage1 `bkrc` to stage2 `bkrc2`

## Bootstrap Representation Notes
- Generic handles such as `Vec<T>`, `Option<T>`, and `Result<T,E>` currently lower to integer handles in the self-host compiler.
- `Option` is represented as a packed integer: `None = 0`, `Some(v) = (v << 1) | 1`.
- `Result` is represented as a runtime handle with tag `0 = Ok`, tag `1 = Err`, and a raw integer payload.
- `HashMap` currently supports integer keys in the self-host C runtime; string values are stored as raw pointer payloads.
- Match expressions lower to scoped C expression blocks so they can be used in `let`, `return`, and nested expressions.
