/*    @(#0.1.0)    sha224.h    */

#ifndef _SHA224_H
#define _SHA224_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void sha224_digest(uint8_t * message, size_t length, uint8_t * digest);

#endif