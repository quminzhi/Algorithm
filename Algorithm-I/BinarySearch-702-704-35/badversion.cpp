#include "badversion.h"
#include "testing/SimpleTest.h"

/*
 * Function: fristBadVersion
 * ------------------------------------
 * The function will return the first bad version that causing all following version to be bad.
 * Notice that all bad version should be consecutive.
 *
 * We are gonna use binary search to find the first bad version.
 * 1. if the pivot is bad
 *      > search in left half using binary search, since all versions on the right half must be bad.
 *    else
 *      > the first bad version must lie in the right half.
 */
int firstBadVersion(const vector<char>& versions, int n) {
    int left = 0;
    int right = n - 1;

    while (left < right) {
        int pivot = left + (right - left) / 2;
        if (isBadVersion(versions, pivot)) {
            right = pivot;
        }
        else {
            left = pivot + 1;
        }
    }

    return (versions[left] == 'B') ? left + 1 : -1;
}

bool isBadVersion(const vector<char>& versions, int n) {
    return (versions[n] == 'B');
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for firstBadVersion():") {
    vector<char> versions = {'G', 'G', 'G', 'B', 'B', 'B'};
    EXPECT_EQUAL(firstBadVersion(versions, versions.size()), 4);
}

PROVIDED_TEST("Test for polarized conditions:") {
    vector<char> versions1 = {'G', 'G', 'G', 'G'};
    EXPECT_EQUAL(firstBadVersion(versions1, versions1.size()), -1);

    vector<char> versions2 = {'B', 'B', 'B', 'B'};
    EXPECT_EQUAL(firstBadVersion(versions2, versions2.size()), 1);
}
