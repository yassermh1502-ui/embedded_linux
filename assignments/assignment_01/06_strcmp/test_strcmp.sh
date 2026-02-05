#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strcmp.sh
# Description: Compile strcmp.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strcmp.c"
BIN="./strcmp"

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
echo ">>> gcc -Wall -Wextra $SRC -o strcmp"
gcc -Wall -Wextra "$SRC" -o strcmp
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Case-sensitive equality
# ---------------------------------------------------------
assert "$BIN \"abc\" \"abc\"" "Equal"

# ---------------------------------------------------------
# Test 2: Case-sensitive inequality
# ---------------------------------------------------------
assert "$BIN \"abc\" \"xyz\"" "Not equal"
assert "$BIN \"Hello\" \"hello\"" "Not equal"

# ---------------------------------------------------------
# Test 3: Case-insensitive (-i)
# ---------------------------------------------------------
assert "$BIN -i \"ABC\" \"abc\"" "Equal"
assert "$BIN -i \"Hello\" \"hello\"" "Equal"
assert "$BIN -i \"Test\" \"tesT\"" "Equal"
assert "$BIN -i \"abc\" \"xyz\"" "Not equal"

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
