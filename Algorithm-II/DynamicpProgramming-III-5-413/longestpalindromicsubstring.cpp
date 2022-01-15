#include "longestpalindromicsubstring.h"
#include <vector>
#include <testing/SimpleTest.h>

/**
 * @brief longestPalindrome
 * @param s
 * @return
 * Work it out in dynamic programming way. Define f as:
 *
 * f(left, right): true if string[left...right] is palindrome.
 *
 * f(left, right) has three cases:
 * 1. left == right, true (base case)
 * 2. right - left == 1, meaning substrings with two letters
 *    f(left, right) = s[left] == s[right], ex> 'aa' (true) 'bc' (false)
 * 3. right - left > 1, meanning the length of substring is greater than 2.
 *    f(left, right) = f(left+1, right-1) & s[left] == s[right]
 *
 * Derivation direction can be figured out from f(left, right) = f(left+1, right-1).
 *
 * T: O(N^2)
 */
string longestPalindrome(string s) {
    if (s.length() == 0) return "";
    int size = s.length();
    vector< vector<bool> > isPalindrome(size, vector<bool>(size, false));

    int longest = 1;
    string result;
    result.push_back(s[0]);

    // case 1: single character
    for (int i = 0; i < size; i++) {
        isPalindrome[i][i] = true;
    }

    // case 2: substring with size of 2
    for (int left = 0; left < size; left++) {
        if (s[left] == s[left+1]) {
            isPalindrome[left][left+1] = true;
            // update longest
            longest = 2;
            result = s.substr(left, 2);
        }
    }

    // case 3: length is greater than 2
    // outter: from left to right
    // inner: from top to bottom
    for (int right = 2; right < size; right++) {
        for (int left = 0; left <= right - 2; left++) {
            if ((isPalindrome[left+1][right-1]) && (s[left] == s[right])) {
                isPalindrome[left][right] = true;
                // update longest
                if ((right - left + 1) > longest) {
                    longest = right - left + 1;
                    result = s.substr(left, longest);
                }
            }
        }
    }

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    EXPECT_EQUAL(longestPalindrome("babad"), "bab");
    EXPECT_EQUAL(longestPalindrome("cbbd"), "bb");
    EXPECT_EQUAL(longestPalindrome(""), "");
}
