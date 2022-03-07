#include "rottingoranges.h"
#include <unordered_set>
#include <queue>
#include "testing/SimpleTest.h"

/*
 * Function: orangesRotting_sol1
 * ------------------------------------
 * We will store all fresh orange first, and put all rotted oranging in BFS queue.
 * Also we have to tag when rotted oranges are put into the queue.
 *
 * 1. How to store fresh orange? hashmap
 * 2. When to update minutes? after dequeuing all rotted oranges with the same timestamp
 *
 * T: O(N^2), S: O(M) where M is the length of queue.
 */
int orangesRotting_sol1(vector< vector<int> >& grid) {
    int minutes = -1;
    int rows = grid.size();
    if (rows == 0) return 0;
    int cols = grid[0].size();

    class Orange {
    public:
        int i;
        int j;
        int timestamp = 0; // when it is rotted
        Orange(int row, int col) : i(row), j(col) {};
        Orange(int row, int col, int t) : i(row), j(col), timestamp(t) {};
    };
    queue<Orange> que;
    int freshOranges = 0;

    // TODO: initialization
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                freshOranges++;
            }
            if (grid[i][j] == 2) {
                que.push(Orange(i, j));
            }
        }
    }

    // Corner cases:
    if (que.empty() && (freshOranges == 0)) return 0;
    if (freshOranges == 0) return 0;
    if (que.empty()) return -1;

    // TODO: bfs
    while (!que.empty()) {
        Orange cur = que.front();
        if (cur.timestamp != minutes) {
            minutes = cur.timestamp;
        }
        que.pop();
        // TODO: rotting adjacent fresh oranges
        if ((cur.i > 0) && (grid[cur.i-1][cur.j] == 1)) {
            que.push(Orange(cur.i-1, cur.j, minutes + 1));
            grid[cur.i-1][cur.j] = 2;
            freshOranges--;
        }
        if ((cur.j > 0) && (grid[cur.i][cur.j-1] == 1)) {
            que.push(Orange(cur.i, cur.j-1, minutes + 1));
            grid[cur.i][cur.j-1] = 2;
            freshOranges--;
        }
        if ((cur.i < rows - 1) && (grid[cur.i+1][cur.j] == 1)) {
            que.push(Orange(cur.i+1, cur.j, minutes + 1));
            grid[cur.i+1][cur.j] = 2;
            freshOranges--;
        }
        if ((cur.j < cols - 1) && (grid[cur.i][cur.j+1] == 1)) {
            que.push(Orange(cur.i, cur.j+1, minutes + 1));
            grid[cur.i][cur.j+1] = 2;
            freshOranges--;
        }
    }

    return (freshOranges == 0) ? minutes : -1;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for orangesRotting_sol1():") {
    vector< vector<int> > grid1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1},
    };
    EXPECT_EQUAL(orangesRotting_sol1(grid1), 4);

    vector< vector<int> > grid2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1},
    };
    EXPECT_EQUAL(orangesRotting_sol1(grid2), -1);

    vector< vector<int> > grid3 = {
        {0}
    };
    EXPECT_EQUAL(orangesRotting_sol1(grid3), 0);

    vector< vector<int> > grid4 = {
        {0, 2}
    };
    EXPECT_EQUAL(orangesRotting_sol1(grid4), 0);
}
