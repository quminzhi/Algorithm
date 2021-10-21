#ifndef TWOSUM_H
#define TWOSUM_H

#include <vector>
using namespace std;

/* Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order,
 * find two numbers such that they add up to a specific target number. Let these two numbers
 * be numbers[index1] and numbers[index2] where 1 <= first < second <= numbers.length.
 *
 * Return the indices of the two numbers, index1 and index2, as an integer array [index1, index2]
 * of length 2.
 *
 * The tests are generated such that there is exactly one solution. You may not use the same
 * element twice.
 *
 * Input: numbers = [2,3,4], target = 6
 * Output: [1,3]
 */

vector<int> twoSum_sol1(vector<int>& numbers, int target);
vector<int> twoSum_sol2(vector<int>& numbers, int target);


#endif // TWOSUM_H
