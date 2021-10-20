#include "binarysearch.h"
#include "testing/SimpleTest.h"


/*
 * Function: searchHelper
 * ------------------------------------
 * This is a helper function for binary search, which will return the index of target number in an array.
 *
 * @param nums: an array with numbers in ascending order.
 * @param left: the leftmost index of search range (included).
 * @param right: the rightmost index of search range (included).
 * @param target: the target number.
 *
 * Classic binary search is implemented in recursion.
 * Base case:
 *      if left boundary is greater than right boundary, then target is not found in the given array.
 * Recursion:
 *      1. find the middle number.
 *      2. if target is equal to the middle one, then return index
 *         else > if smaller, search left half.
 *              > if greater, search right half.
 */
int searchHelper(vector<int>& nums, int left, int right, int target) {
    if (left > right) {
        return -1;
    }

    int pivot = (right + left) / 2;
    if (nums[pivot] != target) {
        if (nums[pivot] > target) {
            return searchHelper(nums, left, pivot-1, target);
        }
        else {
            return searchHelper(nums, pivot+1, right, target);
        }
    }
    else {
        return pivot;
    }
}

int search(vector<int>& nums, int target) {
    return searchHelper(nums, 0, nums.size()-1, target);
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */

PROVIDED_TEST("Test for binary search:") {
    vector<int> num = {-1, 0, 3, 5, 9, 12};
    EXPECT_EQUAL(search(num, 3), 2);
    EXPECT_EQUAL(search(num, 7), -1);
}

PROVIDED_TEST("Extreme test:") {
    vector<int> num = {};
    EXPECT_EQUAL(search(num, 3), -1);
}
