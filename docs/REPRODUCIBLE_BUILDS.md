# Bunker Reproducible Self-Host Artifact Specification

**Authoritative Specification for Deterministic Builds, Fixpoints, and Cryptographic Artifact Verification**  
**Document ID:** `BKR-SPEC-REPRO-001`  
**Tracker Reference:** Milestone `Q-241` / `SH-010`  
**Status:** Approved & Enforced  

---

## 1. Executive Summary & Design Invariants

Bunker compiler self-hosting demands strict **byte-for-byte reproducibility**. A self-hosted compiler must not introduce non-deterministic variations (timestamps, unseeded hash maps, platform pointer leaks, or unstable collection iterations) into generated machine code or intermediate representations.

This document defines the formal reproducibility contract, the cryptographic checksum protocol (`SHA256SUMS`), the fixpoint verification criteria, and the artifact distribution structure for Bunker self-host compiler releases.

---

## 2. The Determinism Invariant & Fixpoint Proof

During the self-host bootstrap pipeline, the compiler undergoes a multi-stage self-compilation loop:
1. **Stage 0 (`bunker-cli`):** Compiles `self-host/bkrc.bkr` into `bkrc-stage1.c`.
2. **Stage 1 Binary (`bkrc`):** Compiled via native C compiler (`cc -std=c11 bkrc-stage1.c -o bkrc`).
3. **Stage 2 Compilation:** `bkrc` compiles its own source code `self-host/bkrc.bkr` into `bkrc-stage2.c`.

### 2.1. Fixpoint Invariant
The fixpoint invariant requires that `bkrc-stage1.c` and `bkrc-stage2.c` are identical in their semantic and emitted code structure:
```bash
diff -u /tmp/bkrc.c "$self_compile_dir/self_host_output.c"
```
Zero diff demonstrates that the self-hosted compiler has reached a stable mathematical fixpoint: compiling the compiler with itself introduces no code drift or dialect deviation.

---

## 3. Cryptographic Checksums & Manifest (`SHA256SUMS`)

Every CI run and distribution packaging step must compute SHA-256 cryptographic hashes for all generated stage assets and runtime headers.

### 3.1. Artifact Structure
```
self-host-artifacts/
├── bkrc-stage1.c       # C source emitted by Stage 0 (Rust host)
├── bkrc-stage1         # Executable binary compiled from bkrc-stage1.c
├── bkrc-stage2.c       # C source emitted by Stage 1 (pure Bunker bkrc)
├── bkrc-stage2         # Executable binary compiled from bkrc-stage2.c
├── runtime.h           # Canonical C ABI runtime header
└── SHA256SUMS          # Cryptographic verification manifest
```

### 3.2. Manifest Generation
Manifest generation is automated in `.github/workflows/ci.yml`:
```bash
(cd self-host-artifacts && sha256sum bkrc-stage1.c bkrc-stage2.c runtime.h > SHA256SUMS)
cat self-host-artifacts/SHA256SUMS
sha256sum -c self-host-artifacts/SHA256SUMS
```

### 3.3. Verification by Downstream Consumers
Downstream users or independent auditors verifying an artifact archive can execute:
```bash
sha256sum -c SHA256SUMS
```
This guarantees that:
1. None of the stage sources or runtime headers were modified or corrupted in transit.
2. The Stage 2 compiler code matches the verified upstream build.

---

## 4. Sources of Non-Determinism and Elimination Rules

To maintain strict reproducibility, all Bunker compiler modules must observe the following rules:

1. **Deterministic Hash Map Iteration:** Symbol tables, identifier tables, and type registries must never rely on random hash seeds for iteration order. Output declarations must sort or preserve insertion order.
2. **Normalized Line Endings:** Source files and emitted C code must use uniform LF (`\n`) in Linux/CI environments and preserve exact formatting across compilation passes.
3. **No Dynamic Timestamps in Code:** Emitted C headers must use static build markers rather than dynamic timestamps (`__DATE__`, `__TIME__`) to ensure reproducible object hashes.
4. **Stable Capability Reports:** Machine-readable diagnostics (`BUNKER_CAPABILITY_JSON`) must emit JSON fields in fixed, deterministic lexical order.
