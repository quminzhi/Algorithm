#include "deleteoperationfortwostrings.h"
#include <testing/SimpleTest.h>

/**
 * @brief minDistance
 * @param word1
 * @param word2
 * @return
 * The problem can be converted as longest common subsequence problem.
 */
int minDistance(string word1, string word2) {
    if (word1.length() == 0) return 0;
    if (word2.length() == 0) return 0;
    int length1 = word1.size();
    int length2 = word2.size();
    vector< vector<int> > lcs(length1, vector<int>(length2, 0));
    // base case:
    bool include = false;
    for (int i = 0; i < length1; i++) {
        if (!include) {
            if (word1[i] == word2[0]) {
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
            if (word1[0] == word2[j]) {
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
            if (word1[i] == word2[j]) {
                lcs[i][j] = lcs[i-1][j-1] + 1;
            }
            else {
                lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
            }
        }
    }

    return length1 + length2 - 2 * lcs[length1-1][length2-1];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    string s1 = "sea";
    string s2 = "eat";
    EXPECT_EQUAL(minDistance(s1, s2), 2);
}
