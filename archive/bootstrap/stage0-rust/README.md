# Archived Stage 0 Bootstrap Compiler (Rust)

**Status:** RETRACTED & ARCHIVED
**Specification:** `BKR-SPEC-MIGRATE-001` (Milestone `Q-240` / `SH-008`, Phase 5: Stage 0 Sunsetting)

---

## Historical Context

This directory contains the initial Stage 0 bootstrap compiler (`bunker-cli`), historically implemented in Rust using Cranelift, Pest, and Z3. It served as the temporary bootstrapping host used to develop and compile the self-hosted Bunker compiler (`self-host/bkrc.bkr`).

As of the completion of the 4-phase pure-Bunker transition roadmap:
1. **Shell Layer (`self-host/modules/shell.bkr`)**: Complete native actor system in pure Bunker (`BKR-SPEC-SHELL-001`).
2. **View Layer (`self-host/modules/view.bkr`)**: Complete declarative UI runtime in pure Bunker (`BKR-SPEC-VIEW-001`).
3. **Verification Engine (`self-host/modules/verify.bkr`)**: Complete linear arithmetic contract verification in pure Bunker (`BKR-SPEC-VERIFY-001`).
4. **Bootstrap & Toolchain Independence (`bootstrap/`)**: Standalone C11 bootstrap compiler package (`bkrc-stage1.c`, `runtime.h`) requiring only a standard C compiler (GCC, Clang, MSVC).

## Active Toolchain

The active Bunker language toolchain is 100% pure Bunker:
- **Compiler Source**: `self-host/bkrc.bkr` and `self-host/modules/*.bkr`
- **Bootstrap Package**: `bootstrap/build.sh` (POSIX) / `bootstrap/build.bat` (Windows)
- **Runtime**: `self-host/runtime.h`
