/* ------------------------- File Information ------------------------- */
/* 
 * File Name: perfect.c
 * Author: Yasser Mahmoud
 * Description: Check perfect numbers and list them in a range
 * Date: 01-02-2026
*/

/* ------------------------- Header File Includes ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* ------------------------- Helper Functions ------------------------- */
int is_perfect(int n) {
    int sum = 0;
    for(int i=1;i<n;i++) {
        if(n % i == 0) sum += i;
    }
    return sum == n;
}

/* ------------------------- Main Function ------------------------- */
int main(int argc, char *argv[]) {
    int opt;
    int range_mode = 0, start=0, end=0;
    int verbose = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"range", no_argument, 0, 'r'},
        {"verbose", no_argument, 0, 'v'},
        {0,0,0,0}
    };

    while((opt = getopt_long(argc, argv,"hrv",long_options,NULL))!=-1){
        switch(opt){
            case 'h':
                printf("Usage:\n");
                printf("  ./perfect NUMBER\n");
                printf("  ./perfect -r START END\n\n");
                printf("Options:\n");
                printf("  -h, --help    Show this help\n");
                printf("  -r, --range   Check all numbers in range START END\n");
                printf("  -v, --verbose Show divisors\n");
                return 0;
            case 'r': range_mode=1; break;
            case 'v': verbose=1; break;
            default:
                fprintf(stderr,"Unknown option\n");
                return 1;
        }
    }

    if(range_mode){
        if(optind+1 >= argc){
            fprintf(stderr,"Error: missing range numbers\n");
            return 1;
        }
        start = atoi(argv[optind]);
        end   = atoi(argv[optind+1]);
        for(int i=start;i<=end;i++){
            if(is_perfect(i)){
                if(verbose){
                    printf("%d: divisors = ",i);
                    for(int j=1;j<i;j++){
                        if(i%j==0){
                            printf("%d",j);
                            if(j<i/2) printf("+");
                        }
                    }
                    printf("\n");
                } else {
                    printf("%d\n",i);
                }
            }
        }
    } else {
        if(optind >= argc){
            fprintf(stderr,"Error: missing number\n");
            return 1;
        }
        int num = atoi(argv[optind]);
        if(is_perfect(num)) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}
