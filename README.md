# Bunker Language

**The first systems programming language designed for human-AI collaborative development.**

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

## Why Bunker?

Research shows that **33.6% of LLM-generated code fails due to type errors**, grammar complexity determines AI generation accuracy, and **formal contracts eliminate hallucinations** through mathematical proof. Bunker is designed from the ground up with these insights—not retrofitted.

| Feature | Rust | C++ | Bunker |
|---------|------|-----|--------|
| Memory Safety | Borrow checker (complex) | Manual | Arena-based (simple) |
| AI Code Generation | Poor (borrow checker confuses LLMs) | Poor (templates) | **Designed for AI** |
| Concurrency | `async`/channels | Threads/locks | Actor model (built-in) |
| Compile-time Computation | Limited const | constexpr | Full `comptime` |
| Formal Verification | External tools | None | Built-in `#[verified]` |
| Error Handling | `Result<T,E>` | Exceptions | `Option<T>` + contracts |

## 6 Killer Features

1. **AI-First Grammar** - LL(1) parseable, flat syntax, no significant whitespace—96% syntax error reduction with grammar-constrained decoding
2. **`comptime` Functions** - Full compile-time execution (like Zig, but integrated)
3. **`defer` Statement** - Deterministic cleanup without RAII complexity
4. **Design-by-Contract** - `#[requires]` and `#[ensures]` with verification—contracts eliminate AI hallucinations
5. **`Option<T>` Only** - No null, no exceptions, no `Result<T,E>` boilerplate
6. **Explicit `copy`** - No hidden copies, move semantics simpler than Rust's borrow checker

## Quick Example

```bunker
// Kernel: Pure, verified computation
kernel Math {
    #[verified]
    #[requires(b != 0)]
    #[ensures(result * b == a)]
    fn divide(a: i32, b: i32) -> i32 {
        return a / b;
    }
}

// Shell: Concurrent agents
shell Counter {
    agent CounterAgent {
        count = 0;

        on receive "increment" {
            count = count + 1;
        }

        on receive "get" {
            send "value" to Requester with value=count;
        }
    }
}

// View: Declarative UI
view CounterApp {
    #[target(graphics)]
    Window {
        title: "Counter";

        Label { text: "Count: " + Counter.CounterAgent.count; }
        Button {
            text: "+";
            on_click: send "increment" to Counter.CounterAgent;
        }
    }
}
```

## The AI Collaboration Workflow

```
Human writes contracts → AI generates code → Compiler verifies → Ship proven-correct code
```

1. **Human** defines contracts (`#[requires]`, `#[ensures]`)—what the code should do
2. **AI** generates implementation proposals
3. **Compiler** verifies contracts are satisfied with mathematical proof
4. If verification fails, AI refines based on counterexamples
5. **Proven-correct code** ships to production

## Installation

### Prerequisites
- Rust 1.70+ (for building the compiler)
- Cargo

### Build from Source

```bash
git clone https://github.com/emiliancristea/bunker-lang.git
cd bunker-lang/bunker-cli
cargo build --release
```

The compiler binary will be at `target/release/bunker-cli`.

## Usage

```bash
# Check syntax and types
bunker-cli check myfile.bkr

# Run with JIT compilation
bunker-cli run myfile.bkr

# Compile to object file
bunker-cli build myfile.bkr -o myfile.o

# Parse and show AST (debugging)
bunker-cli parse myfile.bkr
```

## Project Structure

```
bunker-lang/
├── bunker-cli/           # Compiler implementation (Rust)
│   ├── src/
│   │   ├── main.rs           # CLI entry point
│   │   ├── grammar/
│   │   │   └── bunker.pest   # PEG grammar (AI-friendly LL(1))
│   │   ├── ast.rs            # AST type definitions
│   │   ├── ast_builder.rs    # Parse tree → AST
│   │   ├── typeck.rs         # Type checker + move tracking
│   │   ├── jit.rs            # Cranelift JIT compilation
│   │   ├── codegen.rs        # Cranelift AOT compilation
│   │   └── shell_runtime.rs  # Agent VM runtime
│   └── Cargo.toml
├── tests/                # 64 golden test files
├── docs/
│   ├── VISION.md         # Language design philosophy
│   └── ARCHITECTURE.md   # Compiler pipeline design
├── ROADMAP.md            # Implementation phases
└── README.md
```

## Language Reference

### File Extension
`.bkr` (short for Bunker)

### Three Layers

#### Kernel Layer
Pure, verified functions. No side effects allowed.

```bunker
kernel MyKernel {
    struct Point { x: i32, y: i32 }

    fn add(a: i32, b: i32) -> i32 {
        return a + b;
    }

    comptime fn factorial(n: i32) -> i32 {
        if n <= 1 { return 1; }
        return n * factorial(n - 1);
    }

    // Move semantics: simpler than Rust's borrow checker
    fn process() {
        let a = create_buffer();
        let b = a;          // 'a' is MOVED to 'b'. 'a' is now invalid.
        let c = copy b;     // 'c' is a COPY of 'b'. Both are valid.
        // use_buffer(a);   // ERROR: use of moved value 'a'
    }
}
```

#### Shell Layer
Concurrent agents with message passing.

```bunker
shell MyShell {
    import MyKernel;

    agent Worker {
        state = 0;

        on receive "work" with data: i32 {
            let result = use MyKernel.add with a=state, b=data;
            state = result;
            send "done" to Manager with result=state;
        }
    }
}
```

#### View Layer
Declarative UI for graphics or embedded targets.

```bunker
view MyView {
    #[target(graphics)]
    Window {
        title: "My App";
        width: 800;
        height: 600;

        Button {
            text: "Click Me";
            on_click: send "clicked" to Handler;
        }
    }

    #[target(embedded)]
    Pin {
        id: 13;
        value: led_on;
    }
}
```

### Types

| Type | Description |
|------|-------------|
| `i32`, `i64` | Signed integers |
| `f32`, `f64` | Floating point |
| `bool` | Boolean |
| `str` | String |
| `[T; N]` | Fixed-size array |
| `Option<T>` | Optional value |

### Attributes (Design-by-Contract)

| Attribute | Description |
|-----------|-------------|
| `#[verified]` | Function is formally verified |
| `#[requires(expr)]` | Precondition (caller must satisfy) |
| `#[ensures(expr)]` | Postcondition (function guarantees) |
| `#[unsafe_trust]` | Skip verification (escape hatch) |

## Current Status

### Implemented ✅
- [x] Full PEG grammar for all three layers (AI-friendly LL(1))
- [x] Complete AST builder
- [x] Kernel: full type checking + Cranelift JIT for `fn main() -> i32|i64|f64|bool`
- [x] Kernel: structs, arrays, Option<T>, match expressions, defer, type casting, constants
- [x] Kernel: comptime functions with compile-time evaluation
- [x] Kernel: **move semantics** with explicit `copy` (simpler than Rust's borrow checker)
- [x] Shell: agent compiler + message-queue VM + Kernel bridge
- [x] Shell: typed message schemas with compile-time validation
- [x] View: text backend + Windows `#[target(graphics)]` backend
- [x] Contracts: `#[requires]`/`#[ensures]` with lightweight verification
- [x] **64 tests passing** (including 9 negative `*_BAD` tests)

### In Progress 🚧
- [x] Z3 SMT verification integration (`--smt` flag, requires Z3 installation) ✅
- [x] Structured JSON error output (`--format=json` for AI feedback loops) ✅
- [ ] View layout (Row/Column/Grid) & more widgets
- [ ] Standard library
- [ ] AI training dataset and benchmarks

> **Note:** Run `/check-update-status` to get a full specification compliance report and gap analysis.

### Planned 📋
- [ ] LLVM backend (alternative to Cranelift)
- [ ] Embedded profile (`--profile=metal`)
- [ ] Language server (LSP)
- [ ] Package manager
- [ ] Self-hosting compiler

## Why Not Existing Languages?

| Language | AI Problem |
|----------|------------|
| **Rust** | Borrow checker "largely undermines the ability of LLMs to generate valid code" |
| **C++** | Templates generate "long and cryptic error messages" that confuse AI |
| **Python** | Dynamic typing means errors surface only at runtime—AI can't predict them |
| **TypeScript** | Optional typing creates boundaries where AI-generated code fails |

Bunker is designed so that **correct code is easy to generate and incorrect code is impossible to compile**.

## Contributing

Contributions welcome! See [ROADMAP.md](ROADMAP.md) for the implementation plan.

## Project Direction (Docs)

- **`docs/SPECIFICATION.md`** - **The Definitive AI-Native Systems Programming Language Specification** - Complete language design covering grammar theory, type systems, memory models, formal verification, agent semantics, and tooling
- **`docs/TECHNICAL_SPEC.md`** - **Complete Technical Specification** - In-depth technical reference covering grammar-constrained decoding, type-constrained generation, ownership models, contracts, agent runtime, and cross-layer integration
- `docs/VISION.md` - Language design philosophy and AI collaboration insights
- `docs/ARCHITECTURE.md` - Compiler pipeline and runtime design
- `ROADMAP.md` - Implementation phases and milestones

## License

MIT License - see [LICENSE](LICENSE) for details.

## Acknowledgments

- **Cranelift** - Fast code generation
- **Pest** - PEG parser generator
- **Z3** - SMT solver for verification (planned)
- **MoonBit** - Research on AI-friendly language design (ICSE 2024)
- **SPARK/Ada** - Design-by-contract for AI code generation
