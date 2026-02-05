#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_calc.sh
# Description: Compile calc.c and run automated tests
# ---------------------------------------------------------

SRC="calc.c"
BIN="./calc"

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
echo ">>> gcc -Wall -Wextra $SRC -o calc -lm"
gcc -Wall -Wextra "$SRC" -o calc -lm
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN -a 5 3" "8"
assert "$BIN -s 5 3" "2"
assert "$BIN -m 5 3" "15"
assert "$BIN -d 6 3" "2"
assert "$BIN -p 2 3" "8"

# ---------------------------------------------------------
# Test error: division by zero
# ---------------------------------------------------------
assert "$BIN -d 5 0" "Error: division by zero"

# ---------------------------------------------------------
# Test error: missing operands
# ---------------------------------------------------------
assert "$BIN -a 5" "Error: missing operands"

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
