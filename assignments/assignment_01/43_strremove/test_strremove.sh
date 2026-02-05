#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strremove.sh
# Description: Compile strremove.c and run automated tests
# ---------------------------------------------------------

SRC="strremove.c"
BIN="./strremove"

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
echo ">>> gcc -Wall -Wextra $SRC -o strremove"
gcc -Wall -Wextra "$SRC" -o strremove
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
assert "$BIN 'hello' -c l" "heo"
assert "$BIN 'hello' -c l -f" "helo"
assert "$BIN -h" $'Usage:\n  ./strremove STRING -c CHAR [OPTIONS]\n\nOptions:\n  -h          Show this help\n  -c CHAR     Character to remove\n  -f          Remove first occurrence only'

# Error: missing string
assert "$BIN -c l" "Error: missing STRING"

# Error: missing -c
assert "$BIN 'hello'" "Error: missing -c CHAR"

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
