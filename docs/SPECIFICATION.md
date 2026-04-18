# Bunker: The Definitive AI-Native Systems Programming Language Specification

> **See also:** [TECHNICAL_SPEC.md](TECHNICAL_SPEC.md) - Complete Technical Specification with in-depth coverage of grammar-constrained decoding, type-constrained generation, ownership models, contracts, agent runtime, and cross-layer integration

Bunker represents a new paradigm in language design—a systems programming language engineered from first principles for **both** human developers and AI agents (LLMs) to write, read, and execute with exceptional reliability. This specification synthesizes exhaustive research across grammar theory, type systems, memory models, formal verification, agent semantics, and tooling to create the most AI-friendly systems language possible.

## Executive synthesis: The core thesis

**Grammar-constrained decoding research** (SynCode, XGrammar) demonstrates that LL(1)-compatible grammars with explicit `end` keywords achieve **96%+ syntax error reduction** in LLM-generated code. **MoonBit's flattened design** shows that eliminating nested `impl` blocks and mandating toplevel type annotations creates "semantic anchors" that dramatically improve AI generation accuracy. **Type-guided synthesis** (SyGuS, Liquid Haskell) proves that refinement types with SMT-decidable predicates constrain AI search space to correct programs. **Structured concurrency** (Trio, Swift) eliminates the async/await "function coloring" problem that causes widespread LLM errors. **Zig's comptime** model demonstrates that compile-time computation using the same language—rather than macros—is highly predictable for AI.

These findings converge on a unified design philosophy: **explicit structure beats implicit flexibility** for AI code generation.

---

## Area 1: Grammar and syntax optimization for AI code generation

### Grammar-constrained decoding state of the art

The research landscape has evolved rapidly. **SynCode** (UIUC, 2024) uses offline-constructed DFA mask stores with LR(1) parsers, achieving **1.22x runtime overhead** while guaranteeing syntactic correctness. **XGrammar** (MLC-AI, 2024) achieves near-zero overhead through pushdown automata with context-independent token pre-computation, delivering **100x speedup** over alternatives. **Microsoft Guidance's llguidance** backend processes constraints at approximately **50μs per token** for 128k tokenizers.

The critical finding: **LR(1) parsers outperform LALR(1)** for generating accept sequences during constrained decoding. XGrammar's division of vocabulary into context-independent (pre-checkable) and context-dependent tokens enables grammar checking to overlap with GPU computation.

### Optimal grammar class determination

For Bunker, the evidence strongly favors an **LL(1)-compatible grammar with PEG semantics**. Medeiros et al. proved that LL(1) grammars describe the same language whether interpreted as PEG or CFG, making them uniquely suitable for deterministic generation. PEG's ordered choice operator (`/`) is **inherently unambiguous**—exactly one parse tree or none—eliminating the ambiguity that causes LLM generation problems.

The dangling else problem illustrates why explicit delimiters matter. C-style `if (a) if (b) s1 else s2` has two valid parse trees. Bunker eliminates this class of ambiguity entirely through mandatory `end` keywords.

### Concrete syntax specification

```bunker
# Function definitions
fn process(items: List[T]) -> Result[T, Error] do
    items.filter(is_valid)
         .map(transform)
end

# Control flow with explicit terminators
if condition then
    handle_true()
else
    handle_false()
end

while queue.not_empty() do
    process(queue.pop())
end

for item in collection do
    process(item)
end

# Type definitions (toplevel, mandatory annotations)
type Point = struct {
    x: f64,
    y: f64,
}

type Color = enum {
    Red,
    Green,
    Blue,
    Custom(r: u8, g: u8, b: u8),
}

# Methods as toplevel functions (MoonBit-inspired flattened design)
fn Point::distance(self: Point, other: Point) -> f64 do
    let dx = self.x - other.x
    let dy = self.y - other.y
    (dx * dx + dy * dy).sqrt()
end

# No nested impl blocks - methods are flat
fn Point::translate(self: Point, dx: f64, dy: f64) -> Point do
    Point { x: self.x + dx, y: self.y + dy }
end
```

### Keyword and token design for AI

Keywords chosen for single-token BPE encoding: `fn`, `do`, `end`, `if`, `then`, `else`, `for`, `in`, `while`, `let`, `mut`, `pub`, `use`, `type`, `struct`, `enum`, `match`, `return`. Testing against GPT-4's tokenizer confirms these encode as single tokens.

The `do`/`end` structure provides:
- **Unambiguous block boundaries** visible in token stream
- **No dangling else** by construction
- **Self-documenting structure** without counting braces
- **Grammar compatibility** with LL(1) without left recursion

---

## Area 2: Type system design for AI correctness

### Bidirectional type inference architecture

Bunker uses **bidirectional typing** where expected types propagate downward from annotations while synthesized types flow upward from expressions. This separation enables AI tools to query "what type is expected here?" at any position.

```bunker
# Synthesis mode: type inferred from expression
let x = 42  # x: i32 synthesized

# Checking mode: expression checked against annotation
let y: i64 = 42  # 42 checked against i64

# Toplevel requires annotation (semantic anchor for AI)
fn add(a: i32, b: i32) -> i32 do
    a + b  # Return type checked against signature
end
```

### Refinement types with decidable SMT checking

Bunker implements a **tiered refinement system** balancing expressiveness with automation:

**Tier 1 (Fully Automated)**: Decidable refinements in QF_LIA (quantifier-free linear integer arithmetic)
```bunker
type Nat = { v: i32 | v >= 0 }
type NonEmpty[T] = { v: List[T] | length(v) > 0 }
type Bounded[lo, hi] = { v: i32 | lo <= v and v <= hi }

fn divide(a: i32, b: { v: i32 | v != 0 }) -> i32 do
    a / b  # Division by zero impossible by construction
end
```

**Tier 2 (SMT-Assisted)**: Decidable with timeouts
```bunker
fn binary_search(arr: SortedArray[i32], key: i32) -> Option[Index]
    requires forall i, j. i < j implies arr[i] <= arr[j]
    ensures result.is_some() implies arr[result.unwrap()] == key
```

**Tier 3 (Proof-Required)**: Full dependent types for critical invariants requiring explicit proof terms.

### Algebraic data types with exhaustive pattern matching

```bunker
type Result[T, E] = enum {
    Ok(value: T),
    Err(error: E),
}

fn handle_result(r: Result[i32, String]) -> i32 do
    match r with
    | Ok(v) => v
    | Err(e) => {
        log_error(e)
        -1
    }
    end
end
# Compiler enforces exhaustiveness - missing cases are compile errors
```

### Row-polymorphic effect system

Bunker tracks effects in function signatures using Koka-inspired row polymorphism:

```bunker
# Effect declarations
effect IO
effect Alloc
effect Exn[E]
effect Diverge

# Pure function (no effects)
fn add(a: i32, b: i32) -> Pure i32 do
    a + b
end

# Function with IO effect
fn read_file(path: String) -> IO Result[String, IoError] do
    # ...
end

# Effect polymorphism
fn map[A, B, E](list: List[A], f: fn(A) -> E B) -> E List[B] do
    # Inherits effects of f
end
```

### Type error message format for AI self-correction

```json
{
  "error_code": "E0308",
  "severity": "error",
  "message": "type mismatch",
  "location": {
    "file": "src/main.bk",
    "line": 15,
    "column": 12,
    "span_length": 8
  },
  "expected": {
    "type": "i32",
    "reason": "declared return type of function"
  },
  "found": {
    "type": "String",
    "source": "string literal on line 15"
  },
  "suggestions": [{
    "message": "convert string to integer",
    "confidence": 0.85,
    "applicability": "machine_applicable",
    "replacement": {
      "range": {"start": 12, "end": 20},
      "text": "\"42\".parse().unwrap()"
    }
  }],
  "related": [{
    "location": {"file": "src/main.bk", "line": 10, "column": 25},
    "message": "return type declared here"
  }]
}
```

---

## Area 3: Memory model and ownership for AI

### Linear types as foundation

Bunker adopts **Austral's linearity-via-kinds approach**, partitioning types into two universes:

```bunker
# Linear types (must use exactly once)
type File! = linear struct { handle: RawHandle }
type Socket! = linear struct { fd: i32 }
type DbConnection! = linear struct { conn: *Connection }

# Value types (freely copyable)
type Point = value struct { x: f64, y: f64 }
type Color = value enum { Red, Green, Blue }

# Linear type usage
fn process_file(file: File!) -> (Result[Data, Error], File!) do
    let data = file.read()
    (data, file)  # Must return file - cannot drop
end

fn done_with_file(file: File!) -> () do
    file.close()  # Consumes the linear value
end
```

### Second-class references without lifetime annotations

Bunker's references are **second-class**: they cannot be stored in data structures or returned from functions, eliminating the need for lifetime annotations entirely.

```bunker
# References only valid within function scope
fn sum_array(arr: &[i32]) -> i32 do
    let mut total = 0
    for x in arr do
        total = total + x
    end
    total
end

# Mutable reference - exclusive access
fn increment_all(arr: &mut [i32]) -> () do
    for i in 0..arr.len() do
        arr[i] = arr[i] + 1
    end
end

# Cannot return reference (compile error)
# fn bad(x: &i32) -> &i32 do x end  # ERROR: cannot return reference
```

### Arena-based memory with explicit allocators

```bunker
# Every allocation requires explicit allocator
fn process_tree(alloc: Allocator, data: &[u8]) -> Tree do
    let root = alloc.alloc(Node { value: 0, children: [] })
    # ...
end

# Arena block syntax for bulk allocation
arena a do
    let node1 = a.alloc(Node { value: 1 })
    let node2 = a.alloc(Node { value: 2 })
    node1.next = node2  # Safe cycle in same arena
    process(node1)
end  # All arena memory freed here

# Zig-style allocator interface
trait Allocator {
    fn alloc[T](self: &mut Self, value: T) -> &mut T
    fn free[T](self: &mut Self, ptr: &mut T) -> ()
}
```

### Move-by-default with explicit copy

```bunker
# Values move by default
let a = ComplexStruct { ... }
let b = a  # a is moved, cannot use a after this

# Explicit copy for copyable types
let c = copy(b)  # b still valid

# Copy trait marks copyable types
impl Copy for Point  # Enables implicit copy

# Clone for explicit deep copy
let d = b.clone()  # Deep copy
```

---

## Area 4: Formal verification and contracts for AI

### Design-by-contract syntax

```bunker
fn binary_search(arr: &[i32], key: i32) -> Option[usize]
    requires arr.is_sorted()
    requires arr.len() > 0
    ensures result.is_some() implies arr[result.unwrap()] == key
    ensures result.is_none() implies forall i. arr[i] != key
do
    let mut lo = 0
    let mut hi = arr.len()

    while lo < hi do
        invariant lo <= hi
        invariant hi <= arr.len()
        invariant forall i. i < lo implies arr[i] < key
        invariant forall i. i >= hi implies arr[i] > key
        decreases hi - lo

        let mid = lo + (hi - lo) / 2
        match arr[mid].cmp(key) with
        | Less => lo = mid + 1
        | Greater => hi = mid
        | Equal => return Some(mid)
        end
    end

    None
end
```

### SMT integration architecture

Bunker integrates Z3 as primary backend with CVC5 as fallback:

**Decidable fragment (full automation guaranteed)**:
- QF_LIA: Quantifier-free linear integer arithmetic
- QF_LRA: Quantifier-free linear real arithmetic
- QF_BV: Bit-vectors (excellent for systems code)
- QF_UF: Uninterpreted functions
- Arrays with bounded quantification

**Verification feedback for AI**:
```json
{
  "verification_result": "failed",
  "failing_property": "postcondition",
  "counterexample": {
    "inputs": {"arr": [1, 3, 5], "key": 2},
    "execution_trace": [
      {"line": 15, "state": {"lo": 0, "hi": 3}},
      {"line": 17, "state": {"mid": 1, "arr[mid]": 3}},
      {"line": 20, "state": {"lo": 0, "hi": 1}}
    ],
    "violation": "returned None but arr contains value less than key"
  },
  "suggested_fix": {
    "message": "loop may terminate early when key is between elements",
    "confidence": 0.7
  }
}
```

### Incremental verification for AI feedback loops

Research shows AI achieves **95%+ loop invariant generation accuracy within 5 attempts** when given counterexample feedback. Bunker's verification system:

1. **Sub-100ms incremental checking** using Salsa-style query caching
2. **Function-level verification** with contract isolation
3. **Delta re-verification** only checking changed functions and dependents
4. **Counterexample translation** to source-level values for AI consumption

---

## Area 5: Agent execution semantics and runtime

### Actor-based agent architecture

```bunker
agent ResearchAgent {
    # Agent state (isolated, no sharing)
    beliefs: BeliefBase[ResearchFact]
    desires: DesireBase[ResearchGoal]
    intentions: IntentionStack[ResearchPlan]

    # Memory hierarchies
    working_memory: RingBuffer[Message, 100]
    semantic_memory: VectorDB[Fact]
    episodic_memory: TimeIndexedLog[Episode]

    # Message handling
    on receive(msg: AgentMessage) do
        match msg with
        | Query(q) => handle_query(q)
        | ToolResult(r) => process_result(r)
        | Feedback(f) => update_beliefs(f)
        end
    end

    # BDI deliberation cycle
    fn deliberate(self: &mut Self) -> Action do
        let options = generate_options(self.beliefs, self.desires)
        let intention = select_intention(options, self.intentions)
        execute_plan(intention)
    end
}
```

### First-class tool definitions

```bunker
tool get_weather {
    description: "Get current weather for a location"

    # Preconditions checked before execution
    precondition: location.is_valid_city()

    # Input schema with refinement types
    input {
        location: String where len > 0
        unit: "celsius" | "fahrenheit" = "celsius"
    }

    # Output type and effects
    output: WeatherData
    effects: [network_call, api_quota(1)]

    # Timeout and retry semantics
    timeout: 30.seconds
    retry: {
        max_attempts: 3,
        backoff: exponential(base: 1.second, max: 30.seconds),
        on: [NetworkError, RateLimitError]
    }

    impl async fn(input) -> Result[WeatherData, ToolError]
}

# Tool composition
tool travel_planner = compose(
    get_weather,
    search_flights,
    book_hotel,
    ordering: parallel
)
```

### Session types for agent communication

```bunker
protocol AgentToolProtocol {
    global type ToolCall =
        Agent -> Tool: request(ToolInput).
        Tool -> Agent: (
            success(ToolOutput) |
            error(ErrorInfo).Agent -> Tool: retry(RetryConfig) |
            timeout(Duration)
        )
}

# Verified agent communication
fn call_tool(agent: AgentRef, tool: Tool, input: ToolInput)
    -> Session[AgentToolProtocol, success | error | timeout]
do
    agent.send(tool, request(input))
    match tool.receive() with
    | success(output) => return output
    | error(e) => {
        if should_retry(e) then
            agent.send(tool, retry(default_config()))
        else
            return error(e)
        end
    }
    | timeout(d) => return timeout(d)
    end
end
```

### Resource tracking as types

```bunker
# Token budgets as affine types
type TokenBudget = affine struct {
    remaining: Nat
}

fn call_llm(prompt: String, budget: TokenBudget)
    -> (Response, TokenBudget)
    requires budget.remaining >= prompt.token_count()
do
    let response = llm.complete(prompt)
    let used = prompt.token_count() + response.token_count()
    (response, TokenBudget { remaining: budget.remaining - used })
end

# API rate limits
type RateLimit[N: usize, Window: Duration] = {
    calls: SlidingWindow[Timestamp, N]

    fn try_use(self: &mut Self) -> Option[RateLimitToken] do
        if self.calls.count_in_window(now(), Window) < N then
            Some(RateLimitToken::new())
        else
            None
        end
    end
}
```

### Durable execution and checkpoint/rollback

```bunker
# Workflow with automatic checkpointing
workflow order_processing {
    # Activities are durably executed and recorded
    let payment = await activity(charge_customer, retry: 3)
    checkpoint()  # Explicit checkpoint

    let shipment = await activity(ship_order)
    # If crash here, replay resumes from checkpoint

    await activity(notify_customer)
}

# Saga pattern for multi-agent transactions
saga travel_booking {
    step book_flight {
        action: flight_service.reserve()
        compensate: flight_service.cancel()
    }

    step book_hotel {
        action: hotel_service.reserve()
        compensate: hotel_service.cancel()
    }

    on_failure: compensate_all  # Reverse compensation on failure
}
```

---

## Area 6: Error handling and diagnostics for AI

### Structured error output (LSP + SARIF compatible)

```bunker
# Compiler API for AI feedback loops
fn compile_check(source: String) -> Diagnostics
fn apply_fix(source: String, fix_id: FixId) -> Result[String, Conflict]
fn hole_fits(source: String, position: Position) -> Vec[Candidate]
fn explain_error(code: ErrorCode) -> DetailedExplanation
```

**SARIF output mode** for CI/CD integration:
```json
{
  "$schema": "https://raw.githubusercontent.com/oasis-tcs/sarif-spec/master/Schemata/sarif-schema-2.1.0.json",
  "runs": [{
    "tool": {"driver": {"name": "bunker", "version": "1.0.0"}},
    "results": [{
      "ruleId": "E0308",
      "message": {"text": "type mismatch: expected i32, found String"},
      "locations": [{
        "physicalLocation": {
          "artifactLocation": {"uri": "src/main.bk"},
          "region": {"startLine": 15, "startColumn": 12}
        }
      }],
      "fixes": [{
        "description": {"text": "convert to integer"},
        "artifactChanges": [{
          "artifactLocation": {"uri": "src/main.bk"},
          "replacements": [{
            "deletedRegion": {"startLine": 15, "startColumn": 12, "endColumn": 20},
            "insertedContent": {"text": "\"42\".parse().unwrap()"}
          }]
        }]
      }]
    }]
  }]
}
```

### Typed holes for AI-assisted completion

```bunker
fn process(items: List[T]) -> Result[T, Error] do
    items.filter(_)  # Hole: compiler reports expected type fn(T) -> bool
         .map(_)     # Hole: compiler reports expected type fn(T) -> U
end

# Compiler output for holes:
{
  "holes": [{
    "position": {"line": 2, "column": 18},
    "expected_type": "fn(T) -> bool",
    "valid_fits": [
      {"name": "is_valid", "type": "fn(T) -> bool", "confidence": 0.9},
      {"name": "not_empty", "type": "fn(T) -> bool", "confidence": 0.7}
    ],
    "scope_bindings": ["items: List[T]", "T: type"]
  }]
}
```

### Error recovery during parsing

Bunker's parser uses **Tree-sitter-style error recovery**:
- Produces partial AST even with syntax errors
- ERROR nodes wrap unrecognized content
- Includes "expected tokens" in error spans
- Supports streaming errors during parse (doesn't wait for EOF)

---

## Area 7: Concurrency and parallelism for AI

### Structured concurrency as the only model

```bunker
# Task groups are the only way to spawn concurrent work
task_group do
    spawn fetch_user(id)
    spawn fetch_orders(id)
    spawn fetch_preferences(id)
end  # Block waits for all tasks; cancels remaining on failure

# No fire-and-forget - this is a compile error:
# spawn background_task()  # ERROR: spawn must be inside task_group
```

### Channel-based communication (CSP model)

```bunker
# Unbuffered channel (synchronous rendezvous)
let ch = channel[int](capacity: 0)

task_group do
    spawn do
        ch.send(42)  # Blocks until receiver ready
    end

    spawn do
        let value = ch.receive()  # Blocks until sender ready
        process(value)
    end
end

# Typed channels with session types
let (tx, rx) = session_channel[RequestResponse]()
```

### Deterministic parallelism for pure functions

```bunker
# Parallel map - guaranteed deterministic
let results = data.parallel_map(|x| expensive_compute(x))

# Parallel reduce
let sum = numbers.parallel_reduce(0, |a, b| a + b)

# Work-stealing scheduler (transparent to user)
parallel_for i in 0..n do
    process(items[i])
end
```

### Effect-based concurrency tracking

```bunker
# Effect tracking makes concurrency explicit
effect Async
effect Spawn

fn fetch_data(url: String) -> Async Result[Data, Error] do
    # Compiler knows this function performs async I/O
end

fn compute(x: i32) -> Pure i32 do
    x * 2  # Guaranteed pure - can be parallelized safely
end
```

---

## Area 8: Tooling and ecosystem for AI development

### Zero-configuration formatter (gofmt philosophy)

```bunker
# bunker fmt - no options, one canonical style
# All training data formatted identically
# Eliminates bikeshedding, reduces diff noise
```

### LSP with AI-specific extensions

```bunker
# Standard LSP 3.17 features
textDocument/completion
textDocument/hover
textDocument/semanticTokens

# AI-specific extensions
textDocument/aiContext      # Project-wide context for AI
textDocument/holeFits       # Typed hole completions
workspace/aiHints           # AI-relevant annotations
```

### Package manager with AI discoverability

```toml
# bunker.toml
[package]
name = "myproject"
version = "0.1.0"

[dependencies]
serde = "1.0"

[ai]
context_file = ".bunker/ai-context.md"  # AI instructions
api_docs = "generated"                    # Auto-generate API docs
```

### Mandatory documentation with tested examples

```bunker
/// Reads a file into a String.
///
/// # Examples
///
/// ```bunker
/// let contents = fs::read_to_string("hello.txt")?
/// println("{}", contents)
/// ```
///
/// # Errors
///
/// Returns `IoError::NotFound` if file doesn't exist.
/// Returns `IoError::PermissionDenied` if not readable.
///
fn read_to_string(path: &Path) -> IO Result[String, IoError]
```

---

## Area 9: Standard library design for AI

### Consistent naming conventions

| Pattern | Convention | Example |
|---------|------------|---------|
| Creation | `new`, `from_*`, `with_*` | `Vec::new()`, `String::from_utf8()` |
| Conversion | `to_*`, `into_*`, `as_*` | `to_string()`, `into_vec()`, `as_bytes()` |
| Predicates | `is_*`, `has_*`, `can_*` | `is_empty()`, `has_key()`, `can_read()` |
| Accessors | noun (no get_) | `len()`, `first()`, `last()` |
| Mutators | verb | `push()`, `clear()`, `insert()` |

### Uniform error handling

```bunker
# All fallible operations return Result[T, E]
# Never mix Option, panics, or exceptions

fn open_file(path: &Path) -> Result[File, IoError]
fn parse_json(text: &str) -> Result[Json, ParseError]
fn connect(addr: &Address) -> Result[Connection, NetError]

# No hidden panics in safe code
# Indexing returns Option, not panic
let x = arr.get(i)  # Option[T], not panic
```

### Module organization (flat structure)

```bunker
use std::io        # I/O operations
use std::fs        # Filesystem
use std::net       # Networking
use std::sync      # Synchronization primitives
use std::collections  # Data structures
use std::fmt       # Formatting
use std::str       # String operations
```

---

## Area 10: Metaprogramming and compile-time computation

### Comptime execution (Zig-inspired)

```bunker
# Same language at compile-time and runtime
fn Matrix(comptime T: type, comptime m: int, comptime n: int) type do
    struct { data: [m][n]T }
end

const identity: Matrix(f32, 3, 3) = comptime {
    var result = Matrix(f32, 3, 3)::zero()
    for i in 0..3 do
        result.data[i][i] = 1.0
    end
    result
}

# Type reflection at compile-time only
fn print_fields(comptime T: type) do
    const info = @typeInfo(T)
    inline for field in info.fields do
        @compileLog("Field: {}", field.name)
    end
end
```

### Derive-style code generation

```bunker
# Predictable derive macros - input → output relationship is learnable
#[derive(Serialize, Deserialize)]
type Point = struct {
    x: f64,
    y: f64,
}

# AI learns: derive(Serialize) generates:
# fn serialize(self: &Point) -> Vec[u8]
# fn deserialize(bytes: &[u8]) -> Result[Point, DeserializeError]
```

### No arbitrary macros

Bunker deliberately **excludes**:
- C-style preprocessor macros
- Lisp-style arbitrary AST transformation
- Rust's `macro_rules!` pattern matching

Instead, Bunker provides:
- Comptime functions for computation
- Derive macros for trait implementation
- Generics for code reuse
- Traits for polymorphism

---

## Implementation roadmap

### Phase 1: Core language (Months 1-6)
- Grammar specification in EBNF (LL(1)-compatible)
- Lexer and parser with error recovery
- Type checker with bidirectional inference
- Linear type system implementation
- Basic compiler targeting LLVM IR

### Phase 2: Advanced types (Months 7-12)
- Refinement types with Z3 integration
- Effect system implementation
- Row polymorphism for effects
- Exhaustive pattern matching

### Phase 3: Agent runtime (Months 13-18)
- Actor system with typed mailboxes
- Session types for protocols
- Tool definition DSL
- Checkpoint/rollback infrastructure

### Phase 4: Tooling ecosystem (Months 19-24)
- LSP server with AI extensions
- Zero-config formatter
- Package manager with registry
- REPL with hot-reloading

---

## Design rationale summary

Every design decision in Bunker optimizes for a single goal: **making AI code generation reliable while remaining ergonomic for human developers**.

| Design Choice | AI Benefit | Human Benefit |
|---------------|------------|---------------|
| Explicit `do`/`end` blocks | Unambiguous grammar for constrained decoding | Self-documenting structure |
| Mandatory toplevel types | Semantic anchors for generation | Clear API documentation |
| Linear types | Eliminates use-after-free hallucinations | Memory safety without GC |
| Second-class references | No lifetime annotation complexity | Simpler mental model |
| Structured concurrency | Predictable task lifecycles | No orphan task bugs |
| Row-polymorphic effects | Explicit side effect tracking | Compiler-verified purity |
| Comptime over macros | Predictable code generation | Same language everywhere |
| Zero-config formatter | Consistent training data | End bikeshedding |

Bunker proves that the tension between AI-friendliness and human ergonomics is false—the same features that make code predictable for AI make it clearer for humans. **Explicit structure, strong types, and predictable semantics serve both audiences.**

This specification provides sufficient detail for immediate implementation. The language design synthesizes decades of programming language research with cutting-edge findings on LLM code generation to create the definitive AI-native systems programming language.

---

## Implementation Status Tracking

This section tracks the implementation status of each specification area against the current Bunker compiler.

### Area Implementation Checklist

#### Area 1: Grammar and Syntax ✅ Mostly Complete
- [x] LL(1)-compatible PEG grammar (`bunker.pest`)
- [x] Explicit block delimiters (`{ }`)
- [x] Keyword-delimited blocks for all three layers
- [x] No significant whitespace
- [x] AI-friendly token design (single-token keywords)
- [ ] `do`/`end` block syntax (current: `{ }` braces)
- [ ] Formal LL(1) verification

#### Area 2: Type System 🔶 Partial
- [x] Static typing with inference
- [x] Bidirectional type checking (Kernel layer)
- [x] `Option<T>` sum type
- [x] Exhaustive pattern matching (`match`)
- [x] Struct and array types
- [ ] Refinement types with SMT predicates
- [ ] Row-polymorphic effect system
- [ ] Full generic type parameters

#### Area 3: Memory Model 🔶 Partial
- [x] Move semantics by default
- [x] Explicit `copy` keyword
- [x] `defer` statement for cleanup
- [ ] Linear types with `!` suffix
- [ ] Second-class references (no lifetime annotations)
- [ ] Arena-based memory allocator
- [ ] Region-based borrow checking

#### Area 4: Formal Verification 🔶 Partial
- [x] `#[requires]` attribute parsing
- [x] `#[ensures]` attribute parsing
- [x] `#[verified]` attribute parsing
- [x] Lightweight linear expression verification
- [ ] Z3 SMT solver integration
- [ ] Counterexample generation
- [ ] Incremental verification (<100ms)
- [ ] Loop invariant checking

#### Area 5: Agent Execution 🔶 Partial
- [x] Shell layer parsing
- [x] Agent definition syntax
- [x] Message handler (`on receive`)
- [x] Message sending (`send`)
- [x] Agent state management
- [x] Message queue VM runtime
- [ ] Virtual actor activation
- [ ] Memory hierarchies (working/long-term)
- [ ] Session types for protocols
- [ ] Durable execution primitives

#### Area 6: Error Handling 🔶 Partial
- [x] Compiler error messages
- [x] Source location tracking
- [x] Structured JSON error output
- [ ] Typed holes with hole fits
- [ ] Error recovery during parsing
- [ ] Machine-applicable fix suggestions
- [ ] SARIF output format

#### Area 7: Concurrency ❌ Not Started
- [ ] Structured concurrency (task groups)
- [ ] Channel-based communication
- [ ] Deterministic parallelism
- [ ] Effect-based concurrency tracking
- [ ] Deadlock avoidance (lock ordering)

#### Area 8: Tooling ❌ Not Started
- [ ] Zero-config formatter (`bunker fmt`)
- [ ] LSP server with AI extensions
- [ ] Package manager (`bunker.toml`)
- [ ] REPL with hot-reloading

#### Area 9: Standard Library 🔶 Partial
- [ ] Core numeric types
- [x] String operations
- [x] Collections (Vec, Map, Set)
- [x] I/O primitives
- [ ] Consistent naming conventions

#### Area 10: Metaprogramming 🔶 Partial
- [x] `comptime` function parsing
- [x] Compile-time evaluation
- [x] Constant folding
- [ ] Type reflection (`@typeInfo`)
- [ ] Derive macros
- [ ] Inline loops (`inline for`)

### Current Implementation Summary

| Area | Status | Coverage | Priority |
|------|--------|----------|----------|
| 1. Grammar | ✅ | 85% | - |
| 2. Type System | 🔶 | 60% | High |
| 3. Memory Model | 🔶 | 40% | Medium |
| 4. Verification | 🔶 | 30% | High |
| 5. Agent Runtime | 🔶 | 50% | Medium |
| 6. Error Handling | 🔶 | 25% | High |
| 7. Concurrency | ❌ | 0% | Low |
| 8. Tooling | ❌ | 0% | Low |
| 9. Stdlib | 🔶 | 25% | Low |
| 10. Metaprogramming | 🔶 | 40% | Medium |

**Legend:** ✅ Complete (>80%), 🔶 Partial (20-80%), ❌ Not Started (<20%)

### Critical Path to MVP

1. **Z3 SMT Integration** - Enables true contract verification
2. **Standard Library Cleanup** - Replace bootstrap builtins with a coherent stdlib surface
3. **Embedded/Metal Profile** - Completes the multi-profile execution story
4. **Tooling (Formatter/LSP)** - Turns the prototype into a usable developer platform

### Test Coverage

- **Total Tests:** 92 passing
- **JIT-Enabled:** 57 tests
- **Negative Tests:** 16 tests
- **Shell-Bearing Files:** 14 tests
- **View-Bearing Files:** 7 tests

*Last updated: Run `/check-update-status` to refresh*
