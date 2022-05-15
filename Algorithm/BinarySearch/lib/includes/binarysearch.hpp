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
int findMinII(vector<int>& nums);   // with duplicates

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
double myPow(double x, long n);   // allow negative power
bool isPerfectSquare(int num);
char nextGreatestLetter(vector<char>& letters, char target);

vector<int> intersectionI(vector<int>& nums1, vector<int>& nums2);
vector<int> intersectionII(vector<int>& nums1, vector<int>& nums2);
vector<int> twoSum(vector<int>& numbers, int target);

int findDuplicate(vector<int>& nums);
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);
int smallestDistancePair(vector<int>& nums, int k);
int pairDistanceLessOrEqual(vector<int> nums, int m);
int splitArray(vector<int>& nums, int m);
int splitArrayHelper(vector<int>& nums, vector<int>& sum, int begin, int m);
int mySum(vector<int>::iterator begin, vector<int>::iterator end);
int myMax(vector<int>::iterator begin, vector<int>::iterator end);
int splitArrayII(vector<int>& nums, int m);

class CountIntervals {
   public:
    vector<int> lv;
    vector<int> rv;
    int sz;

    CountIntervals() : sz(0){};

    void add(int left, int right) {
        if (lv.empty()) {
            lv.push_back(left);
            rv.push_back(right);
            sz += right - left + 1;
            return;
        }
        // find the idx1 in rv the first greater or equal than left
        int idx1 = greaterThan(left);
        // find the idx2 in lv the first less or equal than right
        int idx2 = lessThan(right);

        // no overlap
        if (left > rv[idx1]) {
            // largest interval
            lv.push_back(left);
            rv.push_back(right);
            sz += right - left + 1;
            return;
        }
        if (right < lv[idx2]) {
            // smallest interval
            lv.insert(lv.begin(), left);
            rv.insert(rv.begin(), right);
            sz += right - left + 1;
            return;
        }

        if (idx1 > idx2) {
            // insert between idx1 and idx2
            lv.insert(lv.begin() + idx1, left);
            rv.insert(rv.begin() + idx1, right);
            sz += right - left + 1;
        }

        // overlap with only one interval
        if (idx1 == idx2) {
            int newLeft = min(left, lv[idx1]);
            int newRight = max(right, rv[idx1]);
            sz += (newRight - newLeft + 1) - (rv[idx1] - lv[idx1] + 1);
            lv[idx1] = newLeft;
            rv[idx1] = newRight;
        }
        // overlap with multiple intervals
        if (idx1 < idx2) {
            // merge intervals and update count
            int newLeft = min(left, lv[idx1]);
            int newRight = min(right, rv[idx2]);
            // delete intervals from idx1 to idx2 and update 'sz'
            for (int i = idx1; i <= idx2; i++) {
                sz = sz - (rv[i] - lv[i] + 1);
            }
            lv.erase(lv.begin() + idx1, lv.begin() + idx2 + 1);
            rv.erase(rv.begin() + idx1, rv.begin() + idx2 + 1);

            // insert new intervals
            sz += newRight - newLeft + 1;
            lv.insert(lv.begin() + idx1, newLeft);
            rv.insert(rv.begin() + idx1, newRight);
        }
    }

    int count() { return sz; }

   private:
    // find the first greater or equal to left in vector 'rv'
    int greaterThan(int left) {
        int l = 0;
        int r = rv.size() - 1;
        while (l < r) {
            int mid = l + ((r - l) >> 1);
            if (rv[mid] < left) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }

    // find the first less or equal to right in vector 'lv'
    int lessThan(int right) {
        int l = 0;
        int r = lv.size() - 1;
        while (l < r) {
            int mid = l + ((r - l + 1) >> 1);
            if (lv[mid] > right) {
                r = mid - 1;
            } else {
                l = mid;   // add 1 to mid to prevent dead loop
            }
        }
        return l;
    }
};

#endif
