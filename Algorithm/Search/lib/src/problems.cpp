#include "problems.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_set>

DisjointSet::DisjointSet(int n) {
    size = n;
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
}

void DisjointSet::merge(int x, int y) {
    p[find(x)] = find(y);
    size--;
}

int DisjointSet::find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }

    return p[x];
}

/**
 * @brief
 * 
 * @param isConnected: an adjacency matrix
 * @return int: the number of connected graphs
 */
int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    DisjointSet uds(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && isConnected[i][j] == 1) {
                if (uds.find(i) != uds.find(j)) {
                    uds.merge(i, j);
                }
            }
        }
    }

    return uds.size;
}

void dfs(vector<vector<int>>& isConnected, vector<int>& color, int i, int c) {
    color[i] = c;
    for (int j = 0; j < isConnected.size(); j++) {
        if (isConnected[i][j] == 1 && color[j] == 0) {
            dfs(isConnected, color, j, c);
        }
    }
}

int findCircleNumII(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    // 0: no color, 1: first color, 2: second color ...
    vector<int> color(n, 0);
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            c++;
            dfs(isConnected, color, i, c);
        }
    }

    return c;
}

/**
 * @brief 
 * 
 * @param n 
 * @param edges 
 * @return true 
 * @return false 
 */
bool validTree(int n, vector<vector<int>>& edges) {
    DisjointSet uds(n);
    for (int i = 0; i < edges.size(); i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        if (uds.find(aa) == uds.find(bb)) {
            return false;
        } else {
            uds.merge(aa, bb);
        }
    }

    return uds.size == 1;
}

/**
 * @brief 
 * 
 * @param n 
 * @param edges 
 * @return int 
 */
int countComponents(int n, vector<vector<int>>& edges) {
    DisjointSet uds(n);
    for (int i = 0; i < edges.size(); i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        if (uds.find(aa) != uds.find(bb)) {
            uds.merge(aa, bb);
        }
    }

    return uds.size;
}

int earliestAcq(vector<vector<int>>& logs, int n) {
    int m = logs.size();
    struct Edge {
        int log;
        int aa;
        int bb;
        bool operator< (const Edge& e) const {
            return log < e.log;
        }
    } edges[m];

    for (int i = 0; i < m; i++) {
        edges[i].log = logs[i][0];
        edges[i].aa = logs[i][1];
        edges[i].bb = logs[i][2];
    }

    sort(edges, edges + m);

    DisjointSet uds(n);
    for (int i = 0; i < m; i++) {
        int aa = edges[i].aa;
        int bb = edges[i].bb;
        if (uds.find(aa) != uds.find(bb)) {
            uds.merge(aa, bb);
            if (uds.size == 1) {
                return edges[i].log;
            }
        }
    }

    return -1;
}