#include "linear.hpp"

#include <iostream>
#include <queue>
#include <string>

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
            if (sl[i] == sr[j]) {
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
    for (int dst = 0; dst < max_state; dst++) { // state of ith col
        for (int src = 0; src < max_state; src++) { // state of i-1th col
            if ((src & dst) == 0 && isValidState[src | dst]) {
                // src & dst == 0 means it cannot be 1 on the same bit of two binary numbers
                // src | dst explains the state of i-1 after inserting i'th plan (dst)
                isValidTrans[src][dst] = true;
            }
        }
    }

    f[0][0] = 1; // state of i-1 is 0x00000000
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

    return f[m][0];
}