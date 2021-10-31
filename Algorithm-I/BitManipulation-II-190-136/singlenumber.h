#ifndef SINGLENUMBER_H
#define SINGLENUMBER_H

#include <vector>
using namespace std;

/**
 * Given a non-empty array of integers nums, every element appears twice except for
 * one. Find that single one.
 *
 * You must implement a solution with a linear runtime complexity and use only constant
 * extra space.
 *
 * Input: nums = [2,2,1]
 * Output: 1
 *
 * Constrains:
 * 1 <= nums.length <= 3 * 10^4
 * -3 * 10^4 <= nums[i] <= 3 * 10^4
 * Each element in the array appears twice except for one element which appears only once.
 */

int singleNumber_sol1(vector<int>& nums);

#endif // SINGLENUMBER_H
