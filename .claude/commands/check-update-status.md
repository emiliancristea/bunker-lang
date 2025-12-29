# Bunker Language: Status Check & Roadmap Update

You are analyzing the Bunker Language project to assess current implementation status and determine next steps.

## Instructions

Execute the following workflow systematically:

### Step 1: Gather Project Context

Read these files to understand the project:
- `README.md` - Project overview, goals, and current status section
- `ROADMAP.md` - Implementation phases and milestones
- `docs/VISION.md` - Language design goals
- `docs/ARCHITECTURE.md` - Technical architecture
- `docs/SPECIFICATION.md` - AI-Native Language Specification
- `docs/TECHNICAL_SPEC.md` - Complete Technical Specification

### Step 2: Assess Current Implementation State

#### 2.1 Run Test Suite
```bash
powershell -ExecutionPolicy Bypass -File run_tests.ps1
```

#### 2.2 Analyze Test Coverage
- Count of test files: `ls tests/*.bkr | wc -l`
- JIT-enabled tests (with `fn main`): `grep -l "fn main" tests/*.bkr | wc -l`
- Negative tests (`*_BAD` suffix): `ls tests/*_BAD.bkr | wc -l`
- Shell execution tests: `grep -l "shell " tests/*.bkr | wc -l`

#### 2.3 Check Compiler Components
Verify each compiler module exists and assess completeness:
```bash
ls bunker-cli/src/*.rs
```

Key modules to check:
- `grammar/bunker.pest` - PEG grammar completeness
- `ast.rs` - AST node coverage
- `ast_builder.rs` - Parse tree to AST transformation
- `typeck.rs` - Type checker implementation
- `jit.rs` - Cranelift JIT compilation
- `codegen.rs` - AOT code generation
- `shell_codegen.rs` - Shell layer compilation
- `shell_runtime.rs` - Agent VM runtime
- `view_runtime.rs` - View layer execution
- `comptime.rs` - Compile-time evaluation
- `verify.rs` - Contract verification

#### 2.4 Grammar Feature Coverage
Check grammar for implemented constructs:
```bash
grep -E "^[a-z_]+ =" bunker-cli/src/grammar/bunker.pest | head -50
```

#### 2.5 Specification Compliance Check

Compare implementation against specification requirements:

**From SPECIFICATION.md - Area Checklist:**
- [ ] Area 1: Grammar (LL(1), explicit delimiters, AI-friendly tokens)
- [ ] Area 2: Type System (bidirectional inference, refinement types, effects)
- [ ] Area 3: Memory Model (linear types, second-class refs, arenas)
- [ ] Area 4: Verification (contracts, SMT integration, incremental)
- [ ] Area 5: Agent Runtime (actors, memory hierarchies, tools, sessions)
- [ ] Area 6: Error Handling (structured JSON, typed holes, recovery)
- [ ] Area 7: Concurrency (structured, channels, deterministic parallelism)
- [ ] Area 8: Tooling (formatter, LSP, package manager)
- [ ] Area 9: Standard Library (consistent naming, uniform errors)
- [ ] Area 10: Metaprogramming (comptime, derives, no macros)

**From TECHNICAL_SPEC.md - Part Checklist:**
- [ ] Part 1: Grammar-Constrained Decoding Optimization
- [ ] Part 2: Type-Constrained Generation
- [ ] Part 3: Ownership Without Borrow Checker
- [ ] Part 4: Design-by-Contract & Verification
- [ ] Part 5: Agent Execution Semantics
- [ ] Part 6: AI Feedback Loop Diagnostics
- [ ] Part 7: Structured Concurrency
- [ ] Part 8: Flat Module System
- [ ] Part 9: Standard Library Primitives
- [ ] Part 10: LSP & Tooling
- [ ] Part 11: Embedded & Systems Features
- [ ] Part 12: Cross-Layer Integration (Kernel/Shell/View)

### Step 3: Report to User

Provide a structured report with these sections:

#### Bunker Language Goals
Summarize from README.md:
- The three-layer architecture (Kernel/Shell/View)
- The 6 killer features
- Target use cases and audiences
- What success looks like

#### Current Implementation State
Based on test results and code analysis:
- Total tests passing/failing
- ROADMAP phases completed (0-9)
- Key features implemented
- Key features missing

#### Specification Compliance Matrix

| Spec Area | Implementation Status | Coverage % | Priority |
|-----------|----------------------|------------|----------|
| Grammar (LL(1)) | ✅/🔶/❌ | X% | High/Med/Low |
| Type System | ✅/🔶/❌ | X% | High/Med/Low |
| Memory Model | ✅/🔶/❌ | X% | High/Med/Low |
| Verification | ✅/🔶/❌ | X% | High/Med/Low |
| Agent Runtime | ✅/🔶/❌ | X% | High/Med/Low |
| Error Handling | ✅/🔶/❌ | X% | High/Med/Low |
| Concurrency | ✅/🔶/❌ | X% | High/Med/Low |
| Tooling | ✅/🔶/❌ | X% | High/Med/Low |
| Stdlib | ✅/🔶/❌ | X% | High/Med/Low |
| Metaprogramming | ✅/🔶/❌ | X% | High/Med/Low |

Legend: ✅ Complete, 🔶 Partial, ❌ Not Started

#### Gap Analysis
Compare current state vs README/Specification goals:
- What the specs promise that works today
- What the specs promise that doesn't work yet
- Critical path items to close the gap
- Technical debt that needs addressing

#### Recommended Next Steps
Propose 3-5 concrete, actionable tasks in priority order:
1. High-impact items that unlock other features
2. Items that match ROADMAP phase progression
3. Items that improve developer experience
4. Items that close specification gaps

### Step 4: Update ROADMAP.md (If Needed)

If the ROADMAP is out of date:
- Update phase checkboxes to reflect completed items
- Add any new phases or tasks discovered
- Keep timeline estimates realistic
- Preserve the document structure
- Update the Current Progress Summary table

Only modify ROADMAP.md if there are actual changes needed. Do not make cosmetic changes.

### Step 5: Update README.md Status Section (If Needed)

If the README status section is out of date:
- Update the test count
- Update implemented features list
- Update in-progress items
- Ensure accuracy with current codebase

### Step 6: Update Specification Implementation Status (If Needed)

If significant implementation progress has been made:
- Update implementation status sections in SPECIFICATION.md
- Update implementation status sections in TECHNICAL_SPEC.md
- Ensure checklists reflect current state

## Output Format

Structure your response as:

```
## Bunker Language Status Report

### Project Goals
[Summary of what Bunker aims to be]

### Current State
- Tests: X passing / Y total
- ROADMAP Progress: Phase N of 9
- Key Capabilities: [list]

### Specification Compliance
| Area | Status | Notes |
|------|--------|-------|
| ... | ... | ... |

### Gap Analysis
| Goal | Status | Priority |
|------|--------|----------|
| ... | ... | ... |

### Recommended Next Steps
1. [Task 1 - why it matters]
2. [Task 2 - why it matters]
3. [Task 3 - why it matters]

### Files Updated
- [List any files modified, or "None"]
```

## Implementation Priority Guidelines

When recommending next steps, consider this priority order:

### Tier 1: Core Language (Blocking Everything Else)
- Grammar completeness for all three layers
- Type checker for Kernel layer
- Basic code generation (JIT working)

### Tier 2: AI-Critical Features
- Structured error messages (JSON output)
- Type-constrained generation support
- Contract parsing and lightweight verification

### Tier 3: Production Readiness
- Full Z3 SMT integration
- Arena memory allocator
- View layout containers
- Shell agent runtime

### Tier 4: Ecosystem
- LSP server
- Formatter
- Package manager
- Standard library

### Tier 5: Advanced Features
- Embedded profile
- Self-hosting
- AI training datasets

## Important Notes

- Focus on production-ready implementation progress
- Prioritize items that move toward a working end-to-end demo
- Consider dependencies between features
- Be honest about what works vs what's stubbed/partial
- The goal is a compiler that can build real applications
- Track specification compliance as a key metric
- Ensure documentation stays synchronized with implementation

## Context

This command is used to maintain alignment between documentation and implementation as the Bunker Language evolves. Run it periodically to ensure the project stays on track toward its stated goals and specification requirements.

The Bunker Language aims to be the first AI-native systems programming language. Every implementation decision should be evaluated against this core thesis: **does this make AI code generation more reliable while remaining ergonomic for humans?**
