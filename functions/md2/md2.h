/*    @(#0.1.0)    md2.h    */

#ifndef _MD2_H
#define _MD2_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void md2_digest(uint8_t * message, size_t length, uint8_t * digest);

#endif