# Bunker Language

**A systems programming language with three architectural layers designed to beat Rust and C++ in safety, performance, and developer experience.**

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

| Feature | Rust | C++ | Bunker |
|---------|------|-----|--------|
| Memory Safety | Borrow checker (complex) | Manual | Arena-based (simple) |
| Concurrency | `async`/channels | Threads/locks | Actor model (built-in) |
| Compile-time Computation | Limited const | constexpr | Full `comptime` |
| Formal Verification | External tools | None | Built-in `#[verified]` |
| Error Handling | `Result<T,E>` | Exceptions | `Option<T>` + contracts |
| GUI | External crates | Qt/etc | Native View layer |

## 5 Killer Features

1. **`comptime` Functions** - Full compile-time execution (like Zig, but integrated)
2. **`defer` Statement** - Deterministic cleanup without RAII complexity
3. **Design-by-Contract** - `#[requires]` and `#[ensures]` with Z3 verification
4. **`Option<T>` Only** - No null, no exceptions, no `Result<T,E>` boilerplate
5. **Explicit `copy`** - No hidden copies, clear ownership semantics

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
    @graphics
    component Window {
        title: "Counter"
        
        Text { content: count }
        Button { 
            label: "+"
            on_click: send "increment" to CounterAgent
        }
    }
}
```

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
│   │   ├── parser.rs         # Pest parser integration
│   │   ├── grammar/
│   │   │   └── bunker.pest   # PEG grammar
│   │   ├── ast.rs            # AST type definitions
│   │   ├── ast_builder.rs    # Parse tree → AST
│   │   ├── typeck.rs         # Type checker
│   │   ├── codegen.rs        # Cranelift code generation
│   │   └── shell_codegen.rs  # Agent compilation
│   └── Cargo.toml
├── tests/                # Golden test files
│   ├── 00_empty_kernel.bkr
│   ├── 01_basic_math.bkr
│   ├── 02_arena_memory.bkr
│   ├── 03_agent_ping_pong.bkr
│   ├── 04_shell_calls_kernel.bkr
│   ├── 05_hello_gui.bkr
│   └── 06_verified_transfer.bkr
├── example.bkr           # Smart thermostat demo
├── overview.md           # Language specification
├── ROADMAP.md            # Implementation roadmap
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
    @graphics
    component MainWindow {
        title: "My App"
        size: (800, 600)
        
        Button {
            label: "Click Me"
            on_click: send "clicked" to Handler
        }
    }
    
    @embedded
    component StatusLED {
        pin: 13
        state: led_on
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
| `&T`, `&mut T` | References |

### Attributes

| Attribute | Description |
|-----------|-------------|
| `#[verified]` | Enable Z3 formal verification |
| `#[requires(expr)]` | Precondition |
| `#[ensures(expr)]` | Postcondition |
| `#[unsafe_trust]` | Skip verification |

## Current Status

### Implemented ✅
- [x] Full PEG grammar for all three layers
- [x] Complete AST builder
- [x] Type checker for Kernel layer
- [x] Cranelift code generation (Kernel)
- [x] Shell layer agent compilation
- [x] 8 passing test files

### In Progress 🚧
- [ ] View layer compilation
- [ ] Z3 verification integration
- [ ] Runtime library (message queue)
- [ ] Standard library

### Planned 📋
- [ ] LLVM backend (alternative to Cranelift)
- [ ] Language server (LSP)
- [ ] Package manager
- [ ] Documentation generator

## Contributing

Contributions welcome! See [ROADMAP.md](ROADMAP.md) for the implementation plan.

## License

MIT License - see [LICENSE](LICENSE) for details.

## Acknowledgments

- **Cranelift** - Fast code generation
- **Pest** - PEG parser generator
- **Z3** - SMT solver for verification (planned)
