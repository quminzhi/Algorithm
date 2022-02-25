# Binary Tree

## Problems

### Count Univalue Subtrees

> Given the root of a binary tree, return the number of uni-value subtrees.
>
> A uni-value subtree means all nodes of the subtree have the same value.

There are two cases where coalescence will happen (increase 1):

- only one child and root->val == child->val and child is UnivalTree.
- two children and root has the same val and count(left) == count(right) == 1 and both of them are UnivalTree.

```c++
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
    if ((root->left == nullptr)) {
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
```

Key:

- How to track state of each node: `unordered_map` or `vector`.
- How to master down stream and up stream (backtracking): code after recursive call is to handle backtracking.
- `return i++` != `return ++i`.

### Connect II

> Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
>
> Initially, all next pointers are set to NULL.

The key to this problem is to practice how to traverse tree in level order. Particularly, solve all nodes in each level once at a time.

At each loop, we will pop all nodes (at the same level) and push all 1-gen children of them.

```c++
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
```

### Non-recursive Inorder Traversal

> Given a tree, inorder traverse the tree in a non-recursive way.

Notice the inorder traversal follows pattern of (left) root (right). We will resort to greedy algorithm to solve it.

- find the leftmost node and print it out.
- print out root (which is on the top of the stack) and put pointer to right child if possible. (repeat last step)

```c++
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
```

### Lowest Common Ancestor

> Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
>
> According to the definition of LCA on Wikipedia: "The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself)."

Our solution is to search two nodes first and record two search path. Two search paths must follow patterns:

```bash
# c means common node, d means different nodes
p_path: c c c c d d d d d
q_path: c c c c d d
```

Therefore, we just need to find the last common node.

```c++
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
```

Key:

- Searching target and recording path worth being discussed here. This is a pattern of finding one solution path and recording the path.

```c++
bool searchPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
    // base case

    // found
    if (found) {
        path.push_back(root);
        return true;
    }

    // not found
    path.push_back(root); // record
    for (type choice: choices) {
        if (choice works) { // meaning return true
            return true;
        }
    }

    // all choices through this node failed
    path.pop_back() // erase
    return false;
}
```