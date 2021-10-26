#ifndef POPULATINGNEXTRIGHTPOINTERS_H
#define POPULATINGNEXTRIGHTPOINTERS_H

/**
 * You are given a perfect binary tree where all leaves are on the same level, and
 * every parent has two children. The binary tree has the following definition.
 * Populate each next pointer to point to its next right node. If there is no next
 * right node, the next pointer should be set to NULL.
 *
 * Initially, all next pointers are set to NULL.
 *
 * Perfect Tree:  1 ---> nullptr
 *          2    --->    3  ---> nullptr
 *      4 ---> 5 ---> 6 ---> 5  ---> nullptr
 */
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;  // points to its right siblings

    Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

Node* connect_sol1(Node* root);
Node* connect_sol2(Node* root);


#endif // POPULATINGNEXTRIGHTPOINTERS_H
