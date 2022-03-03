#ifndef BINARYSEARCH_HPP
#define BINARYSEARCH_HPP

#include <vector>
using namespace std;

int bsearchHelper(vector<int>& nums, int target, int left, int right);
int searchRec(vector<int>& nums, int target);
int searchLoop(vector<int>& nums, int target);

int mySqrt(int x);
int guessNumber(int n);
int guess(int x);
int searchRotatedArr(vector<int>& nums, int target);

#endif
