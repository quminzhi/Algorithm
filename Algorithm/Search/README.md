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
for v in all vertexes   // iterate n times
    for e in all edges   // e: a -> b with weight w
        dist[b] = min(dist[b], dist[a] + w)   // relax

dist[i] represents the min path from origin to ith vertex so far.
```

**IMPORTANT: after kth outmost loop, we got the min path from origin to ith vertex through at most k edges.** Each time we relax a vertex with an edge, then number of the edge on the min path add `1` if relaxation successes (`dist[b] > dist[a] + w`, so the min path must include `edge[a][b]`).

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

    if (dist[n - 1] >= (inf >> 1)) {   // weird!
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
   +--...--- a
origin       | -10
   +--...--- b
dist[b] = inf

for each loop, dist[b] = dist[a] - 10 = inf - 10
it is even worth when there is a edge from b to a with weight -10 (meaning negative loop), in that case, dist[a] or dist[b] may be go down to a negative number. Bellman-Ford algorithm prevent that from happening.
```

### SPFA

Shortest Path Faster Algorithm (SPFA) is an optimized Bellman-Ford algorithm.

First, let's see where can be optimized in Bellman-Ford algorithm.

```text
for v in all vertexes
    for e in all edges   // <-- trivial
        dist[b] = min(dist[b], dist[a] + w)   // relax

dist[i] represents the min path from origin to ith vertex so far.
```

We do not need to traverse all edges. Recall from Dijkstra algorithm, we just need to update correlated vertexes with newly-updated vertexes (correlated means directly connection or adjacent vertex).

With this idea in mind, we will use a `queue` to store those newly-updated vertex which will be used to update their adjacent vertexes.

```text
for v in all vertexes   // update at most v.size time
    while queue not empty
        for v in queue   // solve by level (round)
            for e in adjacent edges of v   // like bfs
                dist[adjacent vertex] = min(dist[adjacent vertex], dist[v] + w)
                queue <-- adjacent vertex if dist[adjacent vertex] is updated
```

- Basic SPFA

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
    vector<bool> st(N, false);   // prevent there are multiple edges on two adjacent vertexes.
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

Why use `st[]` to track if a vertex is in the queue, i.e. it can be used to update adjacent vertexes?

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

When using vertex 1 to relax 2, 2 will be pushed into queue nearly 100000 times horribly.
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
    // since negative loop may start from any vertex, not necessary to be 1
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
                if (counter[j] >= n) return true;   <== check
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
    vector<bool> st(n + 1, false);   // prevent there are multiple edges on two adjacent vertexes.
    queue<int> que;
    // push origin vertex into queue
    dist[1] = 0;
    que.push(1);
    st[1] = true;
    int i = 0;
    while (!que.empty()) {
        i++;
        if (i > limit) break;   // control path length
        int sz = que.size();
        for (int k = 0; k < sz; k++) {   // solve by level
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

The implementation is:

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
