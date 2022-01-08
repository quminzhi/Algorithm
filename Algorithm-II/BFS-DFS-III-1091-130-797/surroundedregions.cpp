#include "surroundedregions.h"
#include <queue>
#include "testing/SimpleTest.h"

/**
 * @brief solve_sol1
 * @param board
 * Captured areas are those not containing points on the border of board.
 */
void solve_sol1(vector< vector<char> >& board) {
    if (board.size() == 0) return;
    vector< vector<bool> > visited(board.size(),
                                   vector<bool>(board[0].size(), false));
    class Point {
    public:
        int x;
        int y;
        Point(int _x, int _y)
            : x(_x), y(_y) {};
    };

    int dir_x[4] = {-1, +1, 0, 0};
    int dir_y[4] = {0, 0, -1, +1};

    queue<Point> que;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if ((board[i][j] == 'O') && (!visited[i][j])) {
                visited[i][j] = true;

                // store possible capture area
                vector<Point> buf;
                bool captured = true;
                // if point is on the border
                if (i == 0 || i == (board.size() - 1) || j == 0 || j == (board[0].size() - 1)) {
                    captured = false;
                }
                que.push(Point(i, j));
                buf.push_back(Point(i, j));
                while (!que.empty()) {
                    Point cur = que.front();
                    que.pop();
                    for (int index = 0; index < 4; index++) {
                        int x = cur.x + dir_x[index];
                        int y = cur.y + dir_y[index];
                        if ((x >= 0) && (y >= 0) && (x < board.size()) && (y < board[0].size())
                            && (board[x][y] == 'O')
                            && (!visited[x][y])) {
                            visited[x][y] = true;
                            que.push(Point(x, y));
                            buf.push_back(Point(x, y));
                            if (x == 0 || x == (board.size() - 1) || y == 0 || y == (board[0].size() - 1)) {
                                captured = false;
                            }
                        }
                    }
                }

                if (captured) {
                    for (Point pt : buf) {
                        board[pt.x][pt.y] = 'X';
                    }
                }
            }
        }
    }
}

class Point {
public:
    int x;
    int y;
    Point(int _x, int _y)
        : x(_x), y(_y) {};
};

void traverseHelper(vector< vector<char> >& board,
                    vector< vector<bool> >& visited,
                    vector<Point>& buf,
                    int ox, int oy) {
    int dir_x[4] = {-1, +1, 0, 0};
    int dir_y[4] = {0, 0, -1, +1};

    visited[ox][oy] = true;

    queue<Point> que;
    que.push(Point(ox, oy));
    buf.push_back(Point(ox, oy));
    while (!que.empty()) {
        Point cur = que.front();
        que.pop();
        for (int index = 0; index < 4; index++) {
            int x = cur.x + dir_x[index];
            int y = cur.y + dir_y[index];
            if ((x >= 0) && (y >= 0) && (x < board.size()) && (y < board[0].size())
                && (board[x][y] == 'O')
                && (!visited[x][y])) {
                visited[x][y] = true;
                que.push(Point(x, y));
                buf.push_back(Point(x, y));
            }
        }
    }
}

/**
 * @brief solve_sol2
 * @param board
 * On the contrary to sol1, we will concentrate on cells remain to be 'O', meaning
 * will not be captured. Those cells are connected to the cells on the border.
 *
 * So what we need to do is find all islands connected to the border.
 * - starting from all border cells and BFS
 */
void solve_sol2(vector< vector<char> >& board) {
    if (board.size() == 0) return;
    vector< vector<bool> > visited(board.size(),
                                   vector<bool>(board[0].size(), false));

    // keep track all cells on islands connected with borders.
    vector<Point> buff;
    // left and right border
    for (int i = 0; i < board.size(); i++) {
        if ((board[i][0] == 'O') && (!visited[i][0])) {
            traverseHelper(board, visited, buff, i, 0);
        }
        if ((board[i][board[0].size()-1] == 'O') && (!visited[i][board[0].size()-1])) {
            traverseHelper(board, visited, buff, i, board[0].size()-1);
        }
    }
    // top and bottom border
    for (int j = 0; j < board[0].size(); j++) {
        if ((board[0][j] == 'O') && (!visited[0][j])) {
            traverseHelper(board, visited, buff, 0, j);
        }
        if ((board[board.size()-1][j] == 'O') && (!visited[board.size()-1][j])) {
            traverseHelper(board, visited, buff, 0, board.size()-1);
        }
    }

    // re-render board
    for (int i = 0; i < board.size() - 1; i++) {
        for (int j = 0; j < board[0].size() - 1; j++) {
            board[i][j] = 'X';
        }
    }
    for (Point pt : buff) {
        board[pt.x][pt.y] = 'O';
    }
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector< vector<char> > board = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };

    solve_sol1(board);

//    output = {
//        {'X', 'X', 'X', 'X'},
//        {'X', 'X', 'X', 'X'},
//        {'X', 'X', 'X', 'X'},
//        {'X', 'O', 'X', 'X'}
//    }
}
