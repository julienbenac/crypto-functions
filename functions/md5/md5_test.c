/*    @(#0.1.0)    md5_test.c    */

/*
 * gcc -c md5.c
 * gcc md5.o md5_test.c -o md5_test
 */

#include <stdio.h>

#include "md5.h"

/* Test working only on the first argument */
int main(int argc, char * argv[]) {
    uint8_t digest[16];
    size_t i;
    
    if (argc != 2) {
        printf("Usage : md5_test <your_word>");
        return 1;
    }
        
    md5_digest(*(argv + 1), strlen(*(argv + 1)), digest);

    printf("Initial message : %s\n", *(argv + 1));
    printf("Digest : ");
    
    for (i = 0 ; i < (sizeof(digest) / sizeof(*(digest + i))) ; i++) {
        printf("%2.2x", *(digest + i));
    }

    return 0;
}