#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

class TreeNode {
   public:
    TreeNode() : val(0), left(nullptr), right(nullptr){};
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr){};
    TreeNode(int _val, TreeNode* left, TreeNode* right)
        : val(_val), left(left), right(right){};

    int val;
    TreeNode* left;
    TreeNode* right;
};

class BinaryTree {
   public:
    BinaryTree() : root(nullptr){};
    BinaryTree(TreeNode* _root) : root(_root){};
    BinaryTree(vector<int> v);

    // Traverse:
    vector<int> preorderTraversal(TreeNode* root);
    vector<int> inorderTraversal(TreeNode* root);
    vector<int> postorderTraversal(TreeNode* root);
    vector<vector<int> > levelOrderTraversal(TreeNode* root);

    // Query:
    int maxDepth(TreeNode* root);
    bool isStrictlySymmetric(TreeNode* root);
    bool isSymmetric(TreeNode* root);
    bool isMirror(TreeNode* left, TreeNode* right);
    bool hasPathSum(TreeNode* root, int targetSum);
    bool isUnivalTree(TreeNode* root);
    int countUnivalSubtrees(TreeNode* root);

    TreeNode* root;

   private:
    void clear();

    // Traverse:
    void preorderTraversalHelper(TreeNode* root, vector<int>& result);
    void inorderTraversalHelper(TreeNode* root, vector<int>& result);
    void postorderTraversalHelper(TreeNode* root, vector<int>& result);
    void levelOrderTraversalHelper(TreeNode* root, vector<vector<int> >& result);
    // NR: non-recursive implementation
    void preorderTraversalHelperNR(TreeNode* root, vector<int>& result);
    void inorderTraversalHelperNR(TreeNode* root, vector<int>& result);
    void postorderTraversalHelperNR(TreeNode* root, vector<int>& result);

    int countUnivalSubtreesHelper(TreeNode* root,
                                  unordered_map<TreeNode*, bool>& isUnival);
};

void Solution();

#endif /* SOLUTION_HPP */