#ifndef SEARCH2DMATRIX_H
#define SEARCH2DMATRIX_H

#include <vector>
using namespace std;

/**
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 *  - Integers in each row are sorted from left to right.
 *  - The first integer of each row is greater than the last integer of the
 *    previous row.
 *
 * Input: matrix = [[1,3,5,7],
 *                  [10,11,16,20],
 *                  [23,30,34,60]], target = 3
 * Output: true
 *
 * Constrains:
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 100
 * -104 <= matrix[i][j], target <= 104
 */

bool searchMatrix(vector< vector<int> >& matrix, int target);

#endif // SEARCH2DMATRIX_H
