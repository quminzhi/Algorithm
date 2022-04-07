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

## Count Dynamic Programming

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

## State Dynamic Programming

### Filling Matrix

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

## Tree-like Dynamic Programming

> Assuming there are N workers in a company, they have different occupation. There job hierarchy can be represented with a tree. The parent worker is the direct leader of its children. Say we have a party and each worker has an expectation value for the party. But when a worker and his direct leader come to party at the same time, the worker will be unhappy. So we need to avoid that thing to happen. Return the maximum expectation of the tree if we will select only the part of workers to join the party.

This is a dynamic programming problem with tree-like updating logic.

Since the co-existence of worker and his direct leader should be avoided, we should take into consideration if the current node is selected (our second parameter). Define `f[u, 0]` as the maximum expectation of selecting from `u`'s subtree and do not select `u` (indicated by 0). Similarly, define `f[u, 1]` as the maximum expectation of selecting from `u`'s subtree and select `u`.

So, the deduction is

- `f[u, 0] = sum of max(f[si, 0], f[si, 1])`, where `si` is `u`'s direct children. If `u` is not selected, its children can be selected or not.
- `f[u, 1] = sum of f[si, 0]`, since `u` has been selected.

The definition of `TreeNode`:

```c++
class TreeNode {
   public:
    TreeNode() : id(0), parent(-1) {};
    TreeNode(int _id) : id(_id), parent(-1) {};

    int id;
    int parent;
    vector<int> children;
};
```

Tree-like dp:

```c++
void dfs(vector<vector<int> >& f, vector<TreeNode>& tree, vector<int>& exp, int u) {
    f[u][1] = exp[u];
    // solve children
    for (int i = 0; i < tree[u].children.size(); i++) {
        int child = tree[u].children[i];
        dfs(f, tree, exp, child);   // tree-like dp
        f[u][0] += max(f[child][0], f[child][1]);
        f[u][1] += f[child][0];
    }
}

/**
 * @brief return the maximum expectation of selection
 * 
 * Because it is a hierarchy tree, there must be n-1 rel (edges) when there are n workers (nodes)
 * 
 * @param exp: expectation of each worker
 * @param rel: relationship between two workers, worker -> leader
 * @return int 
 */
int PartyWithoutLeader(vector<int> exp, vector<vector<int> > rel) {
    // initialize tree
    vector<TreeNode> tree(exp.size());
    for (int i = 0; i < exp.size(); i++) {
        tree[i].id = i;
    }
    // build up relationship
    for (int i = 0; i < rel.size(); i++) {
        tree[rel[i][0]].parent = rel[i][1];
        tree[rel[i][1]].children.push_back(rel[i][0]);
    }

    vector<vector<int> > f(exp.size(), vector<int>(2, 0));
    // find root node, notice root is not necessarily on index 0.
    int root = 0;
    for (; root < tree.size() && tree[root].parent != -1; root++) {}

    dfs(f, tree, exp, root);

    return max(f[root][0], f[root][1]);
}
```

## Heuristic Dynamic Programming

### Skating

> Given a matrix which represents an elevation map, return the maximum length of paths starting from ANY point in the matrix. We are able to go from higher place to lower place.

Define `f[i, j]` as the maximum length of paths starting from (i, j).

There are four choices: up, left, right, down.

`f[i, j] == 1 + max(f[i-1, j], f[i, j-1], f[i+1, j], f[i, j+1])` if we can go from (i, j) to this place (`h[i][j]` > height of these places).

```c++
int dfs_skating(vector<vector<int> >& f, vector<vector<int> >& h, int x, int y) {
    static int dir_x[4] = {-1, +1, 0, 0};
    static int dir_y[4] = {0, 0, -1, +1};

    // if f[x][y] is calculated, return result
    if (f[x][y] != -1) return f[x][y];

    f[x][y] = 1; // path has length of at least 1 (start point)
    for (int i = 0; i < 4; i++) {
        int nx = x + dir_x[i];
        int ny = y + dir_y[i];
        if (nx >= 0 && nx < h.size() && ny >= 0 && ny < h[0].size() && h[x][y] > h[nx][ny]) {
            f[x][y] = max(f[x][y], dfs_skating(f, h, nx, ny) + 1);
        }
    }

    return f[x][y];
}

/**
 * @brief return the maximum length of paths starting from (i, j)
 * Define `f[i, j]` as the maximum length of paths starting from (i, j).
 * 
 * f[i, j] == 1 + max(f[i-1, j], f[i, j-1], f[i+1, j], f[i, j+1])
 * 
 * @param h 
 * @return int 
 */
int Skating(vector<vector<int> > h) {
    vector<vector<int> > f(h.size(), vector<int>(h[0].size(), -1));
    int res = 0;
    for (int i = 0; i < h.size(); i++) {
        for (int j = 0; j < h[0].size(); j++) {
            res = max(res, dfs_skating(f, h, i, j));
        }
    }

    return res;
}
```

## Related Problems

### House Robber

> You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
>
> Given an integer array `nums` representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Define `f[i]` as:

- problem sets: select from first i houses.
- property: maximum value.

Deduction: we have two choices on `i`th house, robbing or not.

- `f[i] = f[i-2] + w[i]`, if robbing `i`th house.
- `f[i] = f[i-1]`, if not robbing `i`th house.

So, `f[i] = max(f[i-2] + w[i], f[i-1])`.

```c++
int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    if (nums.size() == 2) return max(nums[0], nums[1]);
    vector<int> f(nums.size(), 0);
    // base case
    f[0] = nums[0];
    f[1] = max(nums[0], nums[1]);
    // deduction
    for (int i = 2; i < nums.size(); i++) {
        f[i] = max(f[i - 1], f[i - 2] + nums[i]);
    }

    return f[nums.size() - 1];
}
```

### Min Cost Climbing Stairs

> You are given an integer array cost where `cost[i]` is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.
>
> You can either start from the step with index 0, or the step with index 1.
>
> Return the minimum cost to reach the top of the floor.

Define `f[i]` as:

- problem sets: all paths from step 0 to step i.
- property: the minimum cost.

Deduction:

- 1 step to `i`th step: `f[i] = f[i-1] + cost[i-1]`.
- 2 steps to `i`th step: `f[i] = f[i-2] + cost[i-2]`.

So, `f[i] = min(f[i-1] + cost[i-1], f[i-2] + cost[i-2])`.

```c++
int minCostClimbingStairs(vector<int>& cost) {
    if (cost.size() < 2) return 0;
    int top_idx = cost.size() + 1;
    vector<int> f(top_idx, 1e4);
    
    // base case: either start from 0th or 1th step
    f[0] = 0;
    f[1] = 0;
    // deduction
    for (int i = 2; i < top_idx; i++) {
        f[i] = min(f[i - 1] + cost[i - 1], f[i - 2] + cost[i - 2]);
    }

    return f[top_idx - 1];
}
```

### N-th Tribonacci Number

> The Tribonacci sequence Tn is defined as follows:
>
> - `T0 = 0, T1 = 1, T2 = 1`, and `Tn+3 = Tn + Tn+1 + Tn+2` for `n` >= 0.
>
> Given `n`, return the value of `Tn`.

Define `f[i] = f[i-3] + f[i-2] + f[i-1]`.

```c++
int tribonacci(int n) {
    if (n == 0) return 0;
    if (n < 3) return 1;
    int max_n = 37;
    vector<int> f(max_n + 1, 0);
    f[1] = 1;
    f[2] = 1;
    for (int i = 3; i <= n; i++) {
        f[i] = f[i - 3] + f[i - 2] + f[i - 1];
    }

    return f[n];
}
```

### Delete and Earn

> You are given an integer array `nums`. You want to maximize the number of points you get by performing the following operation any number of times:
>
> - Pick any `nums[i]` and delete it to earn `nums[i]` points. Afterwards, you must delete every element equal to `nums[i] - 1` and every element equal to `nums[i] + 1`.
>
> Return the maximum number of points you can earn by applying the above operation some number of times.

One observation is that if one number is selected, all its replicates should be selected to achieve maximum interest. We can convert the input into a form that easy to use `{num : time of occurrence}`.

Define `f[i]` as:

- problem sets: all kinds of operations on first `i` numbers, i.e. ranging from [0...i].
- property: maximum points earned.

Deduction:

- select `i`th number: `f[i] = f[i-2] + earns[i]`.
- do not select `i`th number: `f[i] = f[i-1]`.

So, `f[i] = max(f[i-2] + earns[i], f[i-1]`.

```c++
int deleteAndEarn(vector<int>& nums) {
    vector<int> earned(1e4 + 10, 0);   // maximum of nums[i] <= 10^4
    sort(nums.begin(), nums.end());
    int num = nums[0], cnt = 1;
    int maxVal = num;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != num) {
            earned[num] = num * cnt;
            num = nums[i];
            cnt = 1;
            // update max value
            if (nums[i] > maxVal) {
                maxVal = nums[i];
            }
        } else {
            cnt++;
        }
    }
    // add the last one
    earned[num] = num * cnt;
    if (num > maxVal) {
        maxVal = num;
    }

    // dp
    vector<int> f(earned.size(), 0);
    f[0] = earned[0];
    f[1] = max(earned[0], earned[1]);   // we can choose either 0 or 1
    for (int i = 2; i <= maxVal; i++) {
        f[i] = max(f[i - 1], f[i - 2] + earned[i]);
    }

    return f[maxVal];
}
```

### Maximum Score from Performing Multiplication Operations

> You are given two integer arrays nums and multipliers of size n and m respectively, where n >= m. The arrays are 1-indexed.
>
> You begin with a score of 0. You want to perform exactly m operations. On the ith operation (1-indexed), you will:
>
> - Choose one integer x from either the start or the end of the array nums.
> - Add `multipliers[i] * x` to your score.
> - Remove x from the array nums.
> 
> Return the maximum score after performing m operations.

Define `f[i][j]` as:

- problem sets: all kinds of choices of selection from `nums[i...end]` and the first `j` elements of multipliers.
- `end` can be calculated. Since sum of # of selecting from begin and end should be `j` and # of selecting from the start is `i`, we got `end = multipliers.size() - 1 - j - i`.
- property: the maximum number of `f`.

The problem can be solved with recursion plus memorization.

```c++
/**
 * @brief recursively solve the problems with memorization.
 *
 * @param nums
 * @param multiplies
 * @param i: ith step.
 * @param result
 */
int maximumScoreHelper(vector<int>& nums, vector<int>& multipliers,
                       vector<vector<int> >& f, int begin, int i) {
    if (f[begin][i] != -1e4) {
        return f[begin][i];
    }
    
    int end = nums.size() - 1 - (i - begin);
    if (i == multipliers.size() - 1) {
        // check if it is the maximum score
        return max(nums[begin] * multipliers[i], nums[end] * multipliers[i]);
    }

    int maxVal = max(
        maximumScoreHelper(nums, multipliers, f, begin + 1, i + 1) +
            nums[begin] * multipliers[i],
        maximumScoreHelper(nums, multipliers, f, begin, i + 1) + nums[end] * multipliers[i]);
    return maxVal;
}

/**
 * @brief the max score we can get.
 *
 * define memory as f[i][j]: i is begin of nums, and j means jth step of multipliers.
 *
 * the end can be calculated by nums.size() - 1 - (j - i), where 'j - i' is # of selecting
 * the end 'i' is # of selecting the begin.
 *
 * @param nums
 * @param multipliers
 * @return int
 */
int maximumScore(vector<int>& nums, vector<int>& multipliers) {
    vector<vector<int> > f(multipliers.size(), vector<int>(multipliers.size(), -1e4));
    int result = maximumScoreHelper(nums, multipliers, f, 0, 0);
    return result;
}
```

### Minimal Square

> Given an `m x n` binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Define `f[i, j]` as the side length of the maximum square **whose bottom right corner** is the cell with index (i,j) in the original matrix. In other word, there is a square with length of `f[i, j]` whose bottom right corner is (i, j).

for example,

```text
+---+
| 1 |
+---+ (i, j)  <--- the bottom right corner of this square

so f[i, j] = 1 (max side length)

+---+
| 0 |
+---+ (i, j)  <--- f[i, j] = 0, no 1's square with bottom right corner of (i, j)

To form a square with side length of 2, it requires (i-1, j), (i, j-1), and (i-1, j-1) all have at least 1 square ends with them.

+---+---+
| 1 | 1 |
|---|---|
| 1 | 2 |
+---+---+ (i, j)

similarly, imagine there is a square with side length of 2 on each cell, we can form a square with side length of 3 ending with (i, j)

+---+---+
| 2 | 2 |
|---|---|
| 2 | 3 |
+---+---+ (i, j)
```

So, we got deduction formula:

`f[i, j] = min(f[i-1][j], f[i][j-1], f[i-1][j-1]) + 1`, if `matrix[i, j] = 1`. `f[i, j] = 0` otherwise.

```c++
int maximalSquare(vector<vector<char> >& matrix) {
    vector< vector<int> > f(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0)); // 1-based

    int maxLen = 0;
    for (int i = 1; i <= matrix.size(); i++) {
        for (int j = 1; j <= matrix[0].size(); j++) {
            if (matrix[i-1][j-1] == '1') {
                f[i][j] = min(f[i][j-1], f[i-1][j]);
                f[i][j] = min(f[i][j], f[i-1][j-1]);
                f[i][j] += 1;
                maxLen = max(maxLen, f[i][j]);
            }
        }
    }

    return maxLen * maxLen;
}
```

### Minimum Difficulty of a Job Schedule

> You want to schedule a list of jobs in `d` days. Jobs are dependent (i.e To work on the ith job, you have to finish all the jobs `j` where `0 <= j < i`).
>
> You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the `d` days. The difficulty of a day is the maximum difficulty of a job done on that day.
>
> You are given an integer array `jobDifficulty` and an integer `d`. The difficulty of the ith job is `jobDifficulty[i]`.
>
> Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

This is a classic grouping problem. Define `f[i, j]` as: (how to describe the assigned jobs for ith day?)

- problem sets: all arrangements up to `i`th day and the last scheduled job is `j`. `i` indicates the first `i` days and `j` the last index of scheduled jobs.
- property: minimum difficulty.

Deduction:

- `f[i, j] = f[i-1, j-k] + jobDifficulty of ith day`. Since it is required that each day has at least 1 scheduled job, `k` is in range `j-k >= i-1` ==> `1 < k <= j - i + 1`.
- `jobDifficulty of ith day = max(jobDifficulty[j-k+1...j])`.

```c++
/**
 * @brief return the minimum difficulty of job scheduling
 *
 * `f[i, j] = f[i-1, j-k] + jobDifficulty of ith day`, j >= i  is must
 *
 * how to obtain max of a specific range? track along the process
 * how to obtain sum of a specific range? prefix.
 *
 * @param jobDifficulty
 * @param d
 * @return int
 */
int minDifficulty(vector<int>& jobDifficulty, int d) {
    if (jobDifficulty.size() < d) return -1;
    if (jobDifficulty.size() == d) {
        int sum = 0;
        for (int i = 0; i < jobDifficulty.size(); i++) {
            sum += jobDifficulty[i];
        }
        return sum;
    }

    vector<vector<int> > f(d, vector<int>(jobDifficulty.size(), 1e6));

    // initialize when i = 0
    int hardest = 0; // track hardest job from [j-k+1 to j]
    for (int j = 0; j < jobDifficulty.size(); j++) {
        hardest = max(hardest, jobDifficulty[j]);
        f[0][j] = hardest;
    }

    for (int i = 1; i < d; i++) {
        for (int j = i; j < jobDifficulty.size(); j++) {
            // select last k job for ith day
            hardest = 0;
            for (int k = 1; k <= j - i + 1; k++) {
                hardest = max(hardest, jobDifficulty[j - k + 1]);
                f[i][j] = min(f[i][j], hardest + f[i - 1][j - k]);
            }
        }
    }

    return f[d - 1][jobDifficulty.size() - 1];
}
```

### Coin Change

> You are given an integer array `coins` representing coins of different denominations and an integer amount representing a total amount of money.
>
> Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
>
> You may assume that you have an infinite number of each kind of coin.

This is a unlimited knapsack problem. Define `f[i][j]` as follows:

- problem sets: all combinations of selection from first `i` coins and total amount is `j`.
- property: the fewest number of coins.

Deduction:

- continue to select ith coin: `f[i][j] = f[i][j-coins[i]] + 1`.
- do not select ith coin: `f[i][j] = f[i-1][j]`.

So, we got `f[i][j] = min(f[i][j-coins[i]], f[i-1][j]) + 1`.

```c++
/**
 * @brief f[i][j] = min(f[i-1][j], f[i][j-coins[i]] + 1)
 *
 * @param coins
 * @param amount
 * @return int
 */
int coinChange(vector<int>& coins, int amount) {
    vector<vector<int> > f(coins.size(), vector<int>(amount + 1, 1e5));
    for (int j = 1; j <= amount; j++) {
        if (j % coins[0] == 0) {
            f[0][j] = j / coins[0];
        }
    }
    for (int i = 0; i < coins.size(); i++) {
        f[i][0] = 0;
    }

    for (int i = 1; i < coins.size(); i++) {
        for (int j = 0; j <= amount; j++) {
            f[i][j] = f[i-1][j]; // no choose from ith
            if (j >= coins[i]) {
                f[i][j] = min(f[i][j], f[i][j - coins[i]] + 1); // choose
            }
        }
    }

    int res = f[coins.size()-1][amount] == 1e5 ? -1 : f[coins.size()-1][amount];
    return res;
}
```

or 1-d implementation with rolling array:

```c++
int coinChange(vector<int>& coins, int amount) {
    vector<int> f(amount + 1, 1e5);
    f[0] = 0;

    for (int i = 0; i < coins.size(); i++) {
        for (int j = coins[i]; j <= amount; j++) {
            f[j] = min(f[j], f[j - coins[i]] + 1); // choose
        }
    }

    int res = f[amount] == 1e5 ? -1 : f[amount];
    return res;
}
```

### Word Break

> Given a string `s` and a dictionary of strings `wordDict`, return true if `s` can be segmented into a space-separated sequence of one or more dictionary words.
>
> Note that the same word in the dictionary may be reused multiple times in the segmentation.

```text
Input:  s = "applepenapple", wordDict = ["apple","pen"]
Answer: true
```

Define `f[i]` as:

- problem sets: all divisions of first `i` characters in the string `s`.
- property: true if word break successfully.

Deduction:

- select kth word from `workDict` as ith choice.

`f[i] = f[i-len(wordDict[k])]` if `wordDict[k]` matches last `len(wordDict[k])` characters of `s`. `f[i] = false`, if all matches failed on ith match.

```c++
/**
 * @brief check if there is a word breakdown for s
 *
 * @param s
 * @param wordDict
 * @return true
 * @return false
 */
bool wordBreak(string s, vector<string>& wordDict) {
    vector<bool> f(s.size(), false);

    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < wordDict.size(); j++) {
            // conds:
            // 1. f[i](s[0..i]) has not found correct breakdown.
            // 2. s[0..i] with length of i + 1 has at least size of word[j].
            // 3. word[j] matches last k characters (s[k - word[i].size + 1..i]).
            if (!f[i] && i + 1 >= wordDict[j].size() &&
                // s[k..i]: i - k + 1 = word[i].size => k = i - word[i].size + 1
                s.substr(i - wordDict[j].size() + 1, wordDict[j].size()) == wordDict[j]) {
                // if (i - wordDict[j].size() >= 0) { // unsigned int overflow
                if (i - wordDict[j].size() + 1 > 0) {
                    // k > 0
                    f[i] = f[i - wordDict[j].size()];
                } else {
                    f[i] = true;
                }
            }
        }
    }

    return f[s.size() - 1];
}
```

### Longest Increasing Subsequence

> Given an integer array `nums`, return the length of the longest strictly increasing subsequence.
>
> A **subsequence** is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, `[3,6,2,7]` is a subsequence of the array `[0,3,1,6,2,2,7]`.

Define `f[i]` as:

- problem sets: all increasing subsequence of `nums[0..i]` ending with `nums[i]`.
- property: length of longest subsequence.

Deduction:

- `f[i] = max( f[i-j] or f[i-j] + 1 if nums[i-j] == nums[i]`, where `0 < j < i`.

```c++
/**
 * @brief f[i] = max( f[i-j] or f[i-j] + 1 if nums[i-j] == nums[i], where 0 < j < i
 *
 * @param nums
 * @return int
 */
int lengthOfLIS(vector<int>& nums) {
    vector<int> f(nums.size(), 1);
    
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 1; j <= i; j++) {
            if (nums[i] > nums[i - j]) {
                f[i] = max(f[i], f[i - j] + 1);
            }
        }
    }

    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
        res = max(res, f[i]);
    }

    return res;
}
```

### Best Time to Buy and Sell Stock IV

> You are given an integer array prices where `prices[i]` is the price of a given stock on the ith day, and an integer `k`.
>
> Find the maximum profit you can achieve. You may complete **at most** k transactions.
>
> Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
>
> One transaction includes buy and sell once.

Top-Bottom method: Define `f[i][j][k]` as:

- problem sets: on ith day, we have at most j transactions and we are holding a stock now (k == 1) or not holding (k == 0).
- property: max profit we can get.

Deduction:

- On ith day, if we are holding a stock:
    - if we sold on ith day, we got `price[i]`. `f[i][j][1] = f[i+1][j-1][0] + price[i]`.
    - if we do not sold on ith day. `f[i][j][1] = f[i+1][j][1]`.
    - we cannot buy on ith day.
- On ith day, if we are not holding a stock:
    - if we buy on ith day, we got `-price[i]`. `f[i][j][0] = f[i+1][j][1] - price[i]`.
    - if we do not buy on ith day. `f[i][j][0] = f[i+1][j][0]`.

```c++
int maxProfitHelper(vector<vector<vector<int>>>& f, vector<vector<vector<bool>>>& visited,
                    const vector<int>& prices, int i, int j, int k) {
    if (i >= prices.size()) return 0;
    if (j <= 0) return 0;

    if (visited[i][j][k]) {
        return f[i][j][k];
    } else {
        visited[i][j][k] = true;
        if (k == 0) {
            // if we are not holding a stock: buy or not buy
            f[i][j][k] = max(maxProfitHelper(f, visited, prices, i + 1, j, 1) - prices[i],
                             maxProfitHelper(f, visited, prices, i + 1, j, 0));
        } else {
            // holding
            f[i][j][k] =
                max(maxProfitHelper(f, visited, prices, i + 1, j - 1, 0) + prices[i],
                    maxProfitHelper(f, visited, prices, i + 1, j, 1));
        }
        return f[i][j][k];
    }
}

/**
 * @brief return the best profit
 *
 * @param k
 * @param prices
 * @return int
 */
int maxProfit(int k, vector<int>& prices) {
    vector<vector<vector<int>>> f(prices.size(),
                                  vector<vector<int>>(k + 1, vector<int>(2, 0)));
    vector<vector<vector<bool>>> visited(
        prices.size(), vector<vector<bool>>(k + 1, vector<bool>(2, false)));

    return maxProfitHelper(f, visited, prices, 0, k, 0);
}
```

### Best Time to Buy and Sell Stock with Cooldown

> You are given an array prices where `prices[i]` is the price of a given stock on the ith day.
>
> Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
>
> - After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
>
> Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

This problem is similar to the one above other than constrains. In the last problem, the constrain is limitation of number of transaction while in this problem it becomes cooldown day.

It can be solved in a similar way. Define `f[i][j][k]` as `i` means we are processing ith day, `j` indicates the day when the stock is sold out last time, and `k` is a binary number with 1 representing holding a stock and 0 not.

On ith day, there are three cases:

- if `i == j+1`, only thing we can do is doing nothing, `f[i][j][k] = f[i+1][j][k]`
- if `k == 0` (not holding a stock) and `i != j+1` (not in cooldown day), I can choose to buy on ith day or not.
    - if buying one, `f[i][j][k] = f[i+1][j][1] - prices[i]`
    - if not, `f[i][j][k] = f[i+1][j][k]`
- if `k == 1` (holding a stock),
    - if selling the stock, `f[i][j][k] = f[i+1][i][0] + prices[i]`
    - if not, ``f[i][j][k] = f[i+1][j][k]`

```c++
int maxProfitHelperII(vector<vector<vector<int>>>& f,
                      vector<vector<vector<bool>>>& visited, const vector<int>& prices,
                      int i, int j, int k) {
    if (i >= prices.size()) {
        return 0;
    }

    if (visited[i][j][k]) {
        return f[i][j][k];
    }

    if (k == 1) {
        f[i][j][k] = max(maxProfitHelperII(f, visited, prices, i + 1, i, 0) +
                             prices[i],   // sell and update selling day
                         maxProfitHelperII(f, visited, prices, i + 1, j, k));
    } else {
        // check if this is cooldown day if i want to buy a stock
        if (j != 0 &&
            i == j + 1) {   // if j has been updated (at least 1 trans completed)
            f[i][j][k] = maxProfitHelperII(f, visited, prices, i + 1, j, k);
        } else {
            f[i][j][k] = max(
                maxProfitHelperII(f, visited, prices, i + 1, j, 1) - prices[i],   // buy
                maxProfitHelperII(f, visited, prices, i + 1, j, k));
        }
    }

    visited[i][j][k] = true;
    return f[i][j][k];
}

/**
 * @brief different constrains compared to the last problem
 *
 * @param prices
 * @return int
 */
int maxProfit(vector<int>& prices) {
    vector<vector<vector<int>>> f(prices.size(),
                                  vector<vector<int>>(prices.size(), vector<int>(2, 0)));
    vector<vector<vector<bool>>> visited(
        prices.size(), vector<vector<bool>>(prices.size(), vector<bool>(2, false)));

    int ret = maxProfitHelperII(f, visited, prices, 0, 0, 0);

    return ret;
}
```

### Min Cost Climbing Stairs II

> You are given an integer array cost where `cost[i]` is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.
>
> You can either start from the step with index 0, or the step with index 1.
>
> Return the minimum cost to reach the top of the floor.

- Top to bottom:

```c++
int minCostClimbingStairsHelper(vector<int>& f, vector<bool>& visited, vector<int>& cost,
                                int start) {
    if (start >= cost.size()) {
        return 0;
    }

    if (visited[start]) {
        return f[start];
    }

    f[start] =
        cost[start] + min(minCostClimbingStairsHelper(f, visited, cost, start + 1),
                          minCostClimbingStairsHelper(f, visited, cost, start + 2));

    return f[start];
}

/**
 * @brief return the minimum cost of climbing stairs, recursion plus memo
 *
 * @param cost
 * @return int
 */
int minCostClimbingStairsII(vector<int>& cost) {
    vector<int> f(cost.size(), 1e5);
    vector<bool> visited(cost.size(), false);
    return min(minCostClimbingStairsHelper(f, visited, cost, 0),
               minCostClimbingStairsHelper(f, visited, cost, 1));
}
```

- Bottom to top

Define `f[i]` as minimum cost from 0 to `i` (where `i` is the top index). And the deduction is `f[i] = min(f[i-1] + cost[i-1], f[i-2] + cost[i-2])`.

```c++
int minCostClimbingStairsIII(vector<int>& cost) {
    vector<int> f(cost.size() + 1, 1e5);
    f[0] = f[1] = 0;
    for (int i = 2; i <= cost.size(); i++) {
        f[i] = min(f[i - 1] + cost[i - 1], f[i - 2] + cost[i - 2]);
    }

    return f[cost.size()];
}
```

- State Compression

Note that `f[i]` only relies on `f[i-1]` and `f[i-2]`, and we are only concerned about the result (`f[top]`) rather than intermediate calculations. So we can save array space with some variables.

```c++
int minCostClimbingStairsIV(vector<int>& cost) {
    int twosteps = 0;
    int onestep = 0;
    int top;
    for (int i = 2; i <= cost.size(); i++) {
        top = min(twosteps + cost[i-2], onestep + cost[i-1]);
        // update iteratively for the next top
        twosteps = onestep;
        onestep = top;
    }

    return top;
}
```

### Paint Fence

> You are painting a fence of `n` posts with `k` different colors. You must paint the posts following these rules:
>
> - Every post must be painted exactly one color.
> - There CANNOT be three or more consecutive posts with the same color.
>
> Given the two integers n and k, return the number of ways you can paint the fence.

Define `f[i]` as

- problem sets: all paints first `i` posts with k colors.
- property: count.

Deduction: on `i`th fence,

- painting the color different from `i-1`th post. Then we have `(k - 1) * f[i-1]` plans.
- painting the color same as `i-1`th post WHEN painting `i-1`th post with different color than `i-2`th post. How many ways do we have? Painting `i`th post with the same color with `i-1`th, there is only one choice. And painting different colors for `i-1`th post from `i-2`th post, there are `k - 1` choices for `i-1`th post and `f[i-2]` choices for `i-2`th post.

So, `f[i] = (k - 1) * f[i-1] + 1 * (k - 1) * f[i-2]`.

with base case `f[0] = k`, `f[1] = k * k`.

```c++
int numWays(int n, int k) {
    int N_MAX = 52;
    int f[N_MAX];
    memset(f, 0, sizeof(f[0]) * N_MAX);
    
    f[0] = k; f[1] = k * k;
    for (int i = 2; i < n; i++) {
        f[i] = (k - 1) * f[i-1] + (k - 1) * f[i-2];
    }

    return f[n-1];  // 0-indexed
}
```

### Coin Change II

> You are given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.
>
> Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.
>
> You may assume that you have an infinite number of each kind of coin.
>
> The answer is guaranteed to fit into a signed 32-bit integer.

Define `f[i][j]` as:

- problem sets: select from first `i` (different kinds) coins all ways of coins combination whose total is equal to `j`.
- property: count.

Deduction: On ith coin

- continue to choose `i`th coin. `f[i][j] = 1 * f[i][j-coins[i]]`.
- choose from first `i-1` coins. `f[i][j] = 1 * f[i-1][j]`.

So, we get `f[i][j] = f[i][j-coins[i]] + f[i-1][j]`.

Base: when amount == 0, `f[i][0] = 1`. C(n, 0).

- 2-d implementation

```c++
vector<vector<int>> f(coins.size(), vector<int>(amount + 1, 0));

    // base: don't choose is 1 choice when amount == 0
    for (int i = 0; i < coins.size(); i++) {
        f[i][0] = 1;
    }

    // preprocess 0th row for 0-index coins
    for (int j = 1; j <= amount; j++) {
        if (j % coins[0] == 0) {
            f[0][j] = 1;
        }
    }

    for (int i = 1; i < coins.size(); i++) {
        for (int j = 0; j <= amount; j++) {
            f[i][j] = f[i - 1][j];
            if (coins[i] <= j) {
                f[i][j] += f[i][j - coins[i]];
            }
        }
    }

    return f[coins.size() - 1][amount];
```

- 1-d with state compression: rolling array (refer to complete knapsack)

```c++
int changeIII(int amount, vector<int>& coins) {
    vector<int> f(amount + 1, 0);

    // base: don't choose is 1 choice when amount == 0
    f[0] = 1;

    for (int i = 0; i < coins.size(); i++) {
        for (int j = coins[i]; j <= amount; j++) {
            f[j] += f[j - coins[i]];
        }
    }

    return f[amount];
}
```

### Decode Ways

> A message containing letters from `A-Z` can be encoded into numbers using the following mapping:
>
> 'A' -> "1", 'B' -> "2", ..., 'Z' -> "26"
>
> To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:
>
> - "AAJF" with the grouping (1 1 10 6)
> - "KJF" with the grouping (11 10 6)
>
> Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".
>
> Given a string s containing only digits, return the number of ways to decode it.
>
> The test cases are generated so that the answer fits in a 32-bit integer.

Define `f[i]` as:

- problem set: all ways of decode first i digits in the given string.
- property: count.

Deduction:

- on ith digit, it can be decoded in one digit on its own, or combined with `i-1`th digit and decoded together if it is valid. `f[i] = 1 * f[i-1]` or `f[i] = 1 * f[i-2]` if `ch[i-1]ch[i]` is a valid text to be decoded.

So, `f[i] = f[i-1] + f[i-2]` if `ch[i-1]ch[i]` is a valid text to be decoded.

```c++
unordered_map<string, char> key;
    for (int i = 1; i <= 26; i++) {
        key[to_string(i)] = 'A' + i - 1;
    }

    vector<int> f(s.size(), 0);
    f[0] = s[0] == '0' ? 0 : 1;    // decode on its own

    for (int i = 1; i < s.size(); i++) {
        if (s[i] != '0') {
            // when s[i] != '0', it can decode on its own
            f[i] += f[i - 1];
        }
        string comb = s.substr(i - 1, 2);
        if (key.find(comb) != key.end()) {
            if (i - 2 >= 0) {
                f[i] += f[i - 2];
            } else {
                f[i] += 1;
            }
        }
        
        if (s[i] == '0' && key.find(comb) == key.end()) {   // bad 0
            return 0;
        }
    }

    return f[s.size() - 1];
```

The code above can be optimized with three variables to calculate result iteratively, given that `f[i]` only relies on `f[i-1]` and `f[i-2]` and we do not need to save intermediate calculation.

### Maximum Subarray

> Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
>
> A subarray is a contiguous part of an array.

Define `f[i]` as:

- problem sets: all different continuous subsequences ending with `nums[i]`.
- property: maximum sum of the subsequence.

Deduction:

- since `nums[i] + f[i-1]` or  `nums[i]` may be negative, so `f[i] = max(nums[i], nums[i] + f[i-1])`.

```c++
int maxSubArray(vector<int>& nums) {
    vector<int> f(nums.size(), -1e5);
    f[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        f[i] = max(nums[i], nums[i] + f[i - 1]);
    }

    int res = -1e5;
    for (int i = 0; i < nums.size(); i++) {
        res = max(res, f[i]);
    }
 
    return res;
}
```

- state compression

Given that `f[i] only relies on f[i-1]` and we do not care about the intermediate results. We are able to use two variables to solve the problem iteratively. Since the subsequence with max sum is not necessarily ending with the last element. We should store the maximum value among intermediate results.

```c++
int maxSubArrayII(vector<int>& nums) {
    int pre = 0;
    int cur = 0;
    int maxSum = -1e5;
    for (int i = 0; i < nums.size(); i++) {
        cur = max(nums[i], pre + nums[i]);   // update f[i]
        maxSum = max(maxSum, cur);
        pre = cur;   // record f[i-1]
    }

    return maxSum;
}
```

### Best Time to Buy and Sell Stock

> You are given an array prices where prices[i] is the price of a given stock on the ith day.
>
> You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
>
> Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Define `f[i]` as:

- problem sets: all transactions happen in the first i days and sell stock on ith day.
- property: maximum profit.

Deduction:

- The maximum profit when selling on ith day is the maximum profit when selling on `i-1`th day - `prices[i-1]` + `prices[i]`, or buying stock on `i-1`th day and selling on `i`th day, i.e. `f[i] = max(prices[i] - prices[i-1], f[i-1] - prices[i-1] + prices[i])`.

```c++
int maxProfitI(vector<int>& prices) {
    vector<int> f(prices.size(), 0);
    f[0] = 0;
    for (int i = 1; i < prices.size(); i++) {
        f[i] = max(prices[i] - prices[i-1], f[i-1] - prices[i-1] + prices[i]);
    }

    int maxVal = -1e5;
    for (int i = 0; i < prices.size(); i++) {
        maxVal = max(maxVal, f[i]);
    }

    return maxVal;
}
```

- state compression

With the same idea as the problem above, we can use three variables to solve the problem iteratively.

```c++
int maxProfitII(vector<int>& prices) {
    int pre = 0;
    int cur = 0;
    int maxVal = pre;   // assuming f[0] is the maximum
    for (int i = 1; i < prices.size(); i++) {
        cur = max(prices[i] - prices[i - 1], pre - prices[i - 1] + prices[i]);
        maxVal = max(maxVal, cur);
        pre = cur;
    }

    return maxVal;
}
```

### Maximum Sum Circular Subarray

> Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.
>
> A circular array means the end of the array connects to the beginning of the array. Formally, the next element of `nums[i]` is `nums[(i + 1) % n]` and the previous element of `nums[i]` is `nums[(i - 1 + n) % n]`.
>
> A subarray may only include each element of the fixed buffer nums at most once. Formally, for a subarray `nums[i], nums[i + 1], ..., nums[j]`, there does not exist `i <= k1, k2 <= j` with `k1 % n == k2 % n`.

The problem is similar to **Maximum Sum Subarray**. The only difference is the array becomes circular. We can decompose the problem into `n` non-circular arrays and solve them one by one.

Define `f[i]` as:

- problem set: all subarray ending with `nums[i]`.
- property: maximum sum.

Deduction:

- maximums sum of subarray ending with `nums[i]` may be 1. maximum subarray ending with `nums[i-1]` concatenated by `nums[i]` (including subarray) or 2. `nums[i]` itself (`f[i-1] < 0`) (exclude subarray).

So, we got `f[i] = max(f[i-1] + nums[i], nums[i])`.

Repeat the algorithm `n` times for each non-circular array.

```c++
int maxSubarraySumCircular(vector<int>& nums) {
    int maxVal = -1e5;
    int shift = 0;
    while (shift < nums.size()) {
        shiftVector(nums, 1);
        int pre = 0;
        int cur = 0;
        for (int i = 0; i < nums.size(); i++) {
            cur = max(pre + nums[i], nums[i]);
            maxVal = max(maxVal, cur);
            pre = cur;
        }
        shift++;
    }

    return maxVal;
}
```

The solution above may Time Limit Exceed (TLE). Let's consider the second solution where we will present a normal way to solve circular problem, i.e. convert to linear problem. Although the solution above is also trying to do such conversion, we will discuss another better way to convert circular into linear problem. Let's see the problem from the perspective of solution.

Say, we have `nums` as follows,

```text
ex> nums = 1  -2  3  -4  5 [ 1  -2  3  -4  5 ]
           <solution1>   ^
                        last
```

There are two possible solutions for a given problem:

- solution does not go cross the last point. (which can be solved in linear method)
- solution go cross the last point.

```text
ex> nums = 1  -2  3  -4  5 [ 1  -2  3  -4  5 ]
     idx = 0   1  2   3  4   0   1  2   3  4
               ^     < solution2 >      ^
               i     <left><right>      i
               |<-ff[i]->|   |<- f[i] ->|
```

We just need a wise way to solve the second solution. And the answer is `max(solution1, solution2)`

Now let's discuss how to solve `solution2`.

Define `f[i]` as maximum subarray in range `[0, i]` and starting from 0. `f[i]` has two possibles: 1. sum starts from 0 to `i`, or 2. `f[i-1]` (maximum subarray we got from last calculation).

So, we got `f[i] = max(sum[0..i], f[i-1])`.

In the similar idea, define `ff[i]` as the max sum of subarray in range `[i, last]` and ending with last. `ff[i]` may be: 1. sum starts from i to last, or 2. `ff[i+1]`.

So, we got `ff[i] = max(sum[i..last], ff[i+1])`.

Therefore, we got `f[i]` (max sum ending with `i`]) and `ff[i]` (max sum beginning with `i`). Concatenate them and we get maxVal with `i` as the middle point. We just need to enumerate all possible middle points and get the maximum value, i.e. `max[i] = f[i] + ff[(i - 1 + size) % size]`.

For all solutions across the middle point, we can combine them with `f[i]` and `ff[i]`. Say, we want to find the max value for the following array.

```text
ex> nums = 1  -2  [ 3  -4   5   1  -2 ] 3  -4   5 
     idx = 0   1    2   3   4   0   1   2   3   4
                    < ff[2] >   <f[1]>

ff[2] = 5, f[1] = 1, so the max sum = 5 + 1 = 6.
```

So, solution 2 can be constructed with `ff[i] + f[(i - 1 + size) % size]`, where `i` is ranging from 1 to last. The final answer is the max value of values in solution 1 and solution 2.

```c++
int maxSubarraySumCircularII(vector<int>& nums) {
    int size = nums.size();

    // solution 1
    int pre = 0;
    int cur = 0;
    int maxSum = -1e5;
    for (int i = 0; i < nums.size(); i++) {
        cur = max(nums[i], pre + nums[i]);
        maxSum = max(maxSum, cur);
        pre = cur;
    }

    // solution 2
    vector<int> f(size, -1e5);   // max sum subarray in [0..i]
    f[0] = nums[0];
    int sum = nums[0];
    for (int i = 1; i < size; i++) {
        sum += nums[i];
        f[i] = max(sum, f[i - 1]);
        maxSum = max(maxSum, f[i]);
    }

    vector<int> ff(size, -1e5);   // max sum subarray in [i..last]
    ff[size - 1] = nums[size - 1];
    sum = nums[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        sum += nums[i];
        ff[i] = max(sum, ff[i + 1]);
    }

    // find the max value among solution 2
    for (int mid = 1; mid < size - 1; mid++) {
        maxSum = max(maxSum, ff[mid] + f[(mid - 1 + size) % size]);
    }

    return maxSum;
}
```

### Unique Paths

> There is a robot on an `m x n` grid. The robot is initially located at the top-left corner (i.e., `grid[0][0]`). The robot tries to move to the bottom-right corner (i.e., `grid[m - 1][n - 1]`). The robot can only move either down or right at any point in time.
>
> Given the two integers `m` and `n`, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
>
> The test cases are generated so that the answer will be less than or equal to `2 * 10^9`.

Note that the robot can only move either down or right at any point in time. Define `f[i][j]` as:

- problem sets: unique ways from begin to `matrix[i][j]`.
- property: total numbers.

Deduction:

- we can go to `(i, j)` from `(i-1, j)` or `(i, j-1)`.

So, we got `f[i][j] = f[i-1][j] + f[i][j-1]`.

```c++
int uniquePaths(int m, int n) {
    vector< vector<int> > f(m, vector<int>(n, 1));
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[i][j] = f[i-1][j] + f[i][j-1];
        }
    }

    return f[m-1][n-1];
}
```

- state compression: with a rolling array.

```c++
int uniquePathsCompressed(int m, int n) {
    vector<int> f(n, 1);
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[j] = f[j] + f[j - 1];
        }
    }

    return f[n - 1];
}
```

