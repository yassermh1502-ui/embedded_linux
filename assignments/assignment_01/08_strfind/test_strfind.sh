#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strfind.sh
# Description: Compile strfind.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strfind.c"
BIN="./strfind"

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
echo ">>> gcc -Wall -Wextra $SRC -o strfind"
gcc -Wall -Wextra "$SRC" -o strfind
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Find first occurrence
# ---------------------------------------------------------
assert "$BIN \"hello\" -c 'l'" "Found at position 2"
assert "$BIN \"world\" -c 'w'" "Found at position 0"

# ---------------------------------------------------------
# Test 2: Find all occurrences (-a)
# ---------------------------------------------------------
assert "$BIN \"hello\" -c 'l' -a" "2, 3"
assert "$BIN \"banana\" -c 'a' -a" "1, 3, 5"

# ---------------------------------------------------------
# Test 3: Character not found
# ---------------------------------------------------------
assert "$BIN \"hello\" -c 'x'" "Not found"
assert "$BIN \"world\" -c 'z' -a" "Not found"

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
