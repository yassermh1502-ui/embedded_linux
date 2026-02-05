/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strfirst.c
 * Author: Yasser Mahmoud
 * Description: Extract first N characters or words from a string
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
                printf("  ./strfirst STRING [OPTIONS]\n");
                printf("Options:\n");
                printf("  -h          Show this help\n");
                printf("  -n N        First N characters\n");
                printf("  -w N        First N words\n");
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

    if (n_chars > 0) {
        for (int i = 0; i < n_chars && input[i]; i++)
            putchar(input[i]);
        putchar('\n');
    } else if (n_words > 0) {
        int count = 0;
        int in_word = 0;
        for (size_t i = 0; i < strlen(input); i++) {
            if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') {
                in_word = 0;
                putchar(input[i]);
            } else {
                if (!in_word) {
                    count++;
                    in_word = 1;
                }
                if (count <= n_words)
                    putchar(input[i]);
                else
                    break;
            }
        }
        putchar('\n');
    } else {
        fprintf(stderr,"Error: specify -n or -w\n");
        return 1;
    }

    return 0;
}
