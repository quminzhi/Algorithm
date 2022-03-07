#ifndef MATRIX01_H
#define MATRIX01_H

#include <vector>
using namespace std;

/**
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 *
 * The distance between two adjacent cells is 1 4-dimentionally.
 *
 * Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
 * Output: [[0,0,0],[0,1,0],[0,0,0]]
 *
 * m == mat.length
 * n == mat[i].length
 * 1 <= m, n <= 104
 * 1 <= m * n <= 104
 * mat[i][j] is either 0 or 1.
 * There is at least one 0 in mat.
 */
vector< vector<int> > updateMatrix_sol1(vector< vector<int> >& mat);

#endif // MATRIX01_H
