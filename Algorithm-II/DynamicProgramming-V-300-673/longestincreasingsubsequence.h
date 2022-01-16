#ifndef LONGESTINCREASINGSUBSEQUENCE_H
#define LONGESTINCREASINGSUBSEQUENCE_H

#include <vector>
using namespace std;

/**
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 *
 * A subsequence is a sequence that can be derived from an array by deleting some or no elements
 * without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence
 * of the array [0,3,1,6,2,2,7].
 *
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
 *
 * Constrains:
 * 1 <= nums.length <= 2500
 * -104 <= nums[i] <= 104
 */
int lengthOfLIS(vector<int>& nums);

#endif // LONGESTINCREASINGSUBSEQUENCE_H
