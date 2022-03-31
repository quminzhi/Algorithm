#include <gtest/gtest.h>
#include "solution.hpp"
#include "bit.hpp"

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

TEST(MyTests, BitCounterCases) {
    EXPECT_EQ(BitCounter(0), 0);
    EXPECT_EQ(BitCounter(1), 1);
    EXPECT_EQ(BitCounter(5), 2);
    EXPECT_EQ(BitCounter(7), 3);
    EXPECT_EQ(BitCounter(15), 4);
    EXPECT_EQ(BitCounter(16), 1);
    EXPECT_EQ(BitCounter(255), 8);
    EXPECT_EQ(BitCounter(256), 1);
}

TEST(MyTests, BitCounterIICases) {
    EXPECT_EQ(BitCounterII(0), 0);
    EXPECT_EQ(BitCounterII(1), 1);
    EXPECT_EQ(BitCounterII(5), 2);
    EXPECT_EQ(BitCounterII(7), 3);
    EXPECT_EQ(BitCounterII(15), 4);
    EXPECT_EQ(BitCounterII(16), 1);
    EXPECT_EQ(BitCounterII(255), 8);
    EXPECT_EQ(BitCounterII(256), 1);
}
