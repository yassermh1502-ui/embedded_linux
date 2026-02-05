/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strupper.c
 * Author: Yasser Mahmoud
 * Description: A simple program that converts a string or file content to uppercase.
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_STRING,   /* Convert input string (default) */
    MODE_FILE      /* Convert file contents */
} input_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static void print_upper(const char *str);
static void process_file(const char *filename);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt = 0;
    input_mode_t mode = MODE_STRING;   /* default behavior */
    const char *filename = NULL;

    static struct option long_options[] = {
        {"help", no_argument,       0, 'h'},
        {"file", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hf:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'f':
                mode = MODE_FILE;
                filename = optarg;
                break;

            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (mode == MODE_STRING) {
        if (optind >= argc) {
            fprintf(stderr, "Error: missing STRING\n");
            print_usage(argv[0]);
            return 1;
        }
        print_upper(argv[optind]);
    } else {
        if (filename == NULL) {
            fprintf(stderr, "Error: missing FILE\n");
            print_usage(argv[0]);
            return 1;
        }
        process_file(filename);
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING\n", prog);
    printf("  %s -f FILE\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -f, --file     Read input from file\n");
}

static void print_upper(const char *str) {
    while (*str) {
        putchar(toupper((unsigned char)*str));
        str++;
    }
    putchar('\n');
}

static void process_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    int ch;

    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while ((ch = fgetc(fp)) != EOF) {
        putchar(toupper((unsigned char)ch));
    }

    fclose(fp);
}
