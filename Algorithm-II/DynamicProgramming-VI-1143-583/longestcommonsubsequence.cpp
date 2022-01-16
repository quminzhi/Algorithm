#include "longestcommonsubsequence.h"
#include <testing/SimpleTest.h>

/**
 * @brief longestCommonSubsequence
 * @param text1
 * @param text2
 * @return
 * When comes to dynamic programming, we define f as:
 *
 * f(i, j): the longest common subsequence of text1[0..i] and text2[0..j].
 *
 * Derivation: consider that how new coming characters text1[i] and text2[j] impact
 * f(i, j).
 *
 * case 1: if text1[i] == text2[j], f(i, j) = f(i-1, j-1) + 1.
 * case 2: otherwise, only text1[i] affects f(i, j), then f(i, j) = f(i, j-1)
 *                    only text2[j] affects f(i, j), then f(i, j) = f(i-1, j)
 *         to sum up, f(i, j) = max(f(i, j-1), f(i-1, j)).
 *
 * Base case:
 * f(0, 0) = 0;
 */
int longestCommonSubsequence(string text1, string text2) {
    if (text1.length() == 0) return 0;
    if (text2.length() == 0) return 0;
    int length1 = text1.size();
    int length2 = text2.size();
    vector< vector<int> > lcs(length1, vector<int>(length2, 0));
    // base case:
    bool include = false;
    for (int i = 0; i < length1; i++) {
        if (!include) {
            if (text1[i] == text2[0]) {
                include = true;
                lcs[i][0] = 1;
            }
        }
        else {
            lcs[i][0] = 1;
        }
    }
    include = false;
    for (int j = 0; j < length2; j++) {
        if (!include) {
            if (text1[0] == text2[j]) {
                include = true;
                lcs[0][j] = 1;
            }
        }
        else {
            lcs[0][j] = 1;
        }
    }

    for (int i = 1; i < length1; i++) {
        for (int j = 1; j < length2; j++) {
            if (text1[i] == text2[j]) {
                lcs[i][j] = lcs[i-1][j-1] + 1;
            }
            else {
                lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
            }
        }
    }

    return lcs[length1-1][length2-1];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    string s1 = "abcde";
    string s2 = "ace";
    EXPECT_EQUAL(longestCommonSubsequence(s1, s2), 3);
}

PROVIDED_TEST("test for sol1:") {
    string s1 = "bl";
    string s2 = "yby";
    EXPECT_EQUAL(longestCommonSubsequence(s1, s2), 1);
}
