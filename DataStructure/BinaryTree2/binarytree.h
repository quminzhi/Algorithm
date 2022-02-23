#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "treenode.h"
#include <vector>
using namespace std;

class BinaryTree
{
public:
    BinaryTree()
        : root(nullptr) {};
    BinaryTree(TreeNode* _root)
        : root(_root) {};
    BinaryTree(vector<int> v);

    // Traverse:
    vector<int> preorderTraversal(TreeNode* root);

    ~BinaryTree();

    TreeNode* root;
private:
    void clear();
};

#endif // BINARYTREE_H
