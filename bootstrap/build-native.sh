#!/usr/bin/env bash
set -euo pipefail

# Bunker native bootstrap (Linux x86-64).
# Builds bkrc from the checked-in bkrc binary seed using only Bunker itself:
# no C compiler, no linker, no libc. The seed compiles self-host/bkrc.bkr with the
# native x86-64 backend, and the result rebuilds itself to prove a fixpoint.
#
# Usage: bash bootstrap/build-native.sh [output]   (default: ./bkrc)

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
SEED="$SCRIPT_DIR/bkrc-linux-x86_64"
OUTPUT="${1:-$ROOT_DIR/bkrc}"

cd "$ROOT_DIR"

echo "=== Building Bunker Compiler (bkrc) from the native binary seed ==="
if command -v sha256sum >/dev/null 2>&1; then
    echo "Verifying seed checksum..."
    (cd "$SCRIPT_DIR" && sha256sum -c SHA256SUMS.native)
fi

STAGE1="$(mktemp)"
trap 'rm -f "$STAGE1"' EXIT

# Stage 1: the seed builds the current compiler sources.
"$SEED" native self-host/bkrc.bkr -o "$STAGE1"
# Stage 2: the freshly built compiler builds itself; both must be identical.
"$STAGE1" native self-host/bkrc.bkr -o "$OUTPUT"
if ! cmp -s "$STAGE1" "$OUTPUT"; then
    echo "Error: stage 1 and stage 2 compilers differ (no fixpoint)" >&2
    exit 1
fi

echo "=== Build Successful! (fixpoint verified) ==="
echo "Bunker compiler binary created at: $OUTPUT"
