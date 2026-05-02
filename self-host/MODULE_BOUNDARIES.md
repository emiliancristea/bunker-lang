# Self-Host Module Boundaries

This document is the extraction contract for the self-host compiler module split.

The production self-host compiler entrypoint remains `bkrc.bkr`, but it is now a small module-composition shell. Keep module extraction behavior-preserving and covered by the generated/stage2 compiler gates.

## Module Order

| Order | Module | Source Section | Responsibility |
|---:|---|---|---|
| 1 | `modules/constants.bkr` | Token, AST, pattern, and type constants | Shared numeric tags used by all later modules. |
| 2 | `modules/kind_model.bkr` | Kind model helpers | Centralize node/type/pattern names, AST category mapping, and pure kind predicates behind enum-ready helpers. |
| 3 | `modules/ast.bkr` | AST layout helpers | Centralize raw AST construction/access, typed AST constructor refs, read-only typed AST wrapper structs, typed AST collection refs, AST handle conversion, AST field conversion, semantic child-handle access, explicit optional-field handle names, optional AST handles, node spans, and block child iteration behind named Bunker functions. |
| 4 | `modules/lexer_result.bkr` | Lexer result helpers | Centralize lexer output table layout behind `LexerResultRef` for tokens, names, values, and strings. |
| 5 | `modules/lexer.bkr` | `LEXER` | Convert source text into token/name/value/string tables through `LexerResultRef` lexer-result helpers. |
| 6 | `modules/parser_state.bkr` | Parser state helpers | Centralize parser state layout behind `ParserStateRef`, token table access, position movement, and first-error tracking. |
| 7 | `modules/parser.bkr` | `PARSER` | Build AST nodes from lexer tables through `ParserStateRef`, typed primary/atom/postfix/operator/simple-statement/control-flow/block/param-field/item/kernel-root construction refs, typed atom/postfix/operator/pattern/type/expression/statement/block consumers, parser-side typed category span refs, and raw compatibility adapters while parser signatures remain bootstrap-compatible. |
| 8 | `modules/cgen_state.bkr` | C codegen state helpers | Centralize C codegen state layout behind `CgenStateRef`, output lines, indentation, and local/global/function/array type tables. |
| 9 | `modules/c_codegen.bkr` | `C CODE GENERATOR` | Infer enough expression types for C emission and generate C source through typed AST refs and `CgenStateRef` cgen-state helpers. |
| 10 | `modules/report_support.bkr` | Report support helpers | Centralize JSON field/string escaping, report name lookup, diagnostic state, and small vector helpers shared by self-host reports. |
| 11 | `modules/ast_report.bkr` | Self-host AST report | Produce `BUNKER_AST_JSON`, complete-tree serialization, and AST report summary helpers. |
| 12 | `modules/symbol_table.bkr` | Self-host symbol table report | Produce `BUNKER_SYMBOL_TABLE_JSON` declaration/reference tables from typed AST refs over the bootstrap AST. |
| 13 | `modules/type_graph.bkr` | Bootstrap type graph report | Produce `BUNKER_TYPE_GRAPH_JSON` from typed AST refs and expose `CgenStateRef` bootstrap type-state helpers for typecheck. |
| 14 | `modules/resolver.bkr` | Bootstrap name resolver | Produce `BUNKER_RESOLVER_JSON` duplicate and unresolved symbol diagnostics from typed AST refs over the bootstrap AST. |
| 15 | `modules/typecheck.bkr` | Bootstrap typecheck report | Produce `BUNKER_TYPECHECK_JSON` expected/found semantic diagnostics from typed AST refs over the bootstrap AST and `CgenStateRef` bootstrap type-state helpers. |
| 16 | `modules/driver.bkr` | `COMPILER DRIVER` | Orchestrate lex, parse, codegen, diagnostics, capability reports, AST tree reports, type graph reports, symbol table reports, resolver reports, typecheck reports, file I/O, and process exit. |

## Export Contract

| Module | Required Exports |
|---|---|
| `modules/constants.bkr` | All `TOK_*`, `NODE_*`, `AST_*`, `PAT_*`, and `TYPE_*` constants. |
| `modules/kind_model.bkr` | `ast_node_kind_name`, `ast_type_kind_name`, `ast_pattern_kind_name`, `ast_category_name`, `ast_node_category_kind`, and pure `ast_is_*_kind` predicates. |
| `modules/ast.bkr` | `Ast*Ref` wrapper structs, typed AST collection ref structs, typed AST node/pattern builder refs, typed AST constructor refs, typed AST category-to-node upcasts, raw `ast_*` constructor adapters/accessors, AST node/type/expression/pattern handle helpers, semantic child-handle accessors, explicit optional-field handle accessors, typed AST field conversion helpers, optional AST handle helpers, source-span helpers, typed collection bridge helpers, block iteration helpers, node-level category helpers, and predicates for the current AST vector/type/pattern layout. |
| `modules/lexer_result.bkr` | `LexerResultRef`, `lexer_result_*_ref` constructors/accessors for the current lexer output table layout, and raw `lexer_result_*` compatibility adapters. |
| `modules/lexer.bkr` | `tokenize`, `tokenize_ref`, `intern_name`, character helpers needed by tokenization. |
| `modules/parser_state.bkr` | `ParserStateRef`, `parser_*_ref` state constructors/accessors/cursor/error helpers, and raw `parser_*` compatibility adapters. |
| `modules/parser.bkr` | `parse_kernel`, `parse_kernel_ref`, `parse_match_expr_ref`, `parse_atom_ref`, `parse_postfix_ref`, `parse_mul_ref`, `parse_add_ref`, `parse_shift_ref`, `parse_match_pattern_ref`, `parse_type_ref`, `parse_expr_ref`, `parse_block_ref`, `parse_*_stmt_ref`, token display helpers, grammar routines, parser diagnostic span helpers, typed AST construction for type/pattern/atom/postfix/operator/assignment/simple-statement/control-flow/block/param-field/item/kernel-root paths, typed atom/postfix/operator/pattern/type/expression/statement/block consumers, and parser-side AST span attachment through `ParserStateRef`, `AstNodeRef`, `AstTypeRef`, `AstExprRef`, `AstStmtRef`, `AstItemRef`, `AstBlockRef`, and `AstPatternRef`. |
| `modules/cgen_state.bkr` | `CgenStateRef`, `cgen_*_ref` state constructors/accessors/mutation helpers/lookups, and raw `cgen_*` compatibility adapters for C codegen state. |
| `modules/c_codegen.bkr` | `gen_c_program`, C escaping/name helpers, and typed-ref type inference/emission helpers that consume typed AST collection refs and `CgenStateRef`. |
| `modules/report_support.bkr` | `json_*`, `ast_report_name`, `resolver_state_*`, and shared diagnostic/vector helpers used by report-producing compiler phases. |
| `modules/ast_report.bkr` | `build_ast_report_comment`, `self_host_ast_json`, complete-tree `ast_report_*` serializers that consume typed AST refs and typed AST collection refs, and AST report summary/count helpers. |
| `modules/symbol_table.bkr` | `build_symbol_table_report_comment`, `self_host_symbol_table_json`, and `symbol_table_*` declaration/reference walkers that consume typed AST refs and typed AST collection refs. |
| `modules/type_graph.bkr` | `build_type_graph_report_comment`, `self_host_type_graph_json`, `type_graph_*` JSON helpers that consume typed AST refs and typed AST collection refs, and `CgenStateRef` bootstrap type-state helpers used by typecheck. |
| `modules/resolver.bkr` | `build_resolver_report_comment`, `self_host_resolver_json`, and bootstrap resolver diagnostics helpers that consume typed AST refs and typed AST collection refs. |
| `modules/typecheck.bkr` | `build_typecheck_report_comment`, `self_host_typecheck_json`, and bootstrap typecheck diagnostics helpers that consume typed AST refs, typed AST collection refs, and `CgenStateRef` type-state. |
| `modules/driver.bkr` | `compile_to_c`, `main`, self-host diagnostic JSON helpers, and self-host capability report helpers. |

## Dependency Rules

- `modules/constants.bkr` must not depend on any other self-host module.
- `modules/kind_model.bkr` may depend only on constants and string/int builtins; it must not inspect AST vectors.
- `modules/ast.bkr` may depend only on constants, kind-model helpers, and Vec builtins.
- `modules/lexer_result.bkr` may depend only on Vec builtins; direct lexer result layout indexing must stay isolated here behind `LexerResultRef`.
- `modules/lexer.bkr` may depend only on constants, lexer-result helpers, and string/Vec builtins.
- `modules/parser_state.bkr` may depend on constants, `LexerResultRef` lexer-result helpers, and lexer table shapes; direct parser state layout indexing must stay isolated here behind `ParserStateRef`.
- `modules/parser.bkr` may depend on constants, parser-state helpers, AST helpers, and lexer table shapes, but must not directly index parser state fields, directly index lexer result fields, or call C codegen.
- `modules/cgen_state.bkr` may depend on constants and string/Vec builtins; direct C codegen state layout indexing must stay isolated here behind `CgenStateRef`.
- `modules/c_codegen.bkr` may depend on constants, AST accessors, typed AST refs, typed AST collection refs, and cgen-state helpers, but must not construct AST nodes, directly index C codegen state fields, or call file I/O.
- `modules/report_support.bkr` may depend on constants, AST span/name conventions, and string/Vec builtins, but must not call lexer, parser, C codegen, or file I/O.
- `modules/ast_report.bkr` may depend on constants, AST accessors, parser token display helpers, and report-support helpers, but must not call lexer, parser entrypoints, C codegen, or file I/O.
- `modules/symbol_table.bkr` may depend on constants, AST accessors, AST report summary helpers, and report-support helpers, but must not call lexer, parser, C codegen, or file I/O.
- `modules/type_graph.bkr` may depend on constants, AST accessors, cgen-state helpers, codegen type inference helpers, and report-support helpers, but must not call lexer, parser, or file I/O.
- `modules/resolver.bkr` may depend on constants, AST accessors, and report-support helpers, but must not call lexer, parser, C codegen, or file I/O.
- `modules/typecheck.bkr` may depend on constants, AST accessors, cgen-state helpers, codegen type inference helpers, type-graph helpers, and report-support helpers, but must not call lexer, parser, or file I/O.
- `modules/driver.bkr` is the only compiler module that should call `read_file`, `write_file`, and `file_exists`.

## Q-005 Handoff

Q-005 adds import expansion for the self-host compiler entrypoint. The first behavior-preserving split should keep the same public entry points, fixture set, generated C runtime include pattern, and stage1/stage2 CI gates.
