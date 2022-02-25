#include <gtest/gtest.h>

#include "solution.hpp"

// If there is a set of tests that share same context, we can encapsulate it in to a
// class.
class TestWithContext : public ::testing::Test {
   public:

    virtual void SetUp() override {}

    virtual void TearDown() override {}
};

// TEST_F(<testsuite name>, testname)
TEST_F(TestWithContext, TestWithContextDemo1) {
    EXPECT_TRUE(true);
}

TEST(MyTests, InorderTraversalTEST) {
    vector<int> v = {1, 2, 3, 4, INT_MAX, 5, 6};
    BinaryTree bt(v);
    vector<int> inorder = {4, 2, 1, 5, 3, 6};
    EXPECT_EQ(bt.inorderTraversal(bt.root), inorder);
}

TEST(MyTests, PreorderAndInorderConstruction) {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    BinaryTree bt;
    bt.BuildTreeFromPreorderAndInorder(preorder, inorder);
    vector<int> postorder = {9, 15, 7, 20, 3};
    EXPECT_EQ(bt.postorderTraversal(bt.root), postorder);
}

TEST(MyTests, SerializeAndDeserialize) {
    vector<int> v = {1, 2, 3, INT_MAX, INT_MAX, 4, 5};
    BinaryTree bt(v);
    string stream = serialize(bt.root);
    std::cout << stream << std::endl;
    TreeNode* root = deserialize(stream);
    vector<int> inorder = {2, 1, 4, 3, 5};
    EXPECT_EQ(bt.inorderTraversal(root), inorder);
}