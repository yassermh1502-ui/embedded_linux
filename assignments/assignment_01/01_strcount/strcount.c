/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strcount.c
 * Author: Yasser Mahmoud
 * Description: A simple program that counts characters or words based on user options.
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_CHARS,   /* Count characters (default) */
    MODE_WORDS    /* Count words */
} count_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static int count_words(const char *str);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    count_mode_t mode = MODE_CHARS;   /* default behavior */

    static struct option long_options[] = {
        {"help",  no_argument, 0, 'h'},
        {"chars", no_argument, 0, 'c'},
        {"words", no_argument, 0, 'w'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hcw", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'c':
                mode = MODE_CHARS;
                break;

            case 'w':
                mode = MODE_WORDS;
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

    switch (mode) {
        case MODE_WORDS:
            printf("%d\n", count_words(input));
            break;

        case MODE_CHARS:
        default:
            printf("%lu\n", strlen(input));
            break;
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s [OPTIONS] STRING\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -c, --chars    Count characters (default)\n");
    printf("  -w, --words    Count words\n");
}

static int count_words(const char *str) {
    int count = 0;
    int in_word = 0;

    while (*str) {
        if (*str == ' ' || *str == '\t' || *str == '\n') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }

    return count;
}
