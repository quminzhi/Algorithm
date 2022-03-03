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

int firstBadVersionI(int n);
int firstBadVersionII(int n);
bool isBadVersion(int version);
int findPeakElementI(vector<int>& nums);
int findPeakElementII(vector<int>& nums);
int findMin(vector<int>& nums);

vector<int> searchRange(vector<int>& nums, int target);

#endif
