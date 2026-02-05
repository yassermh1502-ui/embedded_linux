#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_power.sh
# Description: Compile power.c and run automated tests
# ---------------------------------------------------------

SRC="power.c"
BIN="./power"

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
echo ">>> gcc -Wall -Wextra $SRC -o power"
gcc -Wall -Wextra "$SRC" -o power
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests with positional arguments
# ---------------------------------------------------------
assert "$BIN 2 3" "8"
assert "$BIN 5 0" "1"
assert "$BIN 0 5" "0"

# ---------------------------------------------------------
# Tests with flags
# ---------------------------------------------------------
assert "$BIN -b 3 -e 4" "81"
assert "$BIN -b 2 -e 10" "1024"

# ---------------------------------------------------------
# Test help
# ---------------------------------------------------------
assert "$BIN -h" "Usage:
  ./power BASE EXPONENT
  ./power -b BASE -e EXPONENT
Options:
  -h, --help      Show this help
  -b, --base      Base number
  -e, --exponent  Exponent"

# ---------------------------------------------------------
# Test error: missing arguments
# ---------------------------------------------------------
assert "$BIN" "Error: missing base or exponent"
assert "$BIN -b 5" "Error: missing base or exponent"

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
