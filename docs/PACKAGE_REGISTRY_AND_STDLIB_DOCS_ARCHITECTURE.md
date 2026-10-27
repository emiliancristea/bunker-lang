# Bunker Package Registry and Standard Library Documentation Architecture Specification

- **Specification ID**: `BKR-SPEC-ECO-002`
- **Target Subsystems**: Package Manager, Standard Library, Doc Generator, CLI Tooling, Driver
- **Status**: `LOCKED`
- **Related Documents**: `BKR-SPEC-TOOL-002` (`docs/TEST_RUNNER_AND_DOC_GENERATOR_ARCHITECTURE.md`), `BKR-SPEC-TOOL-003` (`docs/PACKAGE_MANAGER_AND_BUILD_CACHE_ARCHITECTURE.md`), `BKR-SPEC-ECO-001` (`docs/CI_AND_VERSIONING_ARCHITECTURE.md`)

---

## 1. Executive Summary

This specification establishes the production architectures for decentralized package distribution and canonical standard library documentation in the Bunker ecosystem:
1. **Package Registry & Archive Format (`E-001`)**: A content-addressed distribution archive format (`.bpk` container with cryptographic SHA-256 validation), offline-first local cache hierarchy (`~/.bunker/registry/`), index synchronization engine, and structured registry index schema (`bunker.registry.v1`).
2. **Standard Library Documentation & API Catalog (`E-003`)**: Complete API specifications, parameter/return contracts, invariant rules, and runnable usage examples for all core standard library modules (`core::io`, `core::string`, `core::vec`, `core::hashmap`, `core::process`, `core::math`, `core::arena`), paired with machine-readable API catalog export (`bunker doc --stdlib`, schema `bunker.stdlib_doc.v1`).

---

## 2. Package Registry & Archive Format Architecture (`E-001`)

### 2.1 The Bunker Package Container Format (`.bpk`)

A Bunker package archive (`.bpk`) is a self-contained, content-addressed container with a deterministic header and payload:

```
+------------------------------------------------------------------------+
| MAGIC: 4 bytes ("BPK1")                                                |
+------------------------------------------------------------------------+
| METADATA HEADER (JSON UTF-8, variable length, null-terminated)         |
|   { "name": "...", "version": "...", "checksum": "sha256:...", ... }   |
+------------------------------------------------------------------------+
| COMPRESSED PAYLOAD (Tar/Deflate payload of source files & Bunker.toml)  |
+------------------------------------------------------------------------+
```

### 2.2 Local Registry Cache Hierarchy

Packages are stored offline in a deterministic, content-addressed directory tree:
```
~/.bunker/registry/
├── index/                     # Synchronized Git/JSON sparse package index
│   ├── config.json            # Registry endpoints, download URL templates
│   └── pkgs/
│       ├── b/u/bunker-math.json
│       └── s/t/string-utils.json
└── cache/                     # Content-addressed archive storage
    ├── bunker-math-1.2.0.bpk
    └── string-utils-0.4.1.bpk
```

### 2.3 Package Registry Index Schema (`bunker.registry.v1`)

```json
{
  "schema": "bunker.registry.v1",
  "package": "bunker-math",
  "version": "1.2.0",
  "description": "High-performance fixed-point and floating-point math routines",
  "license": "MIT OR Apache-2.0",
  "sha256": "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
  "size_bytes": 14820,
  "dependencies": {
    "core-types": "^1.0.0"
  },
  "yanked": false
}
```

---

## 3. Standard Library Documentation & API Catalog (`E-003`)

### 3.1 Standard Library Module Topography

The canonical Bunker standard library is organized into seven foundational modules:

| Module | Core Responsibility | Key Function Primitives |
|---|---|---|
| `core::io` | Native filesystem read/write operations and stream I/O | `read_file(path)`, `write_file(path, data)`, `file_exists(path)`, `read_file_result(path)`, `write_file_result(path, data)` |
| `core::string` | Byte and UTF-8 string manipulation, parsing, conversion | `len(s)`, `substring(s, start, end)`, `string_concat(a, b)`, `parse_int(s)`, `parse_int_result(s)`, `int_to_string(n)`, `from_char_code(c)`, `char_code_at(s, i)` |
| `core::vec` | Dynamic growing typed sequential array container | `vec_new()`, `vec_push(v, x)`, `vec_get(v, i)`, `vec_len(v)`, `vec_pop(v)`, `vec_get_opt(v, i)`, `vec_pop_opt(v)` |
| `core::hashmap` | Key-value associative hash table | `hashmap_new()`, `hashmap_insert(m, k, v)`, `hashmap_get(m, k)`, `hashmap_contains(m, k)`, `hashmap_get_opt(m, k)` |
| `core::process` | Sandboxed external process invocation and query | `process_spawn(cmd, args)`, `process_run(cmd, args)`, `process_is_sandboxed()` |
| `core::math` | Arithmetic, rounding, integer and floating-point primitives | `abs(x)`, `min(a, b)`, `max(a, b)`, `sqrt(x)` |
| `core::arena` | Region-based linear memory allocator | `arena_alloc(size)`, `arena_reset()` |

### 3.2 Dual-Track API Guarantee

Per `BKR-SPEC-ERROR-001` and `BKR-SPEC-SAFE-001`, all I/O, collection lookup, and parsing operations strictly adhere to the Dual-Track error handling model:
1. **Unchecked / Fail-Stop Builtins**: Provide zero-overhead operations (`read_file`, `vec_get`, `hashmap_get`, `parse_int`) aborting on invariant violation (`exit 101`).
2. **Checked / Recoverable Builtins**: Return explicit `Option<T>` or `Result<T, E>` sum types (`vec_get_opt`, `hashmap_get_opt`, `read_file_result`, `parse_int_result`) for graceful error handling.

### 3.3 Standard Library Catalog Schema (`bunker.stdlib_doc.v1`)

```json
{
  "schema": "bunker.stdlib_doc.v1",
  "modules": [
    {
      "name": "core::io",
      "summary": "Native filesystem operations with dual fail-stop and Result error paths",
      "functions": [
        {
          "name": "read_file_result",
          "signature": "fn read_file_result(path: str) -> Result<str, str>",
          "doc": "Reads the entire content of a file into a string. Returns Result.Err if the file does not exist or cannot be read."
        }
      ]
    }
  ],
  "total_modules": 7,
  "total_functions": 27
}
```

---

## 4. Tooling & Driver Integration

- **Capability Reflection**: `self_host_capability_json()` in `self-host/modules/driver.bkr` exposes:
  ```json
  "package_registry": true,
  "stdlib_documentation": true
  ```
- **CLI Commands**:
  - `bunker pkg search <name>`: Queries the package registry index.
  - `bunker doc --stdlib`: Exports the machine-readable standard library API catalog.
- **Self-Host Verification**: Zero diagnostics under `bunker self-host-check`.
