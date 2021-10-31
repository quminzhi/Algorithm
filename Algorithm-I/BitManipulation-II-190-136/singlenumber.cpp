#include "singlenumber.h"
#include <unordered_set>
#include "testing/SimpleTest.h"

/*
 * Function: singleNumber_sol1
 * ------------------------------------
 * Solution 1 will use a stack to find match numbers. Eventually the single number will
 * stay in stack.
 *
 * T: O(Nlog(N)), S: O(N)
 */
int singleNumber_sol1(vector<int>& nums) {
    if (nums.size() == 0) return -1;
    unordered_set<int> buffer;
    for (int i = 0; i < nums.size(); i++) {
        unordered_set<int>::iterator it = buffer.find(nums[i]);
        if (it != buffer.end()) {
            buffer.erase(it);
        }
        else {
            buffer.insert(nums[i]);
        }
    }

    return *buffer.begin();
}

/*
 * Function: singleNumber_sol2
 * ------------------------------------
 * Is there a better way? Bit manipulation!
 *
 * XOR: A   B   A XOR B
 *      0   0      0
 *      1   0      1
 *      0   1      1
 *      1   1      0
 *
 * ex> 1101 XOR 0000 = 1101 same as itself
 *     1101 XOR 1101 = 0000
 *
 * A number n XOR 0 will be it self, n XOR n will be 0.
 *
 * Let's say there are three numbers in 'nums': a, b, a
 * a XOR b XOR a = a XOR a XOR b = 0 XOR b = b, then there you are!
 *
 * XOR in C++/C is '^'
 */
int singleNumber_sol2(vector<int>& nums) {
    int ret = 0;
    for (int& num : nums) {
        ret = ret ^ num;
    }

    return ret;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for singleNumber_sol1():") {
    vector<int> nums1 = {1, 1, 2};
    EXPECT_EQUAL(singleNumber_sol1(nums1), 2);

    vector<int> nums2 = {1, 2, 2};
    EXPECT_EQUAL(singleNumber_sol1(nums2), 1);
}

PROVIDED_TEST("Test for singleNumber_sol2():") {
    vector<int> nums1 = {1, 1, 2};
    EXPECT_EQUAL(singleNumber_sol2(nums1), 2);

    vector<int> nums2 = {1, 2, 2};
    EXPECT_EQUAL(singleNumber_sol2(nums2), 1);
}
