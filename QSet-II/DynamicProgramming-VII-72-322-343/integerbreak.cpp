#include "integerbreak.h"
#include <testing/SimpleTest.h>

/**
 * @brief integerBreak
 * @param n
 * @return
 * Find problem structure that can be decomposed. Define f as:
 *
 * f(num): the maximum product of some positive integers whose sum is 'num'.
 *
 * Derivation: why it is divided by 2 and 3, since that's the best for getting maximum product.
 *
 * f(num) = max(num/2, f(num/2))^2 if num is even.
 *        = max(num/2, f(num/2)) * max(num/2+1, f(num/2 + 1)) if num is odd.
 *        MAX(/2, /3)
 *        = max(num/3, f(num/3))^3 if num is divided by 3
 *        = max(num/3, f(num/3))^2 * max(num/3+1, f(num/3 + 1)) if mod == 1.
 *        = max(num/3, f(num/3)) * max(num/3+1, f(num/3 + 1))^2 if mod == 2.
 *
 * Base case:
 * f(0) = 0; f(1) = 0;
 *
 * T: O(N)
 */
int integerBreak_sol1(int n) {
    if (n < 2) return 0;
    vector<int> f(n+1, 0);
    for (int num = 2; num < f.size(); num++) {
        int bigger1 = 0;
        if (num % 2 == 0) {
            // even
            bigger1 = max(num/2, f[num/2]);
            bigger1 *= bigger1;
        }
        else {
            // odd
            bigger1 = max(num/2, f[num/2]) * max(num/2 + 1, f[num/2 + 1]);
        }

        int bigger2 = 0;
        if (num % 3 == 0) {
            bigger2 = max(num/3, f[num/3]);
            bigger2 *= bigger2 * bigger2;
        }
        else if (num % 3 == 1){
            bigger2 = max(num/3, f[num/3]);
            bigger2 *= bigger2;
            bigger2 *= max(num/3 + 1, f[num/3 + 1]);
        }
        else {
            bigger2 = max(num/3, f[num/3]);
            bigger2 *= max(num/3 + 1, f[num/3 + 1]);
            bigger2 *= max(num/3 + 1, f[num/3 + 1]);
        }

        f[num] = max(bigger1, bigger2);
    }

    return f[n];
}

/**
 * @brief integerBreak_sol2
 * @param n
 * @return
 * what we care about is just divide num into two number.
 *
 * f(num) = max of (max(i, f[i]) * max(num-i, f[num-i])), where i is in [1..num-1].
 *
 */
int integerBreak_sol2(int n) {
    if (n < 2) return 0;
    vector<int> f(n+1, 0);

    for (int num = 2; num < f.size(); num++) {
        int maximum = 0;
        for (int i = 1; i < num; i++) {
            int cur = max(i, f[i]) * max(num - i, f[num-i]);
            if (cur > maximum) {
                maximum = cur;
            }
        }
        f[num] = maximum;
    }

    return f[n];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    EXPECT_EQUAL(integerBreak_sol1(2), 1);
    EXPECT_EQUAL(integerBreak_sol1(10), 36);
    EXPECT_EQUAL(integerBreak_sol1(8), 18);
}

PROVIDED_TEST("test for sol2:") {
    EXPECT_EQUAL(integerBreak_sol2(2), 1);
    EXPECT_EQUAL(integerBreak_sol2(10), 36);
    EXPECT_EQUAL(integerBreak_sol2(8), 18);
}
