#ifndef NUMBEROFLIS_H
#define NUMBEROFLIS_H

#include <vector>
using namespace std;

/**
 * Given an integer array nums, return the number of longest increasing subsequences.
 *
 * Notice that the sequence has to be strictly increasing.
 *
 * Input: nums = [1,3,5,4,7]
 * Output: 2
 * Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
 *
 * Constrains:
 * 1 <= nums.length <= 2000
 * -106 <= nums[i] <= 106
 */
int findNumberOfLIS(vector<int>& nums);

#endif // NUMBEROFLIS_H
