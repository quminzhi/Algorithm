#include "bit.hpp"

/**
 * @brief the program calculates the number of 1's bit in a binary number
 *
 * bottom to top algorithm:
 * 1. calculate 1's bit in all 2-bit range with mask
 *   0b0101 0101 ... 0101 0101 = 0x5555 5555
 * 2. calculate 1's bit in all 4-bit range with mask
 *   0b0011 0011 ... 0011 0011 = 0x3333 3333
 * 3. ... in all 8-bit range with mask 0b0000 1111 ... 0000 1111 = 0x0F0F 0F0F
 * 4. ... in all 16-bit range with mask 0b 0000 0000 1111 1111 ... = 0x00FF 00FF
 * 5. ... in all 32-bit range with mask 0b 0000 ...1111 = 0x0000 FFFF
 *
 * x := x & mask + (x >> half range) & mask
 *
 * @param num
 * @return int
 */
int BitCounter(int num) {
    vector<int> mask = {0x55555555, 0x33333333, 0x0f0f0f0f, 0x00ff00ff, 0x0000ffff};
    int shift = 4;   // 2^4 = 16, it will be shifted at most 16 bit in the last round for
                     // the 32 bit number
    for (int i = 0; i <= shift; i++) {
        int highbits = num >> (1 << i);
        int low = num & mask[i];
        int high = highbits & mask[i];
        num = low + high;
    }

    return num;
}