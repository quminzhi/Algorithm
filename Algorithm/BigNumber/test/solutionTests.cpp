#include <gtest/gtest.h>
#include "solution.hpp"
#include "big.hpp"

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

TEST(MyTests, BigTestCases) {
    Big opt("1999999999", "1");
    EXPECT_EQ(opt.add(), "2000000000");
    EXPECT_EQ(opt.add(opt.v1, opt.v2), "2000000000");
    Big opt2("999", "1");
    EXPECT_EQ(opt2.add(), "1000");
    EXPECT_EQ(opt2.add(opt2.v1, opt2.v2), "1000");

    Big opt3("100", "1");
    EXPECT_EQ(opt3.sub(), "99");
    Big opt4("1", "100");
    EXPECT_EQ(opt4.sub(), "-99");
    Big opt5("11111", "11110");
    EXPECT_EQ(opt5.sub(), "1");

    Big opt6("1936", "28");
    EXPECT_EQ(opt6.mul(), "54208");
}
