#include "permutation2.h"
#include <set>
#include <testing/SimpleTest.h>

void permutationHelper(vector<int>& left, vector<int>& selected,
                       vector< vector<int> >& result) {
    if (left.size() == 0) {
        result.push_back(selected);
        return;
    }

    set<int> seen;
    // choose:
    int size = left.size();
    for (int i = 0; i < size; i++) {
        if (seen.find(left[i]) == seen.end()) {
            // not found
            seen.insert(left[i]);
            int cur = left[i];
            left.erase(left.begin() + i);
            selected.push_back(cur);
            permutationHelper(left, selected, result);
            // restore
            selected.pop_back();
            left.insert(left.begin() + i, cur);
        }
        else {
            // ignore current number
            continue;
        }
    }
}

/**
 * @brief permuteUnique_sol1
 * @param nums
 * @return all unique permutations.
 * We will generate all permutations by construction. If we do not take uniqueness
 * into consideration, n numbers will generate n! permutations.
 * ex> input {1, 1, 2}
 * 1st: (1 | 1 | 2) 3 choices
 * 2nd: (1 | 2) | (1 | 2) | (1 | 1) 2 choices
 * 3nd: ... 1 choice
 * How to get rid of duplications? In each round, ignore duplicated number.
 */
vector< vector<int> > permuteUnique_sol1(vector<int>& nums) {
    vector< vector<int> > result;
    if (nums.size() == 0) return result;
    vector<int> selected;

    sort(nums.begin(), nums.end());
    permutationHelper(nums, selected, result);

    return result;
}


void permutationHelper2(vector<int>& left, vector<int>& selected,
                       vector< vector<int> >& result) {
    if (left.size() == 0) {
        result.push_back(selected);
        return;
    }

    vector<bool> seen(21, false);
    int shift = 10; // -10 -> index 0
    // choose:
    int size = left.size();
    for (int i = 0; i < size; i++) {
        if (!seen[left[i] + shift]) {
            // not found
            seen[left[i] + shift] = true;
            int cur = left[i];
            left.erase(left.begin() + i);
            selected.push_back(cur);
            permutationHelper(left, selected, result);
            // restore
            selected.pop_back();
            left.insert(left.begin() + i, cur);
        }
        else {
            // ignore current number
            continue;
        }
    }
}

/**
 * @brief permuteUnique_sol2
 * @param nums
 * @return
 * Solution 2 will use vector to simulate 'seen' in sol1 given that -10 <= nums[i] <= 10.
 */
vector< vector<int> > permuteUnique_sol2(vector<int>& nums) {
    vector< vector<int> > result;
    if (nums.size() == 0) return result;
    vector<int> selected;

    sort(nums.begin(), nums.end());
    permutationHelper2(nums, selected, result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums = {1, 1, 2};
    EXPECT_EQUAL(permuteUnique_sol1(nums).size(), 3);
}

PROVIDED_TEST("test for sol2:") {
    vector<int> nums = {1, 1, 2};
    EXPECT_EQUAL(permuteUnique_sol2(nums).size(), 3);
}
