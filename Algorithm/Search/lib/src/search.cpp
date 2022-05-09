#include "search.hpp"

void NQueensHelper(vector<vector<string>>& res, vector<string>& attempt, vector<bool>& row, vector<bool>& col,
                   vector<bool>& diag, vector<bool>& anti_diag, int n, int i) {
    if (i == n) {
        res.push_back(attempt);
        return;
    }

    // try
    for (int j = 0; j < n; j++) {
        if (!row[i] && !col[j] && !diag[-i + j + n] && !anti_diag[i + j]) {
            // choose
            attempt[i][j] = 'Q';
            row[i] = col[j] = diag[-i + j + n] = anti_diag[i + j] = true;
            // try next
            NQueensHelper(res, attempt, row, col, diag, anti_diag, n, i + 1);
            // un-choose
            attempt[i][j] = '.';
            row[i] = col[j] = diag[-i + j + n] = anti_diag[i + j] = false;
        }
    }
    // no choice available
    return;
}

/**
 * @brief How to check if a place is valid to put a queen.
 *
 * res[i][j]: means jth row of ith solution, which is a string, ex> '..Q.'.
 *
 * @param n
 * @return vector<vector<string>>
 */
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> attempt(n, string(n, '.'));
    vector<bool> row(n, false);
    vector<bool> col(n, false);
    vector<bool> diag(n + n - 1, false);
    vector<bool> anti_diag(n + n - 1, false);

    NQueensHelper(res, attempt, row, col, diag, anti_diag, n, 0);

    return res;
}

/**
 * @brief bfs
 *
 * @param matrix
 * @return int: the length of min path from (0, 0) to the exit point (right bottom point).
 */
int minPathInMatrix(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    Point final(m - 1, n - 1);
    vector<vector<int>> dis(m, vector<int>(n, 1e6));   // min distance from (i, j) to (0, 0)
    dis[0][0] = 0;
    vector<vector<bool>> visited(m, vector<bool>(n, false));         // avoid repeated visit
    vector<vector<Point>> pre(m, vector<Point>(n, Point(-1, -1)));   // record the previous step of each point
    vector<Point> path;
    queue<Point> que;
    que.push(Point(0, 0));
    visited[0][0] = true;
    int dx[4] = {-1, +1, 0, 0};
    int dy[4] = {0, 0, -1, +1};
    while (!que.empty()) {
        Point cur = que.front();
        que.pop();

        if (cur.x == final.x && cur.y == final.y) {
            // back track
            while (cur.x || cur.y) {   // break when both x and y are 0
                path.push_back(cur);
                Point t = pre[cur.x][cur.y];
                cur.x = t.x, cur.y = t.y;
            }
            path.push_back(Point(0, 0));
            break;
        }

        // try
        for (int i = 0; i < 4; i++) {
            int x = cur.x + dx[i];
            int y = cur.y + dy[i];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] == 0 && !visited[x][y]) {
                dis[x][y] = dis[cur.x][cur.y] + 1;
                que.push(Point(x, y));
                visited[x][y] = true;
                pre[x][y] = Point(cur.x, cur.y);
            }
        }
    }

    // // print path in reverse order
    // for (int i = 0; i < path.size(); i++) {
    //     cout << "(" << path[i].x << ", " << path[i].y << ")" << endl;
    // }
    // cout << endl;

    return dis[m - 1][n - 1];   // or path.size() - 1 (minus (0, 0))
}

// return the size of tree with root `root`
int gravityHelper(vector<int>& head, vector<int>& v, vector<int>& ne, vector<bool>& visited, int& min_size,
                  int& gravity_node, int n, int root) {
    if (visited[root]) return 0;
    visited[root] = true;

    int sum = 1;   // root node
    int max_part = 0;
    for (int p = head[root]; p != -1; p = ne[p]) {
        int j = v[p];
        int size = gravityHelper(head, v, ne, visited, min_size, gravity_node, n, j);
        sum += size;
        max_part = max(max_part, size);
    }
    // upper part
    max_part = max(max_part, n - sum);

    // update gravity
    if (max_part < min_size) {
        min_size = max_part;
        gravity_node = root;
    }

    return sum;
}

void edge_insert(vector<int>& head, vector<int>& v, vector<int>& ne, int& idx, int a, int b) {
    v[idx] = b;
    ne[idx] = head[a];
    head[a] = idx++;
}

/**
 * @brief return the index of center of gravity.
 *
 * When deleting ith node, the number of 3 parts are:
 *   1. size(left subtree)
 *   2. size(right subtree)
 *   3. N - size(i)
 *
 * @param n: number of nodes
 * @param graph
 * @return int
 */
int centerOfGravity(int n, vector<vector<int>>& graph) {
    if (n == 0) return -1;
    int max_size = 1e5 + 10;
    int idx = 0;
    vector<int> head(n, -1);
    vector<bool> visited(n, false);
    vector<int> v(max_size, 0);
    vector<int> ne(max_size, 0);

    // construct adjacency list
    for (int i = 0; i < graph.size(); i++) {
        int a = graph[i][0];
        int b = graph[i][1];
        // no direction
        edge_insert(head, v, ne, idx, a, b);
        edge_insert(head, v, ne, idx, b, a);
    }

    int min_size = 1e5;
    int gravity_node = -1;
    gravityHelper(head, v, ne, visited, min_size, gravity_node, n, 0);   // assumed starting from vertex with label 0

    return min_size;
}

vector<int> pseudoTopologicalSeq(int n, vector<vector<int>>& graph) {
    if (n == 0) return {};
    int max_n = 1e5 + 10;
    int idx = 0;
    vector<int> head(n, -1);
    vector<int> ne(max_n, 0);
    vector<int> v(max_n, 0);

    // construct adjacency list
    for (int i = 0; i < graph.size(); i++) {
        int v1 = graph[i][0];
        int v2 = graph[i][1];
        v[idx] = v2;
        ne[idx] = head[v1];
        head[v1] = idx++;
    }

    // topological seq
    vector<int> topo_result;
    queue<int> que;
    vector<bool> visited(n, false);
    que.push(0);
    visited[0] = true;
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        topo_result.push_back(cur);
        // push all adjacent vertexes
        for (int p = head[cur]; p != -1; p = ne[p]) {
            int j = v[p];
            if (!visited[j]) {
                que.push(j);
                visited[j] = true;
            }
        }
    }

    return topo_result;
}

/**
 * @brief topological sort
 *
 * @param n
 * @param graph
 * @return vector<int>
 */
vector<int> topoSort(int n, vector<vector<int>>& graph) {
    int max_n = 1e5 + 10;
    int idx = 0;
    vector<int> head(n, -1);
    vector<int> id(n, 0);   // id: input degree
    vector<int> ne(max_n, -1);
    vector<int> v(max_n, 0);

    for (int i = 0; i < graph.size(); i++) {
        int a = graph[i][0];
        int b = graph[i][1];
        v[idx] = b;
        ne[idx] = head[a];
        head[a] = idx++;
        id[b]++;
    }

    queue<int> que;
    vector<int> topo;
    // topo: push all nodes with input degree of 0
    for (int i = 0; i < n; i++) {
        if (id[i] == 0) {
            que.push(i);
        }
    }

    while (!que.empty()) {
        // solve by level
        int sz = que.size();
        for (int i = 0; i < sz; i++) {
            int cur = que.front();
            que.pop();
            topo.push_back(cur);
            // update;
            for (int p = head[cur]; p != -1; p = ne[p]) {
                int j = v[p];
                id[j]--;
                if (id[j] == 0) {
                    que.push(j);
                }
            }
        }
    }

    if (topo.size() < n) {
        // if it is not a valid topo sort seq
        return {-1};
    } else {
        return topo;
    }
}

/**
 * @brief naive dijkstra
 *
 * @param n
 * @param graph
 * @return int
 */
int minPathDijkstra(int n, vector<vector<int>>& graph) {
    int N = n + 1;
    int inf = 1e6;
    vector<vector<int>> g(N, vector<int>(N, inf));

    // construct adjacency matrix
    for (int i = 0; i < graph.size(); i++) {
        int aa = graph[i][0];
        int bb = graph[i][1];
        int wt = graph[i][2];
        g[aa][bb] = min(g[aa][bb], wt);   // avoid repeat weight
    }

    vector<int> dist(N, inf);
    vector<bool> st(N, false);
    dist[1] = 0;
    // iteration
    for (int i = 0; i < n; i++) {
        // find idx of min of dist[] not in 'st[]'
        int ver = -1;
        for (int j = 1; j <= n; j++) {
            if (!st[j] && (ver == -1 || dist[j] < dist[ver])) {
                ver = j;
            }
        }

        // update all vertexes which are directly connected to ver
        for (int j = 1; j <= n; j++) {
            if (g[ver][j] != inf) {
                dist[j] = min(dist[j], dist[ver] + g[ver][j]);
            }
        }

        st[ver] = true;
    }

    return dist[n] == inf ? -1 : dist[n];
}

/**
 * @brief use a heap to maintain the min of `nst[]`
 *
 * @param n
 * @param graph
 * @return int
 */
int minPathDijkstraHeap(int n, vector<vector<int>>& edges) {
    int N = n + 1;
    int m = edges.size();
    int inf = 1e6;
    int idx = 0;
    vector<int> head(N, -1);
    vector<int> v(m, 0);
    vector<int> w(m, inf);
    vector<int> ne(m, -1);

    // construct adjacency list
    for (int i = 0; i < edges.size(); i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        int wt = edges[i][2];
        v[idx] = bb;
        w[idx] = wt;
        ne[idx] = head[aa];
        head[aa] = idx++;
    }

    // iteration
    vector<int> dist(N, inf);
    vector<bool> st(N, false);
    dist[1] = 0;
    typedef pair<int, int> PII;   // {dist[i], i}
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({dist[1], 1});

    while (!pq.empty()) {
        PII t = pq.top();
        pq.pop();
        int ver = t.second;

        if (st[ver]) continue;   // if ver has been selected, continue
        st[ver] = true;

        // update connected vertexes
        for (int p = head[ver]; p != -1; p = ne[p]) {
            int j = v[p];
            if (!st[j] && dist[ver] + w[p] < dist[j]) {
                dist[j] = dist[ver] + w[p];
                pq.push({dist[j], j});   // may cause redundancy
                                         // like many {4, inf}, {4, inf} may in pq in the same time
                                         // but it is not a big deal, since we will pop it in 'if (!st[ver])'
            }
        }
    }

    return dist[n] == inf ? -1 : dist[n];
}

/**
 * @brief min path from 0 to i with at most k edges.
 *
 * backup: backup the result of dist[] when updated last time.
 *     To keep each loop, every vertex can add only one edge, we will use a backup array to prevent continuous update
 * from happening.
 *
 * why 'dist[n - 1] >= (inf >> 1)', but not 'dist[n - 1] == inf'?
 *     Since negative edge exists, say dist[3] and dist[5] are all inf, and distance from 3 to 5 is -1. Each time,
 * dist[5] will be relaxed by vertex 3. Eventually, dist[5] may be an infinite, but not as large as 'inf' we defined
 * before.
 *
 *
 * @param n
 * @param edges
 * @param k
 * @return int
 */
int minPathBellman(int n, vector<vector<int>>& edges, int limit) {
    int inf = 1e5;
    vector<int> dist(n, inf);
    dist[0] = 0;

    for (int i = 0; i < limit; i++) {
        vector<int> backup(dist.begin(), dist.end());   // prevent continuous update
        for (int j = 0; j < edges.size(); j++) {
            int a = edges[i][0];
            int b = edges[i][1];
            int w = edges[i][2];
            dist[b] = min(backup[b], backup[a] + w);
        }
    }

    if (dist[n - 1] >= (inf >> 1)) {   // weird!
        return -1;
    }
    return dist[n - 1];
}

/**
 * @brief
 *
 * @param n
 * @param edges
 * @return int
 */
int minPathSPFA(int n, vector<vector<int>>& edges) {
    int m = edges.size() + 10;
    int idx = 0;
    vector<int> h(n + 1, -1);
    vector<int> v(m, 0);
    vector<int> w(m, 0);
    vector<int> ne(m, -1);

    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int weight = edges[i][2];
        v[idx] = b;
        w[idx] = weight;   // weight of a -> b
        ne[idx] = h[a];
        h[a] = idx++;
    }

    int inf = 1e6;
    vector<int> dist(n + 1, inf);
    vector<bool> st(n + 1, false);   // prevent there are multiple edges on two adjacent vertexes.
    queue<int> que;
    // push origin vertex into queue
    dist[1] = 0;
    que.push(1);
    st[1] = true;
    while (!que.empty()) {
        int ver = que.front();
        que.pop();
        st[ver] = false;
        // relaxation
        for (int p = h[ver]; p != -1; p = ne[p]) {
            int j = v[p];
            if (dist[ver] + w[p] < dist[j]) {
                dist[j] = dist[ver] + w[p];
                if (!st[j]) {
                    que.push(j);
                    st[j] = true;
                }
            }
        }
    }

    // no chance in SPFA that inf vertex relaxes inf vertex
    if (dist[n] == inf) return -1;
    return dist[n];
}

/**
 * @brief
 *
 * @param n
 * @param edges
 * @return true
 * @return false
 */
bool checkNegativeLoopWithSPFA(int n, vector<vector<int>>& edges) {
    int m = edges.size();
    int idx = 0;
    vector<int> h(n + 1, -1);
    vector<int> v(m, 0);
    vector<int> w(m, 0);
    vector<int> ne(m, -1);
    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int weight = edges[i][2];
        v[idx] = b;
        w[idx] = weight;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    int inf = 1e6;
    vector<int> dist(n + 1, inf);
    vector<bool> st(n + 1, false);
    vector<int> counter(n + 1, 0);   // count how many edges on the min path of a vertex
    queue<int> q;
    // negative loop may start from any vertex
    for (int i = 1; i <= n; i++) {
        q.push(i);
        st[i] = true;
    }
    while (!q.empty()) {
        int ver = q.front();
        q.pop();
        st[ver] = false;
        // relax adjacent vertexes
        for (int p = h[ver]; p != -1; p = ne[p]) {
            int j = v[p];
            if (dist[ver] + w[p] < dist[j]) {
                dist[j] = dist[ver] + w[p];
                counter[j] = counter[ver] + 1;
                if (counter[j] >= n) return true;
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    return false;
}

/**
 * @brief with path length control
 *
 * @param n
 * @param edges
 * @param k
 * @return int
 */
int minPathSPFAWithControl(int n, vector<vector<int>>& edges, int limit) {
    int m = edges.size() + 10;
    int idx = 0;
    vector<int> h(n + 1, -1);
    vector<int> v(m, 0);
    vector<int> w(m, 0);
    vector<int> ne(m, -1);

    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int weight = edges[i][2];
        v[idx] = b;
        w[idx] = weight;   // weight of a -> b
        ne[idx] = h[a];
        h[a] = idx++;
    }

    int inf = 1e6;
    vector<int> dist(n + 1, inf);
    queue<int> que;
    // push origin vertex into queue
    dist[1] = 0;
    que.push(1);
    int nEdge = 0;
    while (!que.empty()) {
        nEdge++;
        if (nEdge > limit) break;   // control path length
        int sz = que.size();
        for (int k = 0; k < sz; k++) {   // solve by level
            int ver = que.front();
            que.pop();
            vector<int> backup(dist.begin(), dist.end());
            vector<bool> st(n + 1, false);
            // relaxation
            for (int p = h[ver]; p != -1; p = ne[p]) {
                int j = v[p];
                if (backup[ver] + w[p] < dist[j]) {
                    dist[j] = backup[ver] + w[p];
                    if (!st[j]) {
                        que.push(j);
                        st[j] = true;
                    }
                }
            }
        }
    }

    // no chance in SPFA that inf vertex relaxes inf vertex
    if (dist[n] == inf) return -1;
    return dist[n];
}

/**
 * @brief
 *
 * @param n
 * @param edges
 * @return int
 */
int minPathFloyd(int n, vector<vector<int>>& edges) {
    int N = n + 1;
    int inf = 1e6;
    vector<vector<int>> d(N, vector<int>(N, inf));
    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int weight = edges[i][2];
        d[a][b] = min(d[a][b], weight);   // avoid repeated weights on the same edge
    }

    // floyd
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    // same problem with bellman, brute-force relaxation may cause inf relaxes inf
    if (d[1][n] > (inf >> 1)) return -1;
    return d[1][n];
}

/**
 * @brief return the total length of the spinning graph
 *
 * for (int i = 0; i < n; i++) {
 *     ...
 *     if (i)
 *     ...
 * }
 *
 * if (i) is a trick to treat the first iteration (i == 0).
 *
 * @param n
 * @param edges
 * @return int
 */
int minSpinningGraphPrim(int n, vector<vector<int>>& edges) {
    int N = n + 1;
    int inf = 1e6;
    vector<vector<int>> g(N, vector<int>(N, inf));

    for (int i = 0; i < edges.size(); i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        int wt = edges[i][2];
        g[aa][bb] = g[bb][aa] = min(g[aa][bb], wt);
    }

    // Prim
    vector<int> dist(N, inf);
    vector<bool> st(N, false);   // in spinning graph?
    int res = 0;
    for (int i = 0; i < n; i++) {
        // find t
        int ver = 0;
        for (int j = 1; j <= n; j++) {
            // skip ver == 0 in first loop
            if (!st[j] && (ver == 0 || dist[j] < dist[ver])) {
                ver = j;
            }
        }

        // if (i) skip the first vertex (iteration)
        // no connection from ver to spinning graph
        if (i && dist[ver] == inf) return -1;

        // add into the spinning graph
        st[ver] = true;
        if (i) res += dist[ver];

        // update adjacent vertexes
        for (int j = 1; j <= n; j++) {
            if (!st[j] && g[ver][j] < dist[j]) {
                dist[j] = g[ver][j];
            }
        }
    }

    return res;
}

const int MAX_N = 1e5;
class UDSet {
   public:
    int p[MAX_N];
    UDSet(int m) {
        // 1-based
        for (int i = 1; i <= m; i++) {
            p[i] = i;
        }
    }

    int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }

    void join(int x, int y) { p[find(x)] = find(y); }
};

/**
 * @brief
 *
 * @param n
 * @param edges
 * @return int: weight of min spinning graph
 */
int minSpinningGraphKruskal(int n, vector<vector<int>>& edges) {
    int m = edges.size();
    struct Edge {
        int a, b, w;
        // overwrite less sign
        bool operator<(const Edge& e) const { return w < e.w; }
    } e[m];

    // sort
    sort(e, e + m);

    UDSet uds(m);
    int res = 0;
    int cnt_edges = 0;
    // enumerate all edges from shortest to longest
    for (int i = 0; i < m; i++) {
        int aa = e[i].a;
        int bb = e[i].b;
        int wt = e[i].w;
        if (uds.find(aa) != uds.find(bb)) {
            // not connected
            uds.join(aa, bb);
            res += wt;
            cnt_edges++;
        }
    }

    if (cnt_edges < n - 1) return -1;
    return res;
}

bool colorize(vector<int>& h, vector<int>& v, vector<int>& ne, vector<int>& color, int ver, int col) {
    color[ver] = col;
    bool suc = true;
    for (int p = h[ver]; p != -1; p = ne[p]) {
        int j = v[p];
        if (!color[j]) {
            suc = colorize(h, v, ne, color, j, 3 - col);
            if (!suc) {
                return false;
            }
        } else {
            // if colorized and it cannot be same color as ver
            if (color[j] == col) {
                return false;
            }
        }
    }

    return true;
}

bool isBipartiteGraph(int n, vector<vector<int>>& edges) {
    int N = n + 1;
    int m = edges.size();
    int idx = 0;
    vector<int> h(N, -1);
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

    vector<int> color(N, 0);   // 0: no color, 1: color 1, 2: color 2
    int suc = true;
    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            suc = colorize(h, v, ne, color, i, 1);
            if (!suc) {
                return false;
            }
        }
    }

    return true;
}

bool find(vector<int>& h, vector<int>& v, vector<int>& ne, vector<int>& match, vector<bool>& st, int ver) {
    for (int p = h[ver]; p != -1; p = ne[p]) {
        int j = v[p];
        if (!st[j]) {
            st[j] = true;
            if (match[j] == -1 || find(h, v, ne, match, st, match[j])) {
                match[j] = ver;
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief
 *
 * @param n1
 * @param n2
 * @param edges
 * @return int
 */
int maxBipartiteGraph(int n1, int n2, vector<vector<int>>& edges) {
    int N1 = n1 + 1;
    int N2 = n2 + 1;
    int m = edges.size();
    int idx = 0;
    vector<int> h(N1, -1);   // left set points to right set
    vector<int> v(m, 0);
    vector<int> ne(m, -1);
    for (int i = 0; i < m; i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
    }

    vector<int> match(N2, -1);   // match[i] means right i's match vertex on the left
    int res = 0;
    for (int i = 1; i <= n1; i++) {
        vector<bool> st(N2, false);
        if (find(h, v, ne, match, st, i)) {
            res++;
        }
    }

    return res;
}