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

### Three Sum

> Given an integer array nums, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.
>
> Notice that the solution set must not contain duplicate triplets.

Two Sum and Three Sum share a similarity that the sum of elements must match the target exactly. A difference is that, instead of exactly one answer, we need to find all unique triplets that sum to zero. Before jumping in, let's check the existing solutions and determine the best conceivable runtime (BCR) for 3Sum:

- unordered two sum: it can be solved with a hash map with time complexity of O(N) and space complexity of O(N).
- ordered two sum: we are able to deal with it for O(N) by using two pointers. If original array is unordered, we need O(logN) extra time, thereby the total time complexity is O(N + logN).

Considering that there is one more dimension in 3Sum, it sounds reasonable to shoot for O(N^2).

Based on ordered two sum, we can solve three sum conveniently. But we have to take into consideration how to get rid of duplicates.

Now let's discuss how to make sure duplicates will not occur:

- hashset: if the same number is processed before, then skip it.
- order: process from left to right, for example, if `nums[i]` is processed, then we will find solution from `i+1` to `end` for numbers within `[0, i-1]` may be in the solution before, and `-nums[i]` is our target. See example below.
- optimize: `if (nums[i] > 0)`, then there is no need to proceed as all numbers after nums[i] are positive, and their combination can NOT be zero.

```c++
/**
 *  nums = {-1, 0, 1, 2, 3}
 *                 ^
 *                 i
 *  if we find solution in [begin, i) and (i, end], then we will find one solution (-1, 0, 1),
 *  which happens to be one solution when we process nums[0] (-1).
 */
```

From another aspect, for an solution `(-1, 0, 1)`, it can be produced when we process -1, 0, 1 respectively. Therefore, we keep find solution in `[i+1, end]`

```c++
vector< vector<int> > twoSum_pointers(vector<int>& nums, int targetIndex) {
    vector< vector<int> > result;
    int left = targetIndex + 1;
    int right = nums.size() - 1;
    int target = -nums[targetIndex];
    while (left < right) {
        if (nums[left] + nums[right] > target) {
            right--;
        }
        else if (nums[left] + nums[right] < target) {
            left++;
        }
        else {
            // TODO: find one solution
            result.push_back({-target, nums[left], nums[right]});
            right--;
            // avoid duplicate: move left to next different val
            int next = left + 1;
            while ((next < right) && (nums[next] == nums[left])) {
                next++;
            }
            left = next;
        }
    }

    return result;
}

vector< vector<int> > threeSum_sol2(vector<int>& nums) {
    unordered_set<int> seen;
    vector< vector<int> > result;
    vector< vector<int> > subResult;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0) break;
        if (seen.find(nums[i]) != seen.end()) continue;
        seen.insert(nums[i]);
        subResult = twoSum_pointers(nums, i);
        result.insert(result.end(), subResult.begin(), subResult.end());
    }

    return result;
}
```

Similarly, for unsorted nums, we can solve it by hashtable. But question here is how to git rid of duplicates of triplets. One solution is by hashset.

- If one solution is found, then put all combination of the solution into hashset.
- Before we insert one solution into `result`, check if it is in the hashset.

Tricks:

- STL funtions: c `qsort` and c++ `sort` in `<stdlib.h>`

```c++
#include <stdlib.h>

// C style
int myCompare_C(const void* lhs, const void* rhs) {
    return (*(int*)lhs - *(int*)rhs);
    /**
     * // Descending order: same to following if clauses
     * if (*(int*)lhs > *(int*)rhs) return 1;
     * if (*(int*)lhs == *(int*)rhs) return 0;
     * if (*(int*)lhs < *(int*)lhs) return -1;
     */
}

// C++ style
bool myCompare(int lhs, int rhs) {
    return (lhs > rhs);
}

// Calling:

sort(nums.begin(), nums.end()); // non-descending order
sort(nums.begin(), nums.end(), myCompare); // non-ascending order

qsort(arr, size, sizeof(type), compareFunc);
```

### Backspace String Compare

> Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.
>
> Note that after backspacing an empty text, the text will continue empty.

The basic idea is to simulate backspace operation on original string, and then check two strings.

```c++
bool backspaceCompare_sol2(string s, string t) {
    stack<char> ss;
    stack<char> tt;
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == '#') && (!ss.empty())) {
            ss.pop();
        }
        if (s[i] != '#') {
            ss.push(s[i]);
        }
    }
    for (int i = 0; i < t.size(); i++) {
        if ((t[i] == '#') && (!tt.empty())) {
            tt.pop();
        }
        if (t[i] != '#') {
            tt.push(t[i]);
        }
    }

    while ((!ss.empty()) && (!tt.empty())) {
        if (ss.top() != tt.top()) {
            return false;
        }
        ss.pop();
        tt.pop();
    }

    if ((!ss.empty()) || (!tt.empty())) {
        return false;
    }

    return true;
}
```

Another way is also pretty straightforward but slightly complicated.

The algorithm is to scan string from the end to begin with two pointers to two strings perspectively.

- find the first non-'#' character.
- then there are three cases:
    - both pointers are not reaching the end. (depending on)
    - one of them reaches the end. (false)
    - both of them reaches the end. (true) 

```c++
bool backspaceCompare_sol1(string s, string t) {
    string::reverse_iterator it_s = s.rbegin();
    string::reverse_iterator it_t = t.rbegin();
    stack<char> ss;
    stack<char> st;
    while ((it_s != s.rend()) || (it_t != t.rend())) {
        // TODO: find the first character remain in s from the end
        while ((it_s != s.rend()) && (*it_s == '#')) {
            while ((*it_s == '#') && (it_s != s.rend()))  {
                ss.push(*it_s);
                it_s++;
            }
            while ((!ss.empty()) && (*it_s != '#') && (it_s != s.rend())) {
                ss.pop();
                it_s++;
            }
        }

        // TODO: find the first character remain in s from the end
        while ((it_t != t.rend()) && (*it_t == '#')) {
            while ((*it_t == '#') && (it_t != t.rend())) {
                st.push(*it_t);
                it_t++;
            }
            while ((!st.empty()) && (*it_t != '#') && (it_t != t.rend())) {
                st.pop();
                it_t++;
            }
        }

        // TODO: case 1
        if ((it_s != s.rend()) && (it_t != t.rend())) {
            if (*it_s != *it_t) {
                return false;
            }
            else {
                it_s++;
                it_t++;
                continue;
            }
        }
        // TODO: case 2 & 3
        if ((it_s == s.rend()) && (it_t == t.rend())) {
            return true;
        }
        else {
            return false;
        }
    }

    return true; // both s and t are blank strings
}
```

Tricks:

- ALWAYS checking the end of iterator if `++` or `--`.
- Distinguish `rbegin()` and `rend()` from `cbegin()` and `cend()`, where `c` means const.

### Interval List Intersections

> You are given two lists of closed intervals, firstList and secondList, where `firstList[i] = [starti, endi]` and `secondList[j] = [startj, endj]`. Each list of intervals is pairwise disjoint and in sorted order.
>
> Return the intersection of these two interval lists.
>
> A closed interval `[a, b] (with a <= b)` denotes the set of real numbers x with `a <= x <= b`.
>
> The intersection of two closed intervals is a set of real numbers that are either empty or represented as a closed interval. For example, the intersection of [1, 3] and [2, 4] is [2, 3].

The idea of solution 1 is pretty straightforward, which is to simulate intersections with an array. Project A and B to array, and the elements with value 2 consist of intersection list.

If `intersection[i]` is greater than 0, then interval [i, i+1) is painted. 

But the limitation of this method is that it can only find the interval except intersection points. To fix that, we use a hashmap to find intersection points.

```c++
vector< vector<int> > intervalIntersection_sol1(vector< vector<int> >& firstList, vector< vector<int> >& secondList) {
    int max_size = 1002;
    unordered_map<int, int> points;
    vector<int> intersection(max_size);
    vector< vector<int> > result;
    for (int i = 0; i < firstList.size(); i++) {
        if (points.find(firstList[i][0]) == points.end()) {
            points[firstList[i][0]] = 1;
        }
        else {
            points[firstList[i][0]]++;
        }
        if (points.find(firstList[i][1]) == points.end()) {
            points[firstList[i][1]] = 1;
        }
        else {
            points[firstList[i][1]]++;
        }
        for (int j = firstList[i][0]; j < firstList[i][1]; j++) {
            intersection[j]++;
        }
    }
    for (int i = 0; i < secondList.size(); i++) {
        if (points.find(secondList[i][0]) == points.end()) {
            points[secondList[i][0]] = 1;
        }
        else {
            points[secondList[i][0]]++;
        }
        if (points.find(secondList[i][1]) == points.end()) {
            points[secondList[i][1]] = 1;
        }
        else {
            points[secondList[i][1]]++;
        }
        for (int j = secondList[i][0]; j < secondList[i][1]; j++) {
            intersection[j]++;
        }
    }

    // TODO: push overlap points into result
    for (auto pair : points) {
        if (pair.second >= 2) {
            result.push_back({pair.first, pair.first});
        }
    }

    // TODO: construct output with two pointers, interval [l, r)
    int l = 0;
    int r = 0;
    int length = max(firstList[firstList.size()-1][1], secondList[secondList.size()-1][1]);
    while (l <= length) {
        // TODO: move l to the next 2
        while ((intersection[l] != 2) && (l < length)) {
            l++;
        }
        r = l;
        // TODO: r explore the end of consecutive 2
        while ((intersection[r] == 2) && (r < length)) {
            r++;
        }
        if (l < length) {
            result.push_back({l, r});
        }
        else {
            break;
        }
        l = r;
    }

    return result;
}
```

The second solution is based on two observations below. Define: interval [a, b], b as endpoint of an interval.

```c++
/**
 * ex>    list A:  -----    ---------  --------      --------
 *        list B: ---      ----- --------- ---- ---  ----
 *                  ^
 *  intersection:  -- ,which is {max(A[0][0], B[0][0]), min(A[0][1], B[0][1])}
 *                  ^
 */
```

- the interval with smallest endpoint will intersect with only one interval in the other list.
- the interval with smallest endpoint will share the same endpoint with intersection interval.

```c++
vector< vector<int> > intervalIntersection_sol2(vector< vector<int> >& firstList, vector< vector<int> >& secondList) {
    vector< vector<int> > result;
    int pa = 0;
    int pb = 0;
    while ((pa < firstList.size()) && (pb < secondList.size())) {
        // TODO: find interval with smallest endpoint
        int l = max(firstList[pa][0], secondList[pb][0]);
        int r = min(firstList[pa][1], secondList[pb][1]);
        if (l <= r) {
            result.push_back({l, r});
        }
        (firstList[pa][1] < secondList[pb][1]) ? pa++ : pb++;
    }

    return result;
}
```

### Container with Most Water

> Given n non-negative integers `a1, a2, ..., an`, where each represents a point at coordinate `(i, ai)`. n vertical lines are drawn such that the two endpoints of the line i is at `(i, ai)` and `(i, 0)`. Find two lines, which, together with the x-axis forms a container, such that the container contains the most water.
>
> Notice that you may not slant the container.

The equaltion for water area is `area = min(height[l], height[r]) * (r - l)`. Our goal is maximum two operands on the two sides of `*` sign.

We will use greedy algorithm to solve it.

1. Set two pointers to at the leftmost and rightmost index of pillars where we maximize '(r - l)'.
2. Move r to left and l to right respectively.
    - if height[r-1] < height[r], then jump it, since the second operand get smaller but the first remain same at best.
    - same operation to `l` as it moves to right.

Unfortunately, the time complexity for the algorithm above is O(N^2). Our improvement is based on other fact: If left do not change and only move right pillar when the height of right pillar is higher than left one, the water area will get smaller.

```c++
/**
 * ex>  1  2  3  5  3  2  1
 *      ^                 ^
 *     left         <-- right
 *
 * When right go from 1 to 5, (r - l) get smaller, and min(height[l], height[r])
 * do NOT change!
 */
```

Summary:

- maximize min(height[l], height[r]): move smaller one such that it can be greater.
- maximize (r - l): starting from leftmost and rightmost.

```c++
int maxArea_sol1(vector<int>& height) {
    if (height.size() < 2) return 0;
    int l = 0;
    int r = height.size() - 1;
    int maxArea = min(height[l], height[r]) * (r - l);
    int area = 0;
    while (l < r) {
        if (height[l] <= height[r]) {
            // TODO: move to next greater one
            int leftHeight = height[l];
            while ((l < r) && (leftHeight >= height[l])) {
                l++;
            }
        }
        else {
            int rightHeight = height[r];
            while ((l < r) && (height[r] <= rightHeight)) {
                r--;
            }
        }
        // TODO: update maxArea
        if (l < r) {
            area = min(height[l], height[r]) * (r - l);
            maxArea = area > maxArea ? area : maxArea;
        }
    }

    return maxArea;
}
```

Tricks:

- Observation and find patterns.

## Slide Window

### Find All Anagrams

> Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.
>
> An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

Solution 1 uses the method called move and query. We will build a set to store the permutation of string p, and make a window slide from left to right. At each step query if substring within window is in set. If so, got it!

But the time complexity of enumerating all permutations is O(N!)

The key here is frequency. So solution 2 will design two vecotrs to record frequency of s and p.

```c++
/**
 * ex>  cbaebabacd     p = abc
 *   fp = '1110000...000'
 *         ^^^
 *         abcdefg...xyz
 *   fs = '1110000...000'
 *         ^^^
 *         abcdefg...xyz
 * window 'cbaebabacd'
 *         ^ ^
 */
```

```c++
vector<int> findAnagrams_sol2(string s, string p) {
    if (p.length() > s.length()) return {};
    vector<int> result;
    vector<int> ss(26, 0);
    vector<int> sp(26, 0);
    for (int i = 0; i < p.length(); i++) {
        sp[p[i] - 'a']++;
        ss[s[i] - 'a']++;
    }

    int begin = 0;
    int end = begin + p.length();
    while (end <= s.length()) {
        if (sp == ss) {
            result.push_back(begin);
        }
        ss[s[begin] - 'a']--;
        if (end < s.length()) {
            ss[s[end] - 'a']++;
        }
        begin++;
        end++;
    }

    return result;
}
```

Tricks:

- vector comparison: `sp == ss`.

## BFS and DFS

### Number of Islands

> Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
>
> An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

This is a variant problem for Maximum Area of Islands. The solution is similar by BFS.

```c++
/**
 * @brief tagIsland
 * @param grid: the map
 * @param isTagged: record if point is tagged
 * @param i: row index of starting point
 * @param j: column index of starting point
 * tag all points within an island with BFS.
 */
void tagIsland(vector< vector<char> >& grid,
               vector< vector<bool> >& isTagged, int i, int j) {
    isTagged[i][j] = true;
    if ((i + 1 < isTagged.size()) && (grid[i+1][j] == '1') && (!isTagged[i+1][j]))
        tagIsland(grid, isTagged, i+1, j);
    if ((i - 1 >= 0) && (grid[i-1][j] == '1') && (!isTagged[i-1][j]))
        tagIsland(grid, isTagged, i-1, j);
    if ((j + 1 < isTagged[0].size()) && (grid[i][j+1] == '1') && (!isTagged[i][j+1]))
        tagIsland(grid, isTagged, i, j+1);
    if ((j - 1 >= 0) && (grid[i][j-1] == '1') && (!isTagged[i][j-1]))
        tagIsland(grid, isTagged, i, j-1);

    return;
}

/**
 * @brief numIslands
 * @param grid
 * @return the number of islands
 * Starting from (0, 0), find each island and tag it.
 *
 * T: O(N * M), S: O(N * M)
 */
int numIslands_sol1(vector< vector<char> >& grid) {
    vector< vector<bool> > isTagged(
                grid.size(),
                vector<bool>(grid[0].size(), false));
    int numOfIslands = 0;

    // TODO: traverse grid
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if ((grid[i][j] == '1') && (!isTagged[i][j])) {
                numOfIslands++;
                // TODO: tag points within the island
                tagIsland(grid, isTagged, i, j);
            }
        }
    }

    return numOfIslands;
}
```

### Number of Provinces

> There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
>
> A province is a group of directly or indirectly connected cities and no other cities outside of the group.
>
> You are given an n x n matrix isConnected where `isConnected[i][j] = 1` if the ith city and the jth city are directly connected, and `isConnected[i][j] = 0` otherwise.
>
> Return the total number of provinces.

Basic idea: traverse all cities. 

- if the city is tagged with a province, then skip.
- else find all cities which belongs to the same province as current city.

```c++
/**
 * @brief tagCity
 * @param isConnected: connection map
 * @param isTagged: if current city is tagged
 * @param i: ith city
 */
void tagCity(vector< vector<int> >& isConnected, vector<bool>& isTagged, int i) {
    queue<int> q;
    q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        isTagged[cur] = true;
        for (int i = 0; i < isConnected.size(); i++) {
            if ((i != cur) && (!isTagged[i]) && (isConnected[cur][i] == 1)) {
                q.push(i);
            }
        }
    }
}

/**
 * @brief findCircleNum_sol1
 * @param isConnected: a connection map where isConnected[i][j] = 1 if the ith city
 * and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
 * @return the number of provinces
 *
 * Input: [ [1,1,0],
 *          [1,1,0],
 *          [0,0,1] ]
 *
 * Basic idea: traverse all cities.
 *  if the city is tagged with a province, then skip.
 *  else find all cities which belongs to the same province as current city.
 *
 * How to find directly or indirectly connected cities? isConnected map!
 *
 * T: O(N), S: O(N)
 */
int findCircleNum_sol1(vector< vector<int> >& isConnected) {
    vector<bool> isTagged(isConnected.size(), false);
    int numOfProvinces = 0;

    // TODO: traverse all cities
    for (int i = 0; i < isConnected.size(); i++) {
        if (!isTagged[i]) {
            numOfProvinces++;
            tagCity(isConnected, isTagged, i);
        }
    }

    return numOfProvinces;
}
```

### Subtree of Another Tree

> Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
>
> A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.

How to check if two trees are same? Recursion!

```c++
bool isEqual(TreeNode* lhs, TreeNode* rhs) {
    if ((lhs == nullptr) && (rhs == nullptr)) {
        return true;
    }
    // either of them is nullptr then return false
    if ((lhs == nullptr) || (rhs == nullptr)) return false;

    if (lhs->val != rhs->val) return false;
    return (isEqual(lhs->left, rhs->left) && isEqual(lhs->right, rhs->right));
}

/**
 * @brief isSubtree
 * @param root: the root of original tree
 * @param subRoot: sample subtree
 * @return true if root tree includes subRoot tree
 */
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (subRoot == nullptr) return true;
    if (root == nullptr) return false;

    if (isEqual(root, subRoot)) return true;

    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}
```

### Populating Pointers

> Given a binary tree, populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
>
> Initially, all next pointers are set to NULL.

Notice that different from the similar question in Algorithm I, this is NOT a complete tree. But we are able to solve it with level-order search as well.

```c++
/**
 * @brief connect
 * @param root: the root of tree
 * @return a tree has been connected
 * Add new property 'level' to each node. Traverse node in level order and connect
 * them.
 */
Node* connect(Node* root) {
    class QueueNode {
    public:
        QueueNode(int _level, Node* _node)
            : node(_node), level(_level) {}

        Node* node;
        int level;
    };

    if (root == nullptr) return root;
    QueueNode first(0, root);
    queue<QueueNode> que;
    que.push(first);
    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();
        if (!que.empty()) {
            QueueNode next = que.front();
            if (cur.level == next.level) {
                cur.node->next = next.node;
            }
        }
        if (cur.node->left != nullptr) {
            que.push(QueueNode(cur.level+1, cur.node->left));
        }
        if (cur.node->right != nullptr) {
            que.push(QueueNode(cur.level+1, cur.node->right));
        }
    }

    return root;
}
```

Tricks:

- track level of each node.

### Shortest Path in Binary Matrix

> Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
>
> A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

- All the visited cells of the path are 0.
- All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).

> The length of a clear path is the number of visited cells of this path.

The algorithm is use point whose shortest path is known to render its neighboring points, tracking the shortest path for each point.

```c++
int shortestPathBinaryMatrix_sol3(vector< vector<int> >& grid) {
    if (grid.size() == 0) return -1;
    if (grid[0][0] == 1) return -1;

    int target_x = grid.size() - 1;
    int target_y = grid[0].size() - 1;
    int x_direction[8] = {1, 0, 1, -1, 1, -1, 0, -1};
    int y_direction[8] = {1, 1, 0, 1, -1, 0, -1, -1};

    class Point {
    public:
        int x;
        int y;

        Point()
            : x(0), y(0) {};
        Point(int _x, int _y)
            : x(_x), y(_y) {};
    };

    vector< vector<int> > dist(grid.size(),
                               vector<int>(grid[0].size(), INT_MAX));
    dist[0][0] = 1;
    queue<Point> que;
    que.push(Point(0, 0));

    while (!que.empty()) {
        Point cur = que.front();
        que.pop();

        for (int i = 0; i < 8; i++) {
            int x = cur.x + x_direction[i];
            int y = cur.y + y_direction[i];
            if ((x >= 0) && (y >= 0)
                && (x < grid.size()) && (y < grid[0].size())
                && (grid[x][y] == 0)
                && (dist[x][y] == INT_MAX)) {
                dist[x][y] = dist[cur.x][cur.y] + 1;
                que.push(Point(x, y));
            }
        }
    }

    return (dist[target_x][target_y] == INT_MAX) ? -1 : dist[target_x][target_y];
}
```

Tricks:

- Tracking shortest path for each point.

### Surrounded Regions

> Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally surrounded by 'X'.
>
> A region is captured by flipping all 'O's into 'X's in that surrounded region.

We will concentrate on cells remain to be 'O', meaning will not be captured. Those cells are connected to the cells on the border. So we start from all border cells and BFS. At last, re-render our board with `buff`.

```c++
class Point {
public:
    int x;
    int y;
    Point(int _x, int _y)
        : x(_x), y(_y) {};
};

void traverseHelper(vector< vector<char> >& board,
                    vector< vector<bool> >& visited,
                    vector<Point>& buf,
                    int ox, int oy) {
    int dir_x[4] = {-1, +1, 0, 0};
    int dir_y[4] = {0, 0, -1, +1};

    visited[ox][oy] = true;

    queue<Point> que;
    que.push(Point(ox, oy));
    buf.push_back(Point(ox, oy));
    while (!que.empty()) {
        Point cur = que.front();
        que.pop();
        for (int index = 0; index < 4; index++) {
            int x = cur.x + dir_x[index];
            int y = cur.y + dir_y[index];
            if ((x >= 0) && (y >= 0) && (x < board.size()) && (y < board[0].size())
                && (board[x][y] == 'O')
                && (!visited[x][y])) {
                visited[x][y] = true;
                que.push(Point(x, y));
                buf.push_back(Point(x, y));
            }
        }
    }
}

/**
 * @brief solve_sol2
 * @param board
 * On the contrary to sol1, we will concentrate on cells remain to be 'O', meaning
 * will not be captured. Those cells are connected to the cells on the border.
 *
 * So what we need to do is find all islands connected to the border.
 * - starting from all border cells and BFS
 */
void solve_sol2(vector< vector<char> >& board) {
    if (board.size() == 0) return;
    vector< vector<bool> > visited(board.size(),
                                   vector<bool>(board[0].size(), false))

    // keep track all cells on islands connected with borders.
    vector<Point> buff;
    // left and right border
    for (int i = 0; i < board.size(); i++) {
        if ((board[i][0] == 'O') && (!visited[i][0])) {
            traverseHelper(board, visited, buff, i, 0);
        }
        if ((board[i][board[0].size()-1] == 'O') && (!visited[i][board[0].size()-1])) {
            traverseHelper(board, visited, buff, i, board[0].size()-1);
        }
    }
    // top and bottom border
    for (int j = 0; j < board[0].size(); j++) {
        if ((board[0][j] == 'O') && (!visited[0][j])) {
            traverseHelper(board, visited, buff, 0, j);
        }
        if ((board[board.size()-1][j] == 'O') && (!visited[board.size()-1][j])) {
            traverseHelper(board, visited, buff, 0, board.size()-1);
        }
    }

    // re-render board
    for (int i = 0; i < board.size() - 1; i++) {
        for (int j = 0; j < board[0].size() - 1; j++) {
            board[i][j] = 'X';
        }
    }
    for (Point pt : buff) {
        board[pt.x][pt.y] = 'O';
    }
}
```

Tricks:

- Find characteristics of result cells.

### All Paths from Source to Target

> Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1, find all possible paths from node 0 to node n - 1 and return them in any order.
>
> The graph is given as follows: `graph[i]` is a list of all nodes you can visit from node i (i.e., there is a directed edge from node i to node `graph[i][j]`).

Basically there are two ways: BFS or DFS with path tracking.

- BFS solution:

```c++
/**
 * @brief allPathsSourceTarget_sol1
 * @param graph
 * @return all paths
 * Basically, BFS or DFS with tracking path.
 */
vector< vector<int> > allPathsSourceTarget_sol1(vector< vector<int> >& graph) {
    vector< vector<int> > result;
    if (graph.size() == 0) return result;

    class QueueNode {
    public:
        int node;
        vector<int> path;
        QueueNode(int _node, vector<int> _path)
            : node(_node), path(_path) {}
    };

    int target = graph.size() - 1;
    queue<QueueNode> que;
    que.push(QueueNode(0, {0}));
    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();
        if (cur.node == target) {
            result.push_back(cur.path);
        }
        for (int neighbor = 0; neighbor < graph[cur.node].size(); neighbor++) {
            // choose
            cur.path.push_back(graph[cur.node][neighbor]);
            que.push(QueueNode(graph[cur.node][neighbor], cur.path));
            // unchoose
            cur.path.pop_back();
        }
    }

    return result;
}
```

- DFS solution:

```c++
void searchHelper(vector< vector<int> >& graph,
                  vector< vector<int> >& result,
                  int node,
                  vector<int>& path,
                  int target) {
    if (node == target) {
        result.push_back(path);
    }

    for (int i = 0; i < graph[node].size(); i++) {
        // choose
        path.push_back(graph[node][i]);
        searchHelper(graph, result, graph[node][i], path, target);
        // unchoose
        path.pop_back();
    }
}

/**
 * @brief allPathsSourceTarget_sol2
 * @param graph
 * @return
 * Solution2 will employ deep first search.
 */
vector<vector <int> > allPathsSourceTarget_sol2(vector< vector<int> >& graph) {
    vector< vector<int> > result;
    if (graph.size() == 0) return result;
    vector<int> path = {0};

    searchHelper(graph, result, 0, path, graph.size()-1);

    return result;
}
```

## Recursion and Backtracking

### Subsets

> Given an integer array nums of unique elements, return all possible subsets (the power set).
>
> The solution set must not contain duplicate subsets. Return the solution in any order.

```c++
void subsetsHelper(vector<int>& left, vector<int>& sofar,
                   vector< vector<int> >& result) {
    if (left.size() == 0) {
        result.push_back(sofar);
        return;
    }

    int cur = left.back();
    left.pop_back();
    // not choose the last number
    subsetsHelper(left, sofar, result);
    // choose the last number
    sofar.push_back(cur); // reuse sofar
    subsetsHelper(left, sofar, result);
    // restore environment
    sofar.pop_back();
    left.push_back(cur);
}

/**
 * @brief subsets
 * @param nums
 * @return all subsets of given nums
 * Choose and not choose.
 */
vector< vector<int> > subsets(vector<int>& nums) {
    vector< vector<int> > result;
    if (nums.size() == 0) return result;

    vector<int> sofar;
    subsetsHelper(nums, sofar, result);

    return result;
}
```

Tricks:

- Reuse buffers and keep environment unchanged.

### Subsets II

> Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
>
> The solution set must not contain duplicate subsets. Return the solution in any order.

One way to generate all subsets is construction.

```c++
/**
 * ex> input: {0, 1, 2}
 * - start from {}
 * - 1st (add 0): ({}) + {0}
 * - 2nd (add 1): ({}, {0}) + {1}, {0, 1}
 * - 3rd (add 2): ({}, {0}, {1}, {0, 1}) + {2}, {0, 2}, {1, 2}, {0, 1, 2}
 * - so we get all subsets {}, {0}, {1}, {0, 1}, {2}, {0, 2}, {1, 2}, {0, 1, 2}
 */
```

How to solve duplicates? Refine construction process (input nums must be ordered).

```c++
/**
 * ex> input: {0, 2, 1, 2, 2, 3} -> ordered {0, 1, 2, 2, 2, 3}
 * - start from {}
 * - 1st (add 0): ({}) + {0}
 * - 2nd (add 1): ({}, {0}) + {1}, {0, 1}
 * - 3rd (add 2): ({}, {0}, {1}, {0, 1}) + {2}, {0, 2}, {1, 2}, {0, 1, 2}
 * - 4th (add 2): when add duplicated number, we just need add to subsets generated
 * by previous step.
 * ({}, {0}, {1}, {0, 1}, {2}, {0, 2}, {1, 2}, {0, 1, 2}) + {2, 2}, {0, 2, 2}, {1, 2, 2}, {0, 1, 2, 2}
 *                         |-------- previous --------|
 * - 5th (add 2): ...
 */
```

So we need to track the starting index of subsets generated in previous step. The algorithm will be:

- If new number has been seen before, construct new subsets with subsets generated in previouse step.
- Construct new subsets with all existed subsets otherwise.

```c++
/**
 * @brief subsetsWithDup
 * @param nums
 * @return
 */
vector< vector<int> > subsetsWithDup(vector<int>& nums) {
    set<int> seen;
    vector< vector<int> > result;
    result.push_back({});
    int start = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        if (seen.find(nums[i]) != seen.end()) {
            // has been seen, add to previous subsets
            vector< vector<int> > add;
            for (int j = start; j < result.size(); j++) {
                vector<int> subset = result[j];
                subset.push_back(nums[i]);
                add.push_back(subset);
            }
            start = result.size();
            // concatenate new subsets
            result.insert(result.end(), add.begin(), add.end());
        }
        else {
            // not seen, add to all subsets
            seen.insert(nums[i]);
            vector< vector<int> > add;
            for (int j = 0; j < result.size(); j++) {
                vector<int> subset = result[j];
                subset.push_back(nums[i]);
                add.push_back(subset);
            }
            start = result.size();
            // concatenate new subsets
            result.insert(result.end(), add.begin(), add.end());
        }
    }

    return result;
}
```

Tricks:

- For `seen`, there are two ways to achieve that. The generic way is use `set`. The other is based on given contrains: the range of `nums[i]` is from -10 to 10. Therefore, we are able to use a vector to map the range.

### Permutation II

> Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

The way to get rid of duplications is similar to Subsets II. At each step of constructing new permutations, get rid of duplicated choices.

```c++
void permutationHelper(vector<int>& left, vector<int>& selected,
                       vector< vector<int> >& result) {
    if (left.size() == 0) {
        result.push_back(selected);
        return;
    }

    set<int> seen;
    // choose:
    int size = left.size();
    for (int i = 0; i < size; i++) {
        if (seen.find(left[i]) == seen.end()) {
            // not found
            seen.insert(left[i]);
            int cur = left[i];
            left.erase(left.begin() + i);
            selected.push_back(cur);
            permutationHelper(left, selected, result);
            // restore
            selected.pop_back();
            left.insert(left.begin() + i, cur);
        }
        else {
            // ignore current number
            continue;
        }
    }
}

/**
 * @brief permuteUnique_sol1
 * @param nums
 * @return all unique permutations.
 * We will generate all permutations by construction. If we do not take uniqueness
 * into consideration, n numbers will generate n! permutations.
 * ex> input {1, 1, 2}
 * 1st: (1 | 1 | 2) 3 choices
 * 2nd: (1 | 2) | (1 | 2) | (1 | 1) 2 choices
 * 3nd: ... 1 choice
 * How to get rid of duplications? In each round, ignore duplicated number.
 */
vector< vector<int> > permuteUnique_sol1(vector<int>& nums) {
    vector< vector<int> > result;
    if (nums.size() == 0) return result;
    vector<int> selected;

    sort(nums.begin(), nums.end());
    permutationHelper(nums, selected, result);

    return result;
}


void permutationHelper2(vector<int>& left, vector<int>& selected,
                       vector< vector<int> >& result) {
    if (left.size() == 0) {
        result.push_back(selected);
        return;
    }

    vector<bool> seen(21, false);
    int shift = 10; // -10 -> index 0
    // choose:
    int size = left.size();
    for (int i = 0; i < size; i++) {
        if (!seen[left[i] + shift]) {
            // not found
            seen[left[i] + shift] = true;
            int cur = left[i];
            left.erase(left.begin() + i);
            selected.push_back(cur);
            permutationHelper(left, selected, result);
            // restore
            selected.pop_back();
            left.insert(left.begin() + i, cur);
        }
        else {
            // ignore current number
            continue;
        }
    }
}
```

Tricks:

- `vector.erase(iter)`: remove ith item.
- `vector.insert(iter, item)`: insert item to ith index.

### Combination Sum

> Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
>
> The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
>
> It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

The key to this problem is how to remove duplication. In general, we will handle that by `set` or a mapping `vector`.

```c++
/**
 * @brief combinationSumHelper
 * @param candidates
 * @param selected
 * @param result
 * @param target
 * Base case:
 *  if target is equal to 0, then bingo.
 *  if there is no candidate and target is not 0, fail.
 * Recursion:
 *  reduce the problem.
 *
 * Remove duplications with set<string>, we will sort the result and compare.
 */
void combinationSumHelper(vector<int>& candidates,
                          vector<int>& selected,
                          set< vector<int> >& seen,
                          vector< vector<int> >& result,
                          int target) {
    if (target == 0) {
        // BUG: we cannot sort selected directly as it will affect pop_back() in higher
        // level.
        // ex> {3, 2, 2}, pop_back() will pop 2.
        //     {2, 2, 3}, pop_back() will pop 3. which causes conflicts.
        vector<int> sorted = selected;
        sort(sorted.begin(), sorted.end());
        if (seen.find(sorted) == seen.end()) {
            seen.insert(sorted);
            result.push_back(sorted);
        }
        return;
    }
    if ((candidates.size() == 0) || (target < 0)) {
        return;
    }

    for (int i = 0; i < candidates.size(); i++) {
        int cur = candidates[i];
        selected.push_back(cur);
        combinationSumHelper(candidates, selected, seen, result, target - cur);
        selected.pop_back();
    }
}

/**
 * @brief combinationSum_sol1
 * @param candidates
 * @param target
 * @return
 * Reduce the problem until the target is 0.
 * ex> input: {2, 3, 6, 7} target 7
 * reduce to: {2} + result of {2 ,3, 6, 7} target 5 (should be {2, 3} target 5, as
 * 6 and 7 are greater than 5)
 * ...
 * until target == 0.
 */
vector< vector<int> > combinationSum_sol1(vector<int>& candidates, int target) {
    vector< vector<int> > result;
    vector<int> selected;
    set< vector<int> > seen;

    combinationSumHelper(candidates, selected, seen, result, target);

    return result;
}
```

However, for combination problems, we are able to solve it cleverly. Notice that all solutions starting from the first elements will include all other elements. Therefore, we are able to ignore the first element when we get all solutions starting from the second element.

Solve in order.

```bash
# 1st: starting from 2, candidates are {2, 3, 6, 7}
# 2nd: starting from 3, candidates are {3, 6, 7}
# 3rd: starting from 6, candidates are {6, 7}
# ...
```

```c++
/**
 * @brief combinationSumHelper2
 * @param candidates
 * @param selected
 * @param result
 * @param target
 * @param start: start from ith candidates
 */
void combinationSumHelper2(vector<int>& candidates,
                          vector<int>& selected,
                          vector< vector<int> >& result,
                          int target, int start) {
    if (target == 0) {
        vector<int> sorted = selected;
        sort(sorted.begin(), sorted.end());
        result.push_back(sorted);
        return;
    }
    if ((candidates.size() == 0) || (target < 0)) {
        return;
    }

    for (int i = start; i < candidates.size(); i++) {
        int cur = candidates[i];
        selected.push_back(cur);
        combinationSumHelper2(candidates, selected,  result, target - cur, i);
        selected.pop_back();
    }
}

/**
 * @brief combinationSum_sol2
 * @param candidates
 * @param target
 * @return
 * Is there a better way to solve duplications? sorting and select in order.
 * ex> input {3, 4, 5}
 * in all solution starting with 3, it involves 4. So we don't have to consider 3 for
 * the solution starting with 4.
 */
vector< vector<int> > combinationSum_sol2(vector<int>& candidates, int target) {
    vector< vector<int> > result;
    vector<int> selected;
    set< vector<int> > seen;

    combinationSumHelper2(candidates, selected, result, target, 0);

    return result;
}
```

Tricks:

- Remove duplications in combination problem: select in order. 

### Combination Sum II

> Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
>
> Each number in candidates may only be used once in the combination.
>
> Note: The solution set must not contain duplicate combinations.

The difference for this problem from Combination is there are duplicated elements. How to get rid of duplicated elements? One way to solve it is grouping them. For example, if there are `n` 1's, then when process 1, it will have `n+1` branches. Keep each group unique.

```c++
void combinationSum2Helper2(vector<int>& candidates_group,
                            vector<int>& selected,
                            vector< vector<int> >& result,
                            int target,
                            int start) {
    // base case:
    if (target == 0) {
        result.push_back(selected);
        return;
    }
    if ((target < 0) | (start >= candidates_group.size())) {
        return;
    }

    // recursion:
    int cnt = candidates_group[start];
    int cur = start;
    int next_start = start + 1;
    while ((next_start < candidates_group.size()) && (candidates_group[next_start] == 0)) {
        next_start++;
    }

    // select 0 to cnt times
    for (int i = 0; i <= cnt; i++) {
        for (int j = 0; j < i; j++) {
            selected.push_back(cur);
        }
        combinationSum2Helper2(candidates_group, selected, result, target - cur * i, next_start);
        for (int j = 0; j < i; j++) {
            selected.pop_back();
        }
    }
}

/**
 * @brief combinationSum2_sol2
 * @param candidates
 * @param target
 * @return
 * Two observations:
 * - In this problem, each number in the input is not unique. The implication of this
 * difference is that we need some mechanism to avoid generating duplicate combinations.
 * - In this problem, each number can be used only once. The implication of this difference
 * is that once a number is chosen as a candidate in the combination, it will not appear
 * again as a candidate later.
 * The key here is to keep all elements unique. Then is has the same solution to CombinationSum.
 *
 * One way to solve it is to group.
 * ex> candidates: {1, 1, 1, 1, 3}   target = 3
 * We will see 4 1's as a group. Then there are two elements {1, 1, 1, 1} and 3.
 * 1st: {}(3) -> {}(3) | {1}(2) | {1, 1}(1) | {1, 1, 1}(0) | {1, 1, 1, 1}(-1)
 * 2nd: choose 3 or not.
 *
 * in other word, if 1 is seen in previous candidates, then it can only be chosen. That is
 * the first 1 can be chosen and not, but the following 1's must be chosen.
 */
vector< vector<int> > combinationSum2_sol2(vector<int>& candidates, int target) {
    vector< vector<int> > result;
    vector<int> selected;
    sort(candidates.begin(), candidates.end());

    // TODO: group, 1 <= candidates[i] <= 50
    vector<int> candidates_group(51, 0);
    for (int i = 0; i < candidates.size(); i++) {
        candidates_group[candidates[i]]++;
    }

    combinationSum2Helper2(candidates_group, selected, result, target, candidates[0]);

    return result;
}
```

Tricks:

- Group: one way to keep elements unique.

### Letter Combinations Of Phone Number

> Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
>
> A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

This a a classic combination problem which can be solved with decision tree.

```c++
void letterCombinationsHelper(string& left, string& chosen,
                              vector<string>& result,
                              unordered_map<int, string>& map,
                              int index) {
    if (index >= left.size()) {
        result.push_back(chosen);
        return;
    }

    char cur = left[index];
    for (char ch : map[cur - '0']) {
        // choose
        chosen.push_back(ch);
        letterCombinationsHelper(left, chosen, result, map, index + 1);
        // unchoose
        chosen.pop_back();
    }
}

/**
 * @brief letterCombinations
 * @param digits
 * @return
 * Decision tree.
 */
vector<string> letterCombinations(string digits) {
    vector<string> result;
    if (digits.size() == 0) return result;

    unordered_map<int, string> map = {
        {2, "abc"}, {3, "def"}, {4, "ghi"},
        {5, "jkl"}, {6, "mno"}, {7, "pqrs"},
        {8, "tuv"}, {9, "wxyz"}
    };
    string chosen;
    letterCombinationsHelper(digits, chosen, result, map, 0);

    return result;
}
```

### Generate Parentheses

> Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Group and make decisions. Two observations:

- left parentheses `(` is allowed to be chosen when it is available.
- right parentheses `)` allowed when the number of right parentheses is greater than that of left parentheses.

```c++
void generateParenthesisHelper(vector<int>& left,
                               string chosen,
                               vector<string>& result) {
    if (left[0] == 0) {
        // left parentheses has been run out of.
        for (int i = 0; i < left[1]; i++) {
            chosen.push_back(')');
        }
        result.push_back(chosen);
        for (int i = 0; i < left[1]; i++) {
            chosen.pop_back();
        }
        return;
    }

    // choose left or right?
    // - condition for left: if left is available
    // - condition for right: if # of right parentheses > # of left parentheses
    // choose left
    chosen.push_back('(');
    left[0]--;
    generateParenthesisHelper(left, chosen, result);
    chosen.pop_back();
    left[0]++;

    // choose right
    if (left[1] > left[0]) {
        chosen.push_back(')');
        left[1]--;
        generateParenthesisHelper(left, chosen, result);
        chosen.pop_back();
        left[1]++;
    }
}

/**
 * @brief generateParenthesis
 * @param n
 * @return combinations of all parentheses
 * It can be seen as group problem. We can create a vector to store how much left/right
 * parentheses left and make decisions on each step.
 *
 * T: O(N!)
 */
vector<string> generateParenthesis(int n) {
    vector<string> result;
    if (n == 0) return result;
    vector<int> left = {n, n};
    string chosen;
    generateParenthesisHelper(left, chosen, result);

    return result;
}
```

### Word Search

> Given an m x n grid of characters board and a string word, return true if word exists in the grid.
>
> The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

The solution to the problem is similar to maze with DFS.

```c++
bool existHelper(vector< vector<char> >& board,
                 vector< vector<bool> >& visited,
                 string& word,
                 int x, int y,
                 int start) {
    static int dir_x[4] = {0, +1, 0, -1};
    static int dir_y[4] = {+1, 0, -1, 0};

    if (start >= word.size()) {
        return true;
    }

    if ((x < 0) || (x >= board.size()) || (y < 0) || (y >= board[0].size())) {
        // out of bounds
        return false;
    }
    if (word[start] != board[x][y]) {
        // not equal
        return false;
    }
    if (visited[x][y]) {
        // cannot be chosen twice
        return false;
    }

    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        // search on 4 directions
        int next_x = x + dir_x[i];
        int next_y = y + dir_y[i];
        if (existHelper(board, visited, word, next_x, next_y, start+1)) {
            return true;
        }
    }
    visited[x][y] = false;

    return false;
}

/**
 * @brief exist
 * @param board
 * @param word
 * @return
 * The solution to the problem is similar to maze with DFS.
 */
bool exist(vector< vector<char> >& board, string word) {
    int m = board.size();
    int n = board[0].size();
    if (word.size() == 0) return true;
    if (m == 0) return false;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0]) {
                // keep one cell chosen one time
                vector< vector<bool> > visited(m, vector<bool>(n, false));
                // seed cell is found
                if (existHelper(board, visited, word, i, j, 0)) {
                    return true;
                }
            }
        }
    }

    return false;
}
```

Tricks:

- Restore environment before backtracking.

## Dynamic Programming

### House Robber II

> You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
>
> Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

The first solution is by recursion and buffer.

```c++
/**
 * @brief maxIncome
 * @param vals: a vector of money each house has
 * @param size: size of houses
 * @param start: start of available houses to rob
 * @param length: how many houses left to rob
 * @return
 */
int maxIncome(vector< vector< int > >& buf,
              vector<int>& vals, int size,
              int start, int length) {
    if (length <= 0) {
        return 0;
    }

    if (buf[start][length] != -1) {
//        cout << start << ": " << length << " => " << buf[start][length] << endl;
        return buf[start][length];
    }

    buf[start][length] = max(vals[start] + maxIncome(buf, vals, size, (start + 2) % size, length - 2),
                             maxIncome(buf, vals, size, (start + 1) % size, length - 1)
                            );
//    cout << start << ": " << length << " => " << buf[start][length] << endl;

    return buf[start][length];
}

/**
 * @brief rob_sol1
 * @param nums
 * @return the maximum value of robbed money
 * Recall from algorithm for houserobber, and we can find there is some similarity betwee
 * these two problems. The only difference is there is a circle in houserobber2.
 *
 * But the circle only affects the decision for the first time.
 *
 * ex> 1 -> 2 -> 3 -> 4 -> 5
 *     |-------<-----------|
 *
 * If we have decided where to start, let's say 1.
 * then the problem will be:
 *
 * - choose 1 + max{ 3 -> 4 }
 * - not choose 1 + max { 2 -> 3 -> 4 -> 5 }
 *
 * it will become houserobber problem. And for the houserobber, the basic algorithm is
 *
 * f(start, length) = max(
 *     val[start] + f((start + 2) % size, length - 2),  // circle version
 *     f((start + 1) % size, length - 1)
 * )
 *
 * and base case occurs when length < 0, return 0;
 */
int rob_sol1(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    int size = nums.size();
    vector< vector< int > > buf(
                size,
                vector<int>(size+1, -1));
    for (int i = 0; i < size; i++) {
        buf[i][0] = 0;
    }

    int maxMoney = 0;
    // try all starting point
    for (int i = 0; i < size; i++) {
        int bigger = max(nums[i] + maxIncome(buf, nums, size, (i + 2) % size, size-3), // i-1, i, i+1
                       maxIncome(buf, nums, size, (i + 1) % size, size-1)); // i
        if (bigger > maxMoney) {
            maxMoney = bigger;
        }
    }

    return maxMoney;
}
```

The second solution is from bottom to top by dynamic programming.

```c++
/**
 * @brief rob_sol2
 * @param nums
 * @return
 * According to the formula we derived from solution 1, we are able to solve the problem
 * from bottom to top. That's dynamic programming.
 *
 * f(start, length) = max(val[start] + f((start + 2) % size), length-2),
 *                        f((start + 1) % size), length-1)
 *                       )
 *
 * ex> 2 -> 3 -> 2 -> 3  (size: 4)
 *     |------<-------|
 * buf:
 * start\length  0  1  2              3
 *   0           0  2  max(2 + 0, 3)  ...
 *   1           0  3  ...
 *   2           0  2
 *   3           0  3
 */
int rob_sol2(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    if (nums.size() == 2) return max(nums[0], nums[1]); // notice 'size-3' in formula
    int size = nums.size();
    vector< vector< int > > buf(
                size,
                vector<int>(size+1, -1));
    for (int start = 0; start < size; start++) {
        buf[start][0] = 0;
        buf[start][1] = nums[start];
    }

    // !!!: notice render order
    for (int length = 2; length <= size; length++) {
        for (int start = 0; start < size; start++) {
            buf[start][length] = max(nums[start] + buf[(start + 2) % size][length-2],
                                     buf[(start + 1) % size][length-1]);
//            cout << start << ": " << length << " => " << buf[start][length] << endl;
        }
    }

    int maxMoney = 0;
    // try all starting point
    for (int i = 0; i < size; i++) {
        int bigger = max(nums[i] + buf[(i + 2) % size][size-3], // i-1, i, i+1
                       buf[(i + 1) % size][size-1]); // i
        if (bigger > maxMoney) {
            maxMoney = bigger;
        }
    }

    return maxMoney;
}
```

Tricks:

- Start from divide and conquer and derive formula.
- Be careful for the order when solving from bottom to top.

### Jump Game

> You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
>
> Return true if you can reach the last index, or false otherwise.

Start from divide and conquer. 

```bash
# ex> 2, 3, 1, 1, 4
#  i: 0  1  2  3  4
# start from index 0: jump choice 1 ~ val[0]
# =>: 1 + jump in {3, 1, 1, 4}
#     2 + jump in {1, 1, 4}
#     ...
#
# define f as f(index)
# f(index) = true means I can jump to the end from index, f(index) = false otherwise.
```

```c++
/**
 * @brief canJump_sol3
 * @param nums
 * @return
 * In fact, we can refine function to have only one parameter.
 * f(index) = true means I can jump to the end from index, f(index) = false otherwise.
 *
 * ex> 2, 3, 1, 1, 4
 *  i: 0  1  2  3  4
 *
 * In dynamic programming, we start from the last one.
 * f(4) = true;
 * f(3) = f(3+1) | f(3+2) | ... | f(3+maximum)
 * ...
 *
 * T: O(N^2)
 */
bool canJump_sol3(vector<int>& nums) {
    if (nums.size() == 0)  return false;
    if (nums.size() == 1)  return true;
    int size = nums.size();
    vector<bool> buf(size, false);
    int target_index = size - 1;
    for (int i = size - 1; i >= 0; i--) {
        if (i == target_index) {
            buf[i] = true;
        }
        else {
            for (int jump = 1; jump <= nums[i]; jump++) {
                if (buf[i+jump] == true) {
                    buf[i] = true;
                    break;
                }
            }
        }
    }

    return buf[0];
}

```

Tricks:

- Simplify the defination of `buf` and grasp core information.

### Jump Game II

> Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
>
> Each element in the array represents your maximum jump length at that position.
>
> Your goal is to reach the last index in the minimum number of jumps.
>
> You can assume that you can always reach the last index.

We provide two solutions to this problem: dynamic programming and greedy.

- Dynamic Programming Solution

But think of shortest path problem. The key idea is to find the shortest jumps by making locally optimal choices at each index which leads to a globally optimal solution. We are able to define `f` as:

f(index): the shortest step from start to index.

f(index) = min(f(directly connected indices) + 1), where directly connected means indices where I can jump to current index with one jump.

```c++
/**
 * @brief jump_sol1
 * @param nums
 * @return
 * From the solution for jump I, we can enumerate all solutions to the last index and find
 * the one with the least steps.
 *
 * T: O(N^2 * M), where M is maximum length one can jump from an index.
 *
 * But think of shortest path problem. The key idea is to find the shortest jumps by making
 * locally optimal choices at each index which leads to a globally optimal solution. We are
 * able to define f as:
 *
 * f(index): the shortest step from start to index.
 *
 * ex> 2, 3, 1, 1, 4
 *  i: 0  1  2  3  4
 *
 * f(index) = min(f(directly connected indices) + 1);
 * directly connected means indices where I can jump to current index with one jump.
 *
 * T: O(N^2)
 */
int jump_sol1(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int size = nums.size();
    vector<int> shortest_steps(size, INT_MAX);
    shortest_steps[0] = 0;

    for (int cur = 1; cur < size; cur++) {
        int shortest = INT_MAX;
        for (int pre = cur-1; pre >= 0; pre--) {
            // find all directed connected indices and update shortest_steps[cur]
            if (pre + nums[pre] >= cur) {
                if (shortest_steps[pre] + 1 < shortest) {
                    shortest = shortest_steps[pre] + 1;
                }
            }
        }
        shortest_steps[cur] = shortest;
    }

    return shortest_steps[nums.size()-1];
}
```

- Greedy Algorithm

```c++
/**
 * @brief jump_sol2
 * @param nums
 * @return
 * Solution 2 will introduce greedy algorithm. What we are concerned about is which place
 * is able to take me furthest?
 *
 * ex> ... 3, 5, 2, 1, 4, 1, 6, 2, ...
 *         ^  |-----|
 *        cur   jump
 *
 * There are three choices (jump to 5, 2, 1) but where to go?
 * The greedy algorithm tells us to choose the one take me farthest, given that 'end' is
 * not within the range where current jump can reach. Consider the next jump:
 *
 * - if I jump to 5, I can jump to as farthest as 6 with 2 steps (one current and one next).
 *
 *    ... 3, 5, 2, 1, 4, 1, 6, 2, ...
 *        ^  ^              ^
 *       cur next        farthest
 *
 * - if I jump to 1, I can jump to as farthest as 4 with 2 steps
 *
 *    ... 3, 5, 2, 1, 4, 1, 6, 2, ...
 *        ^        ^  ^
 *       cur      next farthest
 *
 * Therefore, I will choose to jump to 5 for current jump decision.
 *
 * T: O(N)
 */
int jump_sol2(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int size = nums.size();
    int cur = 0;
    int target = size - 1;
    // the right end of the range where current jump can reach
    int next_end = cur + nums[cur];
    int jump = 0;
    while (next_end < target) {
        int farthest = 0;
        int best_next = 0;
        for (int next = cur + 1; next <= cur + nums[cur]; next++) {
            // jump range
            if ((next + nums[next]) > farthest) {
                farthest = next + nums[next];
                best_next = next;
            }
        }
        cur = best_next;
        next_end = farthest;
        jump++;
    }

    // last jump
    if (cur < target) jump++;

    return jump;
}
```

Tricks:

- Make locally optimal choices at each step which leads to a globally optimal solution

### Unique Path

> There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., `grid[0][0]`). The robot tries to move to the bottom-right corner (i.e., `grid[m - 1][n - 1]`). The robot can only move either down or right at any point in time.
>
> Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
>
> The test cases are generated so that the answer will be less than or equal to 2 * 10^9.

Define `unique_path[m][n]` as the number of unique path to (m-1, n-1), then `unique[i][j] = unique[i-1][j] (up) + unique[i][j-1] (left)`.

```c++
/**
 * @brief uniquePaths
 * @param m
 * @param n
 * @return
 * Solution 1 is to solve from easy case to complex one.
 *
 * ex> m = 2, n = 3
 *
 * define unique_path[m][n] as the number of unique path to (m-1, n-1).
 * unique[0][0] = 0 ==> unique[m-1][n-1]?
 *
 * unique[i][j] = unique[i-1][j] (up) + unique[i][j-1] (left);
 *
 * T: O(M * N)
 */
int uniquePaths(int m, int n) {
    if ((m == 0) || (n == 0)) return 0;
    vector< vector<int> > unique_path(m, vector<int>(n, 0));
    for (int row = 0; row < m; row++) {
        unique_path[row][0] = 1;
    }
    for (int col = 0; col < n; col++) {
        unique_path[0][col] = 1;
    }

    for (int row = 1; row < m; row++) {
        for (int col = 1; col < n; col++) {
            if ((row - 1) >= 0) {
                unique_path[row][col] += unique_path[row-1][col];
            }
            if ((col - 1) >= 0) {
                unique_path[row][col] += unique_path[row][col-1];
            }
        }
    }

    return unique_path[m-1][n-1];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    EXPECT_EQUAL(uniquePaths(3, 7), 28);
    EXPECT_EQUAL(uniquePaths(3, 2), 3);
}
```

### Jump Game III

> Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to `i + arr[i]` or `i - arr[i]`, check if you can reach to any index with value 0.
>
> Notice that you can not jump outside of the array at any time.

The linear search can be transformed as graph search. Therefore, BFS or DFS.

```c++
/**
 * @brief canReach_sol2
 * @param arr
 * @param start
 * @return
 * Change linear structure of arr to a graph, then DFS or BFS!
 */
bool canReach_sol2(vector<int>& arr, int start) {
    if (arr.size() == 0) return false;
    int size =  arr.size();

    vector<bool> visited(size, false);

    // TODO: start from 'start' with BFS
    queue<int> que;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        visited[cur] = true;

        if (arr[cur] == 0) {
            return true;
        }

        if ((cur - arr[cur] >= 0) && (!visited[cur - arr[cur]])) {
            que.push(cur - arr[cur]);
        }
        if ((cur + arr[cur] < size) && (!visited[cur + arr[cur]])) {
            que.push(cur + arr[cur]);
        }
    }

    return false;
}
```

Tricks:

- Data representation is VERY important in depending algorithm.

### Jump Game IV

> Given an array of integers arr, you are initially positioned at the first index of the array.
>
> In one step you can jump from index i to index:
> 1. i + 1 where: i + 1 < arr.length.
> 2. i - 1 where: i - 1 >= 0.
> 3. j where: arr[i] == arr[j] and i != j.
>
> Return the minimum number of steps to reach the last index of the array.
>
> Notice that you can not jump outside of the array at any time.

The problem is similar to jump game III. To find the minimum steps, BFS is the solution.

```c++
int minJumps(vector<int>& arr) {
    if (arr.size() == 0) return 0;
    int size = arr.size();
    int target = size - 1;
    vector<bool> visited(size, false);

    class QueueNode {
    public:
        int index;
        int step;
        QueueNode(int _index, int _step)
            : index(_index), step(_step) {}
    };
    queue<QueueNode> que;
    que.push(QueueNode(0, 0));
    visited[0] = true;

    // cluster[val] -> {index with val == 'val'}
    unordered_map<int, vector<int> > cluster;
    for (int i = 0; i < size; i++) {
           cluster[arr[i]].push_back(i);
    }

    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();


        if (cur.index == target) {
            return cur.step;
        }

        if ((cur.index - 1 >= 0) && (!visited[cur.index-1])) {
            que.push(QueueNode(cur.index-1, cur.step+1));
            visited[cur.index-1] = true;
        }
        if ((cur.index + 1 < size) && (!visited[cur.index+1])) {
            que.push(QueueNode(cur.index+1, cur.step+1));
            visited[cur.index+1] = true;
        }

        // all brothers and sisters in cluster
        vector<int> brothers = cluster[arr[cur.index]];
        for (int i = 0; i < brothers.size(); i++) {
            if ((brothers[i] != cur.index) && (!visited[brothers[i]])){
                que.push(QueueNode(brothers[i], cur.step+1));
                visited[brothers[i]] = true;
            }
        }
    }

    return -1;
}
```

Tricks:

- To avoid traverse circly, use `visited` to record visited node.
