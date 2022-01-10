#ifndef PERMUTATION2_H
#define PERMUTATION2_H

#include <vector>
using namespace std;

/**
 * Given a collection of numbers, nums, that might contain duplicates, return
 * all possible unique permutations in any order.
 *
 * Input: nums = [1,1,2]
 * Output:
 * [[1,1,2],
 *  [1,2,1],
 *  [2,1,1]]
 *
 * Constrains:
 * 1 <= nums.length <= 8
 * -10 <= nums[i] <= 10
 */
vector< vector<int> > permuteUnique(vector<int>& nums);


#endif // PERMUTATION2_H
