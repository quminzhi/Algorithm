#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <vector>
using namespace std;

int ZeroOneKnapsack(vector<int> weights, vector<int> values, int total);
int ZeroOneKnapsackII(vector<int> weights, vector<int> values, int total);
int CompleteKnapsack(vector<int> weights, vector<int> values, int total);
int CompleteKnapsackII(vector<int> weights, vector<int> values, int total);
int CompleteKnapsackIII(vector<int> weights, vector<int> values, int total);
int LimitedKnapsack(vector<int> weights, vector<int> values, vector<int> limits,
                    int total);

#endif
