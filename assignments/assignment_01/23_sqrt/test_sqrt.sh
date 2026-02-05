#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_sqrt.sh
# Description: Compile sqrt.c and run automated tests
# ---------------------------------------------------------

SRC="sqrt.c"
BIN="./sqrt"

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
echo ">>> gcc -Wall -Wextra $SRC -o sqrt"
gcc -Wall -Wextra "$SRC" -o sqrt -lm
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests with positional arguments
# ---------------------------------------------------------
assert "$BIN 16" "4"
assert "$BIN 25" "5"

# ---------------------------------------------------------
# Tests with precision flag
# ---------------------------------------------------------
assert "$BIN -p 2 2" "1.41"
assert "$BIN -p 3 10" "3.162"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./sqrt NUMBER
  ./sqrt -p PRECISION NUMBER
Options:
  -h, --help      Show this help
  -p, --precision Decimal precision"

# ---------------------------------------------------------
# Test error: missing or negative numbers
# ---------------------------------------------------------
assert "$BIN" "Error: missing or invalid number"
assert "$BIN -p 2" "Error: missing or invalid number"

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
