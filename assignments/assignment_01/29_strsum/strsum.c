/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strsum.c
 * Author: Yasser Mahmoud
 * Description: Sum digits in a string, optionally verbose
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
    int verbose = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"verbose", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hv", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./strsum STRING\n");
                printf("Options:\n");
                printf("  -h, --help     Show this help\n");
                printf("  -v, --verbose  Show which digits found\n");
                return 0;
            case 'v':
                verbose = 1;
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
    int sum = 0;

    if (verbose) printf("Digits found: ");
    for (const char *p = str; *p; p++) {
        if (isdigit((unsigned char)*p)) {
            sum += *p - '0';
            if (verbose) printf("%c ", *p);
        }
    }
    if (verbose) printf("\n");

    printf("%d\n", sum);
    return 0;
}
