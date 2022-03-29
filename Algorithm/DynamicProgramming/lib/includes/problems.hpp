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

#endif