#include "maxareaofisland.h"
#include "testing/SimpleTest.h"


void exploreIsland(vector< vector<int> >& grid, vector< vector<int> >& visited, int row, int col, int& area) {
    if ((row >= 0) && (row < grid.size()) &&
        (col >= 0) && (col < grid[0].size()) &&
        (grid[row][col] == 1) && (visited[row][col] == 0)) {
        visited[row][col] = 1;
        area++;
        exploreIsland(grid, visited, row - 1, col, area);
        exploreIsland(grid, visited, row + 1, col, area);
        exploreIsland(grid, visited, row, col - 1, area);
        exploreIsland(grid, visited, row, col + 1, area);
    }
}


/*
 * Function: maxAreaOfIsland_sol1
 * ------------------------------------
 * The function will return the maximum area of island.
 *
 * Imagine we are a band of people who are going to travel all over the world. We are trying
 * to find new island. What should we do?
 *
 * 1. Traverse from a starting point in raster order.
 * 2. If I step on to a new island (find a new 1). Then I will explore on the island and tag
 * all the area I have left my steps. Record the area of the island. (DFS)
 * 3. Go back to where I step on to the island, and start my sea travel until find a new island.
 * 4. If I have gone to all the area of the world, then there you go. We got the maximum area
 * of island.
 */
int maxAreaOfIsland_sol1(vector< vector<int> >& grid) {
    int maxIsland = 0;
    vector< vector<int> > visited(grid.size(), vector<int>(grid[0].size(), 0));
    // TODO: start to travel
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if ((grid[i][j] == 1) && (visited[i][j] == 0)) {
                int area = 0;
                exploreIsland(grid, visited, i, j, area);
                if (area > maxIsland) {
                    maxIsland = area;
                }
            }
        }
    }

    return maxIsland;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for maxAreaOfIsland_sol1():") {
    vector< vector<int> > world = {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };
    EXPECT_EQUAL(maxAreaOfIsland_sol1(world), 6);
}
