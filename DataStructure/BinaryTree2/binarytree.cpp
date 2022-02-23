#include "binarytree.h"

void preorderTraversalHelper(TreeNode* root, vector<int>& result) {
    if (root != nullptr) {
        result.push_back(root->val);
        if (root->left != nullptr) {
            preorderTraversalHelper(root->left, result);
        }
        if (root->right != nullptr) {
            preorderTraversalHelper(root->right, result);
        }
    }
}

vector<int> BinaryTree::preorderTraversal(TreeNode* root) {
    vector<int> result;
    preorderTraversalHelper(root, result);

    return result;
}
