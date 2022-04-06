# Data Structure I

## Singly Linked List

Since `new` in c++ is time-consuming, we will discuss how to simulate a singly linked list with an array.

```c++
class Node {
   public:
    int val;
    Node *next;
};
```

To avoid allocating memory dynamically (in heap), we define 'singly linked list' (actually an array) as follows:

- `head` is an int pointing to the index of head.
- `size` is the end of the array and happens to be the size of array.
- `v` array: `v[i]` stores the value on index `i`.
- `next` array: `next[i]` stores the next index of 'node'. Specially, next is `-1` for the node where next is `nullptr`.

So the basic implementation is:

- declaration (.hpp)

```c++
class SinglyLinkedList {
   public:
    SinglyLinkedList();

    void HeadInsert(int val);
    void Insert(int val, int idx);    // idx refers to the ith node in a linked list
    void InsertAbs(int val, int i);   // i here refers to the index of array
    int HeadDelete();
    int DeleteAbs(int i);   // do not care about freeing space

    int Top();
    int Size();
    bool IsEmpty();
    void Traverse();

    static const int INIT_SIZE = 100;
    int head;
    int size;
    int vals[INIT_SIZE];
    int next[INIT_SIZE];   // index by an array index not a pointer
};
```

- implementation (.cpp)

```c++
SinglyLinkedList::SinglyLinkedList() {
    head = -1;   // nullptr
    size = 0;
}

void SinglyLinkedList::HeadInsert(int val) {
    // new 'node' will be assigned to the end of the array
    vals[size] = val;
    next[size] = head;
    head = size;
    size++;
}

/**
 * @brief
 *
 * ex>
 * val   1   2   5   8   9   7
 * next  2   3   1   6   -1  5
 *               ^       ^      ^
 *             head     tail    size
 *
 * @param val
 * @param idx: is not necessarily on ith index of array, it is actually an pointer for
 * array.
 */
void SinglyLinkedList::Insert(int val, int idx) {
    assert(idx >= 0 && idx < size);
    if (idx == 0) {
        HeadInsert(val);
    } else {
        int pre = -1;
        int ptr = head;
        for (int i = 0; i < idx && next[ptr] != -1; i++, ptr = next[ptr]) {
            pre = ptr;
        }
        vals[size] = val;
        next[size] = ptr;
        next[pre] = size;
        size++;
    }
}

/**
 * @brief insert after ith node
 *
 * @param val
 * @param i: refers to the index of array
 */
void SinglyLinkedList::InsertAbs(int val, int i) {
    vals[size] = val;
    next[size] = next[i];
    next[i] = size;
    size++;
}

/**
 * @brief time-consuming since array has to be moved.
 *
 * If we do not care about the size, we can save the time to move the array.
 *
 */
int SinglyLinkedList::HeadDelete() {
    assert(!IsEmpty());
    int backup = vals[head];
    head = next[head];
    // move all elements 1 step backward
    size--;
    for (int i = 0; i < size; i++) {
        vals[i] = vals[i + 1];
    }

    return backup;
}

/**
 * @brief delete the node after index of i
 *
 * @param val
 * @param i
 * @return int
 */
int SinglyLinkedList::DeleteAbs(int i) {
    if (next[i] != -1) {   // if i's next exists
        int ret = vals[next[i]];
        next[i] = next[next[i]];
        return ret;
    }
    return -1;
}

int SinglyLinkedList::Top() {
    assert(!IsEmpty());
    return vals[head];
};

int SinglyLinkedList::Size() { return size; }

bool SinglyLinkedList::IsEmpty() { return size == 0; }

void SinglyLinkedList::Traverse() {
    for (int ptr = head; ptr != -1; ptr = next[ptr]) {
        cout << vals[ptr] << " ";
    }
    cout << endl;
}
```

To sum up: following are some common operations: note that `k`th here is not the traverse order but the memory order of 'nodes'.

- init: `head = -1; idx = 0;`, `idx` is used to indicate index of free space.
- head insert: `val[idx] = val; next[idx] = head; head = idx; idx++;`.
- insert after `k`th node: `val[idx] = val; next[idx] = next[k]; next[k] = idx; idx++;`.
- delete after `k`th node: `next[k] = next[next[k]];`.

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
when `j == 4`, 'prefix = ab' == 'postfix = ba', so next[5] = 2.
```

```c++
vector<int> kmp(string s, string pattern) {
    // transform to 1-based string
    string ss = string("0") + s;
    string pp = string("0") + pattern;

    // build next
    vector<int> ne(pp.size(), 0);
    // the first char pp[1] cannot have common prefix and postfix since our definition.
    // note that j is also the len of matching string.
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
            res.push_back(i - j);
            j = ne[j];   // move forward for next possible match
        }
    }

    return res;
}
```
