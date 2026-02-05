#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strascii.sh
# Description: Compile strascii.c and run automated tests
# ---------------------------------------------------------

SRC="strascii.c"
BIN="./strascii"

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
echo ">>> gcc -Wall -Wextra $SRC -o strascii"
gcc -Wall -Wextra "$SRC" -o strascii
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN \"ABC\"" "A=65, B=66, C=67"
assert "$BIN -d 65" "A"
assert "$BIN -d 90" "Z"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./strascii STRING
  ./strascii -d ASCII_VALUE

Options:
  -h, --help    Show this help
  -d, --decode  Decode ASCII value to character"

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
