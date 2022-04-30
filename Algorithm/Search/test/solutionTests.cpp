#include <gtest/gtest.h>

#include "search.hpp"
#include "solution.hpp"

// If there is a set of tests that share same context, we can encapsulate it in to a class.
class TestWithContext : public ::testing::Test {
   public:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

// TEST_F(<testsuite name>, testname)
TEST_F(TestWithContext, TestWithContextDemo1) { EXPECT_TRUE(true); }

TEST(SearchTests, NQueensCases) {
    vector<vector<string>> res = {{".Q..", "...Q", "Q...", "..Q."}, {"..Q.", "Q...", "...Q", ".Q.."}};
    EXPECT_EQ(solveNQueens(4), res);
}

TEST(SearchTests, PathInMatrixCases) {
    vector<vector<int>> matrix = {{0}};
    EXPECT_EQ(minPathInMatrix(matrix), 0);

    vector<vector<int>> matrix1 = {{0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 1, 0}};
    EXPECT_EQ(minPathInMatrix(matrix1), 8);
}

TEST(SearchTests, GravityCases) {
    vector<vector<int>> graph = {
        {0, 1},
        {0, 6},
        {0, 3},
        {1, 7},
        {1, 4},
        {3, 2},
        {2, 8},
        {3, 5}
    };
    EXPECT_EQ(centerOfGravity(9, graph), 4);
}

TEST(SearchTests, TopologicalSeqTEST) {
    vector<vector<int>> graph = {
        {0, 1},
        {0, 6},
        {0, 3},
        {1, 7},
        {1, 4},
        {3, 2},
        {2, 8},
        {3, 5}
    };
    vector<int> res = {0, 3, 6, 1, 5, 2, 4, 7, 8};
    EXPECT_EQ(pseudoTopologicalSeq(9, graph), res);
}

TEST(SearchTests, TopoSortTEST) {
    vector<vector<int>> graph = {
        {0, 1},
        {0, 6},
        {0, 3},
        {1, 7},
        {1, 4},
        {3, 2},
        {2, 8},
        {3, 5}
    };
    vector<int> res = {0, 3, 6, 1, 5, 2, 4, 7, 8};
    EXPECT_EQ(topoSort(9, graph), res);

    vector<vector<int>> graph2 = {
        {0, 1},
        {1, 2},
        {0, 2}
    };
    vector<int> res2 = {0, 1, 2};
    EXPECT_EQ(topoSort(3, graph2), res2);
}

TEST(MinPathTests, NaiveDijkstraTEST) {
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 2, 1},
        {0, 2, 4}
    };
    EXPECT_EQ(minPathDijkstra(3, graph), 3);
    EXPECT_EQ(minPathDijkstraHeap(3, graph), 3);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
    };
    EXPECT_EQ(minPathDijkstra(3, graph2), -1);
    EXPECT_EQ(minPathDijkstraHeap(3, graph2), -1);
}

TEST(MinPathTests, SPFATEST) {
    vector<vector<int>> edges = {
        {1, 2, 5},
        {2, 3, -3},
        {1, 3, 4}
    };
    EXPECT_EQ(minPathSPFA(3, edges, 3), 2);

    vector<vector<int>> edges2 = {
        {1, 2, 1},
        {2, 3, 1},
        {1, 3, 3}
    };
    EXPECT_EQ(minPathSPFA(3, edges2, 1), 3);
}