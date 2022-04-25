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
    EXPECT_EQ(topologicalSeq(9, graph), res);
}