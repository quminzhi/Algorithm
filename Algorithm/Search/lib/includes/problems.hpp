#ifndef PROBLEMS_HPP
#define PROBLEMS_HPP

#include <vector>
using namespace std;

const int N = 210;

class DisjointSet {
   public:
    DisjointSet(int n);
    void merge(int x, int y);
    int find(int x);

    int p[N];
};

int findCircleNum(vector<vector<int>>& isConnected);
int findCircleNumII(vector<vector<int>>& isConnected);

#endif