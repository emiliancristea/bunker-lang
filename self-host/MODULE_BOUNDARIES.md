# Self-Host Module Boundaries

This document is the extraction contract for splitting `self-host/bkrc.bkr` once multi-file compilation exists.

The production self-host compiler remains `bkrc.bkr` until Q-005 adds imports. Do not move behavior out of the monolith before imports are supported; keep changes mirrored against these boundaries.

## Module Order

| Order | Future Module | Current Section | Responsibility |
|---:|---|---|---|
| 1 | `constants.bkr` | Token, AST, pattern, and type constants | Shared numeric tags used by all later modules. |
| 2 | `lexer.bkr` | `LEXER` | Convert source text into token/name/value/string tables. |
| 3 | `parser.bkr` | `PARSER` | Build raw `Vec<i64>` AST nodes from lexer tables. |
| 4 | `c_codegen.bkr` | `C CODE GENERATOR` | Infer enough expression types for C emission and generate C source. |
| 5 | `driver.bkr` | `COMPILER DRIVER` | Orchestrate lex, parse, codegen, diagnostics, file I/O, and process exit. |

## Export Contract

| Future Module | Required Exports |
|---|---|
| `constants.bkr` | All `TOK_*`, `NODE_*`, `PAT_*`, and `TYPE_*` constants. |
| `lexer.bkr` | `tokenize`, `intern_name`, character helpers needed by tokenization. |
| `parser.bkr` | `parser_new`, parser accessors, `parse_kernel`, parse error accessors. |
| `c_codegen.bkr` | `gen_c_program`, C escaping/name helpers, type inference helpers used by codegen. |
| `driver.bkr` | `compile_to_c`, `main`. |

## Dependency Rules

- `constants.bkr` must not depend on any other self-host module.
- `lexer.bkr` may depend only on constants and string/Vec builtins.
- `parser.bkr` may depend on constants and lexer table shapes, but must not call C codegen.
- `c_codegen.bkr` may depend on constants and parser AST shapes, but must not call file I/O.
- `driver.bkr` is the only future module that should call `read_file`, `write_file`, and `file_exists`.

## Q-005 Handoff

Q-005 should add import resolution and then compile a root driver plus the modules above. The first behavior-preserving split should keep the same public entry points, fixture set, generated C runtime include pattern, and stage1/stage2 CI gates.
