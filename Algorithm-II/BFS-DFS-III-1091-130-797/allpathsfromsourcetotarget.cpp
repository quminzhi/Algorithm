#include "allpathsfromsourcetotarget.h"
#include <queue>
#include <testing/SimpleTest.h>

/**
 * @brief allPathsSourceTarget_sol1
 * @param graph
 * @return all paths
 * Basically, BFS or DFS with tracking path.
 */
vector< vector<int> > allPathsSourceTarget_sol1(vector< vector<int> >& graph) {
    vector< vector<int> > result;
    if (graph.size() == 0) return result;

    class QueueNode {
    public:
        int node;
        vector<int> path;
        QueueNode(int _node, vector<int> _path)
            : node(_node), path(_path) {}
    };

    int target = graph.size() - 1;
    queue<QueueNode> que;
    que.push(QueueNode(0, {0}));
    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();
        if (cur.node == target) {
            result.push_back(cur.path);
        }
        for (int neighbor = 0; neighbor < graph[cur.node].size(); neighbor++) {
            // choose
            cur.path.push_back(graph[cur.node][neighbor]);
            que.push(QueueNode(graph[cur.node][neighbor], cur.path));
            // unchoose
            cur.path.pop_back();
        }
    }

    return result;
}

void searchHelper(vector< vector<int> >& graph,
                  vector< vector<int> >& result,
                  int node,
                  vector<int>& path,
                  int target) {
    if (node == target) {
        result.push_back(path);
    }

    for (int i = 0; i < graph[node].size(); i++) {
        // choose
        path.push_back(graph[node][i]);
        searchHelper(graph, result, graph[node][i], path, target);
        // unchoose
        path.pop_back();
    }
}

/**
 * @brief allPathsSourceTarget_sol2
 * @param graph
 * @return
 * Solution2 will employ deep first search.
 */
vector<vector <int> > allPathsSourceTarget_sol2(vector< vector<int> >& graph) {
    vector< vector<int> > result;
    if (graph.size() == 0) return result;
    vector<int> path = {0};

    searchHelper(graph, result, 0, path, graph.size()-1);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector< vector<int> > graph1 = {
        {1, 2},
        {3},
        {3},
        {}
    };

    EXPECT_EQUAL(allPathsSourceTarget_sol1(graph1).size(), 2);
}

PROVIDED_TEST("test for sol2:") {
    vector< vector<int> > graph1 = {
        {1, 2},
        {3},
        {3},
        {}
    };

    EXPECT_EQUAL(allPathsSourceTarget_sol2(graph1).size(), 2);
}
