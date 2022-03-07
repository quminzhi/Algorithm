#ifndef DELETEOPERATIONFORTWOSTRINGS_H
#define DELETEOPERATIONFORTWOSTRINGS_H

#include <string>
#include <vector>
using namespace std;

/**
 * Given two strings word1 and word2, return the minimum number of steps required to make
 * word1 and word2 the same.
 *
 * In one step, you can delete exactly one character in either string.
 *
 * Input: word1 = "sea", word2 = "eat"
 * Output: 2
 * Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
 *
 * Constrains:
 * 1 <= word1.length, word2.length <= 500
 * word1 and word2 consist of only lowercase English letters.
 */
int minDistance(string word1, string word2);

#endif // DELETEOPERATIONFORTWOSTRINGS_H
