/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strconsonant.c
 * Author: Yasser Mahmoud
 * Description: Count consonants in a string, optionally case-insensitive.
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
} consonant_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static int count_consonants(const char *str, consonant_mode_t mode);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    consonant_mode_t mode = MODE_SENSITIVE;

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
    int result = count_consonants(input, mode);
    printf("%d consonants\n", result);

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING           # count consonants (case-sensitive)\n", prog);
    printf("  %s -i STRING        # count consonants (case-insensitive)\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -i             Case insensitive\n");
}

static int count_consonants(const char *str, consonant_mode_t mode) {
    int count = 0;

    while (*str) {
        char c = *str;
        if (mode == MODE_INSENSITIVE) {
            c = tolower(c);
        }
        if ((c >= 'a' && c <= 'z') && !(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')) {
            count++;
        }
        str++;
    }

    return count;
}
