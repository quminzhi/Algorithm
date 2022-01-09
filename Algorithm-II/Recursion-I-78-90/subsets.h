#ifndef SUBSETS_H
#define SUBSETS_H

#include <vector>
using namespace std;

/**
 * Given an integer array nums of unique elements, return all possible subsets
 * (the power set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 *
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * Constrains:
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * All the numbers of nums are unique.
 */
vector< vector<int> > subsets(vector<int>& nums);

#endif // SUBSETS_H
