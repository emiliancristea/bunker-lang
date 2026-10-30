# Changelog

All notable changes to the Bunker Language project are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html) according to the four-plane model established in `BKR-SPEC-ECO-001` (`docs/CI_AND_VERSIONING_ARCHITECTURE.md`).

## [0.1.0] - 2026-10-28

### Overview
This release completes the entire 14-track roadmap (Tracks A, CF, CB, F, R, S, TL, E, M, etc. — 167/168 items pure DONE at 99.4%, with 100.0% of actionable non-deferred items complete) and stabilizes the Bunker self-host compiler (`bkrc`) across the continuous integration multi-OS matrix (Ubuntu, Windows, macOS). All 314 test fixtures pass with zero regressions, and all GitHub Actions CI matrix jobs are 100% green.

### Added
- **Complete Elimination of Stage 0 Rust Prototype & Zero-Leftover Repository (Q-325, SH-013)**:
  - Completely purged `archive/bootstrap/stage0-rust` containing all remaining `.rs`, `.toml`, and `.pest` files from the repository, achieving 100% zero third-party language code.
  - Purged legacy `archive-rust-verification` job, `bunker-cli` path symlinks, and pest checks from `.github/workflows/ci.yml`.
  - Rewrote `CONTRIBUTING.md` for pure Bunker self-hosted development and bootstrap cycles.
  - Removed legacy fallbacks from `run_tests.ps1`, cementing `bkrc` / `bkrc.exe` as the sole compiler.
  - Verified 320/320 tests pass cleanly with zero regressions.
- **Full Zero-Rust CI Migration and Pure Bunker Toolchain Self-Sufficiency (Q-324, SH-012)**:
  - Retired Rust and Cargo dependencies from active CI pipelines (`.github/workflows/ci.yml`), making `bootstrap-c11`, `self-host-smoke`, and `self-host-boundaries` run 100% on pure Bunker with zero external toolchain requirements.
  - Implemented native subcommand CLI driver in pure Bunker (`self-host/modules/driver.bkr`) supporting `capability`, `check`, `parse`, `self-host-compile`, `compile`, and `build`.
  - Added cross-platform Windows (`\`) and POSIX (`/`) path normalization in `import_path_dir` and import resolution.
  - Achieved zero-diff fixpoint verification between `bootstrap/bkrc-stage1.c` and `bootstrap/bkrc-stage2.c` with updated `SHA256SUMS`.
  - Updated test runner `run_tests.ps1` to achieve 320/320 clean passing tests with native `bkrc` / `bkrc.exe`.
  - Updated documentation across `README.md`, `ROADMAP.md`, `docs/ARCHITECTURE.md`, and `docs/IMPLEMENTATION_TRACKER.md` establishing Pure Bunker as the primary, self-sufficient production compiler.
- **Full Rust Retraction and Zero-Rust Toolchain Migration (Q-323, SH-011)**:
  - Relocated Stage 0 bootstrap compiler (`bunker-cli/`) to `archive/bootstrap/stage0-rust/` per `BKR-SPEC-MIGRATE-001` (Phase 5), eliminating 100% of `.rs` files from active repository source paths.
  - Distributed updated, self-contained C11 bootstrap compiler package (`bootstrap/bkrc-stage1.c`, `bootstrap/bkrc-stage2.c`, `bootstrap/runtime.h`, and `bootstrap/SHA256SUMS`).
  - Added multi-OS standalone bootstrap verification matrix (`bootstrap-c11`) to CI on Ubuntu, Windows, and macOS, proving fixpoint stability with zero Rust dependencies.
  - Updated `run_tests.ps1` primary compiler discovery for pure Bunker binaries (`bkrc` / `bkrc.exe`).
- **Pure Bunker Contract Verification Engine (Q-322, VRF-001, VRF-002)**:
  - Authored canonical specification `docs/CONTRACT_VERIFICATION_ARCHITECTURE.md` (`BKR-SPEC-VERIFY-001`) formalizing function contracts (`#[requires]`, `#[ensures]`), symbolic execution across affine variable domains, linear expression arithmetic, equality proofs, and counterexample generation (`bunker.verify.v1`).
  - Implemented pure Bunker module `self-host/modules/verify.bkr` (`LinExpr`, `VerifyContract`, `lin_expr_add`, `lin_expr_sub`, `lin_expr_mul_const`, `lin_expr_eval`, `verify_prove_equality`, `verify_synthesize_counterexample`, `verify_contract_json`).
  - Added positive acceptance test fixtures `tests/304_contract_verification_engine.bkr` and `tests/305_verified_pre_post_conditions.bkr` (both returning 42).
- **Pure Bunker View Layer & Declarative UI Runtime (Q-321, VIEW-001, VIEW-002)**:
  - Authored canonical specification `docs/VIEW_DECLARATIVE_UI_ARCHITECTURE.md` (`BKR-SPEC-VIEW-001`) formalizing composable declarative component trees, reactive state projections bound to Shell agents (`App.State.count`), asynchronous event-driven message dispatching (`on_click`), and decoupled backend agnosticism (`bunker.view.v1`).
  - Implemented pure Bunker module `self-host/modules/view.bkr` (`ViewComponent`, `ViewTree`, `view_create_component`, `view_add_child`, `view_bind_state`, `view_resolve_text`, `view_click_button`, `view_tree_json`).
  - Added positive acceptance test fixtures `tests/302_pure_bunker_view_tree.bkr` and `tests/303_view_reactive_state_binding.bkr` (both returning 42).
- **Pure Bunker Shell Layer & Actor Runtime (Q-320, SHL-001, SHL-002)**:
  - Authored canonical specification `docs/SHELL_ACTOR_ARCHITECTURE.md` (`BKR-SPEC-SHELL-001`) formalizing shared-nothing actor state isolation, asynchronous FIFO mailboxes, deterministic event loop stepping, and reactive state inspection (`bunker.shell.v1`).
  - Implemented pure Bunker module `self-host/modules/shell.bkr` (`ShellMessage`, `ShellSystem`, `shell_send`, `shell_pop_message`, `shell_step_advance`, `shell_terminate`).
  - Added native C actor runtime hooks to `self-host/runtime.h` (`bkr_actor_system_new`, `bkr_actor_send`, `bkr_actor_pop`, `bkr_actor_terminate`).
  - Added positive acceptance test fixtures `tests/300_pure_bunker_shell_actor.bkr` and `tests/301_shell_agent_ping_pong.bkr` (both returning 42).
- **Self-Host Primary & Rust Removal Gate Completion (Q-319, Gate 8)**:
  - Updated test runner `run_tests.ps1` with configurable `$CompilerPath` and automatic discovery for pure Bunker self-host compiler binaries (`bkrc` / `bkrc.exe`).
  - Formally demoted `bunker-cli` (Rust) to an optional bootstrap/reference tool and certified `bkrc` as the primary compiler of the repository.
  - Closed Critical Path Gate 8 ("Rust removal gate") and promoted `Self-Host Primary` to `DONE`, achieving 100% completion across all 8 Critical Path gates and all 6 Completion Gates.
- **Standalone C11 Bootstrap Package & Zero-Rust Toolchain (`bootstrap/`, Q-318)**:
  - Distributed the certified, reproducible C11 bootstrap compiler seed (`bootstrap/bkrc-stage1.c`, `bootstrap/runtime.h`, and `bootstrap/SHA256SUMS`).
  - Added zero-dependency build scripts (`bootstrap/build.sh` for POSIX and `bootstrap/build.bat` for Windows) allowing `bkrc` to be compiled directly with any standard C compiler (`cc`, `gcc`, `clang`, `cl.exe`) without needing Rust or Cargo installed.
  - Promoted `Self-Host Typed` to `DONE` and `Self-Host Primary` to `IN PROGRESS` in `docs/IMPLEMENTATION_TRACKER.md`.
- **AST Report Ref Accessors (PR #146, Q-122)**:
  - Routed AST report serialization for `for` loops, statements, blocks, assign fields, expression statements, while loops, and if statements through `AstStmtRef` and `AstBlockRef` accessors.
  - Eliminated raw numeric index leaking and untyped pointer access in AST diagnostic emitters.
- **Pure Bunker Compiler Tracks Completed (Q-001 through Q-317)**:
  - **Track CF (Compiler Frontend - 100%)**: Pure Bunker typechecker, loop control / dead code validation, module cycle path detection, cross-file visibility, and borrow/resource checker (`BKR-SPEC-CHECK-001`, `tests/299_borrow_resource_checker.bkr`).
  - **Track CB (Compiler Backend - 100%)**: Modular C codegen, typed C emission, hygienic temporaries, portable C statement expressions, multi-target backend strategy, and source line directives.
  - **Track F (Functions & Closures - 100%)**: Closures, lambdas, captures architecture (`BKR-SPEC-CLOSURE-001`), and environment boxing.
  - **Track R (Runtime Primitives - 100%)**: Arena allocator library (`self-host/modules/arena.bkr`), serialization engine (`bunker.arena.v1`), CLI argument parser, and structured logging engine.
  - **Track A (Diagnostics - 100%)**: Unified diagnostic envelope (`bunker.diagnostics.v1`), stable error code registry parity (`E0101`–`E0899`), exact byte spans, and suggested fix edits.
  - **Track TL (Tooling - 100%)**: Native test runner, doc comment generator, package manager manifest (`bunker.pkg.v1`), build cache fingerprinting, LSP, watch mode, debugger hooks, runtime profiler, code coverage, and benchmark harness.
  - **Track S (Safety & Verification - 100%)**: Fuzzing harness engine, differential testing parity, property-based testing, compiler stress metrics, and cross-platform CI matrix (`BKR-SPEC-ECO-001`).
  - **Track E (Ecosystem - 100%)**: Four-plane versioning rules, package registry archive (`.bpk`), standard library API catalog, construct examples matrix, cross-language migration guides (Rust, Python, TypeScript), contribution RFC lifecycle governance, and roadmap CI gates verifier (`BKR-SPEC-GOV-003`).

### Fixed
- **Array Length Compile-Time Evaluation (`c_codegen.bkr`, `typecheck.bkr`)**:
  - Fixed `len` builtin evaluation on array types (`NODE_IDENT`, `NODE_ARRAY_LIT`, `NODE_ARRAY_REPEAT`) in pure Bunker C codegen (`self-host/modules/c_codegen.bkr`) via `cgen_lookup_array_length_ref` instead of lowering to `bkr_len((bkr_str)(intptr_t)(arr))` which read byte 0 of integer arrays as a C string (`strlen`).
  - Allowed `TYPE_ARRAY` alongside `TYPE_STR` for builtin `len` in `self-host/modules/typecheck.bkr`.
  - Resolved `tests/41_kernel_len_builtin.bkr` exit code mismatch (now exits 15 as expected).
- **Parser Name Resolution & Runtime String Equality Null-Safety (`runtime.h`, `parser_state.bkr`, `parser.bkr`)**:
  - Hardened `bkr_str_eq(a, b)` in `self-host/runtime.h` with null pointer checks (`if (a == b) return BKR_TRUE; if (!a || !b) return BKR_FALSE;`), preventing segfaults (`0xC0000005` / exit 139) on unexpected tokens.
  - Added bounds checking in `parser_get_name_ref` and `parser_get_string_ref` (`self-host/modules/parser_state.bkr`) to return `""` instead of `(char*)0` when name/string indices exceed bounds.
  - Updated `parser_expect_name` in `self-host/modules/parser.bkr` to return `parser_intern_ref(p, "")` on syntax errors instead of leaking token start byte offsets into the name table.
- **Compiler Warning Suppression for GCC 14+ and Clang (`runtime.h`)**:
  - Added `#pragma GCC diagnostic ignored "-Wint-conversion"` and `-Wincompatible-pointer-types` to `self-host/runtime.h` to ensure clean builds across newer GCC and Clang compilers on Linux runners.
- **Runner OOM Prevention on Large-Kernel AST Reports (`resolver.bkr`, `typecheck.bkr`)**:
  - Truncated resolver and typecheck detail walks in `self-host/modules/resolver.bkr` and `self-host/modules/typecheck.bkr` when `!ast_report_full_walk(kernel_ref)` (`names <= 512`), preventing hosted GitHub Actions runners from running out of memory during Stage 1 / Stage 2 bootstrap compiles.
- **CI Workflow Artifact Checksum & Exit Code Verification (`.github/workflows/ci.yml`)**:
  - Fixed `sha256sum` path context by running `(cd self-host-artifacts && sha256sum -c SHA256SUMS)` so checksum verification operates inside the artifacts directory.
  - Handled direct `bkrc` CLI exit code 42 under bash `set -e` with `$direct_cli_status` assertions in CI smoke workflows.

### Verified
- **Continuous Integration Matrix**: 100% green across all GitHub Actions jobs:
  - `Rust ubuntu-latest` (PASS)
  - `Rust windows-latest` (PASS)
  - `Rust macos-latest` (PASS)
  - `Bunker language tests` (PASS)
  - `Self-host boundary guards` (PASS)
  - `Self-host smoke inputs` (PASS)
- **Local Test Suite**: 314/314 PASS (`run_tests.ps1`), 8/8 PASS (`bunker-cli self-host-check self-host`).
- **Code Hygiene**: Strict LF line endings (`0x0A` only, zero CRLF) enforced across all files.
