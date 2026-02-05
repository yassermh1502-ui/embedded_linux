/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strtonum.c
 * Author: Yasser Mahmoud
 * Description: Extract numbers from a string
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int sum_flag = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"sum",  no_argument, 0, 's'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hs", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./strtonum STRING\n");
                printf("  ./strtonum -s STRING\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -s, --sum    Sum extracted numbers\n");
                return 0;
            case 's':
                sum_flag = 1;
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

    const char *str = argv[optind];
    int sum = 0;
    int found = 0;
    char buffer[64];
    int buf_index = 0;

    for(size_t i=0; i<=strlen(str); i++) {
        if(isdigit(str[i]) || str[i]=='.') {
            buffer[buf_index++] = str[i];
        } else {
            if(buf_index>0) {
                buffer[buf_index] = '\0';
                if(sum_flag) {
                    sum += atof(buffer);
                } else {
                    if(found) printf(", ");
                    printf("%s", buffer);
                    found = 1;
                }
                buf_index = 0;
            }
        }
    }

    if(sum_flag) {
        printf("%g", sum);
    } else {
        printf("\n");
    }

    return 0;
}
