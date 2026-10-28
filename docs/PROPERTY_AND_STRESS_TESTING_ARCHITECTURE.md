# Bunker Property-Based and Stress Testing Architecture Specification

- **Specification ID**: `BKR-SPEC-TEST-002`
- **Target Subsystems**: Test Runner, Standard Library, Typechecker, Compiler Frontend, Driver, Runtime
- **Status**: `LOCKED`
- **Related Documents**: `BKR-SPEC-SAFE-001` (`docs/SAFETY_MODEL.md`), `BKR-SPEC-SEC-001` (`docs/SANDBOX_SECURITY_MODEL.md`), `BKR-SPEC-TOOL-002` (`docs/TEST_RUNNER_AND_DOC_GENERATOR_ARCHITECTURE.md`), `BKR-SPEC-TEST-001` (`docs/FUZZING_AND_DIFFERENTIAL_TESTING_ARCHITECTURE.md`)

---

## 1. Executive Summary

This specification establishes the architectures for property-based invariant verification and large-scale compiler stress testing in Bunker:
1. **Property-Based Testing Framework (`S-010`)**: An automated invariant testing system (`bunker test --property`, schema `bunker.prop.v1`) that validates algebraic laws, type system soundness, and collection semantics across randomly generated input spaces with integrated counterexample shrinking.
2. **Compiler Stress Testing Engine (`S-011`)**: A compiler scalability and load-verification suite (`bunker build --stress`, schema `bunker.stress.v1`) testing the lexer, parser, typechecker, and code generator under massive workloads (10,000+ AST nodes, deep call recursion, heavy symbol tables), verifying linear throughput and strict memory bounds (<256MB peak).

---

## 2. Property-Based Testing Architecture (`S-010`)

### 2.1 Theoretical Foundations & Invariant Categories

Property testing verifies that universally quantified mathematical and operational properties hold for all inputs $\forall x \in \text{Domain}: P(x) = \text{true}$:

| Invariant Class | Formal Law Tested | Verification Target |
|---|---|---|
| **Arithmetic Laws** | Commutativity: $a + b = b + a$<br>Associativity: $(a + b) + c = a + (b + c)$<br>Distributivity: $a \cdot (b + c) = a \cdot b + a \cdot c$ | Integer arithmetic, modular wrapping rules (`S-003`). |
| **Bitwise Laws** | Involution: $\sim(\sim a) = a$<br>De Morgan's: $\sim(a \ \& \ b) = (\sim a) \mid (\sim b)$<br>Idempotence: $a \ \& \ a = a$, $a \mid a = a$ | Bitwise operators, mask calculations. |
| **Collection Invariants** | Size Monotonicity: $\text{len}(\text{push}(v, x)) = \text{len}(v) + 1$<br>LIFO Preservation: $\text{pop}(\text{push}(v, x)) = x$<br>Map Idempotence: $\text{get}(\text{insert}(\text{insert}(m, k, v), k, v), k) = v$ | `Vec<T>`, `HashMap<K, V>`, slice views. |
| **Round-Trip Serialization** | Invertibility: $\text{deserialize}(\text{serialize}(x)) \equiv x$ | AST JSON reports, diagnostics, lockfiles. |

### 2.2 Input Generators & Shrunk Counterexamples

- **Generators (`Arbitrary<T>`)**: Provide deterministic pseudo-random sequence generation with distribution biasing towards boundary values (`0`, `1`, `-1`, `MAX_I64`, `MIN_I64`, empty strings, null terminators).
- **Shrinking Protocol**: When a property $P(x)$ fails for a generated input $x$, the runner enters a binary-search shrinking loop:
  1. Reduce magnitude (halving integers toward 0).
  2. Shorten collection lengths and string sizes.
  3. Simplify AST node nesting depth.
  4. Yield the smallest irreducible counterexample triggering $P(x) = \text{false}$.

### 2.3 Property Report Schema (`bunker.prop.v1`)

```json
{
  "schema": "bunker.prop.v1",
  "properties_tested": 15,
  "samples_per_property": 1000,
  "total_executions": 15000,
  "failures": 0,
  "shrunk_counterexamples": [],
  "status": "PASS"
}
```

---

## 3. Compiler Stress Testing Architecture (`S-011`)

### 3.1 Workload Dimensions & Scaling Limits

The stress harness constructs synthetic high-density codebases to verify that the compiler scales predictably without exponential blowup or unbounded memory consumption:

```
Workload Category          Target Magnitude       Resource Constraint
------------------------------------------------------------------------
AST Node Volume            10,000+ Nodes          Parse time < 250 ms
Symbol Table Declarations  1,000+ Functions       Resolve time < 100 ms
Expression Tree Depth      128 Nested Binary Ops  No stack overflow
Typecheck Unification      5,000 Identifiers      Typecheck < 200 ms
Heap Memory Watermark      Large Multi-File AST   Peak Heap < 256 MB
```

### 3.2 Invariants Enforced Under Stress

1. **Memory Ceiling**: Compiler memory must remain bounded under massive workloads via deterministic arena allocation and move semantics.
2. **Linear Time Complexity ($O(N)$)**: Execution duration of lexing, parsing, and typechecking must scale linearly with token and AST node count.
3. **Absence of Stack Overflow**: Expression evaluation, symbol resolution, and C code generation must use explicit worklist stacks or bounded recursion.
4. **Deterministic Output Integrity**: Code generation under stress must produce bit-for-bit identical C source code regardless of compilation iteration order.

### 3.3 Stress Report Schema (`bunker.stress.v1`)

```json
{
  "schema": "bunker.stress.v1",
  "ast_nodes_generated": 10000,
  "functions_synthesized": 1000,
  "max_expression_depth": 128,
  "total_source_bytes": 524288,
  "parse_elapsed_ms": 112,
  "typecheck_elapsed_ms": 94,
  "codegen_elapsed_ms": 138,
  "peak_memory_mb": 48,
  "status": "PASS"
}
```

---

## 4. Tooling & Driver Integration

- **Capability Reflection**: `self_host_capability_json()` in `self-host/modules/driver.bkr` exposes:
  ```json
  "property_testing": true,
  "stress_testing": true
  ```
- **CLI Commands**:
  - `bunker test --property`: Runs algebraic property suites with automated shrinking.
  - `bunker build --stress`: Runs compiler throughput and memory stress tests.
- **Self-Host Verification**: Zero diagnostics under `bunker self-host-check`.
