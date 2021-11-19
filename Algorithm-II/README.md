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
