#include <gtest/gtest.h>

#include "knapsack.hpp"
#include "linear.hpp"
#include "problems.hpp"
#include "solution.hpp"

// If there is a set of tests that share same context, we can encapsulate it in to a
// class.
class TestWithContext : public ::testing::Test {
   public:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

// TEST_F(<testsuite name>, testname)
TEST_F(TestWithContext, TestWithContextDemo1) { EXPECT_TRUE(true); }

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
    vector<vector<int> > items = {{0, 1, 2}, {0, 2, 4}, {1, 3, 4}, {2, 4, 5}};
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

TEST(LinearDPTests, MinEditDistanceTEST) { EXPECT_EQ(MinEditDistance("abdc", "aec"), 2); }

TEST(RangeDPTests, MergeStonesTEST) {
    vector<int> stones = {1, 3, 5, 2};
    EXPECT_EQ(MergeStones(stones), 22);
}

TEST(MyTests, NumberDivisionTEST) {
    EXPECT_EQ(IntegerDivision(5), 7);
    EXPECT_EQ(IntegerDivisionII(5), 7);
    EXPECT_EQ(IntegerDivisionIII(5), 7);
}

TEST(MyTest, BlockFillingTEST) {
    EXPECT_EQ(BlockFilling(1, 2), 1);
    EXPECT_EQ(BlockFilling(2, 1), 1);
    EXPECT_EQ(BlockFilling(1, 3), 0);
    EXPECT_EQ(BlockFilling(1, 4), 1);
    EXPECT_EQ(BlockFilling(2, 2), 2);
    EXPECT_EQ(BlockFilling(2, 3), 3);
    EXPECT_EQ(BlockFilling(2, 4), 5);
    EXPECT_EQ(BlockFilling(2, 11), 144);
    EXPECT_EQ(BlockFilling(4, 11), 51205);
}

TEST(MyTest, ShortestHamiltonPathTEST) {
    vector<vector<int> > graph = {{0, 2, 4, 5, 1},
                                  {2, 0, 6, 5, 3},
                                  {4, 6, 0, 8, 3},
                                  {5, 5, 8, 0, 5},
                                  {1, 3, 3, 5, 0}};

    EXPECT_EQ(ShortestHamiltonPath(graph), 18);
}

TEST(MyTest, PartyWithoutLeaderTEST) {
    vector<int> exps = {1, 1, 1, 1, 1, 1, 1};
    vector<vector<int> > rels = {{0, 2}, {1, 2}, {5, 3}, {6, 3}, {3, 4}, {2, 4}};
    EXPECT_EQ(PartyWithoutLeader(exps, rels), 5);
}

TEST(MyTest, SkatingTEST) {
    vector<vector<int> > h = {{1, 2, 3, 4, 5},
                              {16, 17, 18, 19, 6},
                              {15, 24, 25, 20, 7},
                              {14, 23, 22, 21, 8},
                              {13, 12, 11, 10, 9}};
    EXPECT_EQ(Skating(h), 25);
}

TEST(MyTest, DeleteAndEarnTEST) {
    vector<int> nums1 = {3, 4, 2};
    // EXPECT_EQ(deleteAndEarn(nums1), 6);

    vector<int> nums2 = {8, 10, 4, 9, 1, 3, 5, 9, 4, 10};
    EXPECT_EQ(deleteAndEarn(nums2), 37);
}

TEST(MyTest, MaximumScoreTEST) {
    vector<int> nums1 = {1, 2, 3};
    vector<int> multi1 = {3, 2, 1};
    EXPECT_EQ(maximumScore(nums1, multi1), 14);
}

TEST(MyTest, MaxSquareTEST) {
    vector<vector<char> > matrix = {{'1', '0', '1', '0', '0'},
                                    {'1', '0', '1', '1', '1'},
                                    {'1', '1', '1', '1', '1'},
                                    {'1', '0', '0', '1', '0'}};
    EXPECT_EQ(maximalSquare(matrix), 4);
}

TEST(MyTest, JobDifficultyTEST) {
    vector<int> jobDifficulty = {7, 1, 7, 1, 7, 1};
    EXPECT_EQ(minDifficulty(jobDifficulty, 3), 15);
}

TEST(MyTest, CoinChangeTEST) {
    vector<int> coins = {1, 2, 5};
    EXPECT_EQ(coinChange(coins, 11), 3);
}

TEST(MyTest, WordBreakTEST) {
    vector<string> dict = {"leet", "code"};
    // EXPECT_TRUE(wordBreak("leetcode", dict));

    vector<string> dict2 = {"dog", "s", "gs"};
    EXPECT_TRUE(wordBreak("dogs", dict2));

    vector<string> dict3 = {"a",      "aa",      "aaa",      "aaaa",      "aaaaa",
                            "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"};
    EXPECT_TRUE(!wordBreak(
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
        dict3));
}

TEST(MyTest, lengthOfLISTEST) {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    EXPECT_EQ(lengthOfLIS(nums), 4);

    vector<int> nums1 = {4, 10, 4, 3, 8, 9};
    EXPECT_EQ(lengthOfLIS(nums1), 3);
}

TEST(MyTest, maxProfitTEST) {
    vector<int> prices = {1, 2, 3, 0, 2};
    EXPECT_EQ(maxProfit(prices), 3);
}

TEST(MyTest, changeIITEST) {
    vector<int> coins = {1, 2, 5};
    EXPECT_EQ(changeII(5, coins), 4);
    EXPECT_EQ(changeIII(5, coins), 4);
}

TEST(MyTest, numDecodingTEST) {
    EXPECT_EQ(numDecodings("226"), 3);
    EXPECT_EQ(numDecodings("06"), 0);
    EXPECT_EQ(numDecodings("10"), 1);
    EXPECT_EQ(numDecodings("0"), 0);
    EXPECT_EQ(numDecodings("2101"), 1);
}

TEST(MyTest, maxSubArrayTEST) {
    vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    EXPECT_EQ(maxSubArray(v), 6);
    EXPECT_EQ(maxSubArrayII(v), 6);
}

TEST(MyTest, maxCirSubArrayTEST) {
    vector<int> v = {1, 2, 3, 4};
    vector<int> v1 = {4, 1, 2, 3};
    vector<int> v2 = {3, 4, 1, 2};
    vector<int> v3 = {2, 3, 4, 1};
    // inplace shift
    shiftVector(v, 1);
    EXPECT_EQ(v, v1);
    shiftVector(v, 1);
    EXPECT_EQ(v, v2);
    shiftVector(v, 1);
    EXPECT_EQ(v, v3);

    vector<int> vv = {1, -2, 3, -2};
    EXPECT_EQ(maxSubarraySumCircular(vv), 3);
    EXPECT_EQ(maxSubarraySumCircularII(vv), 3);
    vector<int> vv1 = {5, -3, 5};
    EXPECT_EQ(maxSubarraySumCircular(vv1), 10);
    EXPECT_EQ(maxSubarraySumCircularII(vv1), 10);
}

TEST(MyTest, ObstaclesTEST) {
    vector<vector<int>> matrix = {
        {0, 0, 0, 0},
        {0, 1, 0, 0}
    };
    EXPECT_EQ(uniquePathsWithObstacles(matrix), 2);
}

TEST(MyTest, binaryMaxLengthTEST) {
    EXPECT_EQ(binaryMaxLength("110110101", 40), 6);
    EXPECT_EQ(binaryMaxLength("110110101", 0), 0);
    EXPECT_EQ(binaryMaxLength("110110101", 1), 1);
    EXPECT_EQ(binaryMaxLength("110110101", 5), 3);
    EXPECT_EQ(binaryMaxLength("101101", 198), 6);
    EXPECT_EQ(binaryMaxLength("10110010", 2), 2);
    EXPECT_EQ(binaryMaxLength("10010100", 3), 2);
    EXPECT_EQ(binaryMaxLength("1101101010001110010101101", 4000000), 22);
}