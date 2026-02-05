/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strdigit.c
 * Author: Yasser Mahmoud
 * Description: Count digits in a string, optionally list all digits.
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
    MODE_COUNT,  /* Count digits (default) */
    MODE_LIST    /* List all digits */
} digit_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static int count_digits(const char *str, char *digits, int max_digits);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    digit_mode_t mode = MODE_COUNT;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"list", no_argument, 0, 'l'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hl", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'l':
                mode = MODE_LIST;
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

    char digits[1024];  // buffer for list mode
    int count = count_digits(input, digits, sizeof(digits));

    switch (mode) {
        case MODE_LIST:
            if (count > 0) {
                digits[count] = '\0';
                printf("Digits: %s\n", digits);
            } else {
                printf("Digits: none\n");
            }
            break;

        case MODE_COUNT:
        default:
            printf("%d %s\n", count, count == 1 ? "digit" : "digits");
            break;
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING        # count digits\n", prog);
    printf("  %s -l STRING     # list all digits\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -l, --list     List all digits found\n");
}

static int count_digits(const char *str, char *digits, int max_digits) {
    int count = 0;

    while (*str) {
        if (isdigit((unsigned char)*str)) {
            if (digits && count < max_digits - 1) {
                digits[count] = *str;
            }
            count++;
        }
        str++;
    }

    return count;
}
