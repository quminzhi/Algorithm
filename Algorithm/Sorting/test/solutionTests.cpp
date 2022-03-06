#include <gtest/gtest.h>

#include "solution.hpp"
#include "sorting.hpp"

// If there is a set of tests that share same context, we can encapsulate it in to a
// class.
class TestWithContext : public ::testing::Test {
   public:
    vector<int> v1 = {2, 5, 4, 2, 3, 0, 9};
    vector<int> expected1 = {0, 2, 2, 3, 4, 5, 9};

    vector<int> v2;
    vector<int> expected2;

    virtual void SetUp() override {
        for (int i = 0; i < 1000000; i++) {
            v2.push_back(i);
            expected2.push_back(i);
        }
    }
    virtual void TearDown() override {}
};

// TEST_F(<testsuite name>, testname)
TEST_F(TestWithContext, QuickSortTEST) {
    qsort(v1, 0, v1.size() - 1);
    EXPECT_EQ(v1, expected1);

    qsort(v2, 0, v2.size() - 1);
    EXPECT_EQ(v2, expected2);
}

TEST_F(TestWithContext, MergeSortTEST) {
    vector<int> tmp(v1.size(), 0);
    merge_sort(v1, tmp, 0, v1.size() - 1);
    EXPECT_EQ(v1, expected1);

    vector<int> tmp2(v2.size(), 0);
    merge_sort(v2, tmp2, 0, v2.size() - 1);
    EXPECT_EQ(v2, expected2);
}

TEST(MyTests, QuickSortTEST) {
    EXPECT_TRUE(true);
}