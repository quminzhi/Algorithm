#include <gtest/gtest.h>
#include "solution.hpp"
#include "list.hpp"
#include "sq.hpp"

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

TEST(MyTests, SinglyLinkedListTestCases) {
    SinglyLinkedList list;
    list.HeadInsert(1);
    list.HeadInsert(2);
    list.HeadInsert(3);
    // list.Traverse();
    list.InsertAbs(5, 2);
    // list.Traverse();
    list.DeleteAbs(1);
    // list.Traverse();
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