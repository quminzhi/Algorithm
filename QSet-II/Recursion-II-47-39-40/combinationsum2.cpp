#include "combinationsum2.h"
#include <iostream>
#include <set>
#include <testing/SimpleTest.h>

void  combinationSum2Helper(vector<int>& candidates,
                            vector<int>& selected,
                            vector< vector<int> >& result,
                            set<vector<int>>& seen,
                            int target,
                            int start) {
    // base case:
    if (target == 0) {
        if (seen.find(selected) == seen.end()) {
            seen.insert(selected);
            result.push_back(selected);
        }
        return;
    }
    if ((candidates.size() == 0) || (target < 0)) {
        return;
    }
    if (start >= candidates.size()) {
        return;
    }
    if (candidates[start] > target) {
        return;
    }

    // recursion:
    // choose
    int cur = candidates[start];
    selected.push_back(cur);
    combinationSum2Helper(candidates, selected, result, seen, target - cur, start + 1);
    selected.pop_back();
    // don't choose
    combinationSum2Helper(candidates, selected, result, seen, target, start + 1);
}

/**
 * @brief combinationSum2
 * @param candidates
 * @param target
 * @return
 * The key to remove duplication resorts to set.
 *
 * T: O(2^N)
 */
vector< vector<int> > combinationSum2(vector<int>& candidates, int target) {
    vector< vector<int> > result;
    vector<int> selected;
    set<vector<int>> seen;
    sort(candidates.begin(), candidates.end());

    combinationSum2Helper(candidates, selected, result, seen, target, 0);

    return result;
}

void combinationSum2Helper2(vector<int>& candidates_group,
                            vector<int>& selected,
                            vector< vector<int> >& result,
                            int target,
                            int start) {
    // base case:
    if (target == 0) {
        result.push_back(selected);
        return;
    }
    if ((target < 0) | (start >= candidates_group.size())) {
        return;
    }

    // recursion:
    int cnt = candidates_group[start];
    int cur = start;
    int next_start = start + 1;
    while ((next_start < candidates_group.size()) && (candidates_group[next_start] == 0)) {
        next_start++;
    }

    // select 0 to cnt times
    for (int i = 0; i <= cnt; i++) {
        for (int j = 0; j < i; j++) {
            selected.push_back(cur);
        }
        combinationSum2Helper2(candidates_group, selected, result, target - cur * i, next_start);
        for (int j = 0; j < i; j++) {
            selected.pop_back();
        }
    }
}

/**
 * @brief combinationSum2_sol2
 * @param candidates
 * @param target
 * @return
 * Two observations:
 * - In this problem, each number in the input is not unique. The implication of this
 * difference is that we need some mechanism to avoid generating duplicate combinations.
 * - In this problem, each number can be used only once. The implication of this difference
 * is that once a number is chosen as a candidate in the combination, it will not appear
 * again as a candidate later.
 * The key here is to keep all elements unique. Then is has the same solution to CombinationSum.
 *
 * One way to solve it is to group.
 * ex> candidates: {1, 1, 1, 1, 3}   target = 3
 * We will see 4 1's as a group. Then there are two elements {1, 1, 1, 1} and 3.
 * 1st: {}(3) -> {}(3) | {1}(2) | {1, 1}(1) | {1, 1, 1}(0) | {1, 1, 1, 1}(-1)
 * 2nd: choose 3 or not.
 *
 * in other word, if 1 is seen in previous candidates, then it can only be chosen. That is
 * the first 1 can be chosen and not, but the following 1's must be chosen.
 */
vector< vector<int> > combinationSum2_sol2(vector<int>& candidates, int target) {
    vector< vector<int> > result;
    vector<int> selected;
    sort(candidates.begin(), candidates.end());

    // TODO: group, 1 <= candidates[i] <= 50
    vector<int> candidates_group(51, 0);
    for (int i = 0; i < candidates.size(); i++) {
        candidates_group[candidates[i]]++;
    }

    combinationSum2Helper2(candidates_group, selected, result, target, candidates[0]);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    EXPECT_EQUAL(combinationSum2(candidates, 8).size(), 4);

    vector<int> candidates2 = {2, 5, 2, 1, 2};
    EXPECT_EQUAL(combinationSum2(candidates2, 5).size(), 2);

    // time limited error: 2^100
//    vector<int> candidates3(100, 1);
//    EXPECT_EQUAL(combinationSum2(candidates3, 30).size(), 1);
}

PROVIDED_TEST("test for sol2:") {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    EXPECT_EQUAL(combinationSum2_sol2(candidates, 8).size(), 4);

    vector<int> candidates2 = {2, 5, 2, 1, 2};
    EXPECT_EQUAL(combinationSum2_sol2(candidates2, 5).size(), 2);

    // time limited error: 2^100
    vector<int> candidates3(100, 1);
    EXPECT_EQUAL(combinationSum2_sol2(candidates3, 30).size(), 1);
}
