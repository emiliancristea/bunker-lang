# Self-Host Bootstrap Subset

The following kernel programs are required for the current bootstrap gate in `run_tests.ps1`.
This list is intentionally explicit so AI workflows can report exact progress toward full self-hosting.

- `tests\01_basic_math.bkr` ?
- `tests\14_kernel_if_branching.bkr` ?
- `tests\38_kernel_while_loop.bkr` ?
- `tests\39_kernel_while_break.bkr` ?

## Supported constructs in this gate
- `kernel` and `fn`
- `let` with optional types
- `if` / `else`
- `while`
- `break` / `continue`
- arithmetic and boolean operators already handled by `bkrc.bkr`
- function calls with nested argument expressions
- string literal emission
- basic `str` concatenation in expressions
