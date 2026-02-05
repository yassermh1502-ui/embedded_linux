/* ------------------------- File Information ------------------------- */
/* 
 * File Name: max.c
 * Author: Yasser Mahmoud
 * Description: Find maximum number from input or file
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"file", required_argument, 0, 'f'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hf:", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./max [NUMBERS...]\n");
                printf("  ./max -f FILE\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -f FILE      Read numbers from file\n");
                return 0;
            case 'f':
                filename = optarg;
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                return 1;
        }
    }

    int max_found = 0;
    int first = 1;

    if (filename) {
        FILE *fp = fopen(filename, "r");
        if (!fp) {
            fprintf(stderr, "Error opening file\n");
            return 1;
        }
        int num;
        while (fscanf(fp, "%d", &num) == 1) {
            if (first) { max_found = num; first = 0; }
            else if (num > max_found) max_found = num;
        }
        fclose(fp);
    } else {
        if (optind >= argc) {
            fprintf(stderr, "Error: missing numbers\n");
            return 1;
        }
        for (int i = optind; i < argc; i++) {
            int num = atoi(argv[i]);
            if (first) { max_found = num; first = 0; }
            else if (num > max_found) max_found = num;
        }
    }

    printf("%d\n", max_found);
    return 0;
}
