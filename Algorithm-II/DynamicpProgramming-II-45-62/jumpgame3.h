#ifndef JUMPGAME3_H
#define JUMPGAME3_H

#include <vector>
using namespace std;

/**
 * Given an array of non-negative integers arr, you are initially positioned at start
 * index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i],
 * check if you can reach to any index with value 0.
 *
 * Notice that you can not jump outside of the array at any time.
 *
 * Input: arr = [4,2,3,0,3,1,2], start = 5
 * Output: true
 * Explanation:
 * All possible ways to reach at index 3 with value 0 are:
 * index 5 -> index 4 -> index 1 -> index 3
 * index 5 -> index 6 -> index 4 -> index 1 -> index 3
 *
 * Constrains:
 * 1 <= arr.length <= 5 * 104
 * 0 <= arr[i] < arr.length
 * 0 <= start < arr.length
 */
bool canReach(vector<int>& arr, int start);

#endif // JUMPGAME3_H
