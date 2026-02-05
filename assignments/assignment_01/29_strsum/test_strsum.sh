#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strsum.sh
# Description: Compile strsum.c and run automated tests
# ---------------------------------------------------------

SRC="strsum.c"
BIN="./strsum"

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
echo ">>> gcc -Wall -Wextra $SRC -o strsum"
gcc -Wall -Wextra "$SRC" -o strsum
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN \"abc123xyz456\"" "21"
assert "$BIN \"hello123\"" "6"
assert "$BIN -v \"abc123xyz456\"" $'Digits found: 1 2 3 4 5 6 \n21'

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./strsum STRING
Options:
  -h, --help     Show this help
  -v, --verbose  Show which digits found"

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
