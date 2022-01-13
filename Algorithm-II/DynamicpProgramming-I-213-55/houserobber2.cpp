#include "houserobber2.h"
#include <testing/SimpleTest.h>
#include <iostream>

/**
 * @brief maxIncome
 * @param vals: a vector of money each house has
 * @param size: size of houses
 * @param start: start of available houses to rob
 * @param length: how many houses left to rob
 * @return
 */
int maxIncome(vector< vector< int > >& buf,
              vector<int>& vals, int size,
              int start, int length) {
    if (length <= 0) {
        return 0;
    }

    if (buf[start][length] != -1) {
//        cout << start << ": " << length << " => " << buf[start][length] << endl;
        return buf[start][length];
    }

    buf[start][length] = max(vals[start] + maxIncome(buf, vals, size, (start + 2) % size, length - 2),
                             maxIncome(buf, vals, size, (start + 1) % size, length - 1)
                            );
//    cout << start << ": " << length << " => " << buf[start][length] << endl;

    return buf[start][length];
}

/**
 * @brief rob_sol1
 * @param nums
 * @return the maximum value of robbed money
 * Recall from algorithm for houserobber, and we can find there is some similarity betwee
 * these two problems. The only difference is there is a circle in houserobber2.
 *
 * But the circle only affects the decision for the first time.
 *
 * ex> 1 -> 2 -> 3 -> 4 -> 5
 *     |-------<-----------|
 *
 * If we have decided where to start, let's say 1.
 * then the problem will be:
 *
 * - choose 1 + max{ 3 -> 4 }
 * - not choose 1 + max { 2 -> 3 -> 4 -> 5 }
 *
 * it will become houserobber problem. And for the houserobber, the basic algorithm is
 *
 * f(start, length) = max(
 *     val[start] + f((start + 2) % size, length - 2),  // circle version
 *     f((start + 1) % size, length - 1)
 * )
 *
 * and base case occurs when length < 0, return 0;
 */
int rob_sol1(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    int size = nums.size();
    vector< vector< int > > buf(
                size,
                vector<int>(size+1, -1));
    for (int i = 0; i < size; i++) {
        buf[i][0] = 0;
    }

    int maxMoney = 0;
    // try all starting point
    for (int i = 0; i < size; i++) {
        int bigger = max(nums[i] + maxIncome(buf, nums, size, (i + 2) % size, size-3), // i-1, i, i+1
                       maxIncome(buf, nums, size, (i + 1) % size, size-1)); // i
        if (bigger > maxMoney) {
            maxMoney = bigger;
        }
    }

    return maxMoney;
}

/**
 * @brief rob_sol2
 * @param nums
 * @return
 * According to the formula we derived from solution 1, we are able to solve the problem
 * from bottom to top. That's dynamic programming.
 *
 * f(start, length) = max(val[start] + f((start + 2) % size), length-2),
 *                        f((start + 1) % size), length-1)
 *                       )
 *
 * ex> 2 -> 3 -> 2 -> 3  (size: 4)
 *     |------<-------|
 * buf:
 * start\length  0  1  2              3
 *   0           0  2  max(2 + 0, 3)  ...
 *   1           0  3  ...
 *   2           0  2
 *   3           0  3
 */
int rob_sol2(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    if (nums.size() == 2) return max(nums[0], nums[1]); // notice 'size-3' in formula
    int size = nums.size();
    vector< vector< int > > buf(
                size,
                vector<int>(size+1, -1));
    for (int start = 0; start < size; start++) {
        buf[start][0] = 0;
        buf[start][1] = nums[start];
    }

    // !!!: notice render order
    for (int length = 2; length <= size; length++) {
        for (int start = 0; start < size; start++) {
            buf[start][length] = max(nums[start] + buf[(start + 2) % size][length-2],
                                     buf[(start + 1) % size][length-1]);
//            cout << start << ": " << length << " => " << buf[start][length] << endl;
        }
    }

    int maxMoney = 0;
    // try all starting point
    for (int i = 0; i < size; i++) {
        int bigger = max(nums[i] + buf[(i + 2) % size][size-3], // i-1, i, i+1
                       buf[(i + 1) % size][size-1]); // i
        if (bigger > maxMoney) {
            maxMoney = bigger;
        }
    }

    return maxMoney;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums1 = {2, 3, 2};
    EXPECT_EQUAL(rob_sol1(nums1), 3);

    vector<int> nums2 = {1, 2, 3, 1};
    EXPECT_EQUAL(rob_sol1(nums2), 4);

    vector<int> nums3 = {1, 1, 3, 6, 7, 10, 7, 1, 8, 5, 9, 1, 4, 4, 3};
    EXPECT_EQUAL(rob_sol1(nums3), 41);
}

PROVIDED_TEST("test for sol2:") {
    vector<int> nums1 = {2, 3, 2};
    EXPECT_EQUAL(rob_sol2(nums1), 3);

    vector<int> nums2 = {1, 2, 3, 1};
    EXPECT_EQUAL(rob_sol2(nums2), 4);

    vector<int> nums3 = {0, 0};
    EXPECT_EQUAL(rob_sol2(nums3), 0);

    vector<int> nums4 = {1, 1, 3, 6, 7, 10, 7, 1, 8, 5, 9, 1, 4, 4, 3};
    EXPECT_EQUAL(rob_sol2(nums4), 41);
}
