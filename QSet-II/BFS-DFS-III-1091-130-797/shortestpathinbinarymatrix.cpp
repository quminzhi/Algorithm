#include "shortestpathinbinarymatrix.h"
#include "testing/SimpleTest.h"
#include <queue>
#include <iostream>

void shortestPathHelper(const vector< vector<int> >& grid,
                       vector< vector<bool> >& visited,
                       int x, int y, int curPath, int& shortestPath) {
    if ((x == grid.size() - 1) && (y == grid[0].size() - 1)) {
        if (curPath < shortestPath) {
            shortestPath = curPath;
        }
        return;
    }

    // recursion:
    // left-bottom
    if (((x + 1) < grid.size()) && ((y + 1) < grid[0].size())
        && (!visited[x+1][y+1])
        && (grid[x+1][y+1] == 0)) {
        // choose
        visited[x+1][y+1] = true;
        shortestPathHelper(grid, visited, x+1, y+1, curPath+1, shortestPath);
        // unchoose
        visited[x+1][y+1] = false;
    }

    // bottom
    if (((x + 1) < grid.size())
        && (!visited[x+1][y])
        && (grid[x+1][y] == 0)) {
        // choose
        visited[x+1][y] = true;
        shortestPathHelper(grid, visited, x+1, y, curPath+1, shortestPath);
        // unchoose
        visited[x+1][y] = false;
    }

    // right
    if (((y + 1) < grid[0].size())
        && (!visited[x][y+1])
        && (grid[x][y+1] == 0)) {
        // choose
        visited[x][y+1] = true;
        shortestPathHelper(grid, visited, x, y+1, curPath+1, shortestPath);
        visited[x][y+1] = false;
    }

    // right top
    if (((y + 1) < grid[0].size()) && (x > 0)
        && (!visited[x-1][y+1])
        && (grid[x-1][y+1] == 0)) {
        // choose
        visited[x-1][y+1] = true;
        shortestPathHelper(grid, visited, x-1, y+1, curPath+1, shortestPath);
        visited[x-1][y+1] = false;
    }

    // left bottom
    if ((y > 0) && ((x + 1) < grid.size())
        && (!visited[x+1][y-1])
        && (grid[x+1][y-1] == 0)) {
        // choose
        visited[x+1][y-1] = true;
        shortestPathHelper(grid, visited, x+1, y-1, curPath+1, shortestPath);
        visited[x+1][y-1] = false;
    }

    // left
    if ((y > 0)
        && (!visited[x][y-1])
        && (grid[x][y-1] == 0)) {
        // choose
        visited[x][y-1] = true;
        shortestPathHelper(grid, visited, x, y-1, curPath+1, shortestPath);
        visited[x][y-1] = false;
    }

    // top
    if ((x > 0)
        && (!visited[x-1][y])
        && (grid[x-1][y] == 0)) {
        // choose
        visited[x-1][y] = true;
        shortestPathHelper(grid, visited, x-1, y, curPath+1, shortestPath);
        visited[x-1][y] = false;
    }

    // left top
    if ((x > 0) && (y > 0)
        && (!visited[x-1][y-1])
        && (grid[x-1][y-1] == 0)) {
        // choose
        visited[x-1][y-1] = true;
        shortestPathHelper(grid, visited, x-1, y-1, curPath+1, shortestPath);
        visited[x-1][y-1] = false;
    }
}

/**
 * @brief shortestPathBinaryMatrix_sol1
 * @param grid
 * @return the shortest length of clear path if possible, -1 otherwise.
 * There are basically two ways to do it, BFS and DFS. BFS gives each decision
 * a chance fairly yet DFS will explore one possible solution chain recursively.
 *
 * For all decisions, the priority is listed from top to bottom:
 * - right bottom
 * - right/bottom
 * - right up/left bottom
 * - left/top
 * - left top
 *
 * The key here is to track visited points. Solution 1 will employ DFS.
 *
 * T: O(N^8)
 */
int shortestPathBinaryMatrix_sol1(vector< vector<int> >& grid) {
    if (grid.size() == 0) return -1;
    if (grid[0][0] == 1) return -1;
    vector< vector<bool> > visited(grid.size(),
                                   vector<bool>(grid[0].size(), false));
    int shortestPath = INT_MAX;
    visited[0][0] = true;
    shortestPathHelper(grid, visited, 0, 0, 1, shortestPath);

    return (shortestPath == INT_MAX) ? -1 : shortestPath;
}


/**
 * @brief shortestPathBinaryMatrix_sol2
 * @param grid
 * @return
 * The solution2 will use BFS to solve the problem with a 'visit' matrix to track
 * visited points.
 */
int shortestPathBinaryMatrix_sol2(vector< vector<int> >& grid) {
    if (grid.size() == 0) return -1;
    if (grid[0][0] == 1) return -1;

    class QueueNode {
    public:
        int x;
        int y;
        int cur_path;
        vector< vector<bool> > visited;

        QueueNode(int _x, int _y, int _cur_path, vector< vector<bool> > _visited)
                : x(_x), y(_y), cur_path(_cur_path), visited(_visited) {};
    };

    int NOT_FOUND = -1;
    vector< vector<bool> > visited(grid.size(),
                                   vector<bool>(grid[0].size(), false));
    visited[0][0] = true;
    queue<QueueNode> que;
    que.push(QueueNode(0, 0, 1, visited));
    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();
        int x = cur.x;
        int y = cur.y;

        // exit: must be shortest under BFS
        if ((x == (grid.size() - 1)) && (y == (grid[0].size() - 1))) {
            return cur.cur_path;
        }

        // left-bottom
        if (((x + 1) < grid.size()) && ((y + 1) < grid[0].size())
            && (!cur.visited[x+1][y+1])
            && (grid[x+1][y+1] == 0)) {
            cur.visited[x+1][y+1] = true;
            que.push(QueueNode(x+1, y+1, cur.cur_path+1, cur.visited));
            cur.visited[x+1][y+1] = false;
        }

        // bottom
        if (((x + 1) < grid.size())
            && (!cur.visited[x+1][y])
            && (grid[x+1][y] == 0)) {
            // choose
            cur.visited[x+1][y] = true;
            que.push(QueueNode(x+1, y, cur.cur_path+1, cur.visited));
            // unchoose
            cur.visited[x+1][y] = false;
        }

        // right
        if (((y + 1) < grid[0].size())
            && (!cur.visited[x][y+1])
            && (grid[x][y+1] == 0)) {
            // choose
            cur.visited[x][y+1] = true;
            que.push(QueueNode(x, y+1, cur.cur_path+1, cur.visited));
            cur.visited[x][y+1] = false;
        }

        // right top
        if (((y + 1) < grid[0].size()) && (x > 0)
            && (!cur.visited[x-1][y+1])
            && (grid[x-1][y+1] == 0)) {
            // choose
            cur.visited[x-1][y+1] = true;
            que.push(QueueNode(x-1, y+1, cur.cur_path+1, cur.visited));
            cur.visited[x-1][y+1] = false;
        }

        // left bottom
        if ((y > 0) && ((x + 1) < grid.size())
            && (!cur.visited[x+1][y-1])
            && (grid[x+1][y-1] == 0)) {
            // choose
            cur.visited[x+1][y-1] = true;
            que.push(QueueNode(x+1, y-1, cur.cur_path+1, cur.visited));
            cur.visited[x+1][y-1] = false;
        }

        // left
        if ((y > 0)
            && (!cur.visited[x][y-1])
            && (grid[x][y-1] == 0)) {
            // choose
            cur.visited[x][y-1] = true;
            que.push(QueueNode(x, y-1, cur.cur_path+1, cur.visited));
            cur.visited[x][y-1] = false;
        }

        // top
        if ((x > 0)
            && (!cur.visited[x-1][y])
            && (grid[x-1][y] == 0)) {
            // choose
            cur.visited[x-1][y] = true;
            que.push(QueueNode(x-1, y, cur.cur_path+1, cur.visited));
            cur.visited[x-1][y] = false;
        }

        // left top
        if ((x > 0) && (y > 0)
            && (!cur.visited[x-1][y-1])
            && (grid[x-1][y-1] == 0)) {
            // choose
            cur.visited[x-1][y-1] = true;
            que.push(QueueNode(x-1, y-1, cur.cur_path+1, cur.visited));
            cur.visited[x-1][y-1] = false;
        }
    }

    return NOT_FOUND;
}

/**
 * @brief shortestPathBinaryMatrix_sol3
 * @param grid
 * @return
 * A more elegant and clean code for sol2.
 *
 * The algorithm is use point whose shortest path is known to render its neighboring
 * points.
 */
int shortestPathBinaryMatrix_sol3(vector< vector<int> >& grid) {
    if (grid.size() == 0) return -1;
    if (grid[0][0] == 1) return -1;

    int target_x = grid.size() - 1;
    int target_y = grid[0].size() - 1;
    int x_direction[8] = {1, 0, 1, -1, 1, -1, 0, -1};
    int y_direction[8] = {1, 1, 0, 1, -1, 0, -1, -1};

    class Point {
    public:
        int x;
        int y;

        Point()
            : x(0), y(0) {};
        Point(int _x, int _y)
            : x(_x), y(_y) {};
    };

    vector< vector<int> > dist(grid.size(),
                               vector<int>(grid[0].size(), INT_MAX));
    dist[0][0] = 1;
    queue<Point> que;
    que.push(Point(0, 0));

    while (!que.empty()) {
        Point cur = que.front();
        que.pop();

        for (int i = 0; i < 8; i++) {
            int x = cur.x + x_direction[i];
            int y = cur.y + y_direction[i];
            if ((x >= 0) && (y >= 0)
                && (x < grid.size()) && (y < grid[0].size())
                && (grid[x][y] == 0)
                && (dist[x][y] == INT_MAX)) {
                dist[x][y] = dist[cur.x][cur.y] + 1;
                que.push(Point(x, y));
            }
        }
    }

    return (dist[target_x][target_y] == INT_MAX) ? -1 : dist[target_x][target_y];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector< vector<int> > grid1 = {
        {0},
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol1(grid1), 1);

    vector< vector<int> > grid2 = {
        {0, 1},
        {1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol1(grid2), 2);

    vector< vector<int> > grid3 = {
        {0, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol1(grid3), 4);

    vector< vector<int> > grid4 = {
        {1, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol1(grid4), -1);

    vector< vector<int> > grid5 = {
        {0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol1(grid5), 14);

    vector< vector<int> > grid6 = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol1(grid6), 4);
}

PROVIDED_TEST("test for sol2:") {
    vector< vector<int> > grid1 = {
        {0},
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol2(grid1), 1);

    vector< vector<int> > grid2 = {
        {0, 1},
        {1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol2(grid2), 2);

    vector< vector<int> > grid3 = {
        {0, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol2(grid3), 4);

    vector< vector<int> > grid4 = {
        {1, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol2(grid4), -1);

    vector< vector<int> > grid5 = {
        {0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol2(grid5), 14);

    vector< vector<int> > grid6 = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol2(grid6), 4);
}

PROVIDED_TEST("test for sol3:") {
    vector< vector<int> > grid1 = {
        {0},
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol3(grid1), 1);

    vector< vector<int> > grid2 = {
        {0, 1},
        {1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol3(grid2), 2);

    vector< vector<int> > grid3 = {
        {0, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol3(grid3), 4);

    vector< vector<int> > grid4 = {
        {1, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol3(grid4), -1);

    vector< vector<int> > grid5 = {
        {0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol3(grid5), 14);

    vector< vector<int> > grid6 = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    EXPECT_EQUAL(shortestPathBinaryMatrix_sol3(grid6), 4);
}

