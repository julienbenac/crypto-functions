/*    @(#0.1.0)    sha256_test.c    */

/*
 * gcc -c sha256.c
 * gcc sha256.o sha256_test.c -o sha256_test
 */

#include <stdio.h>

#include "sha256.h"
 
/* Test working only on the first argument */
int main(int argc, char * argv[]) {
    uint8_t digest[32];
    size_t i;

    if (argc != 2) {
        printf("Usage : sha256_test <your_word>");
        return 1;
    }

    sha256_digest(*(argv + 1), strlen(*(argv + 1)), digest);

    printf("Initial message : %s\n", *(argv + 1));
    printf("Digest : ");

    for (i = 0 ; i < (sizeof(digest) / sizeof(*(digest + i))) ; i++) {
        printf("%2.2x", *(digest + i));
    }

    return 0;
}