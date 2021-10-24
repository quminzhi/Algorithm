#include "permutationinstring.h"
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include "testing/SimpleTest.h"

void permutation(string& left, string& result, unordered_set<string>& records) {
    if (left.size() == 0) {
        records.insert(result);
        return;
    }

    for (int i = 0; i < left.size(); i++) {
        // choose left[i]
        result += left[i];
        left = left.substr(0, i) + left.substr(i+1);
        // recursion
        permutation(left, result, records);
        // unchoose left[i]
        left = left.substr(0, i) + *result.rbegin() + left.substr(i);
        result.pop_back();

    }
}

/*
 * Function: checkInclusion_sol1
 * ------------------------------------
 * The function will return true if s2 contains one of permutation of s1, and return false
 * otherwise.
 *
 * Our preliminary method is decomposing the problem into two subproblems.
 * 1. enumerate all permutation of s1. (how to deal with repetition) => set
 * 2. check if s2 contains the given string. (how to do it efficiently, notice that the
 * permutation of a string has equal length)
 *
 * For the second subproblem, we are able to use a slide window with fixed length to check
 * if s2 contains the given string.
 *
 * But in this way the time complexity is O(N^2 * record.size()), which is bad.
 */
bool checkInclusion_sol1(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    // TODO: get permutation strings
    unordered_set<string> records;
    string result;
    permutation(s1, result, records);

    // TODO: check if match
    int begin = 0;
    int end = s1.length();
    bool flag = true;
    int index = 0;
    for (string s : records) {
        while (end < s2.length()) {
            for (int i = begin; i < end; i++) {
                if (s[index] != s2[i]) {
                    flag = false;
                    break;
                }
                index++;
            }
            if (flag) {
                return true;
            }

            // TODO: move forward
            begin++;
            end++;
            flag = true;
            index = 0;
        }

        // TODO: reset begin and end
        begin = 0;
        end = s1.length();
    }

    return false;
}


/*
 * Function: checkInclusion_sol2
 * ------------------------------------
 * We can do some optimization on subproblem 2. In fact, there are a lot of repeated work we
 * have done in the implementation of sol1.
 *
 * Notice s2 is unchanged. So we can breakdown s2 into some substrings with the length of s1.
 * Then we get two sets.
 * 1. set1: all permutations of s1.
 * 2. set2: all substrings of s2 (substring with length of s1 and consecusive indexes).
 * We are able to check if s2 contains permutations of s1 by checking if set1 and set2 have
 * common set (intersection).
 *
 * Pattern for constructing set2:
 * s2:  a  b  c  d  e  f (size = 6), s1.size = 2 (assumed)
 * We are able to get (s2.size - s1.size + 1) substrings.
 */
bool checkInclusion_sol2(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    // TODO: get permutation strings
    unordered_set<string> records_s1;
    string result;
    permutation(s1, result, records_s1);

    // TODO: construct set2
    unordered_set<string> records_s2;
    int begin = 0;
    int size = s1.size();
    while (begin <= (s2.size() - size)) {
        records_s2.insert(s2.substr(begin, size));
        begin++;
    }

    // TODO: check if there is intersection
    for (auto&& str : records_s1) {
        if (records_s2.find(str) != records_s2.end()) {
            return true;
        }
    }

    return false;
}

/*
 * Function: checkInclusion_sol3
 * ------------------------------------
 * In solution 3, we will improve the subproblem 1 by using queue to produce permutaions
 * (BFS in nature) rather than recursion.
 *
 * BTW: there are two kind of recursion roughly that can be simulated by queue or stack.
 *  - DFS recursion can be simulated by stack.
 *  - BFS recursion can be simulated by queue.
 */
bool checkInclusion_sol3(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    // TODO: construct set2
    unordered_set<string> records_s2;
    int begin = 0;
    int size = s1.size();
    while (begin <= (s2.size() - size)) {
        records_s2.insert(s2.substr(begin, size));
        begin++;
    }

    // TODO: search permutations and find if s2 contains it
    class PermutationState {
    public:
        string left;
        string result;
        PermutationState(string left, string result)
            : left(left), result(result) {}
    };

    queue<PermutationState*> buffer;
    buffer.push(new PermutationState(s1, ""));
    while (!buffer.empty()) {
        PermutationState* cur = buffer.front();
        if (cur->left.size() == 0) {
            // Base case: find one
            if (records_s2.find(cur->result) != records_s2.end()) {
                return true;
            }
        }
        else {
            for (int i = 0; i < cur->left.size(); i++) {
                // choose left[i]
                cur->result += cur->left[i];
                cur->left = cur->left.substr(0, i) + cur->left.substr(i+1);
                // recursion
                buffer.push(new PermutationState(cur->left, cur->result));
                // unchoose left[i]
                cur->left = cur->left.substr(0, i) + *cur->result.rbegin() + cur->left.substr(i);
                cur->result.pop_back();
            }
        }
        buffer.pop();
        delete cur;
    }

    return false;
}

/*
 * Function: checkInclusion_sol4
 * ------------------------------------
 * All three solutions above have done one thing, which is enumerating permutations. But
 * the question is: is it necessary? Let's recap our original problem.
 *
 * Check if s2 contains any permutation of s1.
 *
 * From another perspective, if a substring of s2 has the same characters that s1 does without
 * considering order, then s2 must contains at least one of permutation of s1.
 *
 * Now our problem is check if any substring of s2 has the same characters as s1. We will
 * do it in a method sort of like encryptic algorithm. We will predefined a private key, and
 * calculate each substring. If any substring has the same encrypted code, then they have the
 * same characters without taking order into consideration.
 *
 * ex> private key:  a: 2,  b: 77, c: 193, o: 1001
 *     s1: ab  =>  1 * 2 + 1 * b = 79
 *     s2: aabacooc:  aa(4), ab(79), ba(79), ac(195), co(1194), oo(2002), oc(1194)
 *
 * By comparing encrypted code, we are able to check if two strings have same characters without
 * considering the order of characters.
 *
 * Tricks:
 *     How to calcualte encrypted code of substrings efficiently?
 *     s2: a  a  b  a  c  o  o  c
 *         ^     ^
 *        begin end (code = 4)
 *
 * As window slides from left to right, we only need subtract the value of the frist character and
 * add the value of the last character.
 */
bool checkInclusion_sol4(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    unordered_map<char, int> privateKey = {
        {'a', 2}, {'b', 77}, {'c', 56}, {'d', 101}, {'e', 89}, {'f', 54},
        {'g', 171}, {'h', 133}, {'i', 179}, {'j', 203}, {'k', 301}, {'l', 111},
        {'m', 511}, {'n', 607}, {'o', 1021}, {'p', 1891}, {'q', 1099}, {'r', 1999},
        {'s', 2117}, {'t', 2738}, {'u', 2919}, {'v', 3113}, {'w', 3573}, {'x', 4011},
        {'y', 4193}, {'z', 5111}
    };

    int code_s1 = 0;
    for (char ch : s1) {
        code_s1 += privateKey[ch];
    }

    int begin = 0;
    int end = s1.size();
    int code_s2 = 0;
    for (int i = begin; i < end; i++) {
        code_s2 += privateKey[s2[i]];
    }
    while (end <= s2.size()) {
        if (code_s2 == code_s1) {
            return true;
        }

        code_s2 -= privateKey[s2[begin]];
        begin++;
        code_s2 += privateKey[s2[end]];
        end++;
    }

    return false;
}

/*
 * Function: checkInclusion_sol5
 * ------------------------------------
 * Solution 5 will use hashmap (or vector) to record the frequency of characters in the window. The
 * idea is similar to that above.
 *
 * Also, we will use 'numOfMatch' to count the number of characters whose frequency matches in both
 * strings. 'targetNum' indicates how many characters should match.
 *
 * Some details:
 * 1. when both substrings will match? if (numOfMatch == SIZE_OF_CHARACTERS), there you go.
 * 2. when to update 'numOfMatch'?
 *    - for 'begin',
 *          if character[begin] matches before, then de-window will make it not matching.
 *          if the number of character[begin] for s1 is one less than that for s2, then de-window
 *          will make them matching.
 *    - for 'end',
 *          if character[end] matches  before, then en-window will make it not matching.
 *          if the number of character[end] for s2 is one more than that for s2, then en-window will
 *          make them matching.
 */
bool checkInclusion_sol5(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    const int SIZE_OF_CHARACTERS = 26;
    vector<int> s1map(SIZE_OF_CHARACTERS);
    vector<int> s2map(SIZE_OF_CHARACTERS);
    for (int i = 0; i < s1.size(); i++) {
        s1map[s1[i] - 'a']++;
        s2map[s2[i] - 'a']++;
    }

    int numOfMatch = 0;
    for (int i = 0; i < SIZE_OF_CHARACTERS; i++) {
        if (s1map[i] == s2map[i]) {
            numOfMatch++;
        }
    }

    // TODO: slide window and update numOfMatch
    int begin = 0;
    int end = s1.size();
    while (end <= s2.size()) {
        if (numOfMatch == SIZE_OF_CHARACTERS) {
            return true;
        }
        // TODO: dequeue (en-window)
        if (s1map[s2[begin] - 'a'] == s2map[s2[begin] - 'a']) {
            // if character is match before
            numOfMatch--;
        }
        else {
            if (s1map[s2[begin] - 'a'] == s2map[s2[begin] - 'a'] - 1) {
                // whether match if begin character subtract 1, that's what will happen.
                numOfMatch++;
            }
        }
        s2map[s2[begin] - 'a']--;
        begin++;
        // TODO: enqueue (de-window)
        if (s1map[s2[end] - 'a'] == s2map[s2[end] - 'a']) {
            // if character is match before
            numOfMatch--;
        }
        else {
            if (s1map[s2[end] - 'a'] == s2map[s2[end] - 'a'] + 1) {
                // whether match if end character add 1.
                numOfMatch++;
            }
        }
        s2map[s2[end] - 'a']++;
        end++;
    }

    return false;
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for checkInclusion_sol1():") {
    string s1 = "ab";
    string s2 = "eidbaooo";
    EXPECT(checkInclusion_sol1(s1, s2));

    string s3 = "ab";
    string s4 = "eidboaoo";
    EXPECT(!checkInclusion_sol1(s3, s4));

    string s5 = "ab";
    string s6 = "a";
    EXPECT(!checkInclusion_sol1(s5, s6));

//    string s7 = "prosperity";
//    string s8 = "properties";
//    EXPECT(checkInclusion_sol1(s7, s8));
}

PROVIDED_TEST("Test for checkInclusion_sol2():") {
    string s1 = "ab";
    string s2 = "eidbaooo";
    EXPECT(checkInclusion_sol2(s1, s2));

    string s3 = "ab";
    string s4 = "eidboaoo";
    EXPECT(!checkInclusion_sol2(s3, s4));

    string s5 = "ab";
    string s6 = "a";
    EXPECT(!checkInclusion_sol2(s5, s6));

//    string s7 = "prosperity";
//    string s8 = "properties";
//    EXPECT(checkInclusion_sol2(s7, s8));
}

PROVIDED_TEST("Test for checkInclusion_sol3():") {
    string s1 = "ab";
    string s2 = "eidbaooo";
    EXPECT(checkInclusion_sol3(s1, s2));

    string s3 = "ab";
    string s4 = "eidboaoo";
    EXPECT(!checkInclusion_sol3(s3, s4));

    string s5 = "ab";
    string s6 = "a";
    EXPECT(!checkInclusion_sol3(s5, s6));

//    string s7 = "prosperity";  // 10!
//    string s8 = "properties";
//    EXPECT(checkInclusion_sol3(s7, s8));
}

PROVIDED_TEST("Test for checkInclusion_sol4():") {
    string s1 = "ab";
    string s2 = "eidbaooo";
    EXPECT(checkInclusion_sol4(s1, s2));

    string s3 = "ab";
    string s4 = "eidboaoo";
    EXPECT(!checkInclusion_sol4(s3, s4));

    string s5 = "ab";
    string s6 = "a";
    EXPECT(!checkInclusion_sol4(s5, s6));

    string s7 = "prosperity";  // 10!
    string s8 = "properties";
    EXPECT(!checkInclusion_sol4(s7, s8));

    string s9 = "prosperity";
    string s10 = "prosperyti";
    EXPECT(checkInclusion_sol4(s9, s10));

    string s11 = "dinitrophenylhydrazine";
    string s12 = "dimethylhydrazine";
    EXPECT(!checkInclusion_sol4(s11, s12));
}

PROVIDED_TEST("Test for checkInclusion_sol5():") {
    string s1 = "ab";
    string s2 = "eidbaooo";
    EXPECT(checkInclusion_sol5(s1, s2));

    string s3 = "ab";
    string s4 = "eidboaoo";
    EXPECT(!checkInclusion_sol5(s3, s4));

    string s5 = "ab";
    string s6 = "a";
    EXPECT(!checkInclusion_sol5(s5, s6));

    string s7 = "prosperity";  // 10!
    string s8 = "properties";
    EXPECT(!checkInclusion_sol5(s7, s8));

    string s9 = "prosperity";
    string s10 = "prosperyti";
    EXPECT(checkInclusion_sol5(s9, s10));

    string s11 = "dinitrophenylhydrazine";
    string s12 = "dimethylhydrazine";
    EXPECT(!checkInclusion_sol5(s11, s12));
}
