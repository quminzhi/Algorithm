#ifndef LETTERCASEPERMUTATION_H
#define LETTERCASEPERMUTATION_H

#include <vector>
#include <string>
using namespace std;

/**
 * Given a string s, we can transform every letter individually to be lowercase or
 * uppercase to create another string.
 *
 * Return a list of all possible strings we could create. You can return the output
 * in any order.
 *
 * Input: s = "a1b2"
 * Output: ["a1b2","a1B2","A1b2","A1B2"]
 *
 * s will be a string with length between 1 and 12.
 * s will consist only of letters or digits.
 */

vector<string> letterCasePermutation(string s);

#endif // LETTERCASEPERMUTATION_H
