#include "problems.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
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

/**
 * @brief
 *
 * @param n: 1-based
 * @param wells: 0-based
 * @param pipes
 * @return int
 */
int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
    int N = n + 1;
    int m = pipes.size();
    int inf = 1e5;
    vector<vector<int>> g(N, vector<int>(N, inf));
    for (int i = 0; i < m; i++) {
        int aa = pipes[i][0];
        int bb = pipes[i][1];
        int cost = pipes[i][2];
        g[aa][bb] = g[bb][aa] = min(g[aa][bb], cost);
    }

    vector<int> dist(N, inf);
    vector<int> st(N, false);
    for (int i = 1; i <= n; i++) {
        dist[i] = wells[i - 1];
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        // find min dist
        int t = -1;
        for (int j = 1; j <= n; j++) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }

        if (i && dist[t] == inf) return inf;

        // update
        for (int j = 1; j <= n; j++) {
            if (!st[j]) {
                dist[j] = min(dist[j], g[t][j]);
            }
        }

        res += dist[t];
        st[t] = true;
    }

    return res;
}

/**
 * @brief
 *
 * @param n
 * @param wells
 * @param pipes
 * @return int
 */
int minCostToSupplyWaterII(int n, vector<int>& wells, vector<vector<int>>& pipes) {
    int N = n + 1;
    int m = pipes.size();
    struct Edge {
        int aa, bb, cost;
        bool operator<(const Edge& e) const { return cost < e.cost; }
    } edges[m + n];   // pipe edges + well edges

    for (int i = 0; i < m; i++) {
        int aa = pipes[i][0];
        int bb = pipes[i][1];
        int cost = pipes[i][2];
        edges[i].aa = aa;
        edges[i].bb = bb;
        edges[i].cost = cost;
    }

    // i points to well, j points to edges
    for (int i = 1, j = m; i <= n; i++, j++) {
        edges[j].aa = 0;   // virtual endpoint of well edge
        edges[j].bb = i;
        edges[j].cost = wells[i - 1];   // well is 0-based
    }

    sort(edges, edges + m + n);

    DisjointSet dsu(N);
    int res = 0;
    for (int i = 0; i < m + n; i++) {
        int aa = edges[i].aa;
        int bb = edges[i].bb;
        int cost = edges[i].cost;
        if (dsu.find(aa) != dsu.find(bb)) {
            dsu.merge(aa, bb);
            res += cost;
        }
    }

    return res;
}

bool findPathHelper(vector<int>& h, vector<int>& v, vector<int>& ne, vector<bool>& st, int src, int dst) {
    if (src == dst) {
        return true;
    }

    st[src] = true;
    for (int p = h[src]; p != -1; p = ne[p]) {
        int j = v[p];
        if (!st[j] && findPathHelper(h, v, ne, st, j, dst)) {
            return true;
        }
    }

    return false;
}

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    int m = edges.size();
    int idx = 0;
    vector<int> h(n, -1);
    vector<int> v(2 * m, 0);
    vector<int> ne(2 * m, -1);
    vector<bool> st(n, false);
    for (int i = 0; i < m; i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
        v[idx] = aa;
        ne[idx] = h[bb];
        h[bb] = idx++;
    }

    if (findPathHelper(h, v, ne, st, source, destination)) {
        return true;
    }
    return false;
}

void pathSearch(vector<vector<int>>& graph, int src, int dst, vector<bool>& st, vector<int>& path,
                vector<vector<int>>& res) {
    if (src == dst) {
        res.push_back(path);
        return;
    }

    st[src] = true;
    for (auto v : graph[src]) {
        if (!st[v]) {
            path.push_back(v);
            pathSearch(graph, v, dst, st, path, res);
            path.pop_back();
        }
    }
    st[src] = false;

    return;
}

/**
 * @brief
 *
 * @param graph
 * @return vector<vector<int>>
 */
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    vector<vector<int>> res;
    vector<int> path = {0};
    vector<bool> st(graph.size(), false);
    pathSearch(graph, 0, graph.size() - 1, st, path, res);
    return res;
}

Node* cloneGraphHelper(unordered_map<Node*, Node*>& copyOf, Node* node) {
    if (node == nullptr) return nullptr;
    if (copyOf.find(node) != copyOf.end()) {
        return copyOf[node];
    }

    Node* clone = new Node(node->val);
    copyOf[node] = clone;   // same effect: st[val] = true;

    for (int i = 0; i < node->neighbors.size(); i++) {
        Node* neighborClone = cloneGraphHelper(copyOf, node->neighbors[i]);
        clone->neighbors.push_back(neighborClone);
    }

    return clone;
}

/**
 * @brief
 *
 * @param node
 * @return Node*
 */
Node* cloneGraph(Node* node) {
    int N = 110;
    unordered_map<Node*, Node*> copyOf;
    Node* clone = cloneGraphHelper(copyOf, node);

    return clone;
}

bool allPathsToDst(vector<int>& h, vector<int>& v, vector<int>& ne, vector<bool>& st, int src, int dst) {
    if (h[src] == -1 && src == dst) {
        return true;
    }
    if (h[src] == -1) {
        return false;
    }

    st[src] = true;
    for (int p = h[src]; p != -1; p = ne[p]) {
        int j = v[p];
        if (!st[j] && allPathsToDst(h, v, ne, st, j, dst)) {
            continue;
        } else {
            return false;   // bad path found
        }
    }
    st[src] = false;

    return true;
}

/**
 * @brief
 *
 * @param n
 * @param edges
 * @param source
 * @param destination
 * @return true
 * @return false
 */
bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
    int m = edges.size();
    int idx = 0;
    vector<int> h(n, -1);
    vector<int> v(m, 0);
    vector<int> ne(m, -1);
    for (int i = 0; i < m; i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
    }

    vector<bool> st(n, false);
    if (allPathsToDst(h, v, ne, st, source, destination)) {
        return true;
    }
    return false;
}

/**
 * @brief
 *
 * @param n
 * @param edges
 * @param source
 * @param destination
 * @return true
 * @return false
 */
bool validPathBFS(int n, vector<vector<int>>& edges, int source, int destination) {
    int m = edges.size();
    int idx = 0;
    vector<int> h(n, -1);
    vector<int> v(2 * m, 0);
    vector<int> ne(2 * m, -1);
    for (int i = 0; i < m; i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
        v[idx] = aa;
        ne[idx] = h[bb];
        h[bb] = idx++;
    }

    queue<int> que;
    vector<bool> st(n, false);
    que.push(source);
    bool found = false;
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        st[cur] = true;

        if (cur == destination) {
            found = true;
            break;
        }

        for (int p = h[cur]; p != -1; p = ne[p]) {
            int j = v[p];
            if (st[j]) continue;
            que.push(j);
        }
    }

    return found;
}

/**
 * @brief
 *
 * @param graph
 * @return vector<vector<int>>
 */
vector<vector<int>> allPathsSourceTargetBFS(vector<vector<int>>& graph) {
    queue<vector<int>> que;   // push path
    vector<vector<int>> paths;
    int dst = graph.size() - 1;
    que.push({0});
    while (!que.empty()) {
        vector<int> cur = que.front();
        que.pop();
        int last = cur[cur.size() - 1];
        for (int ver : graph[last]) {
            cur.push_back(ver);
            if (ver == dst) {
                paths.push_back(cur);   // found
            } else {
                que.push(cur);
            }
            cur.pop_back();
        }
    }

    return paths;
}

/**
 * @brief
 *
 * @param grid
 * @return int
 */
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    const vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    const vector<int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};
    int nDir = dx.size();
    typedef pair<int, int> PII;
    queue<PII> que;
    vector<vector<bool>> st(m, vector<bool>(n, false));
    int step = 0;
    if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) {
        return -1;
    }
    que.push({0, 0});
    while (!que.empty()) {
        int sz = que.size();
        if (sz != 0) step++;
        for (int i = 0; i < sz; i++) {
            PII cur = que.front();
            que.pop();
            int x = cur.first, y = cur.second;
            if (x == m - 1 && y == n - 1) return step;
            st[x][y] = true;
            for (int i = 0; i < nDir; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !st[nx][ny] && grid[nx][ny] == 0) {
                    que.push({nx, ny});
                }
            }
        }
    }

    return -1;
}

/**
 * @brief
 *
 * @param root
 * @return vector<vector<int>>
 */
vector<vector<int>> levelOrder(Node* root) {
    if (root == nullptr) return {};
    vector<vector<int>> res;
    queue<Node*> que;
    que.push(root);
    res.push_back({root->val});
    while (!que.empty()) {
        int sz = que.size();
        vector<int> levelNodes;
        for (int i = 0; i < sz; i++) {
            Node* cur = que.front();
            que.pop();
            for (Node* child : cur->neighbors) {
                if (child != nullptr) {
                    que.push(child);
                    levelNodes.push_back(child->val);
                }
            }
        }
    }

    return res;
}

/**
 * @brief
 *
 * @param grid
 * @return int
 */
int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    const vector<int> dx = {-1, 1, 0, 0};
    const vector<int> dy = {0, 0, -1, 1};
    typedef pair<int, int> PII;
    queue<PII> que;
    int freshTotal = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                que.push({i, j});
            }
            if (grid[i][j] == 1) freshTotal++;
        }
    }

    // if no oranges, return 0
    if (que.size() == 0 && freshTotal == 0) return 0;

    int timeElapsed = 0;
    while (!que.empty()) {
        timeElapsed++;
        int sz = que.size();
        for (int i = 0; i < sz; i++) {
            PII cur = que.front();
            que.pop();
            int x = cur.first, y = cur.second;
            for (int i = 0; i < dx.size(); i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                    freshTotal--;
                    grid[nx][ny] = 2;
                    que.push({nx, ny});
                }
            }
        }
    }

    if (freshTotal == 0) {   // no fresh orange available
        return timeElapsed - 1;
    }
    return -1;
}

/**
 * @brief Dijkstra algorithm
 *
 * @param times
 * @param n
 * @param k
 * @return int
 */
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    int N = n + 1;
    int m = times.size();
    int inf = 1e9;
    vector<vector<int>> g(N, vector<int>(N, inf));
    for (int i = 0; i < m; i++) {
        int aa = times[i][0];
        int bb = times[i][1];
        int wt = times[i][2];
        g[aa][bb] = min(g[aa][bb], wt);
    }

    vector<int> dist(N, inf);
    vector<bool> st(N, false);
    typedef pair<int, int> PII;
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    dist[k] = 0;
    pq.push({dist[k], k});

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int ver = cur.second;
        if (st[ver]) continue;
        st[ver] = true;
        for (int j = 1; j <= n; j++) {
            if (!st[j] && dist[ver] + g[ver][j] < dist[j]) {
                dist[j] = dist[ver] + g[ver][j];
                pq.push({dist[j], j});
            }
        }
    }

    int idx = -1;
    for (int i = 1; i <= n; i++) {
        if (idx == -1 || dist[i] > dist[idx]) {
            idx = i;
        }
    }

    return dist[idx] == inf ? -1 : dist[idx];
}

/**
 * @brief SPFA is an optimized version of bellman
 *   BELLMAN:
 *      1. iterate k times
 *      2. for edge in edges:
 *            dist[j] = min(dist[j], dist[i] + weight[i][j])
 *
 *   SPFA: relax other vertexes with newly updated vertexes
 *      queue is used to cache newly updated  vertexes.
 *      st[]: record if a vertex is in the queue.
 *      1. push src in to the queue
 *      2. use src to update its adjacent vertexes, if succeed, add newly updated vertexes
 *         into the queue.
 *
 * @param n
 * @param flights
 * @param src
 * @param dst
 * @param k: transfer time
 * @return int
 */
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    // input graph is a dense graph (0-based)
    int m = flights.size();
    int inf = 1e9;
    vector<vector<int>> g(n, vector<int>(n, inf));
    for (int i = 0; i < m; i++) {
        int aa = flights[i][0];
        int bb = flights[i][1];
        int wt = flights[i][2];
        g[aa][bb] = min(g[aa][bb], wt);
    }

    vector<int> dist(n, inf);
    queue<int> que;
    dist[src] = 0;
    que.push(src);
    int nEdge = 0;
    while (!que.empty()) {
        nEdge++;
        if (nEdge > k + 1) break;
        int sz = que.size();
        // prevent chaining update
        vector<int> backup(dist.begin(), dist.end());
        // check on kth expansion, push the same (newly-updated) vertex once.
        vector<bool> st(n, false);
        for (int i = 0; i < sz; i++) {
            int ver = que.front();
            que.pop();
            for (int j = 0; j < n; j++) {
                if (backup[ver] + g[ver][j] < dist[j]) {
                    dist[j] = backup[ver] + g[ver][j];
                    if (!st[j]) {
                        que.push(j);
                        st[j] = true;
                    }
                }
            }
        }
    }

    return dist[dst] == inf ? -1 : dist[dst];
}

/**
 * @brief
 *
 * @param heights
 * @return int
 */
int minimumEffortPath(vector<vector<int>>& heights) {
    class Cell {
       public:
        Cell(int _x, int _y, int _effort) : x(_x), y(_y), minEffort(_effort) {}
        int x, y;
        int minEffort;
    };

    // customize comparator of Cell for priority queue
    // lhs are children
    struct Comparator {
        bool operator()(const Cell& lhs, const Cell& rhs) { return lhs.minEffort > rhs.minEffort; }
    };

    const vector<int> dx = {-1, 1, 0, 0};
    const vector<int> dy = {0, 0, -1, 1};

    int m = heights.size();
    int n = heights[0].size();
    int inf = 1e9;
    vector<vector<int>> dist(m, vector<int>(n, inf));   // max diff
    vector<vector<bool>> st(m, vector<bool>(n, false));
    dist[0][0] = 0;

    priority_queue<Cell, vector<Cell>, Comparator> pq;
    pq.push(Cell(0, 0, dist[0][0]));
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        int x = t.x, y = t.y, minEffort = t.minEffort;
        if (st[x][y]) continue;
        st[x][y] = true;
        // update
        for (int i = 0; i < dx.size(); i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !st[nx][ny] &&
                dist[nx][ny] > max(dist[x][y], abs(heights[nx][ny] - heights[x][y]))) {
                dist[nx][ny] = max(dist[x][y], abs(heights[nx][ny] - heights[x][y]));
                pq.push(Cell(nx, ny, dist[nx][ny]));
            }
        }
    }

    return dist[m - 1][n - 1];
}

/**
 * @brief
 *
 * @param grid
 * @return int
 */
int maximumMinimumPath(vector<vector<int>>& grid) {
    class Cell {
       public:
        Cell(int _x, int _y, int _maxScore) : x(_x), y(_y), maxScore(_maxScore){};
        int x, y;
        int maxScore;
    };

    struct Comparator {
        bool operator()(const Cell& lhs, const Cell& rhs) { return lhs.maxScore < rhs.maxScore; }
    };

    const vector<int> dx = {-1, 1, 0, 0};
    const vector<int> dy = {0, 0, -1, 1};

    int inf = 1e9;
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> dist(m, vector<int>(n, -inf));   // find max score
    vector<vector<bool>> st(m, vector<bool>(n, false));
    priority_queue<Cell, vector<Cell>, Comparator> pq;
    dist[0][0] = grid[0][0];
    pq.push(Cell(0, 0, dist[0][0]));
    while (!pq.empty()) {
        Cell t = pq.top();
        pq.pop();
        int x = t.x, y = t.y, score = t.maxScore;
        if (st[x][y]) continue;
        st[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !st[nx][ny] && dist[nx][ny] < min(dist[x][y], grid[nx][ny])) {
                dist[nx][ny] = min(dist[x][y], grid[nx][ny]);
                pq.push(Cell(nx, ny, dist[nx][ny]));
            }
        }
    }

    return dist[m - 1][n - 1];
}

/**
 * @brief
 *
 * @param grid
 * @return int
 */
int swimInWater(vector<vector<int>>& grid) {
    class Cell {
       public:
        Cell(int _x, int _y, int _minTime) : x(_x), y(_y), minTime(_minTime){};
        int x, y;
        int minTime;
    };

    struct Comparator {
        bool operator()(const Cell& lhs, const Cell& rhs) { return lhs.minTime > rhs.minTime; }
    };

    const vector<int> dx = {-1, 1, 0, 0};
    const vector<int> dy = {0, 0, -1, 1};

    int m = grid.size();
    int n = grid[0].size();
    int inf = 1e9;
    vector<vector<int>> dist(m, vector<int>(n, inf));
    vector<vector<bool>> st(m, vector<bool>(n, false));
    priority_queue<Cell, vector<Cell>, Comparator> pq;
    dist[0][0] = grid[0][0];
    pq.push(Cell(0, 0, dist[0][0]));

    while (!pq.empty()) {
        Cell t = pq.top();
        pq.pop();
        int x = t.x, y = t.y, minTime = t.minTime;
        if (st[x][y]) continue;
        st[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !st[nx][ny] && dist[nx][ny] > max(dist[x][y], grid[nx][ny])) {
                dist[nx][ny] = max(dist[x][y], grid[nx][ny]);
                pq.push(Cell(nx, ny, dist[nx][ny]));
            }
        }
    }

    return dist[m - 1][n - 1];
}

/**
 * @brief
 *
 * @param points
 * @return int
 */
int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    int inf = 1e9;
    vector<vector<int>> g(n, vector<int>(n, inf));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = g[j][i] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        }
    }

    vector<int> dist(n, inf);
    dist[0] = 0;
    vector<bool> st(n, false);
    int res = 0;
    for (int i = 0; i < n; i++) {
        int t = -1;
        for (int j = 0; j < n; j++) {
            if (!st[j] && (t == -1 || dist[j] < dist[t])) {
                t = j;
            }
        }
        if (dist[t] == inf) return -1;
        st[t] = true;
        res += dist[t];
        for (int j = 0; j < n; j++) {
            if (!st[j] && dist[j] > g[t][j]) {
                dist[j] = g[t][j];
            }
        }
    }

    return res;
}