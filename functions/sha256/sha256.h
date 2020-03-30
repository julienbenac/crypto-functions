/*    @(#0.1.0)    sha256.h    */

#ifndef _SHA256_H
#define _SHA256_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void sha256_digest(uint8_t * message, size_t length, uint8_t * digest);

#endif