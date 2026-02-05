#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_numtostr.sh
# Description: Compile numtostr.c and run automated tests
# ---------------------------------------------------------

SRC="numtostr.c"
BIN="./numtostr"

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
echo ">>> gcc -Wall -Wextra $SRC -o numtostr"
gcc -Wall -Wextra "$SRC" -o numtostr
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN 123" "one two three"
assert "$BIN 0" "zero"
assert "$BIN -w 123" "one hundred twenty three"
assert "$BIN -w 5" "five"
assert "$BIN -h" "Usage:
  ./numtostr NUMBER
  ./numtostr -w NUMBER
Options:
  -h, --help   Show this help
  -w, --words  Full words (not digit by digit)"

# ---------------------------------------------------------
# Test error: missing number
# ---------------------------------------------------------
assert "$BIN" "Error: missing NUMBER"

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
