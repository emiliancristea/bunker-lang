# Bunker Fuzzing and Differential Testing Architecture Specification

- **Specification ID**: `BKR-SPEC-TEST-001`
- **Target Subsystems**: Compiler Frontend, Typechecker, C Codegen, Rust Reference Compiler, Self-Host Compiler, Test Runner
- **Status**: `LOCKED`
- **Related Documents**: `BKR-SPEC-SAFE-001` (`docs/SAFETY_MODEL.md`), `BKR-SPEC-SEC-001` (`docs/SANDBOX_SECURITY_MODEL.md`), `BKR-SPEC-TOOL-002` (`docs/TEST_RUNNER_AND_DOC_GENERATOR_ARCHITECTURE.md`), `BKR-SPEC-TOOL-006` (`docs/COVERAGE_AND_BENCHMARK_ARCHITECTURE.md`)

---

## 1. Executive Summary

This specification establishes the production testing architectures for compiler reliability and semantic soundness in Bunker:
1. **Fuzzing Harness Engine (`S-008`)**: Structured, coverage-guided and grammar-directed fuzzing infrastructure (`bunker fuzz`, schema `bunker.fuzz.v1`) providing dedicated fuzz targets for the lexer, parser, and typechecker, automated byte mutation strategies, seed corpus management, crash artifact minimization, and C ABI compatibility (`LLVMFuzzerTestOneInput` / `__bkr_fuzz_target`).
2. **Differential Testing Parity Engine (`S-009`)**: Systematic dual-pipeline comparison engine (`bunker test --differential`, schema `bunker.diff.v1`) executing Bunker programs side-by-side across the reference Rust compiler (Cranelift JIT) and the pure Bunker self-host compiler (C codegen + host C toolchain), verifying runtime output parity, exit code parity, AST structure congruence, and diagnostic error code alignment on negative test cases.

Together, these testing facilities provide continuous verification that the Bunker compiler and runtime eliminate undefined behavior, resist adversarial or corrupt inputs, and maintain 100% behavioral equivalence across compilation backends.

---

## 2. Fuzzing Harness Architecture (`S-008`)

### 2.1 Target Subsystems & Fuzz Targets

The fuzzing engine provides three isolated fuzz targets targeting each stage of compilation:

| Target ID | Subsystem | Invariant Under Test | Expected Failure Modes Handled |
|---|---|---|---|
| `fuzz_lexer` | Lexer (`lexer.bkr`, `lexer.rs`) | Any arbitrary byte sequence must cleanly produce a token stream or emit structured lexer error `E01xx`. Process must never segfault, panic, or infinite-loop. | Malformed UTF-8, unclosed string/char literals, runaway numeric tokens, nested control characters, zero-byte sequences. |
| `fuzz_parser` | Parser (`parser.bkr`, `parser.rs`) | Any valid or invalid token sequence must produce an AST or emit structured parse error `E02xx`. Process must never stack-overflow on deep nesting or panic on unexpected EOF. | Unbalanced delimiters (`(`, `[`, `{`), deeply nested expressions (>128 depth), missing semicolons, premature EOF, keyword misplacements. |
| `fuzz_typecheck` | Typechecker (`typecheck.bkr`, `typeck.rs`) | Any parsed AST must typecheck cleanly or emit structured type error `E03xx` / `E04xx`. Process must terminate within bounded steps without cycle hangs. | Cyclic type aliases, recursive ADT payloads, infinite generic instantiation, mismatched argument arity/types, invalid traits. |

### 2.2 Mutation Strategies & Seed Corpus

The fuzzer operates with both raw byte mutations and grammar-aware structural mutations:
- **Bit Inversion**: Inverting single bits or nibbles across the input stream to exercise character boundary validation.
- **Byte Splicing & Insertion**: Inserting known syntax tokens (keywords, punctuation, delimiters) or splicing chunks from adjacent corpus entries.
- **Dictionary Mutation**: Injecting keywords (`kernel`, `struct`, `fn`, `match`, `Option`, `Result`), operators (`?`, `as`, `copy`), and boundary values (`9223372036854775807`, `-9223372036854775808`).
- **Delimiter Balancing**: Randomly truncating or inserting closing brackets to probe parser recovery synchronization.
- **Corpus Directory**: Initial seed inputs reside in `tests/fuzz/corpus/` containing canonical minimal syntax constructs.

### 2.3 Crash Capture and Minimization

When an input causes an unexpected failure (process signal, non-zero uncaught exit, or divergence from structured error conventions):
1. **Crash Isolation**: The failing input is immediately written to `.bkr.crash/{target}_{timestamp}_{hash}.bkr`.
2. **Minimization Loop (Delta Debugging)**: The fuzzer iteratively removes bytes, spans, and lines from the input, re-running the target until the smallest input reproducing the exact crash signature is identified.
3. **Reproducer Output**: Emits a standalone `.bkr` file with an execution summary header.

### 2.4 Fuzz Report Schema (`bunker.fuzz.v1`)

```json
{
  "schema": "bunker.fuzz.v1",
  "target": "fuzz_parser",
  "iterations": 100000,
  "execs_per_sec": 14200,
  "corpus_size": 248,
  "crashes": 0,
  "timeouts": 0,
  "unique_features": 3812,
  "coverage_edges": 12450,
  "elapsed_ms": 7042
}
```

---

## 3. Differential Testing Architecture (`S-009`)

### 3.1 Dual-Pipeline Execution Model

Differential testing validates that the Rust reference compiler and the pure Bunker self-host compiler yield identical behaviors for any valid program:

```
                  ┌──────────────────────┐
                  │ Source Program (.bkr)│
                  └──────────┬───────────┘
                             │
            ┌────────────────┴────────────────┐
            ▼                                 ▼
   [ Rust Compiler ]                 [ Self-Host Compiler ]
   (Cranelift JIT)                   (C Codegen -> Clang)
            │                                 │
            ▼                                 ▼
  Runtime Execution A               Runtime Execution B
  (Exit code, stdout, stderr)       (Exit code, stdout, stderr)
            │                                 │
            └────────────────┬────────────────┘
                             │
                             ▼
              [ Differential Comparator ]
              (Parity Check & Report)
```

### 3.2 Parity Dimensions Verified

The differential comparator assesses parity across five explicit dimensions:

1. **Exit Code Parity**: Both backends must terminate with the identical integer exit code (e.g., return code 42 for successful test fixtures; code 101 on invariant panic).
2. **Standard Output / Error Equivalence**: String outputs from `println`, `print`, and diagnostics must match byte-for-byte (accounting for line-ending normalization).
3. **AST Structure Congruence**: On `--ast-parity`, compare normalized JSON AST dumps from `bunker parse --ast-json` and self-host `ast_report.bkr`.
4. **Negative Diagnostic Parity**: On invalid test inputs (e.g. `tests/*_BAD.bkr`), both compilers must reject the source code and emit matching diagnostic codes (e.g. `E0301`, `E0402`).
5. **Memory and Side Effect Invariants**: Verification that allocations, array bounds checks, and cleanup routines operate identically.

### 3.3 Differential Report Schema (`bunker.diff.v1`)

```json
{
  "schema": "bunker.diff.v1",
  "total_fixtures": 302,
  "parity_matches": 302,
  "divergences": 0,
  "backends": {
    "reference": "bunker-cli (rust/cranelift)",
    "target": "bunker self-host-compile (c99/clang)"
  },
  "status": "PASS"
}
```

---

## 4. Driver & Tooling Integration

- **Capability Reflection**: `self_host_capability_json()` in `self-host/modules/driver.bkr` exposes:
  ```json
  "fuzzing_harness": true,
  "differential_testing": true
  ```
- **CLI Commands**:
  - `bunker fuzz <target>`: Executes the specified fuzz target with corpus mutation.
  - `bunker test --differential`: Runs test fixtures across both JIT and C-backend to assert behavioral parity.
- **Zero Diagnostics Invariant**: All fuzz and differential harness modules strictly adhere to self-host compiler typing, with 0 diagnostics under `bunker self-host-check`.
