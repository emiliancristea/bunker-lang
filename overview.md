BUNKER LANG: The Ultimate Overview

"One Syntax. Two Worlds. Infinite Power."

Bunker is the first unified programming ecosystem designed for the post-human era. It abolishes the separation between systems programming, scripting, and UI design, collapsing them into a single `.bkr` file. It is an AI-Authoring Native language where strict architectural constraints allow an AI to generate vertically integrated features—from hardware drivers to UI pixels—without hallucinating bugs.

1. The Architecture: The Trinity of Code

Every Bunker file consists of three distinct layers. They share a syntax but differ radically in compilation and execution.

LAYER 0: KERNEL (The Iron)

Analogy: The muscle and bone.

Language Nature: Native Systems Language (The Rust-Killer).

Compilation: Machine Code (LLVM/ASM).

Role: High-performance math, physics, drivers, and memory management.

Key Feature: Region-Based Memory (Arenas) by Default.
- Unlike Rust: No manual lifetime annotations ('a). The compiler manages memory in scoped "Arenas" (frames), which are freed automatically when the frame ends.
- Unlike C++: No manual `new` or `delete`. Memory leaks are architecturally impossible because data cannot outlive its Arena.
- Why it Wins: It offers C++ speed with complete memory safety, without the mental overhead of Rust's borrow checker.

Key Feature: Formal Verification. The compiler uses a Z3 Solver to prove math is sound. If the math is wrong, it does not compile.

Safety: Explicit #[verified] logic or #[unsafe_trust] for hardware registers.

LAYER 1: SHELL (The Mind)

Analogy: The nervous system.

Language Nature: Agent-based, Scripting.

Compilation: Bytecode / Deterministic Finite Automaton (DFA).

Role: Game logic, quest flows, business state, and orchestration.

Key Feature: No Pointers. Logic is handled by "Agents" that communicate via messages (send, receive, ask).

Safety: Impossible to deadlock (loops detected), no garbage collection pauses in critical profiles.

LAYER 2: VIEW (The HMI - Human Machine Interface)

Analogy: The skin (or the status LEDs).

Language Nature: Declarative, Polymorphic.

Compilation: Target-Dependent Output.
- On Desktop: Compiles to Render Graph / UI Draw Calls (Pixels).
- On Embedded: Compiles to GPIO/Serial Instructions (Pins/Signals).

Role: User feedback, HUDs, menus, or physical status indicators.

Key Feature: Single Source of Truth. View elements bind directly to Agent state in the Shell.
- Reactive Profile: "Agent.health < 10" -> Red Screen Tint.
- Metal Profile: "Agent.health < 10" -> PIN_13 HIGH (Red LED).

2. The Four Profiles (Contexts)

Bunker adapts its compiler backend based on the target industry. One language serves four distinct masters.

I. The "Metal" Profile (Embedded Systems)

Target: Medical devices, Satellites, Microcontrollers.

Constraints: 64KB RAM, No Heap, Zero Crashes.

Behavior: Garbage Collection is disabled. The Shell compiles to a static DFA.

Example: An Infusion Pump.

Kernel: Manages voltage to the motor (unsafe trust).

Shell: Supervisor agent ensures flow rate never exceeds limits.

View: LCD Text or Status LEDs indicating "FLOW OK".

Result: Deterministic execution with zero memory leaks.

II. The "Performance" Profile (AAA Games)

Target: Game Engines, Physics Simulations.

Constraints: 16ms Frame Budget, 1000+ Entities.

Behavior: Kernel manages raw memory arenas (SIMD optimized). Shell handles high-level AI without touching pointers.

Example: A Zombie Horde.

Kernel: Calculates position updates for 500 entities in a hot loop.

Shell: "Director" agent decides when to spawn waves based on player state.

Result: C++ speed with Python-like scripting ease.

III. The "Reactive" Profile (UI & Tools)

Target: Desktop Apps, Editors (Blender/Unreal), Dashboards.

Constraints: Complex State Management, Undo/Redo.

Behavior: Agent state acts as a "Store" (like Redux).

Example: A Level Editor.

Kernel: Handles file I/O and binary saving.

Shell: Manages selection state (selected_count).

View: Toolbar buttons bind directly to Shell.selected_count.

Result: A "Qt-Killer" workflow where logic and UI are inseparable.

IV. The "Fortress" Profile (Fintech & Cloud)

Target: Banking Ledgers, Smart Contracts, MMO Economies.

Constraints: Absolute Correctness. Logic bugs = Money lost.

Behavior: Aggressive Z3 Formal Verification.

Example: A Transaction Ledger.

Kernel: The transfer function must prove that total_money_in == total_money_out.

Shell: Orchestrates the database commits.

Result: Logic that physically cannot compile if a money-leak bug exists.

3. The Syntax: One File, Complete Feature

A Vertical Slice of a Homing Missile in Bunker.

code

Bunker

// 1. THE PHYSICS (Verified Math)

kernel Dynamics {

    #[verified]

    fn seek(pos: vec3, target: vec3, speed: f32) -> vec3 {

        let dir = normalize(target - pos);

        return pos + dir * speed;

    }

}



// 2. THE LOGIC (Agent Orchestration)

shell WarRoom {

    import Dynamics;



    agent Missile {

        position = [0, 0, 0];

        

        on receive "launch" with target: vec3 {

            // Calls the Kernel to do the math

            position = use Dynamics.seek with pos=position, target=target, speed=50.0;

            send "impact" to target_entity;

        }

    }

}



// 3. THE VIEW (Polymorphic Output)

view MissileStatus {

    // If running on Desktop/Game:

    #[target(graphics)]

    Label {

        text: "Missile Pos: " + WarRoom.Missile.position;

        color: #FF0000;

    }



    // If running on Embedded Hardware:

    #[target(embedded)]

    Pin {

        id: 13;

        mode: output;

        value: WarRoom.Missile.position.y > 100 ? HIGH : LOW;

    }

}

4. The Seven Eternal Laws

The compiler enforces these laws to prevent humans (and AI) from writing bad code.

No wait inside Agents: Prevents deadlocks. Time is handled by state machines.

No Discarded Returns: Every function output must be handled. No logic leaks.

Map Safety: Accessing a map without .has(key) is a compile-time error.

No Global Mutable State: Pure data flow only. Agents own their own data.

Verification Mandatory: Kernel math is checked by solvers, not just syntax highlighters.

One Feature = One File: Enforced architectural purity.

No Hidden Inputs: Dependency injection is explicit.

5. Why Bunker?

The Post-Human Promise.

In the modern era, AI writes code, but humans struggle to debug it across 50 files (C++ for physics, Lua for logic, XML for UI).

Bunker is the solution. It provides a Unified Context. An AI can generate a `.bkr` file, and because the Physics, Logic, and UI are tightly coupled and verified by the compiler:

The Physics won't break.

The Logic won't deadlock.

The UI won't desync.

Humans direct. AI implements. The Compiler guarantees.

6. The Genesis: Ambitious Goals & Realized Design

The following pillars define the specific, ambitious goals set for BunkerLang and how the final design accomplishes them.

I. The "Poly-Genre" MMO Goal (The Multiverse)

The Goal: Create a unified MMO where players can seamlessly transition between genres (WoW-style RPG to Tarkov-style FPS to Isometric RTS) within a single world.

The Achievement: The Universal Entity Model & Session Handoff.
*   BunkerScript (Shell) handles the persistent inventory and logic (the "Soul").
*   BunkerLang (Kernel) handles the hot-swapping of physics engines (e.g., switching from Capsule Collider to Hitbox System) without crashing the server.

II. The "Universal Language" Goal

The Goal: A single language perfect for everything: Embedded, UI (Qt-killer), and Game Engines (Unreal-killer).

The Achievement: The Bicameral Architecture & Polymorphic View.
*   Embedded/Engine: Handled by the Kernel (Layer 0), which compiles to raw machine code, disables GC, and allows direct hardware access (unsafe trust).
*   UI/Logic: Handled by the Shell (Layer 1), which allows high-level orchestration and reactive UI binding.
*   Universal View: The View layer is redefined as HMI (Human Machine Interface). It compiles to Draw Calls (Pixels) on desktops or GPIO Signals (Pins) on microcontrollers, maintaining the "One Syntax" promise across all hardware.

III. The "Post-Human" Goal (AI-Native)

The Goal: A future where humans prompt and AI writes code.

The Achievement: Constraint-Based Syntax (The Straitjacket).
*   Most languages (C++, Python) are too loose. Bunker is a "Straitjacket" for AI.
*   The compiler forces explicit inputs (using) and mathematical proofs (#[verified]).
*   If the AI hallucinates a bug, the compiler rejects it before a human ever sees it.

IV. The "Masterpiece" Goal (Forced Quality)

The Goal: A language where even the worst code is an architectural masterpiece by default (PhD-level quality).

The Achievement: Architectural Enforcement as Syntax.
*   No "Spaghetti Code": Global state is forbidden.
*   No "Deadlocks": wait is banned in Agents.
*   No "Logic Leaks": Z3 Theorem Prover mathematically proves correctness (e.g., health > 0) at compile time.

7. The Comprehensive Syntax Specification

To eliminate ambiguity for compiler implementation, the following EBNF-inspired syntax defines the structure of a `.bkr` file.

I. The File Structure

file ::= kernel_block? shell_block? view_block?

kernel_block ::= "kernel" Identifier "{" (function | struct | constant)* "}"
shell_block  ::= "shell" Identifier "{" (import | agent)* "}"
view_block   ::= "view" Identifier "{" component* "}"

II. The Kernel (Systems Layer)

function ::= attribute* "fn" Identifier "(" params ")" "->" type "{" statement* "}"
attribute ::= "#[" ("verified" | "unsafe_trust" | "requires(" expr ")" | "ensures(" expr ")") "]"
params   ::= (Identifier ":" type ("," Identifier ":" type)*)?
statement::= let_binding | return_stmt | if_stmt | loop_stmt | defer_stmt | expr
type     ::= "i32" | "i64" | "f32" | "f64" | "vec3" | "bool" | "str" | "Option<" type ">" | "[" type "; " int "]" | Identifier

III. The Shell (Agent Layer)

agent    ::= "agent" Identifier "{" state_decl* message_handler* "}"
state_decl ::= Identifier "=" literal ";"
message_handler ::= "on" "receive" String_Literal ("with" params)? "{" statement* "}"
send_stmt ::= "send" String_Literal "to" Identifier ";"
match_stmt ::= "match" expr "{" match_arm* "}"
match_arm ::= pattern "=>" (expr | "{" statement* "}") ";"

IV. The View (Polymorphic HMI)

component ::= attribute_target? Identifier "{" (property | component)* "}"
attribute_target ::= "#[target(" ("graphics" | "embedded") ")]"
property  ::= Identifier ":" expr ";"
expr      ::= literal | Identifier | binary_op

8. The Five Killer Features (The Competitive Edge)

These features are what make Bunker superior to Rust, C++, and scripting languages like Python/Lua.

I. Compile-Time Execution (`comptime`)

Problem with Rust: `const fn` is extremely limited. You cannot loop, allocate, or do anything complex.

Bunker's Solution: `comptime fn` runs arbitrary code at compile time and bakes the result into the binary.

Why It Wins: Generate lookup tables, unroll loops, and pre-compute constants without runtime cost.

Example:
```bkr
kernel Math {
    comptime fn generate_sin_table(size: i32) -> [f32; size] {
        let table = [];
        for i in 0..size {
            push sin(i as f32 * 0.01) to table;
        }
        return table;
    }

    const SIN_TABLE: [f32; 1000] = generate_sin_table(1000);
}
```

II. Explicit Cleanup (`defer`)

Problem with C++: Destructors are implicit magic. You cannot see when cleanup happens.

Bunker's Solution: `defer` schedules a statement to run when the current scope exits.

Why It Wins: Cleanup is visible, predictable, and cannot be forgotten.

Example:
```bkr
kernel FileSystem {
    fn read_config(path: str) -> Config {
        let file = open(path);
        defer close(file);

        let data = file.read_all();
        return parse(data);
    }
}
```

III. Design-by-Contract (`requires`, `ensures`)

Problem with Rust/C++: Unit tests are not proofs. Assertions crash at runtime.

Bunker's Solution: `#[requires]` and `#[ensures]` are checked by the Z3 solver at compile time.

Why It Wins: If the code compiles, the contract is mathematically guaranteed. No runtime overhead.

Example:
```bkr
kernel Banking {
    #[requires(amount > 0)]
    #[requires(from.balance >= amount)]
    #[ensures(from.balance + to.balance == old(from.balance) + old(to.balance))]
    fn transfer(from: &mut Account, to: &mut Account, amount: i64) {
        from.balance = from.balance - amount;
        to.balance = to.balance + amount;
    }
}
```

IV. No Null (`Option<T>` + `match`)

Problem with Python/Lua/C++: `null` / `nil` / `nullptr` crashes at runtime.

Bunker's Solution: There is no `null`. Use `Option<T>` which is either `Some(value)` or `None`. The compiler forces you to handle both cases.

Why It Wins: Null pointer exceptions are impossible. The code does not compile if you forget to handle `None`.

Example:
```bkr
shell GameLogic {
    agent Inventory {
        items = [];

        on receive "find_item" with name: str {
            let result: Option<Item> = items.find(|i| i.name == name);

            match result {
                Some(item) => send item to Requester;
                None => send "Item not found" to Requester;
            }
        }
    }
}
```

V. Explicit Copy Semantics (`copy`, `move`)

Problem with C++: Hidden copies destroy performance. You never know when a copy happens.

Bunker's Solution: Assignment is a `move` by default. If you want a copy, you must write `copy` explicitly.

Why It Wins: Performance is predictable. No hidden allocations.

Example:
```bkr
kernel Data {
    fn process() {
        let a = create_large_buffer();
        let b = a;          // 'a' is MOVED to 'b'. 'a' is now invalid.
        let c = copy b;     // 'c' is a COPY of 'b'. Both are valid.
    }
}
```

9. The Complete Feature Matrix (Bunker vs. The World)

| Feature                     | C++           | Rust          | Go            | Python        | Bunker        |
|-----------------------------|---------------|---------------|---------------|---------------|---------------|
| Memory Safety               | Manual        | Borrow Check  | GC            | GC            | Arenas        |
| No Null Crashes             | No            | Yes (Option)  | No            | No            | Yes (Option)  |
| Compile-Time Execution      | constexpr     | const fn      | No            | No            | comptime fn   |
| Formal Verification (Z3)    | No            | No            | No            | No            | Yes           |
| Design-by-Contract          | No            | No            | No            | No            | Yes           |
| Explicit Cleanup            | RAII (hidden) | Drop (hidden) | defer         | No            | defer         |
| Embedded (No GC, No Heap)   | Yes           | Yes           | No            | No            | Yes           |
| Reactive UI Binding         | No            | No            | No            | No            | Yes           |
| AI-Native Constraints       | No            | No            | No            | No            | Yes           |

Bunker is the only language that combines Systems Programming (Rust/C++), Scripting (Python), and Reactive UI (React/Qt) into a single, formally verified ecosystem.
