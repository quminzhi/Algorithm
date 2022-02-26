#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "heap.hpp"
#include "solution.hpp"
using namespace std;

// If there is a set of tests that share same context, we can encapsulate it in to a
// class.
class TestWithContext : public ::testing::Test {
   public:
    virtual void SetUp() override {}

    virtual void TearDown() override {}
};

// TEST_F(<testsuite name>, testname)
TEST_F(TestWithContext, TestWithContextDemo1) { EXPECT_TRUE(true); }

TEST(MyTests, HeapTEST) {
    vector<int> v = {99, 82, 17};
    Heap h(v);
    h.push(10);
    EXPECT_EQ(h.peek(), 10);
    h.push(24);
    h.pop();
    EXPECT_EQ(h.peek(), 17);
    h.pop();
    EXPECT_EQ(h.peek(), 24);
    h.pop();
    h.pop();
    EXPECT_EQ(h.peek(), 99);
    h.pop();
    EXPECT_EQ(h.size(), 0);
}