/* ------------------------- File Information ------------------------- */
/* 
 * File Name: even.c
 * Author: Yasser Mahmoud
 * Description: Check if a number is even or list evens in a range
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

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
                printf("  ./even NUMBER\n");
                printf("  ./even -r START END\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -r, --range  List evens in range START to END\n");
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
        for (int i = start; i <= end; i++) {
            if (i % 2 == 0) {
                printf("%d", i);
                if (i + 2 <= end) printf(",");
            }
        }
        printf("\n");
    } else {
        if (optind >= argc) {
            fprintf(stderr, "Error: missing number\n");
            return 1;
        }
        int num = atoi(argv[optind]);
        if (num % 2 == 0)
            printf("Yes, even\n");
        else
            printf("No, odd\n");
    }

    return 0;
}
