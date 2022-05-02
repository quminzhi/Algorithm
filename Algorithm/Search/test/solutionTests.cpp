#include <gtest/gtest.h>

#include "search.hpp"
#include "solution.hpp"
#include "problems.hpp"

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

TEST(MinPathTests, DijkstraTEST) {
    vector<vector<int>> graph = {
        {1, 2, 2},
        {2, 3, 1},
        {1, 3, 4}
    };
    EXPECT_EQ(minPathDijkstra(3, graph), 3);
    EXPECT_EQ(minPathDijkstraHeap(3, graph), 3);

    vector<vector<int>> graph2 = {
        {1, 2, 2},
    };
    EXPECT_EQ(minPathDijkstra(2, graph2), 2);
    EXPECT_EQ(minPathDijkstraHeap(2, graph2), 2);
}

TEST(MinPathTests, SPFATEST) {
    vector<vector<int>> edges = {
        {1, 2, 5},
        {2, 3, -3},
        {1, 3, 4}
    };
    EXPECT_EQ(minPathSPFA(3, edges), 2);

    vector<vector<int>> edges1= {
        {1, 2, -1},
        {2, 3, 4},
        {3, 1, -4}
    };
    EXPECT_TRUE(checkNegativeLoopWithSPFA(3, edges1));

    vector<vector<int>> edges2 = {
        {1, 2, 1},
        {2, 3, 1},
        {1, 3, 3}
    };
    EXPECT_EQ(minPathSPFAWithControl(3, edges2, 1), 3);
}

TEST(MinPathTests, FloydTEST) {
    vector<vector<int>> edges = {
        {1, 2, 1},
        {2, 3, 2},
        {1, 3, 1}
    };
    EXPECT_EQ(minPathFloyd(3, edges), 1);
}

TEST(SpinningGraphTests, PrimTEST) {
    vector<vector<int>> edges = {
        {1, 2, 1},
        {1, 3, 2},
        {1, 4, 3},
        {2, 3, 2},
        {3, 4, 4}
    };
    // EXPECT_EQ(minSpinningGraphPrim(4, edges), 6);

    vector<vector<int>> edges1 = {
        {1, 2, 8},
        {2, 2, 7},
        {2, 1, 1},
        {3, 4, 3},
        {4, 4, -10},
        {1, 3, -9},
        {5, 2, -4},
        {3, 1, 0},
        {1, 4, 8},
        {4, 4, 7}
    };
    EXPECT_EQ(minSpinningGraphPrim(5, edges1), -9);
}

TEST(BipartiteGraphTests, HungarianTEST) {
    vector<vector<int>> edges = {
        {1, 1},
        {1, 2},
        {2, 1},
        {2, 2}
    };
    EXPECT_EQ(maxBipartiteGraph(2, 2, edges), 2);
}

TEST(ProblemsTests, NumberOfProvinceTEST) {
    vector<vector<int>> g = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    EXPECT_EQ(findCircleNum(g), 2);
    EXPECT_EQ(findCircleNumII(g), 2);

    vector<vector<int>> g2 = {
        {1, 0, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 1, 1}
    };
    EXPECT_EQ(findCircleNum(g2), 1);
    EXPECT_EQ(findCircleNumII(g), 2);
}