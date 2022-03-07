#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <vector>
using namespace std;

/**
 * Given an array nums of distinct integers, return all the possible permutations. You
 * can return the answer in any order.
 *
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * 1 <= nums.length <= 6
 * -10 <= nums[i] <= 10
 * All the integers of nums are unique.
 */

vector< vector<int> > permute(vector<int>& nums);

#endif // PERMUTATION_H
