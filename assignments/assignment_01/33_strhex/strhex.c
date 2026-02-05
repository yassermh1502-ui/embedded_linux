/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strhex.c
 * Author: Yasser Mahmoud
 * Description: Convert string to hex or decode hex to string
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
                printf("  ./strhex STRING\n");
                printf("  ./strhex -d HEX_STRING\n\n");
                printf("Options:\n");
                printf("  -h, --help    Show this help\n");
                printf("  -d, --decode  Decode hex string to normal string\n");
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
        // Decode hex string
        char *hex_str = argv[optind];
        size_t len = strlen(hex_str);
        for (size_t i = 0; i < len; i += 2) {
            char byte[3] = { hex_str[i], hex_str[i+1], 0 };
            printf("%c", (char)strtol(byte, NULL, 16));
        }
        printf("\n");
    } else {
        // Encode string to hex
        const char *str = argv[optind];
        for (const char *p = str; *p; p++) {
            printf("%02X", (unsigned char)*p);
            if (*(p+1)) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
