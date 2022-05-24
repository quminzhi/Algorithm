# Advanced Data Structure

## Data Structure I

### Singly Linked List

Define `v[]` as value array and `ne[]` as next (pointer) array, where node is indexed by `v`'s index.

- init: `head = -1; idx = 0;`, `idx` is used to indicate index of free space.
- head insert: `v[idx] = val; ne[idx] = head; head = idx; idx++;`.
- insert after `k`th node: `v[idx] = val; ne[idx] = ne[k]; ne[k] = idx; idx++;`.
- delete after `k`th node: `ne[k] = ne[ne[k]];`.

**TIP**: `v` is in the order when the node is inserted. `idx` indicates for the next available space for new node. When deleting an node, we do NOT need to move the nodes after that node backward to make use of the space, which is feasible for algorithm problems, but not a good, even a bad, choice for project development.

### Stack

Define `s[]` as a stack, and `top` is top index of stack. Range of `s` is [0, top].

- init: `top = -1;`.
- push: `s[++top] = val;`.
- pop: `top--;`.
- empty: `top < 0;` (exclusive).

### Queue

Define `q[]` as a queue, and `front` and `tail` is front index and tail index of `q`.

- init: `front = 0; tail = -1;`, why -1? we want to include tail in our `q`, i.e. range of `q` is [front, tail].
- push: `q[++tail] = val;`.
- pop: `front++;`.
- empty: `front > tail` (refer to init).

### Monotonic Stack

A monotonic stack is a stack whose elements are monotonically increasing or decreasing.

We will introduce it with a simple problem:

> Given an array `a[]`, return the closest index whose value is less than `a[i]`. If such index does not exist, return -1.
>
> ex:
> a[]   =  3,  4,  2,  5,  7
> res[] = -1,  3, -1,  2,  5

Analysis: say, given `a[2] >= a[3]`, and we are going to find the closest index `a[i]` whose value is less than `a[i]`, `a[2]` must NOT be the answer. So if `a[2] >= a[3]` when dealing with `a[3]`, we can pop `a[2]` from the stack.

So, all candidates are reserved in the stack and arranged in ascending order. In this way, we can get a monotonic stack (ascending).

```c++
vector<int> closestIndex(vector<int>& nums) {
    // init a stack
    int N_MAX = 5000;
    vector<int> s(N_MAX, 0);
    int top = -1;

    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
        while (top >= 0 && s[top] >= nums[i]) {
            top--;
        }
        if (top >= 0) {
            res.push_back(s[top]);
        } else {
            res.push_back(-1);
        }
        s[++top] = nums[i];
    }

    return res;
}
```

### Monotonic Queue

A monotonic Queue is a data structure the elements from the front to the end is strictly either increasing or decreasing.

> You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
>
> Return the max sliding window.

The basic idea is to use a queue to represent sliding window. We need to go from 0 to `n` and each time we iterate all elements in the queue to get maximum number. The time complexity goes to be `O(nk)`.

To optimize it, let's analyze the elements in the queue and see if we can do something on that.

```text
ex>  1  3  -1  -3  5  4  6  7  (k = 3)
                   ^     ^
                front    end

One observation on given window is:
    1. 6 comes after 4 and 5.
    2. 6 is greater than 4 or 5.
So, if 6 will live longer than 4 and 5 and if it exists, neither 4 nor 5 could be the answer. Thereby, we can dump 4 and 5 out of our queue.
```

In this way, our queue is going to be a monotonic queue (non-ascending). Since it is non-ascending, the maximum is `q[front]`.

To check boundary, we push index rather than val of `nums` in `q`.

```c++
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int N_MAX = 1e5 + 10;
    int q[N_MAX], front = 0, tail = -1;   // index not val, [front, tail]
    vector<int> res;

    // slide window [i - k + 1, i]
    for (int i = 0; i < nums.size(); i++) {
        // insert: find the place for nums[i]
        while (front <= tail && nums[q[tail]] <= nums[i] ) {
            tail--;
        }
        q[++tail] = i;
        // check if front is out of the sliding window
        if (q[front] < i - k + 1) {
            front++;
        }
        if (i - k + 1 >= 0) {
            // if slide window completes
            res.push_back(nums[q[front]]);
        }
    }

    return res;
}
```

### KMP

> Given two strings, `s` and pattern `sub`, find all matching index for `sub` in `s`. Return the first index of matching location.

Let's see the problem start from the beginning. (string is 1-based in following discussion)

```text
ex>      s =  a  b  a  b  a  b
   pattern =  a  b  a  b
              ^        ^
              1     ^        ^
                    3

There are two matching points.
```

By abstracting the problem, we got:

```text

      s = oooo1111xoooooooooo
                  ^
                  i: points to the first char that match failed in s string.
pattern =     1111xoooo        (len = 9)
                 ^
                 j: points to the last char that matches in pattern string.

where, '1' means matching chars and 'x' means the first not matching char with index `i`, and 'o' means wait to be determined.
```

So, there are some points should be noted:

- we are focusing on `i` in origin string `s`, which points to the first char that match failed.
- `j` is the size of matching chars in `pattern`. And j happens to point to the last matching char in pattern string, i.e. `pattern[1..j] == s[i-j..i-1]`.
- Given `j == i - 1`, if we subtract `j` by `m`, it looks like we move pattern string forward by m steps. See the diagram below.

```text

      s = oooo1111xoooooooooo
                  ^
                  i
pattern =     1111xoooo    (there are 4 common chars)
                 ^
                 j == i - 1

Move pattern forward by 2.

pattern =       11xoooooo  (there are only 2 common chars left)
                 ^
                 j == i - 1
```

- We need to decide the maximum steps pattern can move forward at each step by `next[j]`. One observation is that we can get maximum interest by move `len` step, where `len` is the length of prefix and postfix of matching string `pattern[1..j]`.

```text
pattern: a  b  c  a  b
  index: 1  2  3  4  5
 next[]: 0  0  0  1  2

when `j == 1`, matching string is `pattern[1..1]`, prefix and postfix can not be the same char, so next[1] = 0.
when `j == 2`, matching string is `pattern[1..1]`, 'prefix = a' != 'postfix = b', so next[2] = 0.
...
when `j == 4`, 'prefix = ab' != 'postfix = ca', but 'prefix = a' == 'postfix = a', so next[4] = 1.
when `j == 5`, 'prefix = ab' == 'postfix = ba', so next[5] = 2. (for moving when match succeeds)

**Note: next[4] = 1 means: when substr = 'abca' matches, and 'b' (pattern[5]) does not match, the most length of matching substring should be 1, since we can move the first `a` to the last `a`.

the meaning of j: indicates how many characters match (pattern[1..j] matches).
```

- How to obtain `ne` (next)?

We have a wise method. Our algorithm above is to find matching prefix in pattern for `s[a..b]` indicated by `i` and `j`, since `a = i - j + 1`

```text
 Note: b - a + 1 = j (j != b, they are on the different strings)
       b = i - 1
       a = i - j + 1 (1-based)  <=== HERE
       a = i - j + 1 - 1 = i - j (0-based)
```

if the original string `s` becomes pattern string `p`, it happens to have the same effect of calculating the previous matching index where `prefix == postfix` in `substring[1..i-1]`, which is what `ne[]` means.

Why we compare pattern string and pattern string being shifted 1 step? How it gets `ne[]`?

Let's focus on the first pattern string (without shift). We want to find the prefix and postfix of `patter[1..i]`.

```text
               <-------->
ex>  pattern = oo 11111 x ooo
               1  ^   ^ ^   m
                  a   b i
     pattern =    11111 x ooooo
  (shifted by 1)  1   ^       m
                      j

when p[j+1] == p[i], j++

               <-------->  p[1..i]
ex>  pattern = oo 11111 1 ooo
               1  ^   ^ ^   m
                  a   b i
                  <-----> p[1..i]'s postfix

     pattern =    11111 1 ooooo
   (shifted by 1) 1     ^     m
                        j  <== after j++, but not i++
                  <-----> p[1..i]'s prefix same as [p..i]'s postfix

where postfix == prefix, and next[i] = j
```

```c++
vector<int> kmp(string s, string pattern) {
    // transform to 1-based string
    string ss = string("0") + s;
    string pp = string("0") + pattern;

    // build next
    vector<int> ne(pp.size(), 0);
    // why start from 2? since we are focusing on p[1..i], when i == 1, p[1..1] has only 1 element, its next is 0 by definition (postfix and prefix cannot be the same element).
    // j always points to the possible right boundary of prefix (p[1..j]).
    for (int i = 2, j = 0; i <= pattern.size(); i++) {
        while (j && pp[i] != pp[j + 1]) {
            j = ne[j];
        }
        if (pp[i] == pp[j + 1]) {
            j++;
        }
        // update ne[j]
        ne[i] = j;
    }

    vector<int> res;
    // match
    for (int i = 1, j = 0; i <= s.size(); i++) {
        while (j > 0 && ss[i] != pp[j + 1]) {
            j = ne[j];   // move forward
        }
        if (ss[i] == pp[j + 1]) {
            j++;
        }
        if (j == pattern.size()) {
            res.push_back(i - j); // the index in ss not pp, assuming answer is 0-based
            j = ne[j];   // move forward for next possible match
        }
    }

    return res;
}
```

#### str str

> Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
>
> What should we return when needle is an empty string? This is a great question to ask during an interview.

This is a pattern-matching problem which is typically solved by KMP algorithm.

The core of KMP algorithm are:

- focusing on substring that matches, the best movement we can do when `s[i] != p[j+1]` is to move p to its 'postfix' of matched substring.

```text
s:  xxxxx 11111 ? xxxxx
          a   b i
p:        11111 ? xx
          1   j

ex> 
s:  xxxxx cdccd ? xxxxx
          a   b i
p:        cdccd ? xx
          1   j
where 'cd...' is the prefix in substring p[1..j], and '...cd' is the postfix in substring p[1..j]. The best movement is to move prefix to postfix place.
```

- `ne[]` (`next[]` is in standard libc) for pattern string: indicate where to move. Say pattern string is `cdccdcab`.

```text
p:    c d c c d c a b
idx:  1 2 3 4 5 6 7 8
ne[]: 0 0 1 1 2 1 0 0

when i == 5, [c d] c [c d]
            prefix  postfix
```

`ne[j]` indicates the max length(or last index of prefix, that's why 1-based index) of prefix and postfix in matched substring when p[j+1] fails to match (matched substring is p[1..j]).

```c++
int strStr(string haystack, string needle) {
    string ss = string("0") + haystack;
    string pp = string("0") + needle;
    // initialize ne[]:
    vector<int> ne(pp.size(), 0);   // 1-based
    for (int i = 2, j = 0; i < pp.size(); i++) {
        while (j && pp[i] != pp[j + 1]) {
            j = ne[j];
        }
        if (pp[i] == pp[j + 1]) {
            j++;
        }
        ne[i] = j;
    }
    // match
    for (int i = 1, j = 0; i < ss.size(); i++) {
        while (j && ss[i] != pp[j + 1]) {
            j = ne[j];
        }
        if (ss[i] == pp[j + 1]){
            j++;
        }
        if (j == needle.size()) {
            return i - j;  // problem is zero-based
            j = ne[j];
        }
    }

    return -1;
}
```

#### Shortest Palindrome

> You are given a string s. You can convert s to a palindrome by adding characters in front of it.
>
> Return the shortest palindrome you can find by performing this transformation.

The basic idea is that such palindrome can be found by finding the longest palindrome substring, say `subPalindrome`. Then `s` will be partitioned into two parts, `subPalindrome` and `rest`. We just need to add the reverse of `rest` to the head to form a bigger palindrome and this palindrome must be the shortest palindrome we can get by adding characters in front of it.

```text
How to check if the sting is palindrome? s == reverse(s)

ex>  s = a b a b c
   rev = c b a b a

1st: s[0..4] == rev[0..4]?  NO
2nd: s[0..3] == rev[1..4]?  NO
3rd: s[0..2] == rev[2..4]?..YES

So we got the max length of subPalindrome is 3.
```

```c++
string shortestPalindrome(string s) {
    int n = s.size();
    string rev(s);
    reverse(rev.begin(), rev.end());
    for (int i = 0; i < n; i++) {
        if (s.substr(0, n - i) == rev.substr(i))
            return rev.substr(0, i) + s;
    }
    return "";
}
```

But, str comparison takes O(n) time and the algorithm costs O(n^2) time in total.

Is there a good way to find the longest palindrome substring from the beginning?

```text
Continue with the last example:
    s = a b a b c
    rev = c b a b a

The process is similar to calculate ne[i] (KMP), i.e. the max length of prefix and postfix (same).

So we can construct a string: s + rev, and find ne[i].

*But the solution does not work for s = aaaa, so we need add a delimiter between s and rev, say #.
```

so, `shortest palindrome = reverse(rest) + s (subPalindrome + rest)`.

```c++
string shortestPalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    string pp = string("0") + s + "#" + rev;   // add 0 for 1-based
    vector<int> ne(pp.size(), 0);
    for (int i = 2, j = 0; i < pp.size(); i++) {
        while (j && pp[i] != pp[j + 1]) j = ne[j];
        if (pp[i] == pp[j + 1]) {
            j++;
        }
        ne[i] = j;
    }
    
    int lenOfSubPalindrome = ne[pp.size() - 1];
    // shortest palindrome = reverse(rest) + s (subpalindrome + rest)
    string revRest = s.substr(lenOfSubPalindrome);
    reverse(revRest.begin(), revRest.end());
    
    return revRest + s;
}
```

### Trie Tree

Trie tree is a tree-like structure, how to use array to simulate tree structure? Array of nodes, where each node is represented with `child[][]` and `v[]`. `idx` is used to indicate new allocated space in the array.

Define `child[N][26]` to indicate the index of child of current node, and `v[N]` as the value of current node.

```c++
#define N 100010

class Trie {
   private:
    int child[N][26];
    int v[N];
    int idx = 0;

   public:
    void insert(string str);
    int query(string str);
};

void Trie::insert(string str) {
    int p = 0;
    for (int i = 0; i < str.size(); i++) {   // the last char of string is '\0'
        int ch = str[i] - 'a';               // map ch to [0, 25]
        if (!child[p][ch]) {
            child[p][ch] = ++idx;   // if not exist, create node for char
        }
        p = child[p][ch];
    }
    v[p]++;   // label the last char
}

int Trie::query(string str) {
    int p = 0;
    for (int i = 0; i < str.size(); i++) {
        int ch = str[i] - 'a';
        if (!child[p][ch]) return 0;
        p = child[p][ch];
    }

    return v[p];
}
```

### Disjoint Set

 A disjoint-set data structure, also called a union–find data structure or merge–find set, is a data structure that stores a collection of disjoint (non-overlapping) sets. It provides operations for adding new sets, merging sets (replacing them by their union), and finding a representative member of a set. The last operation makes it possible to find out efficiently if any two elements are in the same or different sets.

The key problem is how to represent which set a element belongs to.

- set label: we use root of a tree to represent a set, all nodes in the tree belong to this set. (assuming the parent of root is root itself)
- joint: point the root of a set to the root of another set.
- query: find root. O(log(h)), where `h` is the height of the tree.
- optimization for query: since the time complexity of query operation is proportional to the height of the tree, we will collapse it into a tree as low as possible (path compression).

Notice that we operation on unique identity of each element (index in general, not value).

```c++
class DisjointSet {
   private:
    int p[N];

   public:
    DisjointSet(int n);  // @n: number of unique elements
    int find(int x);   // return set label of val x
    void merge(int x, int y);
};

DisjointSet::DisjointSet(int n) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
}

int DisjointSet::find(int x) {
    if (p[x] != x) {   // if not root
        p[x] = find(p[x]);   // path compression
    }
    return p[x];
}

void DisjointSet::merge(int x, int y) {
    p[find(x)] = find(y);
}
```

### String Hash HI

The basic idea is to transform a string to a `len(s)` p-base number.

```text
ex>   s = "abaabd"    =>    p based
   hash = p^5 * map['a'] + p^4 * map['b'] + p^3 * map['a'] + ... + p^0 * map['d'].

for convenience, we use ASCII value as a char map.
```

where `map` is a mapping which maps a character to a specific number (the only requirement is mapped number should not be 0).

Define hash length `N = 1e5 + 10` and `P = 131 or 13331` (nearly no collision or conflict).

```c++
#include <iostream>
#include <cstring>
using namespace std;

typedef unsigned long long ULL;

const int N = 1e5 + 10, P = 131, nil = -1;
ULL h[N], p[N];

ULL find(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    
    memset(h, nil, sizeof h);
    // cache
    p[0] = 1;  // p^0 = 1
    h[0] = 0;  
    for (int i = 1; i <= n; i++) {
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + s[i - 1];   // s[i] cannot be 0
    }
    
    while (m--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if (find(l1, r1) == find(l2, r2)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    
    return 0;
}
```

## Data Structure II

### Segment Tree

The basic idea of segment tree is rearrange a segment into a tree shape where each node represents a smaller segment which includes some important info about this segment (e.g. max, sum, prefix sum, postfix sum, max sum of sub array within the segment).

There are two kinds: 1. single point update (basic), 2. range update (lazy label).

#### Max Segment Tree

For convenience: we treat input as 1-based data. The segment tree will be represented with a 1-d array (location is indexed with indices).

```c++
const int N = 4 * 1e5;   // 4 times of input size (n)
struct Node {
    int l, r;
    int vMax;   // property information for the segment
} tr[N];

// left child:  tr[i << 1] == tr[i * 2]
// right child: tr[i << 1 | 1] == tr[i * 2 + 1]
// parent:      tr[i >> 1] == tr[i / 2] (round down)
```

- Build Tree

We divide a segment `[l, r]` into two parts: left part `[l, mid]` and `[mid + 1, r]` (mid is included in the left part).

```c++
/* build tree: segment division, 1-based for u and l */
void build(int u, int l, int r) {
    tr[u].l == l;
    tr[u].r == r;
    if (l == r) return;   // min segment
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
};
```

- Query

Say we want to find the max in `[L, R]`. There are two cases:

- if `[tr[i].l, tr[i].r]` is within `[L, R]`, return `tr[i].vMax`
- if `[tr[i].l, tr[i].r] and [L, R] != null set` (have intersection). Calculate the mid of the segment `tr[i]`.

```text
case 1:
    L                           R
    o---------------------------o
        o-------------------o
     tr[i].l          tr[i].r

case 2: (mid as pivot)
        L            mid            R
        o-------------o-------------o

    o-------------------o
    tr[i].l          tr[i].r
o-------------o
tr[i].l     tr[i].r

case 3:
    L            mid            R
    o-------------o-------------o

                o-------------------o
                tr[i].l          tr[i].r
                        o-------------o
                        tr[i].l     tr[i].r

case 4:
    L            mid            R
    o-------------o-------------o
        o-------------------o
        tr[i].l          tr[i].r
      o---------o
    tr[i].l  tr[i].r
                    o---------o
                  tr[i].l  tr[i].r
```

```text
From the perspective of tr[i]:
               mid
      o---------o---------o
    tr[i].l          tr[i].r
 o----------------o
 L                R

if R > mid, [L, R] and [mid + 1, tr[i].r] has non-empty intersection.

               mid
      o---------o---------o
    tr[i].l          tr[i].r
            o----------------o
            L                R

if L <= mid, [L, R] and [tr[i].l, mid] has non-empty intersection.
```

```c++
/* query property of segment [l, r] */
int query(int u, int l, int r) {
    // case 1: include
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].vMax;
    int mid = tr[u].l + tr[u].r >> 1;
    int winner = -inf;
    if (l <= mid) winner = max(winner, query(u << 1, l, r));   // left intersection exists
    if (r > mid) winner = max(winner, query(u << 1 | 1, l, r));   // right intersection exists
    return winner; 
};
```

- Modify

```c++
/* calculate parents property info from children's property info */
void pushup(int u) {   // indexed by indices (int ~= Node*)
    tr[u].vMax = max(tr[u << 1].vMax, tr[u << 1 | 1].vMax);
};

void modify(int u, int idx, int val) {
    // find leaf node of modified element
    if (tr[u].l == idx && tr[u].r == idx) tr[u].vMax = val;
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (idx <= mid) modify(u << 1, idx, val);
        else modify(u << 1 | 1, idx, val);
        // backtracking: update parent
        pushup(u);
    }
};
```

#### Max Sum of Subarray

Given two children segments, how to calculate the max sum of sub array of parent segment.

```text
parent:
    o-------------o-------------o
                 mid
children:
    o-------------oo------------o
       left            right
```

The max sum of subarray of parent segment has three possibles:

- max subarray of left segment
- max subarray of right segment
- max postfix of left + max prefix of right (combined)

The new generated problem is how to maintain prefix and postfix of each segment?

- `prefix of parent  = max(prefix of left, sum of left + prefix of right)`
- `postfix of parent = max(postfix of right, sum of right + postfix of right)`

The next problem is how to maintain sum of each segment? Obviously, `sum of parent = sum of left + sum of right`.

```c++
class MaxSubarray {
   private:
    struct Node {
        int l, r;
        int prefix, postfix, sum, vMax;
    };

   public:
    MaxSubarray(vector<int> v) {
        const int n = v.size();
        build(1, 1, n);
        for (int i = 1; i <= n; i++) {
            modify(1, i, v[i - 1]);
        }
    }

    void build(int u, int l, int r) {
        tr[u].l = l;
        tr[u].r = r;
        if (l == r) return;
        int mid = tr[u].l + tr[u].r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }

    /* update regulation */
    void pushup(struct Node& p, struct Node& left, struct Node& right) {
        p.sum = left.sum + right.sum;
        p.prefix = max(left.prefix, left.sum + right.prefix);
        p.postfix = max(right.postfix, right.sum + left.postfix);
        // three possibles
        p.vMax = max(left.vMax, right.vMax);                 // left or right
        p.vMax = max(p.vMax, left.postfix + right.prefix);   // or combination of postfix and prefix
    }

    void pushup(int u) { pushup(tr[u], tr[u << 1], tr[u << 1 | 1]); }

    void modify(int u, int idx, int val) {
        if (tr[u].l == tr[u].r && tr[u].l == idx) {
            tr[u].postfix = tr[u].prefix = tr[u].sum = tr[u].vMax = val;
        } else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (idx <= mid)
                modify(u << 1, idx, val);
            else
                modify(u << 1 | 1, idx, val);
            pushup(u);
        }
    }

    // return the segment including ans
    Node query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u];
        int mid = tr[u].l + tr[u].r >> 1;
        // only left
        if (r <= mid) return query(u << 1, l, r);
        // only right
        if (l > mid) return query(u << 1 | 1, l, r);
        // include left and right: three cases solved with pushup
        struct Node left = query(u << 1, l, r);
        struct Node right = query(u << 1 | 1, l, r);
        struct Node res;
        pushup(res, left, right);   // update res with left and right answer
        return res;
    }

   private:
    struct Node tr[1010];
};
```

#### Range Greatest Common Divisor

One property of greatest common divisor is: `gcd(a1, a2, ..., an) = gcd(a1 - 0, a2 - a1, ..., an - an-1)`.

```text
Proof: gcd(left) <= gcd(right)
let d be the gcd(left). For the first two terms on the left,
    a1 mod d == 0 and a2 mod d == 0
So, for the first two terms on the right,
    (a1 - 0) mod d == 0 and  (a2 - a1) mod d == 0
With the same logic, we can proof all terms have such property. Thus, d must be a common divisor of right. So gcd(left) <= gcd(right).

Proof: gcd(left) >= gcd(right)
let d be the gcd(right). For the first two terms on the right, we have
    (a1 - 0) mod d == 0 and  (a2 - a1) mod d == 0
So, for the first two terms on the left,
    a1 mod d == 0 and ((a2 - a1) + a1) mod d == a2 mod d == 0
d must be a common divisor of left. So, gcd(left) >= gcd(right)
```

So, gcd of an array `arr` is equal to gcd of difference array `diff` of `arr`. If we want to calculate gcd of `arr[L, R]`,

```text
gcd(aL, aL+1, ..., aR) = gcd(aL, aL+1 - aL, aL+2 - aL+1, ..., aR - aR-1)
                       = gcd(aL, bL+1, bL+2, ..., bR).

where b is diff array, a is original array. 'aL' == 'prefixSum[L+1]'.
```

With this property, we will save difference of two adjacent numbers in the segment (refer to the update of difference) to achieve range update. In this case, to query `a[i]` is to query `prefixSum(b[i+1])`.

This is called **difference segment tree** (range change and single point query).

Side note: beautiful gcd code:

```c++
/* 
    if b == 0, return a
    else a = b, b = a % b, and solve recursively
 */
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
```

The complete code:

```c++
/*
    1. one property: gcd(a1, a2, ..., an) = gcd(a1 - 0, a2 - a1, ..., an - an-1)
    i.e. gcd of original sequence is gcd of difference sequence

    2. maintain elements in segment tree in the form of difference sequence.
        - modify(u, l, r, add) -> modify(u, l, add) and modify(u, r + 1, -add) if r + 1 <= n
        - query(u, l, r) -> gcd(a[l], diff[l+1], ..., diff[r]) == gcd(a[l], gcd(diff[l+1], ..., diff[r]))
        where, a[l] = prefixSum[l + 1]
 */
class GCDTree {
   private:
    struct Node {
        int l, r;
        int sum, divisor;   // maintain two property
    };

   public:
    GCDTree(const vector<int>& v) {
        n = v.size();
        // 0-based to 1-based
        vector<int> vv(v.begin(), v.end());
        vv.insert(vv.begin(), 0);
        build(vv, 1, 1, n);
    }

    void pushup(struct Node& p, struct Node& left, struct Node& right) {
        p.sum = left.sum + right.sum;
        p.divisor = gcd(left.divisor, right.divisor);
    }

    void pushup(int u) { pushup(tr[u], tr[u << 1], tr[u << 1 | 1]); }

    // segment: diff sequence
    void build(const vector<int>& v, int u, int l, int r) {
        tr[u].l = l;
        tr[u].r = r;
        if (l == r) {
            // leaf
            int diff = v[l] - v[l - 1];
            tr[u].divisor = diff;
            tr[u].sum = diff;
        } else {
            int mid = l + r >> 1;
            build(v, u << 1, l, mid);
            build(v, u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    // modify: change of value (DELTA) on [idx, idx], not replace with 'add'
    void modify(int u, int idx, int add) {
        if (tr[u].l == tr[u].r && tr[u].l == idx) {
            int t = tr[u].divisor + add;
            tr[u].divisor = tr[u].sum = t;
        } else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (idx <= mid)
                modify(u << 1, idx, add);
            else
                modify(u << 1 | 1, idx, add);
            pushup(u);
        }
    }

    // range modify
    void modify(int u, int l, int r, int add) {
        // update diff sequence
        modify(u, l, add);
        if (r + 1 <= n) modify(u, r + 1, -add);
    }

    struct Node query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u];
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) {
            // ans in left segment (known)
            return query(u << 1, l, r);
        } else if (l > mid) {
            // ans in right segment (known)
            return query(u << 1 | 1, l, r);
        } else {
            // ans need to be calculated by pushup
            struct Node left = query(u << 1, l, r);
            struct Node right = query(u << 1 | 1, l, r);
            struct Node res;
            pushup(res, left, right);
            return res;
        }
    }

    // decorator:
    // gcd(a[l], gcd(diff[l+1], ..., diff[r]))
    int query(int l, int r) {
        auto left = query(1, 1, l);   // for a[l]
        if (l + 1 > r) return left.sum;   // no diff sequence after a[l]
        auto right = query(1, l + 1, r); // gcd of diff[l+1 ... r]
        return abs(gcd(left.sum, right.divisor));
    }

   private:
    struct Node tr[1010];   // 4 * n
    int n;

    int gcd(int a, int b) {
        return b ? gcd(b, a % b) : a;
    }
};
```