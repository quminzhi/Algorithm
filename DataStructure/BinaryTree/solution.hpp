#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <vector>
using namespace std;

class TreeNode {
public:
    TreeNode()
        : val(0), left(nullptr), right(nullptr) {};
    TreeNode(int _val)
        : val(_val), left(nullptr), right(nullptr) {};
    TreeNode(int _val, TreeNode* left, TreeNode* right)
        : val(_val), left(left), right(right) {};

    int val;
    TreeNode* left;
    TreeNode* right;
};

class BinaryTree {
public:
    BinaryTree()
        : root(nullptr) {};
    BinaryTree(TreeNode* _root)
        : root(_root) {};
    BinaryTree(vector<int> v);

    // Traverse:
    vector<int> preorderTraversal(TreeNode* root);
    vector<int> inorderTraversal(TreeNode* root);
    vector<int> postorderTraversal(TreeNode* root);

    ~BinaryTree();

    TreeNode* root;
private:
    void clear();

    // Traverse:
    void preorderTraversalHelper(TreeNode* root, vector<int>& result)
    void inorderTraversalHelper(TreeNode* root, vector<int>& result)
    void postorderTraversalHelper(TreeNode* root, vector<int>& result)
    // NR: non-recursive implementation
    void preorderTraversalHelperNR(TreeNode* root, vector<int>& result)
    void inorderTraversalHelperNR(TreeNode* root, vector<int>& result)
    void postorderTraversalHelperNR(TreeNode* root, vector<int>& result)
};

void Solution();

#endif /* EXAMPLE_HPP */