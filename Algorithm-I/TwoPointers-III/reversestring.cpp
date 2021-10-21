#include "reversestring.h"
#include "testing/SimpleTest.h"

/*
 * Function: reverseString_sol1
 * ------------------------------------
 * The function will reverse a string represented by a vector of char.
 *
 * The first solution resorts to a helper space to store string reversed.
 *
 * T: O(N), S: O(N)
 */
void reverseString_sol1(vector<char>& s) {
    vector<char> before(s);
    int index = 0;
    for (int i = before.size() - 1; i >= 0; i--) {
        s[index++] = before[i];
    }
}


/*
 * Function: reverseString_sol2
 * ------------------------------------
 * The second method is by two pointers, and swap the values they point to.
 *
 * ex> {a, b, c}
 *      ^     ^
 *      l     r
 */
void reverseString_sol2(vector<char>& s) {
    int left = 0;
    int right = s.size() - 1;
    while (left < right) {
        swap(s[left++], s[right--]);
    }
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for reverseString_sol1:") {
    vector<char> s = {'a', 'b'};
    reverseString_sol1(s);
    EXPECT_EQUAL(s[0], 'b');
    EXPECT_EQUAL(s[1], 'a');

    vector<char> s1 = {};
    reverseString_sol1(s1);
    EXPECT(s1.size() == 0);

    vector<char> s2 = {'a'};
    reverseString_sol1(s2);
    EXPECT_EQUAL(s2[0], 'a');
}

PROVIDED_TEST("Test for reverseString_sol2:") {
    vector<char> s = {'a', 'b'};
    reverseString_sol2(s);
    EXPECT_EQUAL(s[0], 'b');
    EXPECT_EQUAL(s[1], 'a');

    vector<char> s1 = {};
    reverseString_sol2(s1);
    EXPECT(s1.size() == 0);

    vector<char> s2 = {'a'};
    reverseString_sol2(s2);
    EXPECT_EQUAL(s2[0], 'a');
}

