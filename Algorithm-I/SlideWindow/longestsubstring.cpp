#include "longestsubstring.h"
#include <vector>
#include <unordered_map>
#include "testing/SimpleTest.h"

/*
 * Function: lengthOfLongestString_sol1
 * ------------------------------------
 * The function will return the max length of substrings without repeating characters.
 *
 * string: a   b   c   b   a   b   c   b   b
 *         ^   ^                              ^
 *       begin end                           END
 * we define a window [begin, end) to detect the longest substring without repeating
 * characters. Obviously, the length of window is end - begin. The philosophy here is
 * to keep all the characters in the window unique.
 *
 * Algorithm:
 * 1. resolve corner cases, null string and string with single character.
 * 2. initialize window
 * 3. move end until it is out of the range of the string.
 *      - if s[end] has the same character in window, then find it, and move begin to the
 *    next element of repeating character in the window.
 *      - update max length at each iteration.
 *
 * T: O(N^2), S: O(1)
 */
int lengthOfLongestString_sol1(const string s) {
    if ((s.size() == 0) || (s.size() == 1)) return s.size();

    int maxLength = 0;
    int begin = 0;
    int end = 1;
    while (end < s.size()) {
        // TODO: find repeating index
        int repeatingIndex = -1;
        for (int i = begin; i < end; i++) {
            if (s[i] == s[end]) repeatingIndex = i;
        }

        if (repeatingIndex != -1) {
            begin = repeatingIndex + 1;
        }

        end++;
        // TODO: update max length
        if ((end - begin) > maxLength) {
            maxLength = end - begin;
        }
    }

    return maxLength;
}

/*
 * Function: lengthOfLongestString_sol2
 * ------------------------------------
 * Solution 2 improve the algorithm above in searching part. It uses a char vector to record
 * if particular character exists in the window.
 *
 * So the definition of our window becomes:
 * string: a   b   c   b   a   b   c   b   b
 *         ^   ^                              ^
 *       begin end                           END
 * along with notes: [0, 0, .... 0], whose index corresponds to ASCII code of 128 characters.
 *
 * T: O(N), S: O(1) with extra space
 */
int lengthOfLongestString_sol2(const string s) {
    if ((s.size() == 0) || (s.size() == 1)) return s.size();

    vector<int> notes(128, 0);

    int maxLength = 0;
    int begin = 0;
    notes[s[begin]]++;  // !!!
    int end = 1;
    while (end < s.size()) {
        // TODO: find repeating index
        while (notes[s[end]] > 0) {
            notes[s[begin]]--;
            begin++;
        }

        notes[s[end]]++;
        end++;

        // TODO: update max length
        maxLength = max(maxLength, end - begin);
    }

    return maxLength;
}

/*
 * Function: lengthOfLongestString_sol3
 * ------------------------------------
 * Solution 3 has the same algorithm but use hashmap instead of vector to record characters
 * in the window.
 */
int lengthOfLongestString_sol3(const string s) {
    if ((s.size() == 0) || (s.size() == 1)) return s.size();

    unordered_map<char, int> index;

    int maxLength = 0;
    int begin = 0;
    index[s[begin]] = 0; // !!!
    int end = 1;
    while (end < s.size()) {
        // TODO: find repeating index
        if (index.find(s[end]) != index.end()) {
            begin = index[s[end]] + 1;
        }

        index[s[end]] = end;
        end++;

        // TODO: update max length
        maxLength = max(maxLength, end - begin);
    }

    return maxLength;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for lengthOfLongestString_sol1():") {
    EXPECT_EQUAL(lengthOfLongestString_sol1("abcabcaa"), 3);
    EXPECT_EQUAL(lengthOfLongestString_sol1(""), 0);
    EXPECT_EQUAL(lengthOfLongestString_sol1("a"), 1);
    EXPECT_EQUAL(lengthOfLongestString_sol1("aaaaa"), 1);
}

PROVIDED_TEST("Test for lengthOfLongestString_sol2():") {
    EXPECT_EQUAL(lengthOfLongestString_sol2("abcabcaa"), 3);
    EXPECT_EQUAL(lengthOfLongestString_sol2(""), 0);
    EXPECT_EQUAL(lengthOfLongestString_sol2("a"), 1);
    EXPECT_EQUAL(lengthOfLongestString_sol2("aaaaa"), 1);
}

PROVIDED_TEST("Test for lengthOfLongestString_sol3():") {
    EXPECT_EQUAL(lengthOfLongestString_sol3("abcabcaa"), 3);
    EXPECT_EQUAL(lengthOfLongestString_sol3(""), 0);
    EXPECT_EQUAL(lengthOfLongestString_sol3("a"), 1);
    EXPECT_EQUAL(lengthOfLongestString_sol3("aaaaa"), 1);
}
