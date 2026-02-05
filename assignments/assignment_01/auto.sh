#!/bin/bash

# Base folder for exercises
BASE_DIR=~/embedded_linux/assignments/assignment_01

# List of exercises: folder name => C file prefix
declare -A EXERCISES=(
    [18_avg]=avg
    [19_max]=max
    [20_min]=min
    [21_factorial]=factorial
    [22_power]=power
    [23_sqrt]=sqrt
    [24_even]=even
    [25_prime]=prime
    [26_fibo]=fibo
    [27_digits]=digits
    [28_reverse]=reverse
    [29_strsum]=strsum
    [30_stralpha]=stralpha
    [31_stralphadigit]=stralphadigit
    [32_strascii]=strascii
    [33_strhex]=strhex
    [34_numtostr]=numtostr
    [35_strtonum]=strtonum
    [36_caesar]=caesar
    [37_strfreq]=strfreq
    [38_strunique]=strunique
    [39_strduplicate]=strduplicate
    [40_strfirst]=strfirst
    [41_strlast]=strlast
    [42_wordcount]=wordcount
    [43_strremove]=strremove
    [44_triangle]=triangle
    [45_table]=table
    [46_pattern]=pattern
    [47_armstrong]=armstrong
    [48_perfect]=perfect
)

# Loop over exercises and create folders, files
for folder in "${!EXERCISES[@]}"; do
    CFILE=${EXERCISES[$folder]}.c
    TESTFILE=test_${EXERCISES[$folder]}.sh

    mkdir -p "$BASE_DIR/$folder"
    cd "$BASE_DIR/$folder" || exit
    touch "$CFILE"
    touch "$TESTFILE"
    chmod +x "$TESTFILE"

    echo "Created: $folder/$CFILE and $folder/$TESTFILE"
done
