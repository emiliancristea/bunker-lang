# Bunker Production And Self-Hosting Completion

Status: Draft
Owner: Bunker Corporation
Created: 2026-07-03
Last updated: 2026-07-03

## 1. Executive Summary

Bunker has a working Rust production compiler, a modular Bunker-written compiler prototype, green CI gates, and broad fixture coverage for the bootstrap language. It is not yet a production-complete language or a primary self-hosted compiler. The remaining work is to turn the bootstrap self-host path into the normal compiler path, replace raw bootstrap representations with real Bunker types, complete the type system and standard library, make memory/resource behavior production-safe, and harden diagnostics, safety, tooling, and release operations.

Current evidence supports this rough status:

| Completion Track | Evidence-Based Estimate | Meaning |
|---|---:|---|
| Bootstrap compiler viability | 70% | Stage1/stage2 self-host smoke, generated C, reports, and fixture gates work in CI. |
| Production language readiness | 35-40% | Many core features exist, but generics, ADTs, memory/resource rules, stdlib, tooling, safety gates, and Rust removal remain. |
| Primary self-hosted compiler | 30-35% | Self-host modules exist and stage through CI, but Rust is still the production compiler and bootstrap driver. |

The shortest useful path is not to add new surface syntax first. It is to finish the self-host compiler's typed foundation, then complete the minimum runtime/type-system pieces needed to make the Bunker compiler build itself as the normal path.

## 2. Background & Problem Statement

Bunker is an AI-native systems language with Kernel, Shell, and View layers. The Rust crate `bunker-cli` currently implements the production compiler and runtime paths. The self-host compiler under `self-host/` has been split into modules and can generate C through CI smoke gates, but the implementation still relies on raw numeric tags, raw `Vec<i64>` storage, compatibility adapters, and Rust orchestration.

The problem is that there is no single implementation-ready completion spec that translates "what remains" into ordered gates. The existing tracker is authoritative and detailed, but it is optimized as a ledger. This spec turns that ledger into a buildable plan for reaching:

1. Production language readiness.
2. Primary self-hosted compiler usage.
3. Rust demotion from production compiler to bootstrap/reference implementation.

## 3. Goals

- Define the remaining work from current repository evidence.
- Preserve the CI-only build/test policy.
- Prioritize self-hosting work that removes real blockers.
- Make each completion gate testable in GitHub Actions.
- Keep implementation slices PR-sized where possible.
- Avoid speculative features until they unblock production or self-hosting.
- Establish concrete acceptance criteria for "100% done."

## 4. Non-Goals

- Do not implement compiler code in this spec.
- Do not replace the authoritative implementation tracker.
- Do not add a new package manager, LSP, LLVM backend, or embedded target before the primary self-host path needs it.
- Do not claim production readiness while Rust remains the only production compiler path.
- Do not run local build, run, or self-host verification commands; CI remains the build authority.

## 5. Repository Findings

| Finding | Evidence | Impact |
|---|---|---|
| CI is the verification authority. | `README.md`, `docs/IMPLEMENTATION_TRACKER.md`, `.github/workflows/ci.yml` | All completion gates must be proven through GitHub Actions. |
| CI is currently healthy. | GitHub Actions run `28668326471` completed successfully on 2026-07-03. | New work can rely on CI as the current source of build truth. |
| Rust is still production compiler and bootstrap driver. | `docs/IMPLEMENTATION_TRACKER.md`, `docs/ARCHITECTURE.md` | Rust removal remains blocked until self-host type/runtime/compiler foundations are complete. |
| Current compiler pipeline is Rust-first. | `docs/ARCHITECTURE.md`, `bunker-cli/src/main.rs`, `bunker-cli/src/ast.rs`, `bunker-cli/src/typeck.rs`, `bunker-cli/src/jit.rs`, `bunker-cli/src/codegen.rs` | Self-host parity must include CLI, diagnostics, typecheck, codegen, and runtime behavior. |
| Self-host source is modular. | `self-host/bkrc.bkr`, `self-host/modules/*.bkr`, `self-host/MODULE_BOUNDARIES.md` | Module split is done, but module semantics still depend on bootstrap import expansion and raw layouts. |
| Typed refs exist over raw bootstrap layouts. | `self-host/modules/ast.bkr`, `self-host/modules/lexer_result.bkr`, `self-host/modules/parser_state.bkr`, `self-host/modules/cgen_state.bkr` | This is a bridge, not the final typed data model. |
| The tracker marks production completion gates as TODO/PARTIAL. | `docs/IMPLEMENTATION_TRACKER.md` | The remaining plan should center the TODO/PARTIAL P0 gates. |
| Tests cover 92 fixtures. | `README.md`, `docs/ARCHITECTURE.md`, `run_tests.ps1` | Coverage is strong for bootstrap fixtures but incomplete for production language semantics. |
| The CI workflow already has boundary guards. | `.github/workflows/ci.yml` | Future refactors should extend guards instead of relying on review memory. |
| Local scratch files are ignored. | `.gitignore` | Spec work should not depend on tmp artifacts such as `tmp_self_host_scan/`. |

## 6. Research Notes & References

No external research was required for this spec. This is an internal implementation-completion plan grounded in repository docs, source, tests, and GitHub Actions state.

Primary references:

- `README.md`
- `ROADMAP.md`
- `docs/ARCHITECTURE.md`
- `docs/IMPLEMENTATION_TRACKER.md`
- `docs/SPECIFICATION.md`
- `docs/TECHNICAL_SPEC.md`
- `self-host/MODULE_BOUNDARIES.md`
- `.github/workflows/ci.yml`
- `bunker-cli/Cargo.toml`
- GitHub Actions run `28668326471`

## 7. Users, Use Cases & User Stories

### Users

- Bunker language implementers.
- AI agents modifying the compiler.
- Early adopters who need reliable language behavior.
- Future users downloading verified compiler artifacts.

### Use Cases

- Compile Bunker projects without relying on the Rust compiler as the production path.
- Use Bunker diagnostics as structured repair input for AI agents.
- Extend the language without breaking self-host compilation.
- Trust compiler releases through reproducible CI artifacts.

### User Stories

- As a compiler maintainer, I can merge a feature only when CI proves Rust and self-host behavior.
- As an AI agent, I can read capability, AST, symbol, resolver, type graph, and typecheck reports for repair context.
- As a language user, I can compile supported Bunker code with documented semantics and stable diagnostics.
- As a release owner, I can produce a reproducible self-host compiler artifact from CI.

## 8. Functional Requirements

### FR-1: Self-Host Runtime Surface

Complete the runtime functions needed by the self-host compiler:

- File I/O must support compiler workloads through typed `Result`/`Option` semantics.
- String APIs must define encoding and bounds behavior.
- Vec/HashMap/Result/Option runtime support must preserve types rather than erased handles.
- Runtime ABI must be versioned and checked by generated C.

Tracker anchors: Critical Path 1, `R-001` through `R-016`, `D-009`, `D-010`, `D-011`.

### FR-2: Real Modules And Multi-File Compilation

Turn bootstrap import expansion into a production module system:

- Resolve imports relative to importer directories.
- Detect cycles with exact cycle paths.
- Preserve source file identity through diagnostics.
- Support visibility/export rules.
- Eliminate global-name collisions through namespaces or packages.

Tracker anchors: Critical Path 2, `L-001` through `L-005`, `CF-009`, `SH-002`.

### FR-3: Typed Compiler Data Structures

Replace raw numeric AST/token/type layouts with language-level types:

- Add Bunker enums for token kinds, node kinds, type kinds, and pattern kinds.
- Replace raw `Vec<i64>` node records with structs/enums where the language can support them.
- Keep transitional adapters only inside explicit compatibility boundaries.
- Expand CI guards so raw layout reads cannot leak back into compiler consumers.

Tracker anchors: Critical Path 3, `SH-003`, `SH-004`, `CF-003`, `M-007`.

### FR-4: Generics, ADTs, And Typed Collections

Implement the minimum type-system features needed for a real compiler:

- Real generics for `Vec<T>`, `HashMap<K,V>`, `Option<T>`, and `Result<T,E>`.
- User-defined enums/sum types.
- Exhaustive matching over ADTs.
- Pattern typing for nested and destructuring patterns.
- Type aliases where they improve compiler readability and diagnostics.

Tracker anchors: Critical Path 4, `T-001` through `T-024`, `D-001` through `D-013`, `SH-005`.

### FR-5: Production Diagnostics

Unify Rust and self-host diagnostics:

- One documented diagnostic envelope.
- Stable diagnostic code registry across compiler phases.
- File, line, column, byte span, source excerpt, severity, phase, expected/found details, and related spans.
- Safe suggested edits with applicability and confidence.
- Multi-error recovery for parser and typechecker.
- CLI-native capability report for both Rust and self-host paths.

Tracker anchors: Critical Path 5, `A-001` through `A-014`, `CF-004` through `CF-010`.

### FR-6: Memory And Resource Model

Make compiler and runtime memory behavior production-safe:

- Define borrow/reference model or explicitly choose a simpler alternative.
- Prove arena/region rules for compiler workloads.
- Add deterministic cleanup/drop/resource semantics.
- Bound long-running compiler memory use.
- Add CI leak/stress gates for stage1/stage2 compiler runs.

Tracker anchors: Critical Path 6, `M-001` through `M-010`, `S-012`.

### FR-7: Bunker-Written Frontend And Backend Parity

Make the Bunker-written compiler semantically equivalent for supported inputs:

- Lexer/parser/typechecker/codegen are Bunker-owned modules.
- Codegen is typed, hygienic, portable, and deterministic.
- Rust/self-host outputs and diagnostics are compared for selected fixtures.
- Known differences are tracked with explicit retirement gates.

Tracker anchors: Critical Path 7, `CF-001` through `CF-012`, `CB-001` through `CB-010`, `SH-007`, `S-009`.

### FR-8: Rust Removal Gate

Demote Rust from production compiler to bootstrap/reference only:

- Self-host compiler builds a working compiler without Rust for normal development.
- Stage0/stage1/stage2 chain is documented and reproducible.
- CI publishes deterministic self-host artifacts with checksums.
- Bunker compiler can compile itself from source and compile the supported fixture suite.

Tracker anchors: Critical Path 8, `SH-006`, `SH-008`, `SH-009`, `SH-010`.

### FR-9: Safety And Production Readiness

Define and test the safety contract:

- Soundness rules.
- Undefined behavior policy.
- Integer overflow policy.
- Bounds checking policy.
- Runtime failure policy.
- Security model for file/process/network APIs.
- Agent-generated code sandboxing.
- Fuzz, property, stress, and leak tests.

Tracker anchors: `S-001` through `S-013`.

### FR-10: Minimum Tooling For Production

Add tooling only when it supports production or self-hosting:

- Formatter before large syntax churn.
- Native `bunker test` once self-hosted fixture execution is stable.
- Linter only for safety/style rules that CI can enforce.
- LSP/package manager after the language and compiler substrate stabilize.

Tracker anchors: `G-001` through `G-012`, `E-001` through `E-008`.

## 9. Non-Functional Requirements

- CI-first: every production feature must add or extend CI coverage.
- Deterministic: generated C and compiler artifacts must be reproducible or differences must be explained.
- Resource bounded: self-host compiler runs must have time and memory caps.
- Cross-platform: production compiler behavior must be checked on Windows, Ubuntu, and macOS where relevant.
- AI-repairable: diagnostics must remain machine-readable and stable.
- Maintainable: self-host module boundaries must be enforced by code and CI, not only prose.
- Minimal: features that do not unblock production or self-hosting should wait.

## 10. Proposed Solution

Use eight sequential gates. A later gate may start only when it does not expand the earlier gate's compatibility debt.

| Gate | Theme | Outcome |
|---|---|---|
| 0 | Keep CI green | Every change starts from a green GitHub Actions baseline. |
| 1 | Runtime substrate | Compiler-needed stdlib/runtime APIs are typed and bounded. |
| 2 | Typed core model | Compiler AST/tokens/types move from raw records to Bunker structs/enums. |
| 3 | Generics and ADTs | Collections and compiler data structures become real typed Bunker code. |
| 4 | Diagnostic parity | Rust and self-host diagnostics share one contract. |
| 5 | Memory/resource safety | Compiler workloads have bounded, documented resource behavior. |
| 6 | Self-host parity | Bunker compiler handles the supported production subset without Rust as production path. |
| 7 | Production release | Self-host artifacts, docs, safety gates, and rollback path are release-ready. |

## 11. API, Interface, CLI, or UX Contract

The existing CLI contract remains until a replacement is proven:

- `bunker-cli check <file>` remains safe for local inspection when a CI-built binary is available.
- `bunker-cli parse <file>` remains safe for local inspection.
- `bunker-cli self-host-check self-host` remains safe for local inspection.
- `bunker-cli build`, `run`, and `self-host-compile` remain CI-only until resource behavior is proven safe.
- `--format=json` remains the machine-readable diagnostics path.
- `--smt` remains optional and must fail gracefully when Z3 is unavailable.

New or changed CLI behavior must include:

- Human text output.
- JSON output where diagnostics are possible.
- A fixture covering success.
- A fixture covering the most important failure path.
- CI coverage under resource caps if it executes generated code or self-host compilation.

## 12. Data Model & Persistence

The target data model is:

- Token kinds as Bunker enums.
- AST nodes as Bunker structs/enums.
- Type representations as Bunker enums/structs.
- Symbol table entries as typed records with source origins.
- Diagnostics as typed records serialized to the shared JSON envelope.
- Module graph as typed nodes/edges with cycle and visibility metadata.
- Runtime handles replaced by typed wrappers or true typed collections.

Transitional data model:

- Raw `Vec<i64>` bootstrap records may remain only inside named compatibility boundaries.
- CI must reject direct raw AST/parser/lexer/codegen state reads outside those boundaries.
- Every transition from raw to typed representation must keep stage1/stage2 self-host smoke green.

No persistent database is involved. Generated C, compiler artifacts, and diagnostic reports are build artifacts and must be produced by CI.

## 13. Security, Privacy & Abuse Considerations

- File, directory, environment, process, and network APIs must have explicit sandbox policy before production use.
- `unsafe_trust` must remain auditable and isolated.
- Generated code must not read host files except through documented runtime APIs.
- Diagnostics must not leak secrets from environment variables or unrelated filesystem paths.
- Agent-generated code must be restrictable by policy.
- CI artifacts must not include host-specific temp paths except intentional diagnostic trace files.

## 14. Error Handling & Edge Cases

Required edge cases:

- Missing imports, duplicate imports, and cyclic imports with exact cycle context.
- Invalid import paths and path traversal attempts.
- `None`, empty arrays, `Ok`, `Err`, `Vec`, and `HashMap` without enough type context.
- Duplicate symbols across modules.
- Missing entry functions and bad entry signatures.
- Non-exhaustive ADT matches.
- Duplicate/unreachable match patterns.
- Invalid assignment targets and const assignment.
- Field/index access against non-struct/non-indexable values.
- Void values used in expression contexts.
- Out-of-bounds collection access policy.
- Resource cleanup on return, break, continue, and error propagation.
- Stage1/stage2 compiler timeout, memory growth, and partial artifact cleanup.

## 15. Observability & Operations

Required operational signals:

- CI job names must remain stable enough for branch protection.
- Stage1/stage2 self-host trace can be enabled through `BUNKER_SELF_HOST_TRACE`.
- Self-host outputs must continue emitting capability, AST, type graph, symbol table, resolver, and typecheck reports while those reports are part of the AI-agent contract.
- Release artifacts must include compiler binary, self-host generated source/artifacts, runtime header, checksums, and CI run link.
- Failures in CI should preserve enough trace to identify whether the failure is parse, typecheck, codegen, runtime, timeout, or artifact mismatch.

## 16. Implementation Plan

### Phase 0: Baseline Lock

- Keep `main` green.
- Protect `main` with required CI checks.
- Keep the PR template checklist.
- Treat GitHub Actions run `28668326471` as the latest verified baseline as of this spec.

### Phase 1: Runtime And Stdlib Substrate

- Finish string, Vec, HashMap, Result, Option, file I/O, JSON writing, CLI args, logging, serialization, and runtime ABI version checks required by the compiler.
- Add fixture coverage through generated and stage2 compilers.
- Keep runtime APIs minimal until compiler needs are clear.

### Phase 2: Typed Self-Host Core

- Add token/node/type/pattern enums.
- Move AST node records to Bunker structs/enums.
- Preserve compatibility adapters only at boundaries.
- Extend self-host boundary guards for every removed raw access pattern.

### Phase 3: Generics And ADTs

- Implement real generic collections.
- Implement user-defined ADTs.
- Re-express Option/Result as ordinary language/runtime constructs where feasible.
- Add ADT exhaustiveness and pattern typing.

### Phase 4: Compiler Pass Separation

- Separate resolver, typechecker, and codegen inference responsibilities.
- Add HIR or Typed IR if it removes duplicated ad hoc inference.
- Keep Rust and self-host parity tests for selected fixtures.

### Phase 5: Unified Diagnostics

- Define one diagnostic schema in docs.
- Emit that schema from Rust and self-host paths.
- Add parse recovery and multi-error semantic reports.
- Add safe suggested edits beyond parse punctuation cases.

### Phase 6: Memory And Resource Safety

- Decide borrow/reference model.
- Define arena and destructor/drop behavior.
- Add compiler workload memory caps and leak/stress CI gates.
- Prove cleanup behavior for return, break, continue, and error propagation.

### Phase 7: Primary Self-Host Compiler

- Document stage0/stage1/stage2 chain.
- Add reproducible artifacts and checksums.
- Make self-host compiler the normal compiler path for the supported subset.
- Keep Rust compiler as bootstrap/reference until retirement criteria are met.

### Phase 8: Production Release

- Freeze supported language version.
- Publish release artifacts.
- Add migration notes and public docs for supported features.
- Defer package manager, LSP, LLVM, embedded targets, and larger ecosystem work unless needed for the release.

## 17. Testing Strategy

Every phase requires:

- Positive `.bkr` fixture.
- Negative `.bkr` fixture when diagnostics are involved.
- Rust compiler check when Rust still owns the behavior.
- Self-host generated compiler check when self-host supports the behavior.
- Stage1/stage2 check for compiler-critical behavior.
- Resource timeout for code-producing or runtime tests.
- JSON diagnostic assertions for errors.
- Golden comparison where generated output or diagnostics must match.

Additional gates:

- Fuzz lexer/parser/typechecker after parser recovery lands.
- Property tests for type compatibility, pattern exhaustiveness, and collection operations.
- Stress tests for large modules and import graphs.
- Leak tests for long-running compiler workloads.

## 18. Rollout, Migration & Rollback

Rollout:

1. Land each phase behind existing Rust behavior or explicit self-host capability flags.
2. Keep compatibility adapters until stage1/stage2 gates prove the typed replacement.
3. Remove adapters only with CI guards preventing reintroduction.
4. Promote self-host as primary only after release artifacts and docs prove reproducibility.

Migration:

- Keep Rust and self-host behavior side by side until parity gates pass.
- Update examples and docs with every surface syntax or CLI change.
- Maintain known-difference logs for temporary parity gaps.

Rollback:

- Revert the smallest phase slice.
- Keep raw compatibility boundary for one additional phase if needed.
- Never rollback by disabling self-host smoke on `main`; move failing experimental coverage to manual canary only when it is clearly non-release-critical.

## 19. Documentation Updates

Required docs:

- Update `docs/IMPLEMENTATION_TRACKER.md` after each completed gate.
- Add a stage0/stage1/stage2 bootstrap document.
- Add diagnostic schema documentation.
- Add memory/resource model documentation.
- Add supported language version and production subset documentation.
- Update `README.md` when local command policy changes.
- Update `docs/EXAMPLES.md` for new syntax and stdlib behavior.
- Add release process documentation once artifacts are reproducible.

## 20. Acceptance Criteria

Bunker is "100% done" for this spec only when all are true:

- GitHub Actions is green on `main` with required checks.
- Self-host compiler builds itself through documented stage0/stage1/stage2 flow.
- The self-host compiler is the normal compiler path for the supported production subset.
- Rust is no longer required for normal compiler development except bootstrap/reference use.
- Compiler data structures use Bunker structs/enums/generics instead of raw bootstrap handles outside compatibility-free internals.
- Real generics and ADTs support compiler data structures and user code.
- Diagnostics share one documented JSON schema across Rust and self-host paths.
- Memory/resource model is documented, enforced, and tested with leak/stress gates.
- Stdlib APIs needed by compiler and production subset are typed, documented, and tested.
- Safety policies for UB, overflow, bounds, runtime failure, unsafe, and sandboxable APIs are documented and tested.
- Release artifacts are reproducible, checksummed, and downloadable from CI or releases.
- Existing fixture suite and new production gates pass without disabling coverage.

## 21. Risks & Mitigations

| Risk | Impact | Mitigation |
|---|---|---|
| Raw bootstrap layout persists too long. | Compiler remains fragile and hard for AI agents to modify. | Prioritize typed compiler structures before new features. |
| Generics/ADTs balloon scope. | Self-host work stalls. | Implement the minimum needed for compiler structures first. |
| Diagnostics diverge between Rust and self-host. | AI repair loops become unreliable. | Define one schema and gate both paths. |
| Self-host compiler memory growth returns. | Local safety policy and CI stability suffer. | Keep resource caps, traces, and leak/stress gates. |
| Rust and self-host behavior drift. | Rust removal becomes risky. | Add golden parity tests and known-difference retirement dates. |
| CI cost grows. | Verification slows or becomes expensive. | Keep heavy canaries manual until needed for release gates. |
| Docs overstate completeness. | Users trust unsupported behavior. | Update README/tracker only when CI evidence exists. |

## 22. Open Questions

- Should HIR and Typed IR be introduced before or after raw AST records are replaced?
- What is the minimum generics/ADT subset needed to rewrite compiler data structures cleanly?
- Should Option/Result be ordinary ADTs before Rust removal, or can that wait until after primary self-hosting?
- What borrow/reference model is simplest while still supporting compiler and systems workloads?
- Should the production backend be self-host C first, Cranelift via Rust bridge, or a staged combination?
- What release name/version marks "primary self-host compiler"?
- Which tooling is mandatory for first production release: formatter only, or formatter plus `bunker test`?

## 23. Assumptions

- `docs/IMPLEMENTATION_TRACKER.md` remains the authoritative backlog.
- GitHub Actions is available and funded for required CI gates.
- The current CI-only local execution policy remains in force until memory/resource safety is proven.
- The first production release can have a documented supported subset rather than every aspirational language feature.
- Existing Rust implementation may remain as a reference until self-host compiler parity is proven.
- External package registry, LSP, LLVM backend, and embedded profile are not prerequisites for primary self-hosting unless the tracker is updated.

## 24. Appendix

### A. Current Green CI Baseline

GitHub Actions run `28668326471` completed successfully on 2026-07-03 with:

- `Rust windows-latest`
- `Rust ubuntu-latest`
- `Rust macos-latest`
- `Bunker language tests`
- `Self-host boundary guards`
- `Self-host smoke inputs`
- `Self-host incremental canary`

### B. Next PR-Sized Work Candidates

1. Add stage0/stage1/stage2 bootstrap documentation.
2. Add a diagnostic schema doc and link every current `BUNKER_*_JSON` report.
3. Add CI guard for any remaining raw token/node kind use outside approved self-host boundaries.
4. Replace one narrow raw AST record family with a Bunker struct/enum-backed representation.
5. Add typed collection semantics needed by that replacement.
6. Add golden parity for the affected fixture subset.

### C. Progress Interpretation

The estimates in this spec are not release claims. They are planning estimates derived from current gates and tracker status:

- Bootstrap viability is high because stage1/stage2 smoke works.
- Production readiness is lower because many P0/P1 type, memory, diagnostics, tooling, and safety gates remain TODO or PARTIAL.
- Primary self-hosting is lower because Rust still owns the production compiler and bootstrap driver.
