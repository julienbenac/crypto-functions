/*    @(#0.1.0)    sha512_test.c    */

/*
 * gcc -c sha512.c
 * gcc sha512.o sha512_test.c -o sha512_test
 */

#include <stdio.h>

#include "sha512.h"

/* Test working only on the first argument */
int main(int argc, char * argv[]) {
    uint8_t digest[64];
    size_t i;

    if (argc != 2) {
        printf("Usage : sha512_test <your_word>");
        return 1;
    }

    sha512_digest(*(argv + 1), strlen(*(argv + 1)), digest);

    printf("Initial message : %s\n", *(argv + 1));
    printf("Digest : ");

    for (i = 0 ; i < (sizeof(digest) / sizeof(*(digest + i))) ; i++) {
        printf("%2.2x", *(digest + i));
    }

    return 0;
}