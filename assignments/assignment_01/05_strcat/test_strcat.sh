#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strcat.sh
# Description: Compile strcat.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strcat.c"
BIN="./strcat"

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
echo ">>> gcc -Wall -Wextra $SRC -o strcat"
gcc -Wall -Wextra "$SRC" -o strcat
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Default concatenation (no separator)
# ---------------------------------------------------------
assert "$BIN \"hello\" \"world\"" "helloworld"
assert "$BIN \"abc\" \"123\"" "abc123"
assert "$BIN \"one\" \"two\" \"three\"" "onetwothree"

# ---------------------------------------------------------
# Test 2: Concatenation with separator (-s)
# ---------------------------------------------------------
assert "$BIN -s \" \" \"hello\" \"world\"" "hello world"
assert "$BIN -s \":\" \"abc\" \"def\" \"ghi\"" "abc:def:ghi"
assert "$BIN -s \"-\" \"1\" \"2\" \"3\" \"4\"" "1-2-3-4"

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
