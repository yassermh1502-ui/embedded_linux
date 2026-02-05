#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_even.sh
# Description: Compile even.c and run automated tests
# ---------------------------------------------------------

SRC="even.c"
BIN="./even"

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
echo ">>> gcc -Wall -Wextra $SRC -o even"
gcc -Wall -Wextra "$SRC" -o even
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests with single numbers
# ---------------------------------------------------------
assert "$BIN 4" "Yes, even"
assert "$BIN 5" "No, odd"

# ---------------------------------------------------------
# Tests with range
# ---------------------------------------------------------
assert "$BIN -r 1 10" "2,4,6,8,10"
assert "$BIN -r 3 8" "4,6,8"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./even NUMBER
  ./even -r START END
Options:
  -h, --help   Show this help
  -r, --range  List evens in range START to END"

# ---------------------------------------------------------
# Test error: missing numbers
# ---------------------------------------------------------
assert "$BIN" "Error: missing number"
assert "$BIN -r 5" "Error: missing range numbers"

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
