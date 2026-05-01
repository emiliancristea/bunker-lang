# Bunker Production Implementation Tracker

This is the authoritative implementation tracker for moving Bunker from a bootstrap language into a production language and then into full self-hosting.

Last updated: 2026-05-01

## Operating Rules

- GitHub Actions is the build and test authority.
- Do not run local builds or test suites on the workstation.
- Each implementation slice must add or extend CI coverage.
- Every production feature must have a compiler behavior, runtime behavior if needed, diagnostics, and tests.
- Self-host work should move Rust responsibilities into Bunker modules only when the Bunker subset can support that module cleanly.

## Status Legend

| Status | Meaning |
|---|---|
| DONE | Implemented and covered by CI. |
| PARTIAL | Some support exists, but not production-complete. |
| TODO | Not implemented or not usable yet. |
| BLOCKED | Requires earlier tracker items. |
| DEFER | Not required for self-hosting, but useful later. |

## Current Baseline

Current bootstrap state after the latest self-host work:

- Self-host `bkrc.bkr` can self-compile through stage1 and stage2 in GitHub Actions.
- CI gates arithmetic, functions, control flow, structs, arrays, strings, constants, recursion, bitwise ops, ternary, match, Option, Result, Vec, and HashMap fixtures through generated and stage2 compilers.
- CI compares selected self-host outputs against Rust JIT results and checks stage1/stage2 generated C determinism.
- The Rust compiler is still the production compiler and the bootstrap driver.
- The self-host compiler entrypoint is now module-composed: constants, kind model, AST helpers, lexer result helpers, lexer, parser state, parser, C codegen state, C codegen, report support, AST report, symbol table, type graph, resolver, typecheck, and driver live in imported Bunker modules.
- AST construction plus parser/codegen AST reads are centralized in Bunker helper functions, AST/tag naming and category reasoning now goes through `modules/kind_model.bkr`, typed AST collection access, optional AST handles, node/type/expression/pattern handle conversion, internal AST field conversions, semantic child-handle access, explicit handle-named optional field access, and read-only AST wrapper structs now route through AST bridge helpers; C codegen plus the AST report, symbol-table report, type-graph report, resolver report, and typecheck report passes now recursively consume typed AST refs over the bootstrap layout, with raw AST kind/predicate reads isolated to the AST boundary. Lexer result layout is centralized in `modules/lexer_result.bkr`, parser state layout is centralized in `modules/parser_state.bkr`, and C codegen state layout is centralized in `modules/cgen_state.bkr`; `LexerResultRef` wraps lexer output tables, `ParserStateRef` wraps parser cursor/error state, and `CgenStateRef` wraps mutable codegen/type-state consumers while raw state adapters remain for bootstrap compatibility. The AST, lexer result, parser state, and codegen state representations still use raw `Vec<i64>` during bootstrap.
- Self-host compiler outputs include `BUNKER_CAPABILITY_JSON`, a machine-readable capability report for agents that states supported constructs, current AI-diagnostic support, and known bootstrap limits.
- Successful self-host compiler outputs include `BUNKER_AST_JSON`, a machine-readable AST report with root/item summaries plus a complete nested AST tree for agent inspection.
- Successful self-host compiler outputs include `BUNKER_TYPE_GRAPH_JSON`, a machine-readable declaration and bootstrap-inference type graph for agent inspection.
- Successful self-host compiler outputs include `BUNKER_SYMBOL_TABLE_JSON`, a machine-readable declaration/reference table for agent inspection.
- Successful self-host compiler outputs include `BUNKER_RESOLVER_JSON`, a machine-readable bootstrap resolver report for duplicate and unresolved symbol diagnostics.
- Successful self-host compiler outputs include `BUNKER_TYPECHECK_JSON`, a machine-readable bootstrap typecheck report for annotation, return, condition, assignment, range, and direct call-argument diagnostics.
- The language is not yet production-complete.

## Critical Path

Implement in this order unless a CI failure forces a repair first.

| Order | Gate | Status | Goal |
|---:|---|---|---|
| 1 | Self-host runtime surface | PARTIAL | Finish file I/O, string methods, stdlib handles, and C runtime coverage. |
| 2 | Modules and multi-file compilation | TODO | Split Bunker compiler source into real modules. |
| 3 | Typed compiler data structures | TODO | Replace raw numeric AST nodes with Bunker structs/enums. |
| 4 | Real generics and ADTs | TODO | Replace erased handles and hardcoded Option/Result logic. |
| 5 | Production diagnostics | PARTIAL | Make compiler errors exact, structured, and AI-repairable. |
| 6 | Memory/resource model | PARTIAL | Make long-running compiler processes safe and leak-controlled. |
| 7 | Self-host module migration | TODO | Move lexer, parser, typechecker, and codegen out of Rust. |
| 8 | Rust removal gate | BLOCKED | Build Bunker compiler with Bunker compiler, with Rust only as bootstrap. |

## Immediate Implementation Queue

These are the next concrete PR-sized slices.

| ID | Status | Work | Definition Of Done |
|---|---|---|---|
| Q-001 | DONE | Add self-host coverage for file I/O fixtures. | `tests/72_file_io.bkr` compiles and runs through generated and stage2 `bkrc` in CI. |
| Q-002 | DONE | Add self-host coverage for string method fixtures. | `tests/73_string_methods.bkr` compiles and runs through generated and stage2 `bkrc` in CI. |
| Q-003 | DONE | Add self-host coverage for arena fixtures if bootstrap syntax allows it. | Arena fixture subset compiles/runs through generated and stage2 `bkrc`; `tests/02_arena_memory.bkr` blockers are logged in `self-host/bootstrap_subset.md`. |
| Q-004 | DONE | Split `self-host/bkrc.bkr` into module-ready sections without changing behavior. | Module boundary contract exists; CI still passes with generated/stage2 compiler behavior unchanged. |
| Q-005 | DONE | Add multi-file self-host compile support. | `self-host-compile` can compile a root Bunker compiler entrypoint plus imported Bunker modules in CI. |
| Q-006 | DONE | Move lexer into Bunker module. | Stage2 compiler uses `self-host/modules/lexer.bkr` through import expansion and passes current self-host smoke. |
| Q-007 | DONE | Move parser into Bunker module. | Stage2 compiler uses Bunker parser module and passes current self-host smoke. |
| Q-008 | DONE | Move C codegen into Bunker module. | Stage2 compiler uses Bunker codegen module and passes current self-host smoke. |
| Q-009 | PARTIAL | Add machine-readable self-host diagnostics. | Self-host parse/import errors plus resolver/typecheck reports emit JSON diagnostics with spans and repair hints; codegen diagnostics and a unified diagnostic envelope still need dedicated phases. |
| Q-010 | DONE | Add self-host golden output tests. | CI compares selected Rust compiler output vs self-host compiler output for stable fixtures. |
| Q-011 | DONE | Reduce `bkrc.bkr` to a module-composed entrypoint. | Entry point imports constants, lexer, parser, codegen, and driver modules; CI passes generated/stage2/golden gates. |
| Q-012 | DONE | Introduce self-host AST layout helpers. | Parser constructs AST nodes through `modules/ast.bkr`; CI passes generated/stage2/golden gates. |
| Q-013 | DONE | Route self-host parser/codegen through AST accessors. | Parser and C codegen read AST/type/pattern fields through `modules/ast.bkr`; CI passes generated/stage2/golden gates. |
| Q-014 | DONE | Isolate self-host C codegen state. | C codegen uses `modules/cgen_state.bkr` for output, indentation, local/global/function/array type tables; CI passes generated/stage2/golden gates. |
| Q-015 | DONE | Isolate self-host parser state. | Parser uses `modules/parser_state.bkr` for token tables, cursor position, and first-error tracking; CI passes generated/stage2/golden gates. |
| Q-016 | DONE | Isolate self-host lexer result layout. | Lexer constructs results through `modules/lexer_result.bkr`, and parser state reads lexer output through lexer-result helpers; CI passes generated/stage2/golden gates. |
| Q-017 | DONE | Introduce self-host AST kind/category helpers. | Node/type/pattern names, categories, predicates, and debug labels exist behind named helpers; C codegen routes repeated AST shape checks through those helpers; CI passes generated/stage2/golden gates. |
| Q-018 | DONE | Add self-host AST byte spans. | Self-host AST nodes and patterns reserve source byte start/end slots, parser construction attaches spans, block iteration is routed through AST helpers, and parse diagnostics consume parser span values; CI passes generated/stage2/golden gates. |
| Q-019 | DONE | Add self-host capability reports for agents. | Generated self-host outputs include `BUNKER_CAPABILITY_JSON` describing supported syntax, enabled diagnostic features, and known missing production features; CI checks the report on success and diagnostic outputs. |
| Q-020 | DONE | Add self-host AST summary reports for agents. | Successful generated self-host outputs include `BUNKER_AST_JSON` with root span, source size, item counts, and per-item kind/name/span metadata; CI checks stage1 and stage2 generated outputs. |
| Q-021 | DONE | Add complete nested self-host AST JSON for agents. | `BUNKER_AST_JSON` includes `complete_tree:true` plus a recursive `tree` object covering functions, params, types, blocks, statements, expressions, patterns, and match arms; CI checks direct, stage1, and stage2 generated outputs. |
| Q-022 | DONE | Add self-host type graph reports for agents. | Successful generated self-host outputs include `BUNKER_TYPE_GRAPH_JSON` with declared structs/constants/functions plus bootstrap-inferred locals and return expression types; CI checks direct, stage1, and stage2 generated outputs. |
| Q-023 | DONE | Add self-host symbol table reports for agents. | Successful generated self-host outputs include `BUNKER_SYMBOL_TABLE_JSON` with declarations, references, scopes, and spans derived from the bootstrap AST walk; CI checks direct, stage1, and stage2 generated outputs. |
| Q-024 | DONE | Add self-host resolver reports for agents. | Successful generated self-host outputs include `BUNKER_RESOLVER_JSON` with duplicate/unresolved symbol diagnostics, and CI checks both clean and intentionally broken resolver inputs. |
| Q-025 | DONE | Add self-host typecheck reports for agents. | Successful generated self-host outputs include `BUNKER_TYPECHECK_JSON` with expected/found semantic diagnostics, and CI checks both clean and intentionally broken typecheck inputs. |
| Q-026 | DONE | Extract shared self-host report support helpers. | `modules/report_support.bkr` owns JSON field/string escaping, report name lookup, diagnostic state, and shared vector helpers so resolver/typecheck report modules can be extracted from `driver.bkr` next. |
| Q-027 | DONE | Extract self-host resolver pass into its own module. | `modules/resolver.bkr` owns `BUNKER_RESOLVER_JSON`, duplicate detection, unresolved symbol diagnostics, and resolver report comment generation; `driver.bkr` only orchestrates the report. |
| Q-028 | DONE | Extract self-host type graph and typecheck passes. | `modules/type_graph.bkr` owns `BUNKER_TYPE_GRAPH_JSON` plus bootstrap type-state helpers, `modules/typecheck.bkr` owns `BUNKER_TYPECHECK_JSON`, and `driver.bkr` only orchestrates both reports. |
| Q-029 | DONE | Extract self-host AST report pass. | `modules/ast_report.bkr` owns `BUNKER_AST_JSON`, complete-tree serialization, and AST report count helpers used by later report modules; `driver.bkr` only orchestrates AST report emission. |
| Q-030 | DONE | Extract self-host symbol table pass. | `modules/symbol_table.bkr` owns `BUNKER_SYMBOL_TABLE_JSON`, declaration/reference table walking, and symbol-table report comment generation; `driver.bkr` only orchestrates symbol table report emission. |
| Q-031 | DONE | Extract enum-ready kind model helpers. | `modules/kind_model.bkr` owns node/type/pattern names, AST category mapping, and pure kind predicates so later enum-backed tags can replace bootstrap numeric constants without changing AST layout call sites. |
| Q-032 | DONE | Add typed AST collection bridge helpers. | `modules/ast.bkr` exposes item/param/field/call-arg/array-element/match-arm/struct-literal field accessors, and codegen/report/resolver/typecheck/type-graph modules use them instead of raw AST collection `vec_get` access. |
| Q-033 | DONE | Add optional AST node bridge helpers. | `modules/ast.bkr` owns optional AST sentinel helpers, and parser/codegen/report/resolver/typecheck/type-graph modules use them where `0` means an absent AST node/type/expression. |
| Q-034 | DONE | Add AST handle bridge helpers. | `modules/ast.bkr` owns node/type/expression/statement/item/block/pattern handle conversion and AST handle-list append helpers; parser/report/resolver/typecheck/type-graph/codegen modules use named helpers instead of direct AST `as i64`/`as Vec<i64>` casts. |
| Q-035 | DONE | Add internal AST field bridge helpers. | `modules/ast.bkr` owns typed field conversion helpers for node, node-list, i64-list, pattern-list, and string-list fields, and AST accessors use them instead of direct `ast_field(...) as Vec<...>` casts. |
| Q-036 | DONE | Add semantic AST child-handle accessors. | `modules/ast.bkr` exposes handle-valued accessors for expression/type child fields and report/resolver/typecheck/type-graph/codegen modules consume those handles instead of re-wrapping child nodes. |
| Q-037 | DONE | Add explicit AST optional-field handle names. | `modules/ast.bkr` exposes `*_handle` aliases for optional expression/type/block fields, and report/resolver/typecheck/type-graph/codegen modules use the explicit names instead of ambiguous `*_node`/`*_expr` accessors. |
| Q-038 | DONE | Add read-only typed AST wrapper structs. | `modules/ast.bkr` declares `AstNodeRef`, `AstTypeRef`, `AstExprRef`, `AstStmtRef`, `AstItemRef`, `AstBlockRef`, and `AstPatternRef` wrappers with handle conversion and read-only kind/span helpers. |
| Q-039 | DONE | Route AST report recursion through typed AST refs. | `modules/ast_report.bkr` serializes complete-tree nodes and patterns through `AstNodeRef`/`AstPatternRef` entry points while preserving the existing JSON contract. |
| Q-040 | DONE | Route symbol table recursion through typed AST refs. | `modules/symbol_table.bkr` walks declaration/reference nodes, expressions, blocks, statements, items, patterns, and type references through `Ast*Ref` entry points while preserving the existing JSON contract. |
| Q-041 | DONE | Route type graph recursion through typed AST refs. | `modules/type_graph.bkr` walks declared types, inferred expression types, structs, constants, functions, locals, and returns through `Ast*Ref` entry points while preserving the existing JSON contract and raw helper adapters used by typecheck. |
| Q-042 | DONE | Route resolver diagnostics through typed AST refs. | `modules/resolver.bkr` walks duplicate/unresolved diagnostics, declarations, expressions, statements, blocks, functions, structs, type references, and pattern bindings through `Ast*Ref` entry points while preserving the existing JSON contract. |
| Q-043 | DONE | Route typecheck diagnostics through typed AST refs. | `modules/typecheck.bkr` walks annotation, return, condition, assignment, range, call-argument, block, function, and const diagnostics through `Ast*Ref` entry points while preserving `BUNKER_TYPECHECK_JSON`. |
| Q-044 | DONE | Route C codegen through typed AST refs. | `modules/c_codegen.bkr` walks type conversion, expression inference, expression emission, statement/block emission, structs, constants, functions, and kernel codegen through `Ast*Ref` entry points while preserving generated C behavior. |
| Q-045 | DONE | Remove residual raw AST predicate reads outside the AST boundary. | AST report summaries, symbol-table match-arm walks, and resolver match-arm walks now use typed refs for item kind and block/body dispatch so raw `ast_kind`, `ast_optional_node`, and `ast_is_*` usage is isolated to AST/kind helpers. |
| Q-046 | DONE | Add typed codegen state refs. | `modules/cgen_state.bkr` exposes `CgenStateRef` over the bootstrap `Vec<i64>` codegen state, and C codegen/type-graph/typecheck consumers route mutable type-state through ref helpers while preserving raw adapters. |
| Q-047 | DONE | Add typed parser state refs. | `modules/parser_state.bkr` exposes `ParserStateRef` over the bootstrap parser state, and parser/driver paths route cursor, token-table, and parse-error access through ref helpers while preserving raw adapters. |
| Q-048 | DONE | Add typed lexer result refs. | `modules/lexer_result.bkr` exposes `LexerResultRef` over bootstrap lexer output tables, `tokenize_ref` returns typed lexer results, and parser-state/driver paths consume ref helpers while preserving raw adapters. |

## Language Core

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| L-001 | TODO | P0 | Real module/import system. | `import` resolves Bunker files with stable module paths, duplicate handling, and CI fixtures. |
| L-002 | TODO | P0 | Multi-file compilation. | Compiler accepts a root file and compiles/imports dependency files deterministically. |
| L-003 | TODO | P1 | Public/private visibility. | Symbols can be exported or hidden; invalid access produces diagnostics. |
| L-004 | TODO | P1 | Namespaces/packages. | Package/module names avoid global collisions. |
| L-005 | TODO | P1 | Stable grammar versioning. | Source declares or infers language version; parser behavior is reproducible. |
| L-006 | PARTIAL | P1 | Full expression-oriented blocks. | Blocks can yield typed values consistently outside match arms. |
| L-007 | PARTIAL | P1 | Statement/expression consistency. | All expression and statement forms have precise grammar and type rules. |
| L-008 | TODO | P1 | Mutable vs immutable binding rules. | Assignments to immutable bindings are rejected everywhere. |
| L-009 | PARTIAL | P2 | Constants across modules. | Constants resolve across imported modules and are typechecked. |
| L-010 | PARTIAL | P2 | Compile-time evaluation. | Comptime works beyond simple current cases with diagnostics and limits. |
| L-011 | PARTIAL | P2 | Attribute semantics. | Parsed attributes are enforced consistently or rejected when unsupported. |
| L-012 | TODO | P3 | Documentation comments. | Doc comments are parsed and exposed to docs/LSP tooling. |

## Type System

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| T-001 | TODO | P0 | Real generics. | Generic types are represented in AST/typechecker, not erased handles. |
| T-002 | TODO | P0 | Generic functions. | Functions can declare type parameters and instantiate safely. |
| T-003 | TODO | P0 | Generic structs. | Structs can be parameterized and monomorphized or represented safely. |
| T-004 | TODO | P1 | Generic constraints. | Generic operations require explicit trait/interface bounds. |
| T-005 | TODO | P1 | Type aliases. | Aliases preserve diagnostics and compile to the same representation. |
| T-006 | PARTIAL | P0 | Local type inference. | Let bindings infer robustly for all supported expressions. |
| T-007 | PARTIAL | P0 | Call-result inference. | Builtins and user functions propagate exact result types. |
| T-008 | TODO | P0 | Inference for `None`, empty arrays, Vec, HashMap, Ok, Err. | Ambiguous values infer from annotation/context or produce precise errors. |
| T-009 | TODO | P0 | User-defined enums/sum types. | Users can define enum variants with payloads. |
| T-010 | TODO | P0 | Exhaustive match checking. | Non-exhaustive matches are rejected with missing cases. |
| T-011 | PARTIAL | P0 | Pattern type checking. | Match patterns are checked against scrutinee type in Rust and self-host paths. |
| T-012 | TODO | P1 | Destructuring patterns. | Struct/tuple/enum destructuring works with bound names. |
| T-013 | TODO | P1 | Nested patterns. | Nested enum/struct patterns typecheck and bind correctly. |
| T-014 | TODO | P1 | Match guards. | `pattern if condition` works with scoped bindings. |
| T-015 | TODO | P1 | Tuple types. | Tuples parse, typecheck, codegen, and destructure. |
| T-016 | TODO | P1 | Unit type. | `()` has consistent syntax and return semantics. |
| T-017 | TODO | P1 | Never/bottom type. | Diverging expressions typecheck in all contexts. |
| T-018 | TODO | P2 | Function types. | Functions can be values when needed for higher-order support. |
| T-019 | TODO | P0 | Trait/interface system. | Shared behavior is expressed without inheritance. |
| T-020 | TODO | P1 | Method resolution. | `value.method(args)` resolves with clear rules. |
| T-021 | TODO | P2 | Operator overloading policy. | Either explicitly supported via traits or rejected with diagnostics. |
| T-022 | PARTIAL | P1 | Numeric promotion rules. | All numeric conversions are specified and tested. |
| T-023 | PARTIAL | P1 | Cast safety rules. | Safe/unsafe casts are documented, checked, and diagnosed. |
| T-024 | PARTIAL | P0 | Type diagnostics. | Self-host generated outputs include `BUNKER_TYPECHECK_JSON` expected/found type diagnostics with spans and repair hints for bootstrap annotation, return, condition, assignment, range, and direct call-argument checks; final gate requires origin tracking and a real typechecker across Rust and self-host modes. |

## Data Model And Standard Types

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| D-001 | PARTIAL | P0 | Real `Option<T>`. | Implemented as an ADT or typed runtime representation, not hardcoded compiler cases. |
| D-002 | PARTIAL | P0 | Real `Result<T,E>`. | Implemented as ADT/runtime type with typed Ok/Err payloads. |
| D-003 | TODO | P0 | User-defined ADTs. | Option/Result can be expressed in Bunker source. |
| D-004 | TODO | P1 | Struct methods. | Methods are declared and called with receiver semantics. |
| D-005 | TODO | P2 | Struct update syntax. | Copy/update syntax works or is intentionally rejected. |
| D-006 | TODO | P2 | Tuple structs. | Tuple-like structs parse and typecheck. |
| D-007 | PARTIAL | P1 | Nested structs/arrays. | Deeply nested values codegen and typecheck robustly. |
| D-008 | TODO | P0 | Slices. | Borrowed views into arrays/Vec have bounds-safe operations. |
| D-009 | PARTIAL | P0 | Typed Vec. | `Vec<T>` preserves element type through all operations. |
| D-010 | PARTIAL | P0 | Typed HashMap. | `HashMap<K,V>` preserves key/value types beyond integer-key bootstrap. |
| D-011 | PARTIAL | P0 | String ownership and encoding. | String allocation/lifetime/Unicode policy is specified and implemented. |
| D-012 | TODO | P1 | Byte buffers. | Efficient byte arrays exist for compiler and I/O work. |
| D-013 | TODO | P1 | Path/file types. | File APIs use typed paths/results, not raw strings everywhere. |

## Functions And Functional Features

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| F-001 | TODO | P2 | Closures. | Closures parse, capture, typecheck, and codegen. |
| F-002 | TODO | P2 | Lambdas. | Lambda syntax and inference are stable. |
| F-003 | TODO | P2 | Higher-order functions. | Functions/closures can be passed and returned. |
| F-004 | TODO | P2 | Captures. | Capture modes are explicit and memory-safe. |
| F-005 | TODO | P1 | Iterators. | Collections expose safe iteration without manual indexing. |
| F-006 | TODO | P2 | Standard combinators. | `map`, `filter`, `fold`, `find`, etc. work on iterators. |
| F-007 | DEFER | P3 | Partial application. | Only implement if proven useful for AI/codegen ergonomics. |

## Control Flow And Errors

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| C-001 | TODO | P0 | `?` operator. | Result/Option propagation is typed, hygienic, and tested. |
| C-002 | PARTIAL | P1 | `defer` in self-host path. | Self-host compiler can parse/codegen defer or rejects it clearly. |
| C-003 | TODO | P2 | Labeled break/continue. | Nested loop exits are explicit and tested. |
| C-004 | TODO | P0 | Pattern guards. | Guards typecheck and preserve exhaustiveness rules. |
| C-005 | TODO | P0 | Early-exit cleanup guarantees. | Return/break/continue/? run required cleanup/defer. |
| C-006 | TODO | P1 | Panic/abort policy. | Runtime failure policy is documented and enforced. |
| C-007 | PARTIAL | P0 | Recoverable error conventions. | Stdlib APIs consistently return Result/Option. |

## Memory And Resource Model

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| M-001 | PARTIAL | P0 | Ownership rules. | Move/copy/borrow behavior is specified and enforced. |
| M-002 | PARTIAL | P0 | Move semantics in self-host path. | Self-host compiler can compile moved/copied values safely. |
| M-003 | TODO | P0 | Borrow/reference model. | References have safe lifetime/resource behavior or a simpler alternative. |
| M-004 | TODO | P0 | Region/arena rules. | Arena allocation is available and verified for compiler workloads. |
| M-005 | TODO | P0 | Destructor/drop semantics. | Resources release deterministically. |
| M-006 | TODO | P0 | Leak checks. | Long-running compiler tests include leak detection or bounded arena reset. |
| M-007 | PARTIAL | P1 | Safe handle rules. | Raw handles have typed wrappers or are phased out; self-host AST node/type/expression/pattern handles now pass through named bridge helpers and read-only wrapper structs during bootstrap, lexer results now pass through `LexerResultRef`, parser state now passes through `ParserStateRef`, and mutable C codegen/type-state now passes through `CgenStateRef`, with compiler passes consuming typed refs. |
| M-008 | PARTIAL | P0 | Null absence guarantees. | Null-like states use Option/Result, not raw zero handles except bootstrap internals; bootstrap AST absence now routes through optional handle helpers. |
| M-009 | TODO | P1 | Copy vs move for aggregate values. | Struct, array, string, Vec, HashMap semantics are explicit and tested. |
| M-010 | TODO | P1 | Resource types. | Files, directories, processes, sockets use deterministic cleanup. |

## Runtime And Standard Library

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| R-001 | PARTIAL | P0 | Complete string library. | CI covers length, indexing, substring, concat, compare, parse, formatting. |
| R-002 | PARTIAL | P0 | Complete Vec library. | Push/pop/get/set/len/iter/clear/free are typed and tested. |
| R-003 | PARTIAL | P0 | Complete HashMap library. | Generic keys/values, collision behavior, deletion, iteration tested. |
| R-004 | PARTIAL | P0 | File I/O in self-host path. | Read/write/exists fixtures run through generated and stage2 compilers. |
| R-005 | TODO | P1 | Directory/path APIs. | Directory traversal and path joins are typed and cross-platform. |
| R-006 | TODO | P1 | Environment variables. | Env APIs return Result/Option with diagnostics. |
| R-007 | TODO | P1 | Process execution policy. | Process APIs are explicit, sandboxable, and disabled where unsafe. |
| R-008 | TODO | P2 | Time/date. | Time APIs are deterministic where needed for tests. |
| R-009 | TODO | P0 | JSON parser/writer. | Compiler diagnostics can be built in Bunker. |
| R-010 | TODO | P1 | CLI argument parser. | Self-host compiler can parse command-line arguments. |
| R-011 | TODO | P1 | Logging. | Compiler/runtime logs have levels and structured output. |
| R-012 | TODO | P0 | Diagnostics builder library. | Bunker code can emit structured diagnostics consistently. |
| R-013 | TODO | P0 | Arena allocator library. | Compiler allocations use bounded arenas. |
| R-014 | TODO | P1 | Serialization. | AST and diagnostics can be serialized. |
| R-015 | TODO | P1 | Unicode policy. | Strings specify UTF-8 vs byte semantics and test it. |
| R-016 | PARTIAL | P0 | Stable C runtime ABI. | Runtime functions are versioned and compatibility-tested. |

## Compiler Frontend

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| CF-001 | PARTIAL | P0 | Reusable Bunker lexer. | Lexer exists as module and routes lexer output layout through `LexerResultRef` lexer-result helpers. |
| CF-002 | PARTIAL | P0 | Reusable Bunker parser. | Parser exists as module with recovery/spans and routes parser cursor, token-table, and parse-error state through `ParserStateRef` parser-state helpers. |
| CF-003 | PARTIAL | P0 | AST definitions in Bunker. | AST construction, parser/codegen reads, AST collection access, optional AST handles, node/type/expression/pattern handle conversion, semantic child-handle access, explicit handle-named optional field access, read-only AST wrapper structs, C-codegen typed-ref consumption, AST-report typed-ref consumption, symbol-table typed-ref consumption, type-graph typed-ref consumption, resolver typed-ref consumption, typecheck typed-ref consumption, internal field conversion, AST kind/category/span reasoning, and codegen state typed-ref consumption are centralized in Bunker helpers; final gate requires structs/enums instead of raw `Vec<i64>` tags. |
| CF-004 | PARTIAL | P0 | Source spans on AST nodes. | Self-host AST nodes and patterns carry byte start/end offsets; final gate requires file, line, column, byte offsets, and source excerpts across compiler phases. |
| CF-005 | TODO | P0 | Parser recovery. | Multiple errors are reported from one parse. |
| CF-006 | PARTIAL | P0 | Machine-readable parse diagnostics. | Parse errors emit JSON and prompt-ready hints. |
| CF-007 | PARTIAL | P0 | Typechecker in Bunker. | Bootstrap typecheck pass lives in `modules/typecheck.bkr`, consumes typed AST refs over the bootstrap layout, and reports annotation, return, condition, assignment, range, and direct call-argument mismatches; final gate requires full subset enforcement and separation from codegen inference. |
| CF-008 | PARTIAL | P0 | Name resolver in Bunker. | Bootstrap resolver pass lives in `modules/resolver.bkr` and reports duplicate declarations plus unresolved identifiers/calls/types/struct literal fields; final gate requires import graph, visibility, overloads, and definition-use related spans. |
| CF-009 | TODO | P0 | Module resolver. | Import graph, cycles, and visibility are checked. |
| CF-010 | TODO | P0 | Semantic validation passes. | Non-type semantic errors are separate and tested. |
| CF-011 | TODO | P0 | Exhaustiveness checker. | Match exhaustiveness works for ADTs. |
| CF-012 | BLOCKED | P0 | Borrow/resource checker. | Depends on selected memory/resource model. |

## Compiler Backend

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| CB-001 | PARTIAL | P0 | Bunker-written C codegen. | Codegen is modular, routes mutable state through `CgenStateRef` cgen-state helpers, consumes typed AST refs over the bootstrap layout, and handles current self-host fixture set. |
| CB-002 | TODO | P0 | Typed C emission. | C output is driven by real types, not heuristics. |
| CB-003 | TODO | P1 | Temporary variable generation. | Temps are hygienic and stable for nested expressions. |
| CB-004 | PARTIAL | P1 | Portable C output. | GNU-only expressions are removed or CI documents/locks GNU-C requirement. |
| CB-005 | PARTIAL | P0 | Runtime ABI versioning. | Generated C declares expected runtime version. |
| CB-006 | TODO | P2 | Debug info/source mapping. | Runtime/compiler errors map back to Bunker spans. |
| CB-007 | TODO | P2 | Optimization passes. | Constant folding/dead code elimination are implemented where safe. |
| CB-008 | TODO | P2 | Incremental compilation. | Changed modules compile without full rebuild. |
| CB-009 | TODO | P2 | Multi-target backend strategy. | C/Cranelift/LLVM roles are explicit and tested. |
| CB-010 | TODO | P1 | Artifact layout. | Output directories and generated files are deterministic. |

## Self-Hosting

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| SH-001 | PARTIAL | P0 | Self-host smoke gate. | Current stage1/stage2 CI remains green after every change. |
| SH-002 | DONE | P0 | Split `bkrc.bkr` into modules. | Compiler source is multiple Bunker files with imports. |
| SH-003 | PARTIAL | P0 | Typed AST in self-host compiler. | Parser construction, parser/codegen reads, common AST collection iteration, optional AST node handles, AST handle conversions, semantic child-handle access, explicit handle-named optional field access, read-only AST wrapper structs, C-codegen typed-ref consumption, AST-report typed-ref consumption, symbol-table typed-ref consumption, type-graph typed-ref consumption, resolver typed-ref consumption, typecheck typed-ref consumption, codegen state typed-ref consumption, and AST field conversions go through Bunker bridge helpers; final gate requires raw numeric tags to be replaced by Bunker types. |
| SH-004 | TODO | P0 | Enums for token/node kinds. | Token and AST tags use language enums. |
| SH-005 | TODO | P0 | Real generic collections in self-host compiler. | `Vec<T>` and maps preserve element/key/value types. |
| SH-006 | TODO | P0 | Stage0/Stage1/Stage2 docs. | Bootstrap chain is documented and reproducible. |
| SH-007 | DONE | P0 | Golden tests vs Rust compiler. | Outputs/diagnostics match for selected fixtures or known differences are logged. |
| SH-008 | TODO | P0 | Rust module migration map. | Each Rust compiler subsystem has a Bunker replacement target. |
| SH-009 | BLOCKED | P0 | Build compiler without Rust. | Requires modules, stdlib, diagnostics, and typed compiler structures. |
| SH-010 | TODO | P1 | Reproducible self-host artifacts. | CI uploads deterministic stage artifacts with checksums. |

## Tooling

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| G-001 | TODO | P1 | Formatter. | `bunker fmt` formats files deterministically. |
| G-002 | TODO | P1 | Linter. | `bunker lint` reports style/safety issues. |
| G-003 | TODO | P1 | Language server. | LSP supports diagnostics, hover, go-to-definition, completion. |
| G-004 | TODO | P1 | `bunker test`. | Native test runner discovers and runs Bunker tests. |
| G-005 | TODO | P2 | `bunker doc`. | Documentation generation from doc comments. |
| G-006 | TODO | P1 | Package manager. | Local package format, dependencies, and lockfile exist. |
| G-007 | TODO | P2 | Build cache. | Rebuilds avoid unchanged work safely. |
| G-008 | TODO | P2 | Watch mode. | File changes trigger rebuilds/tests. |
| G-009 | TODO | P2 | Debugger hooks. | Generated code can be debugged back to source. |
| G-010 | TODO | P2 | Profiler hooks. | Runtime/compiler hotspots are measurable. |
| G-011 | TODO | P2 | Coverage tooling. | Test coverage can be measured. |
| G-012 | TODO | P2 | Benchmark tooling. | Performance regressions are tracked. |

## AI-Agent Diagnostics

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| A-001 | PARTIAL | P0 | JSON diagnostics. | Parse/import errors plus self-host resolver/typecheck reports emit structured JSON diagnostics; final gate requires every compiler phase to share one documented diagnostic envelope. |
| A-002 | PARTIAL | P0 | Stable diagnostic codes. | Codes are documented, unique, and testable. |
| A-003 | PARTIAL | P0 | Exact spans. | Parse diagnostics and self-host AST nodes carry byte offsets; final gate requires file, line, column, byte offset, and source excerpt across compiler phases. |
| A-004 | PARTIAL | P0 | Expected/found details. | Parse diagnostics include expected/actual tokens, resolver diagnostics include expected/actual symbol context, and typecheck diagnostics include expected/found types. |
| A-005 | TODO | P0 | Suggested fix edits. | Diagnostics include concrete text edits when safe. |
| A-006 | TODO | P1 | Confidence levels. | Suggestions carry confidence/applicability. |
| A-007 | TODO | P1 | Related spans. | Diagnostics link definition/use/origin locations. |
| A-008 | PARTIAL | P0 | Prompt-ready explanations. | Errors include short AI repair context. |
| A-009 | TODO | P0 | Multi-error recovery. | Parser/typechecker return multiple useful diagnostics. |
| A-010 | PARTIAL | P0 | Machine-readable AST dump. | Self-host generated outputs include `BUNKER_AST_JSON` root/top-level summaries plus a complete nested `tree`; final gate requires Rust and self-host compiler modes to expose the same stable AST dump contract. |
| A-011 | PARTIAL | P0 | Machine-readable type graph. | Self-host generated outputs include `BUNKER_TYPE_GRAPH_JSON` from `modules/type_graph.bkr` for declared types plus bootstrap-inferred locals/returns; final gate requires a real typechecker-backed graph across Rust and self-host compiler modes. |
| A-012 | PARTIAL | P0 | Machine-readable symbol table. | Self-host generated outputs include `BUNKER_SYMBOL_TABLE_JSON` declarations/references and `BUNKER_RESOLVER_JSON` duplicate/unresolved diagnostics; final gate requires import-aware visibility, overloads, and related definition-use spans. |
| A-013 | PARTIAL | P0 | Capability report. | Self-host generated outputs include `BUNKER_CAPABILITY_JSON`; final gate requires CLI-native capability reports across Rust and self-host compiler modes. |
| A-014 | PARTIAL | P0 | Machine-readable typecheck diagnostics. | Self-host generated outputs include `BUNKER_TYPECHECK_JSON` from `modules/typecheck.bkr` for bootstrap expected/found semantic diagnostics, now walked through typed AST refs; final gate requires stable codes, related origins, fix edits, and parity across Rust and self-host compiler modes. |

## Safety And Production Readiness

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| S-001 | TODO | P0 | Soundness rules. | Spec states what programs are safe and why. |
| S-002 | TODO | P0 | Undefined behavior policy. | UB is eliminated or explicitly isolated behind unsafe constructs. |
| S-003 | TODO | P1 | Integer overflow policy. | Debug/release overflow behavior is specified and tested. |
| S-004 | PARTIAL | P1 | Bounds checking policy. | Array/Vec/HashMap access behavior is consistent and tested. |
| S-005 | TODO | P0 | Runtime failure policy. | Panics/aborts/results are consistent. |
| S-006 | TODO | P0 | Security model for APIs. | File/process/network APIs are sandbox-aware. |
| S-007 | TODO | P0 | Agent-generated code sandboxing. | Dangerous APIs can be restricted by policy. |
| S-008 | TODO | P1 | Fuzzing. | Lexer/parser/typechecker have fuzz targets. |
| S-009 | TODO | P1 | Differential tests. | Rust compiler and self-host compiler are compared. |
| S-010 | TODO | P1 | Property tests. | Core runtime and type rules have property tests. |
| S-011 | TODO | P1 | Stress tests. | Large files/projects compile in CI. |
| S-012 | TODO | P1 | Memory leak tests. | Runtime/compiler memory is bounded or leak-checked. |
| S-013 | PARTIAL | P0 | Cross-platform CI. | Existing CI remains green and expands with self-host features. |

## Ecosystem

| ID | Status | Priority | Item | Definition Of Done |
|---|---|---:|---|---|
| E-001 | TODO | P2 | Package registry or local package format. | Packages can be declared, resolved, and versioned. |
| E-002 | TODO | P1 | Versioning rules. | Language, compiler, stdlib, and ABI versions are explicit. |
| E-003 | TODO | P1 | Standard library documentation. | Public stdlib APIs have docs and examples. |
| E-004 | PARTIAL | P1 | Examples for every construct. | `docs/EXAMPLES.md` covers all implemented features. |
| E-005 | TODO | P2 | Migration guides. | Rust/Python/TypeScript migration docs exist. |
| E-006 | TODO | P1 | Contribution guide for language changes. | New feature process requires spec, tests, diagnostics, CI. |
| E-007 | PARTIAL | P0 | Spec kept in sync. | Implementation tracker, spec, roadmap, and tests are cross-linked. |
| E-008 | TODO | P0 | Roadmap tied to CI gates. | Every roadmap milestone has a CI gate or measurable artifact. |

## Completion Gates

| Gate | Status | Required Evidence |
|---|---|---|
| Bootstrap Viable | DONE | Stage1/stage2 self-host smoke compiles and runs current bootstrap fixture set in CI. |
| Self-Host Modular | DONE | Compiler source is split into Bunker modules and built through imports. |
| Self-Host Typed | TODO | Compiler AST/types use Bunker structs/enums/generics instead of raw handles. |
| Self-Host Primary | TODO | Bunker compiler can build a working compiler without Rust for normal development. |
| Production Language | TODO | Modules, generics, ADTs, diagnostics, memory/resource model, stdlib, tooling, and safety gates are green. |
| AI-Agent Native | TODO | Diagnostics, capability reports, AST/type/symbol dumps, and repair hints are machine-readable and stable. |

## Work Log

Use this log for major capability jumps. Keep detailed implementation notes in PR descriptions.

| Date | Change | Evidence |
|---|---|---|
| 2026-04-19 | Added self-host structs. | GitHub Actions passed before merge. |
| 2026-04-19 | Added self-host Option and match support. | PR #17, CI run passed. |
| 2026-04-19 | Added self-host Result builtins. | PR #18, CI run passed. |
| 2026-04-19 | Added self-host Vec and HashMap builtins. | PR #19, CI run passed. |
| 2026-04-19 | Added self-host file I/O fixture coverage. | `tests/72_file_io.bkr` added to generated and stage2 `bkrc` CI gates. |
| 2026-04-19 | Added self-host string method runtime coverage. | `tests/73_string_methods.bkr` added to generated and stage2 `bkrc` CI gates. |
| 2026-04-19 | Added self-host arena fixture subset coverage. | `tests/63_arena_loop_reuse.bkr`, `tests/64_arena_nested_blocks.bkr`, and `tests/65_arena_if_branches.bkr` added to generated and stage2 `bkrc` CI gates; `tests/02_arena_memory.bkr` blockers logged. |
| 2026-04-19 | Made `bkrc.bkr` module-ready without behavior changes. | `self-host/MODULE_BOUNDARIES.md` defines extraction order, exports, dependencies, and Q-005 handoff. |
| 2026-04-19 | Added multi-file self-host compiler entrypoint imports. | `self-host-compile --compiler fixtures/self-host-import/driver.bkr` expands `import "helper.bkr";` in CI. |
| 2026-04-19 | Moved the self-host lexer into a Bunker module. | `self-host/bkrc.bkr` imports `self-host/modules/lexer.bkr`; generated and stage2 `bkrc` expand imports in CI. |
| 2026-04-19 | Moved the self-host parser into a Bunker module. | `self-host/bkrc.bkr` imports `self-host/modules/parser.bkr`; generated and stage2 `bkrc` expand flat module imports in CI. |
| 2026-04-19 | Moved the self-host C codegen into a Bunker module. | `self-host/bkrc.bkr` imports `self-host/modules/c_codegen.bkr`; the driver remains in the entrypoint. |
| 2026-04-19 | Added machine-readable self-host parse diagnostics. | Invalid generated/stage2 `bkrc` inputs include `BUNKER_DIAGNOSTIC_JSON` with source offsets, line/column, expected/actual, and repair hints. |
| 2026-04-19 | Added self-host golden output tests. | CI compares selected fixture results against Rust JIT output and diffs stage1 vs stage2 generated C. |
| 2026-04-19 | Reduced `bkrc.bkr` to a module-composed entrypoint. | The entrypoint imports constants, lexer, parser, C codegen, and compiler driver modules in dependency order. |
| 2026-04-19 | Introduced self-host AST layout helpers. | Parser node construction now goes through `self-host/modules/ast.bkr`, isolating the raw vector layout behind Bunker functions. |
| 2026-04-19 | Routed self-host parser/codegen through AST accessors. | Expression, statement, item, type, pattern, and kernel reads now use `self-host/modules/ast.bkr` helpers instead of direct AST layout indexing. |
| 2026-04-22 | Isolated self-host C codegen state. | C codegen state layout moved behind `self-host/modules/cgen_state.bkr`; `c_codegen.bkr` no longer directly indexes state fields. |
| 2026-04-23 | Isolated self-host parser state. | Parser state layout moved behind `self-host/modules/parser_state.bkr`; `parser.bkr` no longer directly indexes parser state fields. |
| 2026-04-23 | Isolated self-host lexer result layout. | Lexer result layout moved behind `self-host/modules/lexer_result.bkr`; parser state no longer directly indexes lexer result fields. |
| 2026-04-23 | Introduced self-host AST kind/category helpers. | `self-host/modules/ast.bkr` now names node/type/pattern kinds and classifies AST nodes; C codegen uses AST predicates for repeated shape checks. |
| 2026-04-24 | Added self-host AST byte spans. | AST nodes and patterns reserve byte start/end fields; parser attaches source spans and diagnostics consume parser span helpers. |
| 2026-04-24 | Added self-host capability reports. | `BUNKER_CAPABILITY_JSON` is emitted in self-host compiler outputs and checked by CI for success and diagnostic paths. |
| 2026-04-24 | Added self-host AST summary reports. | `BUNKER_AST_JSON` is emitted for successful self-host compiler outputs with root/item span metadata and CI coverage. |
| 2026-04-24 | Added complete nested self-host AST reports. | `BUNKER_AST_JSON` now carries `complete_tree:true` and a recursive `tree` object for agent inspection, with direct/stage1/stage2 CI checks. |
| 2026-04-24 | Added self-host type graph reports. | `BUNKER_TYPE_GRAPH_JSON` now carries declared structs/constants/functions plus bootstrap-inferred local and return expression types for agents, with direct/stage1/stage2 CI checks. |
| 2026-04-25 | Added self-host symbol table reports. | `BUNKER_SYMBOL_TABLE_JSON` now carries declaration and reference tables with bootstrap scopes and spans for agents, with direct/stage1/stage2 CI checks. |
| 2026-04-25 | Added self-host resolver reports. | `BUNKER_RESOLVER_JSON` now carries bootstrap duplicate/unresolved symbol diagnostics for agents, with clean and intentionally broken CI checks. |
| 2026-04-25 | Added self-host typecheck reports. | `BUNKER_TYPECHECK_JSON` now carries bootstrap expected/found semantic diagnostics for agents, with clean and intentionally broken CI checks. |
| 2026-05-01 | Extracted self-host report support helpers. | `modules/report_support.bkr` now owns shared JSON/report/diagnostic helper plumbing used by driver reports, preparing resolver/typecheck module extraction. |
| 2026-05-01 | Extracted self-host resolver module. | `modules/resolver.bkr` now owns bootstrap name-resolution diagnostics and `BUNKER_RESOLVER_JSON`; `driver.bkr` delegates resolver report generation. |
| 2026-05-01 | Extracted self-host type graph and typecheck modules. | `modules/type_graph.bkr` now owns `BUNKER_TYPE_GRAPH_JSON` plus bootstrap type-state helpers, and `modules/typecheck.bkr` owns `BUNKER_TYPECHECK_JSON`; `driver.bkr` delegates both reports. |
| 2026-05-01 | Extracted self-host AST report module. | `modules/ast_report.bkr` now owns `BUNKER_AST_JSON`, complete-tree serialization, and AST report summary helpers; `driver.bkr` delegates AST report generation. |
| 2026-05-01 | Extracted self-host symbol table module. | `modules/symbol_table.bkr` now owns `BUNKER_SYMBOL_TABLE_JSON`, declaration/reference walking, and symbol-table report generation; `driver.bkr` delegates symbol table report generation. |
| 2026-05-01 | Extracted self-host kind model module. | `modules/kind_model.bkr` now owns node/type/pattern naming, AST category mapping, and pure kind predicates as the enum-ready bridge before typed AST work. |
| 2026-05-01 | Added typed AST collection bridge helpers. | `modules/ast.bkr` now exposes typed collection accessors for kernel items, params, fields, call args, array elements, match arms, and struct literal fields; codegen/report/resolver/typecheck/type-graph modules route common iteration through them. |
| 2026-05-01 | Added optional AST handle bridge helpers. | `modules/ast.bkr` now owns optional AST sentinel helpers, and parser/codegen/report/resolver/typecheck/type-graph modules use them where `0` means an absent AST node/type/expression. |
| 2026-05-01 | Added AST handle bridge helpers. | `modules/ast.bkr` now owns AST node/type/expression/pattern handle conversion plus AST handle-list append helpers, reducing direct bootstrap casts outside the AST boundary. |
| 2026-05-01 | Added internal AST field bridge helpers. | `modules/ast.bkr` now owns typed field conversion helpers for node, node-list, scalar-list, pattern-list, and string-list AST fields, removing direct field casts from AST accessors. |
| 2026-05-01 | Added semantic AST child-handle accessors. | `modules/ast.bkr` now exposes handle-valued accessors for expression/type child fields, reducing downstream node-to-handle wrapping in resolver, typecheck, symbol-table, type-graph, and codegen modules. |
| 2026-05-01 | Added explicit AST optional-field handle names. | `modules/ast.bkr` now exposes explicit `*_handle` aliases for optional expression/type/block fields, and compiler modules consume those names instead of ambiguous `*_node`/`*_expr` accessors. |
| 2026-05-01 | Added read-only typed AST wrapper structs. | `modules/ast.bkr` now declares category-specific `Ast*Ref` wrappers with read-only conversion/kind/span helpers as the first typed AST layer over bootstrap raw handles. |
| 2026-05-01 | Routed AST report recursion through typed AST refs. | `modules/ast_report.bkr` now serializes recursive node and pattern JSON through `AstNodeRef` and `AstPatternRef` entry points while preserving the machine-readable report contract. |
| 2026-05-01 | Routed symbol table recursion through typed AST refs. | `modules/symbol_table.bkr` now walks declaration and reference tables through `AstNodeRef`, `AstTypeRef`, `AstExprRef`, `AstStmtRef`, `AstItemRef`, `AstBlockRef`, and `AstPatternRef` entry points while preserving the machine-readable report contract. |
| 2026-05-01 | Routed type graph recursion through typed AST refs. | `modules/type_graph.bkr` now walks declared type, expression inference, struct, constant, function, local, and return report paths through `AstNodeRef`, `AstTypeRef`, `AstExprRef`, `AstStmtRef`, `AstItemRef`, and `AstBlockRef` entry points while preserving typecheck-facing raw adapters. |
| 2026-05-01 | Routed resolver diagnostics through typed AST refs. | `modules/resolver.bkr` now walks duplicate and unresolved diagnostics through `AstNodeRef`, `AstTypeRef`, `AstExprRef`, `AstStmtRef`, `AstItemRef`, `AstBlockRef`, and `AstPatternRef` entry points while preserving the machine-readable resolver contract. |
| 2026-05-01 | Routed typecheck diagnostics through typed AST refs. | `modules/typecheck.bkr` now walks bootstrap typecheck diagnostics through `AstNodeRef`, `AstTypeRef`, `AstExprRef`, `AstStmtRef`, `AstItemRef`, and `AstBlockRef` entry points while preserving `BUNKER_TYPECHECK_JSON`. |
| 2026-05-01 | Routed C codegen through typed AST refs. | `modules/c_codegen.bkr` now walks type conversion, expression inference, emission, statements, blocks, structs, constants, functions, and kernel codegen through `Ast*Ref` entry points while preserving generated C behavior. |
| 2026-05-01 | Isolated residual raw AST predicate reads. | AST report summaries, symbol-table match-arm body dispatch, and resolver match-arm body dispatch now use typed refs, leaving raw AST kind/predicate access inside AST/kind helper modules. |
| 2026-05-01 | Added typed codegen state refs. | `modules/cgen_state.bkr` now exposes `CgenStateRef`, and C codegen, type graph, and typecheck paths thread mutable codegen/type-state through typed ref helpers while preserving raw bootstrap adapters. |
| 2026-05-01 | Added typed parser state refs. | `modules/parser_state.bkr` now exposes `ParserStateRef`, and parser plus driver paths thread token tables, cursor position, and first-error state through typed ref helpers while preserving raw bootstrap adapters. |
| 2026-05-01 | Added typed lexer result refs. | `modules/lexer_result.bkr` now exposes `LexerResultRef`, and lexer, parser-state, and driver paths thread token/name/value/string tables through typed ref helpers while preserving raw bootstrap adapters. |
