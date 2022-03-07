#ifndef SINGLENUMBERIII_H
#define SINGLENUMBERIII_H

#include <vector>
using namespace std;

/**
 * Given an integer array nums, in which exactly two elements appear only once and all
 * the other elements appear exactly twice. Find the two elements that appear only once.
 * You can return the answer in any order.
 *
 * You must write an algorithm that runs in linear runtime complexity and uses only
 * constant extra space.
 *
 * Input: nums = [1,2,1,3,2,5]
 * Output: [3,5]
 * Explanation:  [5, 3] is also a valid answer.
 *
 * Constrains:
 * 2 <= nums.length <= 3 * 104
 * -231 <= nums[i] <= 231 - 1
 * Each integer in nums will appear twice, only two integers will appear once.
 */

vector<int> singleNumberiii_sol1(vector<int>& nums);
vector<int> singleNumberiii_sol2(vector<int>& nums);

#endif // SINGLENUMBERIII_H
