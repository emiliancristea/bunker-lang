# Bunker CLI Argument Parsing & Structured Logging Architecture

**Document ID:** `BKR-SPEC-CLI-001`  
**Status:** Canonical & Locked  
**Scope:** Runtime & Standard Library (`R-010`, `R-011`)  
**Ecosystem Milestone:** `Q-291`  

---

## 1. Executive Summary & Architectural Motivation

Compilers, toolchains, and runtime services require robust, deterministic interfaces for command-line argument processing and structured diagnostic logging. Historically, low-level builtins (`args_count()`, `arg_at()`) provided primitive string access, leaving application logic to manually scan slices and re-implement flag parsing.

This specification formalizes two first-class, zero-dependency standard library modules authored in pure Bunker:

1. **`self-host/modules/cli_args.bkr` (`R-010`)**: A comprehensive command-line interface specification engine supporting long flags (`--verbose`), short flags (`-v`), key-value options with explicit equals (`--output=file.c`) and adjacent tokens (`--output file.c`), positional arguments, `--` argument termination, validation of required parameters, and deterministic `--help` manual rendering.
2. **`self-host/modules/logger.bkr` (`R-011`)**: A structured logging facility featuring five monotonic severity tiers (`TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`), environment-driven filtering (`BUNKER_LOG`), target-scoped filtering, dual-mode formatting (human-readable ANSI-ready text and machine-readable `bunker.log.v1` JSON), and monotonic timestamp attribution.

---

## 2. Command-Line Argument Parser Architecture (`R-010`)

### 2.1 Lexical & Syntactic Grammar

Bunker CLI tokens are parsed according to standard POSIX and GNU conventions:

| Token Form | Example | Interpretation |
|---|---|---|
| **Long Flag** | `--verbose` | Sets boolean flag `verbose` to `"true"` |
| **Short Flag** | `-v` | Matches short alias `v` and sets flag `verbose` to `"true"` |
| **Long Option (Inline)** | `--out=dist/main.c` | Extracts option `out` with value `"dist/main.c"` |
| **Long Option (Adjacent)** | `--out dist/main.c` | Consumes lookahead token as value for option `out` |
| **Short Option (Adjacent)**| `-o dist/main.c` | Consumes lookahead token as value for short alias `o` |
| **Positional Argument** | `src/main.bkr` | Assigned sequentially to declared positional parameters |
| **Argument Terminator** | `--` | Terminates option parsing; all subsequent tokens are positionals |

### 2.2 Data Structures & Representation

```bunker
struct CliOption {
    name: str,          // Canonical long name, e.g. "output"
    short_name: str,    // 1-character short alias, e.g. "o"
    description: str,   // Help text
    default_val: str,   // Default value if omitted
    is_flag: bool       // True if boolean toggle (takes no value token)
}

struct CliParser {
    program_name: str,
    description: str,
    options: Vec<CliOption>,
    pos_names: Vec<str>,
    pos_descs: Vec<str>,
    pos_required: Vec<bool>
}

struct CliParsedArgs {
    flag_keys: Vec<str>,
    flag_vals: Vec<bool>,
    opt_keys: Vec<str>,
    opt_vals: Vec<str>,
    positionals: Vec<str>
}
```

### 2.3 Error Handling & Help Generation

The parser validates:
- **Missing Value**: Option specified as `--key` (or `-k`) at end of argument vector without a value returns `Err("Option '--key' requires an argument")`.
- **Unknown Option**: Unrecognized `--option` returns `Err("Unknown option: '--option'")`.
- **Missing Positional**: Missing required positional parameters returns `Err("Missing required argument: '<name>'")`.
- **Help Request**: `--help` or `-h` automatically renders a clean terminal usage manual listing syntax, description, positional arguments, and aligned flags/options.

---

## 3. Structured Logging Architecture (`R-011`)

### 3.1 Severity Levels

Severity is represented as a monotonic 64-bit integer:

| Level | Integer Value | Semantics & Intended Usage |
|---|---|---|
| `TRACE` | 10 | High-frequency AST nodes, token streams, memory watermarks |
| `DEBUG` | 20 | Resolution decisions, type inferences, branch specializations |
| `INFO` | 30 | Compiler phase completions, build outputs, elapsed execution times |
| `WARN` | 40 | Deprecated language features, non-fatal performance notices |
| `ERROR` | 50 | Unrecoverable phase errors, invariant violations, fatal exits |

### 3.2 Filter Configuration

Logging threshold is determined hierarchically:
1. Explicit threshold passed to `logger_new(target, min_level)`.
2. Fallback to `BUNKER_LOG` environment variable via `logger_init_from_env()`.
3. Default threshold: `INFO` (30).

The environment parser accepts case-insensitive level names (`"trace"`, `"debug"`, `"info"`, `"warn"`, `"error"`) or raw integer strings (`"10"`, `"20"`, etc.).

### 3.3 Log Record & Schema

```bunker
struct Logger {
    target: str,
    min_level: i64
}

struct LogRecord {
    level: i64,
    target: str,
    message: str,
    timestamp_unix: i64,
    timestamp_ms: i64
}
```

#### Dual Serialization Formats:

1. **Text Format**:
   ```text
   [2026-10-26T18:50:00Z] [INFO] [bunker::compiler] Parsing src/main.bkr completed in 12ms
   ```

2. **JSON Format (`bunker.log.v1`)**:
   ```json
   {
       "schema_version": "bunker.log.v1",
       "timestamp_unix": 1793040600,
       "timestamp_ms": 1793040600123,
       "level": "INFO",
       "level_code": 30,
       "target": "bunker::compiler",
       "message": "Parsing completed successfully",
       "attributes": {
           "file": "src/main.bkr",
           "tokens": 4250,
           "duration_ms": 12
       }
   }
   ```

---

## 4. Verification & Conformance Matrix

| Test Identifier | Coverage / Verification Target | Expected Result |
|---|---|---|
| `tests/248_cli_argument_parser.bkr` | Flags, options (inline & adjacent), short aliases, positionals, `--` terminator, default values, error diagnostics, and `--help` text | Returns 42 |
| `tests/249_structured_logging.bkr` | Level thresholds, filtering (`logger_is_enabled`), text formatting, JSON serialization (`bunker.log.v1`), and environment override | Returns 42 |
| `bunker self-host-check` | Module validation for `cli_args.bkr` and `logger.bkr` in `self-host/` | 8/8 files, 0 diagnostics |
| `bunker self-host-compile` | Compilation of test fixtures through self-host C codegen | Generated C accepted |
| `run_tests.ps1` | Full test suite execution across all 264+ fixtures | 100% pass rate |

---

## 5. Security & Isolation Guarantees

- **No Arbitrary Memory Allocations**: CLI and Logger state structures utilize standard `Vec<str>`, `Vec<bool>`, `Vec<i64>` managed by the runtime arena.
- **Pure Functions**: Formatting and parsing functions operate deterministically on provided strings without mutating host global state or performing unsanctioned I/O.
- **Fail-Safe Fallbacks**: Missing environment variables or malformed inputs return well-typed `Result::Err` or fallback to safe defaults, never crashing the host process.
