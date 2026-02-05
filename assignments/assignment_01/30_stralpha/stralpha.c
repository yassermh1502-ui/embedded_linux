/* ------------------------- File Information ------------------------- */
/* 
 * File Name: stralpha.c
 * Author: Yasser Mahmoud
 * Description: Count alphabets in a string, with options for upper/lower case
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
    int count_upper = 0;
    int count_lower = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"upper", no_argument, 0, 'u'},
        {"lower", no_argument, 0, 'l'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hul", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./stralpha STRING\n");
                printf("Options:\n");
                printf("  -h, --help    Show this help\n");
                printf("  -u, --upper   Count uppercase letters only\n");
                printf("  -l, --lower   Count lowercase letters only\n");
                return 0;
            case 'u':
                count_upper = 1;
                break;
            case 'l':
                count_lower = 1;
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
    int count = 0;

    for (const char *p = str; *p; p++) {
        if (isalpha((unsigned char)*p)) {
            if (count_upper && isupper((unsigned char)*p)) count++;
            else if (count_lower && islower((unsigned char)*p)) count++;
            else if (!count_upper && !count_lower) count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
