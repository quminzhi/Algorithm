#include "binarysearch.hpp"

#include <cmath>

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
int mySqrt(int x) {
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
int guess(int x) {
    return 0;
}

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
                return bsearchHelper(nums, target, left, mid-1);
            } else {
                return searchRotatedArrHelper(nums, target, mid+1, right);
            } 
        } else {
            if ((target > nums[mid]) && (target <= nums[right])) {
                // right half is ordered
                return bsearchHelper(nums, target, mid+1, right);
            } else {
                return searchRotatedArrHelper(nums, target, left, mid-1);
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
    return searchRotatedArrHelper(nums, target, 0, nums.size()-1);
}

// pseudo code to make program run
bool isBadVersion(int version) {
    return true;
}

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
    if (left == (unsigned int)n + 1) return -1; // out of bound
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
    nums.push_back(-INT_MAX); // add right boundary
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (mid - 1 < 0) {
            // no left neighbor
            if (nums[mid] > nums[mid+1]) {
                return mid;
            } else {
                // search right half
                left = mid + 1;
            }
        } else {
            // has left neighbor
            if ((nums[mid-1] < nums[mid]) && (nums[mid] > nums[mid+1])) {
                return mid;
            } else {
                if (nums[mid-1] >= nums[mid]) {
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
        mid = left + ((right - left) >> 1); // always choose left one
        if (nums[mid] > nums[mid+1]) {
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
        if ((mid > 0) && (nums[mid-1] > nums[mid])) {
            return nums[mid];
        }
        if (((mid + 1) < nums.size()) && (nums[mid] > nums[mid+1])) {
            return nums[mid+1];
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