#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <vector>
using namespace std;

int ZeroOneKnapsack(vector<int> weights, vector<int> values, int total);
int ZeroOneKnapsackII(vector<int> weights, vector<int> values, int total);
vector<int> ZeroOneKnapsackWithTracking(vector<int> weights, vector<int> values,
                                        int total);
int TotalNumberOfZeroOneKnapsack(vector<int> weights, vector<int> values,
                                        int total);

int CompleteKnapsack(vector<int> weights, vector<int> values, int total);
int CompleteKnapsackII(vector<int> weights, vector<int> values, int total);
int CompleteKnapsackIII(vector<int> weights, vector<int> values, int total);
int LimitedKnapsack(vector<int> weights, vector<int> values, vector<int> limits,
                    int total);
int LimitedKnapsackII(vector<int> weights, vector<int> values, vector<int> limits,
                      int total);
int LimitedKnapsackIII(vector<int> weights, vector<int> values, vector<int> limits,
                       int total);
int GroupKnapsack(vector<vector<int> > items, int total);
int GroupKnapsackII(vector<vector<int> > items, int total);

class Item {
   public:
    Item(int _kind, int _weight, int _value)
        : kind(_kind), weight(_weight), value(_value), limit(INT_MAX){};
    Item(int _kind, int _weight, int _value, int _limit)
        : kind(_kind), weight(_weight), value(_value), limit(_limit){};
    int kind;
    int weight;
    int value;
    int limit;
};
int MixedKnapsack(vector<Item> items, int total);

#endif
