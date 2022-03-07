#ifndef SINGLENUMBERII_H
#define SINGLENUMBERII_H

#include <vector>
using namespace std;

/**
 * Given an integer array nums where every element appears three times except for one,
 * which appears exactly once. Find the single element and return it.
 *
 * You must implement a solution with a linear runtime complexity and use only constant
 * extra space.
 *
 * Input: nums = [0,1,0,1,0,1,99]
 * Output: 99
 *
 * Constrains:
 * 1 <= nums.length <= 3 * 104
 * -2^31 <= nums[i] <= 2^31 - 1
 * Each element in nums appears exactly three times except for one element which appears once.
 */

int singleNumberii_sol1(vector<int>& nums);

#endif // SINGLENUMBERII_H
