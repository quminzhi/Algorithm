#include "jumpgame4.h"
#include <queue>
#include <unordered_map>
#include <testing/SimpleTest.h>

/**
 * @brief minJumps
 * @param arr
 * @return
 * The problem is similar to jump game 3. To find the minimum steps, BFS is the solution.
 */
int minJumps(vector<int>& arr) {
    if (arr.size() == 0) return 0;
    int size = arr.size();
    int target = size - 1;
    vector<bool> visited(size, false);

    class QueueNode {
    public:
        int index;
        int step;
        QueueNode(int _index, int _step)
            : index(_index), step(_step) {}
    };
    queue<QueueNode> que;
    que.push(QueueNode(0, 0));
    visited[0] = true;

    // cluster[val] -> {index with val == 'val'}
    unordered_map<int, vector<int> > cluster;
    for (int i = 0; i < size; i++) {
           cluster[arr[i]].push_back(i);
    }

    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();


        if (cur.index == target) {
            return cur.step;
        }

        if ((cur.index - 1 >= 0) && (!visited[cur.index-1])) {
            que.push(QueueNode(cur.index-1, cur.step+1));
            visited[cur.index-1] = true;
        }
        if ((cur.index + 1 < size) && (!visited[cur.index+1])) {
            que.push(QueueNode(cur.index+1, cur.step+1));
            visited[cur.index+1] = true;
        }

        // all brothers and sisters in cluster
        vector<int> brothers = cluster[arr[cur.index]];
        for (int i = 0; i < brothers.size(); i++) {
            if ((brothers[i] != cur.index) && (!visited[brothers[i]])){
                que.push(QueueNode(brothers[i], cur.step+1));
                visited[brothers[i]] = true;
            }
        }
    }

    return -1;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> arr1 = {100,-23,-23,404,100,23,23,23,3,404};
    EXPECT_EQUAL(minJumps(arr1), 3);

    vector<int> arr2(5000, 7);
    arr2.push_back(11);
    EXPECT_EQUAL(minJumps(arr2), 2);
}
