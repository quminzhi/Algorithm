#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<string>> solveNQueens(int n);
class Point {
   public:
    Point() : x(0), y(0){};
    Point(int _x, int _y) : x(_x), y(_y){};
    int x;
    int y;
};
int minPathInMatrix(vector<vector<int>>& matrix);

#endif
