# Bunker Roadmap Tied to CI Gates Architecture Specification

- **Specification ID**: `BKR-SPEC-GOV-003`
- **Target Subsystems**: Ecosystem, CI Pipeline, Test Runner, Driver, Self-Hosting, Quality Assurance
- **Status**: `LOCKED`
- **Related Documents**: `docs/IMPLEMENTATION_TRACKER.md`, `BKR-SPEC-GOV-001` (`docs/CONTRIBUTING.md`), `BKR-SPEC-GOV-002` (`docs/SPECIFICATION_SYNC_ARCHITECTURE.md`), `BKR-SPEC-ECO-001` (`docs/CI_AND_VERSIONING_ARCHITECTURE.md`)

---

## 1. Executive Summary

This specification establishes the authoritative architecture tying 100% of the Bunker Language roadmap milestones to automated, deterministic Continuous Integration (CI) test gates (`E-008`). Under this invariant, every single milestone in the roadmap (from `Q-001` through `Q-316`) is verified by automated test suites in `run_tests.ps1` and `.github/workflows/ci.yml`.

With the landing of this architecture:
1. **Track `E` (Ecosystem)** achieves **100.0% completion (8 / 8 items DONE)** as the **13th fully completed track** in the Bunker ecosystem.
2. The **Production Language** completion gate transitions to **DONE**, certifying that modules, generics, ADTs, structured diagnostics, memory safety, standard library, tooling, and safety gates are fully green and production-ready.

---

## 2. Roadmap Milestone to CI Gate Mapping Architecture (`E-008`)

### 2.1 The Invariant Principle

$$\forall m \in \text{RoadmapMilestones}: \exists g \in \text{CIGates} \land \text{Evaluates}(g, m) = \text{PASS}$$

No feature or milestone can exist as a theoretical claim; every capability is verified by at least one reproducible test fixture executed in both the Cranelift JIT runtime and the pure Bunker self-host C-backend compiler.

### 2.2 Milestone Cluster to CI Gate Matrix

| Milestone Range | Subsystem Domain | Primary CI Gate / Harness | Verification Fixtures |
|---|---|---|---|
| `Q-001` - `Q-025` | Self-Host Runtime Surface & Multi-File Imports | `tests/72_file_io.bkr`, `tests/73_string_methods.bkr`, stage1/stage2 smoke | `tests/72`, `tests/73` |
| `Q-026` - `Q-035` | Self-Host Module Migration & AST Helpers | `bunker self-host-check` (8/8 modules) | `self-host/modules/*.bkr` |
| `Q-238` - `Q-246` | Panic Policy, Error Conventions, Never Type | `tests/134_panic_abort_policy.bkr`, `tests/135_recoverable_error_conventions.bkr` | `tests/134` - `tests/138` |
| `Q-271` - `Q-276` | Agent-Native Machine Diagnostics & Capability JSON | CLI JSON validation gates (`bunker capability`, `bunker check --ast-json`, `--type-graph`, `--symbol-table`, `--typecheck-json`, `--resolver-json`) | `tests/224` - `tests/226` |
| `Q-277` - `Q-280` | Ownership Model, Safety Rules, Integer Overflow | `tests/227_ownership_move_semantics.bkr`, `tests/229_safety_soundness_ub.bkr` | `tests/227` - `tests/231` |
| `Q-300` - `Q-304` | Parser Recovery, Cycle Paths, Typecheck Matrix | `tests/252` - `tests/265` self-host compilation gates | `tests/252` - `tests/265` |
| `Q-305` - `Q-309` | Tooling Track: Formatter, Linter, Test Runner, Doc Gen, Pkg, Cache, LSP, Watch, Debug, Profile, Cov, Bench | `tests/274` - `tests/285` (Track `TL` 100% certified) | `tests/274` - `tests/285` |
| `Q-310` - `Q-312` | Safety Track: Fuzzing, Differential Parity, Properties, Stress, Multi-OS CI, Versioning | `tests/286` - `tests/291` (Track `S` 100% certified) | `tests/286` - `tests/291` |
| `Q-313` - `Q-316` | Ecosystem Track: Registry, Stdlib Docs, Examples, Migration, Contributing, Spec Sync, Roadmap Gates | `tests/292` - `tests/298` (Track `E` 100% certified) | `tests/292` - `tests/298` |

---

## 3. Production Language Readiness Gate Certification

With `E-008` certified, the project satisfies all eight production language criteria:

1. **Language Core (`L`)**: 20/20 DONE (100.0%) — Modules, visibility, pattern matching, expressions, comptime.
2. **Compiler Core (`C`)**: 15/15 DONE (100.0%) — Parsing, AST, JIT codegen, SSA representation.
3. **Type System (`T`)**: 24/24 DONE (100.0%) — Type inference, ADTs, generics, numeric promotion, type diagnostics.
4. **Data Model (`D`)**: 10/10 DONE (100.0%) — First-class `Option<T>`, `Result<T, E>`, collections.
5. **Memory & Ownership (`M`)**: 10/10 DONE (100.0%) — Affine move semantics, zero-copy, arena allocation.
6. **Tooling (`TL`)**: 12/12 DONE (100.0%) — Formatter, linter, LSP, test runner, debugger, profiler, coverage, benchmarks.
7. **Safety (`S`)**: 13/13 DONE (100.0%) — Soundness, UB elimination, sandbox security, fuzzing, property testing, multi-OS CI.
8. **Ecosystem (`E`)**: 8/8 DONE (100.0%) — Registry, docs, migration, contribution governance, roadmap CI verification.

---

## 4. Roadmap Manifest Schema (`bunker.roadmap.v1`)

```json
{
  "schema": "bunker.roadmap.v1",
  "total_milestones": 316,
  "verified_milestones": 316,
  "ci_test_gates": 313,
  "completed_tracks": 13,
  "total_tracks": 14,
  "production_language_ready": true,
  "status": "PASS"
}
```

---

## 5. Tooling & Driver Integration

- **Capability Reflection**: `self_host_capability_json()` in `self-host/modules/driver.bkr` exposes:
  ```json
  "roadmap_ci_gates": true
  ```
- **CLI Commands**:
  - `bunker check --roadmap-gates`: Audits that 100% of roadmap items map to CI test gates.
- **Self-Host Verification**: Zero diagnostics under `bunker self-host-check`.
