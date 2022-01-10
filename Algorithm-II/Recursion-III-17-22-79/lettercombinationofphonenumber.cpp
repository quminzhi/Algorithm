#include "lettercombinationofphonenumber.h"
#include <unordered_map>
#include "testing/SimpleTest.h"

void letterCombinationsHelper(string& left, string& chosen,
                              vector<string>& result,
                              unordered_map<int, string>& map,
                              int index) {
    if (index >= left.size()) {
        result.push_back(chosen);
        return;
    }

    char cur = left[index];
    for (char ch : map[cur - '0']) {
        // choose
        chosen.push_back(ch);
        letterCombinationsHelper(left, chosen, result, map, index + 1);
        // unchoose
        chosen.pop_back();
    }
}

/**
 * @brief letterCombinations
 * @param digits
 * @return
 * Decision tree.
 */
vector<string> letterCombinations(string digits) {
    vector<string> result;
    if (digits.size() == 0) return result;

    unordered_map<int, string> map = {
        {2, "abc"}, {3, "def"}, {4, "ghi"},
        {5, "jkl"}, {6, "mno"}, {7, "pqrs"},
        {8, "tuv"}, {9, "wxyz"}
    };
    string chosen;
    letterCombinationsHelper(digits, chosen, result, map, 0);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    string digits = "23";
    EXPECT_EQUAL(letterCombinations(digits).size(), 9);
}
