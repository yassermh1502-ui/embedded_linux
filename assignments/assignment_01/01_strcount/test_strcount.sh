#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strcount.sh
# Description: Compile strcount.c and run all test cases
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strcount.c"
BIN="./strcount"

# ---------------------------------------------------------
# Begin tests
# ---------------------------------------------------------
echo "======================================"
echo "Running strcount test cases"
echo "======================================"

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
echo ">>> gcc -Wall -Wextra $SRC -o strcount"
gcc -Wall -Wextra "$SRC" -o strcount
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN \"hello\"" "5"
assert "$BIN \"hello world\"" "11"

assert "$BIN -c \"abc def\"" "7"
assert "$BIN --chars \"12345\"" "5"

assert "$BIN -w \"hello world\"" "2"
assert "$BIN -w \"one   two  three\"" "3"
assert "$BIN -w $'one\ttwo\tthree'" "3"

assert "$BIN \"\"" "0"
assert "$BIN -w \"     \"" "0"
assert "$BIN -w \"linux\"" "1"

assert "$BIN -w -c \"hello world\"" "11"
assert "$BIN -c -w \"hello world\"" "2"

assert "$BIN -w $'\nhello\nworld\n   my name    '" "4"

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