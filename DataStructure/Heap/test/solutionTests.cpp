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

TEST(MyTests, HeapSortTEST) {
    vector<int> v = {99, 82, 17, 36, 1, 26, 71, 89, 17, 22, 2, 5, 7};
    vector<int> sorted = {1, 2, 5, 7, 17, 17, 22, 26, 36, 71, 82, 89, 99};
    EXPECT_EQ(heapSort(v), sorted);
}

TEST(MyTests, TopKFrequentTEST) {
    vector<int> v = {1, 1, 1, 2, 2, 3};
    vector<int> res = {1, 2};
    EXPECT_EQ(topKFrequent(v, 2), res);
}

TEST(MyTests, KthLargestTEST) {
    vector<int> v = {4, 5, 8, 2};
    KthLargest ks(3, v);
    EXPECT_EQ(ks.add(3), 4);
    EXPECT_EQ(ks.add(5), 5);
    EXPECT_EQ(ks.add(10), 5);
    EXPECT_EQ(ks.add(9), 8);
    EXPECT_EQ(ks.add(4), 8);

    vector<int> v2 = {};
    KthLargest ks2(1, v2);
    EXPECT_EQ(ks2.add(-3), -3);
    EXPECT_EQ(ks2.add(-2), -2);
    EXPECT_EQ(ks2.add(-4), -2);
    EXPECT_EQ(ks2.add(0), 0);
    EXPECT_EQ(ks2.add(4), 4);
}

TEST(MyTests, MeetingRooms) {
    vector< vector<int> > intervals = {
        {0, 30}, {15, 20}, {5, 10}
    };
    EXPECT_EQ(minMeetingRooms(intervals), 2);
}

TEST(MyTests, kClosestPoints) {
    vector< vector<int> > points = {
        {3, 3}, {5, -1}, {-2, 4}
    };
    vector< vector<int> > expected = {
        {-2, 4}, {3, 3}
    };
    EXPECT_EQ(kClosest(points, 2), expected);
}

TEST(MyTests, furthestBuildings) {
    vector<int> heights = {4, 12, 2, 7, 3, 18, 20, 3, 19};
    EXPECT_EQ(furthestBuilding(heights, 10, 2), 7);
}

TEST(MyTests, MedianFinder) {
    MedianFinder finder;
    finder.addNum(1);
    EXPECT_EQ(finder.findMedian(), 1);
    finder.addNum(2);
    EXPECT_EQ(finder.findMedian(), 1.5);
    finder.addNum(3);
    EXPECT_EQ(finder.findMedian(), 2);
    finder.addNum(4);
    EXPECT_EQ(finder.findMedian(), 2.5);
    finder.addNum(5);
    EXPECT_EQ(finder.findMedian(), 3);
}