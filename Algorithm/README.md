# Utils

## Prefix Sum

- 1-d prefix

We define prefix sum as: `prefix[i]` is sum of `nums[0...i]`;

Prefix sum is often used to find the sum of a consecutive nums. Say we want to find sum(l, r) and we can solve it by prefix.

the result is `sum[l...r] == prefix[r] - prefix[l-1]`.

```c++
/**
 * return prefix sum of nums.
 */
vector<int> getPrefix(vector<int> nums) {
    vector<int> prefix(nums.size(), 0);
    prefix[0] = nums[0];
    for (int i = 1; i < prefix.size(); i++) {
        prefix[i] = nums[i] + prefix[i-1];
    }

    return prefix;
}
```

- 2-d prefix

`prefix[m][n]` is the sum of all cells `a[i][j]` where `0 <= i <= m` and `0 <= j <= n`, which is an area of sub square in a square.

```bash
|-----------|
| (x1, y1)  |
|    |------|
|    |      |
|----|------| (x2, y2)
```

The result of given area is `area((x1, y1), (x2, y2)) = prefix[x2][y2] - prefix[x1][y2] - prefix[x2][y1] + prefix[x1][y1]`

How to generate 2-d prefix?

```bash
|-----------|
|           |
|           |  a = (x2-1, y2-1)
|       a |-|
|---------|-| (x2, y2)
```

we can get `prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + cell[x2][y2]`

```c++
vector<vector<int>> getPrefix(vector<vector<int>> grid) {
    vector<vector<int>> prefix;
    // initialize boundary
    prefix[0][0] = grid[0][0];
    for (int i = 1; i < grid.size(); i++) {
        prefix[i][0] = prefix[i-1][0] + grid[i][0];
    }
    for (int j = 1; j < grid[0].size(); j++) {
        prefix[0][j] = prefix[0][j-1] + grid[0][j];
    }

    // calculate the rest of prefix iteratively
    for (int i = 1; i < grid.size(); i++) {
        for (int j = 1; j < grid[0].size(); j++) {
            prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + grid[i][j];
        }
    }

    return prefix;
}
```

## Difference

`difference` is a reverse operation of `prefix`. We need construct an array of `b[i])` where `a[i] = b[0] + b[1] + ... + b[i]`.

`difference` and `prefix` are similar to `differentiation` and `integration` in calculus.

- 1-d difference

```bash
b[1] = a[1]
b[2] = a[2] - a[1]
b[3] = a[3] - a[2]
...
b[n] = a[n] - a[n-1]
```

What's the function of difference? We can change the value in `a[l...r]` by `c` in O(1) instead of O(n) (meaning scan array `a`).

```bash
# add c to all the values in a[l...r]
a[l] + c, a[l+1] + c, ..., a[r] + c

# we can construct a as we did in 1-d prefix from b
# just add c to two values in b, which has the same effect as formula above
b[l] + c
b[r+1] - c

# why?
           a[l]      a[r]          # integration
------------|--- -c ----|-|--- +c -----
b[0]       b[l]      b[r] b[r+1]   # differentiation
```

One classic problem is:

> Given an array `nums`, we need do an operation multiple times. Each time we will update value of a range `[l, r]`.
>
> - add `k` to `nums[l...r]`
> - sub `k` from `nums[l...r]`
>
> Out put the result array after N times of operations.

```c++
void add(vector<int>& diff, int l, int r, int val) {
    diff[l] += val;
    diff[r+1] -= val; 
}

/**
 * @param adds: includes values used to update nums.
 */
vector<int> update(vector<int> nums, int l, int r, int val) {
    // get difference of nums
    vector<int> diff(nums.size(), 0);
    diff[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        diff[i] = nums[i] - nums[i-1];
    }

    add(diff, l, r, val);
    // imagine we have multiple operations here
    // add(diff, l1, r1, val1);
    // add(diff, l2, r2, val2);
    // ...

    // reconstruct nums (prefix)
    for (int i = 1; i < diff.size(); i++) {
        nums[i] = diff[i] + nums[i-1];
    }

    return nums;
}
```

- 2-d difference

The idea is the same. 2-d difference is a reverse operation of 2-d prefix.

```bash
# now each element is the difference not prefix in 2-d prefix.
|------------|
|   b1       | b1 = (x1, y1)
|    |--|    |
|    |--| b2 |
|------------| b2 = (x2, y2)
```

If we want to update the elements in the square of `a[i][j]`, where `x1 <= i <= x2` and `y1 <= j <= y2`.

- Notice that if we add `c` to `b1`, then `a[i][j]`, where `x1 <= i` and `y1 <= j`, will be added `c`.
- But we just want to update the sub square.
- To update, we need eliminate unwanted addition on cells out of the sub square.

```c++
b[x1][y1] += c;
b[x2][y2] += c;   // add square being subbed twice
b[x1][y2+1] -= c; // sub square
b[x2+1][y2] -= c; // sub square
```

Tip: distinguish `diff` from `prefix` (or `integration`).

