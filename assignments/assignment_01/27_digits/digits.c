/* ------------------------- File Information ------------------------- */
/* 
 * File Name: digits.c
 * Author: Yasser Mahmoud
 * Description: Count digits in a number or sum them
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int sum_flag = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"sum", no_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hs", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./digits NUMBER\n");
                printf("  ./digits -s NUMBER\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -s, --sum    Sum of digits\n");
                return 0;
            case 's':
                sum_flag = 1;
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: missing number\n");
        return 1;
    }

    const char *num_str = argv[optind];
    int count = 0, total = 0;

    for (int i = 0; num_str[i]; i++) {
        if (isdigit(num_str[i])) {
            count++;
            total += num_str[i] - '0';
        }
    }

    if (sum_flag)
        printf("%d\n", total);
    else
        printf("%d digits\n", count);

    return 0;
}
