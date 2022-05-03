#ifndef PROBLEMS_HPP
#define PROBLEMS_HPP

#include <vector>
using namespace std;

const int N = 210;

class DisjointSet {
   public:
    DisjointSet(int _n);
    void merge(int x, int y);
    int find(int x);

    int p[N];
    int size;   // size of subgraphs
};

int findCircleNum(vector<vector<int>>& isConnected);
int findCircleNumII(vector<vector<int>>& isConnected);
bool validTree(int n, vector<vector<int>>& edges);
int countComponents(int n, vector<vector<int>>& edges);
int earliestAcq(vector<vector<int>>& logs, int n);

#endif