#include "knapsack.hpp"

#include <math.h>

#include <iostream>

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
    vector<vector<int> > f(weights.size(), vector<int>(total + 1, 0));

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

/**
 * @brief to reduce memory space, we use rolling array to solve the problem iteratively.
 *
 * Note the relationship between the expression on the left and right.
 * 1. f[i] only relies on f[i-1], meaning the level before it. (it implies that f can be
 * reduced to a 1-d array), which will be implemented later.
 * 2. f[j] only relies on f[j], or f[j - w[i]] if w[i] > j, meaning possible elements
 * before j.
 *
 * Observations above ensures that we can use rolloing array to solve the problem.
 *
 * @param weights
 * @param values
 * @param total
 * @return int
 */
int ZeroOneKnapsackII(vector<int> weights, vector<int> values, int total) {
    // vector<vector<int> > f(weights.size(), vector<int>(total, 0));
    vector<int> f(total + 1, 0);

    // initialize the boundary, when i == 0
    for (int j = 0; j <= total; j++) {
        f[j] = weights[0] <= j ? values[0] : 0;
    }

    // deduct
    for (int i = 1; i < weights.size(); i++) {
        // why from total to 0? observation 2
        for (int j = total; j > 0; j--) {
            // on ith level
            // f[j] on the right side is the value on i-1 level
            f[j] = f[j];   // not choose
            if (weights[i] <= j) {
                // f[j - weights[i]] is the value on i-1 level
                // given observation 2
                f[j] = max(f[j], f[j - weights[i]] + values[i]);   // choose
            }
        }
    }

    // 0-indexed: the index of the first item is 0
    return f[total];
}

/**
 * @brief each item can be selected as many times as you want.
 *
 * For the implementation below, initialization part and deduction part can be
 * incorporated into one loop.
 *
 * @param weights
 * @param values
 * @param total
 * @return int
 */
int CompleteKnapsack(vector<int> weights, vector<int> values, int total) {
    vector<vector<int> > f(weights.size(), vector<int>(total + 1, 0));
    // initialize boundary
    for (int j = weights[0]; j < total; j++) {
        f[0][j] = j / weights[0] * values[0];   // pick as many as possible
    }

    // deduction
    for (int i = 1; i < weights.size(); i++) {
        for (int j = 0; j <= total; j++) {
            int maxVal = 0;
            for (int k = 0; k <= j / weights[i]; k++) {
                maxVal = max(maxVal, f[i - 1][j - k * weights[i]] + k * values[i]);
            }
            f[i][j] = maxVal;
        }
    }

    return f[weights.size() - 1][total];
}

/**
 * @brief Simplified deduction formula:
 *
 * f[i][j] = max(f[i-1][j], f[i][j-w] + v)
 *
 * @param weights
 * @param values
 * @param total
 * @return int
 */
int CompleteKnapsackII(vector<int> weights, vector<int> values, int total) {
    vector<vector<int> > f(weights.size(), vector<int>(total + 1, 0));
    // initialize boundary
    for (int j = weights[0]; j < total; j++) {
        f[0][j] = j / weights[0] * values[0];   // pick as many as possible
    }

    // deduction
    for (int i = 1; i < weights.size(); i++) {
        for (int j = 0; j <= total; j++) {
            f[i][j] = f[i - 1][j];
            if (weights[i] <= j) {
                f[i][j] = max(f[i][j], f[i][j - weights[i]] + values[i]);
            }
        }
    }

    return f[weights.size() - 1][total];
}

int CompleteKnapsackIII(vector<int> weights, vector<int> values, int total) {
    vector<int> f(total + 1, 0);
    // initialize boundary
    for (int j = weights[0]; j <= total; j++) {
        f[j] = j / weights[0] * values[0];   // pick as many as possible
    }

    // deduction: steps to simplify
    // // step 1: delete lhs == rhs
    // for (int i = 1; i < weights.size(); i++) {
    //     for (int j = 0; j <= total; j++) {
    //         f[j] = f[j]; // can be simplified
    //         if (weights[i] <= j) {
    //             f[j] = max(f[j], f[j-weights[i]] + values[i]);
    //         }
    //     }
    // }

    // // step 2: combine if into condition of for loop
    // for (int i = 1; i < weights.size(); i++) {
    //     for (int j = 0; j <= total; j++) {
    //         if (weights[i] <= j) {
    //             f[j] = max(f[j], f[j-weights[i]] + values[i]);
    //         }
    //     }
    // }

    // final
    for (int i = 1; i < weights.size(); i++) {
        for (int j = weights[i]; j <= total; j++) {
            f[j] = max(f[j], f[j - weights[i]] + values[i]);
        }
    }

    return f[total];
}

/**
 * @brief The deduction formula is:
 *
 * f[i][j] = max(f[i-1][j - k * w[i]] + k * v[i]), where k is in [0, min(s[i], k / w[i])]
 *
 * @param weights
 * @param values
 * @param limits
 * @param total
 * @return int
 */
int LimitedKnapsack(vector<int> weights, vector<int> values, vector<int> limits,
                    int total) {
    vector<vector<int> > f(weights.size(), vector<int>(total + 1, 0));
    // boundary
    for (int j = 0; j <= total; j++) {
        f[0][j] = values[0] * min(limits[0], j / weights[0]);
    }

    // deduction
    for (int i = 1; i < weights.size(); i++) {
        for (int j = 0; j <= total; j++) {
            int maxVal = 0;
            int kMax = min(limits[i], j / weights[i]);
            for (int k = 0; k <= kMax; k++) {
                maxVal = max(maxVal, f[i - 1][j - k * weights[i]] + k * values[i]);
            }
            f[i][j] = maxVal;
        }
    }

    return f[weights.size() - 1][total];
}

/**
 * @brief 1-d implementation (memory optimization)
 *
 * @param weights
 * @param values
 * @param limits
 * @param total
 * @return int
 */
int LimitedKnapsackII(vector<int> weights, vector<int> values, vector<int> limits,
                      int total) {
    vector<int> f(total + 1, 0);
    // boundary
    for (int j = 0; j <= total; j++) {
        f[j] = values[0] * min(limits[0], j / weights[0]);
    }

    // deduction
    for (int i = 1; i < weights.size(); i++) {
        for (int j = total; j >= 0; j--) {
            int maxVal = 0;
            int kMax = min(limits[i], j / weights[i]);
            for (int k = 0; k <= kMax; k++) {
                maxVal = max(maxVal, f[j - k * weights[i]] + k * values[i]);
            }
            f[j] = maxVal;
        }
    }

    return f[total];
}

/**
 * @brief bit optimization (reduce time complexity to O(N * M * log(S)))
 *
 * @param weights
 * @param values
 * @param limits
 * @param total
 * @return int
 */
int LimitedKnapsackIII(vector<int> weights, vector<int> values, vector<int> limits,
                       int total) {
    vector<int> newWeights;
    vector<int> newValues;

    // construct new items
    for (int i = 0; i < weights.size(); i++) {
        int k = 1;   // notice k is not bit but weight on that bit, 2^0
        while (k <= limits[i]) {
            newWeights.push_back(k * weights[i]);
            newValues.push_back(k * values[i]);
            // one way to calculate bit = floor(log2(limits[i]))
            // limits[i] = 2^0 + 2^1 + 2^2 + ... + 2^(k-1) + C
            limits[i] -= k;
            k = k << 1;
        }

        // now limits[i] becomes C
        if (limits[i] >= 0) {
            newWeights.push_back(limits[i] * weights[i]);
            newValues.push_back(limits[i] * values[i]);
        }
    }

    // zero-one knapsack
    vector<vector<int> > f(newWeights.size(), vector<int>(total + 1, 0));

    for (int j = 0; j <= total; j++) {
        f[0][j] = newWeights[0] <= j ? newValues[0] : 0;
    }

    for (int i = 1; i < newWeights.size(); i++) {
        for (int j = 0; j <= total; j++) {
            f[i][j] = f[i - 1][j];
            if (newWeights[i] <= j) {
                f[i][j] = max(f[i][j], f[i - 1][j - newWeights[i]] + newValues[i]);
            }
        }
    }

    return f[newWeights.size() - 1][total];
}