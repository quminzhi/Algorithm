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
int minPathDijkstra(int n, vector<vector<int>>& graph);
int minPathDijkstraHeap(int n, vector<vector<int>>& graph);
int minPathBellman(int n, vector<vector<int>>& edges, int k);
int minPathSPFA(int n, vector<vector<int>>& edges, int limit);

#endif