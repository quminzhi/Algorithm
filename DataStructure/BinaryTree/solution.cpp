#include "solution.hpp"

#include <iostream>
#include <sstream>
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

/**
 * @brief Populating next right pointers in each node for a complete tree
 * In this problem, we only focus on one thing, that is connect all nodes on the right
 * edge of left children and those on the left edge of right children.
 * @param root
 * @return Node*
 */
Node* connect(Node* root) {
    if (root == nullptr) return nullptr;

    // connect right edge of left children and left edge of right children
    Node* left = root->left;
    Node* right = root->right;
    while ((left != nullptr) && (right != nullptr)) {
        left->next = right;
        left = left->right;
        right = right->left;
    }

    // recursively solve its children
    connect(root->left);
    connect(root->right);
    return root;
}

/**
 * @brief Populating right next pointer in each node for an arbitrary tree
 * For arbitrary trees, it can be solved with level traversal.
 * @param root
 * @return Node*
 */
Node* connect2(Node* root) {
    if (root == nullptr) return nullptr;   // corner case
    queue<Node*> que;
    que.push(root);
    while (!que.empty()) {
        // solve all nodes in a level at once
        int size = que.size();
        Node* last = nullptr;   // save previous node of 'cur'
        for (int i = 0; i < size; i++) {
            Node* cur = que.front();
            que.pop();

            if (cur->left != nullptr) que.push(cur->left);
            if (cur->right != nullptr) que.push(cur->right);

            if (last != nullptr) last->next = cur;   // connect
            last = cur;                              // update last
        }
    }

    return root;
}

/**
 * @brief search and save search path for target
 *
 * @param root
 * @param target
 * @param path
 */
bool BinaryTree::searchHelper(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
    if (root == nullptr) return false;
    if (root == target) {
        // found
        path.push_back(target);
        return true;
    }

    path.push_back(root);
    // left search
    if (searchHelper(root->left, target, path)) {
        return true;
    }
    // right search
    if (searchHelper(root->right, target, path)) {
        return true;
    }

    path.pop_back();
    return false;
}

/**
 * @brief find the lowest common ancestor (LCA) of two given nodes in the tree.
 * The lowest common ancestor is defined between two nodes p and q as the lowest node in T
 * that has both p and q as descendants (where we allow a node to be a descendant of
 * itself).
 *
 * Notice all node values are UNIQUE. Two paths must follow:
 *
 * p_path: (common path) -> other nodes
 * q_path: (common path) -> other nodes
 *
 * - Searching p and q with DFS and recording search path for them.
 * - The lowest common ancestor is the rightmost common node of two paths.
 *
 * @param root
 * @param p
 * @param q
 * @return TreeNode*: the pointer to lowest common ancestor of p and q
 */
TreeNode* BinaryTree::lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // search p and q
    vector<TreeNode*> p_path;
    vector<TreeNode*> q_path;
    searchHelper(root, p, p_path);
    searchHelper(root, q, q_path);

    // find rightmost common node
    int lca_idx = 0;
    int size = min(p_path.size(), q_path.size());
    for (int i = 0; i < size; i++) {
        if (p_path[i] == q_path[i]) {
            lca_idx = i;
        } else {
            break;
        }
    }

    return p_path[lca_idx];
}

/**
 * @brief serialize a tree into a string stream.
 * The key is to find a sequence that can save meta data and relationship between nodes.
 *
 * As we did before, we can build a tree from the combination of inorder sequence and
 * preorder sequence, or that of inorder sequence and postorder sequence. Is it possible
 * to build tree with only one sequence? The answer is YES. But we need to make a minor
 * modification to three traversals. That is adding 'null' string to indicate nullptr.
 *
 * So we have four ways to serialize and deserialize a tree.
 *
 * - DFS includes 1. preorder sequence, 2. inorder sequence, 3. postorder sequence.
 * - BFS includes 4. level order sequence.
 *
 * We will implement preorder sequence.
 *
 * @param root
 * @return string
 */
string serialize(TreeNode* root) {
    if (root == nullptr) return "";
    string stream;
    string delimiter = ",";
    // iterative implementation of preorder traversal
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* cur = s.top();
        s.pop();
        // serialize current node (maybe nullptr)
        if (cur == nullptr) {
            stream += string("null") + delimiter;
        } else {
            // convert integer to a string
            stringstream ss;
            ss << cur->val;
            string str = ss.str();
            stream += str + delimiter;
            // push right first, FILO
            s.push(cur->right);
            s.push(cur->left);
        }
    }

    // delete the last ','
    stream.pop_back();
    return stream;
}

/**
 * @brief deserialize a string stream and build a tree.
 * Deserialize is a reverse operation of serialization. We can solve it with a stack.
 * 
 * Decode stream by delimiter is important.
 * 
 * The stack is used to cache nodes being processed:
 * - if left and right children of top node are solved, then pop it.
 * - if left child is not solved, link it with the new node (if tokens[i] is not
 * "null" or nullptr (if tokens[i] is "null"). Here we assume it is "null" and update
 * it if not "null".
 * - update i and push(new node) if new node is not nullptr.
 * 
 * @param data
 * @return TreeNode*
 */
TreeNode* deserialize(string stream) {
    if (stream.size() == 0) return nullptr;
    vector<string> tokens;
    // separate stream by delimiter ','
    string delimiter = ",";
    size_t pos = 0;
    string token;
    while ((pos = stream.find(delimiter)) != string::npos) {
        token = stream.substr(0, pos);
        tokens.push_back(token);
        stream.erase(0, pos + delimiter.length());   // remove solved token
    }
    tokens.push_back(stream);   // the last token

    for (string& token: tokens) {
        std::cout << token << std::endl;
    }

    if (tokens.size() == 0) return nullptr;   // no token in stream

    // Initialize nodes to point to unsolved, a placeholder
    TreeNode* unsolved = new TreeNode();
    TreeNode* root = new TreeNode(std::stoi(tokens[0]), unsolved, unsolved);
    stack<TreeNode*> s;
    s.push(root);
    int size = tokens.size();
    int i = 1;
    while ((i < size) && (!s.empty())) {
        TreeNode* cur = s.top();
        // if current node is solved, meaning two children have been assigned
        if ((cur->left != unsolved) && (cur->right != unsolved)) {
            s.pop();
            continue;
        }

        TreeNode* node = nullptr;   // assume tokens[i] is "null"
        if (tokens[i] != "null") {
            // update: create new node if tokens[i] != "null"
            node = new TreeNode(std::stoi(tokens[i]), unsolved, unsolved);
        }

        // link to current node
        if (cur->left == unsolved) {
            cur->left = node;
        } else {
            cur->right = node;
        }

        // update
        i++;
        if (node != nullptr) s.push(node);
    }

    delete unsolved;
    return root;
}

// write your solution here
void Solution() {}