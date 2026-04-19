# Self-Host Module Boundaries

This document is the extraction contract for the self-host compiler module split.

The production self-host compiler entrypoint remains `bkrc.bkr`, but it is now a small module-composition shell. Keep module extraction behavior-preserving and covered by the generated/stage2 compiler gates.

## Module Order

| Order | Module | Source Section | Responsibility |
|---:|---|---|---|
| 1 | `modules/constants.bkr` | Token, AST, pattern, and type constants | Shared numeric tags used by all later modules. |
| 2 | `modules/ast.bkr` | AST layout helpers | Centralize raw AST construction/access behind named Bunker functions. |
| 3 | `modules/lexer.bkr` | `LEXER` | Convert source text into token/name/value/string tables. |
| 4 | `modules/parser.bkr` | `PARSER` | Build raw `Vec<i64>` AST nodes from lexer tables through AST helpers. |
| 5 | `modules/c_codegen.bkr` | `C CODE GENERATOR` | Infer enough expression types for C emission and generate C source. |
| 6 | `modules/driver.bkr` | `COMPILER DRIVER` | Orchestrate lex, parse, codegen, diagnostics, file I/O, and process exit. |

## Export Contract

| Module | Required Exports |
|---|---|
| `modules/constants.bkr` | All `TOK_*`, `NODE_*`, `PAT_*`, and `TYPE_*` constants. |
| `modules/ast.bkr` | `ast_*` constructors/accessors for the current AST vector/type/pattern layout. |
| `modules/lexer.bkr` | `tokenize`, `intern_name`, character helpers needed by tokenization. |
| `modules/parser.bkr` | `parser_new`, parser accessors, `parse_kernel`, parse error accessors. |
| `modules/c_codegen.bkr` | `gen_c_program`, C escaping/name helpers, type inference helpers used by codegen. |
| `modules/driver.bkr` | `compile_to_c`, `main`. |

## Dependency Rules

- `modules/constants.bkr` must not depend on any other self-host module.
- `modules/ast.bkr` may depend only on constants and Vec builtins.
- `modules/lexer.bkr` may depend only on constants and string/Vec builtins.
- `modules/parser.bkr` may depend on constants, AST helpers, and lexer table shapes, but must not call C codegen.
- `modules/c_codegen.bkr` may depend on constants and AST accessors, but must not construct AST nodes or call file I/O.
- `modules/driver.bkr` is the only compiler module that should call `read_file`, `write_file`, and `file_exists`.

## Q-005 Handoff

Q-005 adds import expansion for the self-host compiler entrypoint. The first behavior-preserving split should keep the same public entry points, fixture set, generated C runtime include pattern, and stage1/stage2 CI gates.
