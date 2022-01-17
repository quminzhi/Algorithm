#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <vector>
#include <string>
using namespace std;

/**
 * Given two strings word1 and word2, return the minimum number of operations required
 * to convert word1 to word2.
 *
 * You have the following three operations permitted on a word:
 *
 * - Insert a character
 * - Delete a character
 * - Replace a character
 *
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation:
 * horse -> rorse (replace 'h' with 'r')
 * rorse -> rose (remove 'r')
 * rose -> ros (remove 'e')
 *
 * Constrains:
 * 0 <= word1.length, word2.length <= 500
 * word1 and word2 consist of lowercase English letters.
 */
int minDistance(string word1, string word2);

#endif // EDITDISTANCE_H
