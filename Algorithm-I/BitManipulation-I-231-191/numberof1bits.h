#ifndef NUMBEROF1BITS_H
#define NUMBEROF1BITS_H

#include <stdint.h>
using namespace std;

/**
 * Write a function that takes an unsigned integer and returns the number of '1' bits
 * it has (also known as the Hamming weight).
 *
 * Input: n = 00000000000000000000000000001011 (11)
 * Output: 3
 *
 * Constrains:
 * The input must be a binary string of length 32.
 */

int hammingWeight_sol1(uint32_t n);

#endif // NUMBEROF1BITS_H
