#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * @brief For special problems
 */
class Node {
   public:
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {};
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {};
    Node(int _val, TreeNode* left, TreeNode* right)
        : val(_val), left(left), right(right), next(nullptr) {};

    int val;
    Node* left;
    Node* right;
    Node* next;
};

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

    // building tree
    void buildTreeRec(vector<int> v);
    void BuildTreeFromInorderAndPostorder(vector<int> inorder, vector<int> postorder);
    void BuildTreeFromPreorderAndInorder(vector<int> preorder, vector<int> inorder);

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);

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

    TreeNode* BuildTreeFromInorderAndPostorderHelper(const vector<int>& inorder,
                                                     const vector<int>& postorder,
                                                     int inorder_start, int inorder_end,
                                                     int postorder_start,
                                                     int postorder_end);

    TreeNode* BuildTreeFromPreorderAndInorderHelper(const vector<int>& preorder,
                                                    const vector<int>& inorder,
                                                    unordered_map<int, int>& index_of,
                                                    int preorder_start, int preorder_end,
                                                    int inorder_start, int inorder_end);

    void searchHelper(TreeNode* root, TreeNode* target, vector<TreeNode*>& path);
};

void Solution();

#endif /* SOLUTION_HPP */