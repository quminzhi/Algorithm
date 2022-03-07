#include "combination.h"
#include "testing/SimpleTest.h"

void combineHelper(int n, int k, vector<int>& selected, vector< vector<int> >& result) {
    if (n < k) return;
    if (k == 0) {
        result.push_back(selected);
        return;
    }

    // TODO: choose and unchoose
    // not choose
    combineHelper(n - 1, k, selected, result);
    // choose
    selected.push_back(n);
    combineHelper(n - 1, k - 1, selected, result);
    selected.pop_back();
}

/*
 * Function: combine_sol1
 * ------------------------------------
 * How to solve the problem recursively?
 *
 * @param n: the number to be check
 * @param k: how many numbers need to choose
 *
 * There are two choice along the way it goes.
 * 1. current number is chosen, return combine_sol1(n-1, k-1, selected.push(n), result);
 * 2. otherwise, return combineHelper(n-1, k, selected, result);
 */
vector< vector<int> > combine(int n, int k) {
    vector< vector<int> > result;
    vector<int> selected;
    combineHelper(n, k, selected, result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for combine():") {
    vector< vector<int> > result = combine(4, 2);
    EXPECT_EQUAL(result[0][0], 2);
    EXPECT_EQUAL(result[0][1], 1);
    EXPECT_EQUAL(result[1][0], 3);
    EXPECT_EQUAL(result[1][1], 1);
    EXPECT_EQUAL(result[2][0], 3);
    EXPECT_EQUAL(result[2][1], 2);
    EXPECT(result.size() == 6);
}
