#ifndef JUMPGAME4_H
#define JUMPGAME4_H

#include <vector>
using namespace std;

/**
 * Given an array of integers arr, you are initially positioned at the first index of
 * the array.
 *
 * In one step you can jump from index i to index:
 * - i + 1 where: i + 1 < arr.length.
 * - i - 1 where: i - 1 >= 0.
 * - j where: arr[i] == arr[j] and i != j.
 *
 * Return the minimum number of steps to reach the last index of the array.
 *
 * Notice that you can not jump outside of the array at any time.
 *
 * Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
 * Output: 3
 * Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9
 * is the last index of the array.
 *
 * Constrains:
 * 1 <= arr.length <= 5 * 104
 * -108 <= arr[i] <= 108
 */
int minJumps(vector<int>& arr);

#endif // JUMPGAME4_H
