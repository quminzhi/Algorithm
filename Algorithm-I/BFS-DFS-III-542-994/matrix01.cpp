#include "matrix01.h"
#include <queue>
#include "testing/SimpleTest.h"

int bfs0(const vector< vector<int> >& mat, int i, int j) {
    class QueueState {
    public:
        int row;
        int col;
        int dis;  // how long is mat[row][col] away from mat[i][j]
        QueueState(int i, int j, int dis) : row(i), col(j), dis(dis) {};
    };

    int distance = 0;
    queue<QueueState> que;
    que.push(QueueState(i, j, 0));
    while (!que.empty()) {
        QueueState cur = que.front();
        que.pop();
        if ((0 <= cur.row) && (cur.row < mat.size()) &&
            (0 <= cur.col) && (cur.col < mat[0].size())) {
            if (mat[cur.row][cur.col] == 0) {
                distance = cur.dis;
                break;
            }
            else {
                que.push(QueueState(cur.row + 1, cur.col, cur.dis + 1));
                que.push(QueueState(cur.row - 1, cur.col, cur.dis + 1));
                que.push(QueueState(cur.row, cur.col + 1, cur.dis + 1));
                que.push(QueueState(cur.row, cur.col - 1, cur.dis + 1));
            }
        }
    }

    return distance;
}

/*
 * Function: updateMatrix_sol1
 * ------------------------------------
 * The first thought is to traverse all cells in the matrix. On each cell, We will breath
 * first search the closest 0, calculate the distance and update.
 *
 * T: O(r*c*N)
 */
vector< vector<int> > updateMatrix_sol1(vector< vector<int> >& mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            if (mat[i][j] != 0) {
                mat[i][j] = bfs0(mat, i, j);
            }
        }
    }

    return mat;
}

/*
 * Function: updateMatrix_sol2
 * ------------------------------------
 * Where is the information? All 0s!
 * So we are able to use BFS, starting from all 0 cells, and try to update their neighbors.
 * ex> mat: 0  ?  ?
 *          0  0  ?
 *          ?  ?  ?
 * We will use greedy algorithm: if non-zero cells can be updated with a smaller number, then
 * update.
 *
 * 1. Enqueue all zero cells and initialize all non-zero cells to be INT_MAX
 * 2. Try to use the cell in the cell to update four-dimentional neighbors. If so, enqueue
 * the neighbor updated, since they are likely to update their neighbors.
 *
 * T: O(r*c), S: O(r*c)
 */
vector< vector<int> > updateMatrix_sol2(vector< vector<int> >& mat) {
    class QueueState {
    public:
        int i;
        int j;
        QueueState(int row, int col) : i(row), j(col) {};
    };
    queue<QueueState> que;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            if (mat[i][j] == 0) {
                que.push(QueueState(i, j));
            }
            else {
                mat[i][j] = INT_MAX;
            }
        }
    }

    int shorter = 0;
    while (!que.empty()) {
        QueueState cur = que.front();
        que.pop();
        // TODO: try to update my neighbors
        shorter = mat[cur.i][cur.j] + 1;
        if ((cur.i + 1 < mat.size()) && (shorter < mat[cur.i+1][cur.j])) {
            mat[cur.i+1][cur.j] = shorter;
            que.push(QueueState(cur.i+1, cur.j));
        }
        if ((cur.i - 1 >= 0) && (shorter < mat[cur.i-1][cur.j])) {
            mat[cur.i-1][cur.j] = shorter;
            que.push(QueueState(cur.i-1, cur.j));
        }
        if ((cur.j + 1 < mat[0].size()) && (shorter < mat[cur.i][cur.j+1])) {
            mat[cur.i][cur.j+1] = shorter;
            que.push(QueueState(cur.i, cur.j+1));
        }
        if ((cur.j - 1 >= 0) && (shorter < mat[cur.i][cur.j-1])) {
            mat[cur.i][cur.j-1] = shorter;
            que.push(QueueState(cur.i, cur.j-1));
        }
    }

    return mat;
}

/*
 * Function: updateMatrix_sol3
 * ------------------------------------
 * One important observation: the distance of a cell from 0 can be calculated if we
 * know the nearest distance for all the neighbors, in which case the distance is
 * minimum distance of any neightbor + 1. And, instantly, the words come to mind Dynamic
 * Programming (DP)!
 *
 * 1. Traverse from top to bottom and left to right, update (i, j) if they are only pass
 * left and top neighbors to get the shortest path to 0.
 * 2. Traverse from bottom to top and right to left, update (i, j) if they are only pass
 * right and bottom neighbors to get the shortest path to 0.
 *
 * 1 intersects 2, we got the closest path from (i, j) to 0. Since if mat[i][j] is not 0,
 * its nearest distance to 0 must be one of its neighbors + 1.
 *
 * Q: When in the first loop, what we can guaratee is all cells on the left and top of
 * current cell has the shortest path to 0 only if they can only reach 0 by left or top
 * neighbor. For example:
 * ex>  0  0  1  2
 *      1  1  ?  ?
 *      ?  ?  ?  ?
 * at (1, 2), we will update dist[1][2] by min(dist[1][2], dist[0][2]) and min(dist[1][2], dist[1][1]),
 * but at that time top cell (0, 2) and left cell (1, 1) only get shortest distance only if
 * they are allowed to pass left and top neighbors, which may not be the real shortest distance
 * of them?
 *
 * There is a very important property here, if they are updated by second loop, that is they
 * find a new shortest path from right or bottom neighbor, then (1, 2) must be updated before
 * (0, 2) and (1, 1), since (1, 2) is their right or bottom  neighbor.
 *
 * T: O(r*c), S: O(r*c)
 */
vector< vector<int> > updateMatrix_sol3(vector< vector<int> >& mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    if (rows == 0) return mat;
    int MAX_VAL = 10001;
    vector< vector<int> > dist(rows, vector<int>(cols, MAX_VAL));

    // TODO: check for left and top
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == 0) {
                dist[i][j] = 0;
            }
            else {
                if (i > 0) {
                    dist[i][j] = min(dist[i][j], dist[i-1][j] + 1);
                }
                if (j > 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j-1] + 1);
                }
            }
        }
    }

    // TODO: check for right and bottom
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 0; j--) {
            if (i + 1 < rows) {
                dist[i][j] = min(dist[i][j], dist[i+1][j] + 1);
            }
            if (j + 1 < cols) {
                dist[i][j] = min(dist[i][j], dist[i][j+1] + 1);
            }
        }
    }

    return dist;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for updateMatrix_sol1():") { // Time Limit Exceeded
    vector< vector<int> > mat = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 1},
    };
    vector< vector<int> > res = updateMatrix_sol1(mat);
    EXPECT_EQUAL(res[0][0], 0);
    EXPECT_EQUAL(res[0][1], 0);
    EXPECT_EQUAL(res[0][2], 0);
    EXPECT_EQUAL(res[1][0], 0);
    EXPECT_EQUAL(res[1][1], 1);
    EXPECT_EQUAL(res[1][2], 1);
    EXPECT_EQUAL(res[2][0], 1);
    EXPECT_EQUAL(res[2][1], 2);
    EXPECT_EQUAL(res[2][2], 2);
}

PROVIDED_TEST("Test for updateMatrix_sol2():") {
    vector< vector<int> > mat = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 1},
    };
    vector< vector<int> > res = updateMatrix_sol2(mat);
    EXPECT_EQUAL(res[0][0], 0);
    EXPECT_EQUAL(res[0][1], 0);
    EXPECT_EQUAL(res[0][2], 0);
    EXPECT_EQUAL(res[1][0], 0);
    EXPECT_EQUAL(res[1][1], 1);
    EXPECT_EQUAL(res[1][2], 1);
    EXPECT_EQUAL(res[2][0], 1);
    EXPECT_EQUAL(res[2][1], 2);
    EXPECT_EQUAL(res[2][2], 2);
}

PROVIDED_TEST("Test for updateMatrix_sol3():") {
    vector< vector<int> > mat = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 1},
    };
    vector< vector<int> > res = updateMatrix_sol3(mat);
    EXPECT_EQUAL(res[0][0], 0);
    EXPECT_EQUAL(res[0][1], 0);
    EXPECT_EQUAL(res[0][2], 0);
    EXPECT_EQUAL(res[1][0], 0);
    EXPECT_EQUAL(res[1][1], 1);
    EXPECT_EQUAL(res[1][2], 1);
    EXPECT_EQUAL(res[2][0], 1);
    EXPECT_EQUAL(res[2][1], 2);
    EXPECT_EQUAL(res[2][2], 2);
}
