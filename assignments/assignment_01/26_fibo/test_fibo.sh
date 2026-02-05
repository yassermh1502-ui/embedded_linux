#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_fibo.sh
# Description: Compile fibo.c and run automated tests
# ---------------------------------------------------------

SRC="fibo.c"
BIN="./fibo"

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
echo ">>> gcc -Wall -Wextra $SRC -o fibo"
gcc -Wall -Wextra "$SRC" -o fibo
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests with number of terms
# ---------------------------------------------------------
assert "$BIN 7" "0 1 1 2 3 5 8"
assert "$BIN -n 10" "0 1 1 2 3 5 8 13 21 34"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./fibo N
  ./fibo -n N
Options:
  -h, --help   Show this help
  -n N         Number of terms"

# ---------------------------------------------------------
# Test error: missing number
# ---------------------------------------------------------
assert "$BIN" "Error: missing or invalid number of terms"
assert "$BIN -n 0" "Error: missing or invalid number of terms"

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
