# Bunker Cross-Platform CI and Versioning Rules Architecture Specification

- **Specification ID**: `BKR-SPEC-ECO-001`
- **Target Subsystems**: CI Pipeline, Driver, Standard Library, C Runtime ABI, Build System, Package Manager
- **Status**: `LOCKED`
- **Related Documents**: `BKR-SPEC-SAFE-001` (`docs/SAFETY_MODEL.md`), `BKR-SPEC-SEC-001` (`docs/SANDBOX_SECURITY_MODEL.md`), `BKR-SPEC-REPRO-001` (`docs/REPRODUCIBLE_BUILDS.md`), `BKR-SPEC-TOOL-003` (`docs/PACKAGE_MANAGER_AND_BUILD_CACHE_ARCHITECTURE.md`)

---

## 1. Executive Summary

This specification establishes the production standards for continuous multi-OS integration and explicit four-plane versioning contracts in the Bunker ecosystem:
1. **Cross-Platform Continuous Integration Architecture (`S-013`)**: A multi-OS matrix pipeline (`ubuntu-latest`, `windows-latest`, `macos-latest` across x86_64 and arm64 architectures) verifying the reference Rust compiler, Cranelift JIT engine, pure Bunker self-host compiler (`bkrc`), Stage 1/Stage 2 bootstrap fixpoint determinism, C runtime ABI portability, and OS-specific capability boundaries.
2. **Explicit Four-Plane Versioning Rules (`E-002`)**: A strict SemVer 2.0 versioning architecture codifying semantic stability and compatibility contracts across four independent planes:
   - **Language Grammar Edition** (`#![version = "..."]`)
   - **Compiler Engine Version** (`bunker-cli`, `bkrc`)
   - **Standard Library Version** (`bunker-stdlib`)
   - **C Runtime ABI Compatibility Version** (`BKR_ABI_VERSION = 1`)

---

## 2. Cross-Platform CI Architecture (`S-013`)

### 2.1 Multi-OS Matrix Grid

Every continuous integration run executes across a tri-platform matrix grid with distinct compiler and runtime constraints:

| OS Runner | Architectures | Target C Toolchains | Primary Verification Responsibilities |
|---|---|---|---|
| `ubuntu-latest` | x86_64, aarch64 | GCC 11+, Clang 14+ | Production reference JIT, self-host bootstrap smoke, Stage 1/Stage 2 C source SHA-256 fixpoint verification, AddressSanitizer/UBSan validation. |
| `windows-latest` | x86_64 | MSVC (cl.exe), MinGW-w64 | Native Windows path handling (backslashes, drive letters), line-ending normalization (CRLF vs LF), PE32+ executable generation, PowerShell runner parity. |
| `macos-latest` | arm64 (Apple Silicon) | Apple Clang / Xcode | Mach-O binary emission, W^X page protection compliance in JIT execution, ARM64 calling convention alignment. |

### 2.2 Bootstrap Fixpoint Verification

Cross-platform CI enforces reproducible compilation fixpoint determinism (`BKR-SPEC-REPRO-001`):
1. **Stage 0 (`bunker-cli` in Rust)** compiles `self-host/bkrc.bkr` to generate `stage1_bkrc.c`.
2. **Stage 1 (`stage1_bkrc.c` compiled via host C toolchain)** compiles `self-host/bkrc.bkr` to generate `stage2_bkrc.c`.
3. **Fixpoint Assertion**: `stage1_bkrc.c` and `stage2_bkrc.c` must produce bit-for-bit identical outputs:
   $$\text{SHA256}(\text{stage1\_bkrc.c}) \equiv \text{SHA256}(\text{stage2\_bkrc.c})$$
4. Any byte divergence triggers immediate CI build failure.

### 2.3 CI Execution Report Schema (`bunker.ci.v1`)

```json
{
  "schema": "bunker.ci.v1",
  "os": "ubuntu-latest",
  "arch": "x86_64",
  "c_compiler": "clang-14",
  "stages": {
    "rust_build": "PASS",
    "jit_tests": "PASS",
    "self_host_compile": "PASS",
    "stage1_stage2_fixpoint": "PASS"
  },
  "total_tests": 306,
  "passed_tests": 306,
  "status": "PASS"
}
```

---

## 3. Explicit Four-Plane Versioning Rules (`E-002`)

### 3.1 Four-Plane Separation Model

To prevent breaking changes in one layer from destabilizing the entire language ecosystem, Bunker separates versioning into four orthogonal planes:

```
┌────────────────────────────────────────────────────────────────────────┐
│ 1. Language Grammar Edition (#![version = "1.0"] / "2026")             │
│    - Syntax forms, keywords, operator precedence, type rules           │
├────────────────────────────────────────────────────────────────────────┤
│ 2. Compiler Engine Version (bunker-cli 1.0.0 / bkrc 1.0.0)             │
│    - CLI flags, optimization passes, diagnostics formatting            │
├────────────────────────────────────────────────────────────────────────┤
│ 3. Standard Library Version (bunker-stdlib 1.0.0)                      │
│    - Modules (io, math, string, collections), signatures, contracts     │
├────────────────────────────────────────────────────────────────────────┤
│ 4. C Runtime ABI Version (BKR_ABI_VERSION = 1, __bkr_abi_v1)           │
│    - Memory layout, struct alignment, C symbol exports, FFI            │
└────────────────────────────────────────────────────────────────────────┘
```

### 3.2 Compatibility Matrix & Version Semantics

Each plane follows strict SemVer 2.0 semantics (`MAJOR.MINOR.PATCH`):

| Plane | Breaking Change Trigger (MAJOR) | Backward-Compatible Feature (MINOR) | Bugfix / Performance (PATCH) |
|---|---|---|---|
| **Language Grammar** | Syntax removal, keyword addition, precedence change. | New non-reserved syntax, new standard attributes. | Diagnostic grammar phrasing, span precision. |
| **Compiler Engine** | Removal of CLI arguments, machine JSON schema change. | New CLI commands (`bunker bench`), new optional flags. | Internal compiler bugfixes, codegen optimization. |
| **Standard Library** | Function removal, parameter type change, return alteration. | New stdlib functions, new container methods. | Internal algorithm optimization, bug fixes. |
| **C Runtime ABI** | Struct field layout reordering, calling convention change. | New non-colliding exported runtime symbols. | Internal C runtime implementations. |

### 3.3 Version Manifest Schema (`bunker.version.v1`)

```json
{
  "schema": "bunker.version.v1",
  "language_edition": "1.0",
  "compiler_version": "1.0.0",
  "stdlib_version": "1.0.0",
  "abi_version": 1,
  "abi_symbol_tag": "__bkr_abi_v1",
  "compatible": true
}
```

---

## 4. Tooling & Driver Integration

- **Capability Reflection**: `self_host_capability_json()` in `self-host/modules/driver.bkr` exposes:
  ```json
  "cross_platform_ci": true,
  "versioning_rules": true
  ```
- **CLI Commands**:
  - `bunker --version --json`: Emits canonical `bunker.version.v1` manifest.
  - `bunker check --ci-matrix`: Verifies cross-platform compliance checks.
- **Self-Host Verification**: Zero diagnostics under `bunker self-host-check`.
