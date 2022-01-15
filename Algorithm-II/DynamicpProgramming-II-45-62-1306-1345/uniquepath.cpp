#include "uniquepath.h"
#include <testing/SimpleTest.h>

/**
 * @brief uniquePaths
 * @param m
 * @param n
 * @return
 * Solution 1 is to solve from easy case to complex one.
 *
 * ex> m = 2, n = 3
 *
 * define unique_path[m][n] as the number of unique path to (m-1, n-1).
 * unique[0][0] = 0 ==> unique[m-1][n-1]?
 *
 * unique[i][j] = unique[i-1][j] (up) + unique[i][j-1] (left);
 *
 * T: O(M * N)
 */
int uniquePaths(int m, int n) {
    if ((m == 0) || (n == 0)) return 0;
    vector< vector<int> > unique_path(m, vector<int>(n, 0));
    for (int row = 0; row < m; row++) {
        unique_path[row][0] = 1;
    }
    for (int col = 0; col < n; col++) {
        unique_path[0][col] = 1;
    }

    for (int row = 1; row < m; row++) {
        for (int col = 1; col < n; col++) {
            if ((row - 1) >= 0) {
                unique_path[row][col] += unique_path[row-1][col];
            }
            if ((col - 1) >= 0) {
                unique_path[row][col] += unique_path[row][col-1];
            }
        }
    }

    return unique_path[m-1][n-1];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    EXPECT_EQUAL(uniquePaths(3, 7), 28);
    EXPECT_EQUAL(uniquePaths(3, 2), 3);
}
