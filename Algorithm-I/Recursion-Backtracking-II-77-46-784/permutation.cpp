#include "permutation.h"
#include "testing/SimpleTest.h"


void permuteHelper(vector<int>& choices, vector<int>& selected,
                   vector< vector<int> >& result) {
    if (choices.empty()) {
        result.push_back(selected);
        return;
    }

    int selectedNum = 0;
    for (int i = 0; i < choices.size(); i++) {
        // choose
        selectedNum = choices[i];
        choices.erase(choices.begin() + i);
        selected.push_back(selectedNum);
        permuteHelper(choices, selected, result);
        // unchoose
        choices.insert(choices.begin() + i, selectedNum);
        selected.pop_back();
    }
}

/*
 * Function: permute
 * ------------------------------------
 * The function will return the permutation of given number set.
 */
vector< vector<int> > permute(vector<int>& nums) {
    vector< vector<int> > result;
    vector<int> selected;
    permuteHelper(nums, selected, result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for permute():") {
    vector<int> nums = {1, 2, 3, 4};
    vector< vector<int> > result = permute(nums);
    EXPECT_EQUAL(result[0][0], 1);
    EXPECT_EQUAL(result[0][1], 2);
    EXPECT_EQUAL(result[0][2], 3);
    EXPECT_EQUAL(result[0][3], 4);
    EXPECT_EQUAL(result[1][0], 1);
    EXPECT_EQUAL(result[1][1], 2);
    EXPECT_EQUAL(result[1][2], 4);
    EXPECT_EQUAL(result[1][3], 3);
    EXPECT(result.size() == 24);
}
