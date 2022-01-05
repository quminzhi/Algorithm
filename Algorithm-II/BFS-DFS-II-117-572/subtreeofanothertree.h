#ifndef SUBTREEOFANOTHERTREE_H
#define SUBTREEOFANOTHERTREE_H

#include <iostream>
using namespace std;

/**
 * Given the roots of two binary trees root and subRoot, return true if there
 * is a subtree of root with the same structure and node values of subRoot and
 * false otherwise.
 *
 * A subtree of a binary tree tree is a tree that consists of a node in tree and
 * all of this node's descendants. The tree tree could also be considered as a
 * subtree of itself.
 *
 * Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 * Output: true
 *
 * Constrains:
 * The number of nodes in the root tree is in the range [1, 2000].
 * The number of nodes in the subRoot tree is in the range [1, 1000].
 * -104 <= root.val <= 104
 * -104 <= subRoot.val <= 104
 */

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(NULL), right(NULL) {}

    TreeNode(int _val) : val(_val), left(NULL), right(NULL) {}

    TreeNode(int _val, TreeNode* _left, TreeNode* _right, TreeNode* _next)
        : val(_val), left(_left), right(_right) {}
};

bool isSubtree(TreeNode* root, TreeNode* subRoot);

#endif // SUBTREEOFANOTHERTREE_H
