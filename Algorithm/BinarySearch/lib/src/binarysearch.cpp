#include "binarysearch.hpp"

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

int bsearchHelper(vector<int>& nums, int target, int left, int right) {
    if (left > right) return -1;

    int mid = left + ((right - left) >> 1);
    if (nums[mid] == target) {
        return mid;
    } else {
        if (nums[mid] > target) {
            // search in left half
            return bsearchHelper(nums, target, left, mid - 1);
        } else {
            // search in right half
            return bsearchHelper(nums, target, mid + 1, right);
        }
    }
}

/**
 * @brief implement binary search recursively
 *
 * @param nums
 * @param target
 * @return int
 */
int searchRec(vector<int>& nums, int target) {
    return bsearchHelper(nums, target, 0, nums.size() - 1);
}

/**
 * @brief implement binary search with while loop
 *
 * @param nums
 * @param target
 * @return int
 */
int searchLoop(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (target == nums[mid]) {
            return mid;
        } else {
            if (target < nums[mid]) {
                // left search
                right = mid - 1;
            } else {
                // right search
                left = mid + 1;
            }
        }
    }

    return -1;
}

/**
 * @brief we only care about the integer part and the decimal digit is truncated.
 *
 * 0            sqrt of 0 is 0
 * 1 ^ 2 = 1    sqrt of numbers in [1, 4) is 1
 * 2 ^ 2 = 4    sqrt of numbers in [4, 9) is 2
 * 3 ^ 2 = 9    sqrt of numbers in [9, 16) is 3
 * 4 ^ 2 = 16
 * ...
 * a ^ 2        sqrt of numbers in [a^2, (a+1)^2]
 *
 * search [2, x/2]
 *
 * @param x
 * @return int
 */
int mySqrtI(int x) {
    if (x < 2) return x;
    int left = 2;
    int right = x / 2;
    int mid = 0;
    long sqr = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        sqr = mid * mid;
        if (sqr == x) {
            return mid;
        } else {
            if (sqr < x) {
                // the true sqrt is bigger than mid
                left = mid + 1;
            } else {
                // the true sqrt is smaller than mid
                right = mid - 1;
            }
        }
    }

    // notice that the result will converge to 'a+1' which trigers if branch (sqr > x),
    // then right = mid - 1 which happens to be 'a'
    return right;
}

int mySqrtII(int x) {
    if (x < 2) return x;
    long left = 0;
    long right = x;
    long mid = 0;
    while (left < right) {
        mid = left + ((right - left + 1) >> 1);   // int overflow warning
        if (mid * mid <= x) {                     // int overflow warning
            // the true sqrt is bigger than mid
            left = mid;
        } else {
            // the true sqrt is smaller than mid
            right = mid - 1;
        }
    }

    return left;
}

/**
 * @brief This is a mathematical way to solve sqrt problem:
 *
 *    Observation is: sqrt(x) = e^(1/2 * log(x))
 *
 * @param x
 * @return int
 */
int mySqrtMath(int x) {
    if (x < 2) return x;
    int leftInt = exp(0.5 * log(x));
    int rightInt = leftInt + 1;
    int result = (long)rightInt * rightInt > x ? leftInt : rightInt;

    return result;
}

// pseudo code to make program run
int guess(int x) { return 0; }

/**
 * @brief
 * You call a pre-defined API int guess(int num), which returns three possible results:
 *  - -1: Your guess is higher than the number I picked (i.e. num > pick).
 *  - 1: Your guess is lower than the number I picked (i.e. num < pick).
 *  - 0: your guess is equal to the number I picked (i.e. num == pick).
 * @param n
 * @return int
 */
int guessNumber(int n) {
    int left = 1;
    int right = n;
    int mid;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (guess(mid) == 0) {
            return mid;
        } else {
            if (guess(mid) == 1) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return -1;
}

int searchRotatedArrHelper(vector<int>& nums, int target, int left, int right) {
    if (left > right) return -1;
    int mid = left + ((right - left) >> 1);
    if (nums[mid] == target) {
        return mid;
    } else {
        if (nums[mid] >= nums[left]) {
            if ((target < nums[mid]) && (target >= nums[left])) {
                // left half is ordered
                return bsearchHelper(nums, target, left, mid - 1);
            } else {
                return searchRotatedArrHelper(nums, target, mid + 1, right);
            }
        } else {
            if ((target > nums[mid]) && (target <= nums[right])) {
                // right half is ordered
                return bsearchHelper(nums, target, mid + 1, right);
            } else {
                return searchRotatedArrHelper(nums, target, left, mid - 1);
            }
        }
    }
}

/**
 * @brief binary search in a rotated sorted array.
 *
 * ex>  4 ... 8 9 10 1 2 3
 * case 1: pivot is 8 (nums[pivot] > nums[left]), where the left part is ordered
 *      ^-----^
 * case 2: pivot is 2 (nums[pivot] < nums[left]), where the right part is ordered
 *                     ^-^
 *
 * @param nums
 * @param target
 * @return int
 */
int searchRotatedArr(vector<int>& nums, int target) {
    return searchRotatedArrHelper(nums, target, 0, nums.size() - 1);
}

// pseudo code to make program run
bool isBadVersion(int version) { return true; }

/**
 * @brief search the first bad version
 * search bad version first and start from it finding the first one.
 *
 * O(log(N) + N)
 *
 * @param n
 * @return int
 */
int firstBadVersionI(int n) {
    int left = 0;
    int right = n;
    int mid = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (isBadVersion(mid)) {
            break;
        } else {
            left = mid + 1;
        }
    }

    // if not found
    if (left > right) return -1;

    // find the first bad version
    while (isBadVersion(mid)) {
        mid--;
    }
    return mid + 1;
}

/**
 * @brief We will solve the same problem with another form of binary search, which
 * will find until there is only one element left. [left, right)
 *
 * Observations:
 * 1. if current version is good, then all versions before it are good.
 * 2. if current version is bad, then all following versions are bad.
 *
 * O(log(N))
 *
 * @param n
 * @return int
 */
int firstBadVersionII(int n) {
    if (n <= 0) return -1;
    unsigned int left = 0;
    unsigned int right = (unsigned int)n + 1;
    unsigned int mid = 0;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (isBadVersion(mid)) {
            // search left half, since observation 2
            right = mid;
        } else {
            // search right half, observation 1
            left = mid + 1;
        }
    }

    // check if left is out of bound is MUST
    if (left == (unsigned int)n + 1) return -1;   // out of bound
    if (isBadVersion(left)) {
        return left;
    } else {
        return left + 1;
    }
}

/**
 * @brief find the index of any peak in an array
 *
 * Observations:
 * 1. if nums[i-1] < nums[i] < nums[i+1], peak should be in the right of i
 * 2. if nums[i-1] > nums[i] > nums[i+1], peak should be in the left of i
 *
 * @param nums
 * @return int
 */
int findPeakElement(vector<int>& nums) {
    int left = 0;
    int right = nums.size();
    int mid = 0;
    nums.push_back(-INT_MAX);   // add right boundary
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (mid - 1 < 0) {
            // no left neighbor
            if (nums[mid] > nums[mid + 1]) {
                return mid;
            } else {
                // search right half
                left = mid + 1;
            }
        } else {
            // has left neighbor
            if ((nums[mid - 1] < nums[mid]) && (nums[mid] > nums[mid + 1])) {
                return mid;
            } else {
                if (nums[mid - 1] >= nums[mid]) {
                    // search left half first
                    right = mid;
                } else {
                    // search left half (nums[mid+1] >= nums[mid])
                    left = mid + 1;
                }
            }
        }
    }

    return mid;
}

/**
 * @brief we solve the problem with template 2. Note that we need to locate a point,
 * That's what template 2 is good at. We just need to find divide conditions.
 *
 * - if right > current, search right half
 * - otherwise, search left half
 *
 * @param nums
 * @return int
 */
int findPeakElementII(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;
    // while there are more than one elements in the array
    while (left < right) {
        mid = left + ((right - left) >> 1);   // always choose left one
        if (nums[mid] > nums[mid + 1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

/**
 * @brief find minimum number in a rotated array.
 *
 * ex> 4 5 6 1 3
 *
 * Notice: the rotated array consists of two ordered sequence and a infection point.
 * On the infection point (6 -> 1), the order is reversed and the minimum is after
 * infection point.
 *
 * How to find infection point?
 *
 * - if nums[mid] > nums[left], infection point is on the right half.
 * - if otherwise, infection point is on the left half.
 * - if nums[mid-1] > nums[mid] or nums[mid] > nums[mid+1], it is found.
 *
 * @param nums
 * @return int
 */
int findMin(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    // if last number is greater than first number, no rotation
    if (nums[right] > nums[left]) return nums[left];

    int mid = 0;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if ((mid > 0) && (nums[mid - 1] > nums[mid])) {
            return nums[mid];
        }
        if (((mid + 1) < nums.size()) && (nums[mid] > nums[mid + 1])) {
            return nums[mid + 1];
        }
        if (nums[mid] > nums[left]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    // no infection point found, meaning rotate step is 0
    return nums[0];
}

/**
 * @brief with duplicates in nums
 *
 * @param nums
 * @return int
 */
int findMinII(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    // if last number is greater than first number, no rotation
    if (nums[right] > nums[left]) return nums[left];

    int mid = 0;
    while (left < right) {
        // check if nums in range is in order
        if (nums[right] > nums[left]) return nums[left];

        mid = left + ((right - left) >> 1);
        if (nums[mid] == nums[left]) {
            left += 1;
        } else {
            if (nums[mid] < nums[left]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
    }

    return nums[left];
}

/**
 * @brief return the range of target in nums
 * Find leftmost target and rightmost target with template II
 * @param nums
 * @param target
 * @return vector<int>
 */
vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> result = {-1, -1};
    if (nums.size() == 0) return result;
    // find the leftmost
    // if target <= nums[mid], left half search. (target == left, left half search)
    // otherwise, right half search
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (target <= nums[mid]) {
            // left half search
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    if (nums[left] == target) result[0] = left;

    // find the rightmost
    // if target <= nums[mid], left half search. (target == left, left half search)
    // otherwise, right half search
    left = 0;
    right = nums.size() - 1;
    while (left < right) {
        mid = left + ((right - left + 1) >> 1);
        if (target >= nums[mid]) {
            // right half search
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    if (nums[left] == target) result[1] = left;

    return result;
}

/**
 * @brief return k closet numbers in the arr to x, nums is sorted in ascending order.
 * The idea is 1. finding x or the element closest to x first and 2. searching
 * bidirectionally starting from that point.
 * @param arr
 * @param k
 * @param x
 * @return vector<int>
 */
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    // base case: k == arr.size()
    if (arr.size() == k) {
        vector<int> ret(arr.begin(), arr.end());
        sort(ret.begin(), ret.end());
        return ret;
    }

    // find the first one or first closest one
    // the closet will be in either arr[left] or arr[left-1]
    int left = 0;
    int right = arr.size() - 1;
    int mid = 0;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (x <= arr[mid]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    // search bidirectionally
    // notice that: we cannot decide left or left - 1 is the closest
    vector<int> result;
    int l = left - 1;
    int r = left;
    int min = 0;
    while (result.size() < k) {
        // no nums available
        if ((l < 0) && (r >= arr.size())) {
            break;
        }
        // only right
        if (l < 0) {
            result.push_back(arr[r]);
            r++;
            continue;
        }
        // only left
        if (r >= arr.size()) {
            result.push_back(arr[l]);
            l--;
            continue;
        }
        // both exist
        if (abs(arr[l] - x) > abs(arr[r] - x)) {
            // right win
            result.push_back(arr[r]);
            r++;
        } else {
            result.push_back(arr[l]);
            l--;
        }
    }

    sort(result.begin(), result.end());

    return result;
}

/**
 * @brief range search, define range to be [mid, mid + k)
 *
 * @param arr
 * @param k
 * @param x
 * @return vector<int>
 */
vector<int> findClosestElementsII(vector<int>& arr, int k, int x) {
    int left = 0;
    int right = arr.size() - k;
    int mid = 0;
    // find left boundary: converge to an point
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (abs(arr[mid] - x) > abs(arr[mid + k] - x)) {
            // move left
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    vector<int> result;
    for (int i = left; i < left + k; i++) {
        result.push_back(arr[i]);
    }

    return result;
}

/**
 * @brief return sqrt of x, err < 1e-6
 *
 * @param x
 * @return double
 */
double findSqrt(int x) {
    double left = 0;
    double right = x;
    while (right - left > 1e-8) {
        double mid = left + ((right - left) / 2);
        if (mid * mid >= x) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return left;
}

/**
 * @brief find the closest number in BST to target number. Binary search and track closest
 * value.
 *
 * The nature of binary search tree (BST) is range search.
 *
 * @param root
 * @param target
 * @return int
 */
int closestValue(TreeNode* root, double target) {
    if (root == nullptr) return -1;

    int closest = INT_MAX;
    double diff = INT_MAX;   // = abs(target - closest), diff CANNOT be int but double
    TreeNode* p = root;
    while (p != nullptr) {
        if (p->val == target) {
            return p->val;
        } else {
            // update closest
            double p_diff = abs(target - p->val);
            if (p_diff < diff) {
                closest = p->val;
                diff = p_diff;
            }

            if (p->val > target) {
                p = p->left;
            } else {
                p = p->right;
            }
        }
    }
    return closest;
}

// pseudo code
int ArrayReader::get(int index) const { return -1; }

/**
 * @brief Notice 1 <= secret.length <= 10^4. Just binary search on that range.
 * searchI implement normal binary search.
 * @param reader
 * @param target
 * @return int
 */
int searchI(const ArrayReader& reader, int target) {
    int left = 0;
    int right = 1e4;
    int mid = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (reader.get(mid) == target) {
            return mid;
        } else {
            if (reader.get(mid) < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

/**
 * @brief search leftmost method
 *
 * @param reader
 * @param target
 * @return int
 */
int searchII(const ArrayReader& reader, int target) {
    int left = 0;
    int right = 1e4;
    int mid = 0;
    while (left < right) {
        mid = left + ((right - left) >> 1);

        if (reader.get(mid) >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    if (reader.get(left) == target) return left;
    return -1;
}

double powHelper(double x, long n) {
    if (n == 0) return 1;
    double half = powHelper(x, n / 2);
    if ((n & 1) == 1) {
        return half * half * x;
    } else {
        return half * half;
    }
}

/**
 * @brief
 *
 * @param x
 * @param n
 * @return double: return x^n (say: x to the nth power)
 */
double myPow(double x, long n) {
    if (n < 0) {
        x = 1 / x;
        n = -n;
    }
    return powHelper(x, n);
}

/**
 * @brief True if num is a perfect square
 * The idea is same to find sqrt of num.
 */
bool isPerfectSquare(int num) {
    long left = 1;
    int right = num;
    long mid = 1;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (mid * mid >= num) {   // overflow warning
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if (left * left == num) return true;   // overflow warning
    return false;
}

/**
 * @brief return the next smallest number greater than target.
 * 1. find rightmost letter that equals target
 * 2. if letters[left] <= target, return rightmost letter + 1
 * @param letters
 * @param target
 * @return char
 */
char nextGreatestLetter(vector<char>& letters, char target) {
    int left = 0;
    int right = letters.size() - 1;
    int mid = 0;
    while (left < right) {
        mid = left + ((right - left + 1) >> 1);
        if (letters[mid] <= target) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    // letters[left] has three possible outcome:
    // 1. letters[left] > target, when target is smaller than the smallest element of
    // letters.
    // 2. letters[left] == target, left must be the rightmost target.
    // 3. letters[left] == biggest one smaller than target when target is bigger than all
    // the elements of letters.
    if (letters[left] > target) {
        return letters[left];
    } else {
        return letters[(left + 1) % letters.size()];
    }
}

/**
 * @brief return intersection of two arrays, elements of returned array should be unique.
 * 1. Sort the array with bigger size (N).
 * 2. Loop on the smaller one (M) and binary search on sorted array.
 *
 * Time complexity: O(NlogN) + O(M*logN)
 * @param nums1
 * @param nums2
 * @return vector<int>
 */
vector<int> intersectionI(vector<int>& nums1, vector<int>& nums2) {
    vector<int> result;
    if (nums1.size() < nums2.size()) {
        sort(nums2.begin(), nums2.end());
        unordered_set<int> unique(nums1.begin(), nums1.end());
        for (int num : unique) {
            if (bsearchHelper(nums2, num, 0, nums2.size() - 1) != -1) {
                result.push_back(num);
            }
        }
    } else {
        sort(nums1.begin(), nums1.end());
        unordered_set<int> unique(nums2.begin(), nums2.end());
        for (int num : unique) {
            if (bsearchHelper(nums1, num, 0, nums1.size() - 1) != -1) {
                result.push_back(num);
            }
        }
    }

    return result;
}

/**
 * @brief return intersection of two arrays, all intersection elements including
 * duplicates
 * 1. create a statistic map for each array
 * 2. compare maps.
 *
 * @param nums1
 * @param nums2
 * @return vector<int>
 */
vector<int> intersectionII(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> m1;
    unordered_map<int, int> m2;
    for (int num : nums1) {
        m1[num]++;
    }
    for (int num : nums2) {
        m2[num]++;
    }

    vector<int> result;
    for (auto p : m1) {
        if (m2.find(p.first) != m2.end()) {
            for (int i = 0; i < min(m1[p.first], m2[p.first]); i++) {
                result.push_back(p.first);
            }
        }
    }

    return result;
}

/**
 * @brief the property of sorted array. Two ends are extremes.
 *
 * @param numbers
 * @param target
 * @return vector<int>
 */
vector<int> twoSum(vector<int>& numbers, int target) {
    int min = 0, max = numbers.size() - 1;
    while (min < max) {
        if (numbers[min] + numbers[max] == target) {
            return {min + 1, max + 1};
        } else {
            if (numbers[min] + numbers[max] > target) {
                max--;
            } else {
                min++;
            }
        }
    }

    return {-1, -1};
}

/**
 * @brief find duplicate numbers[1...n+1], only one duplicate number repeats m times.
 *
 * count(n) returns the total number that's less than 'n'
 * ex> 1 3 2 3 4 5  sort--> 1 2 3 3 4 5
 * count(1 2 3 3 4 5) -> (1:1, 2:2, 3:4, 4:5, 5:6)
 *
 * count(1 2 3 3 4 5) -> (1:1, 3:3, 4:4, 5:5)
 *
 * So the duplicate number breaks the rule of count(n) <= n, and on the left of duplicate
 * number are numbers follows the rule, and the others are not. Binary search comes into
 * play.
 *
 * @param nums
 * @return int
 */
int findDuplicate(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    while (left < right) {
        mid = left + ((right - left + 1) >> 1);
        if (nums[mid] >= mid - 0 + 1) {
            // n >= count(n)
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    return nums[left];
}

/**
 * @brief find kth number in two sorted array.
 * How to decompose the problem of finding kth in two sorted array?
 *
 * ex>  nums1: 1, 4, 5, 7, 10 (find k/2)
 *      nums2: 2, 2, 5, 6 (find k/2)
 *
 * How finding k/2th in two arrays helps us?
 * There are some cases to discuss:
 * 1. nums1.size() >= k/2 and nums2.size() >= k/2. We can compare nums1[k/2] and
 * nums2[k/2], and eliminate k/2 elements from smaller array based on the idea from horse
 * race problem.
 * 2. nums1.size() < k/2, eliminate k/2 elements from nums2.size() and vice versa.
 * 3. nums1.size() < k/2, and nums2.size() < k/2, CANNOT exists, since k is (sz1 + sz2) /
 * 2
 *
 * @param nums1
 * @param start1
 * @param nums2
 * @param start2
 * @param k: 1-indexed
 * @return double
 */
double findKthHelper(vector<int>& nums1, int start1, vector<int>& nums2, int start2,
                     int k) {
    if (start1 >= nums1.size()) {
        // no element in nums1, k is one-indexed
        return nums2[start2 + k - 1];
    }
    if (start2 >= nums2.size()) {
        // no element in nums2
        return nums1[start1 + k - 1];
    }
    if (k == 1) {
        return min(nums1[start1], nums2[start2]);
    }

    int mid1 = start1 + k / 2 - 1;
    int mid2 = start2 + k / 2 - 1;
    // incorporate case 1 and case 2:
    int val1 = mid1 >= nums1.size() ? INT_MAX : nums1[mid1];
    int val2 = mid2 >= nums2.size() ? INT_MAX : nums2[mid2];
    if (val1 <= val2) {
        return findKthHelper(nums1, mid1 + 1, nums2, start2, k - k / 2);
    } else {
        return findKthHelper(nums1, start1, nums2, mid2 + 1, k - k / 2);
    }
}

/**
 * @brief the more general question is finding kth value in two sorted array.
 *
 * @param nums1
 * @param nums2
 * @return double
 */
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int len = nums1.size() + nums2.size();
    if (len & 1) {
        // odd length
        return findKthHelper(nums1, 0, nums2, 0, len / 2 + 1);
    } else {
        return 0.5 * (findKthHelper(nums1, 0, nums2, 0, len / 2) +
                      findKthHelper(nums1, 0, nums2, 0, len / 2 + 1));
    }
}

/**
 * @brief return count of pairs with distance less or equal to m
 *
 * ex> 1 2 5 7 12 20  (m=10)
 *     ^        ^  ^
 *    (j)       j  i
 *
 * so there are i - j pairs ending with i that have distance less than m
 *
 * @param nums: must be ordered
 * @param m
 * @return int
 */
int pairDistanceLessOrEqual(vector<int> nums, int m) {
    int count = 0;
    for (int i = nums.size() - 1; i > 0; i--) {
        int j = 0;
        while ((j < nums.size()) && (nums[i] - nums[j] > m)) {
            j++;
        }
        count += i - j;
    }

    return count;
}

/**
 * @brief return kth smallest pair in nums.
 * There are two classic ways to find kth element in a sequence:
 * 1. priority queue or heap.
 * 2. binary search.
 *
 * With binary search, we have to find a function reflecting a counting property of given
 * array. In this problem, our search range is (0, nums[max] - nums[min]). Assuming m is
 * in that range, pairLessOrEqual(m) returns the count of pairs with distance less or
 * equal to m.
 * @param nums
 * @param k
 * @return int
 */
int smallestDistancePair(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int left = 0, right = nums[nums.size() - 1] - nums[0];
    int mid = 0;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (pairDistanceLessOrEqual(nums, mid) >= k) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int mySum(vector<int>::iterator begin, vector<int>::iterator end) {
    int sum = 0;
    for (auto it = begin; it != end; it++) {
        sum += *it;
    }
    return sum;
}

int myMax(vector<int>::iterator begin, vector<int>::iterator end) {
    int max = -INT_MAX;
    for (auto it = begin; it != end; it++) {
        if (*it > max) {
            max = *it;
        }
    }
    return max;
}

/**
 * @brief return the maximum of val of m continuous subarrays. The maximum should be as
 * small as possible among different subdivisions.
 *
 * The first solution is to solve the problem recursively.
 *
 * ex> splitArray({7, 2, 5, 10, 8}, 3)
 *   = min(
 *         max({7}, splitArray({2, 5, 10, 8}, 2)),
 *         max({7, 2}, splitArray({5, 10, 8}, 2)),
 *         max({7, 2, 5}, splitArray({10, 8}, 2))   <== a base case
 *     )
 *
 * 1. base case: size of array == split number or m == 1
 * 2. recursion formula:
 *    splitArray(arr, m) = min(possible split, m-1);
 *
 * @param nums
 * @param m
 * @return int
 */
int splitArrayHelper(vector<int>& nums, vector<int>& sum, int begin, int m) {
    if (nums.size() - begin == m) {
        return myMax(nums.begin() + begin, nums.end());
    }

    if (m == 1) {
        return sum[nums.size() - 1] - sum[begin - 1];
        // return mySum(nums.begin() + begin, nums.end());
    }

    int min = INT_MAX;
    int division = 0;
    // offset to array starting from 'begin'
    for (int offset = 0; offset <= nums.size() - begin - m; offset++) {
        division = max(sum[begin + offset] - sum[begin - 1],
                       splitArrayHelper(nums, sum, begin + offset + 1, m - 1));
        // why +1, end is not included in mySum()
        // division = max(mySum(nums.begin() + begin, nums.begin() + begin + offset + 1),
        //    splitArrayHelper(nums, begin + offset + 1, m - 1));
        if (division < min) {
            min = division;
        }
    }

    return min;
}

int splitArray(vector<int>& nums, int m) {
    // optimize: cache sum to void repeated calculation
    // sum[i] means sum of nums[0...i]
    vector<int> sum(nums.size(), 0);
    sum[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum[i - 1] + nums[i];
    }

    return splitArrayHelper(nums, sum, 0, m);
}

/**
 * @brief In the section, we will solve spliting problem by dynamic programming.
 *
 * Define f as:
 *   f(start, m) = minimum val of all spliting divisions.
 *
 * Deduction:
 *   f(start, m) = min(max(f(start + i, m - 1), sum(start...i))), where i is possible
 * offset. where i = [1, last].
 *
 * ex > solve[0][2] =? max(solve[1][1], sum of [0, 1))
 *                  =? max(solve[2][1], sum of [0, 2))
 *                  =? ...
 *                  =? max(solve[last][1], sum of [0, last))
 *                  = MIN of all result above
 *
 * Base: return the sum of current array if 'm == 1' or return the max of current array if
 * 'm == size of current array'.
 *
 * HelperFunction (Op): prefix_sum(int i), the sum of numbers before i in the array, we
 * can cache the result in advance to avoid repeated calculation. With the helper of
 * prefix_sum, we are able to calculate the sum of any range conveniently.
 *
 * ex> sum of 2 to 4 included ==> prefix_sum(5) - prefix_sum(2)
 *     sum of [2, 5) ==> prefix_sum(5) - prefix_sum(2)
 *     sum of all ==> prefix_sum(nums.size())
 *
 * @param nums
 * @param m
 * @return int
 */
int splitArrayII(vector<int>& nums, int m) {
    vector<int> prefix_sum(nums.size() + 1, 0);
    // prefix_sum[0] = 0;
    for (int i = 1; i < prefix_sum.size(); i++) {
        prefix_sum[i] = prefix_sum[i - 1] + nums[i - 1];
    }

    vector<vector<int> > solve(nums.size(), vector<int>(nums.size(), 0));
    // init base case:
    for (int start = 0; start < nums.size(); start++) {
        solve[start][1] = prefix_sum[nums.size()] - prefix_sum[start];
    }

    // deduction
    for (int grp = 2; grp <= nums.size(); grp++) {   // choice of m, # of subgroups
        // notice the diagonal boundary has the property of grp + start == nums.size()
        for (int start = 0; start <= nums.size() - grp; start++) {
            int min = INT_MAX;
            // why 'nums.size() - start - grp + 1'
            // notice the diagonal boundary has the property of grp + start == nums.size()
            // so far, grp = grp - 1, start = start, so we get the relationship.
            for (int offset = 1; offset <= nums.size() - start - grp + 1; offset++) {
                int rangeSum = prefix_sum[start + offset] - prefix_sum[start];
                int cur = max(solve[start + offset][grp - 1], rangeSum);
                if (cur < min) min = cur;
            }
            solve[start][grp] = min;
        }
    }

    return solve[0][m];
}