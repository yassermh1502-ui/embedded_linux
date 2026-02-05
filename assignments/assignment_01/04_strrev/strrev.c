/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strrev.c
 * Author: Yasser Mahmoud
 * Description: A simple program that reverses a string or reverses word order.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_CHARS,   /* Reverse characters (default) */
    MODE_WORDS    /* Reverse word order */
} reverse_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static void reverse_string(const char *str);
static void reverse_words(const char *str);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    reverse_mode_t mode = MODE_CHARS;   /* default behavior */

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"words", no_argument, 0, 'w'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hw", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'w':
                mode = MODE_WORDS;
                break;

            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: missing STRING\n");
        print_usage(argv[0]);
        return 1;
    }

    const char *input = argv[optind];

    switch (mode) {
        case MODE_CHARS:
            reverse_string(input);
            break;

        case MODE_WORDS:
            reverse_words(input);
            break;

        default:
            fprintf(stderr, "Error: unknown mode\n");
            return 1;
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING\n", prog);
    printf("  %s -w STRING\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -w             Reverse word order\n");
}

static void reverse_string(const char *str) {
    size_t len = strlen(str);
    for (int i = (int)len - 1; i >= 0; i--) {
        putchar(str[i]);
    }
    putchar('\n');
}

static void reverse_words(const char *str) {
    // Count words
    const char *ptr = str;
    int word_count = 0;
    while (*ptr) {
        if ((*ptr != ' ') && (*(ptr+1) == ' ' || *(ptr+1) == '\0')) {
            word_count++;
        }
        ptr++;
    }

    // Store word start pointers
    const char *words[word_count];
    int lengths[word_count];

    int index = 0;
    const char *start = NULL;
    ptr = str;
    while (*ptr) {
        if (*ptr != ' ' && start == NULL) {
            start = ptr;
        }
        if ((start != NULL) && (*ptr == ' ' || *(ptr+1) == '\0')) {
            words[index] = start;
            if (*ptr == ' ')
                lengths[index] = ptr - start;
            else
                lengths[index] = ptr - start + 1;
            index++;
            start = NULL;
        }
        ptr++;
    }

    // Print words in reverse order
    for (int i = word_count - 1; i >= 0; i--) {
        fwrite(words[i], sizeof(char), lengths[i], stdout);
        if (i > 0) putchar(' ');
    }
    putchar('\n');
}
