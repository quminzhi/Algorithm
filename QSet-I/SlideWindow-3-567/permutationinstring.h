#ifndef PERMUTATIONINSTRING_H
#define PERMUTATIONINSTRING_H

#include <string>
using namespace std;

/**
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or
 * false otherwise. In other words, return true if one of s1's permutations is the
 * substring of s2.
 *
 * Input: s1 = "ab", s2 = "eidbaooo"
 * Output: true
 * Explanation: s2 contains one permutation of s1 ("ba").
 *
 * 1 <= s1.length, s2.length <= 10^4
 * s1 and s2 consist of lowercase English letters.
 */

// time exceeded: calculation of permutation
bool checkInclusion_sol1(string s1, string s2);
bool checkInclusion_sol2(string s1, string s2);
bool checkInclusion_sol3(string s1, string s2);

//  accepted
bool checkInclusion_sol4(string s1, string s2);
bool checkInclusion_sol5(string s1, string s2);


#endif // PERMUTATIONINSTRING_H
