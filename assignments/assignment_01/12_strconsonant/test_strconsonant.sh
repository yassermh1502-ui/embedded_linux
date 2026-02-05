#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strconsonant.sh
# Description: Compile strconsonant.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strconsonant.c"
BIN="./strconsonant"

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
echo ">>> gcc -Wall -Wextra $SRC -o strconsonant"
gcc -Wall -Wextra "$SRC" -o strconsonant
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Case-sensitive counting
# ---------------------------------------------------------
assert "$BIN \"hello\"" "3 consonants"
assert "$BIN \"HELLO\"" "0 consonants"
assert "$BIN \"aeiou\"" "0 consonants"
assert "$BIN \"xyz\"" "3 consonants"

# ---------------------------------------------------------
# Test 2: Case-insensitive (-i)
# ---------------------------------------------------------
assert "$BIN -i \"HELLO\"" "3 consonants"
assert "$BIN -i \"AeIoU\"" "0 consonants"
assert "$BIN -i \"xyz\"" "3 consonants"

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
