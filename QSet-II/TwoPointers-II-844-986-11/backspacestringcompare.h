#ifndef BACKSPACESTRINGCOMPARE_H
#define BACKSPACESTRINGCOMPARE_H

#include <string>
using namespace std;

/**
 * Given two strings s and t, return true if they are equal when both are typed
 * into empty text editors. '#' means a backspace character.
 *
 * Note that after backspacing an empty text, the text will continue empty.
 *
 * Input: s = "ab#c", t = "ad#c"
 * Output: true
 * Explanation: Both s and t become "ac".
 *
 * Constrains:
 * 1 <= s.length, t.length <= 200
 * s and t only contain lowercase letters and '#' characters.
 */

bool backspaceCompare(string s, string t);

#endif // BACKSPACESTRINGCOMPARE_H
