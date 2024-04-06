#ifndef UTILS_H
#define UTILS_H

#define BYTES_PER_LINE 6

#include <stdio.h>
#include <stdint.h>

#include "wolfssl/wolfcrypt/random.h"

void print_bytes(const uint8_t *bytes, int len);
int generate_random_bytes(uint8_t *out, int len);

#endif