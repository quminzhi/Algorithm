# Dynamic Programming

## Logic

- How to represent a problem? (state representation)
- What's the meaning of value mapped from `f`? (property, e.g. `max`, `min` etc.)
- How to divide the problem into sub-problems? How they contribute to the problem? (deduction formula)

## Knapsack Problems

### 0-1 Knapsack

> Given a number of items with values and weights, and the weight that a knapsack can afford, return the maximum value that we can get.

This is a generic problem for dynamic programming, where each item can be chosen only one time (choose) or zero time (not choose).

- 2-d implementation

```c++
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
```

- 1-d implementation

Can we save memory space? yes if we only care about the solution to a specific problem. In this problem, we only care about `f[i][j]`, where `i` is the number of items we are processing and `j` is available space, but do not care about `f[i-1][j]]` or anything else. So we can use a technique called rolling array, which only stores the solution of `f[j]` on ith level.

```c++
/**
 * @brief to reduce memory space, we use rolling array to solve the problem iteratively.
 * 
 * Note the relationship between the expression on the left and right.
 * 1. f[i] only relies on f[i-1], meaning the level before it. (it implies that f can be
 * reduced to a 1-d array), which will be implemented later.
 * 2. f[j] only relies on f[j], or f[j - w[i]] if w[i] > j, meaning possible elements
 * before j.
 * 
 * Observations above ensures that we can use rolling array to solve the problem.
 * 
 * @param weights 
 * @param values 
 * @param total 
 * @return int 
 */
int ZeroOneKnapsackII(vector<int> weights, vector<int> values, int total) {
    // vector<vector<int> > f(weights.size(), vector<int>(total, 0));
    vector<int> f(total, 0);

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
```

### Complete Knapsack

> Following up 0-1 knapsack problem, what if each item can be selected as much as you want? return the maximum value we can get.

The representation and deduction formula for complete knapsack is similar to 01 knapsack.

- Define `f[i][j]`, where `i` means selecting from first `i` items and `j` means available space.
- The deduction formula is:

```text
f[i][j] = max(
    f[i-1][j - k * w[i]] + k * v[i], if j - k * w[i] > 0 (select ith item for k times)
)
```

- 2-d implementation `O(N^3)`

```c++
/**
 * @brief each item can be selected as many times as you want.
 * 
 * For the implementation below, initialization part and deduction part can be incorporated
 * into one loop.
 * 
 * @param weights 
 * @param values 
 * @param total 
 * @return int 
 */
int CompleteKnapsack(vector<int> weights, vector<int> values, int total) {
    vector< vector<int> > f(weights.size(), vector<int>(total, 0));
    // initialize boundary
    for (int j = weights[0]; j < total; j++) {
        f[0][j] = j / weights[0] * values[0]; // pick as many as possible
    }

    // deduction
    for (int i = 1; i < weights.size(); i++) {
        for (int j = 0; j <= total; j++) {
            int maxVal = 0;
            for (int k = 0; k <= j / weights[i]; k++) {
                maxVal = max(maxVal, f[i-1][j - k * weights[i]] + k * values[i]);
            }
            f[i][j] = maxVal;
        }
    }

    return f[weights.size()-1][total];
}
```

- 2-d implementation `O(N^2)`

Let's see two deduction from the formula

```text
f[i][j] = max(
    f[i-1][j - k * w[i]] + k * v[i], if j - k * w[i] > 0 (select ith item for k times)
)
```

Expand `f[i][j]` and `f[i][j - w]`, where `w` is the weight of ith item and `v` is corresponding value.

```text
f[i][j]   = max( f[i-1][j], f[i-1][j-w] + v, f[i-1][j-2w] + 2v, f[i-1][j-3w] + 3v,...)
f[i][j-w] = max(            f[i-1][j-w],     f[i-1][j-2w] + v,  f[i-1][j-3w] + 2v,...)
                            ^                ^                  ^
                            a lot of repeated calculations
```

So we can derive a new deduction formula: `f[i][j] = max(f[i-1][j], f[i][j-w] + v)`, which means the maximum of first `i` items with available weight of `j` can be derived from two sub-problems instead of `k` sub-problems.

- `f[i-1][j]` means ith item has been chosen 0 times (no pick).
- `f[i][j-v] + w` means ith item has been chosen m times, and we proceed to choose ith item again.

Key idea: examine the CLOSEST representation as much as possible.

```c++
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
    vector< vector<int> > f(weights.size(), vector<int>(total, 0));
    // initialize boundary
    for (int j = weights[0]; j < total; j++) {
        f[0][j] = j / weights[0] * values[0]; // pick as many as possible
    }

    // deduction
    for (int i = 1; i < weights.size(); i++) {
        for (int j = 0; j <= total; j++) {
            f[i][j] = f[i-1][j];
            if (weights[i] <= j) {
                f[i][j] = max(f[i][j], f[i][j-weights[i]] + values[i]);
            }
        }
    }

    return f[weights.size()-1][total];
}
```

- 1-d implementation

Again, for deduction formula: `f[i][j] = max(f[i-1][j], f[i][j-w] + v)`, two observation are: 1. `f[i][j]` relies on the `i-1` level. 2. `f[i][j]` relied on `f[i][j-w]` which occurs before `f[i][j]`.

```text
Case 1: scan from right to left
rolling array: f[i-1][0], f[i-1][1], f[i-1][2], ..., f[i-1][total]
                                     <--- j goes from end to begin

               f[i-1][0], f[i-1][1], ...f[i-1][k], 
                                          f[i][k], f[i][k+1], ..., f[i][total]
                                               ^
                      at i-1th level   <---   j      at ith level

Case 2: scan from left to right
rolling array: f[i-1][0], f[i-1][1], f[i-1][2], ..., f[i-1][total]
               j goes from begin to end --->

                                  f[i-1][k], f[i-1][k+1], ..., f[i-1][total]
               f[i][0], f[i][1], ...f[i][k],
                                         ^
                   at ith level   <---   j      at i-1th level
```

In zero-one knapsack `f[i][j] = f[i-1][j-m*w]`, meaning it relies on the j before it on the i-1th level (**last level**). In this case we need to save the value of `f[i-1][k]`, where `k < j`. Thereby we have to scan from right to left (case 1).

For complete knapsack `f[i][j] = f[i][j-w] + v`, meaning it relies on the j before it on the ith level (**same level**). We have to update the value before `j` first. Therefore, we scan from left to right.

```c++
int CompleteKnapsackIII(vector<int> weights, vector<int> values, int total) {
    vector<int> f(total, 0);
    // initialize boundary
    for (int j = weights[0]; j < total; j++) {
        f[j] = j / weights[0] * values[0]; // pick as many as possible
    }

    // deduction:
    for (int i = 1; i < weights.size(); i++) {
        // for (int j = total; j >= 0; j--) {
        for (int j = weights[i]; j >= total; j++) {
            // f[j] = f[j]; // can be simplified
            // if (weights[i] <= j) // incorporate into loop condition
            f[j] = max(f[j], f[j-weights[i]] + values[i]);
        }
    }

    return f[total];
}
```
