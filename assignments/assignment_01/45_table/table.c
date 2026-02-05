/* ------------------------- File Information ------------------------- */
/* 
 * File Name: table.c
 * Author: Yasser Mahmoud
 * Description: Print multiplication table
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int num = 0;
    int rows = 10;
    int range_start = 0, range_end = 0;
    int range_mode = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"range", no_argument, 0, 'r'},
        {"rows", no_argument, 0, 'n'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hrn:", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./table NUMBER [OPTIONS]\n");
                printf("  ./table -r START END\n\n");
                printf("Options:\n");
                printf("  -h          Show help\n");
                printf("  -n ROWS     Number of rows (default 10)\n");
                printf("  -r START END Use range from START to END\n");
                return 0;
            case 'n': rows = atoi(optarg); break;
            case 'r': range_mode = 1; break;
            default:
                fprintf(stderr,"Unknown option\n");
                return 1;
        }
    }

    if (range_mode) {
        if (optind + 1 >= argc) {
            fprintf(stderr,"Error: missing START or END for range\n");
            return 1;
        }
        range_start = atoi(argv[optind]);
        range_end   = atoi(argv[optind+1]);
        for (int i = range_start; i <= range_end; i++) {
            for (int j = 1; j <= 10; j++) {
                printf("%dx%d=%d\n", i, j, i*j);
            }
        }
    } else {
        if (optind >= argc) {
            fprintf(stderr,"Error: missing NUMBER\n");
            return 1;
        }
        num = atoi(argv[optind]);
        for (int i = 1; i <= rows; i++) {
            printf("%dx%d=%d\n", num, i, num*i);
        }
    }

    return 0;
}
