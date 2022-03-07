#ifndef MOVEZEROS_H
#define MOVEZEROS_H

#include <vector>
using namespace std;

/* Given an integer array nums, move all 0's to the end of it while maintaining
 * the relative order of the non-zero elements.
 * Note that you must do this in-place without making a copy of the array.
 *
 * Input: nums = [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 *
 * Constraints:
 * 1 <= nums.length <= 104
 * -231 <= nums[i] <= 231 - 1
 */

void moveZeroes_sol1(vector<int>& nums);
void moveZeroes_sol2(vector<int>& nums);


#endif // MOVEZEROS_H
