#ifndef LINEAR_HPP
#define LINEAR_HPP

#include <string>
#include <vector>
using namespace std;

int MaxLengthOfNonDescendingSubsequence(string s);
string MaxLengthOfNonDescendingSubsequenceII(string s);
int MaxLengthOfNonDescendingSubsequenceIII(string s);

int LongestCommonSubsequence(string sl, string sr);
int MinEditDistance(string sl, string sr);
int MergeStones(vector<int> stones);
int IntegerDivision(int n);
int IntegerDivisionII(int n);
int IntegerDivisionIII(int n);

int BlockFilling(int n, int m);
int ShortestHamiltonPath(vector<vector<int> > graph);

/**
 * @brief index by int not pointer
 */
class TreeNode {
   public:
    TreeNode() : id(0), parent(-1) {};
    TreeNode(int _id) : id(_id), parent(-1) {};

    int id;
    int parent;
    vector<int> children;
};

int PartyWithoutLeader(vector<int> exp, vector<vector<int> > rel);
int Skating(vector<vector<int> > h);

#endif