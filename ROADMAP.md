# BUNKER LANG: Implementation Roadmap

This document defines the phased approach to building the Bunker compiler from scratch.

## Toolchain Decisions

| Component | Choice | Rationale |
|-----------|--------|-----------|
| **Implementation Language** | Rust | Memory-safe, great ecosystem, eventual self-hosting target. |
| **Parser** | `pest` (PEG) | Clean grammar files, good error messages, easy to iterate. |
| **Code Generation** | Cranelift (Phase 1-3), LLVM (Phase 4+) | Cranelift is simpler for bootstrap; LLVM for production optimization. |
| **Verification Engine** | Z3 (via `z3` crate) | Industry standard SMT solver. |
| **Build System** | Cargo | Standard Rust tooling. |

---

## Phase 0: Project Skeleton (Week 1)

**Goal:** Set up the Rust project structure and parse a trivial file.

**Deliverables:**
- [ ] `bunker-cli/` Rust project initialized with Cargo.
- [ ] `pest` grammar file (`grammar/bunker.pest`) that parses `kernel Name {}`.
- [ ] CLI that reads a `.bkr` file and prints "Parsed successfully" or error.

**Success Criteria:**
```bash
$ bunker build tests/00_empty_kernel.bkr
Parsed successfully: kernel "Math" with 0 functions.
```

---

## Phase 1: Kernel Parsing & AST (Week 2-3)

**Goal:** Parse the full Kernel syntax into an Abstract Syntax Tree.

**Deliverables:**
- [ ] Parse `fn`, `struct`, `const`, `comptime fn`.
- [ ] Parse statements: `let`, `return`, `if/else`, `for`, `defer`.
- [ ] Parse expressions: literals, binary ops, function calls.
- [ ] Parse attributes: `#[verified]`, `#[unsafe_trust]`, `#[requires()]`, `#[ensures()]`.
- [ ] Build AST data structures in Rust.

**Success Criteria:**
```bash
$ bunker build tests/01_basic_math.bkr --emit=ast
AST:
  Kernel "Math"
    Function "add"
      Params: [x: i32, y: i32]
      Return: i32
      Body: Return(BinaryOp(Add, Ident(x), Ident(y)))
```

---

## Phase 2: Kernel Code Generation (Week 4-6)

**Goal:** Compile Kernel functions to native machine code.

**Deliverables:**
- [ ] Integrate Cranelift for code generation.
- [ ] Implement type checking for Kernel layer.
- [ ] Generate machine code for basic functions (math, conditionals, loops).
- [ ] Output a working executable or object file.

**Success Criteria:**
```bash
$ bunker build tests/01_basic_math.bkr -o math.exe
$ ./math.exe
Result: 42
```

---

## Phase 3: Arena Memory Model (Week 7-8)

**Goal:** Implement region-based memory management.

**Deliverables:**
- [ ] Implement Arena allocator in the runtime.
- [ ] Compiler tracks which Arena each allocation belongs to.
- [ ] Automatic deallocation when scope/frame exits.
- [ ] `defer` statement execution.
- [ ] `copy` keyword for explicit copies.

**Success Criteria:**
```bash
$ bunker build tests/02_arena_memory.bkr -o arena.exe
$ ./arena.exe
Allocated 1000 objects. Freed automatically. No leaks.
```

---

## Phase 4: Shell Parsing & Agents (Week 9-11)

**Goal:** Parse Shell layer and compile Agents to state machines.

**Deliverables:**
- [ ] Parse `shell`, `agent`, `on receive`, `send`.
- [ ] Parse `match` expressions and `Option<T>`.
- [ ] Compile Agents to Deterministic Finite Automata (DFA).
- [ ] Implement message queue runtime.

**Success Criteria:**
```bash
$ bunker build tests/03_agent_ping_pong.bkr -o agents.exe
$ ./agents.exe
Agent A sent "ping" to Agent B.
Agent B received "ping", sending "pong".
Agent A received "pong". Done.
```

---

## Phase 5: Kernel <-> Shell Bridge (Week 12-13)

**Goal:** Allow Shell to call Kernel functions via `use`.

**Deliverables:**
- [ ] Implement `use Kernel.function with args` syntax.
- [ ] Type checking across layer boundaries.
- [ ] Runtime bridge between bytecode (Shell) and native code (Kernel).

**Success Criteria:**
```bash
$ bunker build tests/04_shell_calls_kernel.bkr -o bridge.exe
$ ./bridge.exe
Shell Agent called Kernel.add(10, 32). Result: 42.
```

---

## Phase 6: View Layer - Graphics Target (Week 14-16)

**Goal:** Compile View layer to a GUI window (Reactive Profile).

**Deliverables:**
- [ ] Parse `view` blocks and components.
- [ ] Implement reactive binding (View listens to Agent state).
- [ ] Integrate a minimal renderer (e.g., `minifb` or `wgpu` for graphics).
- [ ] Render `Label`, `Button`, `Column`, `Row` components.

**Success Criteria:**
```bash
$ bunker build tests/05_hello_gui.bkr --profile=reactive -o gui.exe
$ ./gui.exe
[Window opens with "Hello, Bunker!" label]
```

---

## Phase 7: Z3 Verification (Week 17-19)

**Goal:** Implement `#[verified]`, `#[requires]`, `#[ensures]` via Z3.

**Deliverables:**
- [ ] Translate Kernel functions to Z3 SMT-LIB format.
- [ ] Check `#[requires]` preconditions.
- [ ] Check `#[ensures]` postconditions.
- [ ] Compile-time error if Z3 finds a counterexample.

**Success Criteria:**
```bash
$ bunker build tests/06_verified_transfer.bkr
Verifying Banking.transfer...
  Precondition (amount > 0): PASSED
  Precondition (from.balance >= amount): PASSED
  Postcondition (conservation of money): PASSED
Compilation successful.

$ bunker build tests/06_verified_transfer_BAD.bkr
Verifying Banking.transfer...
  Postcondition (conservation of money): FAILED
    Counterexample: amount=100, from.balance=50
Error: Verification failed. Code does not compile.
```

---

## Phase 8: Profiles & Embedded Target (Week 20-22)

**Goal:** Implement `--profile=metal` for embedded systems.

**Deliverables:**
- [ ] Disable GC and heap allocation in Metal profile.
- [ ] Compile Shell to static DFA (no dynamic dispatch).
- [ ] Compile View to GPIO instructions.
- [ ] Output bare-metal binary (e.g., ARM Cortex-M).

**Success Criteria:**
```bash
$ bunker build tests/07_blink_led.bkr --profile=metal --target=arm-cortex-m4 -o blink.elf
$ arm-none-eabi-objdump -d blink.elf
[Shows ARM assembly for GPIO toggle]
```

---

## Phase 9: Self-Hosting (Week 23+)

**Goal:** Rewrite the Bunker compiler in Bunker.

**Deliverables:**
- [ ] Port the parser from Rust to Bunker.
- [ ] Port the AST and type checker to Bunker.
- [ ] Port code generation to Bunker.
- [ ] Compile the Bunker compiler with itself.

**Success Criteria:**
```bash
$ bunker build compiler/bunker.bkr -o bunker2.exe
$ ./bunker2.exe build tests/01_basic_math.bkr -o math.exe
$ ./math.exe
Result: 42
```

---

## Timeline Summary

| Phase | Duration | Milestone |
|-------|----------|-----------|
| 0 | 1 week | Project skeleton, trivial parse |
| 1 | 2 weeks | Full Kernel AST |
| 2 | 3 weeks | Kernel compiles to native code |
| 3 | 2 weeks | Arena memory working |
| 4 | 3 weeks | Shell Agents compile |
| 5 | 2 weeks | Kernel <-> Shell bridge |
| 6 | 3 weeks | GUI View rendering |
| 7 | 3 weeks | Z3 verification |
| 8 | 3 weeks | Embedded/Metal profile |
| 9 | Ongoing | Self-hosting |

**Total to MVP (Phases 0-5):** ~13 weeks (3 months)
**Total to Full Language (Phases 0-8):** ~22 weeks (5.5 months)

---

## Next Steps

1. Initialize the Rust project (`bunker-cli`).
2. Write the `pest` grammar for Phase 0.
3. Create the golden test files in `tests/`.
