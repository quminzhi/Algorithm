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
> You may imagine that `nums[-1] = nums[n] = -???`.
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

And there is another way to solve the problem.

```c++
/**
 * ex> 11, 13, 14, 1, 2, 5, 7
 *     left       min
 *     mid     mid      mid
 * There are three cases:
 * 1. nums[mid] == nums[left], left = mid + 1
 * 2. nums[mid] > nums[left], left = mid + 1
 * 3. nums[mid] < nums[left], nums[mid] may be the answer and so right = mid.
 */
int findMin(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    int mid = 0;
    while (left < right) {
        if (nums[right] > nums[left]) return nums[left];
        mid = left + ((right - left) >> 1);
        if (nums[mid] < nums[left]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return nums[left];
}
```

#### Find Minimum in Rotated Sorted Array II

> When there are duplicates in the `nums`, what's the solution to find the minimum?

The solution to duplicates is exactly same as the idea of the second solution above. But we need to be careful to the condition when `nums[mid] == nums[left]`, in which case the target must be on the left of `nums[left]`.

```c++
// 10, 12, 1, 10, 10, 10
// left   min     mid
// when nums[mid] == nums[left], we need to find the last number of duplicates, which
// happens to be nums[left]. So we can move mid to left and proceed as we did before.
if (nums[mid] == nums[left]) {
    left += 1 // ==== mid = left; left = mid + 1;
}
```

```c++
/**
 * Following algorithm only works in rotated array. So we need to check if the nums is
 * in order. If so, just return the first element.
 * 
 * ex> 11, 13, 14, 1, 2, 5, 7
 *     left       min
 *     mid     mid      mid
 * 
 * There are three cases:
 * 1. nums[mid] == nums[left], left = left + 1
 * 2. nums[mid] > nums[left], left = mid + 1
 * 3. nums[mid] < nums[left], nums[mid] may be the answer and so right = mid.
 */
int findMin(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    int mid = 0;
    while (left < right) {
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
    // find the rightmost
    // if target <= nums[mid], left half search. (target == left, left half search)
    // otherwise, right half search
    left = 0;
    right = nums.size() - 1;
    while (left < right) {
        mid = left + ((right - left + 1) >> 1); // +1 is important for left == right-1
        if (target >= nums[mid]) {
            // right half search
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    if (nums[left] == target) result[1] = left;
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

#### Closest Binary Search Tree

> Given the root of a binary search tree and a target value, return the value in the BST that is closest to the target.

The essence of binary search is a binary search tree. A process of binary search can be represented with a binary search tree.

```c++
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
    double diff = INT_MAX; // = abs(target - closest), diff CANNOT be int but double
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
```

#### Search in a Sorted Array of Unknown Size

> You have a sorted array of unique elements and an unknown size. You do not have an access to the array but you can use the ArrayReader interface to access it. You can call `ArrayReader.get(i)` that:
>
> - returns the value at the ith index (0-indexed) of the secret array (i.e., `secret[i]`), or
> - returns 2^31 - 1 if the i is out of the boundary of the array.
>
> You are also given an integer target.
>
> Return the index `k` of the hidden array where `secret[k] == target` or return `-1` otherwise.

Notice `1 <= secret.length <= 10^4`

```c++
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
```

#### Valid Perfect Square

> Given a positive integer `num`, write a function which returns `True` if `num` is a perfect square else `False`.
>
> Follow up: Do not use any built-in library function such as sqrt.

Same idea with `MySqrt(int x)`.

```c++
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
```

#### Find Smallest Letter Greater than Target

> Given a characters array `letters` that is sorted in **non-decreasing** order and a character `target`, return the smallest character in the array that is larger than `target`.
>
> Note that the letters wrap around (circular).
>
> - For example, if `target == 'z'` and `letters == ['a', 'b']`, the answer is `'a'`.

```c++
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
```

#### Intersection of Two Arrays

> Given two integer arrays `nums1` and `nums2`, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.

The idea is straightforward:

- Sort the array with bigger size (N).
- Loop on the smaller one (M) and binary search on sorted array. Since the result should be unique, we can solve it by feed smaller array in an `unordered_set`.

```c++
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
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    vector<int> result;
    if (nums1.size() < nums2.size()) {
        sort(nums2.begin(), nums2.end());
        unordered_set<int> unique(nums1.begin(), nums1.end());
        for (int num : unique) {
            if (bsearchHelper(nums2, num, 0, nums2.size()-1) != -1) {
                result.push_back(num);
            }
        }
    } else {
        sort(nums1.begin(), nums1.end());
        unordered_set<int> unique(nums2.begin(), nums2.end());
        for (int num : unique) {
            if (bsearchHelper(nums1, num, 0, nums1.size()-1) != -1) {
                result.push_back(num);
            }
        }
    }

    return result;
}
```

#### Intersection of Two Arrays II

> Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.

We will sort two arrays first and iterate them like `merge join` to get common elements. Also we can save space by utilizing one of two arrays.

```c++
vector<int> intersectionII(vector<int>& nums1, vector<int>& nums2) {
    sort(begin(nums1), end(nums1));
    sort(begin(nums2), end(nums2));
    int i = 0, j = 0, k = 0;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] < nums2[j]) {
            i++;
        } else if (nums1[i] > nums2[j]) {
            j++;
        } else {
            nums1[k++] = nums1[i++];
            j++;
        }
    }
    return vector<int>(begin(nums1), begin(nums1) + k);
}
```

#### Two Sum

> Given a 1-indexed array of integers `numbers` that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be `numbers[index1]` and `numbers[index2]` where `1 <= index1 < index2 <= numbers.length`.
>
> Return the indices of the two numbers, index1 and index2, added by one as an integer array `[index1, index2]` of length 2.
>
> The tests are generated such that there is exactly one solution. You may not use the same element twice.

- Two pointers: given the array is sorted, set two pointers, `min_ptr` and `max_ptr`, to search the result. The idea is based on the property of sorted array that two end values are extremes:
    - if `numbers[min_ptr] + numbers[max_ptr] > target`, `numbers[max_ptr]` cannot be the result, since when it adds minimum of the array it is still greater than target.
    - As a counterpart, if `numbers[min_ptr] + numbers[max_ptr] < target` `numbers[min_ptr]` cannot be chosen as the result.

```c++
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
            return {min+1, max+1};
        }
        else {
            if (numbers[min] + numbers[max] > target) {
                max--;
            } else {
                min++;
            }
        }
    }

    return {-1, -1};
}
```

#### Find the Duplicate Number

> Given an array of integers nums containing `n + 1` integers where each integer is in the range `[1, n]` inclusive.
>
> There is only one repeated number in nums, return this repeated number.
>
> You must solve the problem without modifying the array nums and uses only constant extra space.

The observation is the last duplicate number must break the rule of `nums[i] <= countBeforeNumber(nums[i])`.

```c++
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
 * number are numbers follows the rule, and the others are not. Binary search comes into play.
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
```

#### Median of Two Sorted Arrays

> Given two sorted arrays `nums1` and `nums2` of size m and n respectively, return the median of the two sorted arrays.
>
> The overall run time complexity should be `O(log (m+n))`.

The basic idea comes from horse race problem and one observation: **`k / 2` elements can be safely eliminated each time**.

To be more general, for `m` sorted arrays and finding kth element, `k / m` elements can be safely eliminated each time.

```c++
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
```

#### Find K-th Smallest Pair Distance

> The distance of a pair of integers a and b is defined as the absolute difference between a and b.
>
> Given an integer array `nums` and an integer `k`, return the kth smallest distance among all the pairs `nums[i]` and `nums[j]` where `0 <= i < j < nums.length`.

This problem can be generalized as a template for finding kth element with binary search without having direct access to the array. We only know two things:

- the range of ordered array
- how many numbers less than given value returned by `prefixCount()`.

```c++
// k is 1-indexed
int findKthElement(int max, int min, int k) {
    int left = min, right = max;
    int mid = 0;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        if (prefixCount(mid) >= k-1) {
            // the count of numbers less than mid is greater than k-1
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}
```

#### Split Array Largest Sum

> Given an array nums which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays.
>
> Write an algorithm to minimize the largest sum among these m subarrays.

See the comment below.

```c++
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
```