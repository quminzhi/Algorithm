#include "lettercasepermutation.h"
#include <cctype>
#include "testing/SimpleTest.h"

void letterCasePermutationHelper(string& s, string& soFar, vector<string>& result) {
    if (s.length() == 0) {
        result.push_back(soFar);
        return;
    }

    char cur = s[0];
    s = s.substr(1);
    if (isdigit(cur)) {
        soFar.push_back(cur);
        letterCasePermutationHelper(s, soFar, result);
        soFar.pop_back();
    }
    else {
        // current character is not digit, two choises: toupper or tolower
        // choose to upper
        soFar.push_back(toupper(cur));
        letterCasePermutationHelper(s, soFar, result);
        soFar.pop_back();
        // choose to lower
        soFar.push_back(tolower(cur));
        letterCasePermutationHelper(s, soFar, result);
        soFar.pop_back();
    }
    s.insert(s.begin(), cur);
    return;
}

/*
 * Function: letterCasePermutation
 * ------------------------------------
 * Scan string from left to right,
 *      if the character is digit, nothing to do
 *      otherwise, choose to upper current character or not.
 *
 * T: O(2^N)
 */
vector<string> letterCasePermutation(string s) {
    vector<string> result;
    string soFar;
    letterCasePermutationHelper(s, soFar, result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for letterCasePermutation():") {
    string s = "a1b2";
    vector<string> result = letterCasePermutation(s);
    EXPECT(result.size() == 4);
    EXPECT_EQUAL(result[0], "A1B2");
    EXPECT_EQUAL(result[1], "A1b2");
    EXPECT_EQUAL(result[2], "a1B2");
    EXPECT_EQUAL(result[3], "a1b2");

    string s1 = "";
    vector<string> res1 = letterCasePermutation(s1);
    EXPECT(res1.size() == 1);

    string s2 = "1";
    vector<string> res2 = letterCasePermutation(s2);
    EXPECT(res2.size() == 1);
    EXPECT_EQUAL(res2[0], "1");
}
