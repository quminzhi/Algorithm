#ifndef PROBLEMS_HPP
#define PROBLEMS_HPP

#include <vector>
#include <algorithm>
using namespace std;

int rob(vector<int>& nums);
int minCostClimbingStairs(vector<int>& cost);
int tribonacci(int n);
int deleteAndEarn(vector<int>& nums);
int maximumScore(vector<int>& nums, vector<int>& multipliers);
int maximalSquare(vector<vector<char> >& matrix);
int minDifficulty(vector<int>& jobDifficulty, int d);
int coinChange(vector<int>& coins, int amount);
bool wordBreakWithMemo(string s, vector<string>& wordDict);
bool wordBreak(string s, vector<string>& wordDict);
int lengthOfLIS(vector<int>& nums);
int maxProfit(int k, vector<int>& prices);
int maxProfit(vector<int>& prices);

class TreeNode2 {
   public:
    int val;
    TreeNode2* left;
    TreeNode2* right;
};
int rob(TreeNode2* root);

int minCostClimbingStairsII(vector<int>& cost);
int minCostClimbingStairsIII(vector<int>& cost);
int minCostClimbingStairsIV(vector<int>& cost);

int numWays(int n, int k);
int changeII(int amount, vector<int>& coins);
int changeIII(int amount, vector<int>& coins);
int numDecodings(string s);
int maxSubArray(vector<int>& nums);
int maxSubArrayII(vector<int>& nums);


int maxProfitI(vector<int>& prices);
int maxProfitII(vector<int>& prices);
void shiftVector(vector<int>& nums, int shift);
int maxSubarraySumCircular(vector<int>& nums);
int maxSubarraySumCircularII(vector<int>& nums);
int uniquePaths(int m, int n);
int uniquePathsCompressed(int m, int n);
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);

int lenOfBin(int x);
int binaryMaxLength(string s, int x);
int minPathSum(vector<vector<int>>& grid);
int minPathSumII(vector<vector<int>>& grid);
int minFallingPathSum(vector<vector<int>>& matrix);

int maxProfit(vector<int>& prices, int fee);
int minPaintCost(vector<vector<int>>& costs);
int minCostII(vector<vector<int>>& costs);
int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target);

int countVowelPermutation(int n);
int findLength(vector<int>& nums1, vector<int>& nums2);
int findLengthII(vector<int>& nums1, vector<int>& nums2);

#endif