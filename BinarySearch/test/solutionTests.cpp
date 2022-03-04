#include <gtest/gtest.h>
#include "binarysearch.hpp"
#include "solution.hpp"

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

TEST(MyTests, BinarySearchTEST) {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    // EXPECT_EQ(searchRotatedArr(nums, 6), 2);
    // EXPECT_EQ(searchRotatedArr(nums, 0), 4);

    vector<int> nums2 = {3, 1};
    EXPECT_EQ(searchRotatedArr(nums2, 1), 1);
}

TEST(MyTest, PeekFinderTEST) {
    vector<int> mountains = {-2147483647, -2147483648};
    EXPECT_EQ(findPeakElementII(mountains), 0);
    vector<int> mountains2 = {-2147483648, -2147483647};
    EXPECT_EQ(findPeakElementII(mountains2), 1);
}

TEST(MyTest, findMinTEST) {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    EXPECT_EQ(findMin(nums), 0);

    vector<int> nums2 = {11, 13, 15, 17};
    EXPECT_EQ(findMin(nums2), 11);

    vector<int> nums3 = {1, 2};
    EXPECT_EQ(findMin(nums3), 1);
}

TEST(MyTest, findKClosestTEST) {
    vector<int> arr = {1, 2, 3, 4, 5};
    vector<int> expected = {1, 2, 3, 4};
    // EXPECT_EQ(findClosestElements(arr, 4, -1), expected);

    vector<int> arr2 = {0, 0, 1, 2, 3, 3, 4, 7, 7, 8};
    vector<int> expected2 = {3, 3, 4};
    EXPECT_EQ(findClosestElements(arr2, 3, 5), expected2);
}