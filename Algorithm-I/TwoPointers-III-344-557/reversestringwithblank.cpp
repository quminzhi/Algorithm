#include "reversestringwithblank.h"
#include "testing/SimpleTest.h"

void reverseHelper(string& s, int begin, int end);

/*
 * Function: reverseWords_sol1
 * ------------------------------------
 * The function will reverse each word in the given string. Compared to the question before,
 * We have to do two things here:
 *
 * 1. split string into words. (how)
 * 2. reverse each word. (bingo)
 *
 * The core problem is how to split words in a string given the delimiter is blank space.
 * As always, two pointers. One for the begin of a word, and the other for the end of the word.
 *
 * s = "Let's take LeetCode contest"
 *      ^    ^
 *     begin end
 *
 * Basic idea:
 * 1. 'end' searches the end of the word that 'begin' points to.
 * 2. if it is a word, reverse the word.
 * 3. 'begin' starts to search the begin of a new word.
 *
 * T: O(N), S: O(1)
 */
string reverseWords_sol1(string s) {
    int begin = 0;
    int end = 0;
    int size = s.size();
    while (begin < size) { // ???
        end = begin;
        while ((end < size) && (s[end] != ' ')) {
            end++;
        };
        if (begin < end) {
            reverseHelper(s, begin, end-1);
        }
        begin = end + 1;
        while ((begin < size) && (s[begin] == ' ')) {
            begin++;
        }
    }

    return s;
}

void reverseHelper(string& s, int begin, int end) {
    while (begin < end) {
        swap(s[begin++], s[end--]);
    }
}

/*
 * Function: reverseWords_sol2
 * ------------------------------------
 * The idea behind solution 2 is same as solution 1, but the code is clean.
 */
string reverseWords_sol2(string s) {
    int begin = 0;
    for (int end = 0; end < s.size(); end++) {
        if (s[end] == ' ') {    // one word found
            reverse(s.begin() + begin, s.begin() + end);
            // words are separated by a single blank space.
            begin = end + 1;
        }
    }

    reverse(s.begin() + begin, s.end());

    return s;
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for reverseWords_sol1:") {
    string s1("I love you");
    string res1 = reverseWords_sol1(s1);
    EXPECT_EQUAL(res1[0], 'I');
    EXPECT_EQUAL(res1[1], ' ');
    EXPECT_EQUAL(res1[2], 'e');
    EXPECT_EQUAL(res1[3], 'v');
    EXPECT_EQUAL(res1[4], 'o');
    EXPECT_EQUAL(res1[5], 'l');
    EXPECT_EQUAL(res1[6], ' ');
    EXPECT_EQUAL(res1[7], 'u');
    EXPECT_EQUAL(res1[8], 'o');
    EXPECT_EQUAL(res1[9], 'y');

    string s2("");
    string res2 = reverseWords_sol1(s2);
    EXPECT(res2.size() == 0);

    string s3("Let's take LeetCode contest");
    string res3 = reverseWords_sol1(s3);
    EXPECT_EQUAL(res3[0], 's');
    EXPECT_EQUAL(res3[1], '\'');
    EXPECT_EQUAL(res3[2], 't');
    EXPECT_EQUAL(res3[3], 'e');
    EXPECT_EQUAL(res3[4], 'L');
    EXPECT_EQUAL(res3[5], ' ');
    EXPECT_EQUAL(res3[6], 'e');
}

PROVIDED_TEST("Test for reverseWords_sol2:") {
    string s1("I love you");
    string res1 = reverseWords_sol2(s1);
    EXPECT_EQUAL(res1[0], 'I');
    EXPECT_EQUAL(res1[1], ' ');
    EXPECT_EQUAL(res1[2], 'e');
    EXPECT_EQUAL(res1[3], 'v');
    EXPECT_EQUAL(res1[4], 'o');
    EXPECT_EQUAL(res1[5], 'l');
    EXPECT_EQUAL(res1[6], ' ');
    EXPECT_EQUAL(res1[7], 'u');
    EXPECT_EQUAL(res1[8], 'o');
    EXPECT_EQUAL(res1[9], 'y');

    string s2("");
    string res2 = reverseWords_sol2(s2);
    EXPECT(res2.size() == 0);

    string s3("Let's take LeetCode contest");
    string res3 = reverseWords_sol2(s3);
    EXPECT_EQUAL(res3[0], 's');
    EXPECT_EQUAL(res3[1], '\'');
    EXPECT_EQUAL(res3[2], 't');
    EXPECT_EQUAL(res3[3], 'e');
    EXPECT_EQUAL(res3[4], 'L');
    EXPECT_EQUAL(res3[5], ' ');
    EXPECT_EQUAL(res3[6], 'e');
}




