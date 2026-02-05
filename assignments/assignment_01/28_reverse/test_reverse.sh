#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_reverse.sh
# Description: Compile reverse.c and run automated tests
# ---------------------------------------------------------

SRC="reverse.c"
BIN="./reverse"

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
echo ">>> gcc -Wall -Wextra $SRC -o reverse"
gcc -Wall -Wextra "$SRC" -o reverse
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN 12345" "54321"
assert "$BIN 12321" "12321"
assert "$BIN -c 12321" "Yes"
assert "$BIN -c 12345" "No"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./reverse NUMBER
  ./reverse -c NUMBER
Options:
  -h, --help   Show this help
  -c, --check  Check if palindrome"

# ---------------------------------------------------------
# Test error: missing number
# ---------------------------------------------------------
assert "$BIN" "Error: missing number"

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
