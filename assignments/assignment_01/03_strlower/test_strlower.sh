#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strlower.sh
# Description: Compile strlower.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strlower.c"
BIN="./strlower"

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
echo ">>> gcc -Wall -Wextra $SRC -o strlower"
gcc -Wall -Wextra "$SRC" -o strlower
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Simple string input
# ---------------------------------------------------------
assert "$BIN \"HELLO\"" "hello"
assert "$BIN \"HELLO WORLD\"" "hello world"
assert "$BIN \"123ABC!@#\"" "123abc!@#"

# ---------------------------------------------------------
# Test 2: Multi-line string input
# ---------------------------------------------------------
assert "$BIN $'HELLO\nWORLD\n My NAME'" $'hello\nworld\n my name'

# ---------------------------------------------------------
# Test 3: File input
# ---------------------------------------------------------
# Create temporary test file
TEST_FILE=$(mktemp)
echo -e "HELLO WORLD\nTHIS IS A TEST" > "$TEST_FILE"
assert "$BIN -f $TEST_FILE" $'hello world\nthis is a test'
rm "$TEST_FILE"

# ---------------------------------------------------------
# Test 4: Help option
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
