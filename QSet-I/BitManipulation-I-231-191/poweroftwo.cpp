#include "poweroftwo.h"
#include "GUI/SimpleTest.h"

/*
 * Function: isPowerOfTwo_sol1
 * ------------------------------------
 * According to the definition, if number n can be divided into the multiple of a series
 * of 2, then n is the power of 2.
 *
 * 1. divide n by 2, and check if the mod is 0 until it is 1.
 */
bool isPowerOfTwo_sol1(int n) {
    if (n == 0) return false;
    if (n == 1) return true;

    int mod = 0;
    while (n != 1) {
        mod = n % 2;
        if (mod != 0) {
            return false;
        }
        n = n / 2;
    }

    return true;
}


/*
 * Function: isPowerOfTwo_sol2
 * ------------------------------------
 * Also, we are able to solve it by recursion.
 *
 * Say, if n is the multiplication of 2 and a number which is power of 2, then n is
 * power of 2.
 *
 * ex>  isPowerOfTwo(5) => isPowerOfTwo()
 */
bool isPowerOfTwo_sol2(int n) {
    if (n == 0) return false;
    if (n == 1) return true;

    if (n % 2 == 1) {
        return false;
    }
    else {
        return isPowerOfTwo_sol2(n / 2);
    }
}


/*
 * Function: isPowerOfTwo_sol3
 * ------------------------------------
 * The idea behind both solutions will be the same: a power of two in binary representation
 * is one 1-bit, followed by some zeros:
 * ex> 1 = (00000001)
 *     2 = (00000010)
 *     4 = (00000100)
 *     8 = (00001000)
 *     ...
 *
 * On the contrary, A number which is not a power of two, has more than one 1-bit in its
 * binary representation.
 *
 * Tip:
 * 'x & (-x)' is a way to keep the rightmost 1-bit and to set all the other bits to 0.
 * That's because two's complement. -x = revert(x) + 1, which is same as all bits are
 * reverted except the rightmost 1-bit and its right bits (and its right bits must be 0).
 *
 * ex>     7: 0 0 0 0 0 1 1 1
 *                          ^
 *    revert: 1 1 1 1 1 0 0 0
 *        +1: 1 1 1 1 1 0 0 1
 *                          ^
 *  7 & (-7): 0 0 0 0 0 0 0 1   == 1
 *
 *         6: 0 0 0 0 0 1 1 0
 *                        ^
 *    revert: 1 1 1 1 1 0 0 1
 *        +1: 1 1 1 1 1 0 1 0
 *                        ^
 *  6 & (-6): 0 0 0 0 0 0 1 0   == 2
 *
 * Therefore, x and -x has just one bit in common, which is the rightmost bit, and
 * 'x & (-x)' will keep all the other bits to 0 except the rightmost 1-bit.
 *
 * For the power of two, 'x & (-x)' would result in itself. Great!
 */
bool isPowerOfTwo_sol3(int n) {
    if (n == 0) return false;
    long x = n;
    return (x & -x) == x;
}

bool isPowerOfTwo_sol4(int n) {
    if (n == 0) return false;
    long x = n;
    return (x & (x -1)) == 0;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for isPowerOfTwo_sol*():") {
    EXPECT(isPowerOfTwo_sol1(1));
    EXPECT(isPowerOfTwo_sol2(1));
    EXPECT(isPowerOfTwo_sol3(1));
    EXPECT(isPowerOfTwo_sol4(1));

    EXPECT(isPowerOfTwo_sol1(4));
    EXPECT(isPowerOfTwo_sol2(4));
    EXPECT(isPowerOfTwo_sol3(4));
    EXPECT(isPowerOfTwo_sol4(4));

    EXPECT(!isPowerOfTwo_sol1(6));
    EXPECT(!isPowerOfTwo_sol2(6));
    EXPECT(!isPowerOfTwo_sol3(6));
    EXPECT(!isPowerOfTwo_sol4(6));
}
