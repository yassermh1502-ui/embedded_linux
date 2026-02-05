#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strduplicate.sh
# Description: Compile strduplicate.c and run automated tests
# ---------------------------------------------------------

SRC="strduplicate.c"
BIN="./strduplicate"

PASS=0
FAIL=0

# ---------------------------------------------------------
# Helper: run command + assert output
# ---------------------------------------------------------
assert() {
    CMD="$1"
    EXPECTED="$2"

    echo
    echo ">>> $CMD"
    OUTPUT=$(eval "$CMD" 2>&1)

    if [ "$OUTPUT" = "$EXPECTED" ]; then
        echo "PASS   Expected: $EXPECTED == OUTPUT: $OUTPUT"
        ((PASS++))
    else
        echo "FAIL   Expected: $EXPECTED != OUTPUT: $OUTPUT"
        ((FAIL++))
    fi
}

# ---------------------------------------------------------
# Compile step
# ---------------------------------------------------------
echo ">>> gcc -Wall -Wextra $SRC -o strduplicate"
gcc -Wall -Wextra "$SRC" -o strduplicate
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
# Default: show count
assert "$BIN hello" $'l appears 2 times'

# List all duplicates
assert "$BIN hello -a" "Duplicate characters: l"

# Multiple duplicates
assert "$BIN mississippi -a" "Duplicate characters: i, s, p"

# Help
assert "$BIN -h" $'Usage:\n  ./strduplicate STRING [OPTIONS]\nOptions:\n  -h          Show this help\n  -a          Show all duplicates'

# Error: missing string
assert "$BIN" "Error: missing STRING"

# ---------------------------------------------------------
# Summary
# ---------------------------------------------------------
echo
echo "======================================"
echo "Tests passed: $PASS"
echo "Tests failed: $FAIL"
echo "======================================"

if [ $FAIL -ne 0 ]; then
    exit 1
fi
