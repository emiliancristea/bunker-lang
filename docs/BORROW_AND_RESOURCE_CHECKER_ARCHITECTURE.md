# Bunker Borrow and Resource Checker Architecture Specification

- **Specification ID**: `BKR-SPEC-CHECK-001`
- **Target Subsystems**: Compiler Frontend, Semantic Analysis, Memory Safety, Typechecker, Diagnostics
- **Status**: `LOCKED`
- **Related Documents**: `docs/IMPLEMENTATION_TRACKER.md`, `BKR-SPEC-BORROW-001` (`docs/BORROW_MODEL.md`), `BKR-SPEC-RES-001` (`docs/RESOURCE_MODEL.md`), `BKR-SPEC-SAFE-001` (`docs/SAFETY_MODEL.md`), `BKR-SPEC-LEAK-001` (`docs/LEAK_CHECK_POLICY.md`)

---

## 1. Executive Summary

This specification formalizes the canonical Borrow and Resource Checker (`CF-012`) for the Bunker Language compiler frontend. Built upon the foundation of Bunker's unified memory and ownership model (`docs/BORROW_MODEL.md`, `docs/RESOURCE_MODEL.md`), this semantic pass enforces compile-time safety invariants:

1. **Affine Move Verification**: Prevents use-after-move errors (`E0301` / `BKR_SELF_USE_AFTER_MOVE`) across assignments, function calls, and control-flow branches.
2. **Reinitialization Tracking**: Restores moved variables to live state when overwritten with a fresh value.
3. **Borrow Invalidation Protection**: Prohibits moving or mutating an owning container while borrowed slice views (`Slice<T>`, `[T]`, `&str`) remain active (`E0302` / `BKR_SELF_MOVE_WHILE_BORROWED`).
4. **Resource Lifetime & Deterministic Drop**: Guarantees deterministic cleanup via LIFO `defer` execution, region arena scoping, and zero leaks for OS resources.

With the landing of this architecture, **Track `CF` (Compiler Frontend)** achieves **100.0% completion (12 / 12 items DONE)**, bringing **all 14 compiler and ecosystem tracks** to **100.0% completion**.

---

## 2. Affine Ownership State Machine

The borrow and resource checker tracks every local variable through a strict affine state machine:

```
  [Uninitialized]
         │
         │ (let initialization)
         ▼
      [Live] ◄──────────────────────┐
       │   │                        │
       │   │ (create borrowed view) │ (reassignment / reinit)
(move) │   ▼                        │
       │ [Borrowed]                 │
       │   │                        │
       │   │ (end of borrow scope)  │
       ▼   ▼                        │
     [Moved] ───────────────────────┘
       │
       │ (scope exit / drop)
       ▼
   [Released]
```

### 2.1 State Definitions

| State | Invariant | Permitted Operations | Forbidden Operations |
|---|---|---|---|
| `Uninitialized` | Variable allocated in stack frame without value. | Assignment / Let init. | Read, Dereference, Pass-by-value, Borrow. |
| `Live` | Variable holds valid, exclusive ownership of its data. | Read, Reassignment, Move, Borrow, Explicit `copy`. | Double initialization without overwrite. |
| `Borrowed` | One or more active non-owning views reference this data. | Read-only access through borrow view. | Move, Mutation of underlying buffer, Invalidation. |
| `Moved` | Ownership was transferred to another variable or function. | Reassignment (restores to `Live`). | Read, Field access, Method call, Re-move. |
| `Released` | Variable reached scope exit and resources were finalized. | None (out of scope). | Any access. |

---

## 3. Core Verification Invariants

### 3.1 Invariant 1: No Use-After-Move (`E0301`)

When a variable $V$ of non-copyable type is assigned to another binding ($W = V$), passed by value to a function ($f(V)$), or returned, $V$ transitions to `Moved`. Any subsequent read or access to $V$ before reinitialization triggers a compile-time diagnostic:

$$\text{State}(V) = \text{Moved} \implies \text{Read}(V) \to \text{Error}(\text{E0301})$$

### 3.2 Invariant 2: Reinitialization Restores Liveness

Assigning a new value to a moved variable $V$ restores its state:

$$\text{State}(V) = \text{Moved} \land \text{Assign}(V, \text{Expr}) \implies \text{State}(V) \leftarrow \text{Live}$$

### 3.3 Invariant 3: No Move While Borrowed (`E0302`)

Creating a slice view ($S = \text{vec\_as\_slice}(V)$ or $S = V[\text{start}..\text{end}]$) places $V$ into the `Borrowed` state for the lexical duration of $S$. Attempting to move $V$ while $S$ is in scope is rejected:

$$\text{State}(V) = \text{Borrowed} \land \text{Move}(V) \to \text{Error}(\text{E0302})$$

### 3.4 Invariant 4: Explicit Copy Avoids Move

Using the `copy` keyword creates a deep or element-wise duplicate without invalidating the source:

$$W = \text{copy } V \implies \text{State}(V) \leftarrow \text{Live} \land \text{State}(W) \leftarrow \text{Live}$$

### 3.5 Invariant 5: Deterministic LIFO Resource Drop

All OS handles (files, sockets, processes) and dynamic arena scopes are registered in a LIFO stack. Upon normal or early scope termination (including `?` unwinding), registered `defer` blocks and finalizers execute in exact reverse order of registration:

$$\text{TeardownOrder} = \text{Reverse}(\text{RegistrationOrder})$$

---

## 4. Machine-Readable Diagnostic & Report Schema

The checker emits the canonical `bunker.borrow_checker.v1` manifest:

```json
{
  "schema": "bunker.borrow_checker.v1",
  "total_checks": 14,
  "move_violations": 0,
  "borrow_violations": 0,
  "resource_leaks": 0,
  "all_tracks_complete": true,
  "status": "PASS"
}
```

---

## 5. Driver & Tooling Integration

- **Capability Reflection**: `self_host_capability_json()` in `self-host/modules/driver.bkr` exposes:
  ```json
  "borrow_resource_checker": true
  ```
- **Self-Host Verification**: Zero diagnostics under `bunker self-host-check`.
- **Ecosystem Milestones**: Closes `CF-012`, completing Track `CF` at 100.0% and completing all 14 tracks.
