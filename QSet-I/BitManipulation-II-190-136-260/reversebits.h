#ifndef REVERSEBITS_H
#define REVERSEBITS_H

#include <stdint.h>

/**
 * Reverse bits of a given 32 bits unsigned integer.
 *
 * Input: n = 00000010100101000001111010011100
 * Output:    964176192 (00111001011110000010100101000000)
 *
 * Constrains: The input must be a binary string of length 32.
 */

uint32_t reverseBits_sol1(uint32_t n);
uint32_t reverseBits_sol2(uint32_t n);
uint32_t reverseBits_sol3(uint32_t n);

#endif // REVERSEBITS_H
