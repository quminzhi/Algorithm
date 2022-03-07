#include "singlenumberiii.h"
#include <unordered_map>
#include "testing/SimpleTest.h"

/*
 * Function: singleNumber_sol1
 * ------------------------------------
 * A generic method to solve the problem is by hash_map.
 *
 * T: O(N), S: O(N)
 */
vector<int> singleNumberiii_sol1(vector<int>& nums) {
    unordered_map<int, int> counters;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        if (counters.find(nums[i]) != counters.end()) {
            counters[nums[i]]++;
        }
        else {
            counters[nums[i]] = 1;
        }
    }

    for (auto&& counter : counters) {
        if (counter.second == 1) {
            result.push_back(counter.first);
        }
    }

    return result;
}


/*
 * Function: singleNumberiii_sol2
 * ------------------------------------
 * To solve the problem in a constant space is a bit tricky but could be done with the
 * help of two bitmasks.
 *
 * XOR: 'x XOR y' indiciates the difference between x and y.
 *
 * Can we use the same method in singleNumberi? Could we extract x and y directly from
 * this bitmask? No. Though we could use this bitmask as a marker to separate x and y.
 *
 * ex> nums = { x, y, a, a }
 *                   x = 0001
 *                   y = 0010
 *                   a = ????
 *                   a = ????
 *             bitmask = 0011 (x XOR y)
 *  bitmask & -bitmask = 0001 (rightmost 1-bit)
 *
 * Let's do bitmask & (-bitmask) to isolate the rightmost 1-bit, which is different
 * between x and y. There are two cases:
 *  - 1-bit for x, and 0-bit for y.
 *  - 1-bit for y, and 0-bit for x.
 *
 * Let's say it's the first case.
 * There is a very important fact: when just looking this bit of a numbers in 'nums', only
 * x and other numbers except y will map to this bit as 1.
 *
 * So we are able to distinguish y from other numbers that map to rightmost bit as 1.
 *
 * ex> nums = {1, 2, 7, 7, 8, 8}
 * say: x = 1 and y = 2, then numbers that map to rightmost bit as 1 is {1, 7, 7}. Thereby
 * we are able to find x by the same method as singleNumberi.
 */
vector<int> singleNumberiii_sol2(vector<int>& nums) {
    int bitmask = 0;
    for (auto&& num : nums) {
        bitmask ^= num; // the difference of x and y
    }

    int rightmostBit = bitmask & -bitmask;
    // TODO: find rightmost bit sequence
    int xBitmast = 0;
    for (auto&& num : nums) {
        // assuming: 1-bit for x, and 0-bit for y.
        if ((num & rightmostBit) == rightmostBit) {
            xBitmast ^= num;
        }
    }
    int x = xBitmast;
    int y = x ^ bitmask;

    return {x, y};
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for singleNumber_sol1():") {
    vector<int> nums1 = {1,2,1,3,2,5};
    EXPECT_EQUAL(singleNumberiii_sol1(nums1)[0], 5);
    EXPECT_EQUAL(singleNumberiii_sol1(nums1)[1], 3);
}

PROVIDED_TEST("Test for singleNumber_sol2():") {
    vector<int> nums1 = {1,2,1,3,2,5};
    EXPECT_EQUAL(singleNumberiii_sol2(nums1)[0], 3);
    EXPECT_EQUAL(singleNumberiii_sol2(nums1)[1], 5);

    vector<int> nums2 = {1,1,0,-2147483648};
    EXPECT_EQUAL(singleNumberiii_sol2(nums2)[0], -2147483648);
    EXPECT_EQUAL(singleNumberiii_sol2(nums2)[1], 0);
}
