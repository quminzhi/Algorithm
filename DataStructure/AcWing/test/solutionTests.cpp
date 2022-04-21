#include <gtest/gtest.h>
#include "solution.hpp"
#include "algo.hpp"

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

TEST(MyTests, MonotonicStackTEST) {
    vector<int> nums = {3, 4, 2, 5, 7};
    vector<int> res = {-1, 3, -1, 2, 5};
    EXPECT_EQ(closestIndex(nums), res);
}

TEST(MyTest, KMP_TEST) {
    string s = "abababbbabbababa";
    string pattern = "aba";
    vector<int> res = {0, 2, 11, 13};
    EXPECT_EQ(kmp(s, pattern), res);
}