#include <gtest/gtest.h>
#include "solution.hpp"
#include "ds.hpp"

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

TEST(MyTests, MonotonicStackTEST) {
    vector<int> nums = {3, 4, 2, 5, 7};
    vector<int> res = {-1, 3, -1, 2, 5};
    EXPECT_EQ(closestIndex(nums), res);
}

TEST(MyTests, KMP_TEST) {
    string s = "abababbbabbababa";
    string pattern = "aba";
    vector<int> res = {0, 2, 11, 13};
    EXPECT_EQ(kmp(s, pattern), res);
}

TEST(MyTestsTest, SegmentTreeTEST) {
    vector<int> v = {1, 3, 4, 5, 20, 17, 4, 19, 25};
    SegmentTree st(v);
    EXPECT_EQ(st.query(1, 1, 3), 4);
    EXPECT_EQ(st.query(1, 1, 4), 5);
    EXPECT_EQ(st.query(1, 3, 5), 20);
    EXPECT_EQ(st.query(1, 3, 6), 20);
}

TEST(MyTestsTest, MaxSubarrayTEST) {
    vector<int> v = {1, 3, 4, 5, -20, 17, 4, 19, 25};
    MaxSubarray st(v);
    EXPECT_EQ(st.query(1, 1, 3).vMax, 8);
    EXPECT_EQ(st.query(1, 1, 4).vMax, 13);
    EXPECT_EQ(st.query(1, 3, 5).vMax, 9);
    EXPECT_EQ(st.query(1, 3, 6).vMax, 17);
}

TEST(MyTestsTest, GCDTreeTEST) {
    vector<int> v = {1, 2, 4, 5, -20, 16, 4, 19, 25};
    GCDTree st(v);
    EXPECT_EQ(st.query(1, 3), 1);
    EXPECT_EQ(st.query(2, 3), 2);
    EXPECT_EQ(st.query(5, 7), 4);
}