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

TEST(MyTests, MySqrtTEST) {
    EXPECT_EQ(mySqrtII(2), 1);
    EXPECT_EQ(mySqrtII(3), 1);
    EXPECT_EQ(mySqrtII(8), 2);
    EXPECT_EQ(mySqrtII(10), 3);
    EXPECT_EQ(mySqrtII(101), 10);
    EXPECT_EQ(mySqrtII(2147395599), 46339);
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
    EXPECT_EQ(findClosestElementsII(arr2, 3, 5), expected2);
}

TEST(MyTest, findSqrtTEST) {
    EXPECT_DOUBLE_EQ(findSqrt(1), 0.9999999925494194);
    EXPECT_DOUBLE_EQ(findSqrt(2), 1.4142135605216026);
}

TEST(MyTest, FindSmallestLargerTEST) {
    vector<char> v1 = {'c', 'f', 'j'};
    EXPECT_EQ(nextGreatestLetter(v1, 'a'), 'c');
    EXPECT_EQ(nextGreatestLetter(v1, 'z'), 'c');

    vector<char> v2 = {'a', 'b'};
    EXPECT_EQ(nextGreatestLetter(v2, 'z'), 'a');
}

TEST(MyTest, FindDuplicatesTEST) {
    vector<int> nums = {7, 9, 7, 4, 2, 8, 7, 7, 1, 5};
    EXPECT_EQ(findDuplicate(nums), 7);
}

TEST(MyTest, FindMedianSortedArraysTEST) {
    vector<int> nums1 = {0, 0, 0, 0, 0};
    vector<int> nums2 = {-1, 0, 0, 0, 0, 0, 1};
    EXPECT_DOUBLE_EQ(findMedianSortedArrays(nums1, nums2), 0.0);
}

TEST(MyTest, FindKthPairDistanceTEST) {
    vector<int> nums = {1, 2, 4, 5, 37, 99};
    EXPECT_EQ(pairDistanceLessOrEqual(nums, 2), 3);

    vector<int> nums1 = {62, 100, 4};
    EXPECT_EQ(smallestDistancePair(nums1, 2), 58);
}

TEST(MyTest, HelperFunctionTEST) {
    vector<int> nums = {1, 3, 5, 6};
    EXPECT_EQ(mySum(nums.begin(), nums.end()), 15);
    EXPECT_EQ(myMax(nums.begin(), nums.end()), 6);
}

TEST(MyTest, SplitArrayTEST) {
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    EXPECT_EQ(splitArray(nums, 5), 4);

    vector<int> nums2 = {7, 2, 5, 10, 8};
    EXPECT_EQ(splitArray(nums2, 2), 18);
}