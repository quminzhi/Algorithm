#include "linear.hpp"

#include <iostream>

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