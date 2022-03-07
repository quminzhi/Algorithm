#include "numberofislands.h"
#include <testing/SimpleTest.h>

/**
 * @brief tagIsland
 * @param grid: the map
 * @param isTagged: record if point is tagged
 * @param i: row index of starting point
 * @param j: column index of starting point
 * tag all points within an island with BFS.
 */
void tagIsland(vector< vector<char> >& grid,
               vector< vector<bool> >& isTagged, int i, int j) {
    isTagged[i][j] = true;
    if ((i + 1 < isTagged.size()) && (grid[i+1][j] == '1') && (!isTagged[i+1][j]))
        tagIsland(grid, isTagged, i+1, j);
    if ((i - 1 >= 0) && (grid[i-1][j] == '1') && (!isTagged[i-1][j]))
        tagIsland(grid, isTagged, i-1, j);
    if ((j + 1 < isTagged[0].size()) && (grid[i][j+1] == '1') && (!isTagged[i][j+1]))
        tagIsland(grid, isTagged, i, j+1);
    if ((j - 1 >= 0) && (grid[i][j-1] == '1') && (!isTagged[i][j-1]))
        tagIsland(grid, isTagged, i, j-1);

    return;
}

/**
 * @brief numIslands
 * @param grid
 * @return the number of islands
 * Starting from (0, 0), find each island and tag it.
 *
 * T: O(N * M), S: O(N * M)
 */
int numIslands_sol1(vector< vector<char> >& grid) {
    vector< vector<bool> > isTagged(
                grid.size(),
                vector<bool>(grid[0].size(), false));
    int numOfIslands = 0;

    // TODO: traverse grid
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if ((grid[i][j] == '1') && (!isTagged[i][j])) {
                numOfIslands++;
                // TODO: tag points within the island
                tagIsland(grid, isTagged, i, j);
            }
        }
    }

    return numOfIslands;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for sol1:") {
    vector< vector<char> > grid1 = {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'1', '0', '0', '0', '0'},
        };
    EXPECT_EQUAL(numIslands_sol1(grid1), 1);

    vector< vector<char> > grid2 = {
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'1', '0', '0', '0', '0'},
        };
    EXPECT_EQUAL(numIslands_sol1(grid2), 2);
}
