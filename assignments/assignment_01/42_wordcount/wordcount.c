/* ------------------------- File Information ------------------------- */
/* 
 * File Name: wordcount.c
 * Author: Yasser Mahmoud
 * Description: Count words, lines, or characters from a string
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
    enum { MODE_WORDS, MODE_LINES, MODE_CHARS } mode = MODE_WORDS;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"words", no_argument, 0, 'w'},
        {"lines", no_argument, 0, 'l'},
        {"chars", no_argument, 0, 'c'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hwlc", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./wordcount STRING [OPTIONS]\n\n");
                printf("Options:\n");
                printf("  -h          Show this help\n");
                printf("  -w          Count words (default)\n");
                printf("  -l          Count lines\n");
                printf("  -c          Count characters\n");
                return 0;
            case 'w': mode = MODE_WORDS; break;
            case 'l': mode = MODE_LINES; break;
            case 'c': mode = MODE_CHARS; break;
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
    size_t len = strlen(input);
    int count = 0;

    switch (mode) {
        case MODE_CHARS:
            printf("%lu\n", len);
            break;
        case MODE_LINES:
            for (size_t i = 0; i < len; i++)
                if (input[i]=='\n') count++;
            // count line even if no \n at end
            printf("%d\n", count + 1);
            break;
        case MODE_WORDS:
        default: {
            int in_word = 0;
            for (size_t i = 0; i < len; i++) {
                if (input[i]==' ' || input[i]=='\t' || input[i]=='\n') {
                    in_word = 0;
                } else if (!in_word) {
                    in_word = 1;
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }

    return 0;
}
