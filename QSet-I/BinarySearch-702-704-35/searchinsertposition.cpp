#include "searchinsertposition.h"
#include "testing/SimpleTest.h"

/*
 * Function: searchInsert
 * ------------------------------------
 * The function will return the index of target if found, or the proper index to insert
 * target value.
 *
 * One good observation is that: if the target value is not found. What will happen to
 * the while loop?
 *
 * ex>             1 3 5 7
 *                   ^
 *                   pivot(left and right)
 * if target > 3, then left = pivot + 1, which will point to the index of 5, which is the place
 * target should be inserted.
 * if target < 3, then right = pivot - 1, which will  point to the index of 1, and left still
 * points to the index of 3, which happens to be the position where target should be inserted.
 *
 * Therefore, return left if target is not found.
 */
int searchInsert(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    int pivot;
    while (left <= right) {
        pivot = left + (right - left) / 2;
        if (nums[pivot] == target) {
            return pivot;
        }
        else {
            if (nums[pivot] > target) {
                right = pivot - 1;
            }
            else {
                left = pivot + 1;
            }
        }
    }

    return left;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for searchInsert():") {
    vector<int> nums = {1, 3, 5, 6};
    EXPECT_EQUAL(searchInsert(nums, 1), 0);
    EXPECT_EQUAL(searchInsert(nums, 2), 1);
    EXPECT_EQUAL(searchInsert(nums, 7), 4);
    EXPECT_EQUAL(searchInsert(nums, 0), 0);
}
