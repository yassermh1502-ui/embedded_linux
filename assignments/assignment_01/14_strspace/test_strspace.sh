#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strspace.sh
# Description: Compile strspace.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strspace.c"
BIN="./strspace"

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
echo ">>> gcc -Wall -Wextra $SRC -o strspace"
gcc -Wall -Wextra "$SRC" -o strspace
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Count only spaces (default)
# ---------------------------------------------------------
assert "$BIN \"hello world\"" "1 space"
assert "$BIN \"a b c d\"" "3 spaces"
assert "$BIN \"   \"" "3 spaces"
assert "$BIN \"no_spaces\"" "0 spaces"

# ---------------------------------------------------------
# Test 2: Count all whitespace (-a)
# ---------------------------------------------------------
assert "$BIN -a \"$(printf 'hello  world')\"" "2 spaces"
assert "$BIN -a \"$(printf 'a b\nc\td')\"" "3 spaces"
assert "$BIN -a \"$(printf ' \t\n7')\"" "3 spaces"

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
