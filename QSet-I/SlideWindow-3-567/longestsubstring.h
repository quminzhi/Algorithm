#ifndef LONGESTSUBSTRING_H
#define LONGESTSUBSTRING_H

#include <string>
using namespace std;

/**
 * Given a string s, find the length of the longest substring without repeating
 * characters.
 *
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 * 0 <= s.length <= 5 * 10^4
 * s consists of English letters, digits, symbols and spaces.
 */

int lengthOfLongestString_sol1(const string s); // for loop
int lengthOfLongestString_sol2(const string s); // vector
int lengthOfLongestString_sol3(const string s); // hashmap

#endif // LONGESTSUBSTRING_H
