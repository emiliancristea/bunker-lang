# Bunker Language: Complete Technical Specification
## An AI-Native Systems Programming Language Designed from First Principles

> **See also:** [SPECIFICATION.md](SPECIFICATION.md) - The Definitive AI-Native Systems Programming Language Specification covering grammar theory, type systems, memory models, formal verification, agent semantics, and tooling

**Bunker** is a systems programming language designed from first principles to be optimal for both human developers and AI agents (LLMs like Claude, GPT-4, Codex) to write, understand, and execute. This specification synthesizes cutting-edge research across grammar-constrained decoding, type-constrained generation, memory safety, formal verification, and agent-native execution to define a language that maximizes AI code generation accuracy while maintaining the power and performance expected of a systems language.

---

# Part 1: Grammar and Syntax Design for AI-Native Code Generation

The foundation of an AI-native language lies in its grammar design. Research demonstrates that **grammar-constrained decoding reduces syntax errors by 96%** while maintaining near-zero overhead when properly designed.

## 1.1 Grammar-constrained decoding optimization

Bunker's grammar is designed specifically for efficient constrained decoding during LLM generation. Modern frameworks like **SynCode** and **XGrammar** demonstrate that proper grammar design enables dramatic improvements in AI-generated code quality.

**XGrammar achieves 100x speedup** over previous constrained decoding solutions through a key insight: dividing vocabulary into context-independent tokens (prechecked offline, typically **>99% of all tokens**) and context-dependent tokens (resolved at runtime). Bunker's grammar is designed to maximize the context-independent token ratio.

The grammar follows strict **LL(1) parseability** for efficient token lookup during generation:

```ebnf
program       ::= declaration*
declaration   ::= fn_decl | type_decl | agent_decl | const_decl
fn_decl       ::= 'fn' IDENT '(' params ')' return_type? contracts? block
block         ::= '{' statement* '}'
statement     ::= let_stmt | expr_stmt | if_stmt | match_stmt | loop_stmt
```

Context-sensitive features like Python's significant whitespace are explicitly avoided. XGrammar's Python support deliberately "ignores indentation" due to complexity—Bunker eliminates this problem entirely through explicit block delimiters.

**Trade-offs between expressiveness and efficiency** favor simplicity: a terminal vocabulary under 100 distinct symbols enables efficient DFA construction, while avoiding left recursion and ensuring unambiguous single-token lookahead. Regular sublanguages for identifiers, numbers, and strings further simplify parsing.

## 1.2 Syntax design for transformer architectures

**MoonBit's "flattened/linear design"** provides the template for transformer-optimized syntax. The key insight is that autoregressive transformers have complexity increasing quadratically with context window, making languages "without nesting" more KV-cache friendly at multiple levels: RAG retrieval, decoder correction, and backtracking during constrained decoding.

Bunker adopts **structural interface implementation** where methods implementing an interface aren't confined to specific code blocks:

```bunker
// Linear: Methods can be anywhere, not nested in impl blocks
fn Robot::think(self) -> String {
    let context = self.get_context();
    self.llm.generate(context)
}

fn Robot::act(self, action: Action) -> Result {
    match action {
        Action::Move(dir) => self.move_to(dir),
        Action::Speak(msg) => self.say(msg),
    }
}

// Type automatically implements interfaces by having required methods
type Robot {
    llm: LLM,
    position: Vec3,
}
```

This enables **nearly linear generation** with minimized KV cache misses. Programs can be developed top-to-bottom without back-and-forth navigation that confuses transformer attention.

Empirical research confirms that **explicit block delimiters help LLMs understand code structure** better than indentation. Studies on fault localization found that "Java explicitly expresses code branching with tokens like `{` and `}` that LLM successfully picks and thus captures the branching logic better" than Python's indentation-based blocks.

## 1.3 Lexical design principles

Bunker's lexical design follows principles that reduce AI hallucination:

| Element | Design Choice | Rationale |
|---------|--------------|-----------|
| **Keywords** | `fn`, `let`, `if`, `for`, `match`, `return` | Common, well-represented in training data |
| **Block delimiters** | `{ }` | Single tokens, explicit structure, best LLM accuracy |
| **Statement terminators** | Optional `;` | Familiar, reduces parse ambiguity |
| **Type annotations** | Postfix `: Type` | Common pattern, easy to parse |
| **Comments** | `//` and `/* */` | Standard, tokenizer-friendly |

**Identifier conventions** follow standard `[a-zA-Z_][a-zA-Z0-9_]*` patterns aligned with training data. Unicode identifiers are avoided for AI reliability. Literal syntax uses distinct, unambiguous formats: `123` for integers, `3.14` for floats, `"string"` for strings, `0x` prefix for hex, `0b` for binary.

**Whitespace is insignificant** (like C/Java/Rust), keeping the grammar truly context-free and simplifying constrained decoding mask computation.

---

# Part 2: Type System Design for AI Constraint and Correctness

Type systems serve as the primary mechanism for constraining AI-generated code. Research demonstrates that **type-constrained decoding reduces compilation errors by more than half** while significantly increasing functional correctness.

## 2.1 Static typing for AI error reduction

Bunker employs **bidirectional type inference** combining checking mode (↓) and synthesis mode (↑). The checking mode allows type constraints to propagate *downward* during generation, constraining valid token choices before they're generated:

```bunker
// Module boundary: explicit annotation required (synthesis point)
pub fn process(data: Buffer) -> Result<i32, Error> {
    // Local: inferred via bidirectional checking
    let x = parse(data)?;  // Type of x inferred from context
    x + 1                  // Checked against i32 return type
}
```

Type-constrained generation uses **prefix automata** and **inhabitable type search** to mask invalid tokens during generation. When generating an expression with expected type `i32`, valid tokens include numeric literals, variables of type `i32`, and function calls returning `i32`—while string literals, boolean values, and void function calls are masked out.

The balance between inference and explicit annotations follows a strategic principle:

- **Require** type annotations at module boundaries (public functions, structs)
- **Infer** types for local variables and closures
- **Allow** explicit annotations anywhere for AI guidance in complex cases

## 2.2 Type system complexity versus AI accuracy

Research indicates clear trade-offs between type system complexity and AI generation accuracy:

**Higher-kinded types correlate with lower LLM accuracy** due to less training data exposure, more abstract patterns to instantiate, and complex type-level reasoning requirements. Bunker avoids complex HKT abstractions in favor of concrete, AI-friendly patterns:

```bunker
// AVOID: Abstract HKT that confuses AI
trait Functor<F: * -> *> {
    fn map<A, B>(fa: F<A>, f: A -> B) -> F<B>;
}

// PREFER: Concrete pattern AI can reliably implement
trait Mappable<T> {
    fn map<U>(self, f: T -> U) -> Self<U>;
}
```

**Dependent types help when specifications are close to implementations** and involve simple size/length dependencies. They hurt when requiring complex proof obligations or undecidable verification conditions:

```bunker
// Good: Simple dependent type AI can handle
fn get<T, const N: usize>(arr: Array<T, N>, idx: {i: usize | i < N}) -> T

// Good: Automatic refinement with clear relationship
fn push<T, const N: usize>(vec: Vec<T, N>, item: T) -> Vec<T, N+1>
```

**Sum types with exhaustive pattern matching** are highly beneficial for AI. Compiler enforcement prevents missed cases, and explicit structure reduces hallucination:

```bunker
enum Result<T, E> {
    Ok(T),
    Err(E),
}

fn handle(r: Result<i32, Error>) -> i32 {
    match r {
        Ok(value) => value,
        Err(e) => {
            log_error(e);
            0
        }
    }
    // Compiler error if case missing - AI sees complete pattern
}
```

## 2.3 Refinement types for verification

Bunker adopts **Liquid Haskell's approach** to refinement types with SMT-decidable predicates only:

```bunker
// Basic refinements
type PositiveInt = {v: i32 | v > 0}
type NonEmptyVec<T> = {v: Vec<T> | len(v) > 0}

// Function with refinements - SMT verifies automatically
fn divide(x: i32, y: {v: i32 | v != 0}) -> i32 {
    x / y  // Safe: y cannot be zero
}

// Refinements propagate through inference
fn average(nums: NonEmptyVec<f64>) -> f64 {
    sum(nums) / len(nums)  // Safe: len(nums) > 0 from type
}
```

The key is restricting predicates to **SMT-decidable logic**: linear arithmetic, equality, uninterpreted functions. Liquid Haskell proves **96% of recursive functions automatically** with only 1.7 lines of termination annotations per 100 lines of code. Non-linear arithmetic and universal quantification over unbounded domains are avoided.

## 2.4 Type error messages for AI feedback

Error messages are designed for machine consumption with structured JSON output:

```json
{
  "errors": [{
    "code": "E0308",
    "message": "mismatched types",
    "location": {"file": "src/main.bk", "line": 42, "col": 15},
    "expected_type": "i32",
    "found_type": "String",
    "suggestion": {
      "message": "try converting the String to i32",
      "replacement": "value.parse::<i32>().unwrap()",
      "applicability": "MachineApplicable",
      "confidence": 0.85
    }
  }]
}
```

Research shows that **compiler feedback enables 62.5% repair accuracy versus 34% without**. Critical fields include `expected_type`/`found_type` for targeted fixes, concrete `suggestion` with replacement code, and `applicability` indicators distinguishing machine-applicable fixes from those requiring review.

---

# Part 3: Memory Model and Ownership for AI Comprehension

Rust's borrow checker is the primary obstacle for LLM code generation, with **94.8% of failures** in code translation stemming from compilation errors—significantly higher than 58-83% in other languages. Bunker adopts alternative ownership models that maintain memory safety while enabling reliable AI generation.

## 3.1 Ownership without borrow checker complexity

**Microsoft's RustAssistant study** found LLMs achieve only ~74% peak accuracy fixing Rust compilation errors. The most problematic categories are lifetime annotations (E0499), borrow conflicts (E0502), and trait implementation (E0277). LLMs struggle because the borrow checker operates on a **per-object basis**, requiring tracking complex non-local invariants across function boundaries.

Bunker adopts **Vale's region borrow checking** operating on **groups of objects** rather than individual objects:

```bunker
// Region markers often inferred by compiler
pure fn compute<'r readonly, 'i mutable>(
    data: &'r World
) -> Result<'i> {
    // 'r = immutable region (zero-cost references, free aliasing)
    // 'i = mutable region (can allocate/modify)
    let items = data.objects*.transform();
    items.filter(|x| x.valid)
}
```

Benefits include: region markers often inferred, immutable regions enabling zero-cost references, free aliasing within regions, and opt-in complexity allowing entire programs without knowing about regions.

**Austral's linear types** provide the resource management foundation:

```bunker
// Linear types marked with ! - must be used exactly once
type File!;

fn open_file(path: String) -> File!;
fn read_all(file: &File!) -> String;  // Borrow for read
fn close(file: File!) -> ();          // Consumes the file

// Usage: value "threaded" through code
let f: File! = open_file("data.txt");
let content = read_all(&f);
close(f);  // Required - won't compile without consuming
```

Austral's linearity checker is **~700 lines of OCaml**—orders of magnitude simpler than Rust's borrow checker—yet catches every lifecycle error at compile time.

## 3.2 Explicit copy and move semantics

Bunker eliminates implicit behavior that confuses AI:

```bunker
// Make copy ALWAYS explicit
let a: String = "hello";
let b = a.copy();        // Explicit copy
let c = move a;          // Explicit move (a now invalid)

// References for borrowing
fn process(data: &String) { ... }  // Always borrows
```

Unlike Rust where `Copy` trait determines whether assignment moves or copies, Bunker uses explicit keywords. What you see is what you get—all types behave identically, and ownership is clear at every call site.

## 3.3 Arena-based memory for complex structures

**Arena scopes** handle self-referential and cyclic structures trivially:

```bunker
arena game_frame {
    // All allocations share arena lifetime
    let graph = Graph::new();
    let node1 = graph.add_node("A");
    let node2 = graph.add_node("B");
    node1.connect(node2);  // Cyclic references safe!
}  // All memory freed here
```

Arenas eliminate individual ownership tracking—all objects share arena lifetime, making cache-friendly adjacent allocations with bulk deallocation.

## 3.4 Deterministic resource management

Bunker uses **defer statements** for visible, predictable cleanup:

```bunker
fn process_file(path: String) -> Result<Data> {
    let file = File::open(path)?;
    defer file.close();  // Always visible, runs at scope end

    let data = file.read_all()?;
    Ok(data)
}
```

Research shows defer's visibility helps AI generate correct cleanup patterns. Unlike RAII where cleanup is hidden in destructors, defer statements are lexically visible and run in reverse declaration order.

---

# Part 4: Design-by-Contract and Formal Verification

Contracts create a powerful synergy with AI generation: they constrain the output space while AI assists in generating and refining specifications, creating a virtuous cycle toward correct-by-construction software.

## 4.1 Contract specification syntax

Bunker adopts a hybrid syntax drawing from SPARK/Ada's maturity and Dafny's concision:

```bunker
fn find_max(arr: &[i32]) -> i32
    requires arr.len() > 0
    ensures result >= arr[i] for all i in 0..arr.len()
    ensures result in arr
{
    // implementation
}

// Contract cases for behavioral partitioning
fn saturating_add(total: &mut i32, incr: i32)
    requires incr >= 0
    contract_cases {
        old(total) + incr < THRESHOLD => total == old(total) + incr,
        _ => total == THRESHOLD
    }

// Frame specifications
fn swap(arr: &mut [i32], i: usize, j: usize)
    requires i < arr.len() && j < arr.len()
    modifies arr
    ensures arr[i] == old(arr[j]) && arr[j] == old(arr[i])
```

Key syntax elements include `old(expr)` for pre-state values, `result` for return values in postconditions, `forall`/`exists` for quantification, and `decreases` for termination metrics.

## 4.2 Stanford's Clover framework integration

**Clover** implements closed-loop verifiable code generation through six consistency checks forming a triangle between code, annotations, and docstrings:

| Check | Method | Purpose |
|-------|--------|---------|
| anno-sound | Dafny verifier | Code satisfies annotations |
| anno-complete | LLM + Compiler | Annotations capture code behavior |
| anno2doc | LLM semantic comparison | Annotations imply docstring |
| doc2anno | LLM + Verifier | Docstring generates equivalent annotations |
| doc2code | LLM + Unit tests | Docstring generates equivalent code |
| code2doc | LLM semantic comparison | Code generates equivalent docstring |

Clover achieves **87% acceptance rate** for correct examples with **100% rejection** of incorrect/adversarial examples. The reconstruction test principle states that correct mappings have significant probability of being reconstructed; incorrect mappings have negligible probability.

## 4.3 SMT solver integration

Bunker integrates Z3/CVC5 through verification condition generation:

```
┌─────────────────────────────────────────────┐
│         Bunker Source with Contracts        │
└────────────────────┬────────────────────────┘
                     ↓
┌─────────────────────────────────────────────┐
│    Verification Condition Generator         │
│    (Weakest Precondition Calculus)          │
└────────────────────┬────────────────────────┘
                     ↓
┌─────────────────────────────────────────────┐
│           SMT-LIB Format VCs                │
└────────────────────┬────────────────────────┘
                     ↓
┌─────────────────────────────────────────────┐
│    Z3/CVC5: SAT (counterexample)            │
│             UNSAT (proven)                  │
│             UNKNOWN (timeout)               │
└─────────────────────────────────────────────┘
```

When verification fails, counterexamples are formatted for AI repair: "Counterexample: when x=5 and y=-3, postcondition fails because..." This enables effective generate-verify-repair loops.

## 4.4 Incremental verification levels

Following SPARK's adoption model:

| Level | Guarantees | Requirements |
|-------|------------|--------------|
| **Bronze** | Initialization, data flow | Global aspects |
| **Silver** | Runtime error freedom | Preconditions, type constraints |
| **Gold** | Key functional properties | Partial postconditions |
| **Platinum** | Full functional correctness | Complete contracts with invariants |

This enables teams to adopt verification incrementally, starting with simple contracts and progressing to full formal verification for critical code.

---

# Part 5: Agent Execution Semantics and Runtime Primitives

Bunker provides first-class language support for AI agent execution, drawing from actor systems (Akka, Erlang/OTP, Orleans), durable execution platforms (Temporal.io), and modern AI frameworks.

## 5.1 Virtual actors for AI agents

Bunker adopts Microsoft Orleans' **virtual actor** pattern where agents always exist conceptually and are activated on-demand:

```bunker
agent CustomerSupport<CustomerId: String> {
    // Virtual actor identity - auto-activated on message
    identity: CustomerId
    activation: on_demand

    // Isolated state with automatic persistence
    state {
        customer: Customer,
        conversation: Vec<Message>,
        satisfaction: f64,
    }

    // Supervision for fault tolerance
    supervise {
        strategy: one_for_one,
        max_restarts: 3,
        restart_window: 60s,
    }

    // Typed message handlers
    receive HandleQuery(query: String) -> Response {
        let context = self.memory.retrieve(query);
        let response = self.llm.generate(query, context);
        self.conversation.push(Message::new(query, response));
        Response { content: response.text }
    }

    // Lifecycle hooks
    on_activate() {
        self.customer = CustomerService::load(self.identity);
    }
}
```

Key properties: virtual existence (addressable by identity), single-threaded illusion (sequential per-agent processing), hierarchical supervision (parent-defined restart strategies), and state encapsulation (no shared memory).

## 5.2 Agent memory hierarchies

Bunker provides built-in memory primitives for AI agents:

```bunker
memory WorkingMemory {
    capacity: 128_000 tokens,
    eviction: LRU | Summarize | Priority,

    fn push(content: Content) {
        if self.usage() > 0.9 * self.capacity {
            self.compress()  // LLM-based summarization
        }
        self.buffer.push(content)
    }
}

memory LongTermMemory {
    vector_store: VectorBackend,  // Semantic similarity search
    graph_store: GraphBackend,    // Entity relationships

    fn retrieve(query: Query, config: RetrievalConfig) -> MemoryResults {
        let vector_results = self.vector_store.similarity_search(query);
        let graph_results = self.graph_store.traverse(query.entities);
        merge(vector_results, graph_results, config.fusion)
    }

    @background
    fn consolidate(episode: Conversation) {
        let facts = extract_facts(episode);
        self.graph_store.upsert(facts);
        self.vector_store.index(episode.embedding());
    }
}
```

Memory types include working memory (bounded context window), episodic memory (past interactions), semantic memory (factual knowledge), and procedural memory (learned behaviors).

## 5.3 Type-safe tool definitions

Tools are defined with contracts specifying preconditions and effects:

```bunker
tool SearchDatabase {
    description: "Search the product database"

    parameters {
        query: String { min_length: 3, max_length: 500 },
        category: Option<Category>,
        limit: u32 = 10 { range: 1..100 },
    }

    requires {
        self.database.is_connected(),
        caller.has_permission("database:read"),
    }

    effects {
        reads: ["products"],
        modifies: [],
    }

    execute(params: Self::Params) -> Result<Vec<Product>, ToolError> {
        timeout: 30s,
        retry: { max_attempts: 3, backoff: exponential },

        let results = self.database.search(params.query);
        Ok(results.take(params.limit))
    }

    fallback() -> Vec<Product> {
        self.cache.get_recent_products()
    }
}
```

Tool composition enables pipelines with type-safe chaining and partial failure handling.

## 5.4 Inter-agent communication

Typed message channels with delivery guarantees:

```bunker
message QueryRequest {
    query_id: Uuid,
    content: String,
    priority: Priority,
    reply_to: Channel<QueryResponse>,
}

channel<T: Message> {
    pattern: RequestResponse | PubSub | Stream,
    buffer_size: usize = 1000,
    delivery: AtLeastOnce | ExactlyOnce,
    timeout: Duration = 30s,
}

// Multi-agent coordination protocol
protocol MultiAgentDebate {
    participants: [Proposer, Critic, Synthesizer],
    max_rounds: 5,

    round {
        1. Proposer.propose(topic) -> Proposal
        2. Critic.critique(Proposal) -> Critique
        3. Proposer.respond(Critique) -> RevisedProposal
        4. if Synthesizer.is_consensus(RevisedProposal, Critique) { break }
    }

    finalize {
        Synthesizer.synthesize(all_proposals) -> FinalAnswer
    }
}
```

## 5.5 Durable execution primitives

Inspired by Temporal.io, Bunker provides durability guarantees:

```bunker
@durable
agent LongRunningResearcher {
    workflow research(topic: Topic) -> Report {
        // Each step recorded in event history
        let plan = checkpoint { self.create_plan(topic) };

        for source in plan.sources {
            // Activities have retry semantics
            let data = activity {
                operation: fetch_source(source),
                timeout: 2m,
                retry: { max: 3, backoff: exponential(1s) },
            };
            self.findings.push(analyze(data));
            checkpoint;  // Explicit persistence point
        }

        checkpoint { self.synthesize(self.findings) }
    }

    // Human-in-the-loop with durable waiting
    fn get_approval(draft: Draft) -> Approval {
        signal approval_signal: Approval;
        wait_for(approval_signal, timeout: 7.days)  // Survives restarts
    }
}
```

Workflows run to completion despite infrastructure failures through automatic state recreation from event history.

---

# Part 6: Error Handling and Diagnostics for AI Feedback Loops

Research demonstrates that **with compiler feedback, LLMs achieve 62.5% repair accuracy versus 34% without**. Bunker's error handling is designed specifically for effective AI self-repair cycles.

## 6.1 Result types over exceptions

Bunker uses **Result types with the `?` operator** for mechanical error propagation:

```bunker
fn process_data(path: String) -> Result<Data, IoError | ParseError> {
    let content = read_file(path)?;       // Propagate IoError
    let data = parse_json(content)?;      // Propagate ParseError
    Ok(data)
}

// Pattern matching for detailed handling
match process_data(path) {
    Ok(data) => use_data(data),
    Err(IoError::NotFound) => create_default(),
    Err(e) => log_and_retry(e),
}
```

Result types win for AI because: compiler-enforced handling means errors cannot be ignored, signatures make error possibility visible, the `?` operator provides simple mechanical propagation, and there's no hidden control flow unlike exceptions.

## 6.2 Structured compiler diagnostics

Bunker's compiler outputs machine-parseable JSON with AI-optimized fields:

```json
{
  "errors": [{
    "code": "B0142",
    "message": "type mismatch in concurrent task",
    "severity": "error",
    "location": {"file": "src/server.rs", "line": 25, "col": 12},
    "context": {
      "source_snippet": "scope.spawn(process(data))",
      "highlight_range": [12, 17]
    },
    "suggestions": [{
      "message": "wrap the call in an async block",
      "replacement": "async { process(data).await }",
      "applicability": "MachineApplicable",
      "confidence": 0.95
    }],
    "explanation": "spawn() requires an async block because...",
    "fix_command": "bunker fix --apply B0142:25:12"
  }]
}
```

Critical features include: unique error codes for pattern matching, precise source locations, confidence scores for prioritization, and concrete replacement suggestions with applicability ratings.

## 6.3 Generate-compile-fix optimization

The optimal feedback loop structure:

1. Generate code from specification/prompt
2. Check compilability (type errors, ownership errors)
3. Run linter (style, common mistakes)
4. Execute tests if compiles
5. Re-prompt with structured feedback on failure

Research on C-to-Rust translation found that "when the translation system uses feedback loops the differences across models diminish"—good feedback equalizes model performance.

---

# Part 7: Concurrency and Parallelism

LLMs struggle with complex concurrency semantics. Research found they "struggle to accurately handle the subtleties of concurrency and memory models." Bunker adopts **structured concurrency** for maximum AI generation accuracy.

## 7.1 Structured concurrency with nurseries

Bunker's primary concurrency model uses **nurseries** inspired by Python Trio and Kotlin coroutines:

```bunker
nursery |scope| {
    scope.spawn(process_file(file1));
    scope.spawn(process_file(file2));

    // Guaranteed: both tasks complete before scope exits
    // First exception cancels siblings
    // No orphan tasks possible
}
```

Structured concurrency wins for AI because:
- Tasks are lexically scoped to their parent (clear ownership)
- Automatic cleanup prevents resource leaks
- Predictable cancellation propagates to all children
- Error propagation uses exception groups gathering all concurrent errors

## 7.2 Channels for communication

CSP-style channels with ownership transfer:

```bunker
let (tx, rx) = channel<Message>();

nursery |scope| {
    scope.spawn(producer(tx));  // Ownership of tx moves to producer
    scope.spawn(consumer(rx));  // Ownership of rx moves to consumer
}
```

Ownership transfer prevents data races by design—you cannot send on a channel you've given away.

## 7.3 Data race prevention

By design, not by complex analysis:

1. **Actor state is private** - no shared mutable state
2. **Channels transfer ownership** - like Rust's `send`
3. **Nursery tasks share only immutable data** by default
4. **Explicit `shared` annotation** for shared mutable state with automatic locking

```bunker
nursery |scope| {
    let counter = shared AtomicInt(0);
    scope.spawn(|| counter.increment());  // OK: atomic operations
    scope.spawn(|| counter.increment());
}
```

## 7.4 Deadlock avoidance

Type-level lock ordering prevents deadlocks:

```bunker
@lock_order(1)
let lock_a = Mutex::new(data_a);

@lock_order(2)
let lock_b = Mutex::new(data_b);

// Compiler enforces: always acquire lock_a before lock_b
```

---

# Part 8: Module System and Package Management

## 8.1 Flat module structure for AI navigation

Following MoonBit's linear philosophy, Bunker uses a **flat module structure** where:

```bunker
// File: math/vector.bk
module math.vector;

pub type Vec3 { x: f64, y: f64, z: f64 }

pub fn Vec3::dot(self, other: Vec3) -> f64 {
    self.x * other.x + self.y * other.y + self.z * other.z
}

pub fn Vec3::cross(self, other: Vec3) -> Vec3 {
    Vec3 {
        x: self.y * other.z - self.z * other.y,
        y: self.z * other.x - self.x * other.z,
        z: self.x * other.y - self.y * other.x,
    }
}
```

Imports use explicit paths without wildcards that confuse AI:

```bunker
use math.vector.Vec3;
use math.vector.{dot, cross};  // Named imports only
// No: use math.vector.*;      // Wildcards disabled
```

## 8.2 Reproducible package management

Packages use content-addressed dependencies with lockfiles:

```bunker
// bunker.toml
[package]
name = "my_agent"
version = "1.0.0"

[dependencies]
http = { version = "2.3", hash = "sha256:abc123..." }
json = { version = "1.0", hash = "sha256:def456..." }
```

---

# Part 9: Standard Library and Primitives

## 9.1 Core types

```bunker
// Numeric types with explicit overflow behavior
type u8, i8, u16, i16, u32, i32, u64, i64, f32, f64;
type usize, isize;

// Overflow options
let safe: i32 = a.checked_add(b)?;        // Returns Option
let wrapped: i32 = a.wrapping_add(b);     // Wraps on overflow
let saturated: i32 = a.saturating_add(b); // Clamps to max

// Strings are always UTF-8
type String;           // Owned, growable
type &str;            // Borrowed slice

// Collections
type Vec<T>;          // Dynamic array
type Array<T, N>;     // Fixed-size array
type Map<K, V>;       // Hash map
type Set<T>;          // Hash set
```

## 9.2 Consistent API patterns

All collection operations follow predictable patterns AI can learn:

```bunker
// Iterator pattern universal across collections
vec.iter().map(f).filter(p).collect()

// Option/Result combinators
option.map(f).unwrap_or(default)
result.map_err(transform)?

// Naming conventions
.len()      // Always returns count
.is_empty() // Always returns bool
.get(i)     // Always returns Option
.get_or(i, default)  // Returns value
```

---

# Part 10: Tooling and Ecosystem

## 10.1 Language server with typed holes

Bunker's LSP extension exposes rich type context to AI systems:

```bunker
fn process(data: []const u8) -> Result {
    let parsed = parse(data) catch return ?parse_error;  // Typed hole
    transform(parsed, ?transformation_logic)              // Typed hole
}
```

The LSP reports for each hole:
- Expected type
- All variables in scope with types
- Valid hole fits (expressions that type-check)
- Relevant function signatures

Research shows typed holes **dramatically improve LLM code generation accuracy** by providing precise context.

## 10.2 Canonical formatter

Bunker includes a mandatory, zero-configuration formatter:

```bash
bunker fmt           # Format all files
bunker fmt --check   # Verify formatting
```

**All code must be formatted before entering training datasets.** This ensures:
- Identical constructs tokenize identically
- Models focus on semantics, not style
- AI-generated code matches corpus style
- No style debates or inconsistencies

## 10.3 Training data strategy

Following JetBrains' Kotlin ML Pack approach:

| Dataset | Purpose | Size |
|---------|---------|------|
| **BunkerStack** | Full permissively-licensed corpus | Millions of files |
| **BunkerStack-clean** | Curated high-quality examples | 25,000 files |
| **BunkerExercises** | Instruction-tuning dataset | 15,000 tasks |
| **BunkerEval** | Expert-written benchmark | 200+ problems |

Research shows **fine-tuning on curated instruction datasets produces best results** (55.28% pass@1), far exceeding raw large corpus training.

---

# Part 11: Embedded and Systems Programming Features

## 11.1 Compile-time computation

Bunker adopts **Zig's comptime** with required evaluation:

```bunker
// Compile-time evaluated generic
fn Vec(comptime T: type, comptime N: usize) type {
    return struct {
        data: [N]T,

        pub fn map(self: @This(), comptime f: fn(T) -> T) @This() {
            var result: @This() = undefined;
            inline for (self.data, 0..) |elem, i| {
                result.data[i] = f(elem);
            }
            return result;
        }
    };
}

// Type reflection
fn serialize(comptime T: type, value: T) []u8 {
    return switch (@typeInfo(T)) {
        .Int => |info| int_to_bytes(value, info.bits),
        .Struct => |info| struct_to_bytes(value, info.fields),
        else => @compileError("unsupported type"),
    };
}
```

Key properties: types as first-class values at compile time, `@typeInfo` for reflection, no I/O in comptime (hermetic, cacheable), and required evaluation (not optional optimization).

## 11.2 Inline assembly

```bunker
fn read_tsc() -> u64 {
    return asm volatile(
        "rdtsc; shl rdx, 32; or rax, rdx",
        : [ret] "=rax" -> u64,
        : ,
        : "rdx"
    );
}

// Memory-mapped I/O
const UART = comptime mmio(0x4000_0000, struct {
    data: volatile u8,
    status: volatile u8,
});
```

## 11.3 Target profiles

```bunker
#![profile(embedded)]  // No std, no heap, static allocation only
#![profile(server)]    // Full std, async runtime, heap allocation
#![profile(wasm)]      // WebAssembly target, sandboxed

// Conditional compilation based on profile
comptime if (@profile() == .embedded) {
    // Stack-only implementation
} else {
    // Heap implementation
}
```

---

# Part 12: Cross-Layer Integration (Kernel/Shell/View)

## 12.1 Functional core, imperative shell architecture

Bunker enforces architectural boundaries at the type level:

```bunker
// FUNCTIONAL CORE - Pure, no effects
@pure
module core {
    fn calculate_discount(order: Order, rules: Rules) -> Money {
        rules.reduce(|acc, rule| rule.apply(order, acc), order.total)
    }

    fn reduce_state(state: State, action: Action) -> State {
        match action {
            Action::Increment => State { count: state.count + 1, ..state },
            Action::Decrement => State { count: state.count - 1, ..state },
        }
    }
}

// IMPERATIVE SHELL - I/O, effects, orchestration
@impure
module shell {
    async fn process_order(order_id: String) -> Result<()> {
        let order = database.fetch(order_id).await?;       // I/O
        let rules = load_discount_rules().await?;           // I/O
        let discounted = core::calculate_discount(order, rules); // Pure
        database.save(discounted).await?;                   // I/O
        Ok(())
    }
}
```

The `@pure` annotation is enforced: pure functions cannot perform I/O, call impure functions, or modify external state. This makes the core trivially testable with no mocks needed.

## 12.2 Reactive view layer

Views are derived from state via pure functions:

```bunker
@view
module view {
    fn render(state: AppState) -> View {
        View {
            text: format!("Count: {}", state.count),
            children: [
                Button { label: "+", on_click: Action::Increment },
                Button { label: "-", on_click: Action::Decrement },
            ]
        }
    }
}
```

State flows unidirectionally: View emits actions → Shell dispatches to Core reducers → New state triggers view re-render.

## 12.3 Compilation strategies

Each layer can use optimized compilation:

- **Core**: Aggressive inlining, constant propagation, SMT verification
- **Shell**: Async runtime integration, effect tracking, resource management
- **View**: Target-specific rendering (native, web, terminal)

---

# Summary: Bunker Language Design Principles

| Principle | Implementation | Benefit |
|-----------|----------------|---------|
| **Linear syntax** | Structural interfaces, no nested impl blocks | KV-cache friendly, linear generation |
| **Explicit everything** | No implicit copy/move, visible cleanup | AI understands exactly what happens |
| **Type-constrained generation** | Bidirectional inference, refinement types | >50% fewer compilation errors |
| **Region-based ownership** | Vale-style regions, Austral-style linear types | Avoids borrow checker complexity |
| **Contract-first** | SPARK/Dafny contracts, Clover consistency | Specifications constrain output space |
| **Structured concurrency** | Nurseries, ownership-transferring channels | No orphan tasks, race-free by design |
| **Rich diagnostics** | Structured JSON, confidence scores, fix commands | Enables 62.5% repair accuracy |
| **Virtual actors** | Orleans-style agents with durable execution | First-class AI agent support |
| **Compile-time computation** | Zig-style comptime with type reflection | Predictable, deterministic evaluation |
| **Canonical formatting** | Mandatory formatter, curated training data | Consistent tokenization, better training |

Bunker represents a fundamental rethinking of programming language design for the AI era. By optimizing every layer—from grammar structure to runtime semantics—for both human comprehension and AI generation accuracy, Bunker positions itself as the definitive AI-native systems programming language. The design synthesizes lessons from cutting-edge research in constrained decoding, type-directed generation, formal verification, and agent architectures into a cohesive whole that advances the state of the art in human-AI collaborative software development.

---

# Appendix A: Complete Grammar Reference

## A.1 Full EBNF Grammar Specification

```ebnf
(* Top-level *)
program         ::= declaration*
declaration     ::= kernel_decl | shell_decl | view_decl

(* Kernel Layer *)
kernel_decl     ::= 'kernel' IDENT '{' kernel_item* '}'
kernel_item     ::= fn_decl | struct_decl | const_decl | comptime_fn

fn_decl         ::= attributes? 'fn' IDENT '(' params? ')' return_type? contracts? block
comptime_fn     ::= attributes? 'comptime' 'fn' IDENT '(' params? ')' return_type? block
struct_decl     ::= 'struct' IDENT '{' struct_fields '}'
const_decl      ::= 'const' IDENT ':' type '=' expr ';'

params          ::= param (',' param)*
param           ::= IDENT ':' type
return_type     ::= '->' type
struct_fields   ::= struct_field (',' struct_field)* ','?
struct_field    ::= IDENT ':' type

(* Contracts *)
contracts       ::= contract+
contract        ::= requires_clause | ensures_clause
requires_clause ::= '#[requires(' expr ')]'
ensures_clause  ::= '#[ensures(' expr ')]'

(* Attributes *)
attributes      ::= attribute+
attribute       ::= '#[' attr_name ('(' attr_args ')')? ']'
attr_name       ::= 'verified' | 'unsafe_trust' | 'requires' | 'ensures' | 'target' | 'pure' | 'impure'
attr_args       ::= expr (',' expr)*

(* Statements *)
block           ::= '{' statement* '}'
statement       ::= let_stmt | return_stmt | if_stmt | match_stmt | for_stmt
                  | while_stmt | loop_stmt | defer_stmt | expr_stmt

let_stmt        ::= 'let' 'mut'? IDENT (':' type)? '=' expr ';'
return_stmt     ::= 'return' expr? ';'
if_stmt         ::= 'if' expr block ('else' (if_stmt | block))?
match_stmt      ::= 'match' expr '{' match_arm+ '}'
match_arm       ::= pattern '=>' (expr | block) ','?
for_stmt        ::= 'for' IDENT 'in' expr block
while_stmt      ::= 'while' expr block
loop_stmt       ::= 'loop' block
defer_stmt      ::= 'defer' (expr ';' | block)
expr_stmt       ::= expr ';'

(* Patterns *)
pattern         ::= literal_pattern | ident_pattern | struct_pattern
                  | enum_pattern | wildcard_pattern
literal_pattern ::= INTEGER | FLOAT | STRING | 'true' | 'false'
ident_pattern   ::= IDENT
struct_pattern  ::= IDENT '{' field_patterns '}'
enum_pattern    ::= IDENT '::' IDENT ('(' patterns ')')?
wildcard_pattern::= '_'
field_patterns  ::= field_pattern (',' field_pattern)* ','?
field_pattern   ::= IDENT (':' pattern)?
patterns        ::= pattern (',' pattern)*

(* Expressions *)
expr            ::= assignment_expr
assignment_expr ::= ternary_expr ('=' assignment_expr)?
ternary_expr    ::= or_expr ('?' expr ':' ternary_expr)?
or_expr         ::= and_expr ('||' and_expr)*
and_expr        ::= equality_expr ('&&' equality_expr)*
equality_expr   ::= comparison_expr (('==' | '!=') comparison_expr)*
comparison_expr ::= bitwise_expr (('<' | '>' | '<=' | '>=') bitwise_expr)*
bitwise_expr    ::= shift_expr (('&' | '|' | '^') shift_expr)*
shift_expr      ::= additive_expr (('<<' | '>>') additive_expr)*
additive_expr   ::= multiplicative_expr (('+' | '-') multiplicative_expr)*
multiplicative_expr ::= unary_expr (('*' | '/' | '%') unary_expr)*
unary_expr      ::= ('-' | '!' | 'copy' | 'move')? postfix_expr
postfix_expr    ::= primary_expr (call_expr | index_expr | field_expr)*
call_expr       ::= '(' args? ')'
index_expr      ::= '[' expr ']'
field_expr      ::= '.' IDENT

primary_expr    ::= literal | IDENT | '(' expr ')' | block_expr
                  | if_expr | match_expr | array_expr | struct_expr
literal         ::= INTEGER | FLOAT | STRING | 'true' | 'false' | 'None'
block_expr      ::= block
if_expr         ::= 'if' expr block 'else' block
match_expr      ::= 'match' expr '{' match_arm+ '}'
array_expr      ::= '[' (expr (',' expr)* ','?)? ']'
struct_expr     ::= IDENT '{' field_inits '}'
field_inits     ::= field_init (',' field_init)* ','?
field_init      ::= IDENT ':' expr

args            ::= expr (',' expr)*

(* Types *)
type            ::= simple_type | array_type | option_type | fn_type
simple_type     ::= 'i32' | 'i64' | 'f32' | 'f64' | 'bool' | 'str' | IDENT
array_type      ::= '[' type ';' INTEGER ']'
option_type     ::= 'Option' '<' type '>'
fn_type         ::= 'fn' '(' type_list? ')' return_type?
type_list       ::= type (',' type)*

(* Shell Layer *)
shell_decl      ::= 'shell' IDENT '{' shell_item* '}'
shell_item      ::= import_stmt | agent_decl | message_decl

import_stmt     ::= 'import' IDENT ';'
agent_decl      ::= 'agent' IDENT '{' agent_item* '}'
agent_item      ::= agent_state | message_handler

agent_state     ::= IDENT '=' expr ';'
message_handler ::= 'on' 'receive' STRING message_params? block
message_params  ::= 'with' param (',' param)*

(* View Layer *)
view_decl       ::= 'view' IDENT '{' view_item* '}'
view_item       ::= attributes? component_decl

component_decl  ::= IDENT '{' component_props '}'
component_props ::= component_prop*
component_prop  ::= IDENT ':' expr ';'
                  | 'on_' IDENT ':' expr ';'
                  | component_decl

(* Lexical *)
IDENT           ::= [a-zA-Z_][a-zA-Z0-9_]*
INTEGER         ::= [0-9]+ | '0x' [0-9a-fA-F]+ | '0b' [01]+
FLOAT           ::= [0-9]+ '.' [0-9]+ ([eE] [+-]? [0-9]+)?
STRING          ::= '"' [^"]* '"'
COMMENT         ::= '//' [^\n]* | '/*' .* '*/'
WHITESPACE      ::= [ \t\n\r]+
```

## A.2 Keywords

| Category | Keywords |
|----------|----------|
| **Declarations** | `fn`, `struct`, `const`, `type`, `kernel`, `shell`, `view`, `agent`, `comptime` |
| **Control Flow** | `if`, `else`, `match`, `for`, `in`, `while`, `loop`, `return`, `break`, `continue` |
| **Variables** | `let`, `mut` |
| **Ownership** | `copy`, `move`, `defer` |
| **Types** | `i32`, `i64`, `f32`, `f64`, `bool`, `str`, `Option`, `None`, `Some` |
| **Boolean** | `true`, `false` |
| **Visibility** | `pub` |
| **Imports** | `import`, `use` |
| **Agent** | `on`, `receive`, `send`, `to`, `with` |

## A.3 Operators by Precedence (Highest to Lowest)

| Precedence | Operators | Associativity | Description |
|------------|-----------|---------------|-------------|
| 1 | `()` `[]` `.` | Left | Call, index, field access |
| 2 | `-` `!` `copy` `move` | Right | Unary negation, not, ownership |
| 3 | `*` `/` `%` | Left | Multiplication, division, modulo |
| 4 | `+` `-` | Left | Addition, subtraction |
| 5 | `<<` `>>` | Left | Bit shift |
| 6 | `&` | Left | Bitwise AND |
| 7 | `^` | Left | Bitwise XOR |
| 8 | `\|` | Left | Bitwise OR |
| 9 | `<` `>` `<=` `>=` | Left | Comparison |
| 10 | `==` `!=` | Left | Equality |
| 11 | `&&` | Left | Logical AND |
| 12 | `\|\|` | Left | Logical OR |
| 13 | `?` `:` | Right | Ternary conditional |
| 14 | `=` | Right | Assignment |

## A.4 Built-in Functions

| Function | Signature | Description |
|----------|-----------|-------------|
| `len` | `fn len<T>(arr: [T; N]) -> i64` | Array/string length |
| `print` | `fn print(s: str) -> ()` | Print to stdout |
| `println` | `fn println(s: str) -> ()` | Print with newline |
| `assert` | `fn assert(cond: bool) -> ()` | Runtime assertion |
| `panic` | `fn panic(msg: str) -> !` | Abort with message |
| `char_code_at` | `fn char_code_at(s: str, index: i64) -> i64` | Byte code at string index, or `0` when out of range |

## A.5 Standard Attributes

| Attribute | Target | Description |
|-----------|--------|-------------|
| `#[verified]` | Function | Mark for formal verification |
| `#[requires(expr)]` | Function | Precondition contract |
| `#[ensures(expr)]` | Function | Postcondition contract |
| `#[unsafe_trust]` | Function | Skip verification |
| `#[target(graphics)]` | View | Target graphics backend |
| `#[target(embedded)]` | View | Target embedded backend |
| `#[pure]` | Function/Module | No side effects |
| `#[impure]` | Function/Module | Has side effects |

---

# Appendix B: Compiler Reference

## B.1 CLI Commands

```bash
bunker check <file.bkr>              # Type-check without compilation
bunker run <file.bkr>                # JIT compile and execute
bunker build <file.bkr> -o <output>  # AOT compile to object file
bunker parse <file.bkr>              # Show parse tree (debugging)
bunker fmt <file.bkr>                # Format source code
bunker fmt --check <file.bkr>        # Check formatting
```

## B.2 Compiler Flags

| Flag | Description |
|------|-------------|
| `-o <file>` | Output file path |
| `--emit=ast` | Emit AST representation |
| `--emit=ir` | Emit Cranelift IR |
| `--profile=reactive` | Enable reactive/UI profile |
| `--profile=metal` | Enable embedded/no-std profile |
| `--verify` | Enable contract verification |
| `--json-errors` | Output errors as JSON |
| `-v`, `--verbose` | Verbose output |

## B.3 Error Code Reference

| Code | Category | Description |
|------|----------|-------------|
| E0001 | Parse | Syntax error |
| E0002 | Parse | Unexpected token |
| E0003 | Parse | Missing delimiter |
| E0100 | Type | Type mismatch |
| E0101 | Type | Unknown type |
| E0102 | Type | Unknown identifier |
| E0103 | Type | Wrong number of arguments |
| E0104 | Type | Missing return statement |
| E0200 | Ownership | Use after move |
| E0201 | Ownership | Double move |
| E0202 | Ownership | Missing copy |
| E0300 | Contract | Precondition violation |
| E0301 | Contract | Postcondition violation |
| E0302 | Contract | Verification timeout |
| E0400 | Shell | Unknown message type |
| E0401 | Shell | Message argument mismatch |
| E0402 | Shell | Unknown agent |
| E0500 | View | Unknown binding |
| E0501 | View | Invalid component |

---

# Appendix C: Type System Details

## C.1 Primitive Types

| Type | Size | Range | Description |
|------|------|-------|-------------|
| `i32` | 4 bytes | -2³¹ to 2³¹-1 | 32-bit signed integer |
| `i64` | 8 bytes | -2⁶³ to 2⁶³-1 | 64-bit signed integer |
| `f32` | 4 bytes | IEEE 754 | 32-bit float |
| `f64` | 8 bytes | IEEE 754 | 64-bit float |
| `bool` | 1 byte | true/false | Boolean |
| `str` | varies | UTF-8 | String slice |

## C.2 Type Inference Rules

```
Γ ⊢ e ⇒ T        (Synthesis: infer type T from expression e)
Γ ⊢ e ⇐ T        (Checking: check expression e against type T)

[Var]       Γ, x:T ⊢ x ⇒ T
[Int]       Γ ⊢ n ⇒ i32                    (integer literal)
[Float]     Γ ⊢ f ⇒ f64                    (float literal)
[String]    Γ ⊢ s ⇒ str                    (string literal)
[App]       Γ ⊢ f ⇒ (T₁,...,Tₙ) -> T_ret
            Γ ⊢ eᵢ ⇐ Tᵢ
            ─────────────────────────────
            Γ ⊢ f(e₁,...,eₙ) ⇒ T_ret
[Check]     Γ ⊢ e ⇒ T
            T = T'
            ─────────────
            Γ ⊢ e ⇐ T'
```

## C.3 Subtyping Relations

```
i32 <: i64                    (integer promotion)
f32 <: f64                    (float promotion)
T <: Option<T>                (Some injection)
None <: Option<T>             (None injection)
[T; N] <: [T]                 (array to slice)
```

---

# Appendix D: Memory Model Semantics

## D.1 Ownership Rules

1. **Single Owner**: Every value has exactly one owner at a time
2. **Move by Default**: Assignment transfers ownership (`let b = a` moves `a`)
3. **Explicit Copy**: Use `copy` keyword for duplication (`let b = copy a`)
4. **Drop at Scope End**: Values are dropped when owner goes out of scope
5. **Defer Execution**: `defer` statements run in reverse declaration order

## D.2 Move Semantics State Machine

```
┌─────────────┐
│   Valid     │
│   (owned)   │
└─────┬───────┘
      │ move/assign
      ▼
┌─────────────┐
│   Moved     │
│  (invalid)  │
└─────────────┘

Use after move → Compile Error E0200
```

## D.3 Copy Semantics

```bunker
// Primitive types: implicitly copyable
let a: i32 = 42;
let b = a;      // a still valid (implicit copy)

// Compound types: explicit copy required
let s: String = "hello";
let t = copy s; // s still valid (explicit copy)
let u = s;      // s now MOVED, invalid

// Deep copy for nested structures
let arr = [[1, 2], [3, 4]];
let arr2 = copy arr;  // Deep copy of all elements
```

---

# Appendix E: Verification Condition Generation

## E.1 Weakest Precondition Rules

```
WP(skip, Q) = Q
WP(x := e, Q) = Q[e/x]
WP(S1; S2, Q) = WP(S1, WP(S2, Q))
WP(if b then S1 else S2, Q) = (b ⟹ WP(S1, Q)) ∧ (¬b ⟹ WP(S2, Q))
WP(while b inv I do S, Q) = I ∧ ∀x. (I ∧ b ⟹ WP(S, I)) ∧ (I ∧ ¬b ⟹ Q)
```

## E.2 Contract Verification Flow

```
Function: fn f(x: T) -> U requires P ensures Q { body }

Generate VCs:
1. P ⟹ WP(body, Q)                    // Function correctness
2. ∀ call sites: Args satisfy P        // Caller obligations
3. Q holds at all return points        // Postcondition
```

## E.3 SMT-LIB Output Format

```smt2
; Generated VC for function divide
(declare-const x Int)
(declare-const y Int)
(declare-const result Int)

; Precondition
(assert (not (= y 0)))

; Function body semantics
(assert (= result (div x y)))

; Check postcondition (negated for UNSAT proof)
(assert (not (= (* result y) x)))

(check-sat)
; UNSAT = postcondition holds
; SAT = counterexample found
```

---

# Implementation Status Tracking

This section tracks the implementation status of each specification part against the current Bunker compiler.

## Part Implementation Checklist

### Part 1: Grammar and Syntax Design ✅ Mostly Complete
- [x] PEG grammar with Pest parser
- [x] LL(1)-compatible structure
- [x] Explicit block delimiters (`{ }`)
- [x] Kernel/Shell/View layer parsing
- [x] AI-friendly keyword design
- [x] No significant whitespace
- [ ] Formal grammar-constrained decoding validation
- [ ] XGrammar/SynCode integration testing

### Part 2: Type System Design 🔶 Partial
- [x] Static typing for Kernel layer
- [x] Bidirectional type inference
- [x] Sum types (`Option<T>`)
- [x] Exhaustive pattern matching
- [x] Struct and array types
- [x] Type error messages with locations
- [ ] Refinement types with SMT predicates
- [ ] Higher-kinded type avoidance (by design)
- [ ] JSON-formatted type errors for AI

### Part 3: Memory Model and Ownership 🔶 Partial
- [x] Move-by-default semantics
- [x] Explicit `copy` keyword
- [x] `defer` for deterministic cleanup
- [x] Use-after-move detection
- [ ] Linear types with `!` suffix notation
- [ ] Second-class references (no lifetimes)
- [ ] Arena-based memory allocation
- [ ] Vale-style region borrow checking

### Part 4: Design-by-Contract and Verification 🔶 Partial
- [x] `#[requires]` precondition parsing
- [x] `#[ensures]` postcondition parsing
- [x] `#[verified]` attribute parsing
- [x] Lightweight linear verification (`verify.rs`)
- [ ] Z3/CVC5 SMT solver integration
- [ ] Verification condition generation
- [ ] Counterexample formatting for AI
- [ ] Incremental verification (<100ms)
- [ ] Clover-style consistency checks

### Part 5: Agent Execution Semantics 🔶 Partial
- [x] Shell layer parsing
- [x] Agent definition and state
- [x] Message handlers (`on receive`)
- [x] Message sending (`send`)
- [x] Kernel↔Shell bridge (`use` syntax)
- [x] Message queue VM runtime
- [ ] Virtual actor pattern (Orleans-style)
- [ ] Agent memory hierarchies
- [ ] Type-safe tool definitions
- [ ] Session types for protocols
- [ ] Durable execution primitives

### Part 6: Error Handling and Diagnostics 🔶 Partial
- [x] Result-based error handling
- [x] Compiler error messages
- [x] Source location tracking
- [x] Structured JSON error output
- [x] Prompt-ready AI repair context
- [x] Structured suggestions with applicability and confidence metadata
- [ ] Typed holes with hole fits
- [ ] SARIF output format
- [ ] Span-backed machine-applicable replacements
- [ ] Error recovery during parsing

### Part 7: Concurrency and Parallelism ❌ Not Started
- [ ] Structured concurrency with nurseries
- [ ] CSP-style channels
- [ ] Ownership-transferring message passing
- [ ] Data race prevention by design
- [ ] Type-level lock ordering
- [ ] Deterministic parallelism for pure functions

### Part 8: Module System and Package Management ❌ Not Started
- [ ] Flat module structure
- [ ] Explicit imports (no wildcards)
- [ ] Content-addressed dependencies
- [ ] Lockfile generation
- [ ] `bunker.toml` configuration

### Part 9: Standard Library 🔶 Partial
- [ ] Core numeric types with overflow options
- [x] UTF-8 String type
- [x] Collections (Vec, Array, Map, Set)
- [ ] Iterator pattern
- [x] Option/Result combinators
- [ ] Consistent naming conventions

### Part 10: Tooling and Ecosystem ❌ Not Started
- [ ] LSP server with typed holes
- [ ] Zero-config formatter (`bunker fmt`)
- [ ] AI-specific LSP extensions
- [ ] Training data curation pipeline

### Part 11: Embedded and Systems Features 🔶 Partial
- [x] `comptime` function parsing
- [x] Compile-time evaluation
- [x] Constant expressions
- [ ] Type reflection (`@typeInfo`)
- [ ] Inline assembly
- [ ] Memory-mapped I/O
- [ ] Target profiles (embedded/server/wasm)

### Part 12: Cross-Layer Integration 🔶 Partial
- [x] Kernel layer compilation (Cranelift JIT)
- [x] Shell layer compilation (VM bytecode)
- [x] View layer parsing
- [x] View text backend
- [x] View Windows graphics backend
- [ ] `@pure`/`@impure` annotations
- [ ] Reactive view bindings
- [x] View layout containers (Row/Column/Grid)
- [ ] Unidirectional data flow enforcement

## Current Implementation Summary

| Part | Status | Coverage | Priority |
|------|--------|----------|----------|
| 1. Grammar | ✅ | 85% | - |
| 2. Type System | 🔶 | 65% | High |
| 3. Memory Model | 🔶 | 45% | Medium |
| 4. Verification | 🔶 | 30% | High |
| 5. Agent Runtime | 🔶 | 55% | Medium |
| 6. Error Handling | 🔶 | 30% | High |
| 7. Concurrency | ❌ | 0% | Low |
| 8. Modules | ❌ | 0% | Low |
| 9. Stdlib | ❌ | 0% | Low |
| 10. Tooling | ❌ | 0% | Low |
| 11. Systems | 🔶 | 35% | Medium |
| 12. Integration | 🔶 | 50% | Medium |

**Legend:** ✅ Complete (>80%), 🔶 Partial (20-80%), ❌ Not Started (<20%)

## AI-Critical Feature Status

These features are specifically critical for AI code generation accuracy:

| Feature | Status | Impact on AI |
|---------|--------|--------------|
| Grammar-constrained decoding compatible | ✅ | 96% syntax error reduction |
| Type-constrained generation | 🔶 | >50% fewer compilation errors |
| Structured JSON errors | ✅ | `--format=json` emits schema version, source excerpts, hints, suggestions, and prompt context |
| Typed holes | ❌ | Precise context for generation |
| Contract verification | 🔶 | Eliminates hallucinations |
| Explicit ownership | ✅ | Avoids borrow checker failures |
| Self-host readiness reporting | ✅ | `self-host-check` reports 8/8 current Bunker-written compiler sources passing |
| Self-host compile wrapper | 🔶 | `self-host-compile` runs `self-host/bkrc.bkr` on real input and emits C for the bootstrap subset |

## Critical Path to AI-Native MVP

1. **Embedded/Metal Profile** - Complete the multi-profile target story
2. **Self-Host Execution Parity** - Expand the Bunker-written compiler subset and compare generated output against the Rust compiler
3. **Typed Holes with Fits** - Provide precise generation context
4. **Canonical Formatter** - Make training and reviews consistent
5. **LSP with AI Extensions** - Expose compiler context to tools
6. **Coherent Standard Library** - Replace bootstrap builtins with a stable surface

## Test Coverage

- **Total Tests:** 92 passing
- **JIT-Enabled:** 57 tests (validated by `run_tests.ps1`)
- **Negative Tests:** 16 tests (type errors, move errors)
- **Shell-Bearing Files:** 14 tests
- **View-Bearing Files:** 7 tests

## Research Validation Needed

- [ ] Benchmark against XGrammar for constrained decoding
- [ ] Measure type-constrained generation error reduction
- [ ] Compare AI repair accuracy with/without JSON errors
- [ ] Test Clover consistency checking integration
- [ ] Validate training data curation pipeline

*Last updated: Run `/check-update-status` to refresh*
