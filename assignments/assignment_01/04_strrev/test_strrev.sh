#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strrev.sh
# Description: Compile strrev.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strrev.c"
BIN="./strrev"

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
echo ">>> gcc -Wall -Wextra $SRC -o strrev"
gcc -Wall -Wextra "$SRC" -o strrev
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Reverse string (characters)
# ---------------------------------------------------------
assert "$BIN \"hello\"" "olleh"
assert "$BIN \"abc123\"" "321cba"
assert "$BIN \"Hello World!\"" "!dlroW olleH"

# ---------------------------------------------------------
# Test 2: Reverse word order (-w)
# ---------------------------------------------------------
assert "$BIN -w \"hello world\"" "world hello"
assert "$BIN -w \"This is a test\"" "test a is This"
assert "$BIN -w \"  multiple   spaces  \"" "spaces multiple"

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
