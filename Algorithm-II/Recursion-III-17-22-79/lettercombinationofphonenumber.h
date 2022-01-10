#ifndef LETTERCOMBINATIONOFPHONENUMBER_H
#define LETTERCOMBINATIONOFPHONENUMBER_H

#include <vector>
#include <string>
using namespace std;

/**
 * Given a string containing digits from 2-9 inclusive, return all possible letter combinations
 * that the number could represent. Return the answer in any order.
 *
 * A mapping of digit to letters (just like on the telephone buttons) is given below. Note that
 * 1 does not map to any letters.
 *
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Constrains:
 * 0 <= digits.length <= 4
 * digits[i] is a digit in the range ['2', '9'].
 */
vector<string> letterCombinations(string digits);

#endif // LETTERCOMBINATIONOFPHONENUMBER_H
