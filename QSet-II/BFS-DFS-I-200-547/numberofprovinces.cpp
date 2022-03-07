#include "numberofprovinces.h"
#include <queue>
#include <testing/SimpleTest.h>

/**
 * @brief tagCity
 * @param isConnected: connection map
 * @param isTagged: if current city is tagged
 * @param i: ith city
 */
void tagCity(vector< vector<int> >& isConnected, vector<bool>& isTagged, int i) {
    queue<int> q;
    q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        isTagged[cur] = true;
        for (int i = 0; i < isConnected.size(); i++) {
            if ((i != cur) && (!isTagged[i]) && (isConnected[cur][i] == 1)) {
                q.push(i);
            }
        }
    }
}

/**
 * @brief findCircleNum_sol1
 * @param isConnected: a connection map where isConnected[i][j] = 1 if the ith city
 * and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
 * @return the number of provinces
 *
 * Input: [ [1,1,0],
 *          [1,1,0],
 *          [0,0,1] ]
 *
 * Basic idea: traverse all cities.
 *  if the city is tagged with a province, then skip.
 *  else find all cities which belongs to the same province as current city.
 *
 * How to find directly or indirectly connected cities? isConnected map!
 *
 * T: O(N), S: O(N)
 */
int findCircleNum_sol1(vector< vector<int> >& isConnected) {
    vector<bool> isTagged(isConnected.size(), false);
    int numOfProvinces = 0;

    // TODO: traverse all cities
    for (int i = 0; i < isConnected.size(); i++) {
        if (!isTagged[i]) {
            numOfProvinces++;
            tagCity(isConnected, isTagged, i);
        }
    }

    return numOfProvinces;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector< vector<int> > isConnected1 = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    EXPECT_EQUAL(findCircleNum_sol1(isConnected1), 2);

    vector< vector<int> > isConnected2 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    EXPECT_EQUAL(findCircleNum_sol1(isConnected2), 3);
}
