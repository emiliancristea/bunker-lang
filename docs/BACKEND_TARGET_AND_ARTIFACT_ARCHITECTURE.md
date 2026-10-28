# Bunker Backend Target Strategy and Deterministic Artifact Layout Specification

- **Document ID:** `BKR-SPEC-CGEN-003`
- **Track:** Compiler Backend (`CB`)
- **Milestones Covered:** `CB-009` (P2: Multi-target backend strategy), `CB-010` (P1: Artifact layout)
- **Status:** `LOCKED`
- **Date:** 2026-10-27
- **Schema Versions:** `bunker.capability.v1`, `bunker.self_host.target.v1`, `bunker.artifact.v1`

---

## 1. Executive Summary

This specification formalizes the multi-target backend architecture (`CB-009`) and deterministic artifact layout hierarchy (`CB-010`) of the Bunker compiler infrastructure across both the Rust bootstrap toolchain (`bunker-cli`) and the self-host compiler (`self-host/modules/driver.bkr` and `self-host/modules/c_codegen.bkr`).

Bunker serves distinct execution environments ranging from rapid agent-driven test-repair cycles to production deployment on heterogeneous platforms. This document defines the clear roles of each code generation target (Cranelift JIT, C Codegen, LLVM AOT), establishes the canonical driver interface for target selection, and locks a deterministic, reproducible artifact filesystem layout.

With this specification and implementation, Track `CB` items `CB-009` and `CB-010` transition to `DONE`.

---

## 2. Multi-Target Backend Architecture (CB-009)

The Bunker compiler architecture decouples the frontend (lexer, parser, typechecker, type graph) from the backend code generation pipeline through a three-tier target strategy:

```
                  [Typed Bunker AST & IR]
                             │
         ┌───────────────────┼───────────────────┐
         ▼                   ▼                   ▼
┌──────────────────┐┌──────────────────┐┌──────────────────┐
│  Cranelift JIT   ││     C Codegen    ││     LLVM AOT     │
│   (Developer)    ││ (Self-Host & OS) ││   (Production)   │
└──────────────────┘└──────────────────┘└──────────────────┘
         │                   │                   │
         ▼                   ▼                   ▼
  In-Memory Exec       Portable C99/GNU       Native Binary
   (< 1ms startup)      (Universal C ABI)    (Full LTO & SIMD)
```

### 2.1 Backend Target Roles & Profiles

1. **Cranelift JIT Backend (`--backend=cranelift` / `bunker run`):**
   - **Role:** Interactive development, test suites, and sub-second feedback for AI coding agents.
   - **Characteristics:** In-memory native machine code compilation directly to executable memory pages via Cranelift. Zero external linker dependency. Ultra-fast compile times (< 5ms per file).
   - **Primary Execution Mode:** Default target for `bunker run` and `run_tests.ps1`.

2. **C Backend (`--backend=c` / `bunker self-host-compile`):**
   - **Role:** Self-hosting bootstrap compiler, embedded systems, and universal cross-platform deployment.
   - **Characteristics:** Pure Bunker translation to portable C99 / GNU statement expressions linked against `runtime.h`. Compiles on any platform with a conforming C compiler (GCC, Clang, MinGW, Apple Clang).
   - **Primary Execution Mode:** Default target for `bkrc.bkr` and full self-hosting bootstrapping.

3. **LLVM AOT Backend (`--backend=llvm` / `bunker build --release`):**
   - **Role:** Production deployment, performance-critical services, and release binaries.
   - **Characteristics:** Whole-program Link-Time Optimization (LTO), auto-vectorization, architecture-specific target tuning (`march=native`), and stripping. Produces standalone executables (`.exe` on Windows, ELF on Linux, Mach-O on macOS).

---

## 3. Deterministic Artifact Layout Specification (CB-010)

### 3.1 Canonical Directory Hierarchy

Bunker projects adopt a standardized, reproducible artifact directory layout rooted at `target/`:

```
<project_root>/
  ├── target/
  │    ├── debug/
  │    │    ├── bin/              # Unoptimized debug executables
  │    │    ├── c/                # Intermediate generated C source files
  │    │    ├── obj/              # Intermediate compiled object files (.o, .obj)
  │    │    └── manifest.json     # Machine-readable compilation manifest
  │    ├── release/
  │    │    ├── bin/              # Fully optimized release executables
  │    │    ├── c/                # Production C output
  │    │    ├── obj/              # Optimized object files
  │    │    └── manifest.json     # Release build manifest
  │    └── cache/                 # Incremental AST and IR caches
```

### 3.2 Invariants for Deterministic Artifact Generation

- **Invariant ARTIFACT-DET-01 (Reproducible Content):** Compiling identical source files with identical compiler flags and compiler versions yields bit-for-bit identical output artifacts. Wall-clock timestamps, user usernames, and machine-specific absolute paths are strictly forbidden in emitted code and manifest files.
- **Invariant ARTIFACT-DET-02 (Deterministic Naming):** Output artifact filenames are strictly derived from the root kernel or module name:
  - Source `file_io.bkr` targeting C produces `file_io.c`.
  - Binary outputs produce `<module_name>` (POSIX) or `<module_name>.exe` (Windows).
  - Intermediate files produce `<module_name>.o` / `<module_name>.obj`.
- **Invariant ARTIFACT-DET-03 (Build Manifest Contract):** Every build produces a structured `manifest.json` conforming to `bunker.artifact.v1`:
  ```json
  {
    "schema_version": "bunker.artifact.v1",
    "target": "c",
    "profile": "debug",
    "input_file": "src/main.bkr",
    "output_file": "target/debug/c/main.c",
    "source_hash": "sha256:...",
    "compiler_version": "0.1.0",
    "abi_version": "1.0.0",
    "deterministic": true
  }
  ```

---

## 4. Capability JSON Integration

The compiler driver exposes backend target and artifact capabilities in `bunker.capability.v1`:

```json
{
  "multi_target_backend_strategy": true,
  "deterministic_artifact_layout": true,
  "supported_backends": "c, cranelift, llvm"
}
```

---

## 5. Verification Matrix

| Milestone | Feature | Test Fixture | Expected Result |
|---|---|---|---|
| `CB-009` | Multi-Target Backend Selection & Roles | `tests/266_multi_target_backend_strategy.bkr` | Returns 42 |
| `CB-010` | Deterministic Artifact Layout & Hashing | `tests/267_deterministic_artifact_layout.bkr` | Returns 42 |
| `CB-009/10` | Self-Host Compilation Subset | `run_tests.ps1` (`$selfHostSubset`) | 100% Pass Rate |
