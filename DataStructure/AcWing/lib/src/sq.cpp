#include "sq.hpp"

vector<int> closestIndex(vector<int>& nums) {
    // init a stack
    int N_MAX = 5000;
    vector<int> s(N_MAX, 0);
    int top = -1;

    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
        while (top >= 0 && s[top] >= nums[i]) {
            top--;
        }
        if (top >= 0) {
            res.push_back(s[top]);
        } else {
            res.push_back(-1);
        }
        s[++top] = nums[i];
    }

    return res;
}

/**
 * @brief monotonic queue
 *
 * @param nums
 * @param k
 * @return vector<int>
 */
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int N_MAX = 1e5 + 10;
    int q[N_MAX], front = 0, tail = -1;   // index not val, [front, tail]
    vector<int> res;

    // slide window [i - k + 1, i]
    for (int i = 0; i < nums.size(); i++) {
        // insert: find the place for nums[i]
        while (front <= tail && nums[q[tail]] <= nums[i]) {
            tail--;
        }
        q[++tail] = i;
        // check if front is out of the sliding window
        if (q[front] < i - k + 1) {
            front++;
        }
        if (i - k + 1 >= 0) {
            // if slide window completes
            res.push_back(nums[q[front]]);
        }
    }

    return res;
}

/**
 * @brief
 *
 *       s = oooo 1111 xoooooooooo
 *                ^  ^ ^
 *                a  b i: points to the first char that match failed in s string.
 *
 * pattern =      1111 xoooo        (len = 9)
 *                   ^
 *                   j: points to the last char that matches in pattern string.
 *                      also the size of matching chars
 *
 * @param s
 * @param pattern
 * @return vector<int>
 */
vector<int> kmp(string s, string pattern) {
    // transform to 1-based string
    string ss = string("0") + s;
    string pp = string("0") + pattern;

    // build next
    vector<int> ne(pp.size(), 0);
    for (int i = 2, j = 0; i <= pattern.size(); i++) {
        while (j && pp[i] != pp[j + 1]) {
            j = ne[j];
        }
        if (pp[i] == pp[j + 1]) {
            j++;
        }
        // update ne[j]
        ne[i] = j;
    }

    vector<int> res;
    // match
    for (int i = 1, j = 0; i <= s.size(); i++) {
        while (j > 0 && ss[i] != pp[j + 1]) {
            j = ne[j];   // move forward
        }
        if (ss[i] == pp[j + 1]) {
            j++;
        }

        if (j == pattern.size()) {
            res.push_back(i - j);
            j = ne[j];   // move forward for next possible match
        }
    }

    return res;
}

/**
 * @brief simplified kmp
 *
 * @param haystack: s
 * @param needle: pattern
 * @return int: the first index when match occurs for the first time
 */
int strStr(string haystack, string needle) {
    string ss = string("0") + haystack;
    string pp = string("0") + needle;
    // initialize ne[]:
    vector<int> ne(pp.size(), 0);   // 1-based
    for (int i = 2, j = 0; i < pp.size() - 1; i++) {
        while (j && pp[i] != pp[j + 1]) {
            j = ne[j];
        }
        if (pp[i] == pp[j + 1]) {
            j++;
        }
        ne[i] = j;
    }
    // match
    for (int i = 1, j = 0; i < ss.size(); i++) {
        while (j && ss[i] != pp[j + 1]) {
            j = ne[j];
        }
        if (ss[i] == pp[j + 1]) {
            j++;
        }
        if (j == needle.size()) {
            return i - j;   // problem is zero-based
            j = ne[j];
        }
    }

    return -1;
}

/**
 * @brief
 *
 * @param s
 * @return string
 */
string shortestPalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    string pp = string("0") + s + "#" + rev;   // add 0 for 1-based
    vector<int> ne(pp.size(), 0);
    for (int i = 2, j = 0; i < pp.size(); i++) {
        while (j && pp[i] != pp[j + 1]) j = ne[j];
        if (pp[i] == pp[j + 1]) {
            j++;
        }
        ne[i] = j;
    }
    
    int lenOfSubPalindrome = ne[pp.size() - 1];
    // shortest palindrome = reverse(rest) + s (subpalindrome + rest)
    string revRest = s.substr(lenOfSubPalindrome);
    reverse(revRest.begin(), revRest.end());
    
    return revRest + s;
}