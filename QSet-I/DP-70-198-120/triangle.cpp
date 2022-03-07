#include "triangle.h"
#include "GUI/SimpleTest.h"

/*
 * Function: minimumTotal
 * ------------------------------------
 * Again, the best way to solve decision problem, if possible, is dynamic programming.
 *
 * minPath(cur) = min {
 *      minPath(cur->left) + pathFrom(cur->left),
 *      minPath(cur->right) + pathFrom(cur->right)
 * }
 *
 * triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
 *                                ^ ^ ^ ^
 *                                  Base
 *
 * Base case:
 * if cur is the start point, then minPath(cur) = 0
 */
int minimumTotal(vector< vector<int> >& triangle) {
    if (triangle.size() == 0) return 0;

    vector< vector<int> > val = triangle;

    // TODO: initialize base case
    int bottom = triangle.size() - 1;
    for (int i = 0; i < triangle[bottom].size(); i++) {
        triangle[bottom][i] = 0;
    }

    // TODO: rendering from bottom to top
    for (int row = triangle.size() - 2; row >= 0; row--) {
        for (int col = 0; col < triangle[row].size(); col++) {
            int leftPath = triangle[row+1][col] + val[row+1][col];
            int rightPath = triangle[row+1][col+1] + val[row+1][col+1];
            triangle[row][col] = min(leftPath, rightPath);
        }
    }

    return triangle[0][0] + val[0][0];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for minimumTotal():") {
    vector< vector<int> > tri1 = {{2}, {3,4}, {6,5,7}, {4,1,8,3}};
    EXPECT_EQUAL(minimumTotal(tri1), 11);
}
