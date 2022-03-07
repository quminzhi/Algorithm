#include "combinationsum.h"
#include <iostream>
#include <set>
#include <string>
#include <testing/SimpleTest.h>

/**
 * @brief combinationSumHelper
 * @param candidates
 * @param selected
 * @param result
 * @param target
 * Base case:
 *  if target is equal to 0, then bingo.
 *  if there is no candidate and target is not 0, fail.
 * Recursion:
 *  reduce the problem.
 *
 * Remove duplications with set<string>, we will sort the result and compare.
 */
void combinationSumHelper(vector<int>& candidates,
                          vector<int>& selected,
                          set< vector<int> >& seen,
                          vector< vector<int> >& result,
                          int target) {
    if (target == 0) {
        // BUG: we cannot sort selected directly as it will affect pop_back() in higher
        // level.
        // ex> {3, 2, 2}, pop_back() will pop 2.
        //     {2, 2, 3}, pop_back() will pop 3. which causes conflicts.
        vector<int> sorted = selected;
        sort(sorted.begin(), sorted.end());
        if (seen.find(sorted) == seen.end()) {
            seen.insert(sorted);
            result.push_back(sorted);
        }
        return;
    }
    if ((candidates.size() == 0) || (target < 0)) {
        return;
    }

    for (int i = 0; i < candidates.size(); i++) {
        int cur = candidates[i];
        selected.push_back(cur);
        combinationSumHelper(candidates, selected, seen, result, target - cur);
        selected.pop_back();
    }
}

/**
 * @brief combinationSum_sol1
 * @param candidates
 * @param target
 * @return
 * Reduce the problem until the target is 0.
 * ex> input: {2, 3, 6, 7} target 7
 * reduce to: {2} + result of {2 ,3, 6, 7} target 5 (should be {2, 3} target 5, as
 * 6 and 7 are greater than 5)
 * ...
 * until target == 0.
 */
vector< vector<int> > combinationSum_sol1(vector<int>& candidates, int target) {
    vector< vector<int> > result;
    vector<int> selected;
    set< vector<int> > seen;

    combinationSumHelper(candidates, selected, seen, result, target);

    return result;
}

/**
 * @brief combinationSumHelper2
 * @param candidates
 * @param selected
 * @param result
 * @param target
 * @param start: start from ith candidates
 */
void combinationSumHelper2(vector<int>& candidates,
                          vector<int>& selected,
                          vector< vector<int> >& result,
                          int target, int start) {
    if (target == 0) {
        vector<int> sorted = selected;
        sort(sorted.begin(), sorted.end());
        result.push_back(sorted);
        return;
    }
    if ((candidates.size() == 0) || (target < 0)) {
        return;
    }

    for (int i = start; i < candidates.size(); i++) {
        int cur = candidates[i];
        selected.push_back(cur);
        combinationSumHelper2(candidates, selected,  result, target - cur, i);
        selected.pop_back();
    }
}

/**
 * @brief combinationSum_sol2
 * @param candidates
 * @param target
 * @return
 * Is there a better way to solve duplications? sorting and select in order.
 * ex> input {3, 4, 5}
 * in all solution starting with 3, it involves 4. So we don't have to consider 3 for
 * the solution starting with 4.
 */
vector< vector<int> > combinationSum_sol2(vector<int>& candidates, int target) {
    vector< vector<int> > result;
    vector<int> selected;

    combinationSumHelper2(candidates, selected, result, target, 0);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> candidates1 = {2, 3, 6, 7};
    int target1 = 7;
    EXPECT_EQUAL(combinationSum_sol1(candidates1, target1).size(), 2);

    vector<int> candidates2 = {2, 3, 5};
    int target2 = 8;
    EXPECT_EQUAL(combinationSum_sol1(candidates2, target2).size(), 3);
}

PROVIDED_TEST("test for sol2:") {
    vector<int> candidates1 = {2, 3, 6, 7};
    int target1 = 7;
    EXPECT_EQUAL(combinationSum_sol2(candidates1, target1).size(), 2);

    vector<int> candidates2 = {2, 3, 5};
    int target2 = 8;
    EXPECT_EQUAL(combinationSum_sol2(candidates2, target2).size(), 3);
}
