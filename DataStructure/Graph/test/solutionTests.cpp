#include <gtest/gtest.h>

#include "problems.hpp"
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
    vector<vector<int>> graph = {{0, 1}, {0, 6}, {0, 3}, {1, 7}, {1, 4}, {3, 2}, {2, 8}, {3, 5}};
    EXPECT_EQ(centerOfGravity(9, graph), 4);
}

TEST(SearchTests, TopologicalSeqTEST) {
    vector<vector<int>> graph = {{0, 1}, {0, 6}, {0, 3}, {1, 7}, {1, 4}, {3, 2}, {2, 8}, {3, 5}};
    vector<int> res = {0, 3, 6, 1, 5, 2, 4, 7, 8};
    EXPECT_EQ(pseudoTopologicalSeq(9, graph), res);
}

TEST(SearchTests, TopoSortTEST) {
    vector<vector<int>> graph = {{0, 1}, {0, 6}, {0, 3}, {1, 7}, {1, 4}, {3, 2}, {2, 8}, {3, 5}};
    vector<int> res = {0, 3, 6, 1, 5, 2, 4, 7, 8};
    EXPECT_EQ(topoSort(9, graph), res);

    vector<vector<int>> graph2 = {{0, 1}, {1, 2}, {0, 2}};
    vector<int> res2 = {0, 1, 2};
    EXPECT_EQ(topoSort(3, graph2), res2);
}

TEST(MinPathTests, DijkstraTEST) {
    vector<vector<int>> graph = {{1, 2, 2}, {2, 3, 1}, {1, 3, 4}};
    EXPECT_EQ(minPathDijkstra(3, graph), 3);
    EXPECT_EQ(minPathDijkstraHeap(3, graph), 3);

    vector<vector<int>> graph2 = {
        {1, 2, 2},
    };
    EXPECT_EQ(minPathDijkstra(2, graph2), 2);
    EXPECT_EQ(minPathDijkstraHeap(2, graph2), 2);
}

TEST(MinPathTests, SPFATEST) {
    vector<vector<int>> edges = {{1, 2, 5}, {2, 3, -3}, {1, 3, 4}};
    EXPECT_EQ(minPathSPFA(3, edges), 2);

    vector<vector<int>> edges1 = {{1, 2, -1}, {2, 3, 4}, {3, 1, -4}};
    EXPECT_TRUE(checkNegativeLoopWithSPFA(3, edges1));

    vector<vector<int>> edges2 = {{1, 2, 1}, {2, 3, 1}, {1, 3, 3}};
    EXPECT_EQ(minPathSPFAWithControl(3, edges2, 1), 3);
}

TEST(MinPathTests, FloydTEST) {
    vector<vector<int>> edges = {{1, 2, 1}, {2, 3, 2}, {1, 3, 1}};
    EXPECT_EQ(minPathFloyd(3, edges), 1);
}

TEST(SpinningGraphTests, PrimTEST) {
    vector<vector<int>> edges = {{1, 2, 1}, {1, 3, 2}, {1, 4, 3}, {2, 3, 2}, {3, 4, 4}};
    // EXPECT_EQ(minSpinningGraphPrim(4, edges), 6);

    vector<vector<int>> edges1 = {{1, 2, 8},  {2, 2, 7},  {2, 1, 1}, {3, 4, 3}, {4, 4, -10},
                                  {1, 3, -9}, {5, 2, -4}, {3, 1, 0}, {1, 4, 8}, {4, 4, 7}};
    EXPECT_EQ(minSpinningGraphPrim(5, edges1), -9);
}

TEST(BipartiteGraphTests, HungarianTEST) {
    vector<vector<int>> edges = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
    EXPECT_EQ(maxBipartiteGraph(2, 2, edges), 2);
}

TEST(ProblemsTests, NumberOfProvinceTEST) {
    vector<vector<int>> g = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    EXPECT_EQ(findCircleNum(g), 2);
    EXPECT_EQ(findCircleNumII(g), 2);

    vector<vector<int>> g2 = {{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 1, 1}};
    EXPECT_EQ(findCircleNum(g2), 1);
    EXPECT_EQ(findCircleNumII(g), 2);
}

TEST(ProblemsTests, ValidTreeTEST) {
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}};
    EXPECT_TRUE(!validTree(5, edges));
}

TEST(ProblemsTests, earlistAcqTEST) {
    vector<vector<int>> logs = {{0, 2, 0}, {1, 0, 1}, {3, 0, 3}, {4, 1, 2}, {7, 3, 1}};
    EXPECT_EQ(earliestAcq(logs, 4), 3);
}

TEST(ProblemTests, smallStringTEST) {
    vector<vector<int>> pairs = {{0, 3}, {1, 2}, {0, 2}};
    EXPECT_EQ(smallestStringWithSwaps("dcab", pairs), "abcd");
}

TEST(ProblemTests, calcEquationTEST) {
    vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
    vector<double> values = {2.0, 3.0};
    vector<vector<string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    vector<double> res = {6.0, 0.5, -1.0, 1.0, -1.0};
    // EXPECT_EQ(calcEquation(equations, values, queries), res);

    vector<vector<string>> equations1 = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
    vector<double> values1 = {1.5, 2.5, 5.0};
    vector<vector<string>> queries1 = {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
    vector<double> res1 = {3.75, 0.4, 5.0, 0.2};
    EXPECT_EQ(calcEquation(equations1, values1, queries1), res1);
}

TEST(ProblemTests, WaterDistributionTEST) {
    vector<vector<int>> pipes = {{1, 2, 1}, {2, 3, 1}};
    vector<int> wells = {1, 2, 2};
    EXPECT_EQ(minCostToSupplyWater(3, wells, pipes), 3);
    EXPECT_EQ(minCostToSupplyWaterII(3, wells, pipes), 3);
}

TEST(DFSTests, findPathTEST) {
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};

    EXPECT_TRUE(validPath(3, edges, 0, 2));
}

TEST(DFSTests, findAllPathTEST) {
    vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};
    vector<vector<int>> res = {{0, 1, 3}, {0, 2, 3}};
    EXPECT_EQ(allPathsSourceTarget(graph), res);
}

TEST(DFSTests, leadsToDestinationTEST) {
    vector<vector<int>> edges = {{0, 1}, {0, 2}};
    EXPECT_FALSE(leadsToDestination(3, edges, 0, 2));

    vector<vector<int>> edges1 = {{0, 1}, {1, 1}};
    EXPECT_FALSE(leadsToDestination(2, edges1, 0, 1));

    vector<vector<int>> edges2 = {{0, 1}, {0, 3}, {1, 2}, {2, 1}};
    EXPECT_FALSE(leadsToDestination(4, edges2, 0, 3));

    vector<vector<int>> edges3 = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    EXPECT_TRUE(leadsToDestination(4, edges3, 0, 3));

    vector<vector<int>> edges4 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    EXPECT_FALSE(leadsToDestination(5, edges4, 0, 3));
}

TEST(BFSTests, shortestBinaryMatrixTEST) {
    vector<vector<int>> grid = {{0, 1}, {1, 0}};
    EXPECT_EQ(shortestPathBinaryMatrix(grid), 2);

    vector<vector<int>> grid1 = {{1, 0, 0}, {1, 1, 0}, {1, 1, 0}};
    EXPECT_EQ(shortestPathBinaryMatrix(grid1), -1);
}

TEST(BFSTests, rottingOrangeTEST) {
    vector<vector<int>> grid{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    EXPECT_EQ(orangesRotting(grid), 4);
}

TEST(MinPathTests, networkDelayTEST) {
    vector<vector<int>> times{{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    EXPECT_EQ(networkDelayTime(times, 4, 2), 2);
}

TEST(MinPathTests, cheapestFlightsTEST) {
    vector<vector<int>> flights{{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    EXPECT_EQ(findCheapestPrice(3, flights, 0, 2, 1), 200);
    EXPECT_EQ(findCheapestPrice(3, flights, 0, 2, 0), 500);

    vector<vector<int>> flights1 = {{0, 1, 1}, {0, 2, 5}, {1, 2, 1}, {2, 3, 1}};
    EXPECT_EQ(findCheapestPrice(4, flights1, 0, 3, 1), 6);

    vector<vector<int>> flights2 = {{0, 1, 1}, {0, 2, 5}, {1, 2, 1}, {2, 3, 2}, {2, 4, 100}, {3, 4, 2}};
    EXPECT_EQ(findCheapestPrice(5, flights2, 0, 4, 2), 9);

    // Hinge Bug: Bellman can solve it.
    vector<vector<int>> flights3 = {{0, 3, 3}, {3, 4, 3}, {4, 1, 3}, {0, 5, 1}, {5, 1, 100}, {0, 6, 2},  {6, 1, 100},
                                    {0, 7, 1}, {7, 8, 1}, {8, 9, 1}, {9, 1, 1}, {1, 10, 1},  {10, 2, 1}, {1, 2, 100}};
    EXPECT_EQ(findCheapestPrice(11, flights3, 0, 2, 4), 11);
}

TEST(MinPathTests, minEffortTEST) {
    vector<vector<int>> heights = {{1, 2, 1, 1, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 1, 1, 2, 1}};
    EXPECT_EQ(minimumEffortPath(heights), 0);
}

TEST(MinPathTests, maxScoreTEST) {
    vector<vector<int>> grid = {{3, 4, 6, 3, 4}, {0, 2, 1, 1, 7}, {8, 8, 3, 2, 7},
                                {3, 2, 4, 9, 8}, {4, 1, 2, 0, 0}, {4, 6, 5, 4, 3}};
    EXPECT_EQ(maximumMinimumPath(grid), 3);
}

TEST(MinPathTests, swimInWaterTEST) {
    vector<vector<int>> grid = {{0, 2}, {1, 3}};
    EXPECT_EQ(swimInWater(grid), 3);

    vector<vector<int>> grid1 = {
        {0, 1, 2, 3, 4}, {24, 23, 22, 21, 5}, {12, 13, 14, 15, 16}, {11, 17, 18, 19, 20}, {10, 9, 8, 7, 6}};
    EXPECT_EQ(swimInWater(grid1), 16);
}

TEST(MinPathTests, minLinesTEST) {
    vector<vector<int>> points = {{0, 1}, {2, 3}, {4, 5}, {4, 3}};
    EXPECT_EQ(minimumLines(points), 2);

    vector<vector<int>> points1 = {{-3, -5}, {0, 1}, {1, -1}, {2, 5}, {-1, -3}, {-2, -4}};
    EXPECT_EQ(minimumLines(points1), 2);

    vector<vector<int>> points2 = {{5, -3}, {-5, 3}, {3, -5}, {-3, 5}};
    EXPECT_EQ(minimumLines(points2), 2);

    vector<vector<int>> points3 = {{0, 0}, {2, -3}, {-2, 3}, {5, -3}, {-5, 3}, {3, -5}, {-3, 5}};
    EXPECT_EQ(minimumLines(points3), 3);

    // vector<vector<int>> points4 = {{-2, 3}, {4, -5}, {3, -2}, {5, 3}};
    // EXPECT_EQ(minimumLines(points4), 2);
}

TEST(TopologyTests, minHeightTEST) {
    vector<vector<int>> edges = {
        {1, 0}, {1, 2}, {1, 3}
    };
    vector<int> res = {1};
    // EXPECT_EQ(findMinHeightTrees(4, edges), res);

    vector<vector<int>> edges1 = {
        {3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}
    };
    vector<int> res1 = {3, 4};
    EXPECT_EQ(findMinHeightTrees(6, edges1), res1);

    vector<vector<int>> edges2 = {
        {0, 1}, {0, 2}
    };
    vector<int> res2 = {0};
    EXPECT_EQ(findMinHeightTrees(3, edges2), res2);
}

TEST(TopologyTests, parallelCourseTEST) {
    vector<vector<int>> rel = {
        {1, 3}, {2, 3}
    };
    EXPECT_EQ(minimumSemesters(3, rel), 2);
}