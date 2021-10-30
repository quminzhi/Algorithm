#include "numberof1bits.h"
#include "GUI/SimpleTest.h"

/*
 * Function: hammingWeight
 * ------------------------------------
 * ex> 11: 00000000000000000000000000001011, which has 3 1-bits
 *
 * The solution is using mask to check each bit and count.
 * Notice:
 * 2^0 = 1: 00000000000000000000000000000001
 * 2^1 = 2: 00000000000000000000000000000010
 * 2^2 = 4: 00000000000000000000000000000100
 * ....
 * 2^31 = 2147483648(not exist): 10000000000000000000000000000000
 * INT_MAX = 2147483647  INT_MIN = -2147483648
 *
 * Also, we are able to use bit manipulator left shift and right shift.
 */
int hammingWeight_sol1(uint32_t n) {
    uint32_t mask = 1;
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if ((n & mask) != 0) {
            count++;
        }
        mask <<= 1;
    }

    return count;
}

int hammingWeight_sol2(u_int32_t n) {
    return __builtin_popcount(n);
}


/*
 * Function: hammingWeight_sol3
 * ------------------------------------
 * We are able to use n-1 to flip the least significant 1-bit to 0 until n == 0;
 *
 * ex> 50:   00110010
 *     49: & 00110001
 *     --------------
 *     48:   00110000 flip the least significant 1-bit
 *     47: & 00101111
 *     --------------
 *     32:   00100000 flip
 *     31: & 00011111
 *     --------------
 *      0:   00000000 There you go!
 */
int hammingWeight_sol3(u_int32_t n) {
    int count = 0;
    while (n != 0) {
        count++;
        n = (n & (n-1));
    }

    return count;
}

PROVIDED_TEST("Test for binary:") {
    EXPECT_EQUAL(INT_MAX + 1, INT_MIN);
}

PROVIDED_TEST("Test for hammingWeight_sol1():") {
    EXPECT_EQUAL(hammingWeight_sol1(00000000000000000000000000001011), 3);
    EXPECT_EQUAL(hammingWeight_sol1(00000000000000000000010000001011), 4);
}
