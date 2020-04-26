/*    @(#0.1.0)    sha384_test.c    */

/*
 * gcc -c sha384.c
 * gcc sha384.o sha384_test.c -o sha384_test
 */

#include <stdio.h>

#include "sha384.h"
 
/* Test working only on the first argument */
int main(int argc, char * argv[]) {
    uint8_t digest[48];
    size_t i;

    if (argc != 2) {
        printf("Usage : sha384_test <your_word>");
        return 1;
    }

    sha384_digest(*(argv + 1), strlen(*(argv + 1)), digest);

    printf("Initial message : %s\n", *(argv + 1));
    printf("Digest : ");

    for (i = 0 ; i < (sizeof(digest) / sizeof(*(digest + i))) ; i++) {
        printf("%2.2x", *(digest + i));
    }

    return 0;
}