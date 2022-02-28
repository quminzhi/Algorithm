#include "heap.hpp"

#include <iostream>
#include <sstream>
#include <queue> // priority_queue
#include <unordered_map>

Heap::Heap() {
    this->heapSize = 0;
    this->capacity = this->INIT_CAPACITY;
    this->heap.resize(this->capacity, 0);
}

// /**
//  * @brief Construct a new Heap:: Heap object
//  * The tree is built by repeatedly pushing new elements. The time complexity is O(NlogN)
//  * 
//  * @param _heap 
//  */
// Heap::Heap(vector<int> _heap) {
//     this->heapSize = 0;
//     this->capacity = this->INIT_CAPACITY;
//     this->heap.resize(this->capacity, 0);
//     while (this->heapSize >= this->capacity) {
//         expandHeap();
//     }
//     for (int i = 0; i < _heap.size(); i++) {
//         this->push(_heap[i]);
//     }
// }

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

/**
 * @brief 
 * - Build a heap from a vector, and the time complexity: `O(N)`
 * - Repeatedly pop an element from the heap until it it empty, and the time complexity `O(NlogN)`
 * @param v 
 * @return vector<int> 
 */
vector<int> heapSort(const vector<int>& v) {
    vector<int> sorted;
    // heapify
    Heap h(v);
    // std::cout << h << std::endl;
    // pop until heap is empty
    while (!h.isEmpty()) {
        // std::cout << h << std::endl;
        sorted.push_back(h.pop());
    }

    return sorted;
}

/**
 * @brief find k-th largest element with max heap
 * 
 * @param nums 
 * @param k 
 * @return int 
 */
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int> pq; // max heap
    for (int val : nums) {
        pq.push(val);
    }

    while (k > 1) {
        pq.pop();
        k--;
    }

    return pq.top();
}

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