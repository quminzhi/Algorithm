#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/* DFS */
vector<vector<string>> solveNQueens(int n);

/* BFS */
class Point {
   public:
    Point() : x(0), y(0){};
    Point(int _x, int _y) : x(_x), y(_y){};
    int x;
    int y;
};
int minPathInMatrix(vector<vector<int>>& matrix);

/* Graph */
int centerOfGravity(int n, vector<vector<int>>& graph);
vector<int> pseudoTopologicalSeq(int n, vector<vector<int>>& graph);
vector<int> topoSort(int n, vector<vector<int>>& graph);

/* Min Path */
int minPathDijkstra(int n, vector<vector<int>>& edges);
int minPathDijkstraHeap(int n, vector<vector<int>>& edges);
int minPathBellman(int n, vector<vector<int>>& edges, int limit);   // positive or negative graph
int minPathSPFA(int n, vector<vector<int>>& edges);
bool checkNegativeLoopWithSPFA(int n, vector<vector<int>>& edges);
int minPathSPFAWithControl(int n, vector<vector<int>>& edges, int limit);   // positive graph
int minPathFloyd(int n, vector<vector<int>>& edges);

/* Spinning Graph */
int minSpinningGraphPrim(int n, vector<vector<int>>& edges);
int minSpinningGraphKruskal(int n, vector<vector<int>>& edges);
int minimumLines(vector<vector<int>>& points);

/* Bipartite Graph */
bool isBipartiteGraph(int n, vector<vector<int>>& edges);
int maxBipartiteGraph(int n1, int n2, vector<vector<int>>& edges);

/* Topology Sorting */
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);
string alienOrder(vector<string>& words);

#endif