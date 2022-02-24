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
    vector<int> v = {1, 2, 3, 4, INT_MAX, 5, 6};
    BinaryTree bt(v);
    vector<int> inorder = {4, 2, 1, 5, 3, 6};
    EXPECT_EQ(bt.inorderTraversal(bt.root), inorder);
    EXPECT_TRUE(true);
}

TEST(MyTests, SampleTestCases) { EXPECT_TRUE(true); }