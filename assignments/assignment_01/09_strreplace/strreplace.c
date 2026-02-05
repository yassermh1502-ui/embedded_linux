/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strreplace.c
 * Author: Yasser Mahmoud
 * Description: Replace a character in a string, optionally first occurrence only.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_ALL,   /* Replace all occurrences (default) */
    MODE_FIRST  /* Replace first occurrence only */
} replace_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static void replace_char(const char *str, char oldc, char newc, replace_mode_t mode);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    replace_mode_t mode = MODE_ALL;
    char oldc = '\0', newc = '\0';

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "ho:n:f", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'o':
                oldc = optarg[0];
                break;

            case 'n':
                newc = optarg[0];
                break;

            case 'f':
                mode = MODE_FIRST;
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

    if (oldc == '\0' || newc == '\0') {
        fprintf(stderr, "Error: both -o and -n must be specified\n");
        print_usage(argv[0]);
        return 1;
    }

    const char *input = argv[optind];
    replace_char(input, oldc, newc, mode);

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING -o OLD -n NEW          # replace all occurrences\n", prog);
    printf("  %s STRING -o OLD -n NEW -f       # replace first occurrence only\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -o OLD         Old character\n");
    printf("  -n NEW         New character\n");
    printf("  -f             Replace first occurrence only\n");
}

static void replace_char(const char *str, char oldc, char newc, replace_mode_t mode) {
    int replaced = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == oldc && (mode == MODE_ALL || (mode == MODE_FIRST && !replaced))) {
            putchar(newc);
            replaced = 1;
        } else {
            putchar(str[i]);
        }
    }
    putchar('\n');
}
