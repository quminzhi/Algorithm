#include "jumpgame2.h"
#include <testing/SimpleTest.h>

/**
 * @brief jump_sol1
 * @param nums
 * @return
 * From the solution for jump I, we can enumerate all solutions to the last index and find
 * the one with the least steps.
 *
 * T: O(N^2 * M), where M is maximum length one can jump from an index.
 *
 * But think of shortest path problem. The key idea is to find the shortest jumps by making
 * locally optimal choices at each index which leads to a globally optimal solution. We are
 * able to define f as:
 *
 * f(index): the shortest step from start to index.
 *
 * ex> 2, 3, 1, 1, 4
 *  i: 0  1  2  3  4
 *
 * f(index) = min(f(directly connected indices) + 1);
 * directly connected means indices where I can jump to current index with one jump.
 *
 * T: O(N^2)
 */
int jump_sol1(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int size = nums.size();
    vector<int> shortest_steps(size, INT_MAX);
    shortest_steps[0] = 0;

    for (int cur = 1; cur < size; cur++) {
        int shortest = INT_MAX;
        for (int pre = cur-1; pre >= 0; pre--) {
            // find all directed connected indices and update shortest_steps[cur]
            if (pre + nums[pre] >= cur) {
                if (shortest_steps[pre] + 1 < shortest) {
                    shortest = shortest_steps[pre] + 1;
                }
            }
        }
        shortest_steps[cur] = shortest;
    }

    return shortest_steps[nums.size()-1];
}


/**
 * @brief jump_sol2
 * @param nums
 * @return
 * Solution 2 will introduce greedy algorithm. What we are concerned about is which place
 * is able to take me furthest?
 *
 * ex> ... 3, 5, 2, 1, 4, 1, 6, 2, ...
 *         ^  |-----|
 *        cur   jump
 *
 * There are three choices (jump to 5, 2, 1) but where to go?
 * The greedy algorithm tells us to choose the one take me farthest, given that 'end' is
 * not within the range where current jump can reach. Consider the next jump:
 *
 * - if I jump to 5, I can jump to as farthest as 6 with 2 steps (one current and one next).
 *
 *    ... 3, 5, 2, 1, 4, 1, 6, 2, ...
 *        ^  ^              ^
 *       cur next        farthest
 *
 * - if I jump to 1, I can jump to as farthest as 4 with 2 steps
 *
 *    ... 3, 5, 2, 1, 4, 1, 6, 2, ...
 *        ^        ^  ^
 *       cur      next farthest
 *
 * Therefore, I will choose to jump to 5 for current jump decision.
 *
 * T: O(N)
 */
int jump_sol2(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int size = nums.size();
    int cur = 0;
    int target = size - 1;
    // the right end of the range where current jump can reach
    int next_end = cur + nums[cur];
    int jump = 0;
    while (next_end < target) {
        int farthest = 0;
        int best_next = 0;
        for (int next = cur + 1; next <= cur + nums[cur]; next++) {
            // jump range
            if ((next + nums[next]) > farthest) {
                farthest = next + nums[next];
                best_next = next;
            }
        }
        cur = best_next;
        next_end = farthest;
        jump++;
    }

    // last jump
    if (cur < target) jump++;

    return jump;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums = {2, 3, 1, 1, 4};
    EXPECT_EQUAL(jump_sol1(nums), 2);

    vector<int> nums2 = {2, 1};
    EXPECT_EQUAL(jump_sol1(nums2), 1);

    vector<int> nums3 = {1};
    EXPECT_EQUAL(jump_sol1(nums3), 0);
}

PROVIDED_TEST("test for sol2:") {
    vector<int> nums = {2, 3, 1, 1, 4};
    EXPECT_EQUAL(jump_sol2(nums), 2);

    vector<int> nums2 = {2, 1};
    EXPECT_EQUAL(jump_sol2(nums2), 1);

    vector<int> nums3 = {1};
    EXPECT_EQUAL(jump_sol2(nums3), 0);
}
