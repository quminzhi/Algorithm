#include "jumpgame.h"
#include <testing/SimpleTest.h>

bool jump(vector<int>& nums, int start, int end) {
    if (start == end) {
        return true;
    }
    if (start > end) {
        return false;
    }

    for (int i = 1; i <= nums[start]; i++) {
        if (jump(nums, start + i, end)) {
            return true;
        }
    }

    return false;
}

/**
 * @brief canJump
 * @param nums
 * @return
 * Divide and conquer.
 *
 * ex> 2, 3, 1, 1, 4
 *  i: 0  1  2  3  4
 *
 * start from index 0: jump choice 1 ~ val[0]
 * =>: 1 + jump in {3, 1, 1, 4}
 *     2 + jump in {1, 1, 4}
 *
 * define f as f(int index, int end)
 * =>: f(index, end) = f(index + 1, end) or f(index + 2, end) or .. or f(index + maximum, end)
 */
bool canJump_sol1(vector<int>& nums) {
    return jump(nums, 0, nums.size()-1);
}

/**
 * @brief canJump_sol2
 * @param nums
 * @return
 * Time for dynamic programming.
 *
 * f(start, end) = f(start+1, end) | f(start+2, end) | ... | f(start+max, end)
 *
 * ex> 2, 3, 1, 1, 4
 *  i: 0  1  2  3  4
 *
 *  end   0  1  2  3  4
 * index
 *   0    T  T  T  T  T
 *   1       T  T  T  T
 *   2          T  T  T
 *   3             T  T
 *   4                T
 *
 * T: O(N^2 * M)
 */
bool canJump_sol2(vector<int>& nums) {
    if (nums.size() == 0)  return false;
    if (nums.size() == 1)  return true;
    int size = nums.size();
    vector< vector<bool> > buf(size,
                               vector<bool>(size, false));
    int target = nums.size() - 1;
    for (int start = size-1; start >= 0; start--) {
        // TODO: where can be reached with my self
        for (int end = start; end <= target; end++) {
            if (end <= start + nums[start]) {
                buf[start][end] = true;
            }
            else {
                for (int jump = start + 1; jump <= start + nums[start]; jump++) {
                    buf[start][end] = buf[start][end] | buf[jump][end];
                }
            }
        }
    }

    return buf[0][target];
}

/**
 * @brief canJump_sol3
 * @param nums
 * @return
 * In fact, we can refine function to have only one parameter.
 * f(index) = true means I can jump to the end from index, f(index) = false otherwise.
 *
 * ex> 2, 3, 1, 1, 4
 *  i: 0  1  2  3  4
 *
 * In dynamic programming, we start from the last one.
 * f(4) = true;
 * f(3) = f(3+1) | f(3+2) | ... | f(3+maximum)
 * ...
 *
 * T: O(N^2)
 */
bool canJump_sol3(vector<int>& nums) {
    if (nums.size() == 0)  return false;
    if (nums.size() == 1)  return true;
    int size = nums.size();
    vector<bool> buf(size, false);
    int target_index = size - 1;
    for (int i = size - 1; i >= 0; i--) {
        if (i == target_index) {
            buf[i] = true;
        }
        else {
            for (int jump = 1; jump <= nums[i]; jump++) {
                if (buf[i+jump] == true) {
                    buf[i] = true;
                    break;
                }
            }
        }
    }

    return buf[0];
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums = {2, 3, 1, 1, 4};
    EXPECT(canJump_sol1(nums));
}

PROVIDED_TEST("test for sol2:") {
    vector<int> nums = {2, 3, 1, 1, 4};
    EXPECT(canJump_sol2(nums));
}

PROVIDED_TEST("test for sol3:") {
    vector<int> nums = {2, 3, 1, 1, 4};
    EXPECT(canJump_sol3(nums));
}
