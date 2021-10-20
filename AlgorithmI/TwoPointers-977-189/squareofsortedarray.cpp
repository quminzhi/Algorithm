#include "squareofsortedarray.h"
#include <map>
#include <math.h>
#include "testing/SimpleTest.h"

/*
 * Function: sortedSquares
 * ------------------------------------
 * The function will square all members in the vector and return a new vector with squared
 * members.
 *
 * @param nums: input vectors with numbers sorted in non-decreasing order.
 *
 * Potential overhead:
 * 1. How to make use of the quality of original vector - non-decreasing.
 * => Sol: Use two pointers pointing to the first negative and non-negative number respectively.
 *    ex> -7, -3, 2, 3, 11
 *             ^  ^
 *          <- l  r ->
 *    Then we have split original vector into two parts. Both of left and right half is in
 * ascending order along the way the pointer goes. So the question becomes kinda like a basic
 * operation in merging sort, which is combining two ordered vectors into one.
 *
 * 2. Calculate square of each number. There will be many repetitive calculation if there
 * are a lot of same numbers in the array.
 * => Sol: use a map to backup the result of calculation of the squre of numbers.
 *
 */
vector<int> sortedSquares_sol1(vector<int>& nums) {
    vector<int> result;
    map<int, int> square;

    /* Initialize pointers as the case for all numbers in the vector are negative.
     * -1 -1 -1 -1
     *           ^  ^
     *           L  R
     */
    int left = nums.size() - 1;
    int right = left + 1;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] >= 0) {
            right = i;
            left = i - 1;
            break;
        }
    }

    int numsLeft = 0;
    int numsRight = 0;
    while ((left >= 0) && (right < nums.size())) {
        numsLeft = abs(nums[left]);
        numsRight = nums[right];
        if (numsLeft < nums[right]) {
            if (square.find(numsLeft) == square.end()) {
                square[numsLeft] = numsLeft * numsLeft;
            }
            result.push_back(square[numsLeft]);
            left--;
        }
        else {
            if (square.find(numsRight) == square.end()) {
                square[numsRight] = numsRight * numsRight;
            }
            result.push_back(square[numsRight]);
            right++;
        }
    }

    while (left >= 0) {
        numsLeft = abs(nums[left]);
        if (square.find(numsLeft) == square.end()) {
            square[numsLeft] = numsLeft * numsLeft;
        }
        result.push_back(square[numsLeft]);
        left--;
    }

    while (right < nums.size()) {
        numsRight = nums[right];
        if (square.find(numsRight) == square.end()) {
            square[numsRight] = numsRight * numsRight;
        }
        result.push_back(square[numsRight]);
        right++;
    }

    return result;
}

/*
 * Function: sortedSquares_sol2
 * ------------------------------------
 * Different from above solution, we just start from two ends and move inward. That will
 * be much easier. Following is the implementation without using map to backup repetitive
 * numbers.
 *
 * ex> -7, -3, 2, 3, 11
 *      ^             ^
 *      L             R
 * result = 121, 49, 9, 9, 4  reverse order: 4, 9, 9, 49, 121
 * But if we insert at beginning index each time, then the order is ascending. Perfect.
 */
vector<int> sortedSquares_sol2(vector<int>& nums) {
    vector<int> result;
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        if (abs(nums[left]) >= abs(nums[right])) {
            result.insert(result.begin(), nums[left] * nums[left]);
            left++;
        }
        else {
            result.insert(result.begin(), nums[right] * nums[right]);
            right--;
        }
    }

    return result;
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sortedSquares_sol1():") {
    vector<int> v1 = {-4, -1, 0, 3, 10};
    vector<int> r1 = sortedSquares_sol1(v1);
    EXPECT_EQUAL(r1[0], 0);
    EXPECT_EQUAL(r1[2], 9);
    EXPECT_EQUAL(r1[4], 100);

    vector<int> v2 = {-7, -3, 2, 3, 11};
    vector<int> r2 = sortedSquares_sol1(v2);
    EXPECT_EQUAL(r2[0], 4);
    EXPECT_EQUAL(r2[1], 9);
    EXPECT_EQUAL(r2[2], 9);

    vector<int> v3 = {1};
    vector<int> r3 = sortedSquares_sol1(v3);
    EXPECT_EQUAL(r3[0], 1);
}

PROVIDED_TEST("Test for sortedSquares_sol2():") {
    vector<int> v1 = {-4, -1, 0, 3, 10};
    vector<int> r1 = sortedSquares_sol2(v1);
    EXPECT_EQUAL(r1[0], 0);
    EXPECT_EQUAL(r1[2], 9);
    EXPECT_EQUAL(r1[4], 100);

    vector<int> v2 = {-7, -3, 2, 3, 11};
    vector<int> r2 = sortedSquares_sol2(v2);
    EXPECT_EQUAL(r2[0], 4);
    EXPECT_EQUAL(r2[1], 9);
    EXPECT_EQUAL(r2[2], 9);

    vector<int> v3 = {1};
    vector<int> r3 = sortedSquares_sol2(v3);
    EXPECT_EQUAL(r3[0], 1);
}
