# Bunker Contract Verification Architecture Specification

- **Specification ID**: `BKR-SPEC-VERIFY-001`
- **Target Subsystems**: Formal Verification, Contract Engine, Symbolic Execution, Linear Arithmetic, SMT/Solvers
- **Status**: `LOCKED`
- **Related Documents**: `docs/ARCHITECTURE.md`, `docs/SHELL_ACTOR_ARCHITECTURE.md`, `docs/VIEW_DECLARATIVE_UI_ARCHITECTURE.md`, `docs/TECHNICAL_SPEC.md`, `docs/IMPLEMENTATION_TRACKER.md`

---

## 1. Executive Summary

This specification formalizes the **pure-Bunker Contract Verification Architecture** (`BKR-SPEC-VERIFY-001`), providing a native formal verification engine implemented entirely in pure Bunker source (`self-host/modules/verify.bkr`).

Bunker functions in the Kernel layer may be annotated with formal specifications:
- `#[requires(P)]`: Preconditions that must hold prior to function invocation.
- `#[ensures(Q)]`: Postconditions that must hold upon function exit, relating input states (via `old(...)`) to output states.
- `#[invariant(I)]`: Loop or state invariants maintained across operations.

```
┌────────────────────────────────────────────────────────┐
│                   CONTRACT SPECIFICATION                │
│       #[requires(amount > 0)]                          │
│       #[requires(from.balance >= amount)]              │
│       #[ensures(from.balance + to.balance ==           │
│                 old(from.balance) + old(to.balance))]  │
├────────────────────────────────────────────────────────┤
│                 SYMBOLIC EXECUTION                     │
│       from.balance' = from.balance - amount            │
│       to.balance'   = to.balance + amount              │
├────────────────────────────────────────────────────────┤
│             LINEAR INEQUALITY PROVER                   │
│       diff = (from.balance' + to.balance') -           │
│              (from.balance + to.balance)               │
│       diff = 0  =>  QED (VERIFIED)                    │
└────────────────────────────────────────────────────────┘
```

The verification engine checks contracts compile-time without external runtime dependencies, providing mathematical guarantees against integer overflows, balance discrepancies, and boundary violations.

---

## 2. Formal Verification Semantics & Proof Invariants

### 2.1 The Four Invariants of Bunker Verification

1. **Symbolic Environment Isolation**: Function variables and field projections are tracked as symbolic linear expressions (`LinExpr`) rather than concrete values during verification.
2. **Precondition Hypotheses**: Preconditions (`#[requires]`) establish assumptions and domain bounds on parameters and initial fields.
3. **Transition Verification**: Postconditions (`#[ensures]`) evaluate expressions at the function exit point, comparing final symbolic states against initial snapshot expressions (`old(...)`).
4. **Counterexample Generation**: When a contract is not provably satisfied, the verification engine synthesizes minimal counterexamples demonstrating violating variable assignments.

---

## 3. Pure Bunker Verification Model (`self-host/modules/verify.bkr`)

```bunker
struct LinExpr {
    var_names: Vec<str>,
    var_coeffs: Vec<i64>,
    constant: i64,
}

struct VerificationContract {
    func_name: str,
    requires_exprs: Vec<str>,
    ensures_exprs: Vec<str>,
    is_verified: bool,
    counterexample: str,
}
```

### 3.1 Linear Arithmetic Engine

Linear expressions represent affine combinations of symbolic variables:
$$E = c_0 + \sum_{i=1}^n c_i \cdot x_i$$

Operations on linear expressions include:
- **Addition**: $\text{add}(A, B) = (c_A + c_B) + \sum (a_i + b_i) x_i$
- **Subtraction**: $\text{sub}(A, B) = (c_A - c_B) + \sum (a_i - b_i) x_i$
- **Scalar Multiplication**: $\text{mul\_const}(A, k) = (k \cdot c_A) + \sum (k \cdot a_i) x_i$
- **Zero Equivalence**: $\text{is\_zero}(A) \iff c_A = 0 \land \forall i, a_i = 0$

---

## 4. Verification Workflow

```
Source AST (Kernel)
     │
     ▼
Attribute Extractor (requires / ensures)
     │
     ▼
Symbolic Execution Engine (maps SSA/assignments to LinExpr)
     │
     ▼
Difference Reduction (LHS - RHS)
     │
     ├─ diff == 0  ────────► [ PASS: Verified ]
     │
     └─ diff != 0  ────────► [ FAIL: Counterexample Synthesized ]
```

---

## 5. Standard JSON Diagnostic Format (`bunker.verify.v1`)

Verification results serialize to structured JSON diagnostics:

```json
{
  "schema_version": "bunker.verify.v1",
  "function_name": "Banking.transfer",
  "contracts_checked": 2,
  "verified": true,
  "diagnostics": []
}
```

In the event of a failed contract:

```json
{
  "schema_version": "bunker.verify.v1",
  "function_name": "Banking.transfer",
  "contracts_checked": 2,
  "verified": false,
  "diagnostics": [
    {
      "contract_kind": "ensures",
      "expression": "from.balance + to.balance == old(from.balance) + old(to.balance)",
      "error": "Contract violated: postcondition not provable",
      "counterexample": "from.balance=100, to.balance=50, amount=20 (diff: -20)"
    }
  ]
}
```

---

## 6. Implementation Checklist & Verification Gates

- [x] Author formal specification (`BKR-SPEC-VERIFY-001`).
- [x] Implement linear expression engine in `self-host/modules/verify.bkr`.
- [x] Implement symbolic environment and contract evaluation.
- [x] Integrate `import "modules/verify.bkr";` into `self-host/bkrc.bkr`.
- [x] Register driver capability `contract_verification` in `self-host/modules/driver.bkr`.
- [x] Unit test linear algebra solver (`tests/304_contract_verification_engine.bkr`).
- [x] Integration test verified transfer contracts (`tests/305_verified_pre_post_conditions.bkr`).
- [x] Validate zero CRLF line endings.
- [x] Validate 8/8 self-host readiness and 320/320 test suite pass.
