#include "problems.hpp"
#include <iostream>
#include <unordered_set>

DisjointSet::DisjointSet(int n) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
}

void DisjointSet::merge(int x, int y) {
    p[find(x)] = find(y);
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

    unordered_set<int> note;
    for (int i = 0; i < n; i++) {
        int t = uds.find(i);
        if (note.find(t) == note.end()) {
            note.insert(t);
        }
    }

    return note.size();
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

    unordered_set<int> note;
    for (int i = 0; i < n; i++) {
        int t = uds.find(i);
        if (note.find(t) == note.end()) {
            note.insert(t);
        }
    }

    return note.size() == 1;
}