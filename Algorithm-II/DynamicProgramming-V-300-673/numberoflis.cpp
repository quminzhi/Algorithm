#include "numberoflis.h"
#include <testing/SimpleTest.h>

/**
 * @brief findNumberOfLIS
 * @param nums
 * @return
 * The solution is based on the algorithm for finding LIS. The difference is that we will
 * add additional information to f. We define f as:
 *
 * f(end) is same.
 * n(end), tracks the num of subseqs.
 */
int findNumberOfLIS(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int size = nums.size();

    vector<int> longest(size, 1);
    vector<int> subseqs(size, 1);
    for (int end = 1; end < size; end++) {
        for (int i = 0; i < end; i++) {
            if ((nums[i] < nums[end]) && (longest[i] + 1 > longest[end])){
                longest[end] = longest[i] + 1;
            }
        }
        // track all subseqs
        int newCnt = 0;
        for (int i = 0; i < end; i++) {
            if ((nums[i] < nums[end]) && ((longest[i] + 1) == longest[end])) {
                // if subseq[i] is connected to subseq[end]
                newCnt += subseqs[i];
            }
        }
        if (newCnt != 0) {
            subseqs[end] = newCnt;
        }
    }

    int max = 0;
    for (int i = 0; i < size; i++) {
        if (longest[i] > max) {
            max = longest[i];
        }
    }

    int cnt = 0;
    for (int i = 0; i < size; i++) {
        if (longest[i] == max) {
            cnt += subseqs[i];
        }
    }

    return cnt;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums = {1, 3, 5, 4, 7};
    EXPECT_EQUAL(findNumberOfLIS(nums), 2);

    vector<int> nums2 = {1, 1, 1, 1, 1};
    EXPECT_EQUAL(findNumberOfLIS(nums2), 5);

    vector<int> nums3 = {1, 2, 4, 3, 5, 4, 7, 2};
    EXPECT_EQUAL(findNumberOfLIS(nums3), 3);
}
