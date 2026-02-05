#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_perfect.sh
# Description: Compile perfect.c and run automated tests
# ---------------------------------------------------------

SRC="perfect.c"
BIN="./perfect"

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
echo ">>> gcc -Wall -Wextra $SRC -o perfect"
gcc -Wall -Wextra "$SRC" -o perfect
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests: Single number check
# ---------------------------------------------------------
assert "$BIN 28" "Yes"
assert "$BIN 12" "No"

# ---------------------------------------------------------
# Tests: Range check
# ---------------------------------------------------------
EXPECTED=$'6\n28\n496'
assert "$BIN -r 1 500" "$EXPECTED"

# ---------------------------------------------------------
# Help test
# ---------------------------------------------------------
assert "$BIN -h" $'Usage:\n  ./perfect NUMBER\n  ./perfect -r START END\n\nOptions:\n  -h, --help    Show this help\n  -r, --range   Check all numbers in range START END\n  -v, --verbose Show divisors'

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
