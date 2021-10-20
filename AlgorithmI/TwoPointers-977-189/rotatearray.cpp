#include "rotatearray.h"
#include "testing/SimpleTest.h"

/*
 * Function: rotate
 * ------------------------------------
 * The function will return a vector with elements being rotated to the right by k steps.
 *
 * The basic idea is take the last k numbers away from vector, and then shift the rest to
 * the right by k steps, lastly put those k numbers in the first k indexes of the array.
 *
 * ex> origin:   1 2 3 4 5 6  step = 2
 *     extra:    5 6
 *     rotate:   x x 1 2 3 4
 *     put back: 5 6 1 2 3 4
 *
 * One insight is that if k == nums.size(), then the rotated array remain same. So effective
 * rotation step = k mod nums.size().
 *
 * T O(N), S O(K);
 */
void rotate_sol1(vector<int>& nums, int k) {
    // rotation feature
    k = k % nums.size();

    vector<int> knums(k, 0);
    int size = nums.size();
    for (int i = 0; i < k; i++) {
        knums[i] = nums[size - k + i];
    }

    // shift
    for (int i = size - 1; i >= k; i--) {
        nums[i] = nums[i-k];
    }

    // put back
    for (int i = 0; i < k; i++) {
        nums[i] = knums[i];
    }
}

/*
 * Function: rotate_sol2
 * ------------------------------------
 * Another way to achieve rotate is pretty mathematic. Notice that the correct index of
 * rotated element is (i + step) mod array.size(). Therefore, we use a new array to record
 * the result and then pass the result to original array.
 *
 * T O(N), S O(N);
 */
void rotate_sol2(vector<int>& nums, int k) {
    int size = nums.size();
    k = k % size;
    vector<int> extra(size, 0);

    for (int i = 0; i < size; i++) {
        extra[(i + k) % size] = nums[i];
    }

    // pass to nums
    for (int i = 0; i < size; i++) {
        nums[i] = extra[i];
    }
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for rotate_sol1():") {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    rotate_sol1(v, 3);
    EXPECT_EQUAL(v[0], 5);
    EXPECT_EQUAL(v[1], 6);
    EXPECT_EQUAL(v[2], 7);
    EXPECT_EQUAL(v[3], 1);
    EXPECT_EQUAL(v[4], 2);
    EXPECT_EQUAL(v[5], 3);
    EXPECT_EQUAL(v[6], 4);

    vector<int> v2 = {1};
    rotate_sol1(v2, 3);
    EXPECT_EQUAL(v2[0], 1);
}

PROVIDED_TEST("Test for rotate_sol2():") {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    rotate_sol2(v, 3);
    EXPECT_EQUAL(v[0], 5);
    EXPECT_EQUAL(v[1], 6);
    EXPECT_EQUAL(v[2], 7);
    EXPECT_EQUAL(v[3], 1);
    EXPECT_EQUAL(v[4], 2);
    EXPECT_EQUAL(v[5], 3);
    EXPECT_EQUAL(v[6], 4);

    vector<int> v2 = {1};
    rotate_sol2(v2, 3);
    EXPECT_EQUAL(v2[0], 1);
}
