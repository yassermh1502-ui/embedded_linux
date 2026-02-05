#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_stralphadigit.sh
# Description: Compile stralphadigit.c and run automated tests
# ---------------------------------------------------------

SRC="stralphadigit.c"
BIN="./stralphadigit"

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
echo ">>> gcc -Wall -Wextra $SRC -o stralphadigit"
gcc -Wall -Wextra "$SRC" -o stralphadigit
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN \"hello123\"" "Alpha: 5, Digits: 3"
assert "$BIN -a \"test456!@#\"" "Alpha: 4, Digits: 3, Other: 3"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./stralphadigit STRING
Options:
  -h, --help    Show this help
  -a, --all     Count all character types (alpha, digit, others)"

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
