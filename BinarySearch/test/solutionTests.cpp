#include <gtest/gtest.h>
#include "binarysearch.hpp"
#include "solution.hpp"

// If there is a set of tests that share same context, we can encapsulate it in to a class.
class TestWithContext : public ::testing::Test {
public:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

// TEST_F(<testsuite name>, testname)
TEST_F(TestWithContext, TestWithContextDemo1) {
    EXPECT_TRUE(true);
}

TEST(MyTests, BinarySearchTEST) {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    // EXPECT_EQ(searchRotatedArr(nums, 6), 2);
    // EXPECT_EQ(searchRotatedArr(nums, 0), 4);

    vector<int> nums2 = {3, 1};
    EXPECT_EQ(searchRotatedArr(nums2, 1), 1);
}
