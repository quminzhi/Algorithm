#ifndef TREENODE_H
#define TREENODE_H

class TreeNode
{
public:
    TreeNode()
        : val(0), left(nullptr), right(nullptr) {};
    TreeNode(int _val)
        : val(_val), left(nullptr), right(nullptr) {};
    TreeNode(int _val, TreeNode* left, TreeNode* right)
        : val(_val), left(left), right(right) {};

    int val;
    TreeNode* left;
    TreeNode* right;
};

#endif // TREENODE_H
