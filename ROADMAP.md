# BUNKER LANG: Implementation Roadmap

This document defines the phased approach to building the Bunker compiler from scratch.

> **See also:**
> - [docs/SPECIFICATION.md](docs/SPECIFICATION.md) - The Definitive AI-Native Systems Programming Language Specification
> - [docs/TECHNICAL_SPEC.md](docs/TECHNICAL_SPEC.md) - Complete Technical Specification covering grammar-constrained decoding, type systems, ownership models, contracts, and agent runtime

## Toolchain Decisions

| Component | Choice | Rationale |
|-----------|--------|-----------|
| **Implementation Language** | Rust | Memory-safe, great ecosystem, eventual self-hosting target. |
| **Parser** | `pest` (PEG) | Clean grammar files, good error messages, easy to iterate. |
| **Code Generation** | Cranelift (Phase 1-3), LLVM (Phase 4+) | Cranelift is simpler for bootstrap; LLVM for production optimization. |
| **Verification Engine** | Z3 (via `z3` crate) | Industry standard SMT solver. |
| **Build System** | Cargo | Standard Rust tooling. |

---

## Phase 0: Project Skeleton ✅

**Goal:** Set up the Rust project structure and parse a trivial file.

**Deliverables:**
- [x] `bunker-cli/` Rust project initialized with Cargo.
- [x] `pest` grammar file (`grammar/bunker.pest`) that parses `kernel Name {}`.
- [x] CLI that reads a `.bkr` file and prints "Parsed successfully" or error.

**Success Criteria:**
```bash
$ bunker build tests/00_empty_kernel.bkr
Parsed successfully: kernel "Math" with 0 functions.
```

---

## Phase 1: Kernel Parsing & AST ✅

**Goal:** Parse the full Kernel syntax into an Abstract Syntax Tree.

**Deliverables:**
- [x] Parse `fn`, `struct`, `const`, `comptime fn`.
- [x] Parse statements: `let`, `return`, `if/else`, `for`, `defer`.
- [x] Parse expressions: literals, binary ops, function calls.
- [x] Parse attributes: `#[verified]`, `#[unsafe_trust]`, `#[requires()]`, `#[ensures()]`.
- [x] Build AST data structures in Rust.

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

## Phase 2: Kernel Code Generation ✅

**Goal:** Compile Kernel functions to native machine code.

**Deliverables:**
- [x] Integrate Cranelift for code generation.
- [x] Implement type checking for Kernel layer.
- [x] Generate machine code for basic functions (math, conditionals, loops).
- [x] Output a working executable or object file.

**Success Criteria:**
```bash
$ bunker build tests/01_basic_math.bkr -o math.exe
$ ./math.exe
Result: 42
```

---

## Phase 3: Arena Memory Model ✅

**Goal:** Implement region-based memory management.

**Deliverables:**
- [x] Implement Arena allocator in the runtime (bump allocator with 64KB blocks).
- [x] Watermark pattern for scope-based deallocation.
- [x] Automatic deallocation when scope/block exits.
- [x] `defer` statement execution.
- [x] `copy` keyword for explicit copies.
- [x] Loop iteration memory reuse (watermarks restore between iterations).
- [x] Nested block scoping (inner blocks free before outer).

**Success Criteria:**
```bash
$ bunker build tests/02_arena_memory.bkr -o arena.exe
$ ./arena.exe
Allocated 1000 objects. Freed automatically. No leaks.
```

---

## Phase 4: Shell Parsing & Agents ✅

**Goal:** Parse Shell layer and compile Agents to state machines.

**Deliverables:**
- [x] Parse `shell`, `agent`, `on receive`, `send`.
- [x] Parse `match` expressions and `Option<T>`.
- [x] Compile Agents to Deterministic Finite Automata (DFA).
- [x] Implement message queue runtime.

**Success Criteria:**
```bash
$ bunker build tests/03_agent_ping_pong.bkr -o agents.exe
$ ./agents.exe
Agent A sent "ping" to Agent B.
Agent B received "ping", sending "pong".
Agent A received "pong". Done.
```

---

## Phase 5: Kernel <-> Shell Bridge ✅

**Goal:** Allow Shell to call Kernel functions via `use`.

**Deliverables:**
- [x] Implement `use Kernel.function with args` syntax.
- [x] Type checking across layer boundaries.
- [x] Runtime bridge between bytecode (Shell) and native code (Kernel).

**Success Criteria:**
```bash
$ bunker build tests/04_shell_calls_kernel.bkr -o bridge.exe
$ ./bridge.exe
Shell Agent called Kernel.add(10, 32). Result: 42.
```

---

## Phase 6: View Layer - Graphics Target ✅

**Goal:** Compile View layer to a GUI window (Reactive Profile).

**Deliverables:**
- [x] Parse `view` blocks and components.
- [x] Reactive binding (View updates on Agent state changes).
- [x] Integrate a minimal renderer (Windows Win32 backend).
- [x] Render `Label`, `Button` components.
- [x] Layout containers: `Column`, `Row`, `Grid` with spacing/padding properties.

**Success Criteria:**
```bash
$ bunker build tests/05_hello_gui.bkr --profile=reactive -o gui.exe
$ ./gui.exe
[Window opens with "Hello, Bunker!" label]
```

---

## Phase 7: Z3 Verification (Structurally Complete)

**Goal:** Implement `#[verified]`, `#[requires]`, `#[ensures]` via Z3.

**Status:** Z3 SMT integration structurally complete. Requires Z3 library installation for full verification.

**Deliverables:**
- [x] Parse `#[verified]`, `#[requires]`, `#[ensures]` attributes.
- [x] Lightweight linear expression verification.
- [x] Z3 expression encoding (`smt.rs`) - Bunker expressions to Z3 AST.
- [x] `--smt` CLI flag for opt-in Z3 verification.
- [x] Graceful fallback when Z3 unavailable.
- [ ] Full Z3 testing (requires Z3 installation).

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

## Current Progress Summary

| Phase | Status | Notes |
|-------|--------|-------|
| 0 | ✅ Complete | Project skeleton, CLI, grammar |
| 1 | ✅ Complete | Full Kernel AST |
| 2 | ✅ Complete | Cranelift JIT, type checking |
| 3 | ✅ Complete | Arena allocator with watermark pattern |
| 4 | ✅ Complete | Shell agents, message queues |
| 5 | ✅ Complete | Kernel↔Shell bridge |
| 6 | ✅ Complete | View layer with Row/Column/Grid layout |
| 7 | 🔶 Partial | Z3 integration complete, requires Z3 installation |
| 8 | ⬜ Not Started | Embedded/Metal profile |
| 9 | ⬜ Not Started | Self-hosting |

**Test Suite:** 74 tests passing (54 JIT-enabled, 9 negative tests, 7 shell execution, 4 view/demo)

---

## Next Steps

1. ~~**Structured JSON Error Output** - Critical for AI feedback loops (62.5% vs 34% repair accuracy).~~ ✅ **DONE** (`--format=json`)
2. ~~**Z3 SMT Integration** - Full contract verification with counterexamples.~~ ✅ **DONE** (`--smt` flag, requires Z3 installation)
3. ~~**Arena Memory Allocator** - Complete Phase 3 memory model.~~ ✅ **DONE** (watermark pattern with scope-based deallocation)
4. ~~**View Layout Containers** - Row/Column/Grid for real UI applications.~~ ✅ **DONE** (recursive layout with spacing/padding)
5. ~~**End-to-End Demo** - Complete application using all three layers.~~ ✅ **DONE** (`69_calculator_demo.bkr` - Calculator with Kernel+Shell+View)
6. ~~**AI Training Dataset** - Begin curating Bunker code samples for AI training.~~ ✅ **DONE** (`docs/EXAMPLES.md` - comprehensive annotated examples)
7. **Embedded/Metal Profile** - Phase 8: bare-metal compilation target.

> **Tip:** Run `/check-update-status` to get a full implementation status report with specification compliance analysis.
