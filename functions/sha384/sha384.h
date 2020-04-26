/*    @(#0.1.0)    sha384.h    */

#ifndef _SHA384_H
#define _SHA384_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void sha384_digest(uint8_t * message, size_t length, uint8_t * digest);

#endif