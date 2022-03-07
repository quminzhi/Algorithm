#include "editdistance.h"
#include <testing/SimpleTest.h>
#include <iostream>

/**
 * @brief getLongestCommonSubsequence
 * @param src
 * @param dst
 * @param common: track common subsequence.
 */
void getLongestCommonSubsequence(string& src, string& dst, string& common) {
    if (src.length() == 0) return;
    if (dst.length() == 0) return;
    int length1 = src.size();
    int length2 = dst.size();
    vector< vector<int> > lcs(length1, vector<int>(length2, 0));
    // base case:
    if (src[0] == dst[0]) {
        // 1. the first characters are equal.
        for (int i = 0; i < length1; i++) {
            lcs[i][0] = 1;
        }
        for (int j = 0; j < length2; j++) {
            lcs[0][j] = 1;
        }
    }
    else {
        // 2. not equal.
        bool include = false;
        // if any character in src is equal to dst[0], only the first equal works
        for (int i = 1; i < length1; i++) {
            if ((!include) && (src[i] == dst[0])) {
                include = true;
                lcs[i][0] = 1;
            }
            else {
                lcs[i][0] = lcs[i-1][0];
            }
        }
        include = false;
        // if any character in dst is equal to src[0]
        for (int j = 1; j < length2; j++) {
            if ((!include) && (src[0] == dst[j])) {
                include = true;
                lcs[0][j] = 1;
            }
            else {
                lcs[0][j] = lcs[0][j-1];
            }
        }
    }

    // TODO: derivation
    for (int i = 1; i < length1; i++) {
        for (int j = 1; j < length2; j++) {
            if (src[i] == dst[j]) {
                lcs[i][j] = lcs[i-1][j-1] + 1;
            }
            else {
                lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
            }
        }
    }

    // TODO: backtrack - mirror derivation
    int i = src.size() - 1;
    int j = dst.size() - 1;
    while ((i > 0) && (j > 0)) {
        if (src[i] == dst[j]) {
            common.push_back(src[i]);
            i--; j--;  // from lcs[i-1][j-1]
        }
        else {
            if (lcs[i-1][j] >= lcs[i][j-1]) {
                i--;   // from lcs[i-1][j]
            }
            else {
                j--;   // from lcs[i][j-1]
            }
        }
    }

    if (common.size() < lcs[src.size()-1][dst.size()-1]) {
        // first character
        if (src[0] == dst[0]) {
            common.push_back(src[0]);
        }
        else {
            if (i == 0) {
                // i == 0
                common.push_back(src[i]);
            }
            else {
                // j == 0
                common.push_back(dst[j]);
            }
        }
    }

    reverse(common.begin(), common.end());
}

/**
 * @brief minDistance_sol1
 * @param word1
 * @param word2
 * @return
 * We have to solve it with the help of Longest Common Subsequence (LCS).
 *
 * 1. find LCS
 * 2. transform: i points to the element in word1, j points the element in word2.
 *    - case 1: both word1[i] and word2[j] are in common subseq. Next.
 *    - case 2: word1[i] is not in common, and word2[j] is in common. Delete until word1[i]
 *    is in common.
 *    - case 3: both word1[i] and word2[i] are not in common subseq. Replace word1[i] with
 *    word2[j]
 *    - case 4: word1[i] is in common, and word2[j] is not in common. Insert word1[i] with
 *    word2[j] until word2[j] in common.
 *
 * ex> word1(src) = "extention"  word2(dst) = "execution"  common = "exetion"
 *
 *    src: e x t e n t i o n
 *         ^   ^   ^ ^
 *         i  del  c ins(u)       distance = 3
 *    dst: e x e c u t i o n
 *         ^
 *         j
 * common: e x e t i o n
 *         ^
 *         k
 *
 * if src[i] == common[k], then src[i] is in common string.
 * if dst[j] == common[k], then dst[j] is in common string.
 *
 * T: O(N^2)
 */
int minDistance_sol1(string word1, string word2) {
    if (word1.length() == 0) return word2.length(); // insert
    if (word2.length() == 0) return word1.length(); // delete

    string src = word1;
    string dst = word2;
    string common;
    getLongestCommonSubsequence(src, dst, common);

    int opt_cnt = 0;
    int i = 0;
    int j = 0; // dst is unchanged
    int k = 0;
    while (j < dst.length()) {
        if ((src[i] == common[k]) && (dst[j] == common[k])) {
            // case 1:
            i++; j++; k++;
        }
        else if (src[i] == common[k]) {
            // case 3: insert s[i-1] with dst[j] until dst[j] is in common seq.
            // insert opt ...
            j++;
            opt_cnt++;
        }
        else if (dst[j] == common[k]) {
            // case 2: delete src[i] until src[i] is in common seq.
            // delete opt ...
            i++;
            opt_cnt++;
        }
        else {
            // case 4: replace src[i] with dst[j]
            src[i] = dst[j];
            i++; j++;
            opt_cnt++;
        }
    }

    // remove src's left
    while (i < src.size()) {
        i++;
        opt_cnt++;
    }

    return opt_cnt;
}

/**
 * @brief minDistance_sol2
 * @param word1
 * @param word2
 * @return
 * Solution 2 is to build formula directly on minimum distance. Define f as:
 *
 * f(i, j) = the edit distance between word1[0..i] and word2[0..j]
 *
 * f(i, j) = when word1[i] == word2[j], f(i, j) = min(1 + f(i, j-1), 1 + f(i-1, j), f(i-1, j-1)).
 *         = when word1[i] != word2[j], f(i, j) = 1 + min(f(i, j-1), f(i-1, j), f(i-1, j-1)).
 *
 */
int minDistance_sol2(string word1, string word2) {
    if (word1.length() == 0) return word2.length();
    if (word2.length() == 0) return word1.length();

    vector< vector<int> > min_dis(word1.size(), vector<int>(word2.size(), INT_MAX));
    // Base case:
    if (word1[0] == word2[0]) {
        min_dis[0][0] = 0;
    }
    else {
        min_dis[0][0] = 1;
    }
    bool used = false; // only works for one set of equal characters
    for (int i = 1; i < word1.size(); i++) {
        if ((!used) && (word1[i] == word2[0])) {
            used = true;
            min_dis[i][0] = min_dis[i-1][0];
        }
        else {
           min_dis[i][0] = min_dis[i-1][0] + 1;
        }
    }
    used = false;
    for (int j = 1; j < word2.size(); j++) {
        if ((!used) && (word1[0] == word2[j])) {
            used = true;
            min_dis[0][j] = min_dis[0][j-1];
        }
        else {
            min_dis[0][j] = min_dis[0][j-1] + 1;
        }
    }

    // Derivation:
    for (int i = 1; i < word1.size(); i++) {
        for (int j = 1; j < word2.size(); j++) {
            min_dis[i][j] = 1 + min(min_dis[i-1][j], min_dis[i][j-1]);
            if (word1[i] == word2[j]) {
                min_dis[i][j] = min(min_dis[i][j], min_dis[i-1][j-1]);
            }
            else {
                min_dis[i][j] = min(min_dis[i][j], min_dis[i-1][j-1] + 1);
            }
        }
    }

    return min_dis[word1.length()-1][word2.length()-1];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    string s1 = "extention";
    string s2 = "execution";
//    EXPECT_EQUAL(minDistance_sol1(s1, s2), 3);

    string s11 = "sea";
    string s21 = "eat";
//    EXPECT_EQUAL(minDistance_sol1(s11, s21), 2);

    string s12 = "horse";
    string s22 = "ros";
    EXPECT_EQUAL(minDistance_sol1(s12, s22), 3);

    string s13 = "intention"; // delete i n t  n->x add e c u
    string s23 = "execution";
    EXPECT_EQUAL(minDistance_sol1(s13, s23), 7);
}

PROVIDED_TEST("test for sol2:") {
    string s1 = "extention";
    string s2 = "execution";
    EXPECT_EQUAL(minDistance_sol2(s1, s2), 3);

    string s11 = "sea";
    string s21 = "eat";
    EXPECT_EQUAL(minDistance_sol2(s11, s21), 2);

    string s12 = "horse";
    string s22 = "ros";
    EXPECT_EQUAL(minDistance_sol1(s12, s22), 3);
}
