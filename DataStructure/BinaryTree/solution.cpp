#include "solution.hpp"

#include <queue>
#include <stack>
using namespace std;

/**
 * @brief root -> left -> right
 * Notice that: pre/in/post refers to the order of root
 * @param root
 * @param result
 */
void BinaryTree::preorderTraversalHelper(TreeNode* root, vector<int>& result) {
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

/**
 * @brief root -> left -> right
 * Track with an stack the traverse order. Push right child first so that it will be
 * traversed later than left child.
 * @param root
 * @param result
 */
void BinaryTree::preorderTraversalHelperNR(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;   // corner case
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        result.push_back(node->val);
        if (node->right != nullptr) {
            s.push(node->right);
        }
        if (node->left != nullptr) {
            s.push(node->left);
        }
    }
}

vector<int> BinaryTree::preorderTraversal(TreeNode* root) {
    vector<int> result;
    // preorderTraversalHelper(root, result);
    preorderTraversalHelperNR(root, result);
    return result;
}

/**
 * @brief left -> root -> right
 *
 * @param root
 * @param result
 */
void BinaryTree::inorderTraversalHelper(TreeNode* root, vector<int>& result) {
    if (root != nullptr) {
        if (root->left != nullptr) {
            inorderTraversalHelper(root->left, result);
        }
        result.push_back(root->val);
        if (root->right != nullptr) {
            inorderTraversalHelper(root->right, result);
        }
    }
}

/**
 * @brief The basic idea is to solve the leftmost leave node. If it has right child,
 * serve right child as the root node, and solve its leftmost leave node.
 *
 * So the basic problem is solve root and left child, which is applied to any root node.
 *
 * 1) Create an empty stack S.
 * 2) Initialize current node as root
 * 3) Push the current node to S and set current = current->left until current is NULL
 * 4) If current is NULL and stack is not empty then
 *      a) Pop the top item from stack.
 *      b) Print the popped item, set current = popped_item->right
 *      c) Go to step 3.
 * 5) If current is NULL and stack is empty then we are done.
 * @param root
 * @param result
 */
void BinaryTree::inorderTraversalHelperNR(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    stack<TreeNode*> s;
    TreeNode* ptr = root;
    while ((ptr != nullptr) || (!s.empty())) {
        while (ptr != nullptr) {   // find the leftmost child
            s.push(ptr);
            ptr = ptr->left;
        }
        // print current and relay to right child
        if ((ptr == nullptr) && (!s.empty())) {
            TreeNode* popped = s.top();
            s.pop();
            result.push_back(popped->val);
            ptr = popped->right;
        }
    }
}

vector<int> BinaryTree::inorderTraversal(TreeNode* root) {
    vector<int> result;
    // inorderTraversalHelper(root, result);
    inorderTraversalHelperNR(root, result);
    return result;
}

/**
 * @brief left -> right -> root
 * @param root
 * @param result
 */
void BinaryTree::postorderTraversalHelper(TreeNode* root, vector<int>& result) {
    if (root != nullptr) {
        if (root->left != nullptr) {
            postorderTraversalHelper(root->left, result);
        }
        if (root->right != nullptr) {
            postorderTraversalHelper(root->right, result);
        }
        result.push_back(root->val);
    }
}

/**
 * @brief left -> right -> root
 * Notice: the reverse of post order is root -> right -> left.
 * The basic idea is to solve the reverse of post order in a way similar to inorder
 * traversal with a stack. But we also need to reverse the output. One way to reverse the
 * output is by stack.
 * @param root
 * @param result
 */
void BinaryTree::postorderTraversalHelperNR(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    stack<int> reverse;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        reverse.push(node->val);
        if (node->left != nullptr) {
            s.push(node->left);
        }
        if (node->right != nullptr) {
            s.push(node->right);
        }
    }

    // TODO: reverse the output
    while (!reverse.empty()) {
        result.push_back(reverse.top());
        reverse.pop();
    }
}

vector<int> BinaryTree::postorderTraversal(TreeNode* root) {
    vector<int> result;
    // postorderTraversalHelper(root, result);
    postorderTraversalHelperNR(root, result);

    return result;
}

void BinaryTree::levelOrderTraversalHelper(TreeNode* root, vector<vector<int> >& result) {
    if (root == nullptr) return;
    queue<TreeNode*> que;
    que.push(root);
    while (!que.empty()) {
        // notice all nodes in the same level will be pushed in the same level time
        int size = que.size();
        result.push_back(vector<int>());
        for (int i = 0; i < size; i++) {
            TreeNode* cur = que.front();
            que.pop();
            result.back().push_back(cur->val);
            if (cur->left != nullptr) {
                que.push(cur->left);
            }
            if (cur->right != nullptr) {
                que.push(cur->right);
            }
        }
    }
}

vector<vector<int> > BinaryTree::levelOrderTraversal(TreeNode* root) {
    vector<vector<int> > result;
    levelOrderTraversalHelper(root, result);

    return result;
}

/**
 * @brief Recursive body: maxDepth is 1 + max(maxDepth(left), maxDepth(right))
 *
 * @param root
 * @return int: the max depth of binary tree
 */
int BinaryTree::maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

/**
 * @brief strictly symmetric means left and right child of each node should be symmetric.
 * A binary tree is strictly symmetric if its left and right subtrees are symmetric and
 * left->val == right->val.
 *
 * @param root
 * @return true: if the tree is symmetric
 * @return false: otherwise
 */
bool BinaryTree::isStrictlySymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    if ((root->left != nullptr) && (root->right != nullptr) &&
        (root->left->val == root->right->val) && (isSymmetric(root->left)) &&
        (isSymmetric(root->right))) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief left tree is a mirror reflection of right tree if
 * 1. left->vale == right->value
 * 2. isMirror(left->left, right->right) && isMirror(left->right, right->left)
 *
 * @param left
 * @param right
 * @return true
 * @return false
 */
bool BinaryTree::isMirror(TreeNode* left, TreeNode* right) {
    // both of them are null
    if ((left == nullptr) && (right == nullptr)) return true;
    // one of them is null
    if (left == nullptr) return false;
    if (right == nullptr) return false;
    // condition 1:
    if (left->val != right->val) return false;
    if (isMirror(left->left, right->right) && isMirror(left->right, right->left))
        return true;

    return false;
}

/**
 * @brief
 *
 * @param root
 * @return true: if left child is a mirror reflection of right child
 * @return false: otherwise
 */
bool BinaryTree::isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    return isMirror(root->left, root->right);
}

/**
 * @brief check if it has a path from root to a leaf node where sum of the value is the
 * target sum. Path exists if left or right has path sum of 'target sum - root->val'
 * if root is a leaf node and target sum is root->val, return true.
 *
 * Notice that negative value is allowed.
 *
 * @param root
 * @param targetSum
 * @return true: if it has path sum
 * @return false: otherwise
 */
bool BinaryTree::hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return false;
    // reach a leaf node
    if ((root->left == nullptr) && (root->right == nullptr) && (targetSum == root->val)) {
        return true;
    }
    return hasPathSum(root->left, targetSum - root->val) ||
           hasPathSum(root->right, targetSum - root->val);
}

/**
 * @brief A tree with root is a unival tree if both left and right are unival subtrees and
 * root->val == left->val == right->val.
 *
 * @param root
 * @return true
 * @return false
 */
bool BinaryTree::isUnivalTree(TreeNode* root) {
    if (root == nullptr) return false;

    // left and right children are nullptr
    if ((root->left == nullptr) && (root->right == nullptr)) return true;
    // right child is not nullptr
    if (root->left == nullptr)
        return (root->val == root->right->val) && isUnivalTree(root->right);
    // left child is not nullptr
    if (root->right == nullptr)
        return (root->val == root->left->val) && isUnivalTree(root->left);
    // left and right children are not nullptr
    return (root->val == root->left->val) && (root->val == root->right->val) &&
           isUnivalTree(root->left) && isUnivalTree(root->right);
}

/**
 * @brief A uni-value subtree means all nodes of the subtree have the same value.
 * The solution is based on that of isUnivalTree
 * @param root
 * @return int
 */
int BinaryTree::countUnivalSubtrees(TreeNode* root) {}

// write your solution here
void Solution() {}