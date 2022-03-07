#ifndef FINDALLANAGRAMS_H
#define FINDALLANAGRAMS_H

#include <vector>
#include <string>
using namespace std;

/**
 * Given two strings s and p, return an array of all the start indices of p's
 * anagrams in s. You may return the answer in any order.
 *
 * An Anagram is a word or phrase formed by rearranging the letters of a different
 * word or phrase, typically using all the original letters exactly once.
 *
 * Input: s = "cbaebabacd", p = "abc"
 * Output: [0,6]
 * Explanation:
 * The substring with start index = 0 is "cba", which is an anagram of "abc".
 * The substring with start index = 6 is "bac", which is an anagram of "abc".
 *
 * Constrains:
 * 1 <= s.length, p.length <= 3 * 104
 * s and p consist of lowercase English letters.
 */

vector<int> findAnagrams(string s, string p);

#endif // FINDALLANAGRAMS_H
