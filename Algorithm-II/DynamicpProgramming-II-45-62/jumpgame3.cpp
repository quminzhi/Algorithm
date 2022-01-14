#include "jumpgame3.h"
#include <testing/SimpleTest.h>
#include <queue>

/**
 * @brief canReach_sol1
 * @param arr
 * @param start
 * @return
 * Define f(index) as: true if it can be jumped from index to index with 0.
 * f(index) = f(index + arr[index]) | f(index - arr[index])
 *
 * T: O(N^2)
 */
bool canReach_sol1(vector<int>& arr, int start) {
    if (arr.size() == 0) return false;
    int size = arr.size();
    vector<int> zero_index;
    vector<bool> reachable(size, false);
    // TODO: get all indices with 0
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            zero_index.push_back(i);
            reachable[i] = true;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int cur = 0; cur < size; cur++) {
            if (cur + arr[cur] < size) {
                reachable[cur] = reachable[cur] | reachable[cur + arr[cur]];
            }
            if (cur - arr[cur] >= 0) {
                reachable[cur] = reachable[cur] | reachable[cur - arr[cur]];
            }
        }
    }

    return reachable[start];
}

/**
 * @brief canReach_sol2
 * @param arr
 * @param start
 * @return
 * Change linear structure of arr to a graph, then DFS or BFS!
 */
bool canReach_sol2(vector<int>& arr, int start) {
    if (arr.size() == 0) return false;
    int size =  arr.size();

    vector<bool> visited(size, false);

    // TODO: start from 'start' with BFS
    queue<int> que;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        visited[cur] = true;

        if (arr[cur] == 0) {
            return true;
        }

        if ((cur - arr[cur] >= 0) && (!visited[cur - arr[cur]])) {
            que.push(cur - arr[cur]);
        }
        if ((cur + arr[cur] < size) && (!visited[cur + arr[cur]])) {
            que.push(cur + arr[cur]);
        }
    }

    return false;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> arr1 = {4,2,3,0,3,1,2};
    EXPECT(canReach_sol1(arr1, 5));
    EXPECT(canReach_sol1(arr1, 0));

    vector<int> arr2 = {3,0,2,1,2};
    EXPECT(!canReach_sol1(arr2, 2));
}

PROVIDED_TEST("test for sol2:") {
    vector<int> arr1 = {4,2,3,0,3,1,2};
    EXPECT(canReach_sol2(arr1, 5));
    EXPECT(canReach_sol2(arr1, 0));

    vector<int> arr2 = {3,0,2,1,2};
    EXPECT(!canReach_sol2(arr2, 2));
}
