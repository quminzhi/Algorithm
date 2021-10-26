#ifndef MERGINGTWOBINARYTREES_H
#define MERGINGTWOBINARYTREES_H

/**
 * You are given two binary trees root1 and root2.
 *
 * Imagine that when you put one of them to cover the other, some nodes of the two
 * trees are overlapped while the others are not. You need to merge the two trees
 * into a new binary tree. The merge rule is that if two nodes overlap, then sum node
 * values up as the new value of the merged node. Otherwise, the NOT null node will
 * be used as the node of the new tree.
 *
 * Return the merged tree.
 *
 * Input: root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
 * Output: [3,4,5,5,4,null,7]
 *
 * Constrains:
 * The number of nodes in both trees is in the range [0, 2000].
 * -104 <= Node.val <= 104.
 */

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* mergeTrees_sol1(TreeNode* root1, TreeNode* root2);
TreeNode* mergeTrees_sol2(TreeNode* root1, TreeNode* root2);



#endif // MERGINGTWOBINARYTREES_H
