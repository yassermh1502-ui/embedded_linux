/* ------------------------- File Information ------------------------- */
/* 
 * File Name: pattern.c
 * Author: Yasser Mahmoud
 * Description: Print patterns (triangle, pyramid, diamond)
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    char symbol = '*';
    int rows = 5;
    char pattern_type[16] = "triangle";  // default

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hs:n:p:", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./pattern [OPTIONS]\n\n");
                printf("Options:\n");
                printf("  -h          Show help\n");
                printf("  -s SYMBOL   Symbol to use (default *)\n");
                printf("  -n ROWS     Number of rows (default 5)\n");
                printf("  -p TYPE     Pattern type: triangle, pyramid, diamond\n");
                return 0;
            case 's': symbol = optarg[0]; break;
            case 'n': rows = atoi(optarg); break;
            case 'p': strncpy(pattern_type, optarg, sizeof(pattern_type)-1); break;
            default:
                fprintf(stderr,"Unknown option\n");
                return 1;
        }
    }

    if (strcmp(pattern_type,"triangle")==0) {
        for (int i = 1; i <= rows; i++) {
            for (int j = 0; j < i; j++) printf("%c", symbol);
            printf("\n");
        }
    } else if (strcmp(pattern_type,"pyramid")==0) {
        for (int i = 1; i <= rows; i++) {
            for (int j = 0; j < rows-i; j++) printf(" ");
            for (int j = 0; j < 2*i-1; j++) printf("%c", symbol);
            printf("\n");
        }
    } else if (strcmp(pattern_type,"diamond")==0) {
        // Upper pyramid
        for (int i = 1; i <= rows; i++) {
            for (int j = 0; j < rows-i; j++) printf(" ");
            for (int j = 0; j < 2*i-1; j++) printf("%c", symbol);
            printf("\n");
        }
        // Lower inverted pyramid
        for (int i = rows-1; i >= 1; i--) {
            for (int j = 0; j < rows-i; j++) printf(" ");
            for (int j = 0; j < 2*i-1; j++) printf("%c", symbol);
            printf("\n");
        }
    } else {
        fprintf(stderr,"Unknown pattern type: %s\n", pattern_type);
        return 1;
    }

    return 0;
}
