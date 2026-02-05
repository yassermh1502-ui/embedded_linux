/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strlast.c
 * Author: Yasser Mahmoud
 * Description: Extract last N characters or words from a string
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
    int n_chars = -1;
    int n_words = -1;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"chars", required_argument, 0, 'n'},
        {"words", required_argument, 0, 'w'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hn:w:", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./strlast STRING [OPTIONS]\n");
                printf("Options:\n");
                printf("  -h          Show this help\n");
                printf("  -n N        Last N characters\n");
                printf("  -w N        Last N words\n");
                return 0;
            case 'n':
                n_chars = atoi(optarg);
                break;
            case 'w':
                n_words = atoi(optarg);
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
    size_t len = strlen(input);

    if (n_chars > 0) {
        if ((size_t)n_chars > len) n_chars = len;
        printf("%.*s\n", n_chars, input + len - n_chars);
    } else if (n_words > 0) {
        // Count total words first
        int total_words = 0;
        int in_word = 0;
        for (size_t i = 0; i < len; i++) {
            if (input[i]==' ' || input[i]=='\t' || input[i]=='\n') {
                in_word = 0;
            } else if (!in_word) {
                in_word = 1;
                total_words++;
            }
        }

        // Print last N words
        int start_word = total_words - n_words;
        if (start_word < 0) start_word = 0;
        int word_count = 0;
        in_word = 0;
        for (size_t i = 0; i < len; i++) {
            if (input[i]==' ' || input[i]=='\t' || input[i]=='\n') {
                if (word_count >= start_word)
                    putchar(input[i]);
                in_word = 0;
            } else {
                if (!in_word) {
                    in_word = 1;
                    word_count++;
                }
                if (word_count > start_word)
                    putchar(input[i]);
            }
        }
        putchar('\n');
    } else {
        fprintf(stderr,"Error: specify -n or -w\n");
        return 1;
    }

    return 0;
}
