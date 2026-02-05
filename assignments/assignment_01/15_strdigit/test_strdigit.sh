#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strdigit.sh
# Description: Compile strdigit.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strdigit.c"
BIN="./strdigit"

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
echo ">>> gcc -Wall -Wextra $SRC -o strdigit"
gcc -Wall -Wextra "$SRC" -o strdigit
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Count digits (default)
# ---------------------------------------------------------
assert "$BIN \"hello123\"" "3 digits"
assert "$BIN \"abc123xyz456\"" "6 digits"
assert "$BIN \"no_digits\"" "0 digits"
assert "$BIN \"1\"" "1 digit"

# ---------------------------------------------------------
# Test 2: List all digits (-l)
# ---------------------------------------------------------
assert "$BIN -l \"hello123\"" "Digits: 123"
assert "$BIN -l \"abc123xyz456\"" "Digits: 123456"
assert "$BIN -l \"no_digits\"" "Digits: none"
assert "$BIN -l \"1a2b3\"" "Digits: 123"

# ---------------------------------------------------------
# Test 3: Help option (-h)
# ---------------------------------------------------------
HELP_OUTPUT=$($BIN -h)
echo
echo ">>> $BIN -h"
echo "$HELP_OUTPUT"

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
