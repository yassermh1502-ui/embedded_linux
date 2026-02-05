/* ------------------------- File Information ------------------------- */
/* 
 * File Name: reverse.c
 * Author: Yasser Mahmoud
 * Description: Reverse a number or check if it is palindrome
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int check_palindrome = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"check", no_argument, 0, 'c'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hc", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./reverse NUMBER\n");
                printf("  ./reverse -c NUMBER\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -c, --check  Check if palindrome\n");
                return 0;
            case 'c':
                check_palindrome = 1;
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
    int len = strlen(num_str);
    char reversed[100];

    for (int i = 0; i < len; i++) {
        reversed[i] = num_str[len - 1 - i];
    }
    reversed[len] = '\0';

    if (check_palindrome) {
        if (strcmp(num_str, reversed) == 0)
            printf("Yes\n");
        else
            printf("No\n");
    } else {
        printf("%s\n", reversed);
    }

    return 0;
}
