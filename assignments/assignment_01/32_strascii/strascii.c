/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strascii.c
 * Author: Yasser Mahmoud
 * Description: Show ASCII values of a string or decode ASCII value to character
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
    int decode = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"decode", no_argument, 0, 'd'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hd", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./strascii STRING\n");
                printf("  ./strascii -d ASCII_VALUE\n\n");
                printf("Options:\n");
                printf("  -h, --help    Show this help\n");
                printf("  -d, --decode  Decode ASCII value to character\n");
                return 0;
            case 'd':
                decode = 1;
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: missing argument\n");
        return 1;
    }

    if (decode) {
        int val = atoi(argv[optind]);
        printf("%c\n", val);
    } else {
        const char *str = argv[optind];
        for (const char *p = str; *p; p++) {
            printf("%c=%d", *p, (unsigned char)*p);
            if (*(p+1)) printf(", ");
        }
        printf("\n");
    }

    return 0;
}
