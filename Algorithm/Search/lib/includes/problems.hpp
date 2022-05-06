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
string smallestStringWithSwaps(string s, vector<vector<int>>& pairs);
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries);
int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes);
int minCostToSupplyWaterII(int n, vector<int>& wells, vector<vector<int>>& pipes);

/* DFS */
bool validPath(int n, vector<vector<int>>& edges, int source, int destination);
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph);

class Node {
   public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* cloneGraph(Node* node);

bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination);

/* BFS */
bool validPathBFS(int n, vector<vector<int>>& edges, int source, int destination);
vector<vector<int>> allPathsSourceTargetBFS(vector<vector<int>>& graph);

#endif