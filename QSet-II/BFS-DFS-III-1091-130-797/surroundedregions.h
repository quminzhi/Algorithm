#ifndef SURROUNDEDREGIONS_H
#define SURROUNDEDREGIONS_H

#include <vector>
using namespace std;

/**
 * Given an m x n matrix board containing 'X' and 'O', capture all regions that
 * are 4-directionally surrounded by 'X'.
 *
 * A region is captured by flipping all 'O's into 'X's in that surrounded region.
 *
 * Input: board = [["X","X","X","X"],
 *                 ["X","O","O","X"],
 *                 ["X","X","O","X"],
 *                 ["X","O","X","X"]]
 *
 * Output: [["X","X","X","X"],
 *          ["X","X","X","X"],
 *          ["X","X","X","X"],
 *          ["X","O","X","X"]]
 *
 * Constrains:
 * m == board.length
 * n == board[i].length
 * 1 <= m, n <= 200
 * board[i][j] is 'X' or 'O'.
 */
void solve(vector< vector<char> >& board);

#endif // SURROUNDEDREGIONS_H
