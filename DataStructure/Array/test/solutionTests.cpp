#include <gtest/gtest.h>
#include "solution.hpp"
#include "list.hpp"

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
    list.Traverse();
    list.InsertAbs(5, 2);
    list.Traverse();
    list.DeleteAbs(1);
    list.Traverse();
}
