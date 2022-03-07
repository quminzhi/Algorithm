#include "generateparentheses.h"
#include <testing/SimpleTest.h>

void generateParenthesisHelper(vector<int>& left,
                               string chosen,
                               vector<string>& result) {
    if (left[0] == 0) {
        // left parentheses has been run out of.
        for (int i = 0; i < left[1]; i++) {
            chosen.push_back(')');
        }
        result.push_back(chosen);
        for (int i = 0; i < left[1]; i++) {
            chosen.pop_back();
        }
        return;
    }

    // choose left or right?
    // - condition for left: if left is available
    // - condition for right: if # of right parentheses > # of left parentheses
    // choose left
    chosen.push_back('(');
    left[0]--;
    generateParenthesisHelper(left, chosen, result);
    chosen.pop_back();
    left[0]++;

    // choose right
    if (left[1] > left[0]) {
        chosen.push_back(')');
        left[1]--;
        generateParenthesisHelper(left, chosen, result);
        chosen.pop_back();
        left[1]++;
    }
}

/**
 * @brief generateParenthesis
 * @param n
 * @return combinations of all parentheses
 * It can be seen as group problem. We can create a vector to store how much left/right
 * parentheses left and make decisions on each step.
 *
 * T: O(N!)
 */
vector<string> generateParenthesis(int n) {
    vector<string> result;
    if (n == 0) return result;
    vector<int> left = {n, n};
    string chosen;
    generateParenthesisHelper(left, chosen, result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    EXPECT_EQUAL(generateParenthesis(0).size(), 0);
    EXPECT_EQUAL(generateParenthesis(1).size(), 1);
    EXPECT_EQUAL(generateParenthesis(2).size(), 2);
    EXPECT_EQUAL(generateParenthesis(3).size(), 5);
}
