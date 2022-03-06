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

    // notice that the result will converge to 'a+1' which triggers if branch (sqr > x),
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

### Template II

This version of binary search defines search range as `[left, right)` different from template I `[left, right]`.

```c++
int binarySearch(vector<int>& nums, int target){
    if (nums.size() == 0)
        return -1;

    int left = 0, right = nums.size();
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (nums[mid] == target) { 
            return mid; 
        } else {
            if (nums[mid] < target) {
                left = mid + 1; 
            } else {
                right = mid;
            }
        }
  }

  // Post-processing:
  // End Condition: left == right
  // Note: left may be nums.size(), which should be excluded
  if(left != nums.size() && nums[left] == target) return left;
  return -1;
}
```

There are something to note:

- Guarantees Search Space is at least 2 in size at each step.
- Post-processing required. Loop/Recursion ends when you have 1 element left (`left == right`). Need to assess if the remaining element meets the condition.
- Use the element's right neighbor to determine if the condition is met and decide whether to go left or right. (See find peek)

```c++
// say 
left = 4, right = 5
// we got:
// it is found that mid always points to the left when left and right have distance 
// of 1.  
mid = left + ((right - left) >> 1) = 4
// two cases for recursion
// case 1: search in right half, left and right becomes 5 (which is the right)
left = mid + 1 = 5
// case 2: search in left half, left and right becomes 4 (which is the left)
right = mid = 4
```

### First Bad Version

> You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
>
> Suppose you have n versions `[1, 2, ..., n]` and you want to find out the first bad one, which causes all the following ones to be bad.
>
> You are given an API `bool isBadVersion(version)` which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

The one of benefits of template II is it enables us to search until only one element left in the array.

```c++
/**
 * @brief We will solve the same problem with another form of binary search, which
 * will find until there is only one element left. [left, right)
 * 
 * Observations:
 * 1. if current version is good, then all versions before it are good.
 * 2. if current version is bad, then all following versions are bad.
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
```

- When all numbers are non-negative, it is suggested to use `unsigned int` instead of `int` for solving a larger input.

#### Find Peek Element

> A peak element is an element that is strictly greater than its neighbors.
>
> Given an integer array `nums`, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.
>
> You may imagine that `nums[-1] = nums[n] = -∞`.
>
> You must write an algorithm that runs in `O(log n)` time.

```c++
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
        if (nums[mid] > nums[mid+1]) { // right-conditional
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}
```

**Explanation:** why there is no out-of-boundary problem?

- First, if there is only one element left, it will jump out of the while loop.
- Second, if there are two elements, it always chooses the left one (since the divide operation in C++).
- Last, if there are more than two elements, the last one cannot be choose. (The last one can only be chosen in two cases above).

#### Find Minimum in Rotated Sorted Array

> Suppose an array of length n sorted in ascending order is rotated between 1 and `n` times. For example, the array `nums = [0,1,2,4,5,6,7]` might become:
>
> - `[4,5,6,7,0,1,2]` if it was rotated 4 times.
> - `[0,1,2,4,5,6,7]` if it was rotated 7 times.
>
> Given the sorted rotated array nums of unique elements, return the minimum element of this array.
>
> You must write an algorithm that runs in O(log n) time.

The idea is the minimum follows 'injection point', which is defined as `[max(nums), min(nums)]`

```c++
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
```

### Template III

```c++
int binarySearch(vector<int>& nums, int target){
    if (nums.size() == 0)
        return -1;

    int left = 0
    int right = nums.size() - 1;
    while (left + 1 < right) {   // <-- condition
        int mid = left + ((right - left) >> 1);
        if (nums[mid] == target) {
            return mid;
        } else {
            if (nums[mid] < target) {
                left = mid;      // <-- change of boundary
            } else {
                right = mid;
            }
        }
    }

    // Post-processing:
    // End Condition: left + 1 == right
    if (nums[left] == target) return left;
    if (nums[right] == target) return right;
    return -1;
}
```

features:

- Guarantees Search Space is at least 3 in size at each step.
- Post-processing required. Loop/Recursion ends when you have 2 elements left. Need to assess if the remaining elements meet the condition.

#### Search for a Range

> Given an array of integers `nums` sorted in non-decreasing order, find the starting and ending position of a given target value.
>
> If target is not found in the array, return `[-1, -1]`.
>
> You must write an algorithm with `O(log n)` runtime complexity.

To search a range, we can search leftmost index of the target and rightmost index of the target if it exists.

- Leftmost search:

```c++
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
```

Notice when we search the index of leftmost target, the condition is `target <= nums[mid]`, which means we need to search left half even `target == nums[mid]`. In that case, we move right boundary as small as possible `right = mid`. When `target > nums[mid]`, we know that `mid` is not the answer and just `left = mid + 1`. **One side benefit of `left = mid + 1`, it will move left back to the first element (`nums[mid+1]`), and keep the final left point to the first target element.** The loop condition in this case is `left < right`, which means we want left and right boundary will converge to one point.

- Rightmost search:

```c++
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;
    while (left + 1 < right) {
        mid = left + ((right - left) >> 1);
        if (target >= nums[mid]) {
            // right half search
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    if (nums[left] == target) result[1] = left;
    if (nums[right] == target) result[1] = right;
```

As a counterpart, when we search the index of rightmost target, the condition becomes `target >= nums[mid]` and we will move right as carefully as possible `left = mid`. With the same idea before, `right = mid - 1` will give us a desired property, one that keep `nums[left]` or `nums[right]` to be the last target element. Another distinction is loop condition (`left + 1 < right`) which means the loop will continue if there are at least three elements in the search range.

#### Find K Closest Elements

> Given a sorted integer array `arr`, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.
>
> An integer a is closer to x than an integer b if:
>
> - `|a - x| < |b - x|`, or
> - `|a - x| == |b - x|` and `a < b`
>
> x is not necessarily in the `arr`.

- We will use find the k closest elements by binary search plus slide window.

```c++
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
```

- The second solution is called binary range search. We are concentrated on find left boundary of the range of the answer.

We can actually find the bounds of our sliding window much faster - and independent of `k`! First of all, what is the biggest index the left bound could be? If there needs to be `k` elements, then the left bound's upper limit is `arr.length - k`, because if it were any further to the right, you would run out of elements to include in the final answer.

Let's consider two indices at each binary search operation, the usual `mid`, and some index `mid + k`. The relationship between these indices is significant because only one of them could possibly be in a final answer. For example, if `mid = 2`, and `k = 3`, then `arr[2]` and `arr[5]` could not possibly both be in the answer, since that would require taking 4 elements `[arr[2], arr[3], arr[4], arr[5]]`. To be short, our solution range is `[mid, mid + k)`.

This leads us to the question: how do we move our pointers left and right? If the element at `arr[mid]` is closer to `x` than `arr[mid + k]`, then that means **`arr[mid + k]`, as well as every element to the right of it can never be in the answer**. This means we should **move our right pointer** to avoid considering them. The logic is the same vice-versa - if `arr[mid + k]` is closer to `x`, then move the left pointer.

```c++
vector<int> findClosestElementsII(vector<int>& arr, int k, int x) {
    int left = 0;
    int right = arr.size() - k;
    int mid = 0;
    // find left boundary: converge to an point
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (abs(arr[mid] - x) > abs(arr[mid+k] - x)) {
            // move left
            left = mid + 1;
        }  else {
            right = mid;
        }
    }

    vector<int> result;
    for (int i = left; i < left + k; i++) {
        result.push_back(arr[i]);
    }

    return result;
}
```