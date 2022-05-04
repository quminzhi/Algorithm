#include "problems.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>
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
    DisjointSet dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && isConnected[i][j] == 1) {
                if (dsu.find(i) != dsu.find(j)) {
                    dsu.merge(i, j);
                }
            }
        }
    }

    return dsu.size;
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
    DisjointSet dsu(n);
    for (int i = 0; i < edges.size(); i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        if (dsu.find(aa) == dsu.find(bb)) {
            return false;
        } else {
            dsu.merge(aa, bb);
        }
    }

    return dsu.size == 1;
}

/**
 * @brief
 *
 * @param n
 * @param edges
 * @return int
 */
int countComponents(int n, vector<vector<int>>& edges) {
    DisjointSet dsu(n);
    for (int i = 0; i < edges.size(); i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        if (dsu.find(aa) != dsu.find(bb)) {
            dsu.merge(aa, bb);
        }
    }

    return dsu.size;
}

int earliestAcq(vector<vector<int>>& logs, int n) {
    int m = logs.size();
    struct Edge {
        int log;
        int aa;
        int bb;
        bool operator<(const Edge& e) const { return log < e.log; }
    } edges[m];

    for (int i = 0; i < m; i++) {
        edges[i].log = logs[i][0];
        edges[i].aa = logs[i][1];
        edges[i].bb = logs[i][2];
    }

    sort(edges, edges + m);

    DisjointSet dsu(n);
    for (int i = 0; i < m; i++) {
        int aa = edges[i].aa;
        int bb = edges[i].bb;
        if (dsu.find(aa) != dsu.find(bb)) {
            dsu.merge(aa, bb);
            if (dsu.size == 1) {
                return edges[i].log;
            }
        }
    }

    return -1;
}

/**
 * @brief
 *
 * @param s
 * @param pairs
 * @return string
 */
string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    int n = s.size();
    int m = pairs.size();
    DisjointSet dsu(n);
    for (int i = 0; i < m; i++) {
        int aa = pairs[i][0];
        int bb = pairs[i][1];
        if (dsu.find(aa) != dsu.find(bb)) {
            dsu.merge(aa, bb);
            if (dsu.size == 1) break;   // optimize
        }
    }

    // group
    unordered_map<int, vector<int>> groups;
    for (int i = 0; i < n; i++) {
        int gid = dsu.find(i);
        groups[gid].push_back(i);   // ascending order
    }

    // sort each group and reconstruct min string
    string res(n, ' ');
    for (auto group : groups) {
        // indices to substring
        vector<char> ss;
        for (int i = 0; i < group.second.size(); i++) {
            int idx = group.second[i];
            ss.push_back(s[idx]);
        }
        sort(ss.begin(), ss.end());
        // add sorted substring to res, note that indices in group are in ascending order
        for (int i = 0; i < group.second.size(); i++) {
            res[group.second[i]] = ss[i];
        }
    }

    return res;
}

// calculate the result from aa to bb
double calcHelper(vector<int>& h, vector<int>& v, vector<double>& w, vector<int>& ne, vector<bool>& visited, int aa,
                  int bb) {
    if (aa == bb) {
        return 1;
    }

    visited[aa] = true;
    for (int p = h[aa]; p != -1; p = ne[p]) {
        int j = v[p];
        if (visited[j]) continue;
        double t = calcHelper(h, v, w, ne, visited, j, bb);
        if (t != 0) {
            return w[p] * t;   // w[p]: weight of aa -> j
        }
    }

    return 0;   // indicate fail on this path
}

/**
 * @brief disjoint set union
 *
 * @param equations
 * @param values
 * @param queries
 * @return vector<double>
 */
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                            vector<vector<string>>& queries) {
    // map string to int for constructing disjoint set
    unordered_map<string, int> toInt;
    // adjacency list: m ~ n
    int m = equations.size();
    int n = 2 * m;   // at most 2 * m vertexes
    int idx = 0;
    vector<int> h(n, -1);
    vector<int> v(2 * m, 0);   // undirected
    vector<double> w(2 * m, 0);
    vector<int> ne(2 * m, -1);
    DisjointSet dsu(n);
    int cntN = 0;   // 0-based
    for (int i = 0; i < m; i++) {
        // map to int
        if (toInt.find(equations[i][0]) == toInt.end()) {
            toInt[equations[i][0]] = cntN++;
        }
        if (toInt.find(equations[i][1]) == toInt.end()) {
            toInt[equations[i][1]] = cntN++;
        }
        // adjacency list
        int aa = toInt[equations[i][0]];
        int bb = toInt[equations[i][1]];
        // a -> b
        v[idx] = bb;
        w[idx] = values[i];
        ne[idx] = h[aa];
        h[aa] = idx++;
        // b -> a
        v[idx] = aa;
        w[idx] = 1 / values[i];
        ne[idx] = h[bb];
        h[bb] = idx++;
        // update dsu
        if (dsu.find(aa) != dsu.find(bb)) {
            dsu.merge(aa, bb);
        }
    }

    vector<double> res;
    for (int i = 0; i < queries.size(); i++) {
        if (toInt.find(queries[i][0]) == toInt.end() || toInt.find(queries[i][1]) == toInt.end()) {
            res.push_back(-1);
            continue;
        }
        int aa = toInt[queries[i][0]];
        int bb = toInt[queries[i][1]];
        if (dsu.find(aa) != dsu.find(bb)) {
            res.push_back(-1);
        } else {
            vector<bool> visited(n, false);
            res.push_back(calcHelper(h, v, w, ne, visited, aa, bb));   // dfs in graph
        }
    }

    return res;
}