#include <gtest/gtest.h>
#include "../example.hpp"

// If there is a set of tests that share same context, we can encapsulate it in to a class.

class ExampleTests : public ::testing::Test {
public:
    int* x;

    int getX() {
        return *x;
    }

    virtual void SetUp() override {
        x = new int(5);
    }

    virtual void TearDown() override {
        delete x;
    }
};

TEST_F(ExampleTests, DemonstrateTestMacros) {
    EXPECT_TRUE(true);
    // EXPECT_TRUE(false);
    EXPECT_EQ(true, true);

    double d1 = 1.2;
    // double d2 = 2.1;
    double d2 = 1.2;
    // print when it failed
    EXPECT_DOUBLE_EQ(d1, d2) << "OOOOh it failed";

    EXPECT_EQ(getX(), 5);
}

TEST_F(ExampleTests, ExampleTest1111) {
    EXPECT_EQ(getX(), 3);
}

TEST(OtherTests, SampleTestCases) {
    EXPECT_TRUE(true);   
}