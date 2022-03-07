#include "search2dmatrix.h"
#include "testing/SimpleTest.h"

/**
 * @brief searchMatrix_sol1
 * @param matrix: a special matrix with elements in each row in ascending order
 * @param target: the number to be found
 * @return
 *
 * The first solution is concatenate a 1-D vector with elements in ascending order
 * and apply binary search to it.
 *
 * T: O(N + logN)
 */
bool searchMatrix_sol1(vector< vector<int> >& matrix, int target) {
    vector<int> vec;
    // TODO: concatenate
    for (int i = 0; i < matrix.size(); i++) {
        vec.insert(vec.end(), matrix[i].begin(), matrix[i].end());
    }

    // TODO: binary search
    int left = 0;
    int right = vec.size() - 1;
    int mid = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (vec[mid] == target) {
            return true;
        }
        else if (vec[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return false;
}

/**
 * A better way? Two cooperative binary search?
 * ex> {1, 3, 5, 7},     <--- top
 *     {10, 11, 16, 20},
 *     {23, 30, 34, 60}  <--- bottom
 *      ^           ^
 *     left        right
 *
 * binary search by row and then search by col.
 *
 * T: O(loglogN)
 */
bool searchMatrix_sol2(vector< vector<int> >& matrix, int target) {
    int top = 0;
    int bottom = matrix.size() - 1;
    int left = 0;
    int last = matrix[0].size() - 1;
    int right = last;
    int midRow = 0;
    int midCol = 0;
    while (top <= bottom) {
        midRow = top + ((bottom - top) >> 1);
        if (matrix[midRow][0] > target) {
            bottom = midRow - 1;
        }
        else if (matrix[midRow][last] < target) {
            top = midRow + 1;
        }
        else {
            // TODO: binary search in midRow
            while (left <= right) {
                midCol = left + ((right - left) >> 1);
                if (matrix[midRow][midCol] == target) {
                    return true;
                }
                else if (matrix[midRow][midCol] < target) {
                    left = midCol + 1;
                }
                else {
                    right = midCol - 1;
                }
            }
            return false;
        }
    }
    return false;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    vector< vector<int> > matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    EXPECT_EQUAL(searchMatrix_sol1(matrix, 3), true);
    EXPECT_EQUAL(searchMatrix_sol1(matrix, 0), false);
}

PROVIDED_TEST("Test for sol2:") {
    vector< vector<int> > matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    EXPECT_EQUAL(searchMatrix_sol2(matrix, 3), true);
    EXPECT_EQUAL(searchMatrix_sol2(matrix, 0), false);
    EXPECT_EQUAL(searchMatrix_sol2(matrix, 13), false);
}
