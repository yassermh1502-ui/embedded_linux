#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_stralpha.sh
# Description: Compile stralpha.c and run automated tests
# ---------------------------------------------------------

SRC="stralpha.c"
BIN="./stralpha"

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
echo ">>> gcc -Wall -Wextra $SRC -o stralpha"
gcc -Wall -Wextra "$SRC" -o stralpha
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN \"hello123\"" "5"
assert "$BIN -u \"Hello123\"" "1"
assert "$BIN -l \"Hello123\"" "4"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./stralpha STRING
Options:
  -h, --help    Show this help
  -u, --upper   Count uppercase letters only
  -l, --lower   Count lowercase letters only"

# ---------------------------------------------------------
# Test error: missing string
# ---------------------------------------------------------
assert "$BIN" "Error: missing string"

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
