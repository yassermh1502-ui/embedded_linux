/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strrepeat.c
 * Author: Yasser Mahmoud
 * Description: Repeat a string N times with optional separator.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);
static void repeat_string(const char *str, int n, const char *sep);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    int n = -1;
    const char *sep = "";  // default: no separator

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hn:s:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;

            case 'n':
                n = atoi(optarg);
                break;

            case 's':
                sep = optarg;
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

    if (n <= 0) {
        fprintf(stderr, "Error: number of repetitions (-n) must be > 0\n");
        print_usage(argv[0]);
        return 1;
    }

    const char *input = argv[optind];
    repeat_string(input, n, sep);

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s STRING -n N             # repeat STRING N times\n", prog);
    printf("  %s STRING -n N -s SEP      # repeat STRING N times with separator SEP\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -n N           Number of repetitions (required)\n");
    printf("  -s SEP         Separator between repetitions (optional)\n");
}

static void repeat_string(const char *str, int n, const char *sep) {
    for (int i = 0; i < n; i++) {
        printf("%s", str);
        if (i < n - 1) {
            printf("%s", sep);
        }
    }
    printf("\n");
}
