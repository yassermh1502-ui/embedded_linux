/* ------------------------- File Information ------------------------- */
/* 
 * File Name: numtostr.c
 * Author: Yasser Mahmoud
 * Description: Convert a number to words
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

/* ------------------------- Word Tables ------------------------- */
const char *digits[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
const char *units[] = {"","one","two","three","four","five","six","seven","eight","nine"};
const char *teens[] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
const char *tens[] = {"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

/* ------------------------- Function Prototypes ------------------------- */
void print_digit_words(const char *num);
void print_full_words(int num);
void number_to_words(int num);

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int full_words = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"words", no_argument, 0, 'w'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "hw", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("Usage:\n");
                printf("  ./numtostr NUMBER\n");
                printf("  ./numtostr -w NUMBER\n");
                printf("Options:\n");
                printf("  -h, --help   Show this help\n");
                printf("  -w, --words  Full words (not digit by digit)\n");
                return 0;
            case 'w':
                full_words = 1;
                break;
            default:
                fprintf(stderr,"Unknown option\n");
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr,"Error: missing NUMBER\n");
        return 1;
    }

    const char *num_str = argv[optind];
    if (full_words) {
        int num = atoi(num_str);
        if(num < 0) {
            printf("minus ");
            num = -num;
        }
        print_full_words(num);
        printf("\n");
    } else {
        print_digit_words(num_str);
        printf("\n");
    }

    return 0;
}

/* ------------------------- Private Functions ------------------------- */

void print_digit_words(const char *num) {
    for(size_t i=0;i<strlen(num);i++) {
        if(!isdigit(num[i])) continue;
        if(i>0) printf(" ");
        printf("%s", digits[num[i]-'0']);
    }
}

void print_full_words(int num) {
    if(num >= 100) {
        printf("%s hundred", units[num/100]);
        num %= 100;
        if(num) printf(" ");
    }
    if(num >= 20) {
        printf("%s", tens[num/10]);
        if(num%10) printf(" %s", units[num%10]);
    } else if(num >= 10) {
        printf("%s", teens[num-10]);
    } else if(num > 0 || num==0) {
        printf("%s", units[num]);
    }
}
