# Bunker Language Examples

This document provides annotated code examples covering all major Bunker language features. These examples serve as training data for AI models and reference documentation for developers.

## Table of Contents

1. [Kernel Layer](#kernel-layer)
2. [Shell Layer](#shell-layer)
3. [View Layer](#view-layer)
4. [Cross-Layer Integration](#cross-layer-integration)

---

## Kernel Layer

The Kernel layer contains pure, deterministic functions compiled to native machine code via Cranelift JIT.

### Basic Functions

```bunker
kernel Math {
    // Simple function with parameters and return type
    fn add(a: i32, b: i32) -> i32 {
        return a + b;
    }

    // Function with local variables
    fn multiply_and_add(x: i32, y: i32, z: i32) -> i32 {
        let product = x * y;
        let result = product + z;
        return result;
    }

    // Entry point for standalone execution
    fn main() -> i32 {
        let answer = add(40, 2);
        return answer;  // Returns 42
    }
}
```

### Control Flow

```bunker
kernel ControlFlow {
    // If-else expressions
    fn max(a: i32, b: i32) -> i32 {
        if a > b {
            return a;
        } else {
            return b;
        }
    }

    // If-else as expression (returns value)
    fn abs(x: i32) -> i32 {
        let result = if x < 0 { -x } else { x };
        return result;
    }

    // Ternary operator
    fn clamp(value: i32, min: i32, max: i32) -> i32 {
        let clamped = value < min ? min : (value > max ? max : value);
        return clamped;
    }
}
```

### Loops

```bunker
kernel Loops {
    // For loop with range
    fn sum_range(n: i32) -> i32 {
        let total = 0;
        for i in 0..n {
            total = total + i;
        }
        return total;  // 0 + 1 + 2 + ... + (n-1)
    }

    // While loop
    fn factorial(n: i32) -> i32 {
        let result = 1;
        let i = n;
        while i > 1 {
            result = result * i;
            i = i - 1;
        }
        return result;
    }

    // Loop with break
    fn find_first_divisor(n: i32) -> i32 {
        let divisor = 2;
        loop {
            if n % divisor == 0 {
                break;
            }
            divisor = divisor + 1;
            if divisor > n {
                divisor = n;
                break;
            }
        }
        return divisor;
    }

    // For loop with continue
    fn sum_odd_numbers(n: i32) -> i32 {
        let total = 0;
        for i in 0..n {
            if i % 2 == 0 {
                continue;  // Skip even numbers
            }
            total = total + i;
        }
        return total;
    }
}
```

### Structs

```bunker
kernel Geometry {
    // Struct definition
    struct Point {
        x: i32,
        y: i32,
    }

    struct Rectangle {
        origin: Point,
        width: i32,
        height: i32,
    }

    // Function returning a struct
    fn make_point(x: i32, y: i32) -> Point {
        return Point { x: x, y: y };
    }

    // Function taking struct parameter
    fn distance_squared(p: Point) -> i32 {
        return p.x * p.x + p.y * p.y;
    }

    // Nested struct access
    fn rect_area(r: Rectangle) -> i32 {
        return r.width * r.height;
    }

    fn main() -> i32 {
        let p = make_point(3, 4);
        let dist_sq = distance_squared(p);  // 9 + 16 = 25
        return dist_sq;
    }
}
```

### Arrays

```bunker
kernel Arrays {
    // Fixed-size array
    fn sum_array() -> i32 {
        let arr: [i32; 5] = [10, 20, 30, 40, 50];
        let total = 0;
        for i in 0..5 {
            total = total + arr[i];
        }
        return total;  // 150
    }

    // Array mutation
    fn initialize_sequence() -> i32 {
        let arr: [i32; 10] = [0; 10];  // All zeros
        for i in 0..10 {
            arr[i] = i * i;
        }
        return arr[5];  // 25
    }

    // len() builtin
    fn array_length() -> i32 {
        let arr: [i32; 7] = [1, 2, 3, 4, 5, 6, 7];
        return len(arr);  // 7
    }
}
```

### Option Type

```bunker
kernel Options {
    // Option<T> for nullable values
    fn safe_divide(a: i32, b: i32) -> Option<i32> {
        if b == 0 {
            return None::<i32>;
        }
        return Some(a / b);
    }

    // Pattern matching on Option
    fn main() -> i32 {
        let result = safe_divide(10, 2);
        let value = match result {
            Some(x) => x;
            None => 0;
        };
        return value;  // 5
    }
}
```

### Match Expressions

```bunker
kernel Matching {
    fn day_type(day: i32) -> i32 {
        // Match on integer values
        let result = match day {
            0 => 0;  // Sunday - weekend
            6 => 0;  // Saturday - weekend
            1 => 1;  // Weekday
            2 => 1;
            3 => 1;
            4 => 1;
            5 => 1;
            _ => -1;  // Invalid
        };
        return result;
    }

    // Match with binding
    fn describe_number(n: i32) -> i32 {
        let category = match n {
            0 => 0;           // Zero
            x if x < 0 => 1;  // Negative (hypothetical syntax)
            x => 2;           // Positive
        };
        return category;
    }
}
```

### Defer Statement

```bunker
kernel ResourceManagement {
    fn with_cleanup() -> i32 {
        let value = 0;

        // Defer runs at end of scope, LIFO order
        defer {
            value = value + 1;  // Runs third
        }
        defer {
            value = value * 2;  // Runs second
        }

        value = 5;  // Runs first

        return value;  // After defers: ((5) * 2) + 1 = 11
    }
}
```

### Type Casting

```bunker
kernel Casting {
    fn convert_types() -> i32 {
        let i: i32 = 42;
        let f: f64 = i as f64;        // i32 to f64
        let back: i32 = f as i32;     // f64 to i32
        let big: i64 = i as i64;      // i32 to i64
        let small: i32 = big as i32;  // i64 to i32
        return small;
    }
}
```

### Comptime Functions

```bunker
kernel ComptimeExample {
    // Computed at compile time
    comptime fn factorial(n: i32) -> i32 {
        if n <= 1 {
            return 1;
        }
        return n * factorial(n - 1);
    }

    comptime fn fibonacci(n: i32) -> i32 {
        if n <= 1 {
            return n;
        }
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    fn main() -> i32 {
        // These are evaluated at compile time
        let fact_5 = factorial(5);   // 120
        let fib_10 = fibonacci(10);  // 55
        return fact_5;
    }
}
```

### Constants

```bunker
kernel Constants {
    const MAX_SIZE: i32 = 100;
    const PI: f64 = 3.14159;
    const GREETING: str = "Hello";

    fn use_constants() -> i32 {
        let area = PI * 10.0 * 10.0;
        return MAX_SIZE;
    }
}
```

### Verified Functions

```bunker
kernel Banking {
    struct Account {
        balance: i32,
    }

    // Verified function with preconditions and postconditions
    #[verified]
    #[requires(amount > 0)]
    #[requires(from.balance >= amount)]
    #[ensures(from.balance + to.balance == old(from.balance) + old(to.balance))]
    fn transfer(from: Account, to: Account, amount: i32) -> Account {
        from.balance = from.balance - amount;
        to.balance = to.balance + amount;
        return to;
    }
}
```

### Move and Copy Semantics

```bunker
kernel Ownership {
    struct Data {
        value: i32,
    }

    fn move_example() -> i32 {
        let a = Data { value: 42 };
        let b = a;  // a is moved to b, a is no longer valid
        return b.value;
    }

    fn copy_example() -> i32 {
        let a = Data { value: 42 };
        let b = copy a;  // Explicit copy, both a and b are valid
        return a.value + b.value;  // 84
    }
}
```

---

## Shell Layer

The Shell layer manages state and message passing between Agents.

### Basic Agent

```bunker
shell SimpleApp {
    agent Counter {
        // State variables
        count = 0;
        name = "Counter";

        // Message handler
        on receive "increment" {
            count = count + 1;
        }

        on receive "decrement" {
            count = count - 1;
        }

        on receive "reset" {
            count = 0;
        }
    }
}
```

### Message Passing

```bunker
shell Communication {
    agent Sender {
        on receive "start" {
            // Send message to another agent
            send "hello" to Receiver;
        }

        on receive "acknowledged" {
            send "done" to System;
        }
    }

    agent Receiver {
        messages_received = 0;

        on receive "hello" {
            messages_received = messages_received + 1;
            send "acknowledged" to Sender;
        }
    }
}
```

### Message with Arguments

```bunker
shell DataPassing {
    agent DataHandler {
        total = 0;

        // Message with typed parameter
        on receive "add_value" with amount: i32 {
            total = total + amount;
        }

        // Message with multiple parameters
        on receive "add_product" with x: i32, y: i32 {
            total = total + x * y;
        }
    }
}
```

### Conditional Message Handling

```bunker
shell ConditionalLogic {
    agent GameState {
        health = 100;
        alive = true;

        on receive "take_damage" with amount: i32 {
            health = health - amount;

            if health <= 0 {
                alive = false;
                health = 0;
                send "game_over" to System;
            }
        }

        on receive "heal" with amount: i32 {
            if alive {
                health = health + amount;
                if health > 100 {
                    health = 100;
                }
            }
        }
    }
}
```

### Match in Shell

```bunker
shell MatchExample {
    agent Router {
        on receive "route" with destination: i32 {
            match destination > 0 {
                true => send "valid" to Handler;
                false => send "invalid" to ErrorHandler;
            }
        }
    }

    agent Handler {
        on receive "valid" {
            send "processed" to System;
        }
    }

    agent ErrorHandler {
        on receive "invalid" {
            send "error" to System;
        }
    }
}
```

### Defer in Shell

```bunker
shell CleanupExample {
    agent Worker {
        busy = false;

        on receive "start_work" {
            busy = true;

            defer {
                busy = false;  // Always reset busy flag
            }

            // Do work...
            send "work_complete" to Manager;
        }
    }

    agent Manager {
        on receive "work_complete" {
            send "done" to System;
        }
    }
}
```

---

## Shell Calling Kernel

The Shell can call Kernel functions for verified computations.

```bunker
kernel Physics {
    fn calculate_velocity(distance: i32, time: i32) -> i32 {
        if time == 0 {
            return 0;
        }
        return distance / time;
    }

    fn calculate_force(mass: i32, acceleration: i32) -> i32 {
        return mass * acceleration;
    }
}

shell Simulation {
    import Physics;

    agent Particle {
        position = 0;
        velocity = 0;
        mass = 10;

        on receive "update" with time: i32 {
            // Call Kernel function from Shell
            velocity = use Physics.calculate_velocity with distance=position, time=time;
        }

        on receive "apply_force" with acceleration: i32 {
            let force = use Physics.calculate_force with mass=mass, acceleration=acceleration;
            velocity = velocity + force / mass;
        }
    }
}
```

---

## View Layer

The View layer declares reactive UIs that update based on Shell state.

### Basic Window

```bunker
view SimpleWindow {
    #[target(graphics)]
    Window {
        title: "My Application";
        width: 400;
        height: 300;

        Label {
            text: "Hello, Bunker!";
        }
    }
}
```

### Reactive Binding

```bunker
shell CounterApp {
    agent State {
        count = 0;

        on receive "increment" {
            count = count + 1;
        }
    }
}

view CounterView {
    #[target(graphics)]
    Window {
        title: "Counter";
        width: 300;
        height: 200;

        Column {
            // Label automatically updates when State.count changes
            Label {
                text: "Count: " + CounterApp.State.count;
            }

            Button {
                text: "Increment";
                on_click: send "increment" to CounterApp.State;
            }
        }
    }
}
```

### Column Layout

```bunker
view ColumnExample {
    #[target(graphics)]
    Window {
        title: "Column Layout";
        width: 300;
        height: 400;

        Column {
            spacing: 10;  // Gap between children

            Label { text: "Item 1"; }
            Label { text: "Item 2"; }
            Label { text: "Item 3"; }
            Button { text: "Click Me"; }
        }
    }
}
```

### Row Layout

```bunker
view RowExample {
    #[target(graphics)]
    Window {
        title: "Row Layout";
        width: 400;
        height: 100;

        Row {
            spacing: 20;  // Gap between children

            Button { text: "Left"; }
            Button { text: "Center"; }
            Button { text: "Right"; }
        }
    }
}
```

### Grid Layout

```bunker
view GridExample {
    #[target(graphics)]
    Window {
        title: "Grid Layout";
        width: 300;
        height: 300;

        Grid {
            columns: 3;   // Number of columns
            spacing: 5;   // Gap between cells

            Button { text: "1"; }
            Button { text: "2"; }
            Button { text: "3"; }
            Button { text: "4"; }
            Button { text: "5"; }
            Button { text: "6"; }
            Button { text: "7"; }
            Button { text: "8"; }
            Button { text: "9"; }
        }
    }
}
```

### Nested Layouts

```bunker
view NestedLayout {
    #[target(graphics)]
    Window {
        title: "Complex Layout";
        width: 400;
        height: 400;

        Column {
            spacing: 15;

            // Header row
            Row {
                spacing: 10;
                Label { text: "Title"; }
                Button { text: "Menu"; }
            }

            // Content grid
            Grid {
                columns: 2;
                spacing: 5;
                Label { text: "Name:"; }
                Label { text: "Value"; }
                Label { text: "Type:"; }
                Label { text: "String"; }
            }

            // Footer
            Button { text: "Submit"; }
        }
    }
}
```

### Button Click Handlers

```bunker
shell ButtonApp {
    agent State {
        message = "Ready";

        on receive "button_a" {
            message = "Button A clicked";
        }

        on receive "button_b" {
            message = "Button B clicked";
        }

        on receive "action" with value: i32 {
            message = "Action with value";
        }
    }
}

view ButtonView {
    #[target(graphics)]
    Window {
        title: "Buttons";
        width: 300;
        height: 200;

        Column {
            Label { text: ButtonApp.State.message; }

            Row {
                // Simple click handler
                Button {
                    text: "Button A";
                    on_click: send "button_a" to ButtonApp.State;
                }

                // Click handler with arguments
                Button {
                    text: "Button B";
                    on_click: send "action" to ButtonApp.State with value=42;
                }
            }
        }
    }
}
```

---

## Cross-Layer Integration

### Complete Application Example

```bunker
// Kernel: Pure computation layer
kernel Calculator {
    fn add(a: i32, b: i32) -> i32 {
        return a + b;
    }

    fn subtract(a: i32, b: i32) -> i32 {
        return a - b;
    }

    fn multiply(a: i32, b: i32) -> i32 {
        return a * b;
    }

    fn divide(a: i32, b: i32) -> i32 {
        if b == 0 {
            return 0;
        }
        return a / b;
    }
}

// Shell: State management and message handling
shell CalculatorApp {
    import Calculator;

    agent State {
        display = 0;
        operand = 0;
        operator = 0;

        on receive "digit" with value: i32 {
            display = display * 10 + value;
        }

        on receive "clear" {
            display = 0;
            operand = 0;
            operator = 0;
        }

        on receive "add" {
            operand = display;
            operator = 1;
            display = 0;
        }

        on receive "equals" {
            if operator == 1 {
                display = use Calculator.add with a=operand, b=display;
            }
            operator = 0;
        }
    }
}

// View: Reactive user interface
view CalculatorView {
    #[target(graphics)]
    Window {
        title: "Calculator";
        width: 300;
        height: 400;

        Column {
            spacing: 10;

            // Display
            Label {
                text: CalculatorApp.State.display;
            }

            // Number grid
            Grid {
                columns: 3;
                spacing: 5;
                Button { text: "7"; on_click: send "digit" to CalculatorApp.State with value=7; }
                Button { text: "8"; on_click: send "digit" to CalculatorApp.State with value=8; }
                Button { text: "9"; on_click: send "digit" to CalculatorApp.State with value=9; }
                Button { text: "4"; on_click: send "digit" to CalculatorApp.State with value=4; }
                Button { text: "5"; on_click: send "digit" to CalculatorApp.State with value=5; }
                Button { text: "6"; on_click: send "digit" to CalculatorApp.State with value=6; }
                Button { text: "1"; on_click: send "digit" to CalculatorApp.State with value=1; }
                Button { text: "2"; on_click: send "digit" to CalculatorApp.State with value=2; }
                Button { text: "3"; on_click: send "digit" to CalculatorApp.State with value=3; }
            }

            // Operators
            Row {
                spacing: 5;
                Button { text: "+"; on_click: send "add" to CalculatorApp.State; }
                Button { text: "="; on_click: send "equals" to CalculatorApp.State; }
                Button { text: "C"; on_click: send "clear" to CalculatorApp.State; }
            }
        }
    }
}
```

---

## Type Reference

| Type | Description | Example |
|------|-------------|---------|
| `i32` | 32-bit signed integer | `let x: i32 = 42;` |
| `i64` | 64-bit signed integer | `let big: i64 = 9223372036854775807;` |
| `f64` | 64-bit floating point | `let pi: f64 = 3.14159;` |
| `bool` | Boolean | `let flag: bool = true;` |
| `str` | String | `let name: str = "Bunker";` |
| `[T; N]` | Fixed-size array | `let arr: [i32; 5] = [1, 2, 3, 4, 5];` |
| `Option<T>` | Nullable value | `let maybe: Option<i32> = Some(42);` |

## Operator Reference

| Category | Operators |
|----------|-----------|
| Arithmetic | `+`, `-`, `*`, `/`, `%` |
| Comparison | `==`, `!=`, `<`, `<=`, `>`, `>=` |
| Logical | `&&`, `\|\|`, `!` |
| Bitwise | `&`, `\|`, `^`, `<<`, `>>` |
| Assignment | `=` |
| Ternary | `? :` |

## Keywords

```
kernel, shell, view, agent, fn, comptime, struct, const,
let, return, if, else, for, while, loop, break, continue,
match, defer, send, to, with, on, receive, import, use,
true, false, Some, None, copy
```

## Attributes

| Attribute | Purpose | Layer |
|-----------|---------|-------|
| `#[verified]` | Enable Z3 verification | Kernel |
| `#[requires(expr)]` | Precondition | Kernel |
| `#[ensures(expr)]` | Postcondition | Kernel |
| `#[target(graphics)]` | Win32 GUI target | View |
| `#[target(embedded)]` | Text/embedded target | View |
