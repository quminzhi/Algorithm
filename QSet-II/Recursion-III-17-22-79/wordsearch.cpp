#include "wordsearch.h"
#include <testing/SimpleTest.h>

bool existHelper(vector< vector<char> >& board,
                 vector< vector<bool> >& visited,
                 string& word,
                 int x, int y,
                 int start) {
    static int dir_x[4] = {0, +1, 0, -1};
    static int dir_y[4] = {+1, 0, -1, 0};

    if (start >= word.size()) {
        return true;
    }

    if ((x < 0) || (x >= board.size()) || (y < 0) || (y >= board[0].size())) {
        // out of bounds
        return false;
    }
    if (word[start] != board[x][y]) {
        // not equal
        return false;
    }
    if (visited[x][y]) {
        // cannot be chosen twice
        return false;
    }

    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        // search on 4 directions
        int next_x = x + dir_x[i];
        int next_y = y + dir_y[i];
        if (existHelper(board, visited, word, next_x, next_y, start+1)) {
            return true;
        }
    }
    visited[x][y] = false;

    return false;
}

/**
 * @brief exist
 * @param board
 * @param word
 * @return
 * The solution to the problem is similar to maze with DFS.
 */
bool exist(vector< vector<char> >& board, string word) {
    int m = board.size();
    int n = board[0].size();
    if (word.size() == 0) return true;
    if (m == 0) return false;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0]) {
                // keep one cell chosen one time
                vector< vector<bool> > visited(m, vector<bool>(n, false));
                // seed cell is found
                if (existHelper(board, visited, word, i, j, 0)) {
                    return true;
                }
            }
        }
    }

    return false;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector< vector<char> > board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word = "ABCCED";
    EXPECT(exist(board, word));

    string word1 = "ABCB";
    EXPECT(!exist(board, word1));

    vector< vector<char> > board2 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'E', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word2 = "ABCEFSADEESE";
    EXPECT(exist(board2, word2));
}
