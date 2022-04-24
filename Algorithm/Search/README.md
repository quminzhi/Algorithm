# Search

## Depth First Search

### N Queens

> The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
>
> Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
>
> Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

One trick in N-Queens is the representation of diagonal line and anti-diagonal line. One fact is that diagonal line is indexed by y-distance of a x-y plane.

```text
    0  1  2  3  4
 0  a
 1   b c 
 2      d e
 3         f g
 4            h i
```

For an anti-diagonal line `y = -x + b`, we got `b = x + y`. So, `Grid[i][j]` is in `AntiDiag[i + j]`. For a diagonal line `y = x + b`, we got `b = -x + y`, but `b` should be non-negative. `b = -x + y + max(N, M)` for any rectangular (`b = -x + y + N or M` for a square), where `N` represents column, and `M` row.

We use `col[]`, `row[]`, `diag[]`, `anti_diag[]` to record if there is a queen on that line.

```c++
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
```

## Breadth First Search

### Find Min Path

> Find a min path from (0, 0) to the right bottom point.

This is a classic BFS problem and there is a lot of details to take into consideration.

```c++
/**
 * @brief bfs
 *
 * @param matrix
 * @return int: the length of min path from (0, 0) to the exit point (right bottom point).
 */
int minPathInMatrix(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    Point final(m - 1, n - 1);
    vector<vector<int>> dis(m, vector<int>(n, 1e6));   // min distance from (i, j) to (0, 0)
    dis[0][0] = 0;
    vector<vector<bool>> visited(m, vector<bool>(n, false));         // avoid repeated visit
    vector<vector<Point>> pre(m, vector<Point>(n, Point(-1, -1)));   // record the previous step of each point
    vector<Point> path;
    queue<Point> que;
    que.push(Point(0, 0));
    visited[0][0] = true;
    int dx[4] = {-1, +1, 0, 0};
    int dy[4] = {0, 0, -1, +1};
    while (!que.empty()) {
        Point cur = que.front();
        que.pop();

        if (cur.x == final.x && cur.y == final.y) {
            // back track
            while (cur.x || cur.y) {   // break when both x and y are 0
                path.push_back(cur);
                Point t = pre[cur.x][cur.y];
                cur.x = t.x, cur.y = t.y;
            }
            path.push_back(Point(0, 0));
            break;
        }

        // try
        for (int i = 0; i < 4; i++) {
            int x = cur.x + dx[i];
            int y = cur.y + dy[i];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] == 0 && !visited[x][y]) {
                dis[x][y] = dis[cur.x][cur.y] + 1;
                que.push(Point(x, y));
                visited[x][y] = true;
                pre[x][y] = Point(cur.x, cur.y);
            }
        }
    }

    // print path in reverse order
    for (int i = 0; i < path.size(); i++) {
        cout << "(" << path[i].x << ", " << path[i].y << ")" << endl;
    }
    cout << endl;

    return dis[m - 1][n - 1];   // or path.size() - 1 (minus (0, 0))
}
```

Tricks:

- record path by making a stamp on each point to indicate its previous point.
- direction vector.
