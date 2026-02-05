#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_caesar.sh
# Description: Compile caesar.c and run automated tests
# ---------------------------------------------------------

SRC="caesar.c"
BIN="./caesar"

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
echo ">>> gcc -Wall -Wextra $SRC -o caesar"
gcc -Wall -Wextra "$SRC" -o caesar
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN 'hello' -k 3" "khoor"
assert "$BIN 'khoor' -k -3" "hello"
assert "$BIN 'ABC xyz' -k 2" "CDE zab"
assert "$BIN -h" "Usage:
  ./caesar STRING -k N
Options:
  -h, --help   Show this help
  -k N         Shift key (positive or negative)"

# ---------------------------------------------------------
# Test error: missing string
# ---------------------------------------------------------
assert "$BIN -k 3" "Error: missing STRING"

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
