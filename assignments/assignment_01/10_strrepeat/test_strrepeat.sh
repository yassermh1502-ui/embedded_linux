#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strrepeat.sh
# Description: Compile strrepeat.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strrepeat.c"
BIN="./strrepeat"

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
echo ">>> gcc -Wall -Wextra $SRC -o strrepeat"
gcc -Wall -Wextra "$SRC" -o strrepeat
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Repeat without separator
# ---------------------------------------------------------
assert "$BIN \"abc\" -n 3" "abcabcabc"
assert "$BIN \"Hi\" -n 1" "Hi"
assert "$BIN \"X\" -n 5" "XXXXX"

# ---------------------------------------------------------
# Test 2: Repeat with separator
# ---------------------------------------------------------
assert "$BIN \"Hi\" -n 5 -s ' '" "Hi Hi Hi Hi Hi"
assert "$BIN \"abc\" -n 3 -s ','" "abc,abc,abc"
assert "$BIN \"abc\" -n 2 -s '-'" "abc-abc"

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
