/* ------------------------- File Information ------------------------- */
/* 
 * File Name: caesar.c
 * Author: Yasser Mahmoud
 * Description: Caesar cipher encryption/decryption
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int key = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"key",  required_argument, 0, 'k'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hk:", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./caesar STRING -k N\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -k N         Shift key (positive or negative)\n");
                return 0;
            case 'k':
                key = atoi(optarg);
                break;
            default:
                fprintf(stderr,"Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr,"Error: missing STRING\n");
        return 1;
    }

    const char *input = argv[optind];
    size_t len = strlen(input);
    char output[len + 1];

    for(size_t i=0; i<len; i++) {
        char c = input[i];
        if(isupper(c)) {
            output[i] = 'A' + ( (c - 'A' + key) % 26 + 26 ) % 26;
        } else if(islower(c)) {
            output[i] = 'a' + ( (c - 'a' + key) % 26 + 26 ) % 26;
        } else {
            output[i] = c;
        }
    }
    output[len] = '\0';
    printf("%s\n", output);

    return 0;
}
