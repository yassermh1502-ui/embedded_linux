/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strremove.c
 * Author: Yasser Mahmoud
 * Description: Remove character from string
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
    char remove_first_only = 0;
    char target = '\0';

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"first", no_argument, 0, 'f'},
        {"char", required_argument, 0, 'c'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hfc:", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./strremove STRING -c CHAR [OPTIONS]\n\n");
                printf("Options:\n");
                printf("  -h          Show this help\n");
                printf("  -c CHAR     Character to remove\n");
                printf("  -f          Remove first occurrence only\n");
                return 0;
            case 'f': remove_first_only = 1; break;
            case 'c': target = optarg[0]; break;
            default:
                fprintf(stderr,"Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr,"Error: missing STRING\n");
        return 1;
    }

    if (target == '\0') {
        fprintf(stderr,"Error: missing -c CHAR\n");
        return 1;
    }

    const char *input = argv[optind];
    size_t len = strlen(input);
    char output[len + 1];
    size_t j = 0;
    int removed = 0;

    for (size_t i = 0; i < len; i++) {
        if (input[i] == target && (!remove_first_only || removed==0)) {
            removed++;
            continue;
        }
        output[j++] = input[i];
    }
    output[j] = '\0';
    printf("%s\n", output);

    return 0;
}
