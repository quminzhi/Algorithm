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
    void Insert(int val, int idx);  // idx refers to the ith node in a linked list
    void InsertAbs(int val, int i); // i here refers to the index of array
    int HeadDelete();

    int Top();
    int Size();
    bool IsEmpty();

    int head;
    int size;
    int val[INIT_SIZE];
    int next[INIT_SIZE];   // index by an array index not a pointer

   private:
    int INIT_SIZE = 100;
}
```

- implementation (.cpp)

```c++
SinglyLinkedList() {
    head = -1;   // nullptr
    size = 0;
}

void SinglyLinkedList::HeadInsert(int val) {
    // new 'node' will be assigned to the end of the array
    val[size] = val;
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
        for (int ptr = head, i = 0; i < idx && next[ptr] != -1; i++, ptr = next[ptr];) {
            pre = ptr;
        }
        val[size] = val;
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
void InsertAbs(int val, int i) {
    val[size] = val;
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
    int backup = val[head];
    head = next[head];
    // move all elements 1 step backward
    size--;
    for (int i = 0; i < size; i++) {
        val[i] = val[i + 1];
    }

    return backup;
}

int SinglyLinkedList::Top() {
    assert(!IsEmpty());
    return val[head]
};

int SinglyLinkedList::Size() { return size; }

bool SinglyLinkedList::IsEmpty() { return size == 0; }
```

To sum up: following are some common operations:

- init: `head = -1; idx = 0;`, `idx` is used to indicate index of free space.
- head insert: `val[idx] = val; next[idx] = head; head = idx; idx++;`.
- insert after `k`th node: `val[idx] = val; next[idx] = next[k]; next[k] = idx; idx++;`.
- delete after `k`th node: `next[k] = next[next[k]];`.

