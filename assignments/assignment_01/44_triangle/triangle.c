/* ------------------------- File Information ------------------------- */
/* 
 * File Name: triangle.c
 * Author: Yasser Mahmoud
 * Description: Print number triangles
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
    int right_aligned = 0;
    int inverted = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"right", no_argument, 0, 'r'},
        {"inverted", no_argument, 0, 'i'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hri", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./triangle N [OPTIONS]\n\n");
                printf("Options:\n");
                printf("  -h         Show this help\n");
                printf("  -r         Right aligned triangle\n");
                printf("  -i         Inverted triangle\n");
                return 0;
            case 'r': right_aligned = 1; break;
            case 'i': inverted = 1; break;
            default:
                fprintf(stderr,"Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr,"Error: missing number N\n");
        return 1;
    }

    n = atoi(argv[optind]);
    if (n <= 0) {
        fprintf(stderr,"Error: N must be positive\n");
        return 1;
    }

    if (inverted) {
        for (int i = n; i >= 1; i--) {
            if (right_aligned)
                for (int s = 0; s < n-i; s++) printf(" ");
            for (int j = 1; j <= i; j++) printf("%d ", j);
            printf("\n");
        }
    } else {
        for (int i = 1; i <= n; i++) {
            if (right_aligned)
                for (int s = 0; s < n-i; s++) printf(" ");
            for (int j = 1; j <= i; j++) printf("%d ", j);
            printf("\n");
        }
    }

    return 0;
}
