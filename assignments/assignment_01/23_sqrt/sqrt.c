/* ------------------------- File Information ------------------------- */
/* 
 * File Name: sqrt.c
 * Author: Yasser Mahmoud
 * Description: Calculate square root of a number
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int precision = 0;
    double number = -1;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"precision", required_argument, 0, 'p'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hp:", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./sqrt NUMBER\n");
                printf("  ./sqrt -p PRECISION NUMBER\n");
                printf("Options:\n");
                printf("  -h, --help      Show this help\n");
                printf("  -p, --precision Decimal precision\n");
                return 0;
            case 'p':
                precision = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (optind < argc) {
        number = atof(argv[optind]);
    }

    if (number < 0) {
        fprintf(stderr, "Error: missing or invalid number\n");
        return 1;
    }

    double result = sqrt(number);

    if (precision > 0)
        printf("%.*f\n", precision, result);
    else
        printf("%.0f\n", result);

    return 0;
}
