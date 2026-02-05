/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strunique.c
 * Author: Yasser Mahmoud
 * Description: Count unique characters in a string
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
    int list_unique = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"list", no_argument, 0, 'l'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hl", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./strunique STRING [OPTIONS]\n");
                printf("Options:\n");
                printf("  -h          Show this help\n");
                printf("  -l          List unique characters\n");
                return 0;
            case 'l':
                list_unique = 1;
                break;
            default:
                fprintf(stderr,"Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr,"Error: missing STRING\n");
        return 1;
    }

    const char *input = argv[optind];
    int seen[256] = {0};
    int unique_count = 0;

    for (size_t i = 0; i < strlen(input); i++) {
        unsigned char c = input[i];
        if (!seen[c]) {
            seen[c] = 1;
            unique_count++;
        }
    }

    if (list_unique) {
        printf("Unique characters: ");
        int first = 1;
        for (int i = 0; i < 256; i++) {
            if (seen[i]) {
                if (!first) printf(", ");
                printf("%c", i);
                first = 0;
            }
        }
        printf("\n");
    } else {
        printf("%d unique chars\n", unique_count);
    }

    return 0;
}
