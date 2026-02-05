#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_triangle.sh
# Description: Compile triangle.c and run automated tests
# ---------------------------------------------------------

SRC="triangle.c"
BIN="./triangle"

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
echo ">>> gcc -Wall -Wextra $SRC -o triangle"
gcc -Wall -Wextra "$SRC" -o triangle
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
EXPECTED=$(printf "1 \n1 2 \n1 2 3 \n1 2 3 4 \n1 2 3 4 5 \n")
assert "$BIN 5" "$EXPECTED"

EXPECTED=$(printf "    1 \n   1 2 \n  1 2 3 \n 1 2 3 4 \n1 2 3 4 5 \n")
assert "$BIN 5 -r" "$EXPECTED"

EXPECTED=$(printf "1 2 3 4 5 \n1 2 3 4 \n1 2 3 \n1 2 \n1 \n")
assert "$BIN 5 -i" "$EXPECTED"

EXPECTED=$(printf "    1 2 3 4 5 \n   1 2 3 4 \n  1 2 3 \n 1 2 \n1 \n")
assert "$BIN 5 -r -i" "$EXPECTED"

# Help test
assert "$BIN -h" $'Usage:\n  ./triangle N [OPTIONS]\n\nOptions:\n  -h         Show this help\n  -r         Right aligned triangle\n  -i         Inverted triangle'

# Error: missing number
assert "$BIN" "Error: missing number N"

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
