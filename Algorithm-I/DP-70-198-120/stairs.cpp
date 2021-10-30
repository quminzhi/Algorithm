#include "stairs.h"
#include <unordered_map>
#include "GUI/SimpleTest.h"
#include <vector>
using namespace std;

int climbStairsHelper(int n, unordered_map<int, int>& buffer) {
    if ((n == 0) || (n == 1)) return 1;

    if (buffer.find(n) != buffer.end()) {
        return buffer[n];
    }
    else {
        int fn = climbStairsHelper(n - 1, buffer) + climbStairsHelper(n - 2, buffer);
        buffer[n] = fn;
        return fn;
    }
}

/*
 * Function: climbStairs_sol1
 * ------------------------------------
 * At first glance, it is a decision problem, which can be solved recursively.
 *
 * f(n) = f(n-1) + f(n-2), where f is defined as the number of distinct ways that I can
 * climb to the top.
 *
 * Base case:
 *      if n equals 1, then there is 1 way (f(2) = f(1) + f(0)). (definition)
 *      if n equals 1, then there is 1 way to do that.
 * Recursion:
 *      the number of ways to the top of n stairs is equal to that of n-1 stairs with 1
 *      step forward plus that of n-2 stairs with 2 step forward.
 *
 * T: O(N^2)
 *
 * If we use a buffer to cache f(n), then the T becomes O(N), but with extra space O(N).
 */
int climbStairs_sol1(int n) {
    unordered_map<int, int> buffer;
    int result = climbStairsHelper(n, buffer);

    return result;
}


/*
 * Function: climbStairs_sol2
 * ------------------------------------
 * From the perspective from bottom to top, we are able to solve problem in a different
 * way, which is known as dynamic programming.
 *
 * f(0) = 1;
 * f(1) = 1;
 * f(2) = f(1) + f(0);
 * f(3) = f(2) + f(1);
 *          ^     ^   KNOWN
 * ....
 */
int climbStairs_sol2(int n) {
    const int MAX_SIZE = 50;
    vector<int> f(MAX_SIZE, 0);
    f[0] = f[1] = 1;
    for (int i = 2; i < MAX_SIZE; i++) {
        f[i] = f[i-1] + f[i-2];
    }

    return f[n];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for climbStairs_sol1():") {
    EXPECT_EQUAL(climbStairs_sol1(0), 1);
    EXPECT_EQUAL(climbStairs_sol1(1), 1);
    EXPECT_EQUAL(climbStairs_sol1(2), 2);
    EXPECT_EQUAL(climbStairs_sol1(3), 3);
}

PROVIDED_TEST("Test for climbStairs_sol2():") {
    EXPECT_EQUAL(climbStairs_sol2(0), 1);
    EXPECT_EQUAL(climbStairs_sol2(1), 1);
    EXPECT_EQUAL(climbStairs_sol2(2), 2);
    EXPECT_EQUAL(climbStairs_sol2(3), 3);
}
