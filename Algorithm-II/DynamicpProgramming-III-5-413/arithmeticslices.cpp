#include "arithmeticslices.h"
#include <testing/SimpleTest.h>

/**
 * @brief numberOfArithmeticSlices
 * @param nums
 * @return
 * Again, dynamic programming. We define f as:
 *
 * f(left, right): true if right - left >= 2 and nums[left, right] is arithmetic.
 *
 * f(left, right) has two cases:
 * 1. base case: f(left, left+2)
 * 2. derive case: f(left, right) = f(left, right-1) &
 *                 (nums[right] - nums[right-1]) == (nums[left+1] - nums[left])
 *
 * Derivation direction can be figured out from f(left, right) = f(left, right-1).
 *
 * T: O(N^2)
 */
int numberOfArithmeticSlices(vector<int>& nums) {
    if (nums.size() < 3) return 0;
    int size = nums.size();
    int cnt = 0;
    vector< vector<bool> > isSlice(size, vector<bool>(size, false));

    // case 1:
    for (int i = 0; i < (size - 2); i++) {
        if ((nums[i+2] - nums[i+1]) == (nums[i+1] - nums[i])) {
            isSlice[i][i+2] = true;
            cnt++;
        }
    }

    // case 2:
    for (int right = 3; right < size; right++) {
        for (int left = 0; left <= right - 3; left++) {
            if ((isSlice[left][right-1]) &&
                ((nums[right] - nums[right-1]) == (nums[left+1] - nums[left]))) {
                isSlice[left][right] = true;
                cnt++;
            }
        }
    }

    return cnt;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums1 = {1, 2, 3, 4};
    EXPECT_EQUAL(numberOfArithmeticSlices(nums1), 3);

    vector<int> nums2 = {1};
    EXPECT_EQUAL(numberOfArithmeticSlices(nums2), 0);
}
