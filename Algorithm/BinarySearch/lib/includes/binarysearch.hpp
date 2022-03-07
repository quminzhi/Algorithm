#ifndef BINARYSEARCH_HPP
#define BINARYSEARCH_HPP

#include <vector>
using namespace std;

class TreeNode {
   public:
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}

    int val;
    TreeNode* left;
    TreeNode* right;
};

int bsearchHelper(vector<int>& nums, int target, int left, int right);
int searchRec(vector<int>& nums, int target);
int searchLoop(vector<int>& nums, int target);

int mySqrtI(int x);
int mySqrtII(int x);
double findSqrt(int x);
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
vector<int> findClosestElementsI(vector<int>& arr, int k, int x);
vector<int> findClosestElementsII(vector<int>& arr, int k, int x);

int closestValue(TreeNode* root, double target);
class ArrayReader {
   public:
    int get(int index) const;
};
int searchI(const ArrayReader& reader, int target);
int searchII(const ArrayReader& reader, int target);
double myPow(double x, long n); // allow negative power
bool isPerfectSquare(int num);
char nextGreatestLetter(vector<char>& letters, char target);


#endif
