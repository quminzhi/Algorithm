#include "threesum.h"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <stdlib.h>
#include "testing/SimpleTest.h"

/**
 * @brief twoSum_hash
 * @param nums: a given array.
 * @return all possible number pairs whose sum is equal to target
 * Our method is to build a hashtable to record match number, and then we just only
 * look through if the match number is in the array.
 * ex>  nums = {1, 3, 4, 7, 1, 0}  target = 4
 * hashtable = {(3: 1), (1: 3), (0: 4), (-3: 7), (4: 0)}
 * (matching number for target given number: number)
 *
 * To solve the problem of repetition in hashtable, like (3: 1) and (1: 3), we
 * could use a set to field it.
 *
 * T: O(N), S: O(N)
 */
vector< vector<int> > twoSum_hash(vector<int>& nums, int target) {
    vector< vector<int> > result;
    unordered_map<int, int> match;
    unordered_set<int> solved;
    for (int num : nums) {
        if (solved.find(num) == solved.end()) {
            match[target - num] = num;
            solved.insert(num);
            solved.insert(target - num);
        }
    }

    for (int num : nums) {
        // TODO: if i'm the number needed to match
        if (match.find(num) != match.end()) {
            result.push_back({target - num, num});
//            cout << "{" << target - num << ", " << num << "}" << endl;
        }
    }

    return result;
}

/**
 * @brief threeSum_sol1
 * @param nums: contains n numbers.
 * @return All three triplets such that sum of each of them is ZERO.
 * Remember that we solve 'Two Sum' problems, which requires to return two indexes
 * in an array whose sum is equal to target number, and there is only one solution.
 * So, can we solve 'Three Sum' problem resorting to the method in solving 'Two
 * Sum' problem.
 *
 * Seems feasible. We just need traverse nums and find two sum with target number
 * -nums[i]. Notice here 'two sum' problem may have more than one solution.
 *
 * How to solve duplication? Hashset!
 *
 * If we find a solution, we will put all combination of the solution into hashset.
 */
vector< vector<int> > threeSum_sol1(vector<int>& nums) {
    vector< vector<int> > result;
    vector< vector<int> > twoSumResult;
    for (int i = 0; i < nums.size(); i++) {
        // TODO: remove the number being processed from nums
        int processed = nums[i];
        nums.erase(nums.begin() + i);
        twoSumResult = twoSum_hash(nums, -processed);
        for (vector<int>& result : twoSumResult) {
            result.push_back(processed);
        }
        result.insert(result.end(), twoSumResult.begin(), twoSumResult.end());
        // TODO: move the number back to original location
        nums.insert(nums.begin() + i, processed);
    }

    return result;
}

// C style
int myCompare_C(const void* lhs, const void* rhs) {
    return (*(int*)lhs - *(int*)rhs);
    /**
     * // Descending order: same to following if clauses
     * if (*(int*)lhs > *(int*)rhs) return 1;
     * if (*(int*)lhs == *(int*)rhs) return 0;
     * if (*(int*)lhs < *(int*)lhs) return -1;
     */
}

// C++ style
bool myCompare(int lhs, int rhs) {
    return (lhs > rhs);
}

/**
 * @brief twoSum_pointers
 * @param nums: a given array
 * @param targetIndex: target number = -nums[targetIndex]
 * @return all possible pairs whose sum is equal to target
 */
vector< vector<int> > twoSum_pointers(vector<int>& nums, int targetIndex) {
    vector< vector<int> > result;
    int left = targetIndex + 1;
    int right = nums.size() - 1;
    int target = -nums[targetIndex];
    while (left < right) {
        if (nums[left] + nums[right] > target) {
            right--;
        }
        else if (nums[left] + nums[right] < target) {
            left++;
        }
        else {
            // TODO: find one solution
            result.push_back({-target, nums[left], nums[right]});
            right--;
            // avoid duplicate: move left to next different val
            int next = left + 1;
            while ((next < right) && (nums[next] == nums[left])) {
                next++;
            }
            left = next;
        }
    }

    return result;
}

/**
 * It is hard to remove duplicate triplets in solution 1. Can we have a better solution
 * with best conceivable runtime? Remember how to solve twoSum with two pointer for an sorted array?
 *
 * ex> {0, 1, 2, 5, 8}  target = 10
 *      ^           ^
 *     left        right
 *     (min)       (max)
 *
 * // If i(left) plus the maximum number is still less than target, then i'm out.
 * If (nums[left] + nums[right] < target), then left++;
 * // If i(right) plus the minimum number is still larger than target, then i'm out.
 * If (nums[left] + nums[right] > target), then right--;
 *
 * Two Sum uses a hashmap to find complement values, and therefore achieves O(N) time complexity.
 * Two Sum II uses the two pointers pattern and also has O(N) time complexity for a sorted array.
 * We can use this approach for any array if we sort it first, which bumps the time complexity to
 * O(NlogN). it sounds reasonable to shoot for O(N^2) time complexity as our BCR.
 *
 * Now let's try to solve 'three sum' problem based on 'two sum' using two pointers method.
 *
 * Algorithm:
 * 1. Sorting in non-descending order.
 * 2. Iterate through the array:
 *  - If the current value is greater than zero, break as the sum of positive numbers cannot
 *  be zero.
 *  - If the current value is same as before, skip it.
 *  - Otherwise, call twoSum.
 *
 * twoSum:
 * // why left = i + 1? since the number before i has been processed, avoiding duplicates.
 * 1. left = i + 1 and right = the last index
 * 2. while (left < right) {
 *        // find possible result and avoid duplicates
 *    }
 */
vector< vector<int> > threeSum_sol2(vector<int>& nums) {
    unordered_set<int> seen;
    vector< vector<int> > result;
    vector< vector<int> > subResult;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0) break;
        if (seen.find(nums[i]) != seen.end()) continue;
        seen.insert(nums[i]);
        subResult = twoSum_pointers(nums, i);
        result.insert(result.end(), subResult.begin(), subResult.end());
    }

    return result;
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector< vector<int> > result = threeSum_sol1(nums);
    // It turns out that there are nine possible triplets here, as there are a lot
    // of duplicate triplets, which is hard to solve. So such method seems not working.
    EXPECT_EQUAL(result.size(), 9);
}

PROVIDED_TEST("Test for sol2:") {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector< vector<int> > result = threeSum_sol2(nums);
    EXPECT_EQUAL(result.size(), 2);
}
