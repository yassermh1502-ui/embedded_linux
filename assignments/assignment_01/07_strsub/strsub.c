/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strsub.c
 * Author: Yasser Mahmoud
 * Description: Extract substring from a string using different options.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_RANGE,  /* -s start -e end */
    MODE_FIRST,  /* -n N */
    MODE_LAST    /* -l N */
} substr_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static void substring(const char *str, substr_mode_t mode, int start, int end, int n);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    substr_mode_t mode = MODE_RANGE;  // default
    int start = -1, end = -1, n = -1;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hs:e:n:l:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 's':
                start = atoi(optarg);
                mode = MODE_RANGE;
                break;

            case 'e':
                end = atoi(optarg);
                mode = MODE_RANGE;
                break;

            case 'n':
                n = atoi(optarg);
                mode = MODE_FIRST;
                break;

            case 'l':
                n = atoi(optarg);
                mode = MODE_LAST;
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
    substring(input, mode, start, end, n);

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING -s START -e END  # substring from START to END-1\n", prog);
    printf("  %s STRING -n N             # first N characters\n", prog);
    printf("  %s STRING -l N             # last N characters\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -s START       Start position (0-based)\n");
    printf("  -e END         End position (exclusive)\n");
    printf("  -n N           First N characters\n");
    printf("  -l N           Last N characters\n");
}

static void substring(const char *str, substr_mode_t mode, int start, int end, int n) {
    int len = strlen(str);

    switch (mode) {
        case MODE_RANGE:
            if (start < 0 || end < 0 || start >= len || end > len || start >= end) {
                fprintf(stderr, "Error: invalid start/end\n");
                return;
            }
            for (int i = start; i < end; i++) {
                putchar(str[i]);
            }
            putchar('\n');
            break;

        case MODE_FIRST:
            if (n < 0 || n > len) n = len;
            for (int i = 0; i < n; i++) {
                putchar(str[i]);
            }
            putchar('\n');
            break;

        case MODE_LAST:
            if (n < 0 || n > len) n = len;
            for (int i = len - n; i < len; i++) {
                putchar(str[i]);
            }
            putchar('\n');
            break;

        default:
            fprintf(stderr, "Error: unknown mode\n");
    }
}
