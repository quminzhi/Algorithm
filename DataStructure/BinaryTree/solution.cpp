#include <stack>
#include "solution.hpp"
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

// write your solution here
void Solution() {}