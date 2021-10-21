#include "movezeros.h"
#include "testing/SimpleTest.h"

/*
 * Function: moveZero_sol1
 * ------------------------------------
 * The function will move all zeros to the end of the vector.
 *
 * Our algorithm make use of the feature that the original elements in the vector are
 * in ascending order except zeros.
 *
 * So we use a pointer scanning from left to right.
 * if the number is nonzero, which means it is in the right index,
 *      nothing to do;
 * else, which means we find the first zero starting from last nonzero number. That's the
 * place where the next nonzero number should be put.
 *      use a new pointer find the next nonzero number;
 *      if not found, then we are done, meaning there are no nonzero numbers left.
 *      else exchange zero and the next nonzero number;
 *
 * T: O(M * k) M is total number of nonzero numbers that before at least one zero.
 * S: O(1)
 */
void moveZeroes_sol1(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 0) {
            int nonzero = i + 1;
            while (nonzero < nums.size()) {
                if (nums[nonzero] != 0) {
                    break;
                }
                nonzero++;
            }
            if (nonzero >= nums.size()) {
                // we are done
                break;
            }
            else {
                nums[i] = nums[nonzero];
                nums[nonzero] = 0;
            }
        }
    }
}


/*
 * Function: moveZeroes_sol2
 * ------------------------------------
 * Solution 2 is pretty clever since it solve the problem from a different perspective.
 * The original question has a counterpart that "move all nonzero numbers to the front".
 * So the problem becomes easier:
 * 1. move all nonzeroes to the front.
 * 2. append zeroes to the last nonzero number.
 *
 * ex> 1, 0, 0, 3, 0, 7
 *     ^
 *    last: point to the place where nonzero number should go
 *
 * T: O(N), S: O(1)
 */
void moveZeroes_sol2(vector<int>& nums) {
    int lastNonZero = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[lastNonZero++] = nums[i];
        }
    }

    for (int i = lastNonZero; i < nums.size(); i++) {
        nums[i] = 0;
    }
}

void moveZeroes_sol3(vector<int>& nums) {
    stable_partition(begin(nums), end(nums), [](int i){ return i; });
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for moveZeroes_sol1():") {
    vector<int> v1 = {0};
    moveZeroes_sol1(v1);
    EXPECT_EQUAL(v1[0], 0);

    vector<int> v2 = {0, 1, 0, 3, 12};
    moveZeroes_sol1(v2);
    EXPECT_EQUAL(v2[0], 1);
    EXPECT_EQUAL(v2[1], 3);
    EXPECT_EQUAL(v2[2], 12);
}

PROVIDED_TEST("Test for moveZeroes_sol2():") {
    vector<int> v1 = {0};
    moveZeroes_sol2(v1);
    EXPECT_EQUAL(v1[0], 0);

    vector<int> v2 = {0, 1, 0, 3, 12};
    moveZeroes_sol2(v2);
    EXPECT_EQUAL(v2[0], 1);
    EXPECT_EQUAL(v2[1], 3);
    EXPECT_EQUAL(v2[2], 12);
}

PROVIDED_TEST("Test for moveZeroes_sol3():") {
    vector<int> v1 = {0};
    moveZeroes_sol3(v1);
    EXPECT_EQUAL(v1[0], 0);

    vector<int> v2 = {0, 1, 0, 3, 12};
    moveZeroes_sol3(v2);
    EXPECT_EQUAL(v2[0], 1);
    EXPECT_EQUAL(v2[1], 3);
    EXPECT_EQUAL(v2[2], 12);
}
