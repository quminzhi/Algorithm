#include "findminimuminrotatedarray.h"
#include "testing/SimpleTest.h"

/**
 * @brief findMin_sol1
 * @param nums: a sorted arrary rotated by n steps.
 * @return the minimum number in nums
 * It's easy to find a O(N) solution by iterating the nums find the minimum number.
 *
 * How to use binary search to find the minimum number of an array?
 *
 * I. Sorted array is rotated by 0 steps
 * ex> nums = {1, 2, 3, 4, 5}  when nums[left] < nums[right], just return nums[left]
 *             ^           ^
 *            left        right
 *
 * II. Sorted array is rotated by n steps
 * ex> nums = {4, 5, 6, 7, 8, 1, 2, 3}  when nums[left] > nums[right]
 *             ^                    ^
 *            left                right
 *
 * Case 1: if nums[mid] > nums[left], the minimum must lie in unsorted half
 *     nums = {4, 5, 6, 7, 8, 1, 2, 3}
 *             ^        ^           ^
 *            left     mid         right
 *            |--sorted-|--unsorted--|
 *                       exclude mid
 *
 * Case 2: if nums[mid] < nums[left], the minimum must lie in unsorted half
 *     nums = {4, 5, 6, 7, 8, 1, 2, 3}
 *             ^                 ^  ^
 *            left              mid right
 *            |-----unsorted-----|---|
 *              include mid      sorted
 *
 * Case 3: if nums[mid] == nums[left], the minimum number is mid + 1
 *     nums = {4, 1, 2, 3}
 *             ^        ^
 *            left      right
 *            mid
 */
int findMin_sol1(vector<int>& nums) {
    if (nums.size() == 0) return INT_MAX;
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
        // TODO: array without rotated
        if (nums[left] <= nums[right]) return nums[left];
        // TODO: array is rotated
        mid = left + ((right - left) >> 1);
        if (nums[mid] == nums[left]) {
            return nums[mid + 1];
        }
        else if (nums[mid] > nums[left]) {
            left = mid + 1; // exclude middle
        }
        else {
            right = mid; // include middle
        }
    }

    return INT_MAX;
}

/**
 * I: if nums[left] < nums[right] return nums[right]
 * I: Case 1: nums[mid] > nums[left], then search in right part, nums[mid] included.
 *    Case 2: nums[mid] < nums[left], then search in left part, nums[mid] excluded.
 *    Case 3: nums[mid] == nums[left], return nums[mid]
 */
int findMax_sol1(vector<int>& nums) {
    if (nums.size() == 0) return INT_MIN;
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
        // TODO: array without rotated
        if (nums[left] <= nums[right]) return nums[right];
        // TODO: array is rotated
        mid = left + ((right - left) >> 1);
        if (nums[mid] == nums[left]) {
            return nums[mid];
        }
        else if (nums[mid] > nums[left]) {
            left = mid; // include middle
        }
        else {
            right = mid - 1; // exclude middle
        }
    }

    return INT_MIN;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    vector<int> nums = {4, 5, 6, 7, 8, 1, 2, 3};
    EXPECT_EQUAL(findMin_sol1(nums), 1);

    vector<int> nums2 = {4, 5, 6, 7, 1, 2, 3};
    EXPECT_EQUAL(findMin_sol1(nums2), 1);

    vector<int> nums3 = {11, 13, 15, 17};
    EXPECT_EQUAL(findMin_sol1(nums3), 11);

    vector<int> nums4 = {1};
    EXPECT_EQUAL(findMin_sol1(nums4), 1);

    vector<int> nums5 = {7, 1};
    EXPECT_EQUAL(findMin_sol1(nums5), 1);
}

PROVIDED_TEST("Test for sol1:") {
    vector<int> nums = {4, 5, 6, 7, 8, 1, 2, 3};
    EXPECT_EQUAL(findMax_sol1(nums), 8);

    vector<int> nums2 = {4, 5, 6, 7, 1, 2, 3};
    EXPECT_EQUAL(findMax_sol1(nums2), 7);

    vector<int> nums3 = {11, 13, 15, 17};
    EXPECT_EQUAL(findMax_sol1(nums3), 17);

    vector<int> nums4 = {1};
    EXPECT_EQUAL(findMax_sol1(nums4), 1);

    vector<int> nums5 = {7, 1};
    EXPECT_EQUAL(findMax_sol1(nums5), 7);
}
