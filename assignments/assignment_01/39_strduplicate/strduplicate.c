/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strduplicate.c
 * Author: Yasser Mahmoud
 * Description: Find duplicate characters in a string
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
    int list_all = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"all",  no_argument, 0, 'a'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "ha", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./strduplicate STRING [OPTIONS]\n");
                printf("Options:\n");
                printf("  -h          Show this help\n");
                printf("  -a          Show all duplicates\n");
                return 0;
            case 'a':
                list_all = 1;
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
    int count[256] = {0};

    for (size_t i = 0; i < strlen(input); i++) {
        unsigned char c = input[i];
        count[c]++;
    }

    if (list_all) {
        printf("Duplicate characters: ");
        int first = 1;
        for (int i = 0; i < 256; i++) {
            if (count[i] > 1) {
                if (!first) printf(", ");
                printf("%c", i);
                first = 0;
            }
        }
        printf("\n");
    } else {
        for (int i = 0; i < 256; i++) {
            if (count[i] > 1) {
                printf("%c appears %d times\n", i, count[i]);
            }
        }
    }

    return 0;
}
