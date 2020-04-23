/*    @(#0.1.0)    sha224_test.c    */

/*
 * gcc -c sha224.c
 * gcc sha224.o sha224_test.c -o sha224_test
 */

#include <stdio.h>

#include "sha224.h"
 
/* Test working only on the first argument */
int main(int argc, char * argv[]) {
    uint8_t digest[28];
    size_t i;

    if (argc != 2) {
        printf("Usage : sha224_test <your_word>");
        return 1;
    }

    sha224_digest(*(argv + 1), strlen(*(argv + 1)), digest);

    printf("Initial message : %s\n", *(argv + 1));
    printf("Digest : ");

    for (i = 0 ; i < (sizeof(digest) / sizeof(*(digest + i))) ; i++) {
        printf("%2.2x", *(digest + i));
    }

    return 0;
}