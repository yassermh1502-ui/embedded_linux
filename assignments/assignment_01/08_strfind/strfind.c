/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strfind.c
 * Author: Yasser Mahmoud
 * Description: Find a character in a string, optionally all occurrences.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_FIRST,  /* Find first occurrence (default) */
    MODE_ALL     /* Find all occurrences */
} find_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static void find_char(const char *str, char c, find_mode_t mode);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    char target = '\0';
    find_mode_t mode = MODE_FIRST;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hc:a", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'c':
                target = optarg[0];
                break;

            case 'a':
                mode = MODE_ALL;
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

    if (target == '\0') {
        fprintf(stderr, "Error: -c option required\n");
        print_usage(argv[0]);
        return 1;
    }

    const char *input = argv[optind];
    find_char(input, target, mode);

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING -c CHAR           # find first occurrence\n", prog);
    printf("  %s STRING -c CHAR -a        # find all occurrences\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -c CHAR        Character to find (required)\n");
    printf("  -a             Find all occurrences\n");
}

static void find_char(const char *str, char c, find_mode_t mode) {
    int found = 0;

    switch (mode) {
        case MODE_FIRST:
            for (int i = 0; str[i] != '\0'; i++) {
                if (str[i] == c) {
                    printf("Found at position %d\n", i);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Not found\n");
            }
            break;

        case MODE_ALL: {
            int first = 1;
            for (int i = 0; str[i] != '\0'; i++) {
                if (str[i] == c) {
                    if (!first) printf(", ");
                    printf("%d", i);
                    found = 1;
                    first = 0;
                }
            }
            if (found) {
                printf("\n");
            } else {
                printf("Not found\n");
            }
            break;
        }

        default:
            printf("Invalid mode\n");
            break;
    }
}
