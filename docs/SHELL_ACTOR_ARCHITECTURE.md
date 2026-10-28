# Bunker Shell Actor Architecture Specification

- **Specification ID**: `BKR-SPEC-SHELL-001`
- **Target Subsystems**: Shell Layer, Actor Model, Concurrency, Message Passing, Runtime ABI
- **Status**: `LOCKED`
- **Related Documents**: `docs/ARCHITECTURE.md`, `docs/RUST_MIGRATION_MAP.md`, `docs/TECHNICAL_SPEC.md`, `docs/IMPLEMENTATION_TRACKER.md`

---

## 1. Executive Summary

This specification formalizes the **pure-Bunker Shell Layer Architecture** (`BKR-SPEC-SHELL-001`), replacing the legacy Rust prototype (`bunker-cli/src/shell_runtime.rs`) with a self-hosted, pure-Bunker actor model engine (`self-host/modules/shell.bkr`) and ISO C11 runtime bindings (`self-host/runtime.h`).

Bunker structures applications into three distinct layers:
1. **Kernel Layer**: Pure, verified deterministic algorithms and systems code.
2. **Shell Layer**: Concurrent agents, message passing, asynchronous queues, and state mutation.
3. **View Layer**: Declarative reactive user interfaces.

```
┌─────────────────────────────────────────────────────┐
│                    VIEW LAYER                        │
│         Declarative UI (Graphics/Embedded)          │
├─────────────────────────────────────────────────────┤
│                   SHELL LAYER                        │
│        Agents + Message Passing (Actor Model)       │
├─────────────────────────────────────────────────────┤
│                  KERNEL LAYER                        │
│     Pure Functions + Verified Math (Rust-killer)    │
└─────────────────────────────────────────────────────┘
```

The Shell Layer provides **shared-nothing actor isolation**: agents communicate exclusively through immutable messages passed to mailboxes.

---

## 2. Actor Model Semantics & State Machine

### 2.1 The Four Invariants of Bunker Shell

1. **Shared-Nothing State Isolation**: Each agent owns private mutable state. No agent can read or write another agent's memory directly.
2. **Asynchronous Message Passing**: Agents communicate by sending messages (`send <message> to <Agent>;`). Messages are appended to FIFO queues.
3. **Deterministic Discrete Event Stepping**: The Shell scheduler processes messages step-by-step in predictable order, guaranteeing 100% reproducible debugging and test replay.
4. **Kernel Bridge**: Agents execute pure computational logic by invoking pure Kernel functions (`use Kernel.func with param=val;`).

### 2.2 Agent State Lifecycle

```
[ Unregistered ] ──> [ Idle / Awaiting Message ] ──> [ Processing Message ]
                             ▲                               │
                             │ (new messages queued)         ▼
                             └──────────────────────── [ Message Dispatched ]
```

---

## 3. Pure Bunker Data Structures (`self-host/modules/shell.bkr`)

```bunker
struct ShellMessage {
    target: str,
    source: str,
    message: str,
    payload: i64,
}

struct ShellAgent {
    name: str,
    state_int: HashMap<str, i64>,
    state_str: HashMap<str, str>,
}

struct ShellSystem {
    agents: Vec<str>,
    queue_target: Vec<str>,
    queue_source: Vec<str>,
    queue_message: Vec<str>,
    queue_payload: Vec<i64>,
    step_count: i64,
    max_steps: i64,
    terminated: bool,
}
```

---

## 4. Machine-Readable Shell Manifest Schema (`bunker.shell.v1`)

```json
{
  "schema": "bunker.shell.v1",
  "status": "COMPLETED",
  "steps_executed": 8,
  "max_steps": 50000,
  "terminated": true,
  "active_agents": 2,
  "queue_depth": 0,
  "agents": [
    {
      "name": "PingAgent",
      "state": { "count": 3 }
    },
    {
      "name": "PongAgent",
      "state": {}
    }
  ]
}
```

---

## 5. Tooling & Verification Contract

- **Pure Bunker Module**: `self-host/modules/shell.bkr`
- **C Runtime ABI**: `bkr_actor_send`, `bkr_actor_step`, `bkr_actor_run` in `self-host/runtime.h`.
- **Positive Test Fixtures**:
  - `tests/300_pure_bunker_shell_actor.bkr` (returns 42)
  - `tests/301_shell_agent_ping_pong.bkr` (returns 42)
