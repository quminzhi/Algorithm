#ifndef INTEGERBREAK_H
#define INTEGERBREAK_H

#include <vector>
using namespace std;

/**
 * Given an integer n, break it into the sum of k positive integers, where k >= 2, and
 * maximize the product of those integers.
 *
 * Return the maximum product you can get.
 *
 * Input: n = 2
 * Output: 1
 * Explanation: 2 = 1 + 1, 1 × 1 = 1.
 *
 * Constrains:
 * 2 <= n <= 58
 */
int integerBreak(int n);

#endif // INTEGERBREAK_H
