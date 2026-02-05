/* ------------------------- File Information ------------------------- */
/* 
 * File Name: power.c
 * Author: Yasser Mahmoud
 * Description: Calculate power of a number
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
    int base = -1, exp = -1;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"base", required_argument, 0, 'b'},
        {"exponent", required_argument, 0, 'e'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hb:e:", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./power BASE EXPONENT\n");
                printf("  ./power -b BASE -e EXPONENT\n");
                printf("Options:\n");
                printf("  -h, --help      Show this help\n");
                printf("  -b, --base      Base number\n");
                printf("  -e, --exponent  Exponent\n");
                return 0;
            case 'b':
                base = atoi(optarg);
                break;
            case 'e':
                exp = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    // If positional args were used
    if (base == -1 && exp == -1 && argc - optind >= 2) {
        base = atoi(argv[optind]);
        exp = atoi(argv[optind + 1]);
    }

    if (base == -1 || exp == -1) {
        fprintf(stderr, "Error: missing base or exponent\n");
        return 1;
    }

    long long result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;

    printf("%lld\n", result);
    return 0;
}
