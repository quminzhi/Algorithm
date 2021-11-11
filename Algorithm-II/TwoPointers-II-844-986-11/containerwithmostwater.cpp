#include "containerwithmostwater.h"
#include "testing/SimpleTest.h"

/**
 * @brief maxArea_sol1
 * @param height: vectors consist of height of each pillar
 * @return the maximum area of water two pillars could contain
 * Area = min(height[l], height[r]) * (r - l)
 * Our goal is maximum two operands on the two sides of '*' sign.
 * We will use greedy algorithm to solve it.
 * 1. Set two pointers to at the leftmost and rightmost index of
 *    pillars where we maximize '(r - l)'.
 * 2. Move r to left and l to right respectively.
 *    - if height[r-1] < height[r], then jump it, since the second operand get
 *      smaller but the first remain same at best.
 *    - same operation to l as it moves to right.
 *
 * T: O(N^2)
 *
 * Bad! Our improvement is based on other fact: If left do not change and only
 * move right pillar when the height of right pillar is higher than left one,
 * the water area will get smaller.
 *
 * ex>  1  2  3  5  3  2  1
 *      ^                 ^
 *     left         <-- right
 *
 * When right go from 1 to 5, (r - l) get smaller, and min(height[l], height[r])
 * do NOT change!
 *
 * So fixing one pillar is not wise. A better way is when height[l] < height[r],
 * move l to right, otherwise move r to left.
 *
 * Summary:
 *  - maximize min(height[l], height[r]): move smaller one such that it can be
 *    greater.
 *  - maximize (r - l): starting from leftmost and rightmost.
 *
 * T: O(N)
 */
int maxArea_sol1(vector<int>& height) {
    if (height.size() < 2) return 0;
    int l = 0;
    int r = height.size() - 1;
    int maxArea = min(height[l], height[r]) * (r - l);
    int area = 0;
    while (l < r) {
        if (height[l] <= height[r]) {
            // TODO: move to next greater one
            int leftHeight = height[l];
            while ((l < r) && (leftHeight >= height[l])) {
                l++;
            }
        }
        else {
            int rightHeight = height[r];
            while ((l < r) && (height[r] <= rightHeight)) {
                r--;
            }
        }
        // TODO: update maxArea
        if (l < r) {
            area = min(height[l], height[r]) * (r - l);
            maxArea = area > maxArea ? area : maxArea;
        }
    }

    return maxArea;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    EXPECT_EQUAL(maxArea_sol1(height), 49);

    vector<int> height1 = {1,1};
    EXPECT_EQUAL(maxArea_sol1(height1), 1);

}
