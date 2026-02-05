#!/bin/bash
# ---------------------------------------------------------
# Script Name: test_strfreq.sh
# Description: Compile strfreq.c and run automated tests
# ---------------------------------------------------------

SRC="strfreq.c"
BIN="./strfreq"

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
echo ">>> gcc -Wall -Wextra $SRC -o strfreq"
gcc -Wall -Wextra "$SRC" -o strfreq
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
# Default order
assert "$BIN hello" $'h:1\ne:1\nl:2\no:1'

# Sort by character
assert "$BIN hello -s" $'e:1\nh:1\nl:2\no:1'

# Sort by frequency
assert "$BIN hello -f" $'e:1\nh:1\no:1\nl:2'

# Help
assert "$BIN -h" $'Usage:
  ./strfreq STRING [OPTIONS]
Options:
  -h          Show this help
  -s          Sort by character
  -f          Sort by frequency'

# Error: missing string
assert "$BIN" "Error: missing STRING"

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
