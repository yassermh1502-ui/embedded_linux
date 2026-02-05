#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_avg.sh
# Description: Compile avg.c and run automated tests
# ---------------------------------------------------------

SRC="avg.c"
BIN="./avg"

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
echo ">>> gcc -Wall -Wextra $SRC -o avg"
gcc -Wall -Wextra "$SRC" -o avg
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests with numbers
# ---------------------------------------------------------
assert "$BIN 10 20 30" "20.00"
assert "$BIN -i 10 20 30" "20"
assert "$BIN 1 2 3 4 5" "3.00"
assert "$BIN -i 1 2 3 4 5" "3"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./avg [NUMBERS...]
Options:
  -h, --help    Show this help
  -i            Integer average (default is floating point)"

# ---------------------------------------------------------
# Test error: missing numbers
# ---------------------------------------------------------
assert "$BIN" "Error: missing numbers"

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
