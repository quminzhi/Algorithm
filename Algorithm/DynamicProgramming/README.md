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

### Limited Knapsack

> Following up complete knapsack problem, what if each item can be selected at most `limit[i]` times? return the maximum value we can get.

The naive implementation of limited knapsack is similar to complete knapsack.

```c++
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
    vector<vector<int> > f(weights.size(), vector<int>(total, 0));
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
```

- 1-d implementation

```c++
int LimitedKnapsackII(vector<int> weights, vector<int> values, vector<int> limits,
                    int total) {
    vector<int> f(total, 0);
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
```

Question: can we optimize `f[i][j]` with `f[i][j-w] + v` as we did in complete knapsack?

```text
f[i][j]   = max(f[i-1][j], f[i-1][j-w] + v, f[i-1][j-2w] + 2v, ..., f[i-1][j-sw] + sv)
f[i][j-w] = max(           f[i-1][j-w],     f[i-1][j-2w] + v,  ..., f[i-1][j-sw] + (s-1)v, f[i-1][j-(s+1)w] + sv)
```

we have an additional item `f[i-1][j-(s+1)w] + sv`, which can be seen as `f[i-1][j-w - sw] + sv`. Given `f[i][j-w]` we cannot get `f[i][j]`, meaning `f[i][j] != max(f[i-1][j], f[i][j-w] + v)`.

### Optimization for Limited Knapsack

Notice that the time complexity of limited knapsack above is `O(N * M * S)`, where `N` is the size of items, `M` is total weight of knapsack, and `S` is the maximum number of limits (`max(limits[i])`).

In this section, we will introduce a classic optimization which is called **binary bit optimization**. We will concentrate on optimizing `S` to `log(S)`.

```text
f[i][j] = max(f[i-1][j], f[i-1][j-w] + v, f[i-1][j-2w] + 2v, ..., f[i-1][j-sw] + sv)
```

Considered the formula above, do we need to enumerate all `s` elements? The answer is no. we can use binary bit to represent `[0...s]`. And each representation can be seen as a new and unique item. Then the limited knapsack problem is transferred to 0-1 knapsack problem, where the number of items is `N * log(S)` and the total weight is `M`.

```text
f[i][j] = max(f[i][j], f[i][j-w[i]] + v[i]), where i is in the range of `[0, Nlog(S)]` and j is in the range of `[0, M]`
```

To explain further, why `[0...s]` can be represented in bit and the problem becomes a 0-1 knapsack problem?

- how to use bit to simulate `[0...s]`

Notice that k-bit number can be used to represent numbers in the range of [0, 2^k - 1]

```text
ex> 0000 0000 (8 bits) can represents 0 ~ 2^8 - 1 (2^8 - 1 = 2^0 + 2^1 + ... + 2^7)

so, with k bits we can represent [0, 2^k - 1].

when 2^k - 1 < s < 2^(k+1) - 1, we can represent s with k-bits and a decimal number C.

       2^k           C (C < 2^k - 1)
|----------------|--------|
0            2^k - 1      s

ex> say s = 200, k = 7, and C = s + 1 - 2^k = 200 + 1 - 128 = 73

0000 000 (7 bits) + C
```

So `s == C + 2^k - 1`, where `k` is bit length and `C` is an offset. We can get `k = floor(log(s))` and `C = s + 1 - 2^k`.

- How's it connected to 0-1 knapsack?

With example of `s = 200`, we can break the ith item down into 7 new items and an offset 73. By selecting or not selecting (binary 0 or 1) new item, we can simulate the limit `s` (`limits[i]`). So ith item becomes `log(limits[i])` new items and we got roughly N * log(S) new items, and all of them are unique and can be selected only once.

The idea above can be justified with a simple example:

```text
limited knapsack: 
we have only one item with value 2 and weight 3 and this item can be selected at most 3 times. Return the maximum value when we have a knapsack of weight 5.

      weight  value  limit   (knapsack = 5)
item1   3       2      5

How can this problem be transferred to 0-1 knapsack? The counterpart problem for limited knapsack is as follow,

0-1 knapsack counterpart:
       weight  value  limit    2-bit  <== log2(5)
item1  3(3*1)  2(2*1)   1      (2^0)
item2  6(3*2)  4(2*2)   1      (2^1)   2-bit binary has range of [0...2^2-1]
item3   3*c     2*c     1      c=2     c = 5 - (2^k - 1), where k = 2

The problem above is a 0-1 problem. Notice all choices of 3 items (in 0-1 knapsack) === limited choice of 1 item (limited knapsack) 
```

```c++
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
```

### Grouped Knapsack

> Given N groups of items, we are allowed to select only one or (zero) item from a group. Give a total weight of knapsack, return the maximum value.

Define `f` as `f[i][j]`, where `i` means select from first `i` **groups** and `j` means available weight.

How to derive deduction formula?

`f[i][j]` consists of `f[i-1][j]` (select 0 item from ith group), `f[i-1][j-w[i][0]] + v[i][0]` (select the first item from ith group), ..., `f[i-1][j-w[i][last] + v[i][last]`. Of course, `j - w[i][k] >= 0`.

- 2-d implementation

```c++
/**
 * @brief the naive implementation of group knapsack
 * 
 * f[i][j] = max(f[i-1][j], f[i-1][j-w[i][k]] + v[i][k]), where k is in the range of items
 * of ith group, and `j-w[i][k]` >= 0.
 * 
 * @param items: vector of { groupId, weight, value }
 * @param total 
 * @return int 
 */
int GroupKnapsack(vector< vector<int> > items, int total) {
    // aggregate by group
    vector<int> groups(items.size(), 0);
    for (int i = 0; i < items.size(); i++) {
        groups[items[i][0]]++;
    }
    // truncate from end
    int end = groups.size() - 1; // the index of last group
    for (; end >= 0 && groups[end] != 0; end--) {}
    groups.resize(end);
    // index the index of the first item in each group with prefix
    // the first item of ith group in items is items[prefix[i] + 0]
    vector<int> prefix(groups.size(), 0);
    for (int i = 1; i < groups.size(); i++) {
        prefix[i] = groups[i-1] + prefix[i-1];
    }

    vector< vector<int> > f(groups.size(), vector<int>(total+1, 0));
    for (int j = 0; j <= total; j++) {
        for (int k = prefix[0]; k < prefix[0] + groups[0]; k++) {
            if (items[k][1] <= j) {
                f[0][j] = max(f[0][j], 0 + items[k][2]);
            }
        }
    }

    for (int i = 1; i < groups.size(); i++) {
        for (int j = 0; j <= total; j++) {
            for (int k = prefix[i]; k < prefix[i] + groups[i]; k++) {
                f[i][j] = f[i-1][j]; // no pick
                if (items[k][1] <= j) {
                    f[i][j] = max(f[i][j], f[i-1][j - items[k][1]] + items[k][2]);
                }
            }
        }
    }

    return f[groups.size()-1][total];
}
```

- 1-d implementation (similar to 0-1 knapsack)

```c++
int GroupKnapsackII(vector<vector<int> > items, int total) {
    // aggregate by group
    vector<int> groups(items.size(), 0);
    for (int i = 0; i < items.size(); i++) {
        groups[items[i][0]]++;
    }
    // truncate from end
    int end = groups.size() - 1;   // the index of last group
    for (; end >= 0 && groups[end] != 0; end--) {
    }
    groups.resize(end);
    // mapping: index the index of the first item in each group with prefix
    // the first item of ith group in items is items[prefix[i] + 0]
    vector<int> prefix(groups.size(), 0);
    for (int i = 1; i < groups.size(); i++) {
        prefix[i] = groups[i - 1] + prefix[i - 1];
    }

    vector<int> f(total + 1, 0);
    for (int j = 0; j <= total; j++) {
        for (int k = prefix[0]; k < prefix[0] + groups[0]; k++) {
            if (items[k][1] <= j) {
                f[j] = max(f[j], 0 + items[k][2]);
            }
        }
    }

    for (int i = 1; i < groups.size(); i++) {
        for (int j = total; j >= 0; j--) {
            // find max in ith group
            for (int k = prefix[i]; k < prefix[i] + groups[i]; k++) {
                f[j] = f[j];   // no pick
                if (items[k][1] <= j) {
                    f[j] = max(f[j], f[j - items[k][1]] + items[k][2]);
                }
            }
        }
    }

    return f[total];
}
```

## Linear DP

### Longest Non-descending Subsequence

> return the maximum length of non-descending subsequence.

`f[i]` means max length of non-descending subsequence of the first ith subsequence.

For ith element, maximum length of ith is maximum of all max length of the state before i, i.e. `f[i] = max(f[j] if i < j or f[j] + 1 if i >= j), where 0 <= j < i`.

```c++
/**
 * @brief f[i] = max(f[j] if i < j or f[j] + 1 if i >= j), where 0 <= j < i
 * 
 * O(N^2)
 * 
 * @param s
 * @return int
 */
int MaxLengthOfNonDescendingSubsequence(string s) {
    vector<int> f(s.size(), 0);
    f[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (s[i] >= s[j]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }

    return f[s.size() - 1];
}
```

Code with backtracking:

```c++
/**
 * @brief track max subsequence
 * 
 * @param s
 * @return int
 */
string MaxLengthOfNonDescendingSubsequenceII(string s) {
    vector<int> f(s.size(), 0);
    vector<int> pre(s.size(), 0);
    f[0] = 1;

    for (int i = 1; i < s.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (s[i] >= s[j]) {
                f[i] = max(f[i], f[j] + 1);
                pre[i] = j;
            }
        }
    }

    // backtrack
    string result;
    int k = s.size() - 1;
    for (int i = 0, len = f[s.size() - 1]; i < len; i++) {
        result.push_back(s[k]);
        k = pre[k];
    }
    reverse(result.begin(), result.end());

    return result;
}
```
