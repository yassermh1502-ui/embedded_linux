#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strtonum.sh
# Description: Compile strtonum.c and run automated tests
# ---------------------------------------------------------

SRC="strtonum.c"
BIN="./strtonum"

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
echo ">>> gcc -Wall -Wextra $SRC -o strtonum"
gcc -Wall -Wextra "$SRC" -o strtonum
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN 'abc123xyz456'" "123, 456"
assert "$BIN -s 'abc123xyz456'" "579"
assert "$BIN 'price: $99.99'" "99.99"
assert "$BIN -s 'price: $99.99'" "99.99"
assert "$BIN -h" "Usage:
  ./strtonum STRING
  ./strtonum -s STRING
Options:
  -h, --help   Show this help
  -s, --sum    Sum extracted numbers"

# ---------------------------------------------------------
# Test error: missing string
# ---------------------------------------------------------
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
