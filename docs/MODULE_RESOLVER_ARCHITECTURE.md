# BKR-SPEC-MOD-001: Module Resolution, Cycle Path Detection, and Name Scoping Architecture

- **Status**: CANONICAL / LOCKED (2026-10-27)
- **Document ID**: `BKR-SPEC-MOD-001`
- **Track**: Compiler Frontend (`CF`)
- **Items Addressed**:
  - `CF-008` (P0): Name resolver in Bunker — Multi-scope resolution, lexical visibility boundaries (`pub` vs private), cross-file definition origins, and structured repair hints.
  - `CF-009` (P0): Module resolver — Normalized relative import paths, cycle-safe traversal, exact cycle path reporting, and duplicate suppression.
- **Conformance Test Fixtures**:
  - `tests/211_multifile_modules.bkr` (multi-file compilation validation)
  - `tests/212_import_cycle_BAD.bkr` (cycle detection validation)
  - `tests/213_import_private_symbol_BAD.bkr` (visibility boundary validation)
  - `tests/256_module_resolver_cycle_paths.bkr` (returns 42)
  - `tests/257_name_resolver_visibility_cross_file.bkr` (returns 42)

---

## 1. Executive Summary & Epistemic Foundations

In modern multi-file programming languages, modularity requires two cooperating compiler subsystems:
1. **Module Resolver (`CF-009`)**: Responsible for file discovery, relative path canonicalization, dependency graph construction, duplicate import suppression, and cycle detection.
2. **Name Resolver (`CF-008`)**: Responsible for mapping textual identifiers in AST expressions and types to specific declaration sites across local, block, function, kernel, and foreign module scopes, while strictly enforcing visibility boundaries (`pub` export vs private encapsulation).

```
+---------------------------------------------------------------------------------------------------+
|                        Bunker Module & Name Resolution Architecture (BKR-SPEC-MOD-001)             |
+---------------------------------------------------------------------------------------------------+
|                                                                                                   |
|  Source Files:                                                                                    |
|  main.bkr ---> import "modules/math.bkr" ---> import "modules/utils.bkr"                          |
|                                                                                                   |
|  +---------------------------------------------------------------------------------------------+  |
|  |                             Module Resolver (self-host/modules/driver.bkr)                  |  |
|  |  - Path Policy: normalized forward slashes, relative, no '..', no leading './', no '//'      |  |
|  |  - Active Importer Stack: [ main.bkr, modules/math.bkr ]                                    |  |
|  |  - Cycle Detection: if next in stack -> emit E0702 (BKR_SELF_IMPORT_CYCLE) with exact chain   |  |
|  |  - Duplicate Suppression: if next in loaded_set -> mark duplicate, skip re-expansion         |  |
|  |  - Emits: BUNKER_IMPORT_GRAPH_JSON (bunker.self_host.import_graph.v1)                         |  |
|  +---------------------------------------------------------------------------------------------+  |
|                                                |                                                  |
|                                                v                                                  |
|  +---------------------------------------------------------------------------------------------+  |
|  |                              Name Resolver (self-host/modules/resolver.bkr)                 |  |
|  |  - Lexical Scopes: Local / Pattern -> Block -> Function -> Kernel -> Foreign Module          |  |
|  |  - Visibility Boundary: check is_pub when target_kernel != current_kernel                    |  |
|  |    * If !is_pub -> emit E0601 (BKR_SELF_VISIBILITY): "Symbol '...' is private"              |  |
|  |  - Duplicate Detection: emit BKR_SELF_DUPLICATE_SYMBOL with related declaration span         |  |
|  |  - Unresolved Reference: emit BKR_SELF_UNRESOLVED_SYMBOL with related declarations and hint   |  |
|  |  - Emits: BUNKER_RESOLVER_JSON (bunker.resolver.v1)                                         |  |
|  +---------------------------------------------------------------------------------------------+  |
|                                                                                                   |
+---------------------------------------------------------------------------------------------------+
```

---

## 2. Module Resolution & Path Policy (`CF-009`)

### 2.1 Normalized Relative Path Policy
All Bunker module import declarations must strictly obey the forward-slash relative path policy:
```bkr
import "modules/math_utils.bkr";
import "helpers/format.bkr";
```

The compiler rejects invalid paths at parse/resolution time:
- **Absolute Paths**: Prohibited (`/usr/lib/math.bkr` or `C:\code\math.bkr`).
- **Backslashes**: Prohibited (`modules\math.bkr`). All paths must use forward slashes `/`.
- **Parent Directory Traversal**: Prohibited (`../sibling/math.bkr` or `./../math.bkr`). Imports cannot escape the project hierarchy.
- **Leading `./`**: Prohibited (`./math.bkr` -> must be `math.bkr`).
- **Trailing Slashes & Empty Segments**: Prohibited (`modules//math.bkr` or `modules/math.bkr/`).

### 2.2 Exact Cycle Path Detection
During recursive module expansion, the compiler maintains an **importer stack** of active file paths being traversed. When an imported file is encountered:
1. **If on the Active Importer Stack**: An import cycle exists. The compiler halts traversal along this edge and formats the exact cycle chain:
   ```
   Cyclic dependency detected: main.bkr -> modules/cycle_a.bkr -> modules/cycle_b.bkr -> modules/cycle_a.bkr
   ```
   Diagnostic details:
   - `error_code`: `E0702`
   - `rule_id`: `BKR_SELF_IMPORT_CYCLE`
   - `severity`: `error`
   - `phase`: `import`
   - `category`: `module`
   - `repair_hint`: Extract shared types or functions into an independent leaf module.
2. **If in Loaded Files (but not on stack)**: A diamond dependency or shared utility module has already been imported. The edge is marked `duplicate` and skipped safely without re-parsing.
3. **If not yet seen**: Added to active stack, recursively expanded, then popped upon completion.

### 2.3 Import Graph JSON Schema (`bunker.self_host.import_graph.v1`)
```json
{
  "schema_version": "bunker.self_host.import_graph.v1",
  "root_base_dir": "string",
  "path_policy": "normalized_relative_forward_slash",
  "base_directory_resolution": true,
  "recursive_expansion": true,
  "duplicate_suppression": true,
  "cycle_safe_expansion": true,
  "unique_import_count": 3,
  "edge_count": 4,
  "ok_edge_count": 3,
  "missing_edge_count": 0,
  "invalid_edge_count": 0,
  "duplicate_edge_count": 1,
  "cycle_edge_count": 0,
  "imports": [ "modules/math.bkr", "modules/common.bkr" ],
  "edges": [
    {
      "from_base": "src",
      "requested": "modules/math.bkr",
      "resolved": "src/modules/math.bkr",
      "status": "ok"
    }
  ],
  "has_duplicate_or_cycle_import": true,
  "has_invalid_import": false,
  "has_missing_import": false
}
```

---

## 3. Name Resolution & Lexical Scopes (`CF-008`)

### 3.1 Lexical Scope Hierarchy
Bunker resolves identifiers using a strict innermost-first lexical scope ladder:
1. **Local Pattern Scope**: Pattern binding variables (e.g. `match x { Status.Active(val) => ... }`).
2. **Block / Statement Scope**: Variables introduced by `let` and `let mut` statements within `{ ... }` blocks.
3. **Function Scope**: Function parameters declared in `fn name(a: i64, b: i64)`.
4. **Kernel Global Scope**: Items declared at the root of the enclosing kernel (`fn`, `struct`, `const`, `enum`, `type`).
5. **Foreign Kernel / Module Scope**: Items qualified with a kernel or module prefix (`MathLib::add(x, y)`).

### 3.2 Visibility Boundaries (`pub` vs Private)
Bunker enforces module and kernel encapsulation:
- Items declared with `pub` (e.g. `pub fn add(...)`, `pub struct Point`, `pub const PI: f64`) are exported and accessible across kernels and imported files.
- Items declared without `pub` are **private** to their declaring kernel.
- Accessing a private item from a different kernel emits a structured visibility diagnostic:
  ```json
  {
    "phase": "resolver",
    "kind": "unresolved_reference",
    "rule_id": "BKR_SELF_VISIBILITY",
    "error_code": "E0601",
    "severity": "error",
    "message": "Symbol 'MathLib::secret_internal' is private and cannot be accessed from outside its module in main",
    "location": {
      "file": "src/main.bkr",
      "line": 42,
      "column": 18
    },
    "ai_prompt_hint": "Declare the symbol 'pub fn secret_internal' in MathLib or call an exported public function",
    "related": [
      {
        "location": {
          "file": "src/modules/math_lib.bkr",
          "line": 15,
          "column": 5
        },
        "message": "Private definition of 'secret_internal' was declared here"
      }
    ]
  }
  ```

### 3.3 Duplicate Declaration Detection
Within any single scope, re-declaring an identifier produces `BKR_SELF_DUPLICATE_SYMBOL` (`E0202` / `E0210`). The diagnostic attaches a `related_declarations` entry pointing to the original declaration.

### 3.4 Cross-File Definition Origins
When resolving symbols across imported modules:
- The symbol table tracks the originating file path, byte span, line/column coordinates, and visibility status for each symbol.
- Unresolved symbol errors list fuzzy matches from known declarations within the same or imported kernels, accompanied by prompt-ready repair hints.

---

## 4. Conformance Matrix

| Capability | Module File | Verification Fixture | Status |
|---|---|---|---|
| Normalized Relative Path Policy | `self-host/modules/driver.bkr` | `tests/214_import_invalid_path_BAD.bkr` | Verified |
| Missing Module Detection | `self-host/modules/driver.bkr` | `tests/215_import_missing_module_BAD.bkr` | Verified |
| Exact Cycle Path Detection | `self-host/modules/driver.bkr` | `tests/212_import_cycle_BAD.bkr`, `tests/256_module_resolver_cycle_paths.bkr` | Verified |
| Multi-file Compilation & Deduplication | `self-host/modules/driver.bkr` | `tests/211_multifile_modules.bkr` | Verified |
| Scoped Symbol Resolution | `self-host/modules/resolver.bkr` | `tests/257_name_resolver_visibility_cross_file.bkr` | Verified |
| Visibility Boundaries (`pub` check) | `self-host/modules/resolver.bkr` | `tests/213_import_private_symbol_BAD.bkr`, `tests/257_name_resolver_visibility_cross_file.bkr` | Verified |
| Cross-File Origin Spans | `self-host/modules/resolver.bkr` | `tests/257_name_resolver_visibility_cross_file.bkr` | Verified |
