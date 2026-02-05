#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_pattern.sh
# Description: Compile pattern.c and run automated tests
# ---------------------------------------------------------

SRC="pattern.c"
BIN="./pattern"

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
echo ">>> gcc -Wall -Wextra $SRC -o pattern"
gcc -Wall -Wextra "$SRC" -o pattern
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests: Triangle
# ---------------------------------------------------------
EXPECTED=$'*\n**\n***\n****\n*****\n'
assert "$BIN -n 5 -s '*'" "$EXPECTED"

# ---------------------------------------------------------
# Tests: Pyramid
# ---------------------------------------------------------
EXPECTED=$'    *\n   ***\n  *****\n *******\n*********\n'
assert "$BIN -n 5 -s '*' -p pyramid" "$EXPECTED"

# ---------------------------------------------------------
# Tests: Diamond
# ---------------------------------------------------------
EXPECTED=$'    *\n   ***\n  *****\n *******\n*********\n *******\n  *****\n   ***\n    *\n'
assert "$BIN -n 5 -s '*' -p diamond" "$EXPECTED"

# ---------------------------------------------------------
# Help test
# ---------------------------------------------------------
assert "$BIN -h" $'Usage:\n  ./pattern [OPTIONS]\n\nOptions:\n  -h          Show help\n  -s SYMBOL   Symbol to use (default *)\n  -n ROWS     Number of rows (default 5)\n  -p TYPE     Pattern type: triangle, pyramid, diamond'

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
