# Search

## Depth First Search

### N Queens

> The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
>
> Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
>
> Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

One trick in N-Queens is the representation of diagonal line and anti-diagonal line. One fact is that diagonal line is indexed by y-distance of a x-y plane.

```text
    0  1  2  3  4
 0  a
 1   b c 
 2      d e
 3         f g
 4            h i
```

For an anti-diagonal line `y = -x + b`, we got `b = x + y`. So, `Grid[i][j]` is in `AntiDiag[i + j]`. For a diagonal line `y = x + b`, we got `b = -x + y`, but `b` should be non-negative. `b = -x + y + max(N, M)` for any rectangular (`b = -x + y + N or M` for a square), where `N` represents column, and `M` row.

We use `col[]`, `row[]`, `diag[]`, `anti_diag[]` to record if there is a queen on that line.

```c++
void NQueensHelper(vector<vector<string>>& res, vector<string>& attempt, vector<bool>& row, vector<bool>& col, vector<bool>& diag,
                   vector<bool>& anti_diag, int n, int i) {
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
```

### Find if Path Exists in Graph

> There is a bi-directional graph with `n` vertices, where each vertex is labeled from `0` to `n - 1` (inclusive). The edges in the graph are represented as a 2D integer array edges, where each `edges[i] = [ui, vi]` denotes a bi-directional edge between vertex `ui` and vertex `vi`. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
>
> You want to determine if there is a valid path that exists from vertex source to vertex destination.
>
> Given edges and the integers `n`, source, and destination, return true if there is a valid path from source to destination, or false otherwise.

DFS to find path. Label visited vertexes if it has been tried.

```c++
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
```

### All Paths From Source to Target

> Given a directed acyclic graph (DAG) of `n` nodes labeled from `0` to `n - 1`, find all possible paths from node `0` to node `n - 1` and return them in any order.
>
> The graph is given as follows: `graph[i]` is a list of all nodes you can visit from node `i` (i.e., there is a directed edge from node `i` to node `graph[i][j]`).

Notice that `graph` is actually a adjacency list.

```c++
void pathSearch(vector<vector<int>>& graph, int src, int dst, vector<bool>& st, vector<int>& path, vector<vector<int>>& res) {
    if (src == dst) {
        res.push_back(path);
        return;
    }

    st[src] = true;   // label
    for (auto v : graph[src]) {
        if (!st[v]) {
            path.push_back(v);
            pathSearch(graph, v, dst, st, path, res);
            path.pop_back();   // restore
        }
    }
    st[src] = false;   // undo label

    return;
}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    vector<vector<int>> res;
    vector<int> path = {0};
    vector<bool> st(graph.size(), false);
    pathSearch(graph, 0, graph.size() - 1, st, path, res);
    return res;
}
```

Tricks:

- `st[]` only needed in undirected graph.

IMPORTANT: DIFFERENCE between finding all paths and one path.

- `st[]` is used for preventing infinite loop in the case of bi-directional graph for both cases. But we need restore the state of `st[]` in finding all paths. If not, we cannot use nodes in found path for finding new path.

### Clone Graph

> Given a reference of a node in a connected undirected graph.
>
> Return a deep copy (clone) of the graph.
>
> Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.

Following code explains why `st[]` is not sufficient in cloning a graph, since when a vertex has been cloned, we have no idea where it is (pointer) and get lost.

```c++
// BAD CODE
Node* cloneGraphHelper(vector<bool>& st, Node* node) {
    if (node == nullptr) return nullptr;
    if (st[node->val]) return ???;   // <---
    st[node->val] = true;   // if the node has been cloned

    Node* clone = new Node(node->val);

    for (int i = 0; i < node->neighbors.size(); i++) {
        Node* neighborClone = cloneGraphHelper(st, node->neighbors[i]);
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
    vector<bool> st(N, false);
    Node* clone = cloneGraphHelper(st, node);

    return clone;
}
```

To store the corresponding clone vertex, we will create a map `copyOf` to replace `st`, mapping from node in graph to node in clone graph.

```c++
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

Node* cloneGraph(Node* node) {
    int N = 110;
    unordered_map<Node*, Node*> copyOf;
    Node* clone = cloneGraphHelper(copyOf, node);

    return clone;
}
```

### All Paths from Source Lead to Destination

> Given the edges of a directed graph where `edges[i] = [ai, bi]` indicates there is an edge between nodes `ai` and `bi`, and two nodes source and destination of this graph, determine whether or not all paths starting from source eventually end at destination, that is:
>
> - At least one path exists from the source node to the destination node.
> - If a path exists from the source node to a node with no outgoing edges, then that node is equal to destination.
> - The number of possible paths from source to destination is a finite number.
>
> Return true if and only if all roads from source lead to destination.

DFS finds all paths. If there is a path not ending with destination, return false.

The basic idea is: all paths from `source` to `destination` is true if all paths from source's neighbors to `destination` are true, and false otherwise.

```c++
bool allPathsToDst(vector<int>& h, vector<int>& v, vector<int>& ne, vector<bool>& st, int src, int dst) {
    // destination and target
    if (h[src] == -1 && src == dst) {
        return true;
    }
    // destination but not target
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
```

Tricks:

- Check if a vertex (node) is a destination (out degree is zero).

## Breadth First Search

### Find Min Path

> Find a min path from (0, 0) to the right bottom point.

This is a classic BFS problem and there is a lot of details to take into consideration.

```c++
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

    // print path in reverse order
    for (int i = 0; i < path.size(); i++) {
        cout << "(" << path[i].x << ", " << path[i].y << ")" << endl;
    }
    cout << endl;

    return dis[m - 1][n - 1];   // or path.size() - 1 (minus (0, 0))
}
```

Tricks:

- record path by making a stamp on each point to indicate its previous point.
- direction vector.

### Find if Path Exists in Graph BFS

> There is a bi-directional graph with `n` vertices, where each vertex is labeled from `0` to `n - 1` (inclusive). The edges in the graph are represented as a 2D integer array edges, where each `edges[i] = [ui, vi]` denotes a bi-directional edge between vertex `ui` and vertex `vi`. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
>
> You want to determine if there is a valid path that exists from vertex source to vertex destination.
>
> Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.

BFS finds path.

```c++
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
```

### All Paths From Source to Target BFS

> Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1, find all possible paths from node 0 to node n - 1 and return them in any order.
>
> The graph is given as follows: `graph[i]` is a list of all nodes you can visit from node i (i.e., there is a directed edge from node i to node `graph[i][j]`).

Notice that BFS searches all paths only works for DAG in following code: (what we push into the queue is path not vertex)

```c++
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
```

### Populating Next Right Pointers in Each Node

> You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. 
> Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Tree is a special graph. Level order traversal is actually BFS in graph.

```c++
Node* connect(Node* root) {
    queue<Node*> que;
    que.push(root);
    while (!que.empty()) {
        int sz = que.size();
        for (int i = 0; i < sz; i++) {
            Node* cur = que.front();
            que.pop();
            if (cur == nullptr) continue;
            if (i != sz - 1) cur->next = que.front();
            que.push(cur->left);
            que.push(cur->right);
        }
    }
    
    return root;
}
```

### Shortest Path in Binary Matrix

> Given an `n x n` binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return `-1`.
>
> A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
>
> - All the visited cells of the path are 0.
> - All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
>
> The length of a clear path is the number of visited cells of this path.

BFS to find shortest path.

```c++
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
```

### N-ary Tree Level Order Traversal

> Given an n-ary tree, return the level order traversal of its nodes' values.
>
> Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

Output the level order traversal of N-ary tree.

```c++
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
            for (Node* child : cur->children) {
                if (child != nullptr) {
                    que.push(child);
                    levelNodes.push_back(child->val);
                }
            }
        }
    }

    return res;
}
```

### Rotting Oranges

> You are given an m x n grid where each cell can have one of three values:
>
> - 0 representing an empty cell,
> - 1 representing a fresh orange, or
> - 2 representing a rotten orange.
>
> Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
>
> Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

BFS labels each level (minute).

```c++
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
```

## Graph

### Representation

There are two ways to represent a graph.

- Adjacency Matrix

Store the graph with a N * N matrix, where N is the number of vertexes.

- Adjacency List

Store the graph with N lists, each list represents all adjacent vertexes that directly connect to the head vertex.

Recall that the simplified representation of a single linked list:

- `head = -1`, where `-1` means NULL index.
- `idx = 0`, which indicate the index of memory waiting to be allocated.
- `v[]`, represents the value of a node.
- `ne[]`, represents the next pointer of a node. (all nodes are indexed by index).

```c++
void head_insert(int val) {
    v[idx] = val;
    ne[idx] = head;
    head = idx++; // head = idx; idx++;
}

void traverse() {
    for (int p = head; p != -1; p = ne[p]) {
        // do something to v[i]
    }
}
```

Array-like linked list shows its power in adjacency list. Since there are N vertexes, we need N heads.

- `head[] = -1`, where `-1` means NULL **index**. Max size of `head[]` is N.
- `idx = 0`, which indicate the **index** of memory waiting to be allocated.
- `v[]`, represents the value of a node. (**val**)
- `ne[]`, represents the next pointer of a node. (all nodes are indexed by **index**).

```c++
// insert an edge from a to b
void edge_insert(int a, int b) {
    v[idx] = b;
    ne[idx] = head[a];
    head[a] = idx++;
}
```

- DFS for a graph

```c++
vector<bool> visited;
void dfs(int root) {
    if (visited[root]) return;

    for (int i = head[root]; i != -1; i = ne[i]) {
        int j = v[i];
        dfs(j);   // where features dfs
    }

    visited[root] = true;
}
```

### Center of Gravity

> Center of gravity of a tree means the node which can divide tree into N parts. Each part has a number of nodes, center of gravity node will divide the tree so that the maximum number of nodes in parts is minimal.

The basic idea is how to calculate the number of nodes in different parts when deleting a node.

One benefit of dfs is that we can calculate the number of nodes of a part. For example, for a tree, the number of nodes equals to the number of left subtree plus the number of right subtree and `1`.

```c++
void edge_insert(vector<int>& head, vector<int>& v, vector<int>& ne, int& idx, int a, int b) {
    v[idx] = b;         // val
    ne[idx] = head[a];  // index
    head[a] = idx++;    // index
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
    int max_size = 1e5 + 10;   // or 2 * m (graph.size())
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
```

`gravityHelper` func will return the number of nodes in subtree on `root`, and calculating the max size of parts when deleting that node.

```c++
// return the size of tree with root `root`
int gravityHelper(vector<int>& head, vector<int>& v, vector<int>& ne, vector<bool>& visited, int& min_size,
                  int& gravity_node, int n, int root) {
    if (visited[root]) return 0;
    visited[root] = true;

    int sum = 1;   // root node
    int max_part = 0;
    for (int i = head[root]; i != -1; i = ne[i]) {
        int j = v[i];
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
```

### Topological Sort

Corresponding to topological sort, we will talk about the bfs of a graph from an entry point (which we call pseudo topo traversal).

```c++
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
```

- Topo Sort

The basic algorithm is:

- find all nodes with input degree of 0.
- delete those nodes and update input degree of nodes being affected by the operation above.
- repeat step 1.

```c++
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
```

## Min Path

### Overview

`n` is the number of vertexes, and `m` is the number of edges.

- Single Origin
    - all weights are positive:
        1. naive dijkstra algorithm (for dense graph, O(n^2))
        2. heapfied dijkstra (for sparse graph, O(m * logn)).
    - otherwise:
        1. bellman-ford (O(n*m))
        2. SPFA (avg. O(m), worst O(n*m))
- Multiple Origin
    - floyd algorithm (O(n^3))

Note: dense graph: `m ~ n^2` (adjacency matrix), sparse graph: `m ~ n` (adjacency list), where `~` represents the magnitude of `m`.

The core idea here is to model the problem, i.e. how to abstract the problem as a graph problem.

### Dijkstra Algorithm

Dijkstra algorithm is a greedy algorithm. The idea of the algorithm is the min path from origin to `i` has two possibles: 1. direct connection from origin to path (may not exist, `-inf`), 2. the min path of `i`s neighbors plus the distance from `i`s neighbor to `i`.

- `dist[i]` represents the minimum path from origin to `i`.
- `st[]` represents all vertexes whose min path have been ensured (selected), and `nst[]` represents all vertexes whose min path have not been ensured (`nst[]` can be ignored since `whole - st[] = nst[]`).

One short tip: why choose the minimum of `dist[i]` where `i` from uncertain sets `nst[]` each loop? Because the minimum vertex of uncertain set can not be optimized further.

```text
all nodes have been divided into two parts

st[]:  1  5  8  3  0
nst[]: 4  7  3  9
where st[i] and nst[i] are label of a vertex.

say vertex labeled with 4 is the minimum distance in nst[].
```

We have some facts worth being discussed:

- `dist[4], dist[7], dist[3], dist[9]` are the minimum distance currently (even though they may be not the ultimate shortest distance), meaning minimum distance after optimization of vertexes `1, 5, 8, 3, 0`.
- `dist[4]` is the minimum one (assumed). Since it is the minimum one in `ust[]`, other vertexes in `ust[]` cannot be used to optimize `dist[4]`. For example, `dist[7] + distance[7][4] > dist[4]` since `dist[7] >= dist[4]` and `distance[7][4] > 0`.

So, the ultimate minimal distance of vertex 4 can be ensured in this round.

Pseudo code for Dijkstra algorithm is:

```text
1. dist[0] = 0; dist[v] = inf
2. for v : 0 ~ n-1
        t <- v not in st[] and dist[v] is the minimum  O(n)
        st <- t   // put the vertex into st, this vertex is ensured  O(1)
        dist[i] = min(dist[i], dist[v] + edge[v][i])   // update dist[i], where vertex i is directly connected to t, O(m)

each loop, one vertex will be ensured.
```

```c++
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
```

- Heap Optimization

For the algorithm above:

```text
1. dist[0] = 0; dist[v] = inf
2. for v : 0 ~ n-1
        t <- v not in st[] and dist[v] is the minimum  O(n * n)
        st <- t   // put the vertex into st, this vertex is ensured  O(n * 1)
        dist[i] = min(dist[i], dist[v] + edge[v][i])   // update dist[i], where vertex i is directly connected to t, O(n * m), where m ~ n^2

each loop, one vertex will be ensured.

notice that: traverse edges of each vertexes is equal to traverse all edges.
```

where first `n` is caused by outer loop. In a dense graph, `m ~ n^2` and so the total time complexity is `O(n^3)`.

If we save `nst[]` with a heap and find min vertex with heap, then the time complexity will be:

```text
1. dist[0] = 0; dist[v] = inf
2. for v : 0 ~ n-1
        t <- v not in st[] and dist[v] is the minimum  O(n * 1)
        st <- t   // put the vertex into st, this vertex is ensured  O(n * 1)
        dist[i] = min(dist[i], dist[v] + edge[v][i])   // update dist[i], where vertex i is directly connected to t, O(n * mlogn), where m ~ n

each loop, one vertex will be ensured.
```

In a sparse graph, `m ~ n`, so the total time complexity will be `O(n^2*logn)`. Note since it is a sparse graph, we will use adjacency list to represent the graph.

A trick for priority queue: the elements in priority queue will be ordered by `pair.first`.

```c++
// max heap
#include <queue>
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;

int main(int argc, char *argv[]) {
    priority_queue<PII> pq;   // max heap
    // priority_queue<PII, vector<PII>, greater<PII>> pq;   // min heap: greater means children are greater than the parent
    pq.push({2, 0});
    pq.push({5, 1});
    pq.push({3, 2});
    pq.push({1, 3});
    while (!pq.empty()) {
        PII cur = pq.top();
        pq.pop();
        printf("%d\n", cur.first);
    }
    
    return 0;
}
```

The code of optimized Dijkstra:

```c++
int minPathDijkstraHeap(int n, vector<vector<int>>& edges) {
    int N = n + 1;
    int m = edges.size();
    int inf = 1e9;
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
```

- TRICK: a general way to use priority queue.

The first is as shown in `Heap` section. We will define greater function by ourselves.

```c++
class Word {
    public:
    Word(int _freq, string _word)
    : freq(_freq), word(_word) {};
    
    int freq;
    string word;
};

int main(int argc, char *argv[]) {
    vector<Word> dict;
    dict.push_back(Word{5, "hello"});
    dict.push_back(Word{3, "world"});
    dict.push_back(Word{7, "minzhi"});
    
    // lhs and rhs have the type of Word
    auto cmp = [&dict](auto lhs, auto rhs) {
        return lhs.freq > rhs.freq;
    };
    // l and r children greater than parent
    priority_queue<Word, vector<Word>, decltype(cmp)> pq(cmp);
    
    for (int i = 0; i < dict.size(); i++) {
        pq.push(dict[i]);   // push Word it self
    }
    
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        cout << cur.word << " " << cur.freq << endl;
    }
    
    return 0;
}
```

The second implementation is used in heapified Dijkstra algorithm, where we create a pair for `{val_to_compare, idx}`. We do not need to put all members of a type into a priority queue but put two key values: 1. value to compare, 2. correlated index. We will use `idx` to index the element of a special type. `pair` is ordered by `pair.first` by default.

```c++
class Word {
    public:
    Word(int _freq, string _word)
    : freq(_freq), word(_word) {};
    
    int freq;
    string word;
};

typedef pair<int, int> PII;

int main(int argc, char *argv[]) {
    vector<Word> dict;
    dict.push_back(Word{5, "hello"});
    dict.push_back(Word{3, "world"});
    dict.push_back(Word{7, "minzhi"});
    
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    
    for (int i = 0; i < dict.size(); i++) {
        pq.push({dict[i].freq, i});   // push pair
    }
    
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int idx = cur.second;
        int freq = cur.first;
        cout << dict[idx].word << " " << freq << endl;
    }
    
    return 0;
}
```

### Bellman-Ford Algorithm

Notice that negative path is allowed in Bellman-Ford algorithm. But when using it, we need to detect if there is a negative loop on the path from origin to end. If so, the min distance from origin to end becomes `-inf`, meaning it does not exist.

How to understand Bellman-Ford Algorithm?

```text
for v in all vertexes except origin  // iterate n - 1 times
    for e in all edges   // e: a -> b with weight w
        dist[b] = min(dist[b], dist[a] + w)   // relax

dist[i] represents the min path from origin to ith vertex so far.
```

**IMPORTANT: after kth outmost loop, we got the min path from origin to ith vertex through at most k edges.** Each time we relax a vertex with an edge, then number of the edge on the min path add `1` if relaxation succeeds (`dist[b] > dist[a] + w`, so the min path must include `edge[a][b]`).

**This (Controlling K) is how Bellman-Ford algorithm solves negative edges.**

- Min Path with at most K edges

> return the min distance from origin to target vertex with at most k edges. (weight may be negative and there may be negative loop)

```c++
/**
 * @brief min path from 0 to i with at most k edges.
 * 
 * backup: backup the result of dist[] when updated last time.
 *     To keep each loop, every vertex can add only one edge, we will use a backup array to prevent continuous update from happening.
 * 
 * why 'dist[n - 1] >= (inf >> 1)', but not 'dist[n - 1] == inf'?
 *     Since negative edge exists, say dist[3] and dist[5] are all inf, and distance from 3 to 5 is -1. Each time, dist[5] will be 
 * relaxed by vertex 3. Eventually, dist[5] may be an infinite, but not as large as 'inf' we defined before.
 * 
 * 
 * @param n 
 * @param edges 
 * @param k 
 * @return int 
 */
int minPathBellman(int n, vector<vector<int>>& edges, int k) {
    int inf = 1e5;
    vector<int> dist(n, inf);
    dist[0] = 0;

    for (int i = 0; i < k; i++) {
        vector<int> backup(dist.begin(), dist.end());  // prevent continuous update which breaks our control on k
        for (int j = 0; j < edges.size(); j++) {
            int a = edges[i][0];
            int b = edges[i][1];
            int w = edges[i][2];
            dist[b] = min(backup[b], backup[a] + w);
        }
    }

    if (dist[n - 1] >= (inf >> 1)) {   // negative edge!
        return -1;
    } else {
        return dist[n - 1];
    }
}
```

- SPFA for min path with at most k edges (ONLY WORKS FOR POSITIVE GRAPH)

Notice SPFA update in a heuristic way, meaning update those should be updated, whereas Bellman-Ford relaxes vertexes without any constraint, which may causing vertex(a) update vertex(b) when there is a negative edge between them even though both `dist[a]` and `dist[b]` are `inf`.

```text
             dist[a] = inf
   +--..........................--- a
origin                              | -10
   +--..........................--- b
             dist[b] = inf

for each loop, dist[b] = dist[a] - 10 = inf - 10
it is even worth when there is a edge from b to a with weight -10 (meaning negative loop), in that case, dist[a] or dist[b] may be go down to a negative number. Bellman-Ford algorithm prevent that from happening.
```

### SPFA

Shortest Path Faster Algorithm (SPFA) is an optimized Bellman-Ford algorithm.

First, let's see where can be optimized in Bellman-Ford algorithm.

```text
for v in all vertexes except origin   // n - 1 times
    for e in all edges   // <-- trivial
        dist[b] = min(dist[b], dist[a] + w)   // relax

dist[i] represents the min path from origin to ith vertex so far.
```

We do not need to traverse all edges. Recall from Dijkstra algorithm, we just need to update correlated vertexes with newly-updated vertexes (correlated means directly connection or adjacent vertex).

With this idea in mind, we will use a `queue` to store those newly-updated vertex which will be used to update their adjacent vertexes.

```text
for v in all vertexes except origin
    while queue not empty
        for v in queue   // solve by level (round)
            for e in adjacent edges of v   // like bfs
                dist[adjacent vertex] = min(dist[adjacent vertex], dist[v] + w)
                queue <-- adjacent vertex if dist[adjacent vertex] is updated
```

- Basic SPFA (without negative loop control -> infinite loop)

Basic SPFA is not recommended. We prefer solve by level (SPFA with edge control).

```c++
int minPathSPFA(int n, vector<vector<int>>& edges) {
    int N = n + 1;
    int m = edges.size() + 10;
    int idx = 0;
    vector<int> h(n + 1, -1);
    vector<int> v(m, 0);
    vector<int> w(m, 0);
    vector<int> ne(m, -1);

    for (int i = 0; i < edges.size(); i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        int wt = edges[i][2];
        v[idx] = bb;
        w[idx] = wt;   // weight of a -> b
        ne[idx] = h[aa];
        h[aa] = idx++;
    }

    int inf = 1e6;
    vector<int> dist(N, inf);
    vector<bool> st(N, false);
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
```

IMPORTANT: `st[]` is used for track if a vertex is in the queue as a newly-updated vertex, but why `st[]`? KEEP UNIQUE.

Imagine following case:

```text
vertex: 1  2  3
 edges:      weight
        1  2  2
        1  2  5
        1  2  6
        1  2  7
        ...
        1  2  100000
        1  3  5
        2  3  1

answer: dist[3] = 4

When using vertex 1 to relax 2, 2 will be pushed into queue nearly 100000 times, which is horrible.
```

To fix the problem above, we keep to relax two vertexes with multiple edges (`dist[j] = dist[ver] + w[p]`) and only one end vertex (`bb`) is put into the queue (`if (!st[j]) {...}`).

```c++
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
```

Without `st[]` to track if vertex 1 is in the queue, nearly 100000 repeated 1 will be in the queue. The time complexity is `O(mul(k[i]))`, `k[i]` is the number of adjacent edges (including repeats) vertex `i` has. With `st[]`, we can reduce repeats to unique path.

- SPFA with negative loop check

If `num of edges of a path > num of total vertexes`, there exists a negative loop in the graph.

NOTE: the negative loop may be not connected with vertex 1, so we have to try all vertexes, and we do not care about the value of `dist[]`, so we do not need initialize min distance of origin point as we did before.

```c++
bool checkNegativeLoopWithSPFA(int n, vector<vector<int>>& edges) {
    int N = n + 1;
    int m = edges.size();
    int idx = 0;
    vector<int> h(N, -1);
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
    vector<int> dist(N, inf);
    vector<bool> st(N, false);
    vector<int> counter(N, 0);   // count how many edges on the min path of a vertex
    queue<int> q;
    // IMPORTANT: since negative loop may start from any vertex, not necessary to be 1
    for (int i = 1; i <= n; i++) {
        q.push(i);
        st[i] = true;
    };
    while (!q.empty()) {
        int ver = q.front();
        q.pop();
        st[ver] = false;
        // relax adjacent vertexes
        for (int p = head[ver]; p != -1; p = ne[p]) {
            int j = v[p];
            if (dist[ver] + w[p] < dist[j]) {
                dist[j] = dist[ver] + w[p];
                counter[j] = counter[ver] + 1;
                if (counter[j] >= n) return true;   // <== check
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    return false;
}
```

- SPFA with edge control

In queue, we solve the vertexes by level to control the relaxation (like bfs).

```c++
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
            vector<bool> st(n + 1, false);  // <-- IMPORTANT
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
```

### Floyd Algorithm

Floyd algorithm is used for calculate the minimum path of multi-origin problem. It applies brute-force relaxation for each vertex.

```text
for through in all vertexes
    for src in all vertexes
        for dst in all vertexes
            // relax dist[src][dst] with dist[src][trough]
            dist[src][dst] = min(dist[src][dst], dist[src][through] + w[through][dst])
```

The basic idea is from dynamic programming.

Define `f[k][i][j]` as

- problem sets: all paths from `i` to `j` through first `k` vertexes (some or all).
- property: min path.

Deduction:

- the minimum path from `i` to `j` through first `k` vertexes is minimum of
    - the min path from `i` to `j` through first `k - 1` vertexes, `f[k-1][i][j]`. (without passing through `k`th vertex)
    - the min path from `i` to `k` trough first `k - 1` vertexes plus min path from `k` to `j` through first `k - 1` vertexes, `f[k-1][i][k] + f[k-1][k][j]` (passing through `k`th vertex).

So we got `f[k][i][j] = min(f[k-1][i][j], f[k-1][i][k] + f[k-1][k][j]`. After optimizing with rotated array, we got `f[i][j] = min(f[i][j], f[i][k] + f[k][j])`.

```c++
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
```

### Network Delay Time

> You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges `times[i] = (ui, vi, wi)`, where `ui` is the source node, `vi` is the target node, and `wi` is the time it takes for a signal to travel from source to target.
>
> We will send a signal from a given node `k`. Return the time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.

Since all edges in the network graph are positive and it is an directed graph, we can solve the problem with Dijkstra algorithm.

```c++
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
```

### Cheapest Flights Within K Stops

> There are n cities connected by some number of flights. You are given an array flights where `flights[i] = [fromi, toi, pricei]` indicates that there is a flight from city `fromi` to city `toi` with cost `pricei`.
>
> You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.

If we want to control the length of path, SPFA is a great choice.

- Bellman-Ford

```c++
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    int inf = 1e9;
    vector<int> dist(n, inf);
    dist[src] = 0;
    for (int i = 0; i <= k; i++) {
        vector<int> backup(dist.begin(), dist.end());
        for (int j = 0; j < flights.size(); j++) {
            int aa = flights[j][0], bb = flights[j][1], wt = flights[j][2];
            dist[bb] = min(dist[bb], backup[aa] + wt);
        }
    }
    
    return dist[dst] >= (inf >> 1) ? -1 : dist[dst];
}
```

- SPFA

```c++
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
        vector<bool> st(n, false);   // <-- IMPORTANT
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
```

`st[]` means on ith expansion, if the newly-updated vertex is pushed into the queue.

- Reflection

If we solve the queue not by level (like basic SPFA), bug occurs.

```text
A hinge graph:
      (1)         (1)             (100)
   +-------- 1 --------+   +-----------------+
  /                     \ /                   \
 0 --------------------- 2 -------- 3 -------- 4
            (5)               (2)        (2)

k = 1: (k here means the number of edges)
    dist:  0   1   2   3   4
           0  inf inf inf inf
           0   1   5  inf inf   (updated)
     que:      1   2
k = 2:
    dist:  0   1   2   3   4
           0   1   5  inf inf
           0   1   2  inf 105   (updated)  (105 = 5 + 100 (where k = 2) but not 2 + 100 (where k = 3), why we should update with backup of dist)
     que:          2       4
k = 3:
    dist:  0   1   2   3   4
           0   1   2  inf 105
           0   1   2   4  102   <== BAD! when k = 3, the min path from 0 to 4 should be 5 + 2 + 2! Why? Since in k = 2, we update dist[2] from 5 to 2, causing the lost of path (0 - 2 with edge with weight 5)

    ... Hinge Bug Occurs
    
k = 4:
    dist:  0   1   2   3   4
           0   1   2   4  102

```

So, we need to solve it by level, where `st[]` means if the newly-updated vertexes **on the same level** are pushed in to the queue. (**IMPORTANT**)

```c++
int nEdge = 0;
while (!que.empty()) {
    nEdge++;
    if (nEdge > limit) break;   // control path length
    int sz = que.size();
    for (int k = 0; k < sz; k++) {   // solve by level
        int ver = que.front();
        que.pop();
        vector<int> backup(dist.begin(), dist.end());
        vector<bool> st(n + 1, false);   // !!! IMPORTANT
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
```

That's why `st[]` has been reset on each level.

### Path With Minimum Effort

> You are a hiker preparing for an upcoming hike. You are given `heights`, a 2D array of size rows `x` columns, where `heights[row][col]` represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
>
> A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
>
> Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

Note that all weights are positive. We can solve it with Dijkstra algorithm.

There are some problems to be solved in matrix graph:

- How to represent a vertex: use cell `(x, y)` as an identification for a vertex, and adjacent vertex can be found by the locale relation in a matrix. **The definition of `Cell` is for sorting `dist[x][y]` in priority queue according its value.**, so it encapsulates location parameters `x`, `y`, and value `minDist`.

```c++
class Cell {
    public:
    Cell(int _x, int _y, int _effort) : x(_x), y(_y), minDist(_minDist) {}
    int x, y;
    int minDist;
};
```

- How to represent min dist? `dist[][]` in matrix is a 2-d representation. `dist[i][j]` represents the minimum distance from `(0, 0)` to `(i, j)`. The meaning of `dist` is varied from one problem to another. In this problem, it represents the max difference along a path.
- How to define the `Comparator` of user-customized object for a priority queue.
- The min path should be the maximum difference along the path from `(0, 0)` to `(x, y)`, or the difference of `(x, y)` and `(nx, ny)` if it is larger. (`dist[nx][ny] = min(dist[nx][ny], max(dist[x][y], abs(heights[nx][ny] - heights[x][y])))`)

```c++
struct Comparator {
    // lhs are children of a heap and rhs is the parent
    bool operator()(const Cell& lhs, const Cell& rhs) {
        return lhs.minDist > rhs.minDist;
    }
};

int foo {
    ....
    priority_queue<Cell, vector<Cell>, Comparator> pq;
}
```

The full code is:

```c++
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
```

### Path With Maximum Minimum Value

> Given an m x n integer matrix grid, return the maximum score of a path starting at (0, 0) and ending at (m - 1, n - 1) moving in the 4 cardinal directions.
>
> The score of a path is the minimum value in that path.
>
> - For example, the score of the path 8 ??? 4 ??? 5 ??? 9 is 4.

Note that all weights are positive and this is a single origin problem -> Dijkstra.

How to define distance? `dist[][]` is the **maximum** score of all the paths from `(0, 0)` to `(i, j)`. if `dist[nx][ny] < min(dist[x][y], grid[nx][ny])`, `dist[nx][ny] = min(dist[x][y], grid[nx][ny])`, i.e. the min path of `(nx, ny)` has two cases: 1. the min value from `(0, 0)` to `(x, y)` or the value of `grid[nx][ny]` if it is smaller. (max heap)

```c++
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

    const vector<int>
        dx = {-1, 1, 0, 0};
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
```

### Swim in Rising Water

> You are given an n x n integer matrix grid where each value `grid[i][j]` represents the elevation at that point `(i, j)`.
>
> The rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
>
> Return the least time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).

The `dist[][]` here means the maximum value along the path.

```text
a --> b --> c --> d
   1     8     3        dist of path = max(1, 8, 3) = 8
```

This is a counterpart problem of the previous problem. `dist[nx][ny] = min(dist[nx][ny], max(dist[x][y], grid[nx][ny]))`.

```c++
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
```

## Min Spinning Graph

In general min spinning graph is undirected graph. There are two classic algorithms: Prim algorithm and Kruskal's algorithm.

- Prim algorithm
    - Naive Prim: dense graph O(n^2) (*)
    - Heap Optimized Prim: sparse graph O(mlog(n)) (x)
- Kruskal's algorithm: sparse graph O(mlog(m)) (*)

### Prim Algorithm

Prim algorithm is very similar to Dijkstra algorithm.

- Naive Prim

The basic idea is to select a vertex from `ust[]` with MINIMUM distance to spinning graph for each iteration. The edge between vertex and spinning graph is the minimum edge we can choose for this iteration.

DEFINE: `dist[]` as the distance between a vertex and a spinning graph, which is different from Dijkstra algorithm. The distance between a vertex and a spinning graph is defined as the min distance from the vertex to the vertexes in the spinning graph.

```text
dist[] = inf
for v in vertexes
    select a vertex t not in `st[]` with min dist
    update dist[] of candidate vertexes with t
    st[] <-- t

*candidate vertexes means those not in `st[]` (the spinning graph)
```

The implementation is: (1-base implementation, when i == 0, dist is initialized. So we don't have to set `dist[0] = 0` explicitly).

```c++
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
        // no connection from ver to spinning graph found
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
```

IMPORTANT: We use adjacency list in directed graph (sparse) and adjacency matrix in undirected graph (dense). **Traverse adjacent vertexes of a vertex in Adjacency List is dangerous when self loop exists**

If we want to use adjacency list to represent an undirected graph, buffer should be `2 * m`, where `m` is the size of edges.

```c++
vector<int> h(N, -1);
vector<int> v(2 * m, 0);
vector<int> w(2 * m, 0);
vector<int> ne(2 * m, -1);

for (int i = 0; i < m; i++) {
    int aa = ...
    int bb = ...
    int wt = ...
    // add aa -> bb
    v[idx] = bb;
    w[idx] = wt;
    ne[idx] = h[aa];
    h[aa] = idx++;
    // add bb -> aa
    v[idx] = aa;
    w[idx] = wt;
    ne[idx] = h[bb];
    h[bb] = idx++;
}
```

### Kruskal's Algorithm

Kruskal's algorithm is a greedy algorithm.

```text
sort all edges in ascending order
for e in edges:
    if vertexes of the edge is not connected (union-disjoint set)
        add edge to the graph

check if the graph includes all vertexes
```

We will implement Kruskal's algorithm with the help of Union-disjoint Set (a tree with ONLY parent pointer).

```c++
class DisjointSet {
    public:
    int p[N];
    DisjointSet(int n) {
        for (int i = 0; i <= n; i++) {
            p[i] = i;
        }
    }

    int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }

    void join(int x, int y) {
        p[find(x)] = find(y);
    }
};
```

The code is:

```c++
int minSpinningGraphKruskal(int n, vector<vector<int>>& edges) {
    int m = edges.size();
    struct Edge {
        int a, b, w;
        // overwrite less sign
        bool operator<(const Edge& e) const { return w < e.w; }
    } e[m];

    // sort
    sort(e, e + m);

    DisjointSet dsu(n);
    int res = 0;
    int cnt_edges = 0;
    // enumerate all edges from shortest to longest
    for (int i = 0; i < m; i++) {
        int aa = e[i].a;
        int bb = e[i].b;
        int wt = e[i].w;
        if (dsu.find(aa) != dsu.find(bb)) {
            // not connected
            dsu.join(aa, bb);
            res += wt;
            cnt_edges++;
        }
    }

    if (cnt_edges < n - 1) return -1;
    return res;
}
```

### Min Cost to Connect All Points

> You are given an array points representing integer coordinates of some points on a 2D-plane, where `points[i] = [xi, yi]`.
>
> The cost of connecting two points `[xi, yi]` and `[xj, yj]` is the manhattan distance between them: `|xi - xj| + |yi - yj|`, where `|val|` denotes the absolute value of val.
>
> Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

An exercise for min spinning tree.

```c++
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
```

### Minimum Number of Lines to Cover Points

> You are given an array points where `points[i] = [xi, yi]` represents a point on an X-Y plane.
>
> Straight lines are going to be added to the X-Y plane, such that every point is covered by at least one line.
>
> Return the minimum number of straight lines needed to cover all the points.

This is a classic min spinning tree problem. Since the graph consisting of points is a dense graph, it is represented with adjacency matrix.

One important fact is that the result of minimum lines that cover all vertexes is the same as the min (distance) spinning tree.

- min spinning tree (BUG)

Some points to consider:

- why one min of spinning tree is almost the answer to the problem after filtering unnecessary lines?
- how to represent a line? `pair<slope, y-intercept>`

```c++
int minimumLines(vector<vector<int>>& points) {
    int n = points.size();
    if (n == 1) return 1;
    int inf = 1e9;
    vector<vector<int>> g(n, vector<int>(n, inf));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int dx = abs(points[i][0] - points[j][0]);
            int dy = abs(points[i][1] - points[j][1]);
            int distance = floor(sqrt(dx * dx + dy * dy));
            g[i][j] = g[j][i] = distance;
        }
    }

    vector<int> dist(n, inf);
    // record the other end of edge in min spinning tree
    vector<int> match(n, -1);
    vector<bool> st(n, false);
    dist[0] = 0;
    match[0] = 0;   // the only self edge
    for (int i = 0; i < n; i++) {
        int t = -1;
        for (int j = 0; j < n; j++) {
            if (!st[j] && (t == -1 || dist[j] < dist[t])) {
                t = j;
            }
        }
        if (dist[t] == inf) return -1;
        st[t] = true;
        for (int j = 0; j < n; j++) {
            if (!st[j] && dist[j] > g[t][j]) {
                dist[j] = g[t][j];
                match[j] = t;
            }
        }
    }

    // points on the line with slopes 's'
    unordered_map<string, unordered_set<int>> vertexesOn;
    // # of lines == # of slopes
    // ignore the first edge (self edge)
    for (int i = 1; i < n; i++) {
        int x1 = points[i][0], y1 = points[i][1];
        int x2 = points[match[i]][0], y2 = points[match[i]][1];

        double slope, yIntercept;
        if (x1 - x2 != 0) {
            slope = double(y1 - y2) / (x1 - x2);
            yIntercept = y1 - slope * x1;
        } else {
            slope = yIntercept = inf;
        }

        // add points to lines
        string id = to_string(slope) + "," + to_string(yIntercept);
        vertexesOn[id].insert(i);
        vertexesOn[id].insert(match[i]);
    }

    // filter unnecessary points
    // occurrence time of each node on different lines
    vector<int> occurrence(n, 0);
    for (auto t : vertexesOn) {
        for (auto v : vertexesOn[t.first]) {
            occurrence[v]++;
        }
    }

    for (auto t : vertexesOn) {
        cout << t.first << " ";
        for (auto v : vertexesOn[t.first]) {
            cout << v << " ";
        }
        cout << endl;
    }

    int res = 0;
    for (auto t : vertexesOn) {
        for (auto v : vertexesOn[t.first]) {
            if (occurrence[v] - 1 == 0) {
                res++;
                break;
            }
        }
    }

    return res;
}
```

## Bipartite Graph

We will talk about: 1. how to check if a graph is a bipartite, and 2. match problem (Hungarian algorithm).

a bipartite graph (or bigraph) is a graph whose vertices can be divided into two disjoint and independent sets `U` and `V`, that is every edge connects a vertex in `U` to one in `V`. Vertex sets `U` and `V` are usually called the parts of the graph. Equivalently, a bipartite graph is a graph that does not contain any odd-length cycles.

### Check Bipartite

We check bipartite graph by colorizing vertexes.

```text
for v in all vertexes:   // graph may be not a full connected graph
    if v not colored
        dfs(paint v with color)
        if fail
            not partite

if painting succeed, partite graph
```

```c++
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
```

### Hungarian Algorithm

The core idea of Hungarian algorithm is:

```text
left             right
 1 -------+----+-  1
 2 --------\--/    2
 3          \----  3

where left 1 points to right 1 and 3
      left 2 points to right 1
```

When right 1 has matched with left 1, `match[1] = 1 (left)`, and we want to match left 2 with right 1, we will try to match right 1 with other possible vertexes on the left to make room for left vertex 2.

```c++
// if right j has no match or its match vertex can find alternative.
if (match[j] == -1 || find(match[j])) {
    ...
}
```

```c++
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
```

```c++
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
```

Note: `st[]` is for each round in finding match right vertex for left `i` vertex. `st[j]` records if right `j` vertex has been occupied by a left vertex.

## Disjoint Set

### Number of Province

> There are `n` cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
>
> A province is a group of directly or indirectly connected cities and no other cities outside of the group.
>
> You are given an `n x n` matrix `isConnected` where `isConnected[i][j] = 1` if the ith city and the jth city are directly connected, and `isConnected[i][j] = 0` otherwise.
>
> Return the total number of provinces.

- disjoint set

This is a problem for disjoint set.

```c++
const int N = 210;

class DisjointSet {
   public:
    DisjointSet(int n);
    void merge(int x, int y);
    int find(int x);

    int p[N];
    int size;   // # of subgraphs
};

DisjointSet::DisjointSet(int n) {
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
```

```c++
/**
 * @brief time complexity O(n^2)
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
```

- depth first search

Depth first search and color to find different connected graphs.

```c++
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
```

### Graph Valid Tree

> You have a graph of n nodes labeled from 0 to n - 1. You are given an integer n and a list of edges where `edges[i] = [ai, bi]` indicates that there is an undirected edge between nodes `ai` and `bi` in the graph.
>
> Return true if the edges of the given graph make up a valid tree, and false otherwise.

We can check if a graph has simple cycle with disjoint set. How?

Notice that a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

- disjoint set

Given two vertexes (`a` and `b`) are in a set connected by other vertexes, a simple cycle exists when an edge `a -> b` occurs.

So, a valid tree has two property:

- full connected: size of disjoint set should be 1.
- no simple circle: no additional edge exist between two vertexes within a set.

```c++
bool validTree(int n, vector<vector<int>>& edges) {
    DisjointSet dsu(n);
    for (int i = 0; i < edges.size(); i++) {
        int aa = edges[i][0];
        int bb = edges[i][1];
        // no additional edge
        if (dsu.find(aa) == dsu.find(bb)) {
            return false;
        } else {
            dsu.merge(aa, bb);
        }
    }

    return dsu.size == 1;
}
```

### Number of Connected Components in an Undirected Graph

> You have a graph of n nodes. You are given an integer n and an array edges where `edges[i] = [ai, bi]` indicates that there is an edge between `ai` and `bi` in the graph.
>
> Return the number of connected components in the graph.

Again, disjoint set.

```c++
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
```

### The Earliest Moment When Everyone Become Friends

> There are n people in a social group labeled from 0 to n - 1. You are given an array logs where `logs[i] = [timestamp_i, xi, yi]` indicates that `xi` and `yi` will be friends at the time `timestamp_i`.
>
> Friendship is symmetric. That means if a is friends with b, then b is friends with a. Also, person a is acquainted with a person b if a is friends with b, or a is a friend of someone acquainted with b.
>
> Return the earliest time for which every person became acquainted with every other person. If there is no such earliest time, return -1.

Similar to Kruskal's algorithm.

```c++
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
```

### Smallest String With Swaps

> You are given a string `s`, and an array of pairs of indices in the string pairs where `pairs[i] = [a, b]` indicates 2 indices (0-indexed) of the string.
>
> You can swap the characters at any pair of indices in the given pairs any number of times.
>
> Return the lexicographically smallest string that s can be changed to after using the swaps.

```text
Given s = 'dcab', and pairs = {{0, 3}, {1, 2}, {0, 2}}.
```

How to change it into a lexicographically smallest string by swapping.

One important point to note is that given pairs `{1, 2}` and `{0, 2}`, we can swap `{0, 1}` even such pair does not exist. So indices within a connected component (graph) can be swapped arbitrarily.

With this idea in mind, the solution can be broken down into 4 steps:

- find connected components with disjoint set.
- rearrange indices within a component in lexicon order.
- reconstruct string with ordered indices.

```c++
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
```

### Evaluate Division

> You are given an array of variable pairs equations and an array of real numbers values, where `equations[i] = [Ai, Bi]` and `values[i]` represent the equation `Ai / Bi = values[i]`. Each Ai or Bi is a string that represents a single variable.
>
> You are also given some queries, where `queries[j] = [Cj, Dj]` represents the jth query where you must find the answer for `Cj / Dj =` ?.
>
> Return the answers to all queries. If a single answer cannot be determined, return -1.0.

To make the problem clear, here is an example

```text
equations = [["a","b"],["b","c"]], values = [2.0,3.0],
queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]

Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
```

Note that with the knowledge of `a / b = 2.0` and `b / c = 3.0`, `a / c` can be calculated with `a / b * b / c = 2.0 * 3.0 = 6.0`

Actually, those objects with the property of transition can be modeled with graph. Imagine the equation as a directed graph:

```text
graph from equation:
a -> b = 2.0  b -> a = 1 / 2.0 = 0.5
b -> c = 3.0  c -> b = 1 / 3.0 = 0.3
```

For queries, if two characters are in a connected graph, it can be calculated. If not, the answer cannot be determined.

The algorithm is:

- map string to int for creating disjoint set.
- create adjacency list and disjoint set.
- if two strings in the same graph, calculate the value (dfs).

```c++
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
```

### Optimize Water Distribution in a Village

> There are n houses in a village. We want to supply water for all the houses by building wells and laying pipes.
>
> For each house i, we can either build a well inside it directly with cost `wells[i - 1]` (note the -1 due to 0-indexing), or pipe in water from another well to it. The costs to lay pipes between houses are given by the array `pipes` where each `pipes[j] = [house1j, house2j, costj]` represents the cost to connect `house1j` and `house2j` together using a pipe. Connections are bidirectional, and there could be multiple valid connections between the same two houses with different costs.
>
> Return the minimum total cost to supply water to all houses.

This is a problem for minimum spinning tree (Prim Algorithm).

We will maintain a vector `minCostPipe[]`, which indicates the min cost for piping in water for `house[i]` from any other houses.

- Prim algorithm

The basic algorithm is :

- there are two kind of ways: building a well inside and laying pipes, where the former can be seen as a special edge (self to self).
- `dist[]` maintains the min cost of put `house[i]` into the spinning graph.
- `st[]` check if `house[i]` is selected.

```c++
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
```

- Kruskal's algorithm

The trick here for self-to-self edge (well edge) is: we treat it as a edge from `0 -> i` rather than `i -> i` (AWESOME).

```c++
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
```

## Topology Sort

### Course Schedule II

> There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where `prerequisites[i] = [ai, bi]` indicates that you must take course `bi` first if you want to take course `ai`.
>
> For example, the pair `[0, 1]`, indicates that to take course 0 you have to first take course 1.
>
> Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

```c++
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    int n = numCourses;
    vector<vector<int>> g(n, vector<int>(n, 0));
    vector<int> id(numCourses, 0);
    for (auto prerequisite : prerequisites) {
        g[prerequisite[1]][prerequisite[0]] = 1;
        id[prerequisite[0]]++;
    }

    queue<int> que;
    for (int i = 0; i < numCourses; i++) {
        if (id[i] == 0) que.push(i);
    }

    vector<int> res;
    while (!que.empty()) {
        int ver = que.front();
        que.pop();
        res.push_back(ver);
        for (int i = 0; i < numCourses; i++) {
            if (g[ver][i] == 1) {
                id[i]--;
                if (id[i] == 0) que.push(i);
            }
        }
    }
    
    if (res.size() < numCourses) return {};
    return res;
}
```

### Alien Dictionary

> There is a new alien language that uses the English alphabet. However, the order among the letters is unknown to you.
>
> You are given a list of strings `words` from the alien language's dictionary, where the strings in `words` are sorted lexicographically by the rules of this new language.
>
> Return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there is no solution, return `""`. If there are multiple solutions, return any of them.
>
> A string `s` is lexicographically smaller than a string `t` if at the first letter where they differ, the letter in `s` comes before the letter in `t` in the alien language. If the first min`(s.length, t.length)` letters are the same, then `s` is smaller if and only if `s.length < t.length`.

For example,

```text
words = ["wrt","wrf","er","ett","rftt"];

"wrt" < "wrf" => "wr" == "wr", the index of the first character differs is 2 (0-based). We know that "t" < "f"

"wrf" < "er"  => they have no common prefix and the first different char is the first char. We know that "w" < "e".

"er" < "erw"  => "er" == "er", "er" < "erw" since len("er") < len("erw") (NO INFO ABOUT WHICH CHAR IS SMALLER THAN WHICH CHAR)

answer: "wertf"
```

```c++
void analyze(vector<vector<int>>& g, vector<int>& id, string lhs, string rhs) {
    for (int i = 0; i < min(lhs.size(), rhs.size()); i++) {
        if (lhs[i] == rhs[i]) continue;
        // prevent repeated edges
        if (!g[lhs[i] - 'a'][rhs[i] - 'a']) {
            g[lhs[i] - 'a'][rhs[i] - 'a'] = 1;
            id[rhs[i] - 'a']++;
        }
        break;
    }
}

/**
 * @brief 0-based
 * 
 * Special case: ["abc", "ab"] violates the rule, return ""
 * 
 * @param words 
 * @return string 
 */
string alienOrder(vector<string>& words) {
    int n = 26;
    vector<vector<int>> g(26, vector<int>(26, 0));
    vector<int> id(26, -1);

    // calculate the size of char
    int nChar = 0;
    for (auto word : words) {
        for (auto ch : word) {
            // when char occurs for the first time, set its id as 0 (assumed it is smallest)
            if (id[ch - 'a'] == -1) {
                id[ch - 'a'] = 0;
                nChar++;
            }
        }
    }

    int m = words.size();
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            // handle violation ["abd", "ab"]
            if (words[i].size() > words[j].size() && words[i].rfind(words[j], 0) == 0) {
                return "";
            }
            analyze(g, id, words[i], words[j]);
        }
    }

    queue<int> que;
    for (int i = 0; i < 26; i++) {
        if (id[i] == 0) que.push(i);
    }

    string res;
    while (!que.empty()) {
        int ch = que.front();
        que.pop();
        res.push_back(ch + 'a');
        for (int j = 0; j < 26; j++) {
            if (g[ch][j] == 1) {
                id[j]--;
                if (id[j] == 0) que.push(j);
            }
        }
    }

    return res.size() < nChar ? "" : res;
}
```

### Minimum Height Trees

> A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.
>
> Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).
>
> Return a list of all MHTs' root labels. You can return the answer in any order.
>
> The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

There two important observations:

- Tree is a special graph with `n` vertexes and `n - 1` edges.
- Each vertex (node) in a tree has only one input degree. So, the result of topology sorting is same as that of BFS.

The implementation is shown as follow.

- BFS: Time Limit Exceed.

```c++
int findMHTHelper(vector<int>& h, vector<int>& v, vector<int>& ne, int i) {
    int height = 0;
    // topology sorting
    queue<int> que;
    // undirected graph: prevent dead loop
    vector<bool> st(h.size(), false);
    que.push(i);
    while (!que.empty()) {
        height++;
        int sz = que.size();
        while (sz--) {
            int u = que.front();
            que.pop();
            st[u] = true;
            for (int p = h[u]; p != -1; p = ne[p]) {
                int j = v[p];
                if (!st[j]) que.push(j);
            }
        }
    }

    return height;
}

/**
 * @brief topology sorting == breadth first search in a tree.
 *
 * @param n
 * @param edges
 * @return vector<int>
 */
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    const int inf = 1e6;
    int idx = 0;
    int m = edges.size();
    // undirected graph
    vector<int> h(n, -1);
    vector<int> v(2 * m, 0);
    vector<int> ne(2 * m, -1);
    for (auto edge : edges) {
        int aa = edge[0], bb = edge[1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
        v[idx] = aa;
        ne[idx] = h[bb];
        h[bb] = idx++;
    }

    int minVertex = -1;
    int minHeight = inf;
    vector<int> res;
    for (int i = 0; i < n; i++) {
        int height = findMHTHelper(h, v, ne, i);
        if (minVertex == -1 || height < minHeight) {
            minVertex = i;
            res.clear();
            res.push_back(i);
            minHeight = height;
            continue;
        }
        if (height == minHeight) {
            res.push_back(i);
        }
    }

    return res;
}
```

- Find centroid with topology sorting.

When centroid is treated as the root of a tree, it should have the minimum height.

One important observation is: in tree graph, there are at most two centroids.

```c++
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};
    const int inf = 1e6;
    int idx = 0;
    int m = edges.size();
    // undirected graph
    vector<int> h(n, -1);
    vector<int> v(2 * m, 0);
    vector<int> ne(2 * m, -1);
    vector<int> d(n, 0);   // degree of each node == edges (undirected)
    for (auto edge : edges) {
        int aa = edge[0], bb = edge[1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
        v[idx] = aa;
        ne[idx] = h[bb];
        h[bb] = idx++;

        d[aa]++, d[bb]++;
    }

    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (d[i] == 1) que.push(i);
    }
    vector<int> st(n, false);
    vector<int> res;
    int nLeft = n;
    while (!que.empty()) {
        int sz = que.size();
        if (nLeft <= 2) break;
        while (sz--) {
            int u = que.front();
            que.pop();
            st[u] = true;
            nLeft--;
            for (int p = h[u]; p != -1; p = ne[p]) {
                int j = v[p];
                d[j]--;
                if (!st[j] && d[j] == 1) que.push(j);
            }
        }
    }

    // # of nodes is odd
    res.push_back(que.front());

    // # of nodes is even
    if (que.size() == 2) {
        que.pop();
        res.push_back(que.front());
    }

    return res;
}
```

### Parallel Courses

> You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where `relations[i] = [prevCoursei, nextCoursei]`, representing a prerequisite relationship between course `prevCoursei` and course `nextCoursei`: course `prevCoursei` has to be taken before course `nextCoursei`.
>
> In one semester, you can take any number of courses as long as you have taken all the prerequisites in the previous semester for the courses you are taking.
>
> Return the minimum number of semesters needed to take all courses. If there is no way to take all the courses, return -1.

Topology sorting with loop checking (`nVertexes` to check if all vertexes are visited).

```c++
int minimumSemesters(int n, vector<vector<int>>& relations) {
    int N = n + 1;
    int m = relations.size();
    int idx = 0;
    vector<int> h(N, -1);
    vector<int> v(m, 0);
    vector<int> ne(m, -1);
    vector<int> id(N, 0);
    for (auto rel : relations) {
        int aa = rel[0], bb = rel[1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
        id[bb]++;
    }

    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (id[i] == 0) {
            que.push(i);
        }
    }

    int nVertexes = n;
    int nSemester = 0;
    while (!que.empty()) {
        int sz = que.size();
        nSemester++;
        while (sz--) {
            int u = que.front();
            que.pop();
            nVertexes--;
            for (int p = h[u]; p != -1; p = ne[p]) {
                int j = v[p];
                id[j]--;
                if (id[j] == 0) que.push(j);
            }
        }
    }

    if (nVertexes == 0) {
        return nSemester;
    } else {
        return -1;
    }
}
```

### Parallel Courses II

> You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where `relations[i] = [prevCoursei, nextCoursei]`, representing a prerequisite relationship between course `prevCoursei` and course `nextCoursei`: course `prevCoursei` has to be taken before course `nextCoursei`. Also, you are given the integer k.
>
> In one semester, you can take at most `k` courses as long as you have taken all the prerequisites in the previous semesters for the courses you are taking.
>
> Return the minimum number of semesters needed to take all courses. The testcases will be generated such that it is possible to take every course.

Note that `n <= 15` in the constraint, we are able to represent if a course is selected with a bitmap, `0b00000011` representing the first and second courses are selected.

The basic algorithm is:

- Use masks to represent the set of courses (nodes) taken, till now. If a bit in mask is 1, it means that course is taken.
- For a particular mask, calculate the indegree (pre-requisite) of each node, without including the edges from the nodes that are already taken (courses having been selected).
- Now, at any stage, we can only chose any subset (submask) of the nodes with indegree as 0. This generates overlapping subproblems, which can be easily handled using DP with bitmasking.

There are two cases in each semester: Let p as the number of nodes (so far) with indegree 0 at any stage.

- if `p > k`, it is optimal to take a subset of nodes having exactly k nodes.
- if `p <= k`, it is optimal to take all the p nodes.

Before implementing the algorithm above, we will review the bit operation first:

- bit representation

```text
                        # of states (ignore leading 1)
2^0 = 0b1    = 1 << 0       (0)
2^1 = 0b10   = 1 << 1       (1)
2^2 = 0b100  = 1 << 2       (2)
...
2^n = 0b100..00 = 1 << n    (n)
```

`2^n` can represent subsets of `n` states.

- bit operation
    - set all state bit to be 1: `(1 << n) - 1`.
    - check if ith bit is set: `(mask >> i) & 1 == 1` or `mask & (1 << i) != 0`.
    - set ith bit to be 1: `mask | (1 << i)`.
    - set ith bit to be 0: `mask & ~(1 << i)`.
    - toggle ith bit: `mask ^ (1 << i)`.

- iterate all subset of `mask`: `for (int j = mask; j; j = (j - 1) & mask)`.

- bit functions
    - `__builtin_popcount(int)` returns the number of set bits.

```c++
int solver(vector<int>& h, vector<int>& v, vector<int>& ne, vector<int>& f, int n, int k, int courses) {
    static int inf = 1e5;
    // all courses have been selected, no new semester
    if (courses == (1 << n) - 1) return 0;
    // if calculated before, return the result
    if (f[courses] != -1) return f[courses];

    // find all courses without prerequisites and has not been selected, till now (with indegree 0)
    vector<int> id(h.size(), 0);
    for (int i = 0; i < n; i++) {
        // selected
        if ((courses >> i) & 1) continue;
        // not selected: bit is 0-based and node is 1-based
        for (int p = h[i + 1]; p != -1; p = ne[p]) {
            int j = v[p];
            id[j]++;
        }
    }

    // construct available courses
    int available = 0;   // available courses in this semester
    for (int i = 0; i < n; i++) {
        // if not selected before and no prerequisite
        if (((courses >> i) & 1) == 0 && id[i + 1] == 0) {
            available |= (1 << i);
        }
    }

    int nCourses = __builtin_popcount(available);
    int minSemester = inf;
    if (nCourses < k) {
        minSemester = min(minSemester, solver(h, v, ne, f, n, k, courses | available) + 1);
    } else {
        // use j to enumerate all subsets of available courses with the size of k
        for (int j = available; j; j = (j - 1) & available) {
            int cnt = __builtin_popcount(j);
            if (cnt != k) continue;
            minSemester = min(minSemester, solver(h, v, ne, f, n, k, courses | j) + 1);
        }
    }

    f[courses] = minSemester;
    return minSemester;
}

int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
    int N = n + 1;
    int inf = 1e6;
    int m = relations.size();
    int idx = 0;
    vector<int> h(N, -1);
    vector<int> v(m, 0);
    vector<int> ne(m, -1);
    for (auto rel : relations) {
        int aa = rel[0], bb = rel[1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
    }
    
    // -1 represents no calculation result
    vector<int> f(1 << n, -1);

    return solver(h, v, ne, f, n, k, 0);
}
```

### Parallel Courses III

> You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given a 2D integer array `relations` where `relations[j] = [prevCoursej, nextCoursej]` denotes that course `prevCoursej` has to be completed before course `nextCoursej` (prerequisite relationship). Furthermore, you are given a 0-indexed integer array time where `time[i]` denotes how many months it takes to complete the `(i+1)th` course.
>
> You must find the minimum number of months needed to complete all the courses following these rules:
>
> - You may start taking a course at any time if the prerequisites are met.
> - Any number of courses can be taken at the same time.
>
> Return the minimum number of months needed to complete all the courses.

There are two constraints in this problem compared with Parallel Courses II:

- dependency: some courses are required to be completed before taking other courses.
- cost: time cost for each course varies.

- topology sorting solution

Note that there is no number of selection constraint and we may start taking a course at any time if the prerequisites are met. So, we will use topology sorting to find the course I can take so far, and use priority queue to save the first course will be completed in all on-going courses (with pair `{the month when the course is done, course id}`).

```c++
int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
    int N = n + 1;
    int m = relations.size();
    int inf = 1e7;
    vector<int> h(N, -1);
    vector<int> v(m, 0);
    vector<int> ne(m, -1);
    vector<int> id(N, 0);
    int idx = 0;
    for (auto& rel : relations) {
        int aa = rel[0], bb = rel[1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
        id[bb]++;
    }

    typedef pair<int, int> PII;   // {the month when the course is done, node}
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    for (int i = 1; i <= n; i++) {
        if (id[i] == 0) pq.push({0 + time[i - 1], i});
    }

    int begin = 0;
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        int u = t.second, tm = t.first;
        begin = tm;   // complete
        for (int p = h[u]; p != -1; p = ne[p]) {
            int j = v[p];
            id[j]--;
            if (id[j] == 0) pq.push({begin + time[j - 1], j});
        }
    }

    return begin;
}
```

- dynamic programming solution

Define `f[i]` as the min time cost for all courses depending on `i`th course.

```c++
int minimumTimeHelper(vector<int>& h, vector<int>& v, vector<int>& ne, vector<int>& time, vector<int>& f, int u) {
    if (f[u] != -1) return f[u];

    int t = 0;
    for (int p = h[u]; p != -1; p = ne[p]) {
        int j = v[p];
        t = max(t, minimumTimeHelper(h, v, ne, time, f, j));
    }
    t += time[u - 1];

    f[u] = t;
    return t;
}

int minimumTimeII(int n, vector<vector<int>>& relations, vector<int>& time) {
    int N = n + 1;
    int m = relations.size();
    int inf = 1e7;
    vector<int> h(N, -1);
    vector<int> v(m, 0);
    vector<int> ne(m, -1);
    vector<int> id(N, 0);
    int idx = 0;
    for (auto& rel : relations) {
        int aa = rel[0], bb = rel[1];
        v[idx] = bb;
        ne[idx] = h[aa];
        h[aa] = idx++;
        id[bb]++;
    }

    vector<int> f(N, -1);
    int res = -1;
    for (int i = 1; i <= n; i++) {
        if (id[i] == 0) {
            res = max(res, minimumTimeHelper(h, v, ne, time, f, i));
        }
    }

    return res;
}
```
