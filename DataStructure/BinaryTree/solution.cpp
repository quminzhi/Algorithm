#include "solution.hpp"

#include <iostream>
using namespace std;

/**
 * @brief Construct a new Binary Tree:: Binary Tree object with an array
 * Assuming v[0] is root, left child of v[i] is v[2*i+1] and right child is v[2*i+2].
 * INT_MAX means null in the vector, indicating there is no node on the given index.
 * An array of TreeNode will be created to build tree.
 * @param v: a vector
 */
BinaryTree::BinaryTree(vector<int> v) {
    if (v.size() == 0) {
        this->root = nullptr;
    } else {
        // create an array of TreeNode* based on input vector 'v'
        vector<TreeNode*> arr;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] != INT_MAX) {
                TreeNode* node = new TreeNode(v[i]);
                arr.push_back(node);
            } else {
                arr.push_back(nullptr);   // if INT_MAX, place nullptr as a placeholder
            }
        }

        // build connection among them
        int max_size = v.size() / 2;
        for (int i = 0; i < max_size; i++) {
            if (arr[i] == nullptr) continue;
            // left child
            if (2 * i + 1 < v.size()) {
                arr[i]->left = arr[2 * i + 1];
            }
            if (2 * i + 2 < v.size()) {
                arr[i]->right = arr[2 * i + 2];
            }
        }

        // connect to root
        this->root = arr[0];
    }
}

/**
 * @brief Construct a new Binary Tree:: Binary Tree object with queue
 * Assuming v[0] is root, left child of v[i] is v[2*i+1] and right child is v[2*i+2].
 * INT_MAX means null in the vector, indicating there is no node on the given index.
 * @param v: a vector
 */
void BinaryTree::buildTreeRec(vector<int> v) {
    if (v.size() == 0) {
        this->root = nullptr;
    } else {
        unordered_map<TreeNode*, int> index;   // track treenode and its index in vec
        queue<TreeNode*> q;
        // build tree recursively
        TreeNode* node = new TreeNode(v[0]);
        this->root = node;
        index[this->root] = 0;
        q.push(this->root);
        while (!q.empty()) {
            TreeNode* root = q.front();
            q.pop();
            int i = index[root];
            // left child
            if (((2 * i + 1) < v.size()) && (v[2 * i + 1] != INT_MAX)) {
                TreeNode* left = new TreeNode(v[2 * i + 1]);
                root->left = left;
                q.push(left);
                index[left] = 2 * i + 1;
            }
            // right child
            if (((2 * i + 2) < v.size()) && (v[2 * i + 2] != INT_MAX)) {
                TreeNode* right = new TreeNode(v[2 * i + 2]);
                root->right = right;
                q.push(right);
                index[right] = 2 * i + 2;
            }
        }
    }
}

/**
 * @brief
 *
 * @param inorder
 * @param inorder_left_start
 * @param inorder_right_start
 * @param postorder_left_start
 * @param postorder_right_start
 * @return TreeNode*: the root of current sequence.
 */
TreeNode* BinaryTree::BuildTreeFromInorderAndPostorderHelper(
    const vector<int>& inorder, const vector<int>& postorder, int inorder_start,
    int inorder_end, int postorder_start, int postorder_end) {
    // Base case:
    if ((inorder_start > inorder_end) || (postorder_start > postorder_end)) {
        return nullptr;
    }

    // root is the last element in postorder sequence
    TreeNode* root = new TreeNode(postorder[postorder_end]);

    // NOTICE: finding root index in inorder sequence can be optimized with an index hash
    // table.
    int root_index = inorder_start;
    // find range for left and right children in inorder sequence
    for (; root_index <= inorder_end; root_index++) {
        if (inorder[root_index] == postorder[postorder_end]) {
            break;
        }
    }

    int total_length = inorder_end - inorder_start + 1;
    int length_of_left_range = root_index - inorder_start;
    int length_of_right_range = total_length - length_of_left_range - 1;

    root->left = BuildTreeFromInorderAndPostorderHelper(
        inorder, postorder, inorder_start, root_index - 1, postorder_start,
        postorder_start + length_of_left_range - 1);
    root->right = BuildTreeFromInorderAndPostorderHelper(
        inorder, postorder, root_index + 1, inorder_end,
        postorder_start + length_of_left_range, postorder_end - 1);

    return root;
}

/**
 * @brief build tree from postorder and inorder traversal sequences.
 * Hallmark of inorder sequence: (left) root (right)
 * Hallmark of postorder sequence: (left) (right) root
 *
 * So, we can figure out root from postorder sequence, and separate inorder sequence with
 * root. We can do it recursively until there is no node in the sequence.
 *
 * @param inorder
 * @param postorder
 */
void BinaryTree::BuildTreeFromInorderAndPostorder(vector<int> inorder,
                                                  vector<int> postorder) {
    this->root = BuildTreeFromInorderAndPostorderHelper(
        inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
}

/**
 * @brief we will improve the performance with an index hash table.
 *
 * @param inorder
 * @param postorder
 * @param inorder_start
 * @param inorder_end
 * @param postorder_start
 * @param postorder_end
 * @return TreeNode*
 */
TreeNode* BinaryTree::BuildTreeFromPreorderAndInorderHelper(
    const vector<int>& preorder, const vector<int>& inorder,
    unordered_map<int, int>& index_of, int preorder_start, int preorder_end,
    int inorder_start, int inorder_end) {
    if ((preorder_start > preorder_end) || (inorder_start > inorder_end)) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(preorder[preorder_start]);

    // find index of root in inorder sequence
    int root_index = index_of[preorder[preorder_start]];

    int total_length = preorder_end - preorder_start + 1;
    int length_of_left_range = root_index - inorder_start;
    int length_of_right_range = total_length - length_of_left_range - 1;

    root->left = BuildTreeFromPreorderAndInorderHelper(
        preorder, inorder, index_of, preorder_start + 1,
        preorder_start + length_of_left_range, inorder_start, root_index - 1);
    root->right = BuildTreeFromPreorderAndInorderHelper(
        preorder, inorder, index_of, preorder_start + length_of_left_range + 1,
        preorder_end, root_index + 1, inorder_end);

    return root;
}

/**
 * @brief build tree from preorder and inorder sequences.
 *
 * preorder: root (left) (right)
 * inorder: (left) root (right)
 *
 * The idea is similar to building tree from inorder and postorder sequences.
 *
 * @param preorder
 * @param inorder
 */
void BinaryTree::BuildTreeFromPreorderAndInorder(vector<int> preorder,
                                                 vector<int> inorder) {
    // map from val to index of inorder sequence
    unordered_map<int, int> index_of;
    for (int i = 0; i < inorder.size(); i++) {
        index_of[inorder[i]] = i;
    }
    this->root = BuildTreeFromPreorderAndInorderHelper(
        preorder, inorder, index_of, 0, preorder.size() - 1, 0, inorder.size() - 1);
}

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

    // reverse the output
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
 * The solution is based on that of isUnivalTree.
 *
 * There are two cases where coalescence will happen (increase 1):
 * 1. only one child and root->val == child->val and child is UnivalTree
 * 2. two children and root has the same val and count(left) == count(right) == 1 and
 * both of them are UnivalTree
 *
 * count(root) = count(left) + count(right) otherwise.
 * @param root
 * @return int
 */
int BinaryTree::countUnivalSubtreesHelper(TreeNode* root,
                                          unordered_map<TreeNode*, bool>& isUnival) {
    if (root == nullptr) return 0;   // corner case

    // both children are nullptr
    if ((root->left == nullptr) && (root->right == nullptr)) {
        isUnival[root] = true;
        return 1;
    }
    // only left: let it go down first, check if it is UnivalSubtree when backtracking
    if (root->right == nullptr) {
        int count = countUnivalSubtreesHelper(root->left, isUnival);   // go down first
        if ((isUnival[root->left]) && (root->val == root->left->val)) {
            isUnival[root] = true;
            return ++count;
        }
        return count;
    }
    // only right
    if (root->left == nullptr) {
        int count = countUnivalSubtreesHelper(root->right, isUnival);
        if ((isUnival[root->right]) && (root->val == root->right->val)) {
            isUnival[root] = true;
            return ++count;
        }
        return count;
    }
    // both are non-nullptr: 2 cases
    int leftCount = countUnivalSubtreesHelper(root->left, isUnival);
    int rightCount = countUnivalSubtreesHelper(root->right, isUnival);
    int count = leftCount + rightCount;
    // case 1: coalesce
    if ((root->left != nullptr) && isUnival[root->left] &&
        (root->val == root->left->val) && (root->right != nullptr) &&
        isUnival[root->right] && (root->val == root->right->val)) {
        isUnival[root] = true;
        return ++count;
    }
    // case 2: no coalescence
    isUnival[root] = false;
    return count;
}

int BinaryTree::countUnivalSubtrees(TreeNode* root) {
    unordered_map<TreeNode*, bool> isUnival;
    return countUnivalSubtreesHelper(root, isUnival);
}

// write your solution here
void Solution() {}