#include <gtest/gtest.h>
#include "solution.hpp"

// If there is a set of tests that share same context, we can encapsulate it in to a class.
class TestWithContext : public ::testing::Test {
public:
    int* x;

    int getX() {
        return 3;
    }

    virtual void SetUp() override {
        x = new int(5);
    }

    virtual void TearDown() override {
        delete x;
    }
};

// TEST_F(<testsuite name>, testname)
TEST_F(TestWithContext, TestWithContextDemo1) {
    EXPECT_TRUE(true);
    // EXPECT_TRUE(false);
    EXPECT_EQ(true, true);

    double d1 = 1.2;
    double d2 = 1.2;
    // print when it failed
    EXPECT_DOUBLE_EQ(d1, d2) << "OOOOh it failed";

    EXPECT_EQ(getX(), 3);
}

TEST(MyTests, SampleTestCases) {
    EXPECT_TRUE(true);
}