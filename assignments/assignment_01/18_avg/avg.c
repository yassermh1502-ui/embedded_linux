/* ------------------------- File Information ------------------------- */
/* 
 * File Name: avg.c
 * Author: Yasser Mahmoud
 * Description: Calculate average of numbers (integer or float)
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int integer_avg = 0;  /* default: floating point */
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"int",  no_argument, 0, 'i'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hi", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./avg [NUMBERS...]\n");
                printf("Options:\n");
                printf("  -h, --help    Show this help\n");
                printf("  -i            Integer average (default is floating point)\n");
                return 0;
            case 'i':
                integer_avg = 1;
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: missing numbers\n");
        return 1;
    }

    int count = argc - optind;
    double sum = 0;

    for (int i = optind; i < argc; i++) {
        sum += atof(argv[i]);
    }

    if (integer_avg) {
        printf("%d\n", (int)(sum / count));
    } else {
        printf("%.2f\n", sum / count);
    }

    return 0;
}
