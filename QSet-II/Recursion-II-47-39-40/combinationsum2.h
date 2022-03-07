#ifndef COMBINATIONSUM2_H
#define COMBINATIONSUM2_H

#include <vector>
using namespace std;

/**
 * Given a collection of candidate numbers (candidates) and a target number (target),
 * find all unique combinations in candidates where the candidate numbers sum to
 * target.
 *
 * Each number in candidates may only be used once in the combination.
 *
 * Note: The solution set must not contain duplicate combinations.
 *
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output:
 * [ [1,1,6],
 *   [1,2,5],
 *   [1,7],
 *   [2,6] ]
 *
 * Constrains:
 * 1 <= candidates.length <= 100
 * 1 <= candidates[i] <= 50
 * 1 <= target <= 30
 */
vector< vector<int> > combinationSum2(vector<int>& candidates, int target);

#endif // COMBINATIONSUM2_H
