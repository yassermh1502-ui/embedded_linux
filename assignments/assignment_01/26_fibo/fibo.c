/* ------------------------- File Information ------------------------- */
/* 
 * File Name: fibo.c
 * Author: Yasser Mahmoud
 * Description: Print Fibonacci sequence up to N terms
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int n = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"number", required_argument, 0, 'n'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hn:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./fibo N\n");
                printf("  ./fibo -n N\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -n N         Number of terms\n");
                return 0;
            case 'n':
                n = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (optind < argc) {
        n = atoi(argv[optind]);
    }

    if (n <= 0) {
        fprintf(stderr, "Error: missing or invalid number of terms\n");
        return 1;
    }

    long long a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%lld", a);
        long long tmp = a + b;
        a = b;
        b = tmp;
    }
    printf("\n");
    return 0;
}
