# Heap

## Property of Heap

Heap is a binary tree with following properties:

- It is **a complete tree**: A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible. (FYI, A full binary tree is a tree in which every node other than the leaves has two children.)
- Min-heap: for each node, its left child and right child are smaller than it.
- Max-heap: for each node, its left and right children are greater than it.

### Build Heap

There are two ways to build heap:

- `siftDown` swaps a node that is too small with its largest child (thereby moving it down) until it is at least as large as both nodes below it.
- `siftUp` swaps a node that is too large with its parent (thereby moving it up) until it is no larger than the node above it.

Why building a heap with `sift down` approach has time complexity of `O(N)`.

[Time complexity analysis of building a heap](https://stackoverflow.com/questions/9755721/how-can-building-a-heap-be-on-time-complexity#:~:text=Heapify%20is%20O(n)%20when,O(n%20log%20n)%20.)

```c++
/**
 * @brief Construct a new Heap:: Heap object
 * The tree is built with the 'sift down' approach, which has the time complexity of O(N)
 * 
 * Notice the order of sift down. The idea is somewhat like dynamic algorithm, keep the 
 * property of min heap from bottom to top.
 * 
 * @param _heap 
 */
Heap::Heap(vector<int> _heap) {
    this->capacity = this->INIT_CAPACITY;
    this->heap.resize(this->capacity, 0);
    int size = _heap.size();
    while (size >= this->capacity) {
        expandHeap();
    }
    // copy
    this->heapSize = size;
    for (int i = 0; i < size; i++) {
        this->heap[i] = _heap[i];
    }
    // update every node within the heap in 'sift down' strategy
    int root, left, right;
    for (int i = this->heapSize - 1; i >= 0 ; i--) {
        root = i;
        while (true) {
            left = 2 * root + 1;
            right = 2 * root + 2;
            // case 1: no child
            if ((left >= this->heapSize) && (right >= this->heapSize)) {
                break;
            }
            // case 2: left child only
            if ((right >= this->heapSize) && (this->heap[root] > this->heap[left])) {
                swap(this->heap[root], this->heap[left]);
                root = left; // update pointer
                continue;
            }
            // case 3: left and right child
            int min = this->heap[left] > this->heap[right] ? right : left;
            if (this->heap[root] > this->heap[min]) {
                swap(this->heap[root], this->heap[min]);
                root = min;
                continue;
            }

            // otherwise: root is at correct index
            break;
        }
    }
}
```

## Operation

We will take min-heap as an example.

### Insertion

Insertion means adding an element to the Heap. After inserting the element, the properties of the Heap should remain unchanged.

- Insert node to next index to meet the criteria of a complete tree.
- Update along its ancestor to meet the property of min-heap.

```c++
/**
 * @brief push an element into the heap.
 * 1. put it into the last index of the heap.
 * 2. update along its search path.
 *
 * @param val 
 */
void Heap::push(int val) {
    // Corner case: the first element
    if (this->heapSize == 0) {
        this->heap[0] = val;
        this->heapSize++;
        return;
    }

    // check availability
    while (this->heapSize >= this->capacity) {
        expandHeap();
    }

    // insert to the last index
    this->heap[this->heapSize] = val;
    this->heapSize++;

    // update
    int ptr = this->heapSize - 1;
    int parent = (ptr - 1) / 2;
    while ((ptr != 0) && (this->heap[ptr] < this->heap[parent])) {
        // exchange and update ptr
        swap(this->heap[ptr], this->heap[parent]);
        ptr = parent;
        parent = (ptr - 1) / 2;
    }
}
```

### Deletion

Deletion means removing the “top” element from the Heap. After deleting the element, the property of Heap should remain unchanged.

- Delete the top node (root), the minimum number in the tree.
- Put the last node to the root. Why? because the last node must be a leaf node, it is convenient to move it.
- Update the tree to meet the property of min-heap. To be specific: compare changed node to its children and exchange with its smallest child recursively until it is the smallest.

```c++
int Heap::pop() {
    int popped = 0;
    // Corner case: only one element left
    if (this->heapSize == 1) {
        this->heapSize--;
        return this->heap[0];
    }

    // move the last node to the root of heap
    popped = this->heap[0];
    this->heap[0] = this->heap[this->heapSize-1];
    this->heapSize--;

    // update heap
    int root = 0;
    int left = 0;
    int right = 0;
    while (true) {
        // if left child exists, check property
        left = 2 * root + 1;
        if ((left < this->heapSize) && (this->heap[left] < this->heap[root])) {
            swap(this->heap[root], this->heap[left]);
            root = left;
            continue;
        }
        // if right child exists, check property
        right = 2 * root + 2;
        if ((right < this->heapSize) && (this->heap[right] < this->heap[root])) {
            swap(this->heap[root], this->heap[right]);
            root = right;
            continue;
        }
        // root is the smallest, well done
        break;
    }

    return popped;
}
```

## Implementation

Considered that heap is a complete tree, it is possible to build a complete tree with an array.

Benefits of implementing a tree with an array:

- the relationship is described in index rather than pointer. For zero-indexed array, parent = `(i - 1) / 2`,  left child = `(2 * i) + 1`, and right child = `(2 * i) + 2`.
- all elements are put in the memory in a sequence.

For more details, feel free to check `heap.hpp` and `heap.cpp` in `lib` directory.

## Application

### Heap Sort

- Build a heap from a vector, and the time complexity: `O(N)`
- Repeatedly pop an element from the heap until it it empty, and the time complexity `O(NlogN)`

```c++
vector<int> heapSort(const vector<int>& v) {
    vector<int> sorted;
    // heapify
    Heap h(v);
    // pop until heap is empty
    while (!h.isEmpty()) {
        sorted.push_back(h.pop());
    }

    return sorted;
}
```

### Top K Frequent Elements

> Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in any order.

There are some tricks in this problem:

- Customize Comparison Function for `priority_queue`. By default, `priority_queue` is a max heap, which means it is in a descending order. To keep top k frequent elements, we need convert it to min heap. That is to redefine comparison function.

```c++
    auto cmp = [&counter](int lhs, int rhs) { // capture counter variable
        return counter[lhs] > counter[rhs];
    };
    priority_queue<int, vector<int>, decltype(cmp)> h(cmp);
```

The prototype of **Lambda Function**: `[capture clause](parameter list) (mutable) (throw()) (return type) { lambda body }`.

- **Capture Clause**: A lambda can introduce new variables in its body (in C++14), and it can also access, or capture, variables from the surrounding scope. A lambda begins with the capture clause. It specifies which variables are captured, and whether the capture is by value or by reference. Variables that have the ampersand (`&`) prefix are accessed by reference and variables that don't have it are accessed by value.
- **Mutable Specification**: Typically, a lambda's function call operator is const-by-value, but use of the mutable keyword cancels this out. It doesn't produce mutable data members. The mutable specification enables the body of a lambda expression to modify variables that are captured by value. Some of the examples later in this article show how to use mutable.
- **Return Type**: The return type of a lambda expression is automatically deduced. You don't have to use the auto keyword unless you specify a trailing-return-type. The trailing-return-type resembles the return-type part of an ordinary function or member function. However, the return type must follow the parameter list, and you must include the trailing-return-type keyword `->` before the return type.

```c++
auto x1 = [](int i) -> int { return i; };
```

The complete solution is shown below.

```c++
/**
 * @brief capture the top k frequent elements
 * 
 * @param nums 
 * @param k 
 * @return vector<int> 
 */
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> counter;
    for (int val : nums) {
        counter[val] += 1;
    }

    // min heap
    auto cmp = [&counter](int lhs, int rhs) {
        return counter[lhs] > counter[rhs];
    };
    priority_queue<int, vector<int>, decltype(cmp)> h(cmp);
    for (pair<int, int> p : counter) {
        h.push(p.first);
        if (h.size() > k) {
            h.pop();
        }
    }

    // output
    vector<int> result(k);
    for (int i = k-1; i >= 0; i--) {
        result[i] = h.top();
        h.pop();
    }

    return result;
}
```

### Kth Largest Element

> Design a class to find the `kth` largest element in a stream. Note that it is the `kth` largest element in the sorted order, not the `kth `distinct element.
>
> Implement `KthLargest` class:
>
> - `KthLargest(int k, int[] nums)` Initializes the object with the integer k and the stream of integers nums.
> - `int add(int val)` Appends the integer val to the stream and returns the element representing the kth largest element in the stream.

To make it clear, an example is shown as below:

```c++
// Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
// Output
[null, 4, 5, 5, 8, 8]

// Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8
```

Our algorithm is to maintain a min heap and keep its size to be k so that the kth largest element is the root element in the min heap.

Note: the size of `pq` may be less than k.

```c++
// hpp
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums);
    int add(int val);

    priority_queue< int, vector<int>, std::greater<int> > pq; // min heap
    int kth;
};
```

```c++
// cpp
/**
 * @brief Construct a new Kth Largest:: Kth Largest object
 * Push each element in the priority queue (max heap by default). But for our algorithm,
 * we should push it into a min heap. Keep the size of min heap to be k so that the root
 * of the min heap is the kth largest element.
 * 
 * @param k
 * @param nums
 */
KthLargest::KthLargest(int k, vector<int>& nums) {
    this->kth = k;
    for (int val : nums) {
        this->pq.push(val);
    }

    // keep the size of pq to be k
    while (this->pq.size() > k) {
        this->pq.pop();
    }
}

/**
 * @brief append a val to max heap and return the kth largest element
 * The trick here is to maintain a min heap and keep the heap size to be k. The kth
 * element is the smallest one in the min heap. In the constructor, we have kept the
 * size of pq to be k. Here we only need push new val and pop the minimum to get kth
 * largest element.
 *
 * @param val
 * @return int
 */
int KthLargest::add(int val) {
    // push the given element
    this->pq.push(val);
    while (this->pq.size() > this->kth) {
        this->pq.pop();
    }

    return this->pq.top();
}
```
