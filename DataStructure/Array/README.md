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

Define `s[]` as a stack, and `top` is top index of stack. Range of `s` is [0, top).

- init: `top = 0;`.
- push: `s[top++] = val;`.
- pop: `top--;`.
- empty: `top == 0;` (exclusive).

### Queue

Define `q[]` as a queue, and `front` and `tail` is front index and tail index of `q`.

- init: `front = 0; tail = -1;`, why -1? we want to include tail in our `q`, i.e. range of `q` is [front, tail].
- push: `q[++tail] = val;`.
- pop: `front++;`.
- empty: `front > tail` (refer to init).
