#include <gtest/gtest.h>
#include "solution.hpp"
#include "knapsack.hpp"

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

TEST(MyTests, ZeroOneKnapsackTEST) {
    vector<int> weights = {1, 2, 3, 4};
    vector<int> values = {2, 4, 4, 5};
    EXPECT_EQ(ZeroOneKnapsack(weights, values, 5), 8);
    EXPECT_EQ(ZeroOneKnapsackII(weights, values, 5), 8);
}

TEST(MyTests, CompleteKnapsackTEST) {
    vector<int> weights = {1, 2, 3, 4};
    vector<int> values = {2, 4, 4, 5};
    EXPECT_EQ(CompleteKnapsack(weights, values, 6), 12);
    EXPECT_EQ(CompleteKnapsackII(weights, values, 6), 12);
    EXPECT_EQ(CompleteKnapsackIII(weights, values, 6), 12);
}

TEST(MyTests, LimitedKnapsackTEST) {
    vector<int> weights = {1, 2, 3, 4};
    vector<int> values = {2, 4, 4, 5};
    vector<int> limits = {1, 1, 2, 2};
    EXPECT_EQ(LimitedKnapsack(weights, values, limits, 5), 8);
}
