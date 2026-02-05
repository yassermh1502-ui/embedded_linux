/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strpalindrome.c
 * Author: Yasser Mahmoud
 * Description: Check if a string is a palindrome, optionally case-insensitive.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_SENSITIVE,    /* Case sensitive (default) */
    MODE_INSENSITIVE   /* Case insensitive */
} palindrome_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static int is_palindrome(const char *str, palindrome_mode_t mode);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    palindrome_mode_t mode = MODE_SENSITIVE;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hi", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'i':
                mode = MODE_INSENSITIVE;
                break;

            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: missing STRING\n");
        print_usage(argv[0]);
        return 1;
    }

    const char *input = argv[optind];

    if (is_palindrome(input, mode)) {
        printf("Palindrome\n");
    } else {
        printf("Not a palindrome\n");
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING           # check palindrome (case-sensitive)\n", prog);
    printf("  %s -i STRING        # check palindrome (case-insensitive)\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -i             Case insensitive\n");
}

static int is_palindrome(const char *str, palindrome_mode_t mode) {
    size_t left = 0;
    size_t right = strlen(str);
    if (right == 0) return 1; // empty string is palindrome
    right--; // last valid index

    while (left < right) {
        char c_left = str[left];
        char c_right = str[right];

        if (mode == MODE_INSENSITIVE) {
            c_left = tolower(c_left);
            c_right = tolower(c_right);
        }

        if (c_left != c_right) {
            return 0; // Not palindrome
        }

        left++;
        right--;
    }

    return 1; // Palindrome
}
