#include "search.hpp"

void NQueensHelper(vector<vector<string>>& res, vector<string>& attempt, vector<bool>& row, vector<bool>& col, vector<bool>& diag,
                   vector<bool>& anti_diag, int n, int i) {
    if (i == n) {
        res.push_back(attempt);
        return;
    }

    // try
    for (int j = 0; j < n; j++) {
        if (!row[i] && !col[j] && !diag[-i + j + n] && !anti_diag[i + j]) {
            // choose
            attempt[i][j] = 'Q';
            row[i] = col[j] = diag[-i + j + n] = anti_diag[i + j] = true;
            // try next
            NQueensHelper(res, attempt, row, col, diag, anti_diag, n, i + 1);
            // un-choose
            attempt[i][j] = '.';
            row[i] = col[j] = diag[-i + j + n] = anti_diag[i + j] = false;
        }
    }
    // no choice available
    return;
}

/**
 * @brief How to check if a place is valid to put a queen.
 * 
 * res[i][j]: means jth row of ith solution, which is a string, ex> '..Q.'.
 * 
 * @param n
 * @return vector<vector<string>>
 */
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> attempt(n, string(n, '.'));
    vector<bool> row(n, false);
    vector<bool> col(n, false);
    vector<bool> diag(n + n - 1, false);
    vector<bool> anti_diag(n + n - 1, false);

    NQueensHelper(res, attempt, row, col, diag, anti_diag, n, 0);

    return res;
}