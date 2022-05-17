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
