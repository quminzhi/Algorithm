#include <gtest/gtest.h>
#include "solution.hpp"
#include "que.hpp"

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

TEST(MyTests, MonotonicQueueTEST) {
    vector<int> nums = {1, 2, 3, 4, 3, -1, 4, 3, 2};
    vector<int> result = {1, 2, 3, -1, -1, -1, 2};
    EXPECT_EQ(slideWindow(nums, 3), result);
}
