/*    @(#0.1.0)    sha512.h    */

#ifndef _SHA512_H
#define _SHA512_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void sha512_digest(uint8_t * message, size_t length, uint8_t * digest);

#endif