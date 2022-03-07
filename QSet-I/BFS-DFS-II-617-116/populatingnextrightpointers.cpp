#include "populatingnextrightpointers.h"
#include <queue>
using namespace std;

/*
 * Function: connect_sol1
 * ------------------------------------
 * How to connect siblings for a perfect binary tree?
 *
 * Think about easy case: how to connect siblings with same parents only?
 * If left and right children exist, just let the next of left child point to right child.
 *
 * Question comes to how to connect siblings with different parents?
 * Seems difficult. But if we know the connection of parents, then we are able to utilize
 * it to connect their next generations.
 *
 * We can solve it recursively:
 * if node is not nullptr,
 *      1. connect my childrens
 *      2. connect my left child' right child with my right child's left child if they exist
 *
 * But is that right? Unfortunately No.
 * What we need to connect is the left subtree's right edge and right subtree's left edge.
 */
Node* connect_sol1(Node* root) {
    if ((root != nullptr) && (root->left != nullptr)) {
        // TODO: connect my left subtree's right edge to my right subtree's left edge
        Node* leftSubTree = root->left;
        Node* rightSubTree = root->right;
        while ((leftSubTree != nullptr) &&
               (rightSubTree != nullptr)) {
            leftSubTree->next = rightSubTree;
            leftSubTree = leftSubTree->right;
            rightSubTree = rightSubTree->left;
        }

        root->left = connect_sol1(root->left);
        root->right = connect_sol1(root->right);
    }

    return root;
}

/*
 * Function: connect_sol2
 * ------------------------------------
 * Solve it in level-order traverse.
 */
Node* connect_sol2(Node* root) {
    class QueueNode {
    public:
        int level;
        Node* node;

        QueueNode(int level, Node* node) : level(level), node(node) {}
    };

    queue<QueueNode> que;
    if (root == nullptr) return root;
    que.push(QueueNode(0, root));
    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();
        QueueNode next = que.front();
        if (cur.level == next.level) {
            cur.node->next = next.node;
        }
        if (cur.node->left != nullptr) {
            que.push(QueueNode(cur.level + 1, cur.node->left));
        }
        if (cur.node->right != nullptr) {
            que.push(QueueNode(cur.level + 1, cur.node->right));
        }
    }

    return root;
}
