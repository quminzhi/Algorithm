#ifndef COMBINATION_H
#define COMBINATION_H

#include <vector>
using namespace std;

/**
 * Given two integers n and k, return all possible combinations of k numbers out of the
 * range [1, n].
 *
 * Input: n = 4, k = 2
 * Output:
 * [
 *  [2,4],
 *  [3,4],
 *  [2,3],
 *  [1,2],
 *  [1,3],
 *  [1,4],
 * ]
 *
 * 1 <= n <= 20,
 * 1 <= k <= n
 */

vector< vector<int> > combine(int n, int k);

#endif // COMBINATION_H
