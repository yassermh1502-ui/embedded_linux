/* ------------------------- File Information ------------------------- */
/* 
 * File Name: prime.c
 * Author: Yasser Mahmoud
 * Description: Check if a number is prime or list primes in a range
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

/* ------------------------- Helper Functions ------------------------- */
int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0) return 0;
    return 1;
}

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int range_flag = 0;
    int start = 0, end = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"range", no_argument, 0, 'r'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hr", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./prime NUMBER\n");
                printf("  ./prime -r START END\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -r, --range  List primes in range START to END\n");
                return 0;
            case 'r':
                range_flag = 1;
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    if (range_flag) {
        if (optind + 1 >= argc) {
            fprintf(stderr, "Error: missing range numbers\n");
            return 1;
        }
        start = atoi(argv[optind]);
        end = atoi(argv[optind + 1]);
        int first = 1;
        for (int i = start; i <= end; i++) {
            if (is_prime(i)) {
                if (!first) printf(",");
                printf("%d", i);
                first = 0;
            }
        }
        printf("\n");
    } else {
        if (optind >= argc) {
            fprintf(stderr, "Error: missing number\n");
            return 1;
        }
        int num = atoi(argv[optind]);
        if (is_prime(num))
            printf("Yes, prime\n");
        else
            printf("Not prime\n");
    }

    return 0;
}
