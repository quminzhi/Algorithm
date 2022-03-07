#ifndef THREESUM_H
#define THREESUM_H

#include <vector>
using namespace std;

/**
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
 * such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 *
 * Notice that the solution set must not contain duplicate triplets.
 *
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 *
 * Constrains:
 * 0 <= nums.length <= 3000
 * -105 <= nums[i] <= 105
 */

vector< vector<int> > threeSum(vector<int>& nums);

#endif // THREESUM_H
