#include "subsets.h"
#include <testing/SimpleTest.h>

void subsetsHelper(vector<int>& left, vector<int>& sofar,
                   vector< vector<int> >& result) {
    if (left.size() == 0) {
        result.push_back(sofar);
        return;
    }

    int cur = left.back();
    left.pop_back();
    // not choose the last number
    subsetsHelper(left, sofar, result);
    // choose the last number
    sofar.push_back(cur); // reuse sofar
    subsetsHelper(left, sofar, result);
    // restore environment
    sofar.pop_back();
    left.push_back(cur);
}

/**
 * @brief subsets
 * @param nums
 * @return all subsets of given nums
 * Choose and not choose.
 */
vector< vector<int> > subsets(vector<int>& nums) {
    vector< vector<int> > result;
    if (nums.size() == 0) return result;

    vector<int> sofar;
    subsetsHelper(nums, sofar, result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums = {0};
    EXPECT_EQUAL(subsets(nums).size(), 2);
}
