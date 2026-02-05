/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strspace.c
 * Author: Yasser Mahmoud
 * Description: Count spaces in a string, optionally counting all whitespace.
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
    MODE_SPACES,       /* Count only spaces (default) */
    MODE_ALL_WHITES    /* Count all whitespace (tabs, newlines) */
} space_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static int count_spaces(const char *str, space_mode_t mode);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    space_mode_t mode = MODE_SPACES;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "ha", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'a':
                mode = MODE_ALL_WHITES;
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
    int result = count_spaces(input, mode);
    printf("%d %s\n", result, result == 1 ? "space" : "spaces");

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING           # count spaces only\n", prog);
    printf("  %s -a STRING        # count all whitespace (tabs, newlines)\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -a             Count all whitespace\n");
}

static int count_spaces(const char *str, space_mode_t mode) {
    int count = 0;

    while (*str) {
        if (mode == MODE_ALL_WHITES) {
            unsigned char c = (unsigned char)*str;
            if ((c == ' ') || (c == '\t') || (c == '\n')) count++;
        } else {
            if (*str == ' ') count++;
        }
        str++;
    }

    return count;
}
