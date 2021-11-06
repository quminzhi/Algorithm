# Algorithm II

## Binary Search

### Search the First and the Last Element

> Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
>
> If target is not found in the array, return [-1, -1].
>
> You must write an algorithm with O(log n) runtime complexity.

The key to the problem is how to refine or design naive binary search. How to design a binary search that can search the index of the first target

The trick is trying to detect neighboring element. For the case of finding the first target.

```c++
// ...binary search code...
    if (nums[mid] == target) {
        // try to detect
        if ((mid > 0) && (nums[mid-1] == target)) {
            // not the first! continue to search in the left half
            r = mid - 1;
        }
        else {
            break;
        }
    }
// ...rest code...
```

Similarly, we can design a binary search finding the last target.

```c++
vector<int> searchRange_sol2(vector<int> nums, int target) {
    if (nums.size() == 0) return {-1, -1};
    vector<int> result;
    // TODO: binary search for the first target
    int l = 0;
    int r = nums.size() - 1;
    int mid = 0;
    while (l <= r) {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target) {
            if ((mid > 0) && (nums[mid-1] == target)) {
                r = mid - 1;
            }
            else {
                // mid is the first
                break;
            }
        }
        else if (nums[mid] > target) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    if (l > r) return {-1, -1};
    result.push_back(mid);

    // TODO: binary search for the last target
    l = 0; r = nums.size() - 1;
    while (l <= r) {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target) {
            if ((mid < nums.size() - 1) && (nums[mid+1] == target)) {
                l = mid + 1;
            }
            else {
                break;
            }
        }
        else if (nums[mid] < target) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    if (l > r) return {-1, -1};
    result.push_back(mid);

    return result;
}
```

Tricks:

- Change the behavior of binary search.

### Search in Rotated Array

> There is an integer array nums sorted in ascending order (with distinct values).
>
> Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
>
> Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
>
> You must write an algorithm with O(log n) runtime complexity.

This problem gives us a deep understanding of binary search, also called one half known binary search. If the range of one half can be determined, then we can apply binary search to that problem.

```c++
/**
 * The key point is determine range!
 *
 * ex>  4,  5,  6,  7,  0,  1,  2
 *      ^           ^   ^       ^
 *      |--sorted---|   |sorted-|
 *    begin                    end
 *
 * Case 1: if nums[mid] >= nums[begin] which is 4, then
 *      4,  5,  6,  7,  0,  1,  2
 *          ^
 *         mid
 *      |---|-------------------|
 *      sorted     unsorted
 * if (nums[mid] > target > nums[begin]), then we will search in sorted half,
 * great! do as normal. otherwise, we will search in unsorted half, move begin
 * to mid + 1
 *
 * Case 2: if nums[mid] < nums[begin], then (notice mid == begin cann't be
 * categorized in this case)
 *      4,  5,  6,  7,  0,  1,  2
 *                          ^
 *                         mid
 *      |-----unsorted------|---|
 *                          sorted
 * if (nums[mid] < target < nums[end]), search sorted part, otherwise, search
 * unsorted part.
 */
```

```c++
int search_sol2(vector<int>& nums, int target) {
    if (nums.size() == 0) return -1;
    int begin = 0;
    int end = nums.size() - 1;
    int mid = 0;
    while (begin <= end) {
        mid = begin + ((end - begin) >> 1);
        if (nums[mid] == target) {
            return mid;
        }
        else {
            if (nums[mid] >= nums[begin]) {
                if ((nums[mid] > target) && (target >= nums[begin])) {
                    end = mid - 1;
                }
                else {
                    begin = mid + 1;
                }
            }
            else {
                if ((nums[mid] < target) && (target <= nums[end])) {
                    begin = mid + 1;
                }
                else {
                    end = mid - 1;
                }
            }
        }
    }

    return -1;
}
```

BTW, another way to solve the problem is transfer rotated array back to a completely sorted array, and apply binary search to it.

```c++
int search_sol1(vector<int>& nums, int target) {
    if (nums.size() == 0) return -1;
    vector<int> vec;
    // TODO: find sorted array
    vec.insert(vec.end(), nums.begin(), nums.end());
    vec.insert(vec.end(), nums.begin(), nums.end());
    // return the index of min value
    int begin = min_element(nums.begin(), nums.end()) - nums.begin();
    int end = begin + nums.size() - 1;

    // TODO: binary search on vec[begin, end];
    int left = begin;
    int right = end;
    int mid = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (vec[mid] == target) {
            // find index in rotated array
            return mid % nums.size();
        }
        else if (vec[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}
```

Tricks:

- The condition of using binary search: range of one half is known.
- `std::min_element(v.begin(), v.end())`: return iter for minimum element.
- `vector.insert(vector.end(), other.begin(), other.end())`: insert other to the end of `vector`.

### Search Matrix

> Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
>
> - Integers in each row are sorted from left to right.
> - The first integer of each row is greater than the last integer of the previous row.

This ia a variant of binary search. We are solve the problem by two cooperative binary search.

```c++
/**
 * ex> {1, 3, 5, 7},     <--- top
 *     {10, 11, 16, 20},
 *     {23, 30, 34, 60}  <--- bottom
 *      ^           ^
 *     left        right
 */
```

Search row first and then search column.

```c++
bool searchMatrix_sol2(vector< vector<int> >& matrix, int target) {
    int top = 0;
    int bottom = matrix.size() - 1;
    int left = 0;
    int last = matrix[0].size() - 1;
    int right = last;
    int midRow = 0;
    int midCol = 0;
    while (top <= bottom) {
        midRow = top + ((bottom - top) >> 1);
        if (matrix[midRow][0] > target) {
            bottom = midRow - 1;
        }
        else if (matrix[midRow][last] < target) {
            top = midRow + 1;
        }
        else {
            // TODO: binary search in midRow
            while (left <= right) {
                midCol = left + ((right - left) >> 1);
                if (matrix[midRow][midCol] == target) {
                    return true;
                }
                else if (matrix[midRow][midCol] < target) {
                    left = midCol + 1;
                }
                else {
                    right = midCol - 1;
                }
            }
            return false;
        }
    }
    return false;
}
```

### Find Min in Rotated Array

> Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:
> 
> - [4,5,6,7,0,1,2] if it was rotated 4 times.
> - [0,1,2,4,5,6,7] if it was rotated 7 times.
>
> Notice that rotating an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.
>
> Given the sorted rotated array nums of unique elements, return the minimum element of this array.
>
> You must write an algorithm that runs in O(log n) time.

Agian O(log n) implies our old friend binary search. There are two scenarioes:

- Array is rotated by 0 step.
- Array is rotated by n steps, where n > 0.

```c++
/**
 * I. Sorted array is rotated by 0 steps
 * ex> nums = {1, 2, 3, 4, 5}  when nums[left] < nums[right], just return nums[left]
 *             ^           ^
 *            left        right
 *
 * II. Sorted array is rotated by n steps
 * ex> nums = {4, 5, 6, 7, 8, 1, 2, 3}  when nums[left] > nums[right]
 *             ^                    ^
 *            left                right
 *
 * Case 1: if nums[mid] > nums[left], the minimum must lie in unsorted half
 *     nums = {4, 5, 6, 7, 8, 1, 2, 3}
 *             ^        ^           ^
 *            left     mid         right
 *            |--sorted-|--unsorted--|
 *                       exclude mid
 *
 * Case 2: if nums[mid] < nums[left], the minimum must lie in unsorted half
 *     nums = {4, 5, 6, 7, 8, 1, 2, 3}
 *             ^                 ^  ^
 *            left              mid right
 *            |-----unsorted-----|---|
 *              include mid      sorted
 *
 * Case 3: if nums[mid] == nums[left], the minimum number is mid + 1
 *     nums = {4, 1, 2, 3}
 *             ^        ^
 *            left      right
 *            mid
 */
```

So let's re-design our binary search.

```c++
int findMin_sol1(vector<int>& nums) {
    if (nums.size() == 0) return INT_MAX;
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
        // TODO: array without rotated
        if (nums[left] <= nums[right]) return nums[left];
        // TODO: array is rotated
        mid = left + ((right - left) >> 1);
        if (nums[mid] == nums[left]) {
            return nums[mid + 1];
        }
        else if (nums[mid] > nums[left]) {
            left = mid + 1; // exclude middle
        }
        else {
            right = mid; // include middle
        }
    }

    return INT_MAX;
}
```

Similarly, we are able to find maximum number with binary search. The logic can be summarized as follows.

- Not rotated: if nums[left] < nums[right] return nums[right]
- Rotated:
    - nums[mid] > nums[left], then search in right part, nums[mid] included.
    - nums[mid] < nums[left], then search in left part, nums[mid] excluded.
    - nums[mid] == nums[left], return nums[mid]

```c++
int findMax_sol1(vector<int>& nums) {
    if (nums.size() == 0) return INT_MIN;
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
        // TODO: array without rotated
        if (nums[left] <= nums[right]) return nums[right];
        // TODO: array is rotated
        mid = left + ((right - left) >> 1);
        if (nums[mid] == nums[left]) {
            return nums[mid];
        }
        else if (nums[mid] > nums[left]) {
            left = mid; // include middle
        }
        else {
            right = mid - 1; // exclude middle
        }
    }

    return INT_MIN;
}
```

Tricks:

- Divide and conquer plus binary search.

### Find Peak

> A peak element is an element that is strictly greater than its neighbors.
>
> Given an integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.
>
> You may imagine that nums[-1] = nums[n] = -∞.
>
> You must write an algorithm that runs in O(log n) time.

What's the feature of peak point? its neighboring number must be smaller than it. How to find peak with binary search? There are two cases:

```c++
/**
 * Case 1: nums = {1, 2, 3, 4, 5}
 *                        ^     ^
 *                       mid   peak
 *  If mid is facing uphill (nums[mid] <= nums[mid+1]), then peak must be in the
 *  right side (excluded).
 * Case 2: nums = {5, 4, 3, 2, 1}
 *                  ^     ^
 *                 peak  mid
 *  On the contrary, if mid is facing downhill nums[mid] > nums[mid+1], the peak
 *  must be in the left side (included).
```

So we are able to design our binary search. `left` and `right` will converge at peak.

```c++
int findPeakElement_sol1(vector<int>& nums) {
    // TODO: fill boundaries
    nums.insert(nums.begin(), INT_MIN);
    nums.insert(nums.end(), INT_MIN);
    int left = 1;
    int right = nums.size() - 2;
    int mid = 0;
    while (left < right) {
        mid = left + ((right - left) >> 1);
        // TODO: where am i
        if (nums[mid] > nums[mid+1]) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    return left - 1; // shift boundary
}
```

Tricks:

- Determine searching range.

## Two Pointers

### Remove Duplicates

> Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.

The first solution is a O(N) solution. We will traverse the list with two pointers. The first pointer 'cur' points to the node being examined, and the second pointer 'probe' will explore the nodes follow 'cur' node. 'cur' node is also known as sentinel.

-  Initialize cur and probe as shown above.
-  Use probe to find the next node with different value from that of current node.
-  If `probe != cur->next`, then DUPLICATES! move cur to probe, probe move forward by 1 step. Else, append cur in our new list and move cur to probe, probe move forward.

```c++
ListNode* deleteDuplicates_sol1(ListNode* head) {
    // TODO: corner cases
    if ((head == nullptr) || (head->next == nullptr)) return head;

    ListNode* newList = new ListNode(); // for convenience
    ListNode* endOfNewList = newList;
    ListNode* cur = head;
    ListNode* probe = cur->next;
    while (true) {
        while ((probe != nullptr) && (probe->val == cur->val)) {
            probe = probe->next;
        }
        if (cur->next == probe) {
            // TODO: append to the end of list
            ListNode* node = new ListNode(cur->val);
            endOfNewList->next = node;
            endOfNewList = node;
        }
        cur = probe;
        if (cur == nullptr) { // the last case
            break;
        }
        probe = cur->next;
    }

    return newList->next; // get rid of the first null node.
}
```


