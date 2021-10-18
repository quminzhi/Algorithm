#include "unknownbinarysearch.h"
#include <stdlib.h>
#include "testing/SimpleTest.h"

/* -------------------------------
 *        Idea Description
 * -------------------------------
 * The basic idea is to transform questions with unknown solutions to those with known solutions.
 * 1. The crux of the problem is to define search limits or boundary.
 * 2. If we know the boundary, then it can be solved with binary search.
 *
 * About how to define search limits. There are two perspective.
 * 1. Start from INT_MAX, and try to find possible middle point. Then the left half will be a binary search with defined limits,
 * and right half is unknown one, which could be solved recursively. (Solution1)
 * 2. Start from minimum possible range, and extend limits so that the target is included in the give range. If the right range
 * is greater than target, which means target is not in secret array. (Solution2)
 *
 * More aggressively, given the restrictions that the maximum range is 0 < length < 10^4.
 * We are able to binary search on 10^4 virtual array (Solution3). The time complexity is O(N);
 */

/*
 * Function: knownSearchHelper
 * ------------------------------------
 * The function will search target value in the given secret array. 'Known' here means we know the left and right
 * boundary of searching range.
 *
 * @param reader: the only access to secret array.
 * @param left: leftmost index of array.
 * @param right: rightmost index of array.
 * @param target: the target value to be searched.
 *
 * This is a classic binary search.
 */
int knownSearchHelper(const ArrayReader& reader, int left, int right, int target) {
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;
    if (reader.get(mid) == target) {
        return mid;
    }
    else {
        if (reader.get(mid) > target) {
            return knownSearchHelper(reader, left, mid-1, target);
        }
        else {
            return knownSearchHelper(reader, mid+1, right, target);
        }
    }
}


/*
 * Function: unknownSearchHelper
 * ------------------------------------
 * The function will find the index of target in the given array. If not found, return -1.
 * 'Unknown' here means I don't know the right boundary of the array.
 *
 * @param reader: the only access to secret array.
 * @param left: leftmost index of array if left is within legal range of array.
 * @param target: the target value.
 *
 * We will solve it recursively.
 * Base case:
 *      if left is not in the legal range of array, which means there is no number left in right half of array.
 *      then return -1.
 * Recursion:
 *      1. try to find a possible middle point of array.
 *      2. if target is equal to middle value, return the index of middle point.
 *         else > if target is smaller than middle value, search in left half with knownSearchHelper.
 *              > else search in right half with unknownSearchHelper.
 */
int unknownSearchHelper(const ArrayReader& reader, int left, int target) {
    if (reader.get(left) == INT_MAX) {
        return -1;
    }

    int index = rand() % 10000;
    while (reader.get(index) == INT_MAX) {
        index /= 2;
    }
    if (reader.get(index) == target) {
        return index;
    }
    else {
        if (reader.get(index) > target) {
            return knownSearchHelper(reader, 0, index-1, target);
        }
        else {
            return unknownSearchHelper(reader, index+1, target);
        }
    }
}

int search_sol1(const ArrayReader& reader, int target) {
    return unknownSearchHelper(reader, 0, target);
}

/*
 * Function: search_sol2
 * ------------------------------------
 * There are two things to do here:
 * 1. Define search limits.
 *      a. start with a minimum range.
 *      b. if target is within the range, the range is defined.
 *         else, extend range until the right is not in the maximum limit of secret array which is 10^4.
 * 2. Binary search.
 */
int search_sol2(const ArrayReader& reader, int target) {
    if (reader.get(0) == target) {
        return 0;
    }

    int left = 0; int right = 1;
    while (target > reader.get(right)) {
        left = right;
        right <<= 2;
    }

    // binary search
    int num, mid;
    while (left < right) {
        mid = left + (right - left) / 2;
        num = reader.get(mid);
        if (num == target) {
            return mid;
        }
        else {
            if (num > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
    }

    return -1;
}


int search_sol3(const ArrayReader& reader, int target) {
    int left = 0;
    int right = 39999; // 10^4 - 1

    int num, mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        num = reader.get(mid);
        if (num == target) {
            return mid;
        }
        else {
            if (num > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
    }

    return -1;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */

PROVIDED_TEST("Test for ArrayReader:") {
    vector<int> myth = {-1, 0, 3, 5, 9, 12};
    ArrayReader reader(myth);
    EXPECT_EQUAL(reader.get(0), -1);
    EXPECT_EQUAL(reader.get(5), 12);
    EXPECT_EQUAL(reader.get(6), INT_MAX);
}

PROVIDED_TEST("Test for search_sol1():") {
    vector<int> myth = {-1, 0, 3, 5, 9, 12};
    ArrayReader reader(myth);
    EXPECT_EQUAL(search_sol1(reader, 3), 2);
    EXPECT_EQUAL(search_sol1(reader, 5), 3);
    EXPECT_EQUAL(search_sol1(reader, 10), -1);
    EXPECT_EQUAL(search_sol1(reader, 4), -1);
}

PROVIDED_TEST("Test for search_sol2():") {
    vector<int> myth = {-1, 0, 3, 5, 9, 12};
    ArrayReader reader(myth);
    EXPECT_EQUAL(search_sol2(reader, 3), 2);
    EXPECT_EQUAL(search_sol2(reader, 5), 3);
    EXPECT_EQUAL(search_sol2(reader, 10), -1);
    EXPECT_EQUAL(search_sol2(reader, 4), -1);
}

PROVIDED_TEST("Test for search_sol3():") {
    vector<int> myth = {-1, 0, 3, 5, 9, 12};
    ArrayReader reader(myth);

    EXPECT_EQUAL(search_sol3(reader, 3), 2);
    EXPECT_EQUAL(search_sol3(reader, 5), 3);
    EXPECT_EQUAL(search_sol3(reader, 10), -1);
    EXPECT_EQUAL(search_sol3(reader, 4), -1);
}
