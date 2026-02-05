#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strpalindrome.sh
# Description: Compile strpalindrome.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strpalindrome.c"
BIN="./strpalindrome"

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
echo ">>> gcc -Wall -Wextra $SRC -o strpalindrome"
gcc -Wall -Wextra "$SRC" -o strpalindrome
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Palindromes
# ---------------------------------------------------------
assert "$BIN \"racecar\"" "Palindrome"
assert "$BIN \"level\"" "Palindrome"

# ---------------------------------------------------------
# Test 2: Not palindromes
# ---------------------------------------------------------
assert "$BIN \"hello\"" "Not a palindrome"
assert "$BIN \"world\"" "Not a palindrome"

# ---------------------------------------------------------
# Test 3: Case-insensitive (-i)
# ---------------------------------------------------------
assert "$BIN -i \"RaceCar\"" "Palindrome"
assert "$BIN -i \"LeVel\"" "Palindrome"
assert "$BIN -i \"HeLLo\"" "Not a palindrome"

# ---------------------------------------------------------
# Test 4: Help option (-h)
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
