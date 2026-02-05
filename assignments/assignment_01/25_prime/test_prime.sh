#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_prime.sh
# Description: Compile prime.c and run automated tests
# ---------------------------------------------------------

SRC="prime.c"
BIN="./prime"

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
echo ">>> gcc -Wall -Wextra $SRC -o prime -lm"
gcc -Wall -Wextra "$SRC" -o prime -lm
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests with single numbers
# ---------------------------------------------------------
assert "$BIN 7" "Yes, prime"
assert "$BIN 8" "Not prime"
assert "$BIN 2" "Yes, prime"
assert "$BIN 1" "Not prime"

# ---------------------------------------------------------
# Tests with range
# ---------------------------------------------------------
assert "$BIN -r 1 10" "2,3,5,7"
assert "$BIN -r 10 20" "11,13,17,19"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./prime NUMBER
  ./prime -r START END
Options:
  -h, --help   Show this help
  -r, --range  List primes in range START to END"

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
