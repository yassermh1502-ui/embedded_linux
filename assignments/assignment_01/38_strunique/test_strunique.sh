#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strunique.sh
# Description: Compile strunique.c and run automated tests
# ---------------------------------------------------------

SRC="strunique.c"
BIN="./strunique"

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
echo ">>> gcc -Wall -Wextra $SRC -o strunique"
gcc -Wall -Wextra "$SRC" -o strunique
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
# Count unique characters
assert "$BIN hello" "4 unique chars"

# List unique characters
assert "$BIN hello -l" "Unique characters: h, e, l, o"

# Help
assert "$BIN -h" $'Usage:\n  ./strunique STRING [OPTIONS]\nOptions:\n  -h          Show this help\n  -l          List unique characters'

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
