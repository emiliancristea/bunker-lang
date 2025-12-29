# Bunker Language Vision

> **See also:**
> - [SPECIFICATION.md](SPECIFICATION.md) - The Definitive AI-Native Systems Programming Language Specification
> - [TECHNICAL_SPEC.md](TECHNICAL_SPEC.md) - Complete Technical Specification covering grammar-constrained decoding, type systems, ownership models, contracts, and agent runtime

## The First Systems Language Designed for Human-AI Collaboration

Bunker is a **systems programming language designed from the ground up for human-AI collaborative development**. No existing systems language was built with AI code generation in mind—Bunker fills this gap.

Research shows that **type errors account for 33.6% of all failed LLM-generated programs**, grammar complexity determines whether AI can generate syntactically correct code, and formal contracts eliminate AI hallucinations through mathematical proof. Bunker incorporates these insights as first principles, not afterthoughts.

## The Three-Layer Architecture

Bunker uses a **single-language, single-file "vertical slice"** model: one `.bkr` file can contain three layers that compose cleanly but are compiled and executed differently.

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

- **Kernel**: Native, side-effect-light systems code for hot paths (math/physics/drivers/memory). Pure functions with optional formal verification.
- **Shell**: Agent/actor-style orchestration (state + message passing). First-class support for AI agent patterns—memory hierarchies, tool definitions, supervision trees.
- **View**: Declarative HMI/UI that binds to Shell state, targeting graphics (desktop) or embedded (GPIO/LED/LCD).

The core promise is **architectural enforcement as syntax**: reduce integration drift between "systems", "logic", and "UI" by design.

## Why AI-First Design Matters

### Type Systems Eliminate 33% of AI Errors

Research from multiple sources converges: type errors are the single largest category of LLM code generation failures. Bunker's **mandatory static typing** with bidirectional inference:
- Enables type-constrained decoding (guiding token generation)
- Catches errors before runtime
- Provides clear contracts at module boundaries
- Keeps the type system simple enough for grammar-constrained decoding

### Grammar Design for AI Generation

The SynCode framework achieved **96% reduction in syntax errors** through grammar-constrained decoding. Bunker's grammar is designed for this:
- **LL(1) parseable**: O(1) token lookup per generation step
- **Keyword-delimited blocks**: Clear boundaries for LLMs
- **No significant whitespace**: Eliminates Python's notorious AI generation problems
- **Flat/linear syntax**: Following MoonBit's ICSE 2024 research on transformer-friendly design
- **Unambiguous**: Each parse has exactly one interpretation

### Formal Contracts Eliminate Hallucinations

DeepMind's AlphaProof achieved **zero hallucinations** by generating formally verified proofs—all outputs are machine-verified. Bunker brings this to systems programming:
- `#[requires]` preconditions constrain valid inputs
- `#[ensures]` postconditions guarantee outputs
- `#[verified]` functions are mathematically proven correct
- Contracts serve as "ground truth" that AI must satisfy

AdaCore explicitly positions SPARK as "the best possible language for Generative AI"—Bunker extends this vision to a modern, accessible syntax.

### Agent Primitives as First-Class Citizens

Current AI agent frameworks (LangGraph, AutoGen, CrewAI) reveal what primitives a language should provide. Bunker's Shell layer includes:
- **Explicit memory hierarchies**: Working memory (bounded context), persistent long-term memory
- **Typed tool definitions**: Preconditions, effects, timeouts, retry policies, fallbacks
- **Structured message types**: Type-safe inter-agent communication
- **Supervision trees**: Fault tolerance as a language construct
- **Built-in tracing**: No external instrumentation required

## Design Principles

### Explicit Over Implicit

No hidden behavior anywhere:
- **Explicit error handling** via `Option<T>` (no exceptions, no null)
- **Explicit memory management** via arena-based allocation (no hidden GC pauses)
- **Explicit copies** via the `copy` keyword (no hidden allocations)
- **No operator overloading** that changes semantics unexpectedly
- **No macros** that create unpredictable expansion

### Simple Over Clever

Complexity increases AI hallucination rates:
- No dependent types or higher-kinded types
- No lifetime annotations (arena-based memory is simpler)
- No template metaprogramming
- No multi-phase compilation
- No context-dependent semantics

### Verifiable Over Trusting

Mathematical proof over statistical confidence:
- Contracts are machine-verified, not just documented
- Type system catches errors at compile time
- Move semantics prevent use-after-free at compile time
- Property-based testing generates from contracts

## The End Goal

The end-state toolchain can:

1. **Compile and run complete applications** across profiles:
   - **Metal**: Embedded/deterministic, minimal runtime surface
   - **Performance**: Native hot paths + lightweight orchestration
   - **Reactive**: UI + state management with predictable updates
   - **Fortress**: Correctness-first with aggressive verification

2. **Serve as the optimal target for AI code generation**:
   - Grammar-constrained decoding for syntactic correctness
   - Type-constrained generation for semantic correctness
   - Contract satisfaction for behavioral correctness

3. **Provide built-in verification** via design-by-contract with Z3 SMT solving

4. **Ship a practical runtime** (message passing, scheduling, view updates, arena memory)

5. **Grow into a complete ecosystem**: LSP, package manager, docs generator, curated AI training datasets

## Who It's For

### Primary Targets

- **Embedded/IoT engineers** who want deterministic behavior with fewer footguns
- **Game/tool developers** who want fast kernels with high-level orchestration
- **Safety/finance domains** where invariants must be enforced at compile time
- **AI-assisted development teams** who want reliable code generation with verification

### The AI Collaboration Workflow

1. Human writes contracts (what the code should do)
2. AI generates implementation proposals
3. Compiler verifies contracts are satisfied
4. If verification fails, AI refines based on counterexamples
5. Proven-correct code ships to production

This is the future of programming: **AI generates, formal methods verify, humans supervise**.

## What Success Looks Like

- A newcomer can clone the repo and run demos end-to-end
- **AI tools (Copilot, Claude, GPT) generate valid Bunker code** with high accuracy
- The compiler reliably rejects invalid programs with **AI-readable error messages**
- Verification failures include counterexamples that guide refinement
- Critical systems code is **mathematically proven correct**, not just tested

## Non-Goals (For Early Versions)

- "Beat Rust/C++ everywhere" performance claims (optimize once semantics are correct)
- Full standard library (start with a tiny runtime)
- Perfectly stable syntax (expect iteration)
- Complex type system features (keep it simple for AI)

## The Opportunity

No systems-level language has been designed from the ground up for human-AI collaborative development. Rust's borrow checker "largely undermines the ability of LLMs to generate valid code." C++'s templates generate "long and cryptic error messages" that confuse both humans and AI. Python's dynamic typing means errors surface only at runtime.

Bunker is designed to be **the first systems programming language where AI code generation actually works reliably**—not through prompt engineering, but through language design that makes correct code easy to generate and incorrect code impossible to compile.

## How We Get There

- `ROADMAP.md` for phased milestones
- `docs/ARCHITECTURE.md` for compiler/runtime design
- `docs/SPECIFICATION.md` for AI-native language specification
- `docs/TECHNICAL_SPEC.md` for complete technical specification
- Curated training datasets and benchmarks as first-class deliverables

> **Tip:** Run `/check-update-status` to get a full implementation status report with specification compliance analysis.

## Implementation Status

See the Implementation Status Tracking sections in:
- [SPECIFICATION.md](SPECIFICATION.md#implementation-status-tracking)
- [TECHNICAL_SPEC.md](TECHNICAL_SPEC.md#implementation-status-tracking)

These sections provide detailed checklists tracking progress against each specification area.
