#include <gtest/gtest.h>
#include "solution.hpp"
#include "knapsack.hpp"
#include "linear.hpp"

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

TEST(MyTests, ZeroOneKnapsackTEST) {
    vector<int> weights = {1, 2, 3, 4};
    vector<int> values = {2, 4, 4, 5};
    EXPECT_EQ(ZeroOneKnapsack(weights, values, 5), 8);
    EXPECT_EQ(ZeroOneKnapsackII(weights, values, 5), 8);
}

TEST(MyTests, CompleteKnapsackTEST) {
    vector<int> weights = {1, 2, 3, 4};
    vector<int> values = {2, 4, 4, 5};
    EXPECT_EQ(CompleteKnapsack(weights, values, 6), 12);
    EXPECT_EQ(CompleteKnapsackII(weights, values, 6), 12);
    EXPECT_EQ(CompleteKnapsackIII(weights, values, 6), 12);
}

TEST(MyTests, LimitedKnapsackTEST) {
    vector<int> weights = {1, 2, 3, 4};
    vector<int> values = {2, 4, 4, 5};
    vector<int> limits = {1, 1, 2, 2};
    EXPECT_EQ(LimitedKnapsack(weights, values, limits, 5), 8);
    EXPECT_EQ(LimitedKnapsackII(weights, values, limits, 5), 8);
    EXPECT_EQ(LimitedKnapsackIII(weights, values, limits, 5), 8);
}

TEST(MyTests, GroupedKnapsackTEST) {
    vector< vector<int> > items = {
        {0, 1, 2},
        {0, 2, 4},
        {1, 3, 4},
        {2, 4, 5}
    };
    EXPECT_EQ(GroupKnapsack(items, 5), 8);
    EXPECT_EQ(GroupKnapsackII(items, 5), 8);
}

TEST(MyTests, MixedKnapsackTEST) {
    vector<Item> items;
    items.push_back(Item(-1, 2, 5));
    items.push_back(Item(-1, 3, 7));
    items.push_back(Item(0, 4, 5));
    items.push_back(Item(0, 5, 6));
    items.push_back(Item(1, 2, 6, 3));
    items.push_back(Item(1, 3, 10, 5));
    EXPECT_EQ(MixedKnapsack(items, 20), 63);
}

TEST(MyTests, TrackPathTEST) {
    vector<int> weights = {1, 2, 3, 4};
    vector<int> values = {2, 4, 4, 5};
    vector<int> result = {1, 2};
    EXPECT_EQ(ZeroOneKnapsackWithTracking(weights, values, 5), result);
}

TEST(LinearDPTests, NonDescendingSubsequenceTEST) {
    EXPECT_EQ(MaxLengthOfNonDescendingSubsequence("abcd"), 4);
    EXPECT_EQ(MaxLengthOfNonDescendingSubsequence("abed"), 3);
    EXPECT_EQ(MaxLengthOfNonDescendingSubsequence("abyzdef"), 5);
    

    EXPECT_EQ(MaxLengthOfNonDescendingSubsequenceII("abcd"), "abcd");
    EXPECT_EQ(MaxLengthOfNonDescendingSubsequenceII("abed"), "abd");
    EXPECT_EQ(MaxLengthOfNonDescendingSubsequenceII("abyzdef"), "abdef");
    EXPECT_EQ(MaxLengthOfNonDescendingSubsequenceII("abedfghxyz"), "abdfghxyz");

    EXPECT_EQ(MaxLengthOfNonDescendingSubsequenceIII("abcd"), 4);
    EXPECT_EQ(MaxLengthOfNonDescendingSubsequenceIII("abed"), 3);
    EXPECT_EQ(MaxLengthOfNonDescendingSubsequenceIII("abyzdef"), 5);
}

TEST(LinearDPTests, LongestCommonSubsequenceTEST) {
    EXPECT_EQ(LongestCommonSubsequence("abc", "abc"), 3);
    EXPECT_EQ(LongestCommonSubsequence("abdc", "aebc"), 3);
} 

TEST(LinearDPTests, MinEditDistanceTEST) {
    EXPECT_EQ(MinEditDistance("abdc", "aec"), 2);
}

TEST(RangeDPTests, MergeStonesTEST) {
    vector<int> stones = {1, 3, 5, 2};
    EXPECT_EQ(MergeStones(stones), 22);
}

TEST(MyTests, NumberDivisionTEST) {
    EXPECT_EQ(IntegerDivision(5), 7);
    EXPECT_EQ(IntegerDivisionII(5), 7);
}