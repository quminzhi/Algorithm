#include "longestincreasingsubsequence.h"
#include "testing/SimpleTest.h"

/**
 * @brief lengthOfLIS
 * @param nums
 * @return
 * The problem becomes clear when it is seen from the perspective of dynamic programming.
 *
 * ex> nums = {0, 1, 0, 3, 2, 3}
 *
 * Think of the question: what's the longest subseq of nums + {1, 2, ...} when given the
 * longest subseq length is 4?
 *
 * Define f(end) as: the length of longest subseq ending with 'end'.
 *
 * Derivation: f(end) = max(f[i] + 1) for all i where nums[i] < nums[end] and i < end
 *
 * Base case: f(i) = 1, where i belongs to [0, s.size()-1] as initially subseq ending with
 * all index is 1.
 *
 * T: O(N^2)
 */
int lengthOfLIS(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int size = nums.size();

    vector<int> longest(size, 1);
    for (int end = 1; end < size; end++) {
        for (int i = 0; i < end; i++) {
            if ((nums[i] < nums[end]) && (longest[i] + 1 > longest[end])){
                longest[end] = longest[i] + 1;
            }
        }
    }

    int max = 0;
    for (int i = 0; i < size; i++) {
        if (longest[i] > max) {
            max = longest[i];
        }
    }

    return max;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums = {8, 1, 6, 7, 2, 3, 4};
    EXPECT_EQUAL(lengthOfLIS(nums), 4);
}
