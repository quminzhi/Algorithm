#include "happynumber.h"
#include <unordered_set>
#include <vector>
#include <testing/SimpleTest.h>

int next(int happy) {
    int newHappy = 0;
    while (happy > 0) {
        int remainder = happy % 10;
        happy = happy / 10;
        newHappy += remainder * remainder;
    }

    return newHappy;
}

/**
 * @brief isHappy
 * @param n
 * @return true if it is happy.
 */
bool isHappy(int n) {
    vector<bool> memo(INT_MAX, false);
    if (n == 1) return true;
    int happy = n;
    while ((!memo[happy]) && (happy != 1)) {
        memo[happy] = true;
        happy = next(happy);
    }

    return happy == 1;
}

/**
 * @brief isHappy_sol2
 * @param n
 * @return
 * magic math solution: there is only one cycle:
 *
 * 4 - 16 - 37 - 58 - 89 - 145 - 42 - 20 - 4
 *
 * So hardcode it.
 */
bool isHappy_sol2(int n) {
    unordered_set<int> cycle = {4, 16, 37, 58, 89, 145, 42, 20};
    if (n == 1) return true;
    int happy = n;

    while ((happy != 1) && (cycle.find(happy) == cycle.end())) {
        happy = next(happy);
    }

    return happy == 1;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    EXPECT(isHappy(19));
    EXPECT(!isHappy(2));
    EXPECT(isHappy(10));
    EXPECT(isHappy(28));
}

PROVIDED_TEST("test for sol1:") {
    EXPECT(isHappy_sol2(19));
    EXPECT(!isHappy_sol2(2));
    EXPECT(isHappy_sol2(10));
    EXPECT(isHappy_sol2(28));
}
