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

### Mixed Knapsack

> We have different kind items to be chosen, some can be chosen at most one time, some `m` times, and some unlimited. Return the maximum value we can get given a weight constrain.

The basic idea is converting limited item to 0-1 item (bit optimization) and deduct in two cases, one for 0-1 knapsack and the other for unlimited knapsack.

```c++
class Item {
    int kind; // -1 for 0-1, 0 for unlimited, positive number for limited item.
    int weight;
    int value;
}
```

- 1-d implementation

```c++
/**
 * @brief The basic idea is converting limited item to 0-1 item (bit optimization) and
 * deduct in two cases.
 *
 * 1. when ith item is 0-1 item,
 *     2-d f[i][j] = max(f[i-1][j], f[i-1][j-w[i]] + v[i]) if w[i] <= j.
 *  or 1-d formula (scan from end): f[j] = max(f[j'], f[j'-w[i]] + v[i] if w[i] <= j').
 *                                               ^ rolling array
 * 2. when ith item is unlimited item,
 *     2-d f[i][j] = max(f[i-1][j], f[i][j-w[i]] + v[i]) if w[i] <= j.
 *  or 1-d formula (scan from begin): f[j] = max(f[j'], f[j' - w[i]] + v[i] if w[i] <=
 * j').
 * 
 * ex> each i (row) is independent
 *    i\j 0 1 2 ... 200
 *    0 ----  0-1  ----
 *    1 ----  0-1  ----
 *    2 ---- unlmt ----
 *   ...
 *   10 ----  0-1  ----
 * 
 * @param items
 * @param total
 * @return int
 */
int MixedKnapsack(vector<Item> items, int total) {
    vector<Item> newItems;
    for (int i = 0; i < items.size(); i++) {
        if (items[i].kind > 0) {
            // convert limited item to 0-1 item
            for (int k = 1; k <= items[i].limit; k << 1) {
                newItems.push_back(Item(-1, k * items[i].weight, k * items[i].value, 1));
                items[i].limit -= k;
            }
            if (items[i].limit > 0) {
                int offset = items[i].limit;
                newItems.push_back(
                    Item(-1, offset * items[i].weight, offset * items[i].value, 1));
            }
        } else {
            newItems.push_back(items[i]);
        }
    }

    vector<int> f(total + 1, 0);
    // conditional deduction
    for (int i = 0; i < newItems.size(); i++) {
        if (newItems[i].kind == -1) {
            // 0-1
            for (int j = total; j >= newItems[i].weight; j--) {
                f[j] = max(f[j], f[j - newItems[i].weight] + newItems[i].value);
            }
        } else {
            // unlimited
            for (int j = newItems[i].weight; j <= total; j++) {
                f[j] = max(f[j], f[j - newItems[i].weight] + newItems[i].value);
            }
        }
    }

    return f[total];
}
```

### Knapsack with Tracking

Here we will track and return the optimal choice. Take 0-1 knapsack as an example.

The basic idea is to back track from `f[i][j]`. Notice that we cannot use 1-d implementation which dumps (overwrites) info of `f[0...i-1][j]`. So we will track the path in 2-d implementation.

Imagine starting from `f[i][j]`, what's the path that ends with `f[i][j]` and what it means? There are two paths to `f[i][j]`:

- `f[i-1][j]` => `f[i][j]`, do not select ith item.
- `f[i-1][j - w] + v` => `f[i][j]`, select ith item.

```c++
if (f[i][j] == f[i-1][j]) {
    // nothing to do
} else {
    // f[i][j] == f[i-1][j-w] + v
    chosen.push_back(i);
}
```

Notice `chosen` is in reverse order and we need reverse it for the output.

```c++
/**
 * @brief track the path of the optimal plan
 *
 * @param weights
 * @param values
 * @param total
 * @return vector<int>
 */
vector<int> ZeroOneKnapsackWithTracking(vector<int> weights, vector<int> values,
                                        int total) {
    vector<vector<int> > f(weights.size(), vector<int>(total+1, 0));
    
    // init boundary
    for (int j = weights[0]; j <= total; j++) {
        f[0][j] = values[0];
    }

    // deduction
    for (int i = 1; i < weights.size(); i++) {
        for (int j = 0; j <= total; j++) {
            f[i][j] = f[i-1][j];
            if (weights[i] <= j) {
                f[i][j] = max(f[i][j], f[i-1][j - weights[i]] + values[i]);
            }
        }
    }

    // backtrack
    vector<int> chosen;
    int j = total;
    for (int i = weights.size() - 1; i > 0; i--) {
        if (f[i][j] == f[i-1][j - weights[i]] + values[i]) {
            chosen.push_back(i);
            j = j - weights[i];
        }
    }
    if (f[0][j] != 0) chosen.push_back(0); // boundary

    reverse(chosen.begin(), chosen.end());

    return chosen;
}
```

### Counting Optimal Plan

We will count the number of all optimal choices.

First we have to figure out the difference and correlation between two problems.

- 0-1 knapsack requires the total of chosen items must less than or equal to given 'total'.
- 0-1 knapsack requires the total of chosen items must be exactly given 'total'.

Definition of `f` for two problems has totally different meaning.

- In the first case, `f[i][j]` means selecting from first `i` items and the total weight of chosen items should be less than or equal to `j`.
- In the other, `f[i][j]` means selecting from first `i` items and the total weight of chosen items should be exactly `j`.

But These two problems have the same deduction formula:

```text
f[i][j] = max(f[i-1][j], f[i-1][j-w] + v if w <= j)
or
f[j] = max(f[j], f[j-w] + v if w <= j) with a rolling array scanning from end to begin
```

The ONLY difference goes down to the initialization although there is only subtle difference.

```c++
// case 1: <= j
// initialize the boundary, when i == 0
    for (int j = 0; j <= total; j++) {
        f[j] = weights[0] <= j ? values[0] : 0;
    }

// case 2: == j
// initialize the boundary, when i == 0
    for (int j = weights[0]; j <= total; j++) {
        f[j] = -INT_MAX; // can not be chosen
    }
    f[0] = 0;
    f[weights[0]] = values[0];
```

We use a trick in case 2 where all `f[j]` have been set to `-INT_MAX`, which means they cannot be the answer for `f[j]`. There are only two answers for `f[j]` when `i == 0`, `f[0] = 0` and `f[weights[0]] = values[0]` which meets our definition.

One thing worth being underscored is **the optimal value is not necessarily** `f[total]`, it could be `f[total - n]`, where `0 <= n <= total`.

Say if we want to find the max value for the second case:

```c++
int maxVal = 0;
for (int j = 0; j <= total; j++) {
    maxVal = max(maxVal, f[j]);
}
```

Now go back to count the optimal plan.

```c++
/**
 * @brief f[j] and g[j] means the total weight must be 'j', rather than '<= j' as we did
 * before.
 * 
 * f[j] means optimal plan of choosing best value from first ith items and total weight
 * of chosen items MUST be equal to 'j'.
 * 
 * @param weights 
 * @param values 
 * @param total 
 * @return int 
 */
int TotalNumberOfZeroOneKnapsack(vector<int> weights, vector<int> values,
                                        int total) {
    vector<int> f(total + 1, 0);
    vector<int> g(total + 1, 0); // record number of optimal plans given j
    
    // initialize the boundary, when i == 0
    for (int j = weights[0]; j <= total; j++) {
        f[j] = -INT_MAX; // can not be chosen
    }
    f[0] = 0; g[0] = 0; // not choose
    f[weights[0]] = values[0]; g[weights[0]] = 1; // choose

    for (int i = 1; i < weights.size(); i++) {
        for (int j = total; j >= weights[i]; j--) {
            // cannot overwriting since we have to record number of plans
            int t = max(f[j], f[j - weights[i]] + values[i]);
            int sum = 0;
            // total plans comes from two possible states
            if (t == f[j]) sum += f[j];
            if (t == f[j - weights[i]] + values[i]) sum += f[j - weights[i]];
            f[j] = t;
            g[j] = sum;
        }
    }

    // find optimal result
    int maxVal = 0;
    for (int j = 0; j <= total; j++) {
        maxVal = max(maxVal, f[j]);
    }
    int sum = 0;
    // count all paths for optimal result
    for (int j = 0; j <= total; j++) {
        if (f[j] == maxVal) {
            sum += g[j];
        }
    }

    return sum;
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

- Code with backtracking:

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

- Optimization (Greedy Algorithm)

Let's see the problem from the perspective of length. `f[i]` is defined as the minimum of the last number of longest non-descending sequence with length `i`.

Why is it defined like that? One observation is the best choice for current number `nums[i]` to concatenate the longest sequence before it has two properties:

- length of longest sequence is as long as possible
- the last number of the sequence should be as small as possible if there are multiple sequences with the same length. In other words, we can dump all sequence with the same length but the last number being greater than the minimum one. This explains why `f` is a mapping from `len` to `min(last number)`

```text
len  1  1  2  2  3
ex>  2  1  3  2  4  7  6  8  9
        solved      ^   unsolved
                   ptr
then f[0] = 0
     f[1] = min(2, 1) = 1 (len == 1)
     f[2] = min(3, 2) = 2 (len == 2)
     f[3] = min(4)    = 4 (len == 3)
     ...
```

One important property of `f[i]` is it is non-descending. It can be proved with contradiction. Say if `f[i+1] < f[i]`, it means we can find a subsequence in `f[i+1]` **with the length of `i`**, and **the last number** of this subsequence is less than or equal to `f[i+1]`, which means **less than** `f[i]`. This is a contradiction to our definition, which tells us `f[i]` should be the minimum number of the last number in all sequence with length `i`.

Therefore, our algorithm is:

- find the first number less than or equal to `nums[i]` from the end, say `f[m]`. It means it is the best choice for `nums[i]` to concatenate. (binary search: log(N))
- update `f[m+1]` with `nums[i]`, since `nums[i] < f[m+1]` (if not, `f[m+1]` will be the best choice to concatenate).

```c++
/**
 * @brief f[i] is the minimum last number of the sequence with the same length
 * 
 * @param s 
 * @return int 
 */
int MaxLengthOfNonDescendingSubsequenceIII(string s) {
    vector<int> f(s.size() + 1, INT_MAX);   // the last number of subsequence with length i
    f[0] = 0;

    int len = 0;   // track solved range
    for (int i = 0; i < s.size(); i++) {
        // binary search the last one less than or equal to s[i]
        int left = 0, right = len;
        while (left < right) {
            int mid = left + ((right - left) >> 1) + 1;
            if (f[mid] <= s[i]) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        len = max(len, left + 1);
        f[left + 1] = s[i];
    }

    return len;
}
```

### Longest Common Subsequence

> return the longest common subsequence of two strings.

Define `f[i][j]` as the maximum length of longest common subsequences of `sl[1...i]` and `sr[1...j]` (1-indexed).

How to solve `f[i][j]`?

- if `sl[i] == sr[j]`, then `f[i][j] = f[i-1][j-1] + 1`.
- if `sl[i] != sr[j]`, there are three cases:
    - `sl[i]` may contribute to `f[i-1][j-1]` when `i-1` move 1 step forward. If so, `f[i][j-1] = f[i-1][j-1] + 1` and `f[i][j-1] = f[i-1][j-1]` otherwise. But we do not care about if `sl[i]` contributes to `f[i][j-1]`, it will be handled when calculating `f[i][j-1]`. So we can safely say here `f[i][j] = f[i][j-1]`.
    - same to `sr[j]`, `f[i][j] = f[i-1]f[j]`.
    - also `f[i][j] = f[i-1][j-1]` assuming that `sl[i]` and `sr[j]` have no contribution to `f[i-1][j-1]`.

The relationship among them could be diagramed as follows:

```text
    f[i-1][j-1]: (longest common sequence of sl[1...i-1] and sr[1...j-1])
                  |                |               |
               +0 or +1         +0 or +1           |
     sl[i]        |                |       sr[j]   |
              f[i][j-1]        f[i-1][j]           | +1  sl[i] == sr[j]
                  |----------------|               |
                          |                        |
max(f[i][j-1], f[i-1][j]) |                        |
                          |------------------------| 
                       f[i][j]
```

As you can see, `f[i][j]` can be greater than `f[i-1][j-1]` by 1 at most. One thing to note is `sl[i]` and `sr[j]` must have no contribution to `f[i][j-1]` or `f[i-1][j]` when `sl[i] == sr[j]` where these two character together serve as a common character for two subsequences.

```text
ex>   sl = "adbc"  sr = "abec"

Output of f:
    0 1 1 1 
    0 1 1 1 
    0 1 2 2 
    0 1 2 3

Note: the difference of f[i][j], f[i-1][j], f[i][j-1], f[i-1][j-1] is at most 1!
```

```c++
/**
 * @brief f[i][j] = max(f[i-1][j], f[i][j-1], f[i-1][j-1] if sl[i] == sr[j])
 *
 * @param sl
 * @param sr
 * @return int
 */
int LongestCommonSubsequence(string sl, string sr) {
    vector<vector<int> > f(sl.size() + 1, vector<int>(sr.size() + 1, 0));

    // without initializing boundary (1-indexed)
    for (int i = 1; i <= sl.size(); i++) {
        for (int j = 1; j <= sr.size(); j++) {
            f[i][j] = max(f[i-1][j], f[i][j-1]);
            if (sl[i] == sr[j]) {
                f[i][j] = max(f[i][j], f[i-1][j-1] + 1);
            }
        }
    }

    return f[sl.size()][sr.size()];
}
```

Tricks:

- 1-indexed is better in most cases in dynamic programming since we can save our mind from solving boundary case.

### Edit Distance

> Given two strings, and three kinds of operations: `delete`, `add`, and `replace`. Return the minimum number of operations converting `sl` to `sr`.

The definition is similar to that of longest common subsequence. We define `f[i][j]` as the minimum number of operations that converts `sl[1...i]` to sr`[1...j]`.

`f[i][j]` can be divided into three sub problems:

- `delete` operation: delete `sl[i]`, `f[i][j] = f[i-1]f[j] + 1` where `f[i-1][j]` means the minimum number of operations that converts `sl[1...i-1]` to `sr[1...j]`. Given that `sl[1...1-i]` and `sr[1...j]` have matched, we are going to delete `sl[i]`.
- `add` operation: add `sl[i]`, `f[i][j] = f[i]f[j-1] + 1` where `f[i][j-1]` means the minimum number of operations that converts `sl[1...i]` to `sr[1...j-1]`. Similarly, given that `sl[1...i]` and `sr[1...j-1]` have matched, we need to add `sl[i]` (new-added `sl[i]` should be `sr[j]`) to match `sl[1...i]` and `sr[1...j]`.
- `replace` operation: comes from `f[i-1][j-1]` where  `sl[1...i-1]` and `sr[1...j-1]` are already matched.
    - when `sl[i] == sr[j]`, nothing to do. `f[i][j] == f[i-1][j-1]`.
    - when `sl[i] != sr[j]`, we need to replace `sl[i]` with `sr[j]` to match, where `f[i][j] = f[i-1][j-1]`.

```c++
/**
 * @brief f[i][j] means the minimum number of operations that converts sl[1...i] to 
 * sr[1...j].
 * 
 * f[i][j] = f[i-1][j] + 1 (del);
 * f[i][j] = f[i][j-1] + 1 (add);
 * f[i][j] = f[i-1][j-1] + 1 if sl[i] != sr[j]
 *      or = f[i-1][j-1]     if sl[i] == sr[j]
 * 
 * @param sl 
 * @param sr 
 * @return int 
 */
int MinEditDistance(string sl, string sr) {
    vector< vector<int> > f(sl.size() + 1, vector<int>(sr.size() + 1, 0));
    
    // 1-indexed: initialize boundary
    for (int i = 0; i <= sl.size(); i++) {
        f[i][0] = i; // del
    }
    for (int j = 0; j <= sr.size(); j++) {
        f[0][j] = j; // del
    }

    // deduction
    for (int i = 1; i <= sl.size(); i++) {
        for (int j = 1; j <= sr.size(); j++) {
            f[i][j] = f[i-1][j] + 1;
            f[i][j] = min(f[i][j], f[i][j-1] + 1);
            if (sl[i] != sr[j]) {
                f[i][j] = min(f[i][j], f[i-1][j-1] + 1);
            } else {
                f[i][j] = min(f[i][j], f[i-1][j-1]);
            }
        }
    }

    return f[sl.size()][sr.size()];
}
```

### Merging Stones

> Given a piles of stones, each of them has a weight. We need to merge them into one pile. We are only allowed to merge two adjacent piles each time and the cost is weight sum of two piles to be merged. Return the minimum cost to merge stones.

- Priority Queue

The first solution is by priority queue (min heap). The time complexity is O(3N*log(N)) (for each merge, we need pop two elements and push sum of them, each pop and push incurs the update of heap O(log(N))).

But the constraint of 'adjacent' make it hard to solve with priority queue.

- Dynamic Programming

`f[i][j]` is defined as the minimum cost of merging `stones[i...j]`. `f[i][j]` can be divided into `f[i][j] = min(f[i][k] + f[k+1][j] + cost of merging, where k is in the range of [i, j]`). The cost of merging can be solved with `prefix`, which is `prefix[j+1] - prefix[i]`. Note sum of `a[i]` to `a[j]` is `prefix[j+1] - prefix[i]`.

```c++
/**
 * @brief f[i][j] is the minimum cost of combine stones[i...j].
 *
 * f[i][j] = min(f[i][k] + f[k+1][j] + prefix[j+1] - prefix[i]),
 * Note prefix is 0-indexed.
 *
 * @param stones
 * @return int
 */
int MergeStones(vector<int> stones) {
    vector<int> prefix(stones.size() + 1, 0);
    for (int i = 1; i <= prefix.size(); i++) {
        prefix[i] = prefix[i - 1] + stones[i - 1];
    }

    vector<vector<int> > f(stones.size(), vector<int>(stones.size(), INT_MAX));
    // initialize boundary: len == 1
    for (int i = 0; i < stones.size(); i++) {
        f[i][i] = 0;
    }

    // deduction, from shortest length to longer
     for (int len = 2; len <= stones.size(); len++) {
        // enumerate all ranges with length os len, [i, i + len - 1]
        for (int i = 0; i + len - 1 < stones.size(); i++) {
            int j = i + len - 1;
            f[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                // enumerate division
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + prefix[j+1] - prefix[i]);
            }
        }
    }

    return f[0][stones.size() - 1];
}
```

Tricks:

- Range deduction

### Integer Division

> Given an integer `N`, return the number of divisions. `N = A1 + A2 + ... + An`, where `A1 >= A2 >= ... >= An`.
>
> Say, `N` = 5, we have 7 ways to divide it:
>
> - 5 = 5
> - 5 = 4 + 1
> - 5 = 3 + 1 + 1
> - 5 = 2 + 1 + 1 + 1
> - 5 = 1 + 1 + 1 + 1 + 1
> - 5 = 3 + 2
> - 5 = 2 + 2 + 1

The basic idea is that it can be solved as we did in complete knapsacks.

Define `f[i][j]` as the total number of choosing from first `i` integers, and the total number is `j`.

- `f[i][j] = sum(f[i-1][j], f[i-1][j - a[i]], f[i-2][j - 2*a[i]], ..., f[i-k][j - k*a[i]])`, where `a[1] = 1, a[2] = 2, ..., a[k] = k`. Note `a[i] == i`, so it can be simplified as `f[i][j] = sum(f[i-1][j], f[i-1][j - i], f[i-2][j - 2*i], ..., f[i-k][j - k*i])`

The time complexity is O(N^2 * logN). Why we have `logN`? For k of each loop, `k = N / a[i]`. `N / 1 + N / 2 + N / 3 + ... + N / N = N * (1 + 1/2 + 1/3 + ... + 1/N) = theta(log)`, where `1 + 1/2 + 1/3 + ... + 1/N` is Harmonic series `H(N)` and `H(N) >= 1 + logN / 2`

Also, we can optimize deduction formula as we did in complete knapsacks.

- `f[i][j] = sum(f[i-1][j], f[i][j - i])`.

```c++
/**
 * @brief return the number of divisions
 * f[i][j] = sum(f[i-1][j], f[i][j - i])
 * @param n 
 * @return int 
 */
int IntegerDivision(int n) {
    vector< vector<int> > f(n+1, vector<int>(n+1, 0)); // 1-indexed
    for (int i = 0; i <= n; i++) {
        f[i][0] = 1;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i-1][j];
            if (i <= j) {
                f[i][j] += f[i][j-i];
            }
        }
    }

    return f[n][n];
}
```

- 1-d implementation

```c++
int IntegerDivisionII(int n) {
    vector<int> f(n+1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            f[j] = f[j] + f[j-i];
        }
    }

    return f[n];
}
```

Let's think of the problem from the division perspective. Define `f[i][j]` as all the division plans that have j numbers in it and sum of j numbers is i.

Then set `f[i][j]` can be divided into two subsets:

- The plans that have 1 in them. ex> `plan = [1, ..., k]` and `len(plan) = j`.
- The plans whose minimum is greater than 1. ex> `plan = [2, ..., k]` and `len(plan) = j`.

The question is how two subsets are related to `f[i][j]`?

- For the plans with 1 in them. We can subtract 1 from them and we got `f[i][j] (with 1 in each plan) = f[i-1][j-1]`. (the length of each plan is decreased by 1 and total as well).
- For the plans without 1 in them. We will subtract 1 from all numbers of each plan (the length of each plan will not change, but the total will be smaller). Then we got `f[i-j][j]`.

Therefore, we got `f[i][j] = f[i-1][j-1] + f[i-j][j]`.

```c++
/**
 * @brief f[i][j] = f[i-1][j-1] + f[i-j][j]
 * 
 * @param n 
 * @return int 
 */
int IntegerDivisionIII(int n) {
    vector< vector<int> > f(n+1, vector<int>(n+1, 0));

    // boundary: n has only one plan whose length is 1
    for (int i = 1; i <= n; i++) {
        f[i][1] = 1;
    }

    for (int i = 1; i <= n; i++) {
        // j cannot be greater than i, since if we all choose 1, the max len is n
        for (int j = 2; j <= i; j++) {
            f[i][j] = f[i-1][j-1] + f[i-j][j];
        }
    }

    int sum = 0;
    for (int j = 1; j <= n; j++) {
        sum += f[n][j];
    }

    return sum;
}
```

### State Compression

> Given an `N*M` matrix and return how many different ways to fill out the matrix with `1*2` and `2*1` blocks.

This is a classic problem of dynamic programming. The start point to work it out is to figure out the relationship between two adjacent sub problems.

Since there are two kinds of blocks, so we are able to consider the placement of one kind and fill out the rest place with the other ones.

Say we just consider `1*2` blocks. Define `f[i][j]` to be the number of ways to fill out first `i` columns of the matrix and the state of `i-1`th column is `j`.

**State** here is a binary number used to indicate the status of `i`th column. If there is a block go through from `i-1` to `i` (or bit is used to indicate if that location of i-1 col is placed a 1*2 block), then that bit will be set to 1.

```text
               (i)         (j)
row\col   0  1  2  3  4
       0  ?  ----           1
       1  ?                 0
       2  ?  ----           1
       3  ?                 0
       4  ?                 0
when i == 2, i-1 == 1, the status j is 10100
```

Then what's the relationship between `i` and `i-1`.

```text
                (i-1) (i)       (k1) (k2)
row\col   0  1    2    3    4
       0  ?  ------   (x)        1    0
       1  ?       ------         0    1
       2  ?  ------              0    0
       3  ?                      0    0
       4  ?                      0    0
```

We use k to enumerate all possible ways of putting `1*2` blocks on `i`th column. As shown in the diagram above, `k = 100000` is a bad choice, since on the first row `i-1` has placed a block there for some `f[i-1][j]`. However `k = 01000` seems a feasible placement. So, we can check if current placement is feasible by evaluating `j & k == 0` (the bit on both side cannot be 1 simultaneously).

There is another constrain in this problem. Since all the rest cells will be placed with `2*1` blocks. After placing with `k`, the length of consecutive blank cells must be even. That is `j | k` cannot have consecutive 0s with odd size.

```c++
/**
 * @brief return the number of possible plans to fill out the matrix
 *
 * f[i][j] is the number of ways to fill out first i columns of the matrix and the state
 * of i-1th column is j.
 *
 * 1. Enumerate all states and check if it is legal by checking if it has consecutive 0s
 * with odd size, noting that the maximum number of state is 2^n-1 ((1 << n) - 1), say we
 * have 2 rows, the state will be [00, 01, 11].
 * 
 * f[i][j] = sum(f[i-1][k]) where transition from k to j is valid.
 * 
 * @param n: row number of matrix
 * @param m: col number of matrix
 * @return int
 */
int BlockFilling(int n, int m) {
    const int max_state = 1 << n;
    vector<vector<long long> > f(m + 1, vector<long long>(max_state, 0));
    vector<bool> isValidState(max_state, true);
    vector<vector<bool> > isValidTrans(max_state, vector<bool>(max_state, false));

    // preprocessing states
    // 1. find all valid states, meaning no consecutive 0s with odd size.
    for (int state = 0; state < max_state; state++) {
        int cnt0 = 0;
        for (int mask = 0x01; mask < max_state; mask = mask << 1) {
            if ((mask & state) == mask) {
                // current bit is 1
                if (cnt0 & 1) {
                    // if length is odd
                    isValidState[state] = false;
                    break;
                }
            } else {
                // current bit is 0
                cnt0++;
            }
        }
        // for states ending with 0, process the last sequence of 0s
        if (cnt0 & 1) {
            isValidState[state] = false;
        }
    }

    // 2. find all valid transition. (k & j == 0)
    for (int dst = 0; dst < max_state; dst++) { // state of ith col
        for (int src = 0; src < max_state; src++) { // state of i-1th col
            if ((src & dst) == 0 && isValidState[src | dst]) {
                // src & dst == 0 means it cannot be 1 on the same bit of two binary numbers
                // src | dst explains the state of i-1 after inserting i'th plan (dst)
                isValidTrans[src][dst] = true;
            }
        }
    }

    // means the first-1 (imagined) column cannot be placed 1*2 block. From the perspective
    // of the 1st col, there is no 1*2 block end on the first column (which is the starting
    // state).
    f[0][0] = 1; // state of 0-1 is 0x0000
    // deduction
    for (int i = 1; i <= m; i++) {
        // j enumerates possible states of i-1
        for (int j = 0; j < max_state; j++) {
            // k enumerates possible states of i-2
            for (int k = 0; k < max_state; k++) {
                if (isValidTrans[k][j]) {
                    f[i][j] += f[i-1][k];
                }
            }
        }
    }

    // which means the last column cannot be placed 1*2 block
    return f[m][0];
}
```

### Shortest Hamilton Distance

> Given a non-directed graph, calculate the shortest Hamilton distance from 0 to vertex n-1. Hamilton path requires the path covers all vertexes in the graph and each vertex can only be visited one time.

Different from another classic problem, known as shortest path from an origin, which can be solved with Dijkstra's algorithm. But this problem is a non-directed graph rather than directed.

Define `f[i][j]` is the minimum path from origin (0) to vertex `j` and go through the vertexes in `i`, which is a binary state. Say we have 4 vertex, then `i` is a 4-bit binary number to describe covered vertexes **including the last vertex, destination**.

A hamilton problem can be represented with `f[i][j]`. for example,

```text
vertexes: 0,  1,  2,  3,  4

f[11111, 1]: means the shortest hamilton path from 0 to 1.
f[11111, 2]: means the shortest hamilton path from 0 to 2.
...
f[11111, 4]: means the shortest hamilton path from 0 to 4, which is our problem.

Also, we can use f[i][j] to represent sub problems:
f[00001, 0]: means the shortest hamilton path from 0 to 0.
      ^ zero vertex bit
f[00011, 1]: means the shortest hamilton path from 0 to 1 in the sub graph (0, 1)
...
f[00101, 2]: means the shortest hamilton path from 0 to 2 in the sub graph (0, 2)
f[11001, 4]: means the shortest hamilton path from 0 to 4 in the sub graph (0, 3, 4)
```

So, a valid state should cover the start point and end point as shown above. `f[10001, 2]` is an invalid state since it represents the shortest hamilton path from 0 to 2 in the sub graph (0, 4), which is impossible.

Deduction: say our problem is `f[11111, 4]`. Which sub problem contributes the solution to `f[11111, 4]`? If 2 and 3 are directly connected with 4, then `f[11111, 4]` is the minimum of

- `f[01111, 2] + w[2, 4]`, shortest Hamilton path from 0 to 2 in sub graph (0, 1, 2, 3) (4 must be excluded!)
- `f[01111, 3] + w[3, 4]`, shortest Hamilton path from 0 to 3 in sub graph (0, 1, 2, 3) (4 must be excluded!)

Deduction: what we care about is what's the vertexes directly connected to `j`. Say that point is `k`, then according to the definition of Hamilton distance, `f[i][j] = f[i'][k] + cost[k][j]` and `k` must be in the state and `j` cannot be in the state.


```c++
/**
 * @brief return the shortest path from vertex 0 to the last vertex
 *
 * f[i][j] = f[i'][k] + cost[k][j], f[i'][k] == f[i-k][k] if k is in i or f[i+k][k] if k
 * is not in i.
 *
 * i is a binary number representing state and j is the number of the last vertex.
 *
 * @param graph
 * @return vector<int>
 */
int ShortestHamiltonPath(vector<vector<int> > graph) {
    // [0, 2^size - 1], [0, 11...11] (a set of size-bit binary numbers)
    int max_state = 1 << graph.size();
    vector<vector<int> > f(max_state, vector<int>(graph.size(), 1e5));   // 0-based

    // initialization
    f[1][0] = graph[0][0];   // reach vertex 0 starting from vertex 0

    // deduction
    int start_mask = 0x1;
    for (int state = 1; state < max_state; state++) {
        if (state & start_mask) {   // state must include start point
            for (int j = 0; j < graph.size(); j++) {
                if (state >> j & 1) {
                    for (int k = 0; k < graph.size(); k++) {
                        if ((state - (1 << j)) >> k & 1) {
                            f[state][j] =
                                min(f[state][j], f[state - (1 << j)][k] + graph[k][j]);
                        }
                    }
                }
            }
        }
    }

    // f[1111111][last vertex]
    return f[max_state - 1][graph.size() - 1];
}
```

Tricks:

- Check if ith bit is 1: `state >> i & 1` or `state & ith mask == ith mask`.
- Given ith bit is 1, set it to be 0: `state - i << 1` or `state ^ i << 1`, the latter is more general since `state & i << 1` can be used to reverse ith bit.
- everything XOR(`^`) `0000` is itself and everything XOR itself is `0000`. It can be used to match characters.
