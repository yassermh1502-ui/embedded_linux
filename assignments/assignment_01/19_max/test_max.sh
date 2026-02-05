#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_max.sh
# Description: Compile max.c and run automated tests
# ---------------------------------------------------------

SRC="max.c"
BIN="./max"

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
echo ">>> gcc -Wall -Wextra $SRC -o max"
gcc -Wall -Wextra "$SRC" -o max
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests with command-line numbers
# ---------------------------------------------------------
assert "$BIN 5 10 3 8" "10"
assert "$BIN -h" "Usage:
  ./max [NUMBERS...]
  ./max -f FILE
Options:
  -h, --help   Show this help
  -f FILE      Read numbers from file"

# ---------------------------------------------------------
# Tests with file input
# ---------------------------------------------------------
echo -e "1\n2\n3\n4\n5" > numbers.txt
assert "$BIN -f numbers.txt" "5"
rm numbers.txt

# ---------------------------------------------------------
# Test error: missing numbers
# ---------------------------------------------------------
assert "$BIN" "Error: missing numbers"

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
