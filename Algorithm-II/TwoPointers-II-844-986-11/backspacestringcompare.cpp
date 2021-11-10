#include "backspacestringcompare.h"
#include <iostream>
#include <stack>
#include "testing/SimpleTest.h"

/**
 * @brief backspaceCompare_sol1
 * @param s: frist string
 * @param t: second string
 * @return true if they are equal after backspacing
 * The basic idea is scanning two strings from begin to end by two pointers.
 *
 * ex> s: a  b  #  c
 *        ^
 *     t: a  d  #  c
 *        ^
 *
 * But the problem here is operator (backspace) is following its operand. Even
 * if two characters are not equal, two strings could be same since backspace
 * operation.
 *
 * To solve that, we are able to start from end to begin. Great!
 * Be care of cases like "ab##", "####"
 *
 * Algorithm:
 * 1. Find the first character.
 * 2. Downto three cases:
 *    a. both are not reaching the end.
 *    b. one of them reaches end. (false)
 *    c. both are reaching the end (true)
 *
 * O: T(N);
 */
bool backspaceCompare_sol1(string s, string t) {
//    if (s.size() != t.size()) return false; // false! because of backspace
    string::reverse_iterator it_s = s.rbegin();
    string::reverse_iterator it_t = t.rbegin();
    stack<char> ss;
    stack<char> st;
    while ((it_s != s.rend()) || (it_t != t.rend())) {
        // TODO: find the first character remain in s from the end
        while ((it_s != s.rend()) && (*it_s == '#')) {
            while ((*it_s == '#') && (it_s != s.rend()))  {
                ss.push(*it_s);
                it_s++;
            }
            while ((!ss.empty()) && (*it_s != '#') && (it_s != s.rend())) {
                ss.pop();
                it_s++;
            }
        }

        // TODO: find the first character remain in s from the end
        while ((it_t != t.rend()) && (*it_t == '#')) {
            while ((*it_t == '#') && (it_t != t.rend())) {
                st.push(*it_t);
                it_t++;
            }
            while ((!st.empty()) && (*it_t != '#') && (it_t != t.rend())) {
                st.pop();
                it_t++;
            }
        }

        /**
         * There three cases here
         *   1. both two iterators are not reaching end, and they are both charaters
         *   except '#'. Then make decision on these two characters. (pending)
         *   2. one of them reach the end, and the other not. (false)
         *   3. both of them reach the end. (true)
         */
        // TODO: case 1
        if ((it_s != s.rend()) && (it_t != t.rend())) {
            if (*it_s != *it_t) {
                return false;
            }
            else {
                it_s++;
                it_t++;
                continue;
            }
        }
        // TODO: case 2 & 3
        if ((it_s == s.rend()) && (it_t == t.rend())) {
            return true;
        }
        else {
            return false;
        }
    }

    return true; // both s and t are blank strings
}

/**
 * Solution 2 is pretty straightforward. Simulation.
 */
bool backspaceCompare_sol2(string s, string t) {
    stack<char> ss;
    stack<char> tt;
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == '#') && (!ss.empty())) {
            ss.pop();
        }
        if (s[i] != '#') {
            ss.push(s[i]);
        }
    }
    for (int i = 0; i < t.size(); i++) {
        if ((t[i] == '#') && (!tt.empty())) {
            tt.pop();
        }
        if (t[i] != '#') {
            tt.push(t[i]);
        }
    }

    while ((!ss.empty()) && (!tt.empty())) {
        if (ss.top() != tt.top()) {
            return false;
        }
        ss.pop();
        tt.pop();
    }

    if ((!ss.empty()) || (!tt.empty())) {
        return false;
    }

    return true;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    string s = "a#b#";
    string t = "c#d#";
    EXPECT(backspaceCompare_sol1(s, t));

    string s1 = "ab#c";
    string t1 = "ad#c";
    EXPECT(backspaceCompare_sol1(s1, t1));

    string s2 = "bxj##tw";
    string t2 = "bxo#j##tw";
    EXPECT(backspaceCompare_sol1(s2, t2));

    string s3 = "bxj##tw";
    string t3 = "bxj###tw";
    EXPECT(!backspaceCompare_sol1(s3, t3));

    string s4 = "e##e#o##oyof##q";
    string t4 = "e##e#fq##o##oyof##q";
    EXPECT(backspaceCompare_sol1(s4, t4));
}

PROVIDED_TEST("Test for sol2:") {
    string s = "a#b#";
    string t = "c#d#";
    EXPECT(backspaceCompare_sol2(s, t));

    string s1 = "ab#c";
    string t1 = "ad#c";
    EXPECT(backspaceCompare_sol2(s1, t1));

    string s2 = "bxj##tw";
    string t2 = "bxo#j##tw";
    EXPECT(backspaceCompare_sol2(s2, t2));

    string s3 = "bxj##tw";
    string t3 = "bxj###tw";
    EXPECT(!backspaceCompare_sol2(s3, t3));

    string s4 = "e##e#o##oyof##q";
    string t4 = "e##e#fq##o##oyof##q";
    EXPECT(backspaceCompare_sol2(s4, t4));
}
