#include "findposition.h"
#include "testing/SimpleTest.h"

/**
 * @brief searchRange_sol1
 * @param nums: a sorted array in non-decreasing order
 * @param target: the number to be found
 * @return the first position and the last position
 *
 * When comes to search in sorted array, binary search is a promising solution.
 * For binary search:
 *  case 1: not found, then return {-1, -1}
 *  case 2: the target number is found, return the index. But we cannot ensure the index
 *  is the first or last or in the middle of potential targets.
 *  ex>  {0, 0, 1, ..., 6, 6, 6, 6, 8, 9}
 *                      ^     ^  ^
 *                    first  mid end
 * One way to solve that is search along two sides of target index. (Bidireactional scan)
 * Then T: O(N + logN)
 */
vector<int> searchRange_sol1(vector<int>& nums, int target) {
    if (nums.size() == 0) return {-1, -1};
    int l = 0;
    int r = nums.size() - 1;
    int mid = 0;
    while (l <= r) {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target) {
            break;
        }
        else if (nums[mid] < target) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    if (l > r) return {-1, -1};

    // TODO: bidirectional scan;
    int left = mid;
    int right = mid;
    // always check boundary!!!
    while ((left > 0) && (nums[left-1] == nums[mid])) {
        left--;
    }
    while ((right < (nums.size() - 1)) && (nums[right+1] == nums[mid])) {
        right++;
    }

    return {left, right};
}

/**
 * How about solve it by with binary search twice, one for leftmost target and the other
 * for rightmost target.
 *
 * The question is how to let binary search know if it is the first target or the last
 * target?
 *
 * Let's consider the first target in BS.
 * When we find the target, check if nums[mid-1] == target if mid-1 is within the legal
 * range.
 */
vector<int> searchRange_sol2(vector<int> nums, int target) {
    if (nums.size() == 0) return {-1, -1};
    vector<int> result;
    // TODO: binary search for the first target
    int l = 0;
    int r = nums.size() - 1;
    int mid = 0;
    while (l <= r) {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target) {
            if ((mid > 0) && (nums[mid-1] == target)) {
                r = mid - 1;
            }
            else {
                // mid is the first
                break;
            }
        }
        else if (nums[mid] > target) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    if (l > r) return {-1, -1};
    result.push_back(mid);

    // TODO: binary search for the last target
    l = 0; r = nums.size() - 1;
    while (l <= r) {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target) {
            if ((mid < nums.size() - 1) && (nums[mid+1] == target)) {
                l = mid + 1;
            }
            else {
                break;
            }
        }
        else if (nums[mid] < target) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    if (l > r) return {-1, -1};
    result.push_back(mid);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    vector<int> nums1 = {5, 7, 7, 8, 8, 10};
    vector<int> res1 = searchRange_sol1(nums1, 8);
    EXPECT_EQUAL(res1[0], 3);
    EXPECT_EQUAL(res1[1], 4);

    vector<int> res2 = searchRange_sol1(nums1, 5);
    EXPECT_EQUAL(res2[0], 0);
    EXPECT_EQUAL(res2[1], 0);

    vector<int> res3 = searchRange_sol1(nums1, 0);
    EXPECT_EQUAL(res3[0], -1);
    EXPECT_EQUAL(res3[1], -1);

    vector<int> res4 = searchRange_sol1(nums1, 6);
    EXPECT_EQUAL(res4[0], -1);
    EXPECT_EQUAL(res4[1], -1);

    vector<int> nums2 = {1};
    vector<int> res5 = searchRange_sol1(nums2, 1);
    EXPECT_EQUAL(res5[0], 0);
    EXPECT_EQUAL(res5[1], 0);
}

PROVIDED_TEST("Test for sol2:") {
    vector<int> nums1 = {5, 7, 7, 8, 8, 10};
    vector<int> res1 = searchRange_sol2(nums1, 8);
    EXPECT_EQUAL(res1[0], 3);
    EXPECT_EQUAL(res1[1], 4);

    vector<int> res2 = searchRange_sol2(nums1, 5);
    EXPECT_EQUAL(res2[0], 0);
    EXPECT_EQUAL(res2[1], 0);

    vector<int> res3 = searchRange_sol2(nums1, 0);
    EXPECT_EQUAL(res3[0], -1);
    EXPECT_EQUAL(res3[1], -1);

    vector<int> res4 = searchRange_sol2(nums1, 6);
    EXPECT_EQUAL(res4[0], -1);
    EXPECT_EQUAL(res4[1], -1);

    vector<int> nums2 = {1};
    vector<int> res5 = searchRange_sol2(nums2, 1);
    EXPECT_EQUAL(res5[0], 0);
    EXPECT_EQUAL(res5[1], 0);
}
