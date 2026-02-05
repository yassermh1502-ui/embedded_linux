/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strcat.c
 * Author: Yasser Mahmoud
 * Description: Concatenate strings with optional separator.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_DEFAULT,   /* Concatenate without separator */
    MODE_SEPARATOR  /* Concatenate with separator */
} concat_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static void concat_strings(int argc, char *argv[], const char *sep);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    concat_mode_t mode = MODE_DEFAULT;
    const char *sep = "";   /* default separator is empty string */

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"sep",  required_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hs:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 's':
                mode = MODE_SEPARATOR;
                sep = optarg;
                break;

            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: missing strings to concatenate\n");
        print_usage(argv[0]);
        return 1;
    }

    switch (mode) {
        case MODE_DEFAULT:
        case MODE_SEPARATOR:
            concat_strings(argc, argv, sep);
            break;

        default:
            fprintf(stderr, "Error: unknown mode\n");
            return 1;
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING1 STRING2 [...]\n", prog);
    printf("  %s -s SEPARATOR STRING1 STRING2 [...]\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help       Show this help\n");
    printf("  -s, --sep CHAR   Separator between strings\n");
}

static void concat_strings(int argc, char *argv[], const char *sep) {
    int first = 1;
    for (int i = optind; i < argc; i++) {
        if (!first) {
            printf("%s", sep);
        }
        printf("%s", argv[i]);
        first = 0;
    }
    printf("\n");
}
