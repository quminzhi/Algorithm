# Greedy

## Intervals

### Select Point on Intervals

> Given n intervals `[a, b]`, select points as few as possible so that each interval includes at least 1 point.

For example,

```text
------
   -o--------
    ----
            ----o----

We need select at least two points.
```

The basic idea is to select the point that is included in different intervals as many as possible. How to find a best point on a given interval? best here means it is covered by intervals as many as possible.

The algorithm is:

- sort all intervals by right end.
- if the left point of the next interval is less than the right point of start interval (`next.left < start.right`), pass since we can find a point on overlapping space.
- if not, next interval will be a new start interval and repeat step 2.

Note all points will be selected on the start intervals.

```c++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;

struct Interval {
    int left;
    int right;
    bool operator<(const struct Interval& rhs) const {
        return right < rhs.right;
    }
} interval[N];

int main() {
    int n;
    cin >> n;
    
    if (n == 0) return 0;
    
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        interval[i].left = l;
        interval[i].right = r;
    }
    
    sort(interval, interval + n);
    
    int res = 1;
    int start = 0;
    for (int i = 1; i < n; i++) {
        if (interval[i].left <= interval[start].right) continue;
        start = i;
        res++;
    }
    
    cout << res << endl;
    
    return 0;
}
```

### Max Non-overlapping Intervals

> Given n intervals, return the maximum number of non-overlapping intervals (including endpoint).

The idea is same as the one above:

- sort all intervals by right end. Why? Because we choose the right end as short as possible to get intervals as many as possible.
- if `next.left <= start.right`, next is not a valid interval when selecting the first interval since they are overlapping.
- if `next.left > start.right`, `start = next` and repeat step 2.

### Group Intervals

> Given n intervals, arrange intervals into different groups so that there is no overlapping in each group. Return the minimum number of group it could be.

The corresponding problem of such model is **Meeting Rooms II**.

> Given an array of meeting time intervals intervals where `intervals[i] = [starti, endi]`, return the minimum number of conference rooms required.

The basic algorithm is:

- sort all intervals by left end.
- we represent each group with the maximum right end of the intervals within the group (min heap).
- if `next.left >= min(groups)`, next will be grouped into that group and update the maximum right end of that group.

```c++
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100010;

struct Interval {
    int left, right;
    bool operator<(const struct Interval& rhs) const {
        return left < rhs.left;
    }
}intervals[N];

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].left >> intervals[i].right;
    }
    
    sort(intervals, intervals + n);
    
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(intervals[0].right);
    for (int i = 1; i < n; i++) {
        int right = pq.top();
        if (intervals[i].left <= right) {
            pq.push(intervals[i].right);
        } else {
            pq.pop();
            pq.push(intervals[i].right);
        }
    }
    
    cout << pq.size() << endl;
    
    return 0;
}
```

### Cover Interval

> Given n intervals, select as less as possible intervals from them to cover a given interval.

The algorithm is as follows:

- sort all intervals by left end.
- find the one with the maximum right from those intervals cover the point start (left of given interval).
- update new start as right chosen from step 2. (a new subproblem)

```text
ex>  target: o----------------------
           start
         -----------
           ------
            ----------
for intervals covering start point (whose left < start), we'd better to choose the one with maximum right end, meaning covering as long as possible (greedily).
```

```c++
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

const int N = 100010;
const int inf = 1e9;

struct Interval {
    int l, r;
    bool operator<(const struct Interval& rhs) const {
        return l < rhs.l;
    }
} intervals[N];

int main() {
    int left, right;
    cin >> left >> right;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].l >> intervals[i].r;
    }
    
    sort(intervals, intervals + n);
    
    int start = left;   // assume start is non-covered point
    int res = 0;
    while (start <= right) {
        int maxRight = -inf;
        for (int i = 0; i < n; i++) {
            if (intervals[i].l <= start) maxRight = max(maxRight, intervals[i].r);
            else 
                break;
        }
        if (maxRight < start) {
            cout << -1 << endl;
            return 0;
        }
        cout << maxRight << endl;
        start = maxRight + 1;
        res++;
    }
    
    cout << res << endl;
    
    return 0;
}
```

### Merge Stones

> Given some stacks of stone, each stack has a weight, we want to merge them into one stack and we can merge two stacks each time. The cost for merging is the weight of two stacks. Return the minimum total cost.

This is a kind of Huffman problem. The basic algorithm is:

- select two minimum stones and merge them.
- push the merged stack into the priority queue.
- repeat until there is only one stack.

```c++

```

## Problems

### Remove Duplicate Letters

> Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

The the idea is based on the fact that for two strings with the same length, strings are compared from left to right, and which is greater depends on the comparison between the first two unequal characters in the two strings, ex> `s1 = axxxx` and `s2 = bxxxx`, `s1 < s2`.

Note: lexicographical order implies monolithic property. But we have a constraint here in finding the smallest sub-sequence, every character has to appear in the resulting string for one and only one time.

The algorithm is:

```text
for ch in s:
    if `s[i]` is in the result, skip it.
    if `s[i] < s[i-1]` and `s[i-1]` occurs after `i` (each character should be in the final result exactly once), then `s[i-1]` can be removed. (repeat until s[i] is the largest one in the stack - monotonic)
```

```text
s = "cbacdcbc"

stack = c
      = b (pop c)
      = a (pop a)
      = a c
      = a c d
      = a c d (c) skip
      = a c d b (although d > b, this is the last d, it should be kept)
      = a c d b (c) skip

So, the final result is "acdb"

s = "cbacdcbcd"

stack = c
      = b (pop c)
      = a (pop a)
      = a c
      = a c d
      = a c d (c) skip
      = a (c d) b (pop c and d, since there are c and d occur after b, c and d in the stack is not the best place).
      = a b c
      = a b c d

So, the final result is "abcd"
```

```c++
string removeDuplicateLetters(string s) {
    stack<char> buff;
    unordered_set<char> mm;    // if a char is in the buff
    vector<int> left(26, 0);   // if a char occurs after current one
    for (auto ch : s) {
        left[ch - 'a']++;
    }
    
    for (auto ch : s) {
        left[ch - 'a']--;
        if (mm.find(ch) != mm.end()) continue;
        while (!buff.empty() && left[buff.top() - 'a'] > 0 && ch < buff.top()) {
            mm.erase(buff.top());
            buff.pop();
        }
        mm.insert(ch);
        buff.push(ch);
    }
    
    string res;
    while (!buff.empty()) {
        res.push_back(buff.top());
        buff.pop();
    }
    reverse(res.begin(), res.end());
    
    return res;
}
```

### Minimum Swaps to Make Strings Equal

> You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only. Your task is to make these two strings equal to each other. You can swap any two characters that belong to different strings, which means: swap `s1[i] and s2[j]`.
>
> Return the minimum number of swaps required to make s1 and s2 equal, or return -1 if it is impossible to do so.

```text
ex> s1 = "xy", s2 = "yx"

1. swap s1[0] and s2[1] => s1 = "xx"  s2 = "yy"
2. swap s1[1] and s2[0] => s1 = "xy"  s2 = "xy"

we need at least 2 swaps to make s1 and s2 equal.
```

```c++

```

### Valid Triangle Number

> Given an integer array `nums`, return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

sort to boost finding target number.

```c++
class Solution {
public:
    // 1. sort
    // 2. from left to right, find two pair of unique numbers, find the maximum length of third length.
    // since the sequence is ordered, we just need to find the index of first number greater than or equal to max length
    // 3. add triangle to solution
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                int maxLen = nums[i] + nums[j];
                int k = lessThan(nums, j + 1, n - 1, maxLen);
                if (k == j + 1 && nums[k] >= maxLen) continue;   // not found
                res += k - j;
            }
        }
        
        return res;
    }
    
private:
    int lessThan(vector<int>& nums, int l, int r, int target) {
        while (l < r) {
            int mid = l + (r - l + 1 >> 1);
            if (nums[mid] >= target) {
                r = mid - 1;
            } else {
                l = mid;
            }
        }        
        return l;
    }    
};
```
