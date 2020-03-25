/*    @(#0.1.0)    md5.c    */

#include "md5.h"

/* Left rotate macro definition */
#define ROT_LEFT(x, y) (((x) << (y)) | ((x) >> (32 - (y))))

/* Non-linear macros definitions for rounds */
#define F0(x, y, z)    ((z) ^ ((x) & ((y) ^ (z))))
#define F1(x, y, z)    ((y) ^ ((z) & ((x) ^ (y))))
#define F2(x, y, z)    ((x) ^ (y) ^ (z))
#define F3(x, y, z)    ((y) ^ ((x) | (~z)))

#define G0(i)          ((i))
#define G1(i)          ((5 * (i) + 1) % 16)
#define G2(i)          ((3 * (i) + 5) % 16)
#define G3(i)          ((7 * (i)) % 16)

/* Array of binary integer part of the sines of integers (radians) */
const uint32_t K[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

/* Array of the per-round shift amounts */
const size_t S[] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

/* Split a 32-bit value into four 8-bit values */
void to_bytes(uint32_t value, uint8_t * bytes) {
    *(bytes + 0) = (uint8_t) value;
    *(bytes + 1) = (uint8_t) (value >> 8);
    *(bytes + 2) = (uint8_t) (value >> 16);
    *(bytes + 3) = (uint8_t) (value >> 24);
}

/* Recompose four 8-bit values into one 32-bit word */
uint32_t to_word(uint8_t * bytes) {
    return (uint32_t) *(bytes + 0)
        | ((uint32_t) *(bytes + 1) << 8)
        | ((uint32_t) *(bytes + 2) << 16)
        | ((uint32_t) *(bytes + 3) << 24);
}

/* Hash the specified message with the MD5 function */
void md5_digest(uint8_t * message, size_t length, uint8_t * digest) {
    /* Initialize digest variables */
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xefcdab89;
    uint32_t h2 = 0x98badcfe;
    uint32_t h3 = 0x10325476;

    uint32_t words[16];
    uint32_t a, b, c, d, f, g;

    uint8_t * new_message = NULL;

    size_t new_length;
    size_t offset;
    size_t i;

    for (new_length = length + 1 ; new_length % 64 != 448 / 8 ; new_length++);

    new_message = (uint8_t *) malloc(new_length + 8);
    memcpy(new_message, message, length);
    
    /* Append the '1' bit at the end of the new message */
    *(new_message + length) = 0b10000000;
    
    /* Append '0' bits until the end of the new message */
    for (offset = length + 1 ; offset < new_length ; offset++) {
        *(new_message + offset) = 0b0;
    }

    to_bytes(length * 8, new_message + new_length);
    to_bytes(length >> 29, new_message + new_length + 4);

    /* Process the message in successive 512-bit chunks */
    for (offset = 0 ; offset < new_length ; offset += 64) {
        /* Break the current chunk into sixteen 32-bit words */
        for (i = 0 ; i < (sizeof(words) / sizeof(*(words + i))) ; i++) {
            *(words + i) = to_word(new_message + offset + i * 4);
        }

        /* Initialize hash value for the current chunk */
        a = h0;
        b = h1;
        c = h2;
        d = h3;
        
        /* Main loop */
        for (i = 0 ; i < 64 ; i++) {
            if (0 <= i && i <= 15) {
                f = F0(b, c, d);
                g = G0(i);
            } else if (16 <= i && i <= 31) {
                f = F1(b, c, d);
                g = G1(i);
            } else if (32 <= i && i <= 47) {
                f = F2(b, c, d);
                g = G2(i);
            } else if (48 <= i && i <= 64) {
                f = F3(b, c, d);
                g = G3(i);
            }

            f += a + *(K + i) + *(words + g);
            a = d;
            d = c;
            c = b;
            b += ROT_LEFT(f, *(S + i));
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }

    to_bytes(h0, digest);
    to_bytes(h1, digest + 4);
    to_bytes(h2, digest + 8);
    to_bytes(h3, digest + 12);
}