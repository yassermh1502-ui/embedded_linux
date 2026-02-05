#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_digits.sh
# Description: Compile digits.c and run automated tests
# ---------------------------------------------------------

SRC="digits.c"
BIN="./digits"

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
echo ">>> gcc -Wall -Wextra $SRC -o digits"
gcc -Wall -Wextra "$SRC" -o digits
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN 12345" "5 digits"
assert "$BIN 123abc456" "6 digits"
assert "$BIN -s 12345" "15"
assert "$BIN -s 123abc456" "21"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./digits NUMBER
  ./digits -s NUMBER
Options:
  -h, --help   Show this help
  -s, --sum    Sum of digits"

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
