#include "subtreeofanothertree.h"

bool isEqual(TreeNode* lhs, TreeNode* rhs) {
    if ((lhs == nullptr) && (rhs == nullptr)) {
        return true;
    }
    // either of them is nullptr then return false
    if ((lhs == nullptr) || (rhs == nullptr)) return false;

    if (lhs->val != rhs->val) return false;
    return (isEqual(lhs->left, rhs->left) && isEqual(lhs->right, rhs->right));
}

/**
 * @brief isSubtree
 * @param root: the root of original tree
 * @param subRoot: sample subtree
 * @return true if root tree includes subRoot tree
 * How to check if two subtrees are same?
 * - with same height
 * - with same structure (node relations and value)
 *
 * Traverse in level order, check if subtree equals to subRoot.
 */


bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (subRoot == nullptr) return true;
    if (root == nullptr) return false;

    if (isEqual(root, subRoot)) return true;

    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}
