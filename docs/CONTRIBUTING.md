# Bunker Language Contribution and RFC Specification

- **Specification ID**: `BKR-SPEC-GOV-001`
- **Target Subsystems**: Ecosystem, Language Governance, CI Infrastructure, Diagnostic Registry, Tooling
- **Status**: `LOCKED`
- **Related Documents**: `BKR-SPEC-ECO-001` (`docs/CI_AND_VERSIONING_ARCHITECTURE.md`), `BKR-SPEC-DIAG-001` (`docs/DIAGNOSTIC_CODES.md`), `docs/IMPLEMENTATION_TRACKER.md`

---

## 1. Executive Summary

This specification establishes the canonical governance process for proposing, designing, implementing, and qualifying changes to the Bunker programming language. To ensure deterministic evolution and eliminate regressions, every proposed language change must adhere to the **Five-Stage RFC Lifecycle**:

```
[ Stage 1: RFC Design ] ──> [ Stage 2: Diagnostic Allocation ] ──> [ Stage 3: Dual Fixture ]
                                                                             │
[ Stage 5: Multi-OS CI Gate ] <── [ Stage 4: Self-Host Reflection ] <────────┘
```

---

## 2. The Five-Stage Language Feature Lifecycle (`E-006`)

### Stage 1: RFC Design Specification
Every non-trivial modification to syntax, type rules, runtime primitives, or compiler behavior requires a formal Markdown specification in `docs/` adhering to the following structure:
- **Header**: Specification ID (`BKR-SPEC-*`), Target Subsystems, Status (`DRAFT` / `REVIEW` / `LOCKED`).
- **Motivation & Invariants**: The precise problem solved and formal invariants maintained.
- **Syntax & Grammar Specification**: EBNF grammar modifications and token definitions.
- **Type Rules & Semantics**: Type checking unification rules and runtime behavior.
- **Failure Modes & Edge Cases**: Rejection conditions, memory bounds, and security boundaries.

### Stage 2: Diagnostic Code Allocation
If the feature introduces new failure modes or rejection boundaries:
- A unique diagnostic code must be reserved in `docs/DIAGNOSTIC_CODES.md` (`E01xx` - `E08xx`).
- The code must be registered in `BUNKER_DIAGNOSTIC_CODES` in both Rust (`bunker-cli`) and Bunker (`self-host/modules/report_support.bkr`).
- Diagnostics must emit structured metadata: byte span, expected vs found, and actionable repair hints.

### Stage 3: Dual-Fixture Test Requirement
Every language change must contribute a paired set of test fixtures in `tests/`:
1. **Positive Test Fixture (`tests/{N}_{feature}.bkr`)**:
   - Executes the new construct through the self-host C backend (`bkrc run`).
   - Asserts all invariants and returns integer `42` on success.
   - Must be registered in `tests/expected_results.txt` (`<name> <exit code>`).
2. **Negative Test Fixture (`tests/{N}_{feature}_BAD.bkr`)**:
   - Asserts that invalid or corrupt uses of the construct are rejected at compile time.
   - Emits the exact assigned diagnostic code (`E0xxx`).

### Stage 4: Self-Host Capability Reflection
- The feature's capability flag must be registered in `self_host_capability_json()` in `self-host/modules/driver.bkr`.
- If the feature expands the language grammar, both the Rust parser and the self-host parser (`self-host/modules/parser.bkr`) must support it.
- All 8 self-host compiler modules must pass `bunker self-host-check` with **0 diagnostics**.

### Stage 5: Multi-OS CI Gating
- Verification across the full multi-OS matrix (`ubuntu-latest`, `windows-latest`, `macos-latest`).
- `./bkrc run tools/test_runner.bkr` reports 0 unexpected failures.
- Preservation of bit-for-bit Stage 1 / Stage 2 bootstrap fixpoint determinism.
- Enforcement of pure LF line endings (`0x0A`) with zero CRLF contamination.

---

## 3. Contribution Manifest Schema (`bunker.contribute.v1`)

```json
{
  "schema": "bunker.contribute.v1",
  "rfc_id": "RFC-2026-004",
  "feature_name": "const_generics",
  "spec_path": "docs/CONST_GENERICS_SPECIFICATION.md",
  "diagnostics_allocated": ["E0341", "E0342"],
  "fixtures": {
    "positive": "tests/298_const_generics_valid.bkr",
    "negative": "tests/299_const_generics_mismatch_BAD.bkr"
  },
  "self_host_readiness": "PASS",
  "ci_status": "PASS"
}
```

---

## 4. Tooling & Driver Integration

- **Capability Reflection**: `self_host_capability_json()` in `self-host/modules/driver.bkr` exposes:
  ```json
  "contribution_guide": true,
  "spec_sync": true
  ```
- **CLI Commands**:
  - `bunker check --rfc-validate <path>`: Validates an RFC against the five contribution stages.
- **Self-Host Verification**: Zero diagnostics under `bunker self-host-check`.
