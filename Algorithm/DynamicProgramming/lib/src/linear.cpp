#include "linear.hpp"

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>

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

/**
 * @brief f[i] is the minimum last number of the sequence with the same length
 *
 * @param s
 * @return int
 */
int MaxLengthOfNonDescendingSubsequenceIII(string s) {
    vector<int> f(s.size() + 1,
                  INT_MAX);   // the last number of subsequence with length i
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
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (sl[i - 1] == sr[j - 1]) {   // 1-based
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
            }
        }
    }

    return f[sl.size()][sr.size()];
}

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
    vector<vector<int> > f(sl.size() + 1, vector<int>(sr.size() + 1, 0));

    // 1-indexed:
    for (int i = 0; i <= sl.size(); i++) {
        f[i][0] = i;   // del
    }
    for (int j = 0; j <= sr.size(); j++) {
        f[0][j] = j;   // del
    }

    // deduction
    for (int i = 1; i <= sl.size(); i++) {
        for (int j = 1; j <= sr.size(); j++) {
            f[i][j] = f[i - 1][j] + 1;
            f[i][j] = min(f[i][j], f[i][j - 1] + 1);
            if (sl[i] != sr[j]) {
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
            } else {
                f[i][j] = min(f[i][j], f[i - 1][j - 1]);
            }
        }
    }

    return f[sl.size()][sr.size()];
}

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
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + prefix[j + 1] - prefix[i]);
            }
        }
    }

    return f[0][stones.size() - 1];
}

/**
 * @brief return the number of divisions
 * f[i][j] = sum(f[i-1][j], f[i][j - i])
 * @param n
 * @return int
 */
int IntegerDivision(int n) {
    vector<vector<int> > f(n + 1, vector<int>(n + 1, 0));   // 1-indexed
    for (int i = 0; i <= n; i++) {
        f[i][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (i <= j) {
                f[i][j] += f[i][j - i];
            }
        }
    }

    return f[n][n];
}

int IntegerDivisionII(int n) {
    vector<int> f(n + 1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            f[j] = f[j] + f[j - i];
        }
    }

    return f[n];
}

/**
 * @brief f[i][j] = f[i-1][j-1] + f[i-j][j]
 *
 * @param n
 * @return int
 */
int IntegerDivisionIII(int n) {
    vector<vector<int> > f(n + 1, vector<int>(n + 1, 0));

    // boundary: n has only one plan whose length is 1
    for (int i = 1; i <= n; i++) {
        f[i][1] = 1;
    }

    for (int i = 1; i <= n; i++) {
        // j cannot be greater than i, since if we all choose 1, the max len is n
        for (int j = 2; j <= i; j++) {
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
        }
    }

    int sum = 0;
    for (int j = 1; j <= n; j++) {
        sum += f[n][j];
    }

    return sum;
}

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
    for (int dst = 0; dst < max_state; dst++) {       // state of ith col
        for (int src = 0; src < max_state; src++) {   // state of i-1th col
            if ((src & dst) == 0 && isValidState[src | dst]) {
                // src & dst == 0 means it cannot be 1 on the same bit of two binary
                // numbers src | dst explains the state of i-1 after inserting i'th plan
                // (dst)
                isValidTrans[src][dst] = true;
            }
        }
    }

    // means the first-1 (imagined) column cannot be placed 1*2 block. From the
    // perspective of the 1st col, there is no 1*2 block end on the first column (which is
    // the starting state).
    f[0][0] = 1;   // state of 0-1 is 0x0000
    // deduction
    for (int i = 1; i <= m; i++) {
        // j enumerates possible states of i-1
        for (int j = 0; j < max_state; j++) {
            // k enumerates possible states of i-2
            for (int k = 0; k < max_state; k++) {
                if (isValidTrans[k][j]) {
                    // i-1 col with state j and i-2 col with state k
                    f[i][j] += f[i - 1][k];
                }
            }
        }
    }

    // 0-indexed
    return f[m][0];
}

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
                if (state >> j & 1) {   // a valid state should include j
                    for (int k = 0; k < graph.size(); k++) {
                        if ((state - (1 << j)) >> k & 1) {
                            // find all possible k directely connected to the j
                            f[state][j] = min(f[state][j], f[state - (1 << j)][k] + graph[k][j]);
                        }
                    }
                }
            }
        }
    }

    // f[1111111][last vertex]
    return f[max_state - 1][graph.size() - 1];
}

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
 * Because it is a hierarchy tree, there must be n-1 rel (edges) when there are n workers
 * (nodes)
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
    for (; root < tree.size() && tree[root].parent != -1; root++) {
    }

    dfs(f, tree, exp, root);

    return max(f[root][0], f[root][1]);
}

int dfs_skating(vector<vector<int> >& f, vector<vector<int> >& h, int x, int y) {
    static int dir_x[4] = {-1, +1, 0, 0};
    static int dir_y[4] = {0, 0, -1, +1};

    // if f[x][y] is calculated, return result
    if (f[x][y] != -1) return f[x][y];

    f[x][y] = 1;   // path has length of at least 1 (start point)
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

/**
 * @brief return the idx of the first element less or equal than x
 *
 * we can achieve it with binary search since monotonic of f[].
 *
 * @param f
 * @param x
 * @return int
 */
int biSearch(vector<int>& f, int x) {
    int l = 0;
    int r = f.size() - 1;
    while (l < r) {
        int mid = l + ((r - l + 1) >> 1);
        if (f[mid] >= x) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }

    return l;
}

/**
 * @brief define f[i] as the minimum ending element of subsequence with length of i.
 *
 * @param nums
 * @return int
 */
int lengthOfLISII(vector<int>& nums) {
    vector<int> f(nums.size() + 1, 1e6);
    f[0] = -1e6;

    for (int i = 0; i < nums.size(); i++) {
        // find max length of subsequence nums[i] can be connect with.
        // i.e. find the first numbers less than nums[i] in f[]
        int idx = biSearch(f, nums[i]);
        // update f[idx + 1]
        f[idx + 1] = min(f[idx + 1], nums[i]);
    }

    int maxLen = 0;
    for (int i = nums.size(); i >= 0; i--) {
        if (f[i] != 1e6) {
            maxLen = i;
            break;
        }
    }

    return maxLen;
}

/**
 * @brief
 *
 * @param nums
 * @param k
 * @param p
 * @return int
 */
int countDistinct(vector<int>& nums, int k, int p) {
    unordered_set<string> memo;
    int N = nums.size() + 1;
    vector<int> f(N, 0);
    vector<bool> dv(N, false);
    for (int i = 1; i <= nums.size(); i++) {
        dv[i - 1] = nums[i - 1] % p == 0;
        string subarr = "";
        int cntN = 0;
        int cntP = 0;
        int ptr = i - 1;
        while (ptr >= 0 && cntP <= k) {
            if (dv[ptr]) cntP++;
            if (cntP <= k) {
                subarr = to_string(nums[ptr]) + ',' + subarr;
                if (memo.find(subarr) == memo.end()) {
                    memo.insert(subarr);
                    cntN++;
                }
            }
            ptr--;
        }
        f[i] = f[i - 1] + cntN;
    }

    return f[nums.size()];
}

/**
 * @brief
 *
 * @param nums
 * @return int
 */
int maxProduct(vector<int>& nums) {
    int n = nums.size();
    int mmax = nums[0];
    int mmin = nums[0];
    int res = nums[0];
    for (int i = 1; i < n; i++) {
        int lastmax = mmax;
        int lastmin = mmin;
        if (nums[i] > 0) {
            mmax = max(nums[i], nums[i] * lastmax);
            mmin = min(nums[i], nums[i] * lastmin);
        } else {
            mmax = max(nums[i], nums[i] * lastmin);
            mmin = min(nums[i], nums[i] * lastmax);
        }
        res = max(res, mmax);
    }

    return res;
}