#include "reversebits.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * Function: reverseBits_sol1
 * ------------------------------------
 * Our first solution is pretty straightforward. Use mask, record one bit and move it to
 * correct place one by one.
 *
 * ex>  input: 00000010100101000001111010011100
 *                                            ^
 *       mask: 00000000000000000000000000000001
 *        ret: 00000000000000000000000000000000
 *             *
 * round 1: move the least significant bit to the leftmost  << 31
 * round 2:
 *      input: 00000001010010100000111101001110(0)
 *                                            ^
 *       mask: 00000000000000000000000000000001
 *        ret: 00000000000000000000000000000000
 *             **
 * ...
 */
uint32_t reverseBits_sol1(uint32_t n) {
    uint32_t mask = 1; // ....0001
    int shift = 31;
    uint32_t ret = 0;
    // TODO: keep mask unchange, and move n
    while (n != 0) {
        ret += (n & mask) << shift;
        n >>= 1;
        shift--;
    }

    return ret;
}


/*
 * Function: reverseBits_sol2
 * ------------------------------------
 * Solution 2 is more like a divide and conquer strategy. Manual divide and conquer!
 * ex> input: 00000010100101000001111010011100
 *            ***************^^^^^^^^^^^^^^^^^
 *                 B0 <-----------> B1
 * divide and swap until there is no element in B0 or B1.
 */
uint32_t reverseBits_sol2(uint32_t n) {
    n = (n >> 16 | n << 16);
    n = (((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8));
    n = (((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4));
    n = (((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2));
    n = (((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1));

    return n;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for reverseBits_sol1():") {
    EXPECT_EQUAL(reverseBits_sol1(1), INT_MIN);
}

PROVIDED_TEST("Test for reverseBits_sol2():") {
    EXPECT_EQUAL(reverseBits_sol2(1), INT_MIN);
}
