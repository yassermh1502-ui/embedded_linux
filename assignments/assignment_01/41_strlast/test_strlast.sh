#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strlast.sh
# Description: Compile strlast.c and run automated tests
# ---------------------------------------------------------

SRC="strlast.c"
BIN="./strlast"

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
echo ">>> gcc -Wall -Wextra $SRC -o strlast"
gcc -Wall -Wextra "$SRC" -o strlast
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN hello -n 3" "llo"
assert "$BIN 'hello world' -w 1" "world"
assert "$BIN 'hello world from C' -w 3" "world from C"
assert "$BIN -h" $'Usage:\n  ./strlast STRING [OPTIONS]\nOptions:\n  -h          Show this help\n  -n N        Last N characters\n  -w N        Last N words'

# Error: missing string
assert "$BIN" "Error: missing STRING"

# Error: missing option
assert "$BIN hello" "Error: specify -n or -w"

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
