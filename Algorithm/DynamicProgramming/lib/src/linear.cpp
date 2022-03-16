#include "linear.hpp"

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
            if (s[i] < s[j]) {
                f[i] = max(f[i], f[j]);
            } else {
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }

    return f[s.size() - 1];
}