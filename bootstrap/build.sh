#!/usr/bin/env bash
set -euo pipefail

# Bunker Bootstrap Compiler Build Script
# Compiles the self-hosted Bunker compiler directly from portable C11 source.
# Zero dependencies: requires only a standard C compiler (gcc, clang, or cc).
# No Rust, Cargo, or external package manager needed.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

CC="${CC:-cc}"
CFLAGS="${CFLAGS:--std=c11 -O2}"
OUTPUT="${1:-$ROOT_DIR/bkrc}"

echo "=== Building Bunker Compiler (bkrc) from Bootstrap C Seed ==="
echo "Compiler: $CC"
echo "Flags:    $CFLAGS"
echo "Target:   $OUTPUT"

# Verify checksums if sha256sum is available
if command -v sha256sum >/dev/null 2>&1; then
    echo "Verifying bootstrap checksums..."
    (cd "$SCRIPT_DIR" && sha256sum -c SHA256SUMS --status || sha256sum -c SHA256SUMS)
fi

# Compile Stage 1 bkrc
"$CC" $CFLAGS "$SCRIPT_DIR/bkrc-stage1.c" -o "$OUTPUT"

echo "=== Build Successful! ==="
echo "Bunker compiler binary created at: $OUTPUT"
echo "Usage: $OUTPUT <input.bkr> -o <output.c>"
