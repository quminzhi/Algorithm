#include "knapsack.hpp"

/**
 * @brief This is a naive implementation of 01 knapsack problem.
 *
 * Note that f should define a problem set.
 *
 * Define f[i][j], where i means selecting from first i items.
 *                       j means available space.
 *
 * The property of the problem set can be max, min, or something.
 *
 * The deduction formula is:
 *
 * f[i][j] = max(
 *      f[i-1][j] (do not select ith item),
 *      f[i-1][j - w[i]] + v[i], if j - w[i] > 0 (select ith item)
 * )
 *
 * Note the relationship between the expression on the left and right.
 * 1. f[i] only relies on f[i-1], meaning the level before it. (it implies that f can be
 * reduced to a 1-d array), which will be implemented later.
 * 2. f[j] only relies on f[j], or f[j - w[i]] if w[i] > j, meaning possible elements
 * before j.
 *
 * @param weights
 * @param values
 * @param total
 * @return int
 */
int ZeroOneKnapsack(vector<int> weights, vector<int> values, int total) {
    vector<vector<int> > f(weights.size(), vector<int>(total, 0));

    // initialize the boundary, when i == 0
    for (int j = 0; j <= total; j++) {
        f[0][j] = weights[0] <= j ? values[0] : 0;
    }

    // deduct
    for (int i = 1; i < weights.size(); i++) {
        for (int j = 0; j <= total; j++) {
            f[i][j] = f[i - 1][j];   // not choose
            if (weights[i] <= j) {
                f[i][j] = max(f[i][j], f[i - 1][j - weights[i]] + values[i]);   // choose
            }
        }
    }

    // 0-indexed: the index of the first item is 0
    return f[weights.size() - 1][total];
}
