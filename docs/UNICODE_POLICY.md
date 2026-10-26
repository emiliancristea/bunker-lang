# BKR-SPEC-STR-002: Bunker Unicode Policy and String UTF-8 vs Byte Semantics

- **Status**: CANONICAL / LOCKED (2026-10-26)
- **Document ID**: `BKR-SPEC-STR-002`
- **Track**: Runtime & Standard Library (`R`), Strings & Data Model
- **Items Addressed**:
  - `R-015`: Unicode policy (UTF-8 encoding guarantees, scalar value semantics, byte buffer separation, string indexing rules)
  - `D-011`: String escape sequences (`\n`, `\r`, `\t`, `\\`, `\"`, `\'`, `\0`, `\xHH`, `\u{HHHH}`)
  - `D-012`: Efficient byte buffers (`bytes_new`, `bytes_len`, `bytes_get`, `bytes_set`, `bytes_push`, `bytes_from_str`, `bytes_to_str`)
  - `R-001`: Complete string library (`strlen`, `len`, `char_at`, `char_code_at`, `from_char_code`, `substring`, `contains`, `starts_with`, `ends_with`, `trim`, `str_index_of`, `str_replace`, `str_split`, `str_to_upper`, `str_to_lower`, `str_repeat`)
- **Conformance Test Fixtures**:
  - `tests/205_string_escapes_and_bytes.bkr` (String escapes, byte buffers, basic conversions)
  - `tests/206_invalid_escape_BAD.bkr` (Rejection of unrecognized escape sequences)
  - `tests/207_invalid_char_escape_BAD.bkr` (Rejection of malformed char escapes)
  - `tests/241_unicode_byte_semantics.bkr` (1-, 2-, 3-, and 4-byte UTF-8, byte indexing, slicing, buffer roundtrips)
  - `tests/242_unicode_surrogate_BAD.bkr` (Rejection of surrogate codepoints `\u{D800}`)

---

## 1. Executive Summary & Epistemic Foundations

In modern systems programming languages, string representations represent a classic design trap:
1. **The $O(N)$ Codepoint Indexing Disaster**: Languages that model strings as "arrays of characters" (e.g. Python 3's variable-width FSR or naive codepoint indexing) incur $O(N)$ traversal overhead for index lookups, or allocate excessive memory (up to 4 bytes per character for pure ASCII text).
2. **The UTF-16 Historical Debt**: Systems like Java, JavaScript, and Windows Win32 adopt UTF-16, creating surrogate-pair bugs, surrogate truncation vulnerabilities, and constant transcoding overhead when communicating with network sockets and POSIX APIs.
3. **The Buffer vs String Conflation**: C and early C++ treat strings simply as null-terminated `char*` arrays without validating UTF-8 invariants, leading to buffer overruns, invalid multi-byte sequence splits, and security vulnerabilities.

### The Bunker Principle: Provable UTF-8 Invariant with $O(1)$ Byte Semantics
Bunker formalizes a clear, robust architecture:
1. **Provable UTF-8 Invariant**: The string primitive type `str` is an immutable, valid UTF-8 byte sequence. The compiler and runtime guarantee that no malformed UTF-8 sequence can be constructed as a `str`.
2. **$O(1)$ Byte-Level Indexing**: All indexing (`char_code_at`), length operations (`len`), and slicing operations (`substring`) operate strictly on **byte offsets**. This ensures deterministic $O(1)$ performance with zero heap allocations, zero transcoding overhead, and zero hidden traversals.
3. **First-Class Scalar Value Escapes (`\u{HHHH}`)**: Source code supports full Unicode scalar value escapes (`\u{0}` through `\u{10FFFF}`). Surrogate code points (`0xD800..=0xDFFF`) and out-of-range values (> `0x10FFFF`) are rejected at compile time.
4. **Explicit Separation of Binary Streams**: Raw binary data is decoupled from text into the `bytes` buffer system (`bytes_new`, `bytes_get`, `bytes_set`, `bytes_push`), preventing accidental text-corruption or binary-as-string bugs.

---

## 2. Memory Layout & Storage Representation

Bunker strings are allocated in the active arena watermark and carry a dual representation optimized for both Cranelift JIT SSA execution and C FFI compatibility:

### 2.1 JIT Memory Layout
In Cranelift JIT runtime:
```text
+-----------------------+---------------------------------------+------+
| Length: i64 (8 bytes) | UTF-8 Payload: [u8; Length]           | 0x00 |
+-----------------------+---------------------------------------+------+
^
|-- Pointer (i64 handle)
```
- A 64-bit length prefix precedes the byte payload, enabling $O(1)$ bounds checking and slice extraction without calling `strlen()`.
- An explicit null terminator (`0x00`) follows the payload, allowing zero-copy passing to native C functions.

### 2.2 C Runtime Memory Layout
In the self-host C runtime (`self-host/runtime.h`):
- Strings are represented as `bkr_str` (`const char*`).
- String operations leverage arena allocation (`bkr_arena_alloc`) and cached length memoization (`g_bkr_cached_str`, `g_bkr_cached_len`), providing $O(1)$ repeated length queries.
- String literals are pooled as immutable static read-only data sections.

---

## 3. Byte Semantics vs Codepoint Semantics

A fundamental principle of Bunker is that **length and offset metrics in `str` are byte-denominated**:

| Operation | Signature | Semantics | Complexity |
|---|---|---|:---:|
| `len(s)` | `(s: str) -> i64` | Total byte count of the UTF-8 payload | $O(1)$ |
| `char_code_at(s, i)` | `(s: str, i: i64) -> i64` | Unsigned byte value ($0..255$) at byte offset `i` | $O(1)$ |
| `char_at(s, i)` | `(s: str, i: i64) -> str` | Single-byte substring at byte offset `i` | $O(1)$ |
| `substring(s, start, end)` | `(s: str, start: i64, end: i64) -> str` | Substring spanning byte range `[start, end)` | $O(\text{end} - \text{start})$ |
| `str_index_of(s, needle)` | `(s: str, needle: str) -> i64` | Starting byte offset of `needle` within `s` | $O(N \cdot M)$ |

### 3.1 Multi-Byte UTF-8 Encoding Table

In accordance with RFC 3629 / Unicode Standard, characters in Bunker encode across 1 to 4 bytes:

| Unicode Category | Codepoint Range | UTF-8 Byte Sequence | Bunker `len(s)` | Example |
|---|---|---|:---:|---|
| **1-Byte (ASCII)** | `U+0000` .. `U+007F` | `0xxxxxxx` | `1` | `'A'` (65 / `0x41`) |
| **2-Byte (Latin/Greek)** | `U+0080` .. `U+07FF` | `110xxxxx 10xxxxxx` | `2` | `'é'` (`\u{00E9}`, `[195, 169]`) |
| **3-Byte (Symbols/CJK)** | `U+0800` .. `U+FFFF` | `1110xxxx 10xxxxxx 10xxxxxx` | `3` | `'€'` (`\u{20AC}`, `[226, 130, 172]`) |
| **4-Byte (Astral/Emoji)** | `U+10000` .. `U+10FFFF`| `11110xxx 10xxxxxx 10xxxxxx 10xxxxxx` | `4` | `'\u{1F980}'` (`[240, 159, 166, 128]`) |

### 3.2 Conformance Proof: Multi-Byte Invariants
When evaluating composite strings:
```bunker
let greeting: str = "Hi \u{1F980}!";
```
- `'H'` = 1 byte (offset 0)
- `'i'` = 1 byte (offset 1)
- `' '` = 1 byte (offset 2)
- `'\u{1F980}'` = 4 bytes (offsets 3, 4, 5, 6)
- `'!'` = 1 byte (offset 7)
- `len(greeting)` evaluates to **8** (not 5 characters).
- `str_index_of(greeting, "!")` returns **7** (exact byte offset).

---

## 4. Unicode Escape Sequences & Validation Rules

Bunker supports a complete, hygienic escape sequence grammar:

| Escape Sequence | Description | Valid Range | Example |
|---|---|---|---|
| `\n` | Newline (Line Feed) | ASCII 10 (`0x0A`) | `"line1\nline2"` |
| `\r` | Carriage Return | ASCII 13 (`0x0D`) | `"line1\rline2"` |
| `\t` | Horizontal Tab | ASCII 9 (`0x09`) | `"col1\tcol2"` |
| `\\` | Literal Backslash | ASCII 92 (`0x5C`) | `"path\\to\\file"` |
| `\"` | Double Quote | ASCII 34 (`0x22`) | `"quote: \"hello\""` |
| `\'` | Single Quote | ASCII 39 (`0x27`) | `'\'single\''` |
| `\0` | Null Byte | ASCII 0 (`0x00`) | `"zero\0byte"` |
| `\xHH` | 8-bit Hex Byte | `0x00` .. `0xFF` | `"\x41"` ('A') |
| `\u{HHHH}` | Unicode Scalar Value | `0x0` .. `0x10FFFF` (excluding surrogates) | `"\u{20AC}"` ('€') |

### 4.1 Strict Rejection of Invalid Unicode
The compiler AST builder (`bunker-cli/src/ast_builder.rs`) strictly validates `\u{...}` literals:
1. **Surrogate Code Points**: Codepoints in the surrogate range `0xD800` through `0xDFFF` are permanently prohibited because they cannot form valid UTF-8 scalar values.
   ```bunker
   let s = "\u{D800}"; // COMPILE ERROR: [E0101] Invalid Unicode scalar value: 0xD800
   ```
2. **Out of Range Codepoints**: Any value exceeding `0x10FFFF` is rejected:
   ```bunker
   let s = "\u{110000}"; // COMPILE ERROR: [E0101] Invalid Unicode scalar value: 0x110000
   ```
3. **Hex Format**: Empty brackets `\u{}` or malformed hex characters `\u{XYZ}` are rejected at parse time.

---

## 5. The `bytes` Buffer System (`bytes_*`)

For arbitrary binary streams, network packets, file I/O, and image decoders, Bunker provides mutable byte buffers that decouple binary memory from UTF-8 strings:

```bunker
// 1. Allocate arena-backed byte buffer with initial capacity
let buf: i64 = bytes_new(16);

// 2. Push raw byte values (0..255)
bytes_push(buf, 226); // 0xE2
bytes_push(buf, 130); // 0x82
bytes_push(buf, 172); // 0xAC

// 3. Query length and access elements
let sz: i64 = bytes_len(buf);          // 3
let first: i32 = bytes_get(buf, 0);     // 226

// 4. In-place modification
bytes_set(buf, 0, 226);

// 5. Convert to valid UTF-8 str
let s: str = bytes_to_str(buf);         // "\u{20AC}" (Euro sign)

// 6. Convert str back to raw byte buffer
let b: i64 = bytes_from_str("café");    // 5 bytes
```

### 5.1 Zero-Copy Views via Slices
Byte buffers interoperate seamlessly with Bunker's slice subsystem:
- `bytes_as_slice(buf: i64) -> i64`: Produces a read-only `Slice<i32>` view over the buffer's contents.
- `bytes_slice(buf: i64, start: i64, len: i64) -> i64`: Produces a sub-slice view without copying bytes.

---

## 6. ASCII Case & Search Operations

Bunker standard library provides case-conversion and search functions that respect UTF-8 boundaries:
- `str_to_upper(s: str) -> str`: Transforms ASCII letters `a-z` to `A-Z` while preserving multi-byte UTF-8 sequences without corruption.
- `str_to_lower(s: str) -> str`: Transforms ASCII letters `A-Z` to `a-z` while preserving multi-byte UTF-8 sequences.
- `contains(haystack: str, needle: str) -> bool`: Deterministic substring containment.
- `starts_with(s: str, prefix: str) -> bool`: Byte-prefix comparison.
- `ends_with(s: str, suffix: str) -> bool`: Byte-suffix comparison.
- `trim(s: str) -> str`: Strips leading and trailing ASCII whitespace (`' '`, `'\t'`, `'\r'`, `'\n'`).

---

## 7. Dual-Compiler Parity

The Unicode and string semantics are identical across both compilers:

| Feature / Metric | `bunker-cli` (Rust JIT) | `bkrc.bkr` (Self-Host C Codegen) |
|---|---|---|
| **String Storage** | Length-prefixed 64-bit + null-terminated | Length-memoized `bkr_str` (`const char*`) |
| **Indexing Complexity** | $O(1)$ byte indexing via `char_code_at` | $O(1)$ byte indexing via `char_code_at` |
| **`len(s)` Calculation** | Exact UTF-8 byte length | Exact UTF-8 byte length (`strlen` memoized) |
| **Unicode Escapes** | Validates scalar values, rejects surrogates | Unescaped at AST/lexer phase into UTF-8 |
| **Byte Buffer System** | `bunker_bytes_*` with arena reallocation | `bkr_byte_buf_t` with arena reallocation |
| **Roundtrip Determinism**| `bytes_to_str(bytes_from_str(s)) == s` | `bytes_to_str(bytes_from_str(s)) == s` |

---

## 8. Conformance & Verification Audit

Milestone `Q-287` closes `R-015` based on concrete test evidence:
- `tests/241_unicode_byte_semantics.bkr`: Comprehensive positive test verifying 1-byte, 2-byte, 3-byte, and 4-byte UTF-8 encoding, byte indexing, slicing, buffer roundtrips, case transformation, and returning exit code 42.
- `tests/242_unicode_surrogate_BAD.bkr`: Negative rejection test proving compile-time rejection of invalid Unicode scalar values (`0xD800`).
- `tests/205_string_escapes_and_bytes.bkr`: Positive test verifying byte buffer operations and escape sequences.
- `tests/206_invalid_escape_BAD.bkr`: Negative rejection test proving rejection of invalid escape characters.

Advances Track `R` (Runtime & Standard Library) and promotes `R-015` from `TODO` to `DONE`. Total ecosystem pure completion advances to **103 / 168 pure DONE (61.3%)**.
