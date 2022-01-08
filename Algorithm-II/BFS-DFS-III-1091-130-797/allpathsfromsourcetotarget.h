#ifndef ALLPATHSFROMSOURCETOTARGET_H
#define ALLPATHSFROMSOURCETOTARGET_H

#include <vector>
using namespace std;

/**
 * Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1, find
 * all possible paths from node 0 to node n - 1 and return them in any order.
 *
 * The graph is given as follows: graph[i] is a list of all nodes you can visit
 * from node i (i.e., there is a directed edge from node i to node graph[i][j]).
 *
 * Input: graph = [[1,2],[3],[3],[]]
 * Output: [[0,1,3],[0,2,3]]
 *
 * n == graph.length
 * 2 <= n <= 15
 * 0 <= graph[i][j] < n
 * graph[i][j] != i (i.e., there will be no self-loops).
 * All the elements of graph[i] are unique.
 * The input graph is guaranteed to be a DAG.
 */
vector< vector<int> > allPathsSourceTarget(vector< vector<int> >& graph);

#endif // ALLPATHSFROMSOURCETOTARGET_H
