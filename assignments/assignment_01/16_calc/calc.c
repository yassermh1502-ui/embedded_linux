/* ------------------------- File Information ------------------------- */
/* 
 * File Name: calc.c
 * Author: Yasser Mahmoud
 * Description: Simple calculator supporting add, sub, mul, div, power.
 * Date: 05-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

/* --------------------------- Type Definition --------------------------- */
typedef enum {
    MODE_ADD,
    MODE_SUB,
    MODE_MUL,
    MODE_DIV,
    MODE_POW,
    MODE_NONE
} calc_mode_t;

/* --------------------- Private Function Prototypes --------------------- */
static void print_usage(const char *prog);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {

    int opt;
    calc_mode_t mode = MODE_NONE;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hasmdp", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'a':
                mode = MODE_ADD;
                break;
            case 's':
                mode = MODE_SUB;
                break;
            case 'm':
                mode = MODE_MUL;
                break;
            case 'd':
                mode = MODE_DIV;
                break;
            case 'p':
                mode = MODE_POW;
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (argc - optind < 2) {
        fprintf(stderr, "Error: missing operands\n");
        print_usage(argv[0]);
        return 1;
    }

    double x = atof(argv[optind]);
    double y = atof(argv[optind + 1]);
    double result;

    switch (mode) {
        case MODE_ADD:
            result = x + y;
            printf("%.0f\n", result);
            break;
        case MODE_SUB:
            result = x - y;
            printf("%.0f\n", result);
            break;
        case MODE_MUL:
            result = x * y;
            printf("%.0f\n", result);
            break;
        case MODE_DIV:
            if (y == 0) {
                fprintf(stderr, "Error: division by zero\n");
                return 1;
            }
            result = x / y;
            printf("%.0f\n", result);
            break;
        case MODE_POW:
            result = pow(x, y);
            printf("%.0f\n", result);
            break;
        default:
            fprintf(stderr, "Error: no operation selected\n");
            print_usage(argv[0]);
            return 1;
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s -a X Y    # addition\n", prog);
    printf("  %s -s X Y    # subtraction\n", prog);
    printf("  %s -m X Y    # multiplication\n", prog);
    printf("  %s -d X Y    # division\n", prog);
    printf("  %s -p X Y    # power\n\n", prog);
    printf("Options:\n");
    printf("  -h, --help   Show this help\n");
}
