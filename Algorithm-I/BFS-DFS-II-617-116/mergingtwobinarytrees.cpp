#include "mergingtwobinarytrees.h"
#include <vector>
#include <queue>
#include "testing/SimpleTest.h"
using namespace std;

void traverseInLevelOrder(TreeNode* root, vector<int>& res) {
    int NULL_VAL = 10001;
    queue<TreeNode*> que;
    que.push(root);
    while (!que.empty()) {
        TreeNode* cur = que.front();
        que.pop();
        if (cur != nullptr) {
            res.push_back(cur->val);
            que.push(cur->left);
            que.push(cur->right);
        }
        else {
            res.push_back(NULL_VAL);
        }
    }
}

// !!!: works for complete binary tree
TreeNode* constructTreeInLevelOrder(TreeNode* root, const vector<int>& res, int i) {
    static int NULL_VAL = 10001;
    // TODO: if there is possible node, then update node.
    if ((i < res.size()) && (res[i] != NULL_VAL)) {
        root = new TreeNode(res[i]);
        root->left = constructTreeInLevelOrder(root->left, res, 2 * i + 1);
        root->right = constructTreeInLevelOrder(root->right, res, 2 * i + 2);
    }

    return root;
}

/*
 * Function: mergeTrees_sol1
 * ------------------------------------
 * The function will return a new tree which is the merge of two trees given by root1 and
 * root2.
 *
 * 1. Get the result of level-order traverse for tree1 and tree2.
 * 2. Add two results, and construct new tree with the addition result.
 *
 * T: O(N)
 */
TreeNode* mergeTrees_sol1(TreeNode* root1, TreeNode* root2) {
    int NULL_VAL = 10001;
    vector<int> res1;
    traverseInLevelOrder(root1, res1);
    vector<int> res2;
    traverseInLevelOrder(root2, res2);
    if (res1.size() > res2.size()) {
        res2.resize(res1.size(), NULL_VAL);
    }
    else {
        res1.resize(res2.size(), NULL_VAL);
    }

    // TODO: get new tree vector in res1
    for (int i = 0; i < res1.size(); i++) {
        res1[i] += res2[i];
        if (res1[i] > NULL_VAL) {  // for null
            res1[i] -= NULL_VAL;
        }
    }

    TreeNode* root = nullptr;
    root = constructTreeInLevelOrder(root, res1, 0);
    return root;
}


/*
 * Function: mergeTrees_sol2
 * ------------------------------------
 * We will put result into root1.
 *
 * Algorithm:
 * 1. if root1 is nullptr, then put root2 as the child, and vice versa.
 * 2. if they are both non-nullptr, then add value and traverse their left child and
 * right child simultaneously.
 */
TreeNode* mergeTrees_sol2(TreeNode* root1, TreeNode* root2) {
    if (root1 == nullptr) {
        return root2;
    }
    if (root2 == nullptr) {
        return root1;
    }

    root1->val += root2->val;
    root1->left = mergeTrees_sol2(root1->left, root2->left);
    root1->right = mergeTrees_sol2(root1->right, root2->right);

    return root1;
}


/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for constructTreeInLevelOrder() and TraverseInOrderLevel():") {
    int NULL_VAL = 10001;
    vector<int> v = {2, 1, 3, NULL_VAL, 4, NULL_VAL, 7};
    TreeNode* root = nullptr;
    root = constructTreeInLevelOrder(root, v, 0);
    EXPECT_EQUAL(root->val, 2);
    EXPECT_EQUAL(root->left->val, 1);
    EXPECT_EQUAL(root->right->val, 3);
    EXPECT(root->left->left == nullptr);
    EXPECT(root->left->right->val == 4);
    EXPECT(root->right->left == nullptr);
    EXPECT(root->right->right->val == 7);

    vector<int> res;
    traverseInLevelOrder(root, res);
    EXPECT_EQUAL(res.size(), 11); // 7 + 4
}

PROVIDED_TEST("Test for mergeTrees_sol1():") {
    int NULL_VAL = 10001;
    vector<int> v1 = {1, 3, 2, 5};
    vector<int> v2 = {2, 1, 3, NULL_VAL, 4, NULL_VAL, 7};
    TreeNode* root1 = nullptr;
    root1 = constructTreeInLevelOrder(root1, v1, 0);
    TreeNode* root2 = nullptr;
    root2 = constructTreeInLevelOrder(root2, v2, 0);

    TreeNode* root = mergeTrees_sol1(root1, root2);

    EXPECT_EQUAL(root->val, 3);
    EXPECT_EQUAL(root->left->val, 4);
    EXPECT_EQUAL(root->right->val, 5);
    EXPECT_EQUAL(root->left->left->val, 5);
    EXPECT_EQUAL(root->left->right->val, 4);
    EXPECT(root->right->left == nullptr);
    EXPECT_EQUAL(root->right->right->val, 7);
}

PROVIDED_TEST("Test for mergeTrees_sol2():") {
    int NULL_VAL = 10001;
    vector<int> v1 = {1, 2, NULL_VAL, 3};
    TreeNode* root1 = nullptr;
    root1 = constructTreeInLevelOrder(root1, v1, 0);
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    root2->right->right = new TreeNode(3);

    TreeNode* root = mergeTrees_sol2(root1, root2);

    EXPECT_EQUAL(root->val, 2);
    EXPECT_EQUAL(root->left->val, 2);
    EXPECT_EQUAL(root->right->val, 2);
    EXPECT_EQUAL(root->left->left->val, 3);
    EXPECT(root->left->right == nullptr);
    EXPECT(root->right->left == nullptr);
    EXPECT_EQUAL(root->right->right->val, 3);
}
