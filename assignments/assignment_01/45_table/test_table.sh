#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_table.sh
# Description: Compile table.c and run automated tests
# ---------------------------------------------------------

SRC="table.c"
BIN="./table"

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
echo ">>> gcc -Wall -Wextra $SRC -o table"
gcc -Wall -Wextra "$SRC" -o table
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Test: Single number default rows (10)
# ---------------------------------------------------------
EXPECTED=$(printf "5x1=5\n5x2=10\n5x3=15\n5x4=20\n5x5=25\n5x6=30\n5x7=35\n5x8=40\n5x9=45\n5x10=50\n")
assert "$BIN 5" "$EXPECTED"

# Test: Single number custom rows
EXPECTED=$(printf "3x1=3\n3x2=6\n3x3=9\n3x4=12\n")
assert "$BIN 3 -n 4" "$EXPECTED"

# Test: Range mode
EXPECTED=$(printf "1x1=1\n1x2=2\n1x3=3\n2x1=2\n2x2=4\n2x3=6\n")
assert "$BIN -r 1 2" "$EXPECTED"

# Help test
assert "$BIN -h" $'Usage:\n  ./table NUMBER [OPTIONS]\n  ./table -r START END\n\nOptions:\n  -h          Show help\n  -n ROWS     Number of rows (default 10)\n  -r START END Use range from START to END'

# Error: missing number
assert "$BIN" "Error: missing NUMBER"

# Error: missing range
assert "$BIN -r" "Error: missing START or END for range"

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
