# Heap

## Property of Heap

Heap is a binary tree with following properties:

- It is **a complete tree**: A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible. (FYI, A full binary tree is a tree in which every node other than the leaves has two children.)
- Min-heap: for each node, its left child and right child are smaller than it.
- Max-heap: for each node, its left and right children are greater than it.

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

