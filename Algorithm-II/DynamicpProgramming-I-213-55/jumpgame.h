#ifndef JUMPGAME_H
#define JUMPGAME_H

#include <vector>
using namespace std;

/**
 * You are given an integer array nums. You are initially positioned at the array's first
 * index, and each element in the array represents your maximum jump length at that
 * position.
 *
 * Return true if you can reach the last index, or false otherwise.
 *
 * Input: nums = [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Constrains:
 * 1 <= nums.length <= 104
 * 0 <= nums[i] <= 105
 */
bool canJump(vector<int>& nums);

#endif // JUMPGAME_H
