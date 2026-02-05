#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_wordcount.sh
# Description: Compile wordcount.c and run automated tests
# ---------------------------------------------------------

SRC="wordcount.c"
BIN="./wordcount"

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
echo ">>> gcc -Wall -Wextra $SRC -o wordcount"
gcc -Wall -Wextra "$SRC" -o wordcount
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN 'hello world from C'" "4"
assert "$BIN 'hello\nworld'" "2"
assert "$BIN 'hello world' -c" "11"
assert "$BIN -h" $'Usage:\n  ./wordcount STRING [OPTIONS]\n\nOptions:\n  -h          Show this help\n  -w          Count words (default)\n  -l          Count lines\n  -c          Count characters'

# Error: missing string
assert "$BIN" "Error: missing STRING"

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
