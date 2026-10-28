# Self-Host Bootstrap Subset

The authoritative gate is the GitHub Actions `self-host-smoke` job. Local builds are intentionally avoided for this workflow.

## Current Stage1/Stage2 Fixture Families
- Basic arithmetic and branching
- Range `for`, `while`, `loop`, `break`, and `continue`
- Type casts, constants, early returns, recursion, and nested calls
- Strings, string concatenation, `strlen`/`len`, and core string helpers (`char_at`, `char_code_at`, `substring`, `contains`, `starts_with`, `ends_with`, `trim`, `parse_int`, `int_to_string`)
- Bitwise operators, modulo, unary negation, comparisons, bool logic, and ternary expressions
- Fixed arrays, indexing, structs, struct literals, and field access
- Arena-behavior struct/control-flow fixtures that fit the bootstrap subset (`63`, `64`, `65`)
- Runtime `Vec<T>` handles via `vec_new`, `vec_push`, `vec_get`, `vec_set`, `vec_pop`, and `vec_len`
- Runtime `HashMap<i32,V>` handles via insert/get/contains/remove/keys helpers
- File I/O helpers via `read_file`, `write_file`, and `file_exists`
- Enums with single- and multi-field payloads (`Enum.Variant(expr)` and `Enum.Variant(a, b)`)
- Pointer-safe 64-bit boxed enum payloads (`BkrEnumBox`, `bkr_enum_payload1`/`2`, `bkr_enum_tag`, `bkr_enum_field`) for string and heap payloads
- Canonical `Option<T>` and `Result<T, E>` sum types with unified qualified (`Option.Some`, `Option.None`, `Result.Ok`, `Result.Err`) and unqualified (`Some`, `None`, `Ok`, `Err`) pattern matching
- Exhaustiveness checking for boolean, unit-enum, payload-enum, `Option`, and `Result` matches
- Match guards (`pattern if condition => body`) with scoped bindings and fallthrough on false guard evaluation
- Process argument ingestion via `args_count()` and `arg_at(index)` builtins
- Direct standalone CLI execution (`bkrc <input.bkr> -o <output.c>`) without temporary file shims
- Self-compilation from stage1 `bkrc` to stage2 `bkrc2` via command-line arguments
- First-class unit type and value `()` (`fn f() -> ()`, `return ()`, `let u: () = ()`, `Result<(), E>`, `Option<()>`)
- Tuple types, literals, numeric indexing, and pattern matching (`(T1, T2)`, `(a, b)`, `t.0`, `t.1`, `match t { (x, y) => ... }`) backed by arena-allocated uniform 64-bit records (`bkr_tuple2`, `bkr_tuple3`, `bkr_tuple_get`)
- Struct destructuring patterns in match expressions (`Point { x, y }` and `Point { x: a, y: b }`)
- Defer statement lowering with LIFO block execution before returns and scope exits (`defer log(...)`)
- Fixed-array repeat literal syntax (`[elem; count]` e.g. `[0; 1000]`)
- Arbitrary nested postfix expressions including nested array-field assignment (`buf.data[0] = 42`)
- Logging runtime primitive `log(...)` lowering to `bkr_log` in `runtime.h`

## Bootstrap Representation Notes
- Generic handles such as `Vec<T>`, `Option<T>`, and `Result<T,E>` currently lower to integer handles in the self-host compiler.
- `Option` is represented as a packed integer: `None = 0`, `Some(v) = (v << 1) | 1`.
- `Result` is represented as a runtime handle with tag `0 = Ok`, tag `1 = Err`, and a 64-bit payload.
- `HashMap` currently supports integer keys in the self-host C runtime; string values are stored as raw pointer payloads.
- Match expressions lower to scoped C expression blocks (`({ ... })`) with `_matched` flags and per-arm isolated bindings so they can be used in `let`, `return`, and nested expressions with guard fallthrough.
