/* ------------------------- File Information ------------------------- */
/* 
 * File Name: sum.c
 * Author: Yasser Mahmoud
 * Description: Sum numbers from command line or file
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_CMD,   /* Sum from command line arguments */
    MODE_FILE   /* Sum from file */
} sum_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    sum_mode_t mode = MODE_CMD;
    char *filename = NULL;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
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

    long sum = 0;

    if (mode == MODE_FILE) {
        if (!filename) {
            fprintf(stderr, "Error: missing filename\n");
            return 1;
        }
        FILE *fp = fopen(filename, "r");
        if (!fp) {
            perror("Error opening file");
            return 1;
        }
        long num;
        while (fscanf(fp, "%ld", &num) == 1) {
            sum += num;
        }
        fclose(fp);
    } else {
        if (optind >= argc) {
            fprintf(stderr, "Error: missing numbers\n");
            return 1;
        }
        for (int i = optind; i < argc; i++) {
            sum += atol(argv[i]);
        }
    }

    printf("%ld\n", sum);
    return 0;
}

/* ------------------------- Private Functions ------------------------- */
static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s [NUMBERS...]\n", prog);
    printf("  %s -f FILE\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help   Show this help\n");
    printf("  -f FILE      Read numbers from file\n");
}
