#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_factorial.sh
# Description: Compile factorial.c and run automated tests
# ---------------------------------------------------------

SRC="factorial.c"
BIN="./factorial"

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
echo ">>> gcc -Wall -Wextra $SRC -o factorial"
gcc -Wall -Wextra "$SRC" -o factorial
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests with numbers
# ---------------------------------------------------------
assert "$BIN 5" "120"
assert "$BIN -r 5" "120"
assert "$BIN 0" "1"
assert "$BIN -r 0" "1"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./factorial [NUM]
  ./factorial -r [NUM]
Options:
  -h, --help      Show this help
  -r, --recursive Use recursive algorithm"

# ---------------------------------------------------------
# Test error: missing number
# ---------------------------------------------------------
assert "$BIN" "Error: missing number"

# ---------------------------------------------------------
# Test error: negative number
# ---------------------------------------------------------
assert "$BIN -1" "Error: negative number"

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
