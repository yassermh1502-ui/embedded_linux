/* ------------------------- File Information ------------------------- */
/* 
 * File Name: strfreq.c
 * Author: Yasser Mahmoud
 * Description: Count character frequency in a string
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
    int sort_char = 0;
    int sort_freq = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"sort-char", no_argument, 0, 's'},
        {"sort-freq", no_argument, 0, 'f'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hsf", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./strfreq STRING [OPTIONS]\n");
                printf("Options:\n");
                printf("  -h          Show this help\n");
                printf("  -s          Sort by character\n");
                printf("  -f          Sort by frequency\n");
                return 0;
            case 's':
                sort_char = 1;
                break;
            case 'f':
                sort_freq = 1;
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
    int freq[256] = {0};

    for(size_t i=0; i<strlen(input); i++) {
        unsigned char c = input[i];
        freq[c]++;
    }

    // Print frequency array
    if(sort_char) {
        for(int i=0;i<256;i++) {
            if(freq[i] > 0)
                printf("%c:%d\n", i, freq[i]);
        }
    } else if(sort_freq) {
        // simple bubble sort of 256 entries
        struct {
            char c;
            int f;
        } arr[256];
        int n = 0;
        for(int i=0;i<256;i++) {
            if(freq[i]>0){
                arr[n].c = i;
                arr[n].f = freq[i];
                n++;
            }
        }
        // sort by frequency ascending
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                if(arr[i].f > arr[j].f){
                    int tmpf = arr[i].f; char tmpc = arr[i].c;
                    arr[i].f = arr[j].f; arr[i].c = arr[j].c;
                    arr[j].f = tmpf; arr[j].c = tmpc;
                }
            }
        }
        for(int i=0;i<n;i++){
            printf("%c:%d\n", arr[i].c, arr[i].f);
        }
    } else {
        // default order of appearance
        int printed[256] = {0};
        for(size_t i=0;i<strlen(input);i++){
            unsigned char c = input[i];
            if(!printed[c]){
                printf("%c:%d\n", c, freq[c]);
                printed[c] = 1;
            }
        }
    }

    return 0;
}
