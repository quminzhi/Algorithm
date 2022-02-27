#include "heap.hpp"

#include <iostream>
#include <sstream>

Heap::Heap() {
    this->heapSize = 0;
    this->capacity = this->INIT_CAPACITY;
    this->heap.resize(this->capacity, 0);
}

Heap::Heap(vector<int> _heap) {
    this->heapSize = 0;
    this->capacity = this->INIT_CAPACITY;
    this->heap.resize(this->capacity, 0);
    while (this->heapSize >= this->capacity) {
        expandHeap();
    }
    for (int i = 0; i < _heap.size(); i++) {
        this->push(_heap[i]);
    }
}

int Heap::size() const { return this->heapSize; }

int Heap::peek() const { return this->heap[0]; }

bool Heap::isEmpty() const { return this->heapSize == 0; }

// operations
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

int Heap::pop() {
    int popped = 0;
    // Corner case: only one element left
    if (this->heapSize == 1) {
        this->heapSize--;
        return this->heap[0];
    }

    // move the last node to the root of heap
    popped = this->heap[0];
    this->heap[0] = this->heap[this->heapSize - 1];
    this->heapSize--;

    // update heap
    int root = 0;
    int left = 0;
    int right = 0;
    while (true) {
        // root exchange will exchange with min(left, right) if root is not the minimum
        // among them. if left child exists, check property
        left = 2 * root + 1;
        right = 2 * root + 2;
        if ((left >= this->heapSize) && (right >= this->heapSize)) {
            // case 1: neither left nor right child exist
            break;
        }
        if ((right >= this->heapSize) && (this->heap[left] < this->heap[root])) {
            // case 2: only left child exists
            swap(this->heap[root], this->heap[left]);
            root = left;
            continue;
        }
        // Notice: no way that only right child exists due to the property of a complete
        // tree
        // case 3: both of left and right children exist
        int min = this->heap[left] > this->heap[right] ? right : left;
        if (this->heap[root] > this->heap[min]) {
            swap(this->heap[root], this->heap[min]);
            root = min;
            continue;
        }

        // case 4: root is the smallest, well done
        break;
    }

    return popped;
}

void Heap::expandHeap() {
    // allocate a vector with larger space
    this->capacity *= this->EXPAND_FACTOR;
    // v.resize(new_size, padding value)
    this->heap.resize(this->capacity, 0);
}

string Heap::toString() const {
    string output;
    ostringstream os;
    os << "heap: { heapSize: " << this->heapSize << ", capacity: " << this->capacity
       << " }\n";
    os << "{";
    for (int i = 0; i < this->heapSize; i++) {
        if (i == (this->heapSize - 1)) {
            os << this->heap[i] << "}";
        } else {
            os << this->heap[i] << ", ";
        }
    }

    output = os.str();
    return output;
}

std::ostream& operator<<(std::ostream& os, const Heap& h) {
    os << h.toString();
    return os;
}

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