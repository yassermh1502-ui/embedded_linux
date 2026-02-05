/* ------------------------- File Information ------------------------- */
/* 
 * File Name: stralphadigit.c
 * Author: Yasser Mahmoud
 * Description: Count alphabets and digits separately, with option for all characters
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int show_all = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"all",  no_argument, 0, 'a'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "ha", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./stralphadigit STRING\n");
                printf("Options:\n");
                printf("  -h, --help    Show this help\n");
                printf("  -a, --all     Count all character types (alpha, digit, others)\n");
                return 0;
            case 'a':
                show_all = 1;
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: missing string\n");
        return 1;
    }

    const char *str = argv[optind];
    int alpha = 0, digit = 0, other = 0;

    for (const char *p = str; *p; p++) {
        if (isalpha((unsigned char)*p)) alpha++;
        else if (isdigit((unsigned char)*p)) digit++;
        else other++;
    }

    if (show_all) {
        printf("Alpha: %d, Digits: %d, Other: %d\n", alpha, digit, other);
    } else {
        printf("Alpha: %d, Digits: %d\n", alpha, digit);
    }

    return 0;
}
