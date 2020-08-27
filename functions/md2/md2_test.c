/*    @(#0.1.0)    md2_test.c    */

/*
 * gcc -c md2.c
 * gcc md2.o md2_test.c -o md2_test
 */

#include <stdio.h>

#include "md2.h"

/* Test working only on the first argument */
int main(int argc, char * argv[]) {
    uint8_t digest[16];
    size_t i;
    
    if (argc != 2) {
        printf("Usage : md2_test <your_word>");
        return 1;
    }
        
    md2_digest(*(argv + 1), strlen(*(argv + 1)), digest);

    printf("Initial message : %s\n", *(argv + 1));
    printf("Digest : ");
    
    for (i = 0 ; i < (sizeof(digest) / sizeof(*(digest + i))) ; i++) {
        printf("%2.2x", *(digest + i));
    }

    return 0;
}