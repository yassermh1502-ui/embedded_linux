/* ------------------------- File Information ------------------------- */
/* 
 * File Name: factorial.c
 * Author: Yasser Mahmoud
 * Description: Calculate factorial iteratively or recursively
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* --------------------- Function Prototypes --------------------- */
long long factorial_iter(int n);
long long factorial_rec(int n);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int recursive = 0;  // default iterative

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"recursive", no_argument, 0, 'r'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hr", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./factorial [NUM]\n");
                printf("  ./factorial -r [NUM]\n");
                printf("Options:\n");
                printf("  -h, --help      Show this help\n");
                printf("  -r, --recursive Use recursive algorithm\n");
                return 0;
            case 'r':
                recursive = 1;
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: missing number\n");
        return 1;
    }

    int num = atoi(argv[optind]);
    if (num < 0) {
        fprintf(stderr, "Error: negative number\n");
        return 1;
    }

    long long result;
    if (recursive)
        result = factorial_rec(num);
    else
        result = factorial_iter(num);

    printf("%lld\n", result);
    return 0;
}

/* ------------------------- Functions ------------------------- */
long long factorial_iter(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}

long long factorial_rec(int n) {
    if (n <= 1) return 1;
    return n * factorial_rec(n - 1);
}
