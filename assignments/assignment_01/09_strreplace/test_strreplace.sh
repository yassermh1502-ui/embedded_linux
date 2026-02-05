#!/bin/bash

# ---------------------------------------------------------
# Script Name: test_strreplace.sh
# Description: Compile strreplace.c and run automated tests
# Author: Yasser Mahmoud
# ---------------------------------------------------------

SRC="strreplace.c"
BIN="./strreplace"

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
echo ">>> gcc -Wall -Wextra $SRC -o strreplace"
gcc -Wall -Wextra "$SRC" -o strreplace
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test 1: Replace all occurrences
# ---------------------------------------------------------
assert "$BIN \"hello\" -o 'l' -n 'x'" "hexxo"
assert "$BIN \"banana\" -o 'a' -n 'o'" "bonono"

# ---------------------------------------------------------
# Test 2: Replace first occurrence only (-f)
# ---------------------------------------------------------
assert "$BIN \"hello\" -o 'l' -n 'x' -f" "hexlo"
assert "$BIN \"banana\" -o 'a' -n 'o' -f" "bonana"

# ---------------------------------------------------------
# Test 3: Replace character not present
# ---------------------------------------------------------
assert "$BIN \"hello\" -o 'z' -n 'x'" "hello"
assert "$BIN \"hello\" -o 'z' -n 'x' -f" "hello"

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
