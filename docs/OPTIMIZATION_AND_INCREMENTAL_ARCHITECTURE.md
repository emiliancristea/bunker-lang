# Bunker Optimization and Incremental Compilation Architecture Specification

- **Document ID:** `BKR-SPEC-CGEN-004`
- **Track:** Compiler Backend (`CB`)
- **Milestones Covered:** `CB-007` (P2: Optimization passes), `CB-008` (P2: Incremental compilation)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.capability.v1`, `bunker.optimization.v1`, `bunker.cache.v1`

---

## 1. Executive Summary

This specification formalizes the optimization passes (`CB-007`) and incremental compilation caching architecture (`CB-008`) of the Bunker compiler backend (`self-host/modules/c_codegen.bkr` and `self-host/modules/driver.bkr`).

The optimization pipeline performs safe, sound, compile-time constant evaluation and dead code elimination without altering language semantics. The incremental compilation subsystem implements content-addressed caching over module source fingerprints and dependency graphs, eliminating redundant re-compilation of unchanged translation units.

With this specification and implementation, Track `CB` items `CB-007` and `CB-008` transition to `DONE`.

---

## 2. Compile-Time Optimization Passes (CB-007)

### 2.1 Constant Folding Engine

The compiler backend performs constant folding during AST lowering when both sub-expressions are compile-time constants:

- **Invariant OPT-FOLD-01 (Arithmetic Folding):** Literal integer binary operations are folded into single integer literals:
  - Addition (`+`): `a + b` folds to `a + b` (respecting two's complement modular wrapping).
  - Subtraction (`-`): `a - b` folds to `a - b`.
  - Multiplication (`*`): `a * b` folds to `a * b`.
  - Division (`/`): if `b != 0`, folds to `a / b`. If `b == 0`, folding is bypassed to preserve runtime fail-stop trap.
  - Modulo (`%`): if `b != 0`, folds to `a % b`.
- **Invariant OPT-FOLD-02 (Bitwise Folding):**
  - AND (`&`), OR (`|`), XOR (`^`), left-shift (`<<`), and right-shift (`>>`) over integer literals evaluate at compile time.
- **Invariant OPT-FOLD-03 (Relational & Boolean Folding):**
  - Literal comparisons (`==`, `!=`, `<`, `<=`, `>`, `>=`) fold to boolean literals `true` or `false`.
  - Short-circuit algebraic reductions:
    - `true && expr` folds to `expr`
    - `false && expr` folds to `false` (when `expr` is pure)
    - `false || expr` folds to `expr`
    - `true || expr` folds to `true` (when `expr` is pure)
    - `!true` folds to `false`, `!false` folds to `true`.
- **Invariant OPT-FOLD-04 (Side-Effect Soundness):** Expressions containing function calls, process builtins, or mutating operations are never eliminated or folded prematurely.

### 2.2 Dead Code Elimination (DCE)

- **Invariant OPT-DCE-01 (Constant Branch Pruning):**
  - `if true { then_branch } else { else_branch }` emits only `then_branch`; `else_branch` is completely omitted from the generated C translation unit.
  - `if false { then_branch } else { else_branch }` emits only `else_branch`; `then_branch` is completely omitted.
- **Invariant OPT-DCE-02 (Post-Terminator Pruning):** Statements following an unconditional terminator (`return`, `break`, `continue`) within a basic block are pruned from emitted C, eliminating dead instructions and compiler warnings.

---

## 3. Incremental Compilation & Caching Architecture (CB-008)

### 3.1 Content-Addressed Module Fingerprinting

Incremental compilation avoids rebuilding modules by fingerprinting source code and checking artifact freshness:

1. **Source Hash Calculation:** A 64-bit deterministic hash (FNV-1a) is computed across the normalized UTF-8 bytes of each source module:
   $$H_{i+1} = (H_i \oplus \text{byte}) \times 1099511628211 \pmod{2^{64}}$$
2. **Cache Key Tuple:**
   $$\text{CacheKey} = (\text{module\_path}, \text{source\_hash}, \text{compiler\_version}, \text{target\_backend})$$
3. **Cache Record Schema (`bunker.cache.v1`):**
   ```json
   {
     "schema_version": "bunker.cache.v1",
     "module_path": "modules/typecheck.bkr",
     "source_hash": "a1b2c3d4e5f60718",
     "artifact_path": "target/c/typecheck.c",
     "artifact_size": 156400,
     "dependencies": ["modules/ast.bkr", "modules/constants.bkr"],
     "dependency_hashes": ["f0e1d2c3...", "12345678..."],
     "is_clean": true
   }
   ```

### 3.2 Transitive Invalidation Rules

- **Invariant CACHE-INV-01 (Direct Modification):** If a module's current source hash differs from its cached hash, the module is marked dirty and rebuilt.
- **Invariant CACHE-INV-02 (Transitive Invalidation):** If any module in an import dependency chain is marked dirty, all parent modules that import it directly or indirectly are invalidated and rebuilt.
- **Invariant CACHE-INV-03 (Bypass Rebuild):** If a module and all its transitive dependencies have matching hashes and the output artifact exists on disk, the compilation phase is bypassed, returning the cached artifact immediately.

---

## 4. Capability JSON Integration

The compiler driver exposes optimization and caching capabilities in `bunker.capability.v1`:

```json
{
  "constant_folding": true,
  "dead_code_elimination": true,
  "incremental_compilation_cache": true
}
```

---

## 5. Verification Matrix

| Milestone | Feature | Test Fixture | Expected Result |
|---|---|---|---|
| `CB-007` | Constant Folding & Dead Branch Elimination | `tests/268_constant_folding_optimizations.bkr` | Returns 42 |
| `CB-008` | Incremental Compilation & Cache Invalidation | `tests/269_incremental_compilation_cache.bkr` | Returns 42 |
| `CB-007/8`| Self-Host Compilation Subset | `run_tests.ps1` (`$selfHostSubset`) | 100% Pass Rate |
