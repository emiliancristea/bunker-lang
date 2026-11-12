# Bunker Bootstrap Seed & Standalone Toolchain

This directory holds two bootstrap seeds for the self-hosted Bunker compiler (`bkrc`):

- **`bkrc-linux-x86_64`**: a native Linux x86-64 `bkrc` binary built by Bunker itself. With it, Bunker builds with no other language, compiler, linker or libc:

  ```bash
  bash bootstrap/build-native.sh   # seed -> stage 1 -> stage 2, fails unless stage 1 == stage 2
  ```

  `SHA256SUMS.native` holds its checksum. CI also builds the compiler through the C seed and checks both paths give the same binary, so the binary seed can always be re-derived from source.

- **The portable C11 seed** below, for other platforms and as an independent cross-check.

## Overview

Per the architecture defined in [`docs/BOOTSTRAP.md`](../docs/BOOTSTRAP.md) and [`docs/RUST_MIGRATION_MAP.md`](../docs/RUST_MIGRATION_MAP.md) (Phase 5: Stage 0 Deprecation & Toolchain Independence), Bunker achieves complete independence from the initial Rust host implementation (`bunker-cli`) by distributing a verified, reproducible C11 compiler translation.

With this directory, Bunker can be bootstrapped on any system that has a standard C compiler (GCC, Clang, or MSVC) **with zero dependencies on Rust, Cargo, Cranelift, or Pest**.

## Contents

- `bkrc-stage1.c`: The complete Stage 1 self-host compiler generated from `self-host/bkrc.bkr` and all 8 compiler modules.
- `bkrc-stage2.c`: The Stage 2 self-compiled C code verifying fixpoint determinism (`diff -u bkrc-stage1.c bkrc-stage2.c`).
- `runtime.h`: The standalone Bunker C ABI runtime header.
- `SHA256SUMS`: Cryptographic verification checksums for reproducible build certification.
- `build.sh`: One-step shell build script for Linux and macOS (`cc -std=c11 -O2`).
- `build.bat`: One-step batch build script for Windows (`cl.exe`, `gcc`, or `clang`).

## Quick Start (Zero Rust Required)

### Linux / macOS
```bash
./bootstrap/build.sh
./bkrc my_program.bkr -o my_program.c
cc -std=c11 my_program.c -o my_program
./my_program
```

### Windows
```cmd
bootstrap\build.bat
bkrc.exe my_program.bkr -o my_program.c
gcc -std=c11 my_program.c -o my_program.exe
my_program.exe
```

## Self-Compilation Fixpoint

Once `bkrc` is compiled from `bootstrap/bkrc-stage1.c`, it can compile its own source code directly:
```bash
./bkrc self-host/bkrc.bkr -o stage2.c
diff -u bootstrap/bkrc-stage2.c stage2.c
```
Zero diff confirms fixpoint stability and compiler determinism.
