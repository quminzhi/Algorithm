# Binary Search

## Introduction

What is Binary Search?

Binary Search is one of the most fundamental and useful algorithms in Computer Science. It describes the process of searching for a specific value in an ordered collection.

Terminology used in Binary Search:

- Target - the value that you are searching for
- Index - the current location that you are searching
- Left, Right - the indicies from which we use to maintain our search Space
- Mid - the index that we use to apply a condition to determine if we should search left or right

Basic problem:

> Given an array of integers `nums` which is sorted in ascending order, and an integer target, write a function to search target in `nums`. If target exists, then return its index. Otherwise, return -1.
>
> You must write an algorithm with O(log n) runtime complexity.

- Loop solution:

```c++
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
```

- Recursion solution:

```c++
int bsearchHelper(vector<int>& nums, int target, int left, int right) {
    if (left > right) return -1;

    int mid = left + ((right - left ) >> 1);
    if (nums[mid] == target) {
        return mid;
    } else {
        if (nums[mid] > target) {
            // search in left half
            return bsearchHelper(nums, target, left, mid-1);
        } else {
            // search in right half
            return bsearchHelper(nums, target, mid+1, right);
        }
    }
}

int searchRec(vector<int>& nums, int target) {
    return bsearchHelper(nums, target, 0, nums.size()-1);
}
```

## Templates

### Template I

Template I is the basic form as shown in the last section. Following are some problems associated with it.

#### Sqrt

> Given a non-negative integer `x`, compute and return the square root of `x`.
>
> Since the return type is an integer, the decimal digits are truncated, and only the integer part of the result is returned.
>
> Note: You are not allowed to use any built-in exponent function or operator, such as `pow(x, 0.5)` or `x ** 0.5`.

```c++
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
```

#### Guess Number Higher or Lower

> We are playing the Guess Game. The game is as follows:
>
> I pick a number from 1 to n. You have to guess which number I picked.
>
> Every time you guess wrong, I will tell you whether the number I picked is higher or lower than your guess.
>
> - -1: Your guess is higher than the number I picked (i.e. num > pick).
> - 1: Your guess is lower than the number I picked (i.e. num < pick).
> - 0: 0: your guess is equal to the number I picked (i.e. num == pick).
>
> Return the number that I picked.

```c++
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
```

#### Search in Rotated Sorted Array

> There is an integer array nums sorted in ascending order (with distinct values).
>
> Prior to being passed to your function, nums is possibly rotated at an unknown pivot index `k`.
>
> Given the array `nums` after the possible rotation and an integer `target`, return the index of `target` if it is in nums, or `-1` if it is not in nums.

This is a classic "half-ordered" problem. The key is to check which part is ordered given `left`, `pivot`, and `right`.

```c++
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
```