#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_armstrong.sh
# Description: Compile armstrong.c and run automated tests
# ---------------------------------------------------------

SRC="armstrong.c"
BIN="./armstrong"

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
echo ">>> gcc -Wall -Wextra $SRC -o armstrong"
gcc -Wall -Wextra "$SRC" -o armstrong
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests: Single number check
# ---------------------------------------------------------
assert "$BIN 153" "Yes"
assert "$BIN 123" "No"

# ---------------------------------------------------------
# Tests: Range check
# ---------------------------------------------------------
EXPECTED=$'1\n2\n3\n4\n5\n6\n7\n8\n9\n153\n370\n371\n407'
assert "$BIN -r 1 500" "$EXPECTED"

# ---------------------------------------------------------
# Help test
# ---------------------------------------------------------
assert "$BIN -h" $'Usage:\n  ./armstrong NUMBER\n  ./armstrong -r START END\n\nOptions:\n  -h, --help    Show this help\n  -r, --range   Check all numbers in range START END\n  -v, --verbose Show calculation'

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
