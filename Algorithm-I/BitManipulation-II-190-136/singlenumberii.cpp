#include "singlenumberii.h"
#include <unordered_map>
#include "testing/SimpleTest.h"

/*
 * Function: singleNumber_sol1
 * ------------------------------------
 * Same with before, the problem can be solved by hashmap, which records the frequency
 * of each number.
 */
int singleNumberii_sol1(vector<int>& nums) {
    unordered_map<int, int> freq;
    for (int i = 0; i < nums.size(); i++) {
        unordered_map<int, int>::iterator it = freq.find(nums[i]);
        if (it != freq.end()) {
            freq[nums[i]]++;
            if (freq[nums[i]] == 3) {
                freq.erase(it);
            }
        }
        else {
            freq[nums[i]] = 1;
        }
    }

    return freq.begin()->first;
}

/*
 * Function: singleNumberii_sol2
 * ------------------------------------
 * Again, bitwise operations come into play.
 *
 * XOR: could be used to detect those appear odd number of times.
 * AND: &  OR: |
 * That will be tricky with the help of 'seen_once' and 'seen_twice'
 *
 * The idea is to:
 * - change seen_once only if seen_twice is unchanged.
 * - change seen_twice only if seen_once is unchanged.
 *
 * seen_once = ~seen_twice & (seen_once ^ x);
 * seen_twice = ~seen_once & (seen_twice ^ x);
 *
 * Comprehension:
 * seen_once and seen_twice in fact can be seen as two maps, which will save numbers in
 * its binary format. Let's say we have
 *     nums: a, a, b, a
 *     (a): first time to see a, so we squash 'a' into seen_once map by 'seen_once XOR a'
 *     (a): secend time to see a, we will remove 'a' from seen_once and save it in seen_twice.
 *     (b): first time to see b, so we squash 'b' into seen_once map by 'seen_once XOR b'
 *     (a): third time to see a, we will remove it from seen_once and seen_twice.
 *
 * - since a XOR b XOR a = a XOR a XOR b, the order of numbers in 'nums' doesn't matter.
 * ex> nums = {a, b, c, c, b, b, a, a, d, c} it can be seen as {a, a, a, b, b, b, c, c, c, d}
 * - let's say we just have 'seen_once ^ x':
 *   seen_once:  0000
 *     first x:  1001
 *           --------
 *               1001  great
 *    second x:  1001
 *           --------
 *               0000  great
 *     third x:  1001
 *           --------
 *               1001 <-- that's not what i want
 *
 *   seen_twice: 0000
 *      first x: 1001
 *           --------
 *               1001 <-- no, not what i want.
 *   can we do it with the help of seen_once, make myself to be 0 when first time see x.
 *   given that seen_once now is 1001(x), and seen_twice now is 1001(x), how?
 *   !seen_once & 'what i'm now' is the answer.
 *         0110 & 1001 = 0000 (great)
 * Now i will be 0000
 *     second x: 1001
 *           --------
 *               1001
 *      third x: 1001
 *           --------
 *               0000 Now can I help seen_once to fix its bug?
 *
 * Let's go back to the second time we've seen x
 *      seen_once = 0000
 *     seen_twice = 1001
 * third x comes:  (some magic) + seen_once XOR x (which is 1001) == 0000?
 * with the help of seen_twice, given that
 *      !a & a == 0
 *      !0 & a == a
 * so that's the logic expression, that we use to reset seen_once and seen_twice)
 *
 *  seen_once = ~seen_twice & (seen_once ^ x);
 *              |---------| if it is seen in seen_twice, then reset me.
 *                          otherwise, keep my result.
 *
 *  seen_twice = ~seen_once & (seen_twice ^ x);
 *               |--------| if it is seen in seen_once, then reset me.
 *                          otherwise, keep my result.
 *
 * Further thought: this algorithm can solve all multiple of three occurrance problem.
 * ex> every number occurs 3*n times except one number.
 */
int singleNumberii_sol2(vector<int>& nums) {
    int seen_once = 0;
    int seen_twice = 0;
    for (int i = 0; i < nums.size(); i++) {
        seen_once = (~seen_twice) & (seen_once ^ nums[i]);
        seen_twice = (~seen_once) & (seen_twice ^ nums[i]);
    }

    return seen_once;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for singleNumber_sol1():") {
    vector<int> nums1 = {1, 1, 1, 2};
    EXPECT_EQUAL(singleNumberii_sol1(nums1), 2);

    vector<int> nums2 = {1, 1, 1, 2, 2, 2, 3, 4, 3, 3};
    EXPECT_EQUAL(singleNumberii_sol1(nums2), 4);
}

PROVIDED_TEST("Test for singleNumber_sol2():") {
    vector<int> nums1 = {1, 1, 1, 2};
    EXPECT_EQUAL(singleNumberii_sol2(nums1), 2);

    vector<int> nums2 = {1, 1, 1, 2, 2, 2, 3, 4, 3, 3};
    EXPECT_EQUAL(singleNumberii_sol2(nums2), 4);
}
