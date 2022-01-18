#include "bitwiseandofnumbersrange.h"
#include <testing/SimpleTest.h>

/**
 * @brief rangeBitwiseAnd
 * @param left
 * @param right
 * @return
 *
 * ex> 9: 00001 001
 *    10: 00001 010
 *    11: 00001 011
 *    12: 00001 100
 *        |---|
 *    common prefix
 *
 * So the question can be transformed as how to find the common prefix of left and right.
 *
 * left   9: 00001 001
 *                   ^
 *                   i
 * right 12: 00001 100
 *                   ^
 *                   j
 *
 * Right shift until left[i] == right[j]
 *
 * T: O(1)
 */
int rangeBitwiseAnd(int left, int right) {
    if (left == 0) return 0;
    if (right == 0) return 0;

    int shift = 0;

    // right shift:  1  2  3
    // 1: 001        0  0  0
    // 5: 101       10  1  0


    while (left < right) {
        left >>= 1;
        right >>= 1;
        shift++;
    }

    return left << shift;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    EXPECT_EQUAL(rangeBitwiseAnd(1, 5), 0);
    EXPECT_EQUAL(rangeBitwiseAnd(9, 12), 8);
}
