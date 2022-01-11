#ifndef GENERATEPARENTHESES_H
#define GENERATEPARENTHESES_H

#include <vector>
#include <string>
using namespace std;

/**
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed
 * parentheses.
 *
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 *
 * Constrains:
 * 1 <= n <= 8
 */
vector<string> generateParenthesis(int n);

#endif // GENERATEPARENTHESES_H
