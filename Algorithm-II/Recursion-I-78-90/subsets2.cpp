#include "subsets2.h"
#include <set>
#include <testing/SimpleTest.h>

/**
 * @brief subsetsWithDup
 * @param nums
 * @return
 * One way to generate all subsets is construction.
 *
 * ex> input: {0, 1, 2}
 * - start from {}
 * - 1st (add 0): ({}) + {0}
 * - 2nd (add 1): ({}, {0}) + {1}, {0, 1}
 * - 3rd (add 2): ({}, {0}, {1}, {0, 1}) + {2}, {0, 2}, {1, 2}, {0, 1, 2}
 * - so we get all subsets {}, {0}, {1}, {0, 1}, {2}, {0, 2}, {1, 2}, {0, 1, 2}
 *
 * How to solve duplicates? Refine construction process (input nums must be ordered).
 *
 * ex> input: {0, 2, 1, 2, 2, 3} -> ordered {0, 1, 2, 2, 2, 3}
 * - start from {}
 * - 1st (add 0): ({}) + {0}
 * - 2nd (add 1): ({}, {0}) + {1}, {0, 1}
 * - 3rd (add 2): ({}, {0}, {1}, {0, 1}) + {2}, {0, 2}, {1, 2}, {0, 1, 2}
 * - 4th (add 2): when add duplicated number, we just need add to subsets generated
 * by previous step.
 * ({}, {0}, {1}, {0, 1}, {2}, {0, 2}, {1, 2}, {0, 1, 2}) + {2, 2}, {0, 2, 2}, {1, 2, 2}, {0, 1, 2, 2}
 *                         |-------- previous --------|
 * - 5th (add 2): ...
 *
 * So we need to track the starting index of subsets generated in previous step.
 */
vector< vector<int> > subsetsWithDup(vector<int>& nums) {
    set<int> seen;
    vector< vector<int> > result;
    result.push_back({});
    int start = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        if (seen.find(nums[i]) != seen.end()) {
            // has been seen, add to previous subsets
            vector< vector<int> > add;
            for (int j = start; j < result.size(); j++) {
                vector<int> subset = result[j];
                subset.push_back(nums[i]);
                add.push_back(subset);
            }
            start = result.size();
            // concatenate new subsets
            result.insert(result.end(), add.begin(), add.end());
        }
        else {
            // not seen, add to all subsets
            seen.insert(nums[i]);
            vector< vector<int> > add;
            for (int j = 0; j < result.size(); j++) {
                vector<int> subset = result[j];
                subset.push_back(nums[i]);
                add.push_back(subset);
            }
            start = result.size();
            // concatenate new subsets
            result.insert(result.end(), add.begin(), add.end());
        }
    }

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> nums = {1, 2, 2};
    EXPECT_EQUAL(subsetsWithDup(nums).size(), 6);
}
