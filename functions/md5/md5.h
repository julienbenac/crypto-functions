/*    @(#0.1.0)    md5.h    */

#ifndef _MD5_H
#define _MD5_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void md5_digest(uint8_t * message, size_t length, uint8_t * digest);

#endif