#include "populatingpointers.h"
#include <queue>

/**
 * @brief connect
 * @param root: the root of tree
 * @return a tree has been connected
 * Add new property 'level' to each node. Traverse node in level order and connect
 * them.
 */
Node* connect(Node* root) {
    class QueueNode {
    public:
        QueueNode(int _level, Node* _node)
            : node(_node), level(_level) {}

        Node* node;
        int level;
    };

    if (root == nullptr) return root;
    QueueNode first(0, root);
    queue<QueueNode> que;
    que.push(first);
    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();
        if (!que.empty()) {
            QueueNode next = que.front();
            if (cur.level == next.level) {
                cur.node->next = next.node;
            }
        }
        if (cur.node->left != nullptr) {
            que.push(QueueNode(cur.level+1, cur.node->left));
        }
        if (cur.node->right != nullptr) {
            que.push(QueueNode(cur.level+1, cur.node->right));
        }
    }

    return root;
}
