#include "wordbreak.h"
#include <testing/SimpleTest.h>
#include <unordered_set>

bool wordBreakHelper(string& s, vector<string>& wordDict, int start) {
    if (start >= s.size()) {
        return true;
    }

    for (int i = 0; i < wordDict.size(); i++) {
        // rfind(s, the maximum index of start position)
        // std::string test = "0123123";
        // size_t match1 = test.rfind("123");    // returns 4 (rightmost match)
        // size_t match2 = test.rfind("123", 2); // returns 1 (skipped over later match)
        // size_t match3 = test.rfind("123", 0); // returns std::string::npos (i.e. not found)
        // TODO: try all possible matches
        string str = s.substr(start);
        if (str.rfind(wordDict[i], 0) != string::npos) {
            if (wordBreakHelper(s, wordDict, start + wordDict[i].size())) {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief wordBreak_sol1
 * @param s
 * @param wordDict
 * @return
 * Think of it recursively.
 *
 * ex> s = "leetcode", wordDict = ["leet","code"]
 * s will be seen as two parts s = "segmented" + "unsegmented"
 *
 * Define f as f(index): true if s[index..end] can be segmented with 'wordDict'.
 *
 * Derivation: f(index): possible break word in 'wordDict' + f(index + word.length).
 *                       false if no possible break word found.
 *
 * T: O(N^(M/avg(length of word))) if it is solved with recursion
 */
bool wordBreak_sol1(string s, vector<string>& wordDict) {
    if (s.length() == 0) return true;
    if (wordDict.size() == 0) return false;

    bool result = wordBreakHelper(s, wordDict, 0);

    return result;
}

/**
 * @brief wordBreak_sol2
 * @param s
 * @param wordDict
 * @return
 * How to solve it in dynamic programming way? Similar to recursion.
 *
 * Define f as f(index): true if s[start..index] can be segmented with 'wordDict'.
 *
 * ex> s = "leetcode", wordDict = ["leet","code"]
 *
 * Derivation: f(index) = f(j) && (s.sub(j, index-j)), where j is partitioning point for s[start..index]
 *
 * Base case: f(0) = true
 *
 */
bool wordBreak_sol2(string s, vector<string>& wordDict) {
    unordered_set<string> set(wordDict.begin(), wordDict.end());
    vector<bool> breakable(s.length()+1, false);
    breakable[0] = true;

    for (int end = 1; end <= s.length(); end++) {
        for (int partition = 0; partition < end; partition++) {
            if ((breakable[partition]) &&
                (set.find(s.substr(partition, end-partition)) != set.end())) {
                breakable[end] = true;
                break;
            }
        }
    }

    return breakable[s.length()];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    string s1 = "leetcode";
    vector<string> dict1 = {"leet", "code"};
    EXPECT(wordBreak_sol1(s1, dict1));

    string s2 = "catsandog";
    vector<string> dict2 = {"leet", "cats", "dog", "sand", "and", "cat"};
    EXPECT(!wordBreak_sol1(s2, dict2));

    string s = "babababb";
    EXPECT_EQUAL(s.rfind("ba"), 4);
    EXPECT_EQUAL(s.rfind("ba", 2), 2);
    EXPECT_EQUAL(s.rfind("ba", 0), 0);

    EXPECT_EQUAL(s.rfind("babc"), string::npos);
    EXPECT_EQUAL(s.rfind("ba", 1), 0);
}

PROVIDED_TEST("test for sol2:") {
    string s1 = "leetcode";
    vector<string> dict1 = {"leet", "code"};
    EXPECT(wordBreak_sol2(s1, dict1));

    string s2 = "catsandog";
    vector<string> dict2 = {"leet", "cats", "dog", "sand", "and", "cat"};
    EXPECT(!wordBreak_sol2(s2, dict2));
}
