#ifndef PROBLEMS_HPP
#define PROBLEMS_HPP

#include <vector>
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


#endif