#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strhex.sh
# Description: Compile strhex.c and run automated tests
# ---------------------------------------------------------

SRC="strhex.c"
BIN="./strhex"

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
echo ">>> gcc -Wall -Wextra $SRC -o strhex"
gcc -Wall -Wextra "$SRC" -o strhex
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN \"ABC\"" "41 42 43"
assert "$BIN -d 414243" "ABC"
assert "$BIN -d 48656C6C6F" "Hello"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./strhex STRING
  ./strhex -d HEX_STRING

Options:
  -h, --help    Show this help
  -d, --decode  Decode hex string to normal string"

# ---------------------------------------------------------
# Test error: missing argument
# ---------------------------------------------------------
assert "$BIN" "Error: missing argument"

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
