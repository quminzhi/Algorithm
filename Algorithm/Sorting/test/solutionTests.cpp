#include <gtest/gtest.h>
#include "solution.hpp"
#include "sorting.hpp"

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

TEST(MyTests, QuickSortTEST) {
    vector<int> v1 = {2, 5, 4, 2, 3, 0, 9};
    vector<int> expected1 = {0, 2, 2, 3, 4, 5, 9};
    qsort(v1, 0, v1.size()-1);
    EXPECT_EQ(v1, expected1);

    int test_size = 10000000;
    vector<int> v2(test_size, 0);
    for (int i = 0; i < test_size; i++) {
        v2[i] = i;
    }
    vector<int> expected2(v2.begin(), v2.end());
    qsort(v2, 0, v2.size()-1);
    EXPECT_EQ(v2, expected2);
}
