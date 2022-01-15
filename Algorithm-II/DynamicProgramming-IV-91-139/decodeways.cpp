#include "decodeways.h"
#include <vector>
#include <unordered_map>
#include <testing/SimpleTest.h>

int numDecodeHelper(string& s, unordered_map<string, char>& map, int start) {
    if (start >= s.length()) {
        return 1;
    }
    if (start == s.length()-1) {
        string key = string(1, s[start]);
        if ((map[key] <= 'Z') && (map[key] >= 'A')) {
            return 1;
        }
    }

    int num= 0;
    string key = string(1, s[start]);
    if ((map[key] <= 'Z') && (map[key] >= 'A')) {
        num += numDecodeHelper(s, map, start+1);
    }

    key.push_back(s[start+1]);
    if ((map[key] <= 'Z') && (map[key] >= 'A'))  {
        num += numDecodeHelper(s, map, start+2);
    }

    return num;
}

/**
 * @brief numDecodings_sol1
 * @param s
 * @return
 * The first idea is to solve it by recursion.
 *
 * ex> code = '11106'
 * numDecoding(code) = numDecoding(code.substr(1)) + numDecoding(code.substr(2)) if
 * code[0-1] is a valid mapped character.
 *
 * T: O(2^N)
 */
int numDecodings_sol1(string s) {
    if (s.size() == 0) return 0;
    // TODO: construct map
    unordered_map<string, char> map;
    for (int i = 0; i < 26; i++) {
        map[to_string(i+1)] = 'A' + i;
    }

    int result = numDecodeHelper(s, map, 0);

    return result;
}

/**
 * @brief numDecodings_sol2
 * @param s
 * @return
 * To avoid repeated calculation, dynamic programming comes into play. Define f as:
 *
 * f(index) is the number of decodings starting from index.
 *
 * Derivation: f(index) = f(index+1) if s[index] is valid
 *                        + f(index+2) if s[index...index+1] is valid
 *
 * Base case: if index > s.size()-1, f(index) = 1;
 *
 * T: O(N)
 */
int numDecodings_sol2(string s) {
    if (s.size() == 0) return 0;
    int size = s.size();

    // TODO: construct map
    unordered_map<string, char> map;
    for (int i = 0; i < 26; i++) {
        map[to_string(i+1)] = 'A' + i;
    }

    vector<int> f(size + 1, 0);
    f[size] = 1;
    if ((s[size-1] >= '1') && (s[size-1] <= '9')) {
        f[size-1] = 1;
    }

    for (int i = size - 2; i >= 0; i--) {
        string key = string(1, s[i]);
        if ((map[key] <= 'Z') && (map[key] >= 'A')) {
            f[i] += f[i+1];
        }
        key += s[i+1];
        if ((map[key] <= 'Z') && (map[key] >= 'A')) {
            f[i] += f[i+2];
        }
    }

    return f[0];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    string s1 = "12";
    EXPECT_EQUAL(numDecodings_sol1(s1), 2);

    string s2 = "226";
    EXPECT_EQUAL(numDecodings_sol1(s2), 3);

    string s3 = "06";
    EXPECT_EQUAL(numDecodings_sol1(s3), 0);

    string s4 = "10";
    EXPECT_EQUAL(numDecodings_sol1(s4), 1);
}

PROVIDED_TEST("test for sol2:") {
    string s1 = "12";
    EXPECT_EQUAL(numDecodings_sol2(s1), 2);

    string s2 = "226";
    EXPECT_EQUAL(numDecodings_sol2(s2), 3);

    string s3 = "06";
    EXPECT_EQUAL(numDecodings_sol2(s3), 0);

    string s4 = "10";
    EXPECT_EQUAL(numDecodings_sol2(s4), 1);
}
