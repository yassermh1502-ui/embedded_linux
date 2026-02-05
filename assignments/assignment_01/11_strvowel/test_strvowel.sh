#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strvowel.sh
# Description: Compile strvowel.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strvowel.c"
BIN="./strvowel"

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
echo ">>> gcc -Wall -Wextra $SRC -o strvowel"
gcc -Wall -Wextra "$SRC" -o strvowel
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Case-sensitive counting
# ---------------------------------------------------------
assert "$BIN \"hello\"" "2 vowels"
assert "$BIN \"HELLO\"" "0 vowels"
assert "$BIN \"xyz\"" "0 vowels"
assert "$BIN \"aeiou\"" "5 vowels"

# ---------------------------------------------------------
# Test 2: Case-insensitive (-i)
# ---------------------------------------------------------
assert "$BIN -i \"HELLO\"" "2 vowels"
assert "$BIN -i \"AeIoU\"" "5 vowels"
assert "$BIN -i \"xyz\"" "0 vowels"

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
