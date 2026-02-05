/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strcmp.c
 * Author: Yasser Mahmoud
 * Description: Compare two strings, optionally case-insensitive.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_SENSITIVE,   /* Case-sensitive comparison (default) */
    MODE_INSENSITIVE  /* Case-insensitive comparison */
} compare_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static int str_compare(const char *s1, const char *s2, compare_mode_t mode);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    compare_mode_t mode = MODE_SENSITIVE;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"ignore-case", no_argument, 0, 'i'},
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

    if (optind + 1 >= argc) {
        fprintf(stderr, "Error: missing strings to compare\n");
        print_usage(argv[0]);
        return 1;
    }

    const char *s1 = argv[optind];
    const char *s2 = argv[optind + 1];

    int cmp_result = str_compare(s1, s2, mode);
    if (cmp_result == 0) {
        printf("Equal\n");
    } else {
        printf("Not equal\n");
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING1 STRING2\n", prog);
    printf("  %s -i STRING1 STRING2  # Case-insensitive\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -i             Case-insensitive comparison\n");
}

static int str_compare(const char *s1, const char *s2, compare_mode_t mode) {
    if (mode == MODE_INSENSITIVE) {
        while (*s1 && *s2) {
            if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
                return 1; // not equal
            }
            s1++;
            s2++;
        }
        return (*s1 || *s2) ? 1 : 0; // check length mismatch
    } else {
        return strcmp(s1, s2);
    }
}
