# ACWing Data Structure

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

### str str

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

### Shortest Palindrome

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

## Data Structure II

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