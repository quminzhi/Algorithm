#include "floodfill.h"
#include "testing/SimpleTest.h"
#include <queue>

/*
 * Function: floodFill_sol1
 * ------------------------------------
 * We solve it by recursion
 *
 * Base:
 * If I'm in bound and has the same value as source value,
 *      please fill me.
 * Recursion:
 *      fill myself.
 *      Fill four-directional position.
 *
 * Notice:
 * m = image.size(); n = image[0].size()
 */
void floodFillHelper1(vector< vector<int> >& image, vector< vector<int> >& visited,
                      int sr, int sc, int& sourceVal, int& newColor) {
    if ((sr >= 0) && (sr < image.size()) &&
        (sc >= 0) && (sc < image[0].size()) &&
        (image[sr][sc] == sourceVal) &&
        (visited[sr][sc] == 0)) {
        image[sr][sc] = newColor;
        visited[sr][sc] = 1;

        floodFillHelper1(image, visited, sr - 1, sc, sourceVal, newColor); // up
        floodFillHelper1(image, visited, sr + 1, sc, sourceVal, newColor); // down
        floodFillHelper1(image, visited, sr, sc - 1, sourceVal, newColor); // left
        floodFillHelper1(image, visited, sr, sc + 1, sourceVal, newColor); // right
    }
}

vector< vector<int> > floodFill_sol1(vector< vector<int> >& image, int sr, int sc, int newColor) {
    int sourceVal = image[sr][sc];
    int newVal = newColor;
    if (sourceVal == newVal) return image;
    vector< vector<int> > visited(image.size(), vector<int>(image[0].size(), 0));

    floodFillHelper1(image, visited, sr, sc, sourceVal, newVal);

    return image;
}

/*
 * Function: floodFill_sol2
 * ------------------------------------
 * Use queue to simulate BFS.
 */
vector<vector<int>> floodFill_sol2(vector<vector<int>>& image,
                                   int sr, int sc, int newColor) {
    class QueueState {
    public:
        int sr; int sc;
        QueueState(int sr, int sc) {
            this->sr = sr;
            this->sc = sc;
        }
    };

    int sourceVal = image[sr][sc];
    if (sourceVal == newColor) return image;
    vector< vector<int> > visited(image.size(), vector<int>(image[0].size(), 0));

    queue<QueueState> buffer;
    buffer.push(QueueState(sr, sc));
    while (!buffer.empty()) {
        QueueState cur = buffer.front();
        buffer.pop();
        if ((cur.sr >= 0) && (cur.sr < image.size()) &&
            (cur.sc >= 0) && (cur.sc < image[0].size()) &&
            (image[cur.sr][cur.sc] == sourceVal) &&
            (visited[cur.sr][cur.sc] == 0)) {
                image[cur.sr][cur.sc] = newColor;
                visited[cur.sr][cur.sc] = 1;

                buffer.push(QueueState(cur.sr + 1, cur.sc));
                buffer.push(QueueState(cur.sr - 1, cur.sc));
                buffer.push(QueueState(cur.sr, cur.sc - 1));
                buffer.push(QueueState(cur.sr, cur.sc + 1));
            }
    }
    return image;
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for floodFill_sol1():") {
    vector< vector<int> > image = {{0, 0, 0},
                                   {0, 0, 0}};
    int sr = 0;
    int sc = 0;
    int newColor = 2;
    floodFill_sol1(image, sr, sc, newColor);
    EXPECT_EQUAL(image[0][0], 2);
    EXPECT_EQUAL(image[0][1], 2);
    EXPECT_EQUAL(image[0][2], 2);
    EXPECT_EQUAL(image[1][0], 2);
    EXPECT_EQUAL(image[1][1], 2);
    EXPECT_EQUAL(image[1][2], 2);
}

PROVIDED_TEST("Test for floodFill_sol1() when new color equal original color:") {
    vector< vector<int> > image = {{0, 0, 0},
                                   {0, 1, 1}};
    int sr = 1;
    int sc = 1;
    int newColor = 1;
    floodFill_sol1(image, sr, sc, newColor);
    EXPECT_EQUAL(image[0][0], 0);
    EXPECT_EQUAL(image[0][1], 0);
    EXPECT_EQUAL(image[0][2], 0);
    EXPECT_EQUAL(image[1][0], 0);
    EXPECT_EQUAL(image[1][1], 1);
    EXPECT_EQUAL(image[1][2], 1);
}

PROVIDED_TEST("Test for floodFill_sol2():") {
    vector< vector<int> > image = {{0, 0, 0},
                                   {0, 0, 0}};
    int sr = 0;
    int sc = 0;
    int newColor = 2;
    floodFill_sol2(image, sr, sc, newColor);
    EXPECT_EQUAL(image[0][0], 2);
    EXPECT_EQUAL(image[0][1], 2);
    EXPECT_EQUAL(image[0][2], 2);
    EXPECT_EQUAL(image[1][0], 2);
    EXPECT_EQUAL(image[1][1], 2);
    EXPECT_EQUAL(image[1][2], 2);
}

PROVIDED_TEST("Test for floodFill_sol2() when new color equal original color:") {
    vector< vector<int> > image = {{0, 0, 0},
                                   {0, 1, 1}};
    int sr = 1;
    int sc = 1;
    int newColor = 1;
    floodFill_sol2(image, sr, sc, newColor);
    EXPECT_EQUAL(image[0][0], 0);
    EXPECT_EQUAL(image[0][1], 0);
    EXPECT_EQUAL(image[0][2], 0);
    EXPECT_EQUAL(image[1][0], 0);
    EXPECT_EQUAL(image[1][1], 1);
    EXPECT_EQUAL(image[1][2], 1);
}
