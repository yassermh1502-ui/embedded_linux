#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strsub.sh
# Description: Compile strsub.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strsub.c"
BIN="./strsub"

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
echo ">>> gcc -Wall -Wextra $SRC -o strsub"
gcc -Wall -Wextra "$SRC" -o strsub
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Range -s START -e END
# ---------------------------------------------------------
assert "$BIN \"hello\" -s 1 -e 4" "ell"
assert "$BIN \"abcdef\" -s 0 -e 3" "abc"
assert "$BIN \"abcdef\" -s 2 -e 6" "cdef"

# ---------------------------------------------------------
# Test 2: First N characters -n N
# ---------------------------------------------------------
assert "$BIN \"hello\" -n 3" "hel"
assert "$BIN \"abcdef\" -n 4" "abcd"
assert "$BIN \"hi\" -n 5" "hi"  # N > length

# ---------------------------------------------------------
# Test 3: Last N characters -l N
# ---------------------------------------------------------
assert "$BIN \"hello\" -l 2" "lo"
assert "$BIN \"abcdef\" -l 3" "def"
assert "$BIN \"hi\" -l 5" "hi"  # N > length

# ---------------------------------------------------------
# Test 4: Help option -h
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
