# Bunker View Layer Declarative UI Architecture Specification

- **Specification ID**: `BKR-SPEC-VIEW-001`
- **Target Subsystems**: View Layer, Declarative UI, Reactive State Binding, Component Trees, Layouts
- **Status**: `LOCKED`
- **Related Documents**: `docs/ARCHITECTURE.md`, `docs/SHELL_ACTOR_ARCHITECTURE.md`, `docs/TECHNICAL_SPEC.md`, `docs/IMPLEMENTATION_TRACKER.md`

---

## 1. Executive Summary

This specification formalizes the **pure-Bunker View Layer Architecture** (`BKR-SPEC-VIEW-001`), completing the third tier of Bunker's tri-layer architecture (Kernel, Shell, View) directly in pure Bunker source (`self-host/modules/view.bkr`).

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

The View Layer provides **declarative reactive user interfaces** that automatically update when underlying Shell agent states change, without imperative DOM or UI widget manipulation.

---

## 2. Declarative UI Semantics & Reactive Binding

### 2.1 The Four Invariants of Bunker View

1. **Declarative Component Hierarchy**: Views are trees of composable layout and widget components (`Window`, `Column`, `Row`, `Grid`, `Label`, `Button`, `TextInput`).
2. **Reactive State Projections**: View properties bind to Shell Layer agent states (e.g. `App.State.count`). When the agent mutates its state via message handlers, bound components reflect the new values.
3. **Event-Driven Asynchronous Dispatch**: User interactions (such as `on_click`) generate asynchronous messages dispatched directly to target agents (`send "increment" to App.State;`).
4. **Decoupled Backend Agnosticism**: The View tree can be rendered into text terminal output, structured JSON manifests (`bunker.view.v1`), or native graphics backends (Win32/Cocoa/Wayland) without altering the component definitions.

---

## 3. Pure Bunker Component Model (`self-host/modules/view.bkr`)

```bunker
struct ViewComponent {
    id: i64,
    kind: str,
    title: str,
    text: str,
    width: i64,
    height: i64,
    spacing: i64,
    columns: i64,
    font_size: i64,
    bound_agent: str,
    bound_key: str,
    on_click_target: str,
    on_click_message: str,
    children_ids: Vec<i64>,
}

struct ViewTree {
    components: Vec<ViewComponent>,
    root_id: i64,
    next_id: i64,
}
```

---

## 4. Machine-Readable View Manifest Schema (`bunker.view.v1`)

```json
{
  "schema": "bunker.view.v1",
  "view_name": "MainWindow",
  "component_count": 4,
  "root": {
    "id": 0,
    "kind": "Window",
    "title": "Hello Bunker",
    "width": 400,
    "height": 300,
    "children": [
      {
        "id": 1,
        "kind": "Column",
        "children": [
          {
            "id": 2,
            "kind": "Label",
            "text": "Count: 3",
            "bound_to": "App.State.count"
          },
          {
            "id": 3,
            "kind": "Button",
            "text": "Increment",
            "on_click": "send 'increment' to App.State"
          }
        ]
      }
    ]
  }
}
```

---

## 5. Tooling & Verification Contract

- **Pure Bunker Module**: `self-host/modules/view.bkr`
- **Shell Layer Bridge**: Seamless integration with `self-host/modules/shell.bkr`.
- **Positive Test Fixtures**:
  - `tests/302_pure_bunker_view_tree.bkr` (returns 42)
  - `tests/303_view_reactive_state_binding.bkr` (returns 42)
