#ifndef FINDPOSITION_H
#define FINDPOSITION_H

#include <vector>
using namespace std;

/**
 * Given an array of integers nums sorted in non-decreasing order, find the starting
 * and ending position of a given target value.
 *
 * If target is not found in the array, return [-1, -1].
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 *
 * Constrains:
 * 0 <= nums.length <= 105
 * -109 <= nums[i] <= 109
 * nums is a non-decreasing array.
 * -109 <= target <= 109
 */

vector<int> searchRange(vector<int>& nums, int target);

#endif // FINDPOSITION_H
