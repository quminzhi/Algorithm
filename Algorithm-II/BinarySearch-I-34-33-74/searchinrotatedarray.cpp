#include "searchinrotatedarray.h"
#include "testing/SimpleTest.h"

/**
 * @brief search_sol1
 * @param nums: an array of unique number with ascending order, but rotated by unknown steps.
 * @param target: the number to be found
 * @return the index of the number.
 *
 * The ideal case is array is in ascending order without being rotated. Then it can
 * be solved by binary search. So the key problem here is how to rotate back so that
 * the array is sorted in ascending order.
 *
 * The first solution is to scan the smallest element in the array for it should be
 * the index of 0 of ideal array. Then apply binary search to it.
 *
 * T: O(NlogN)
 */
int search_sol1(vector<int>& nums, int target) {
    if (nums.size() == 0) return -1;
    vector<int> vec;
    // TODO: find sorted array
    vec.insert(vec.end(), nums.begin(), nums.end());
    vec.insert(vec.end(), nums.begin(), nums.end());
    // return the index of min value
    int begin = min_element(nums.begin(), nums.end()) - nums.begin();
    int end = begin + nums.size() - 1;

    // TODO: binary search on vec[begin, end];
    int left = begin;
    int right = end;
    int mid = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (vec[mid] == target) {
            // find index in rotated array
            return mid % nums.size();
        }
        else if (vec[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}


/**
 * Is there a better way? a O(logN) solution.
 * Split and binary search in one part?
 * ex> {4,5,6,7,0,1,2}  ==> {4,5,6,7} and {0,1,2}
 *      ^
 *    pivot
 * If target > pivot, search in the first half, otherwise search the second half.
 *
 * T: O(NlogN)
 *
 * Can we do it better? Change the behavior of binary search. How to revise our
 * binary search?
 *
 * The key point is determine range!
 *
 * ex>  4,  5,  6,  7,  0,  1,  2
 *      ^           ^   ^       ^
 *      |--sorted---|   |sorted-|
 *    begin                    end
 *
 * Case 1: if nums[mid] >= nums[begin] which is 4, then
 *      4,  5,  6,  7,  0,  1,  2
 *          ^
 *         mid
 *      |---|-------------------|
 *      sorted     unsorted
 * if (nums[mid] > target > nums[begin]), then we will search in sorted half,
 * great! do as normal. otherwise, we will search in unsorted half, move begin
 * to mid + 1
 *
 * Case 2: if nums[mid] < nums[begin], then (notice mid == begin cann't be
 * categorized in this case)
 *      4,  5,  6,  7,  0,  1,  2
 *                          ^
 *                         mid
 *      |-----unsorted------|---|
 *                          sorted
 * if (nums[mid] < target < nums[end]), search sorted part, otherwise, search
 * unsorted part.
 */
int search_sol2(vector<int>& nums, int target) {
    if (nums.size() == 0) return -1;
    int begin = 0;
    int end = nums.size() - 1;
    int mid = 0;
    while (begin <= end) {
        mid = begin + ((end - begin) >> 1);
        if (nums[mid] == target) {
            return mid;
        }
        else {
            if (nums[mid] >= nums[begin]) {
                if ((nums[mid] > target) && (target >= nums[begin])) {
                    end = mid - 1;
                }
                else {
                    begin = mid + 1;
                }
            }
            else {
                if ((nums[mid] < target) && (target <= nums[end])) {
                    begin = mid + 1;
                }
                else {
                    end = mid - 1;
                }
            }
        }
    }

    return -1;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    vector<int> nums = {4,5,6,7,0,1,2};
    EXPECT_EQUAL(search_sol1(nums, 7), 3);
    EXPECT_EQUAL(search_sol1(nums, 4), 0);
}

PROVIDED_TEST("Test for sol2:") {
    vector<int> nums = {4,5,6,7,0,1,2};
    EXPECT_EQUAL(search_sol2(nums, 7), 3);
    EXPECT_EQUAL(search_sol2(nums, 4), 0);

    vector<int> nums1 = {3, 1};
    EXPECT_EQUAL(search_sol2(nums1, 1), 1);
}
