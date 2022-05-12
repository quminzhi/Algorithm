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

### Last Stone Weight

> You are given an array of integers stones where `stones[i]` is the weight of the ith stone.
> We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with `x <= y`. The result of this smash is:
>
> - If `x == y`, both stones are destroyed, and
> - If `x != y`, the stone of weight x is destroyed, and the stone of weight y has new weight `y - x`.
>
> At the end of the game, there is at most one stone left.
> Return the smallest possible weight of the left stone. If there are no stones left, return 0.

Finding kth elements in an ordered sequence is what `heap` is good at.

```c++
/**
 * @brief Simulate smash game with max heap.
 * 
 * @param stones 
 * @return int 
 */
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());
    // game starts
    int first, second;
    while (pq.size() > 1) {
        // choose two heaviest stones
        first = pq.top();
        pq.pop();
        second = pq.top();
        pq.pop();
        
        // smash
        pq.push(abs(first - second));
    }

    if (pq.empty()) return 0;
    return pq.top();
}
```

### The K Weakest Rows in a Matrix

> You are given an `m x n` binary matrix mat of 1's (representing soldiers) and 0's (representing civilians). The soldiers are positioned in front of the civilians. That is, all the 1's will appear to the left of all the 0's in each row.
>
> A row `i` is weaker than a row `j` if one of the following is true:
>
> - The number of soldiers in row `i` is less than the number of soldiers in row `j`.
> - Both rows have the same number of soldiers and `i < j`.
>
> Return the indices of the `k` weakest rows in the matrix ordered from weakest to strongest.

The key here is to define a min heap in C++ according to the given rules:

- min heap: define greater (`lhs > rhs`)
- max heap (default): define less (`lhs < rhs`)

```c++
    unordered_map<int, int> m;   // row num -> num of soldiers on that row
    // define comparison rules
    auto cmp = [&m](int i, int j) -> bool {
        return (m[i] > m[j]) || ((m[i] == m[j]) && (i > j));
    };
    // notice: 'vector<int>' is the type of the underlying container to use to store the
    // elements
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
```

The full code is shown as follows.

```c++
/**
 * @brief
 * A row i is weaker than a row j if one of the following is true:
 *  - The number of soldiers in row i is less than the number of soldiers in row j.
 *  - Both rows have the same number of soldiers and i < j.
 * @param mat
 * @param k
 * @return vector<int>: k weakest rows in the given matrix.
 */
vector<int> kWeakestRows(vector<vector<int> >& mat, int k) {
    unordered_map<int, int> m;   // row num -> num of soldiers on that row

    // define comparison rules
    auto cmp = [&m](int i, int j) -> bool {
        return (m[i] > m[j]) || ((m[i] == m[j]) && (i > j));
    };
    // notice: 'vector<int>' is the type of the underlying container to use to store the
    // elements
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

    for (int row = 0; row < mat.size(); row++) {
        for (int col = 0; col < mat[0].size(); col++) {
            if (mat[row][col] == 1) {
                m[row] += 1;
            }
        }
        pq.push(row);
    }

    vector<int> result;
    // get k weakest rows
    for (int i = 0; i < k; i++) {
        result.push_back(pq.top());
        pq.pop();
    }

    return result;
}
```

### Kth Smallest Element in a Sorted Matrix

> Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the `kth` smallest element in the matrix.
>
> Note that it is the `kth` smallest element in the sorted order, not the `kth` distinct element.
>
> You must find a solution with a memory complexity better than `O(n2)`.

Generic method for Kth largest number and Kth smallest number: Notice that priority queue is actually a heap. Ascending priority queue is implemented with min heap and descending priority queue is implemented with max heap. Every time we pop an element, the maximum element is popped in max heap and the minimum one in min heap.

- Kth largest: maintain a min heap and keep the size of it to be k. `pq.pop()` will get rid of all smaller numbers.
- Kth smallest: maintain a max heap and keep the size of it to be k. `pq.pop()` will remove all larger numbers.

```c++
/**
 * @brief return kth smallest number in an semi-ordered matrix
 * 'semi-ordered' means two properties are guaranteed:
 *
 * - each row is ordered
 * - each colum is ordered
 *
 * One brute way is ignore those properties and put all numbers into a max heap with 
 * the size of k. Then the root of the max heap is the answer.
 * 
 * Time complexity: O(K) + O(N * log(K))
 * @param matrix
 * @param k
 * @return int
 */
int kthSmallest(vector<vector<int>>& matrix, int k) {
    priority_queue<int> pq;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            pq.push(matrix[i][j]);
            while (pq.size() > k) {
                pq.pop();
            }
        }
    }

    return pq.top();
}
```

### Meeting Rooms II

> Given an array of meeting time intervals intervals where `intervals[i] = [starti, endi]`, return the minimum number of conference rooms required.

We need to allocate room to meetings that occur earlier. Hence we are going to sort all input intervals in terms of start time. We use a min heap to track when the allocated rooms get free (end time).

- Customize Comparison Function

```c++
// customize cmp function for sort: ascending order
    auto cmp = [&intervals](vector<int> left, vector<int> right) -> bool {
        return left[0] < right[0];
    };
    std::sort(intervals.begin(), intervals.end(), cmp);

    // customize cmp function for pq (arg list: the type of key of intervals)
    // min heap: greater, max heap: less
    auto cmp2 = [&intervals](vector<int> left, vector<int> right) -> bool {
        return left[1] > right[1];
    };
    priority_queue<vector<int>, vector< vector<int> >, decltype(cmp2)> pq(cmp2);
```

Full code is shown as below:

```c++
/**
 * @brief We need to allocate room to meetings that occur earlier. Hence we are going
 * to sort all input intervals in terms of start time. We use a min heap to track when
 * the allocated rooms get free (end time).
 * 
 * There are two scenarios when a new request comes:
 *  - the start time of new meeting is greater than the min in the min heap, meaning 
 * it can use that room. We pop the min and push the end time of the new meeting into
 * the min heap.
 *  - the start time of new meeting is smaller than the min in the min heap, we have
 * to allocate a new room for it. Room counter increases one and push the end time of
 * the new meeting into the heap.
 * 
 * @param intervals 
 * @return int 
 */
int minMeetingRooms(vector< vector<int> >& intervals) {
    // customize cmp function for sort: ascending order
    auto cmp = [&intervals](vector<int> left, vector<int> right) -> bool {
        return left[0] < right[0];
    };
    std::sort(intervals.begin(), intervals.end(), cmp);

    // customize cmp function for pq (arg list: the type of key of intervals)
    // min heap: greater, max heap: less
    auto cmp2 = [&intervals](vector<int> left, vector<int> right) -> bool {
        return left[1] > right[1];
    };
    priority_queue<vector<int>, vector< vector<int> >, decltype(cmp2)> pq(cmp2);

    // allocate rooms
    int room_counter = 0;
    for (vector<int> meeting : intervals) {
        if (pq.empty()) {
            room_counter++;
            pq.push(meeting);
        } else {
            if (pq.top()[1] > meeting[0]) {
                // no free room
                room_counter++;
                pq.push(meeting);
            } else {
                // available
                pq.pop();
                pq.push(meeting);
            }
        }
    }

    return room_counter;
}
```

### K Closest Point to Origin

> Given an array of points where `points[i] = [xi, yi]` represents a point on the X-Y plane and an integer `k`, return the `k` closest points to the origin `(0, 0)`.
>
> The distance between two points on the X-Y plane is the Euclidean distance (i.e., `√(x1 - x2)^2 + (y1 - y2)^2)`.
>
> You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

Full code is shown as below,

```c++
double EuclideanDistanceToOrigin(int i, int j) {
    return sqrt(pow(i, 2) + pow(j, 2));
}

/**
 * @brief return k closest points to origin
 * Since we want k closest points, we need maintain a max heap and keep its size to be k.
 * @param points 
 * @param k 
 * @return vector< vector<int> > 
 */
vector< vector<int> > kClosest(vector< vector<int> >& points, int k) {
    auto cmp = [&points](vector<int> left, vector<int> right) -> bool {
        return EuclideanDistanceToOrigin(left[0], left[1]) < EuclideanDistanceToOrigin(right[0], right[1]);
    };
    priority_queue<vector<int>, vector< vector<int> >, decltype(cmp)> pq(cmp);

    for (auto& point : points) {
        pq.push(point);
        while (pq.size() > k) {
            pq.pop();
        }
    }

    vector< vector<int> > closest;
    while (!pq.empty()) {
        closest.push_back(pq.top());
        pq.pop();
    }

    return closest;
}
```

### Minimum Cost to Connect Sticks

> You have some number of sticks with positive integer lengths. These lengths are given as an array sticks, where `sticks[i]` is the length of the `ith` stick.
>
> You can connect any two sticks of lengths `x` and `y` into one stick by paying a cost of `x + y`. You must connect all the sticks until there is only one stick remaining.
>
> Return the minimum cost of connecting all the given sticks into one stick in this way.

The observation is that we should connect two smallest one at each step to get the minimum cost. That's where min heap comes into stage.

```c++
/**
 * @brief return minimum cost to connect sticks
 * The observation is that we should connect two smallest one at each step to get
 * the minimum cost. That's where min heap comes into stage.
 *
 * @param sticks
 * @return int
 */
int connectSticks(vector<int>& sticks) {
    priority_queue<int, vector<int>, std::greater<int>> pq(sticks.begin(), sticks.end());
    int cost = 0;
    int s1, s2;
    while (pq.size() > 1) {
        // retrieve two smallest sticks
        s1 = pq.top();
        pq.pop();
        s2 = pq.top();
        pq.pop();
        cost += s1 + s2;
        pq.push(s1 + s2);
    }

    return cost;
}
```

### Furthest Building

> You are given an integer array `heights` representing the heights of buildings, some `bricks`, and some `ladders`.
>
> You start your journey from building `0` and move to the next building by possibly using bricks or ladders.
>
> While moving from building `i` to building `i+1` (0-indexed)
>
> - If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
> - If the current building's height is less than the next building's height, you can either use one ladder **or** (`h[i+1] - h[i]`) bricks.
>
> Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.

The key idea is to use k ladders on top k positive `margins[0, where we are now]`.

We can use a min heap to track top k positive margins so far.

```c++
/**
 * @brief return the furthest building we can reach from building[0]
 * There are something to think about:
 * 1. when do I need bricks or ladders when going from one building to another?
 *   building[i] < building[i+1]
 * 2. Which tool should I use when it is needed to reach a optimal outcome?
 *   The basic idea is to use ladder for maximum cost when going from one building
 * to another. To achieve that, we have an algorithm as follows:
 *   - Use ladders for top k margins, where k is the size of ladders
 *   - If no bricks available, we are done.
 * 
 * To be short, keep k ladders applied on top k current margins
 * 
 * @param heights 
 * @param bricks 
 * @param ladders 
 * @return int 
 */
int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    vector<int> margins(heights.size()-1, 0); // height margin of (i, i+1)
    for (int i = 0; i < heights.size() - 1; i++) {
        margins[i] = heights[i+1] - heights[i];
    }

    priority_queue<int, vector<int>, std::greater<int>> pq; // min heap
    int i = 0;
    for (; i < margins.size(); i++) {
       if (margins[i] > 0) {
           if (ladders > 0) {
               // use ladders first
               ladders--;
               pq.push(margins[i]);
           } else {
               // use bricks to replace the minimum margin in current margins
               pq.push(margins[i]);
               bricks -= pq.top();
               if (bricks < 0) break;
               pq.pop();
           }
       }
    }

    return i;
}
```

### Find Median from Data Stream

> The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value and the median is the mean of the two middle values.
>
> - For example, for `arr = [2,3,4]`, the median is `3`.
> - For example, for `arr = [2,3]`, the median is `(2 + 3) / 2 = 2.5`.
>
> Implement the MedianFinder class:
>
> - `MedianFinder()` initializes the `MedianFinder` object.
> - `void addNum(int num)` adds the integer num from the data stream to the data structure.
> - `double findMedian()` returns the median of all elements so far. Answers within 10^-5 of the actual answer will be accepted.

Using two heaps to track left and right half of input stream.

```c++
/**
 * @brief Construct a new Median Finder:: Median Finder object
 * Maintain left half of sequence with max heap (lo) and maintain right half with 
 * min heap (hi).
 *   - if size = 2 * n + 1, then keep lo holding n + 1 numbers and hi holding n numbers.
 *   - if size = 2 * n, then both of lo and hi hold n numbers.
 */
MedianFinder::MedianFinder() {}

void MedianFinder::addNum(int num) {
    lo.push(num);

    // balancing step: pop the max of lo (max heap) to hi (min heap) 
    // notice that lo.top() is not necessarily 'num', it should be the max number of lo
    hi.push(lo.top());
    lo.pop();

    // keep our presumed property
    if (lo.size() < hi.size()) {
        lo.push(hi.top());
        hi.pop();
    }
}

double MedianFinder::findMedian() {
    return lo.size() > hi.size() ? lo.top() : ((double)lo.top() + hi.top()) * 0.5;
}
```

### Top K Frequent Words

> Given an array of strings words and an integer k, return the k most frequent strings.
>
> Return the answer sorted by the frequency from highest to lowest. Sort the words with the same frequency by their lexicographical order.

Two different ways to customize comparator of priority queue.

```c++
class Word {
   public:
    Word(string _word, int _freq)
        : word(_word), freq(_freq) {};
    string word;
    int freq;
    
    bool operator> (const Word& rhs) const {
        return freq < rhs.freq || (freq == rhs.freq && word > rhs.word);
    }
};

priority_queue<Word, vector<Word>, greater<Word>> pq;
```

or construct `Comparator`.

```c++
struct Comparator {
    bool operator()(const Word& lhs, const Word& rhs) {
        return lhs.freq < rhs.freq || (lhs.freq == rhs.freq && lhs.word > rhs.word);
    }  
};

priority_queue<Word, vector<Word>, Comparator> pq;
```

The full code is:

```c++
class Solution {
public:
    class Word {
       public:
        Word(string _word, int _freq)
            : word(_word), freq(_freq) {};
        string word;
        int freq;
        
        bool operator> (const Word& rhs) const {
            return freq < rhs.freq || (freq == rhs.freq && word > rhs.word);
        }
    };
    
    struct Comparator {
        bool operator()(const Word& lhs, const Word& rhs) {
            return lhs.freq < rhs.freq || (lhs.freq == rhs.freq && lhs.word > rhs.word);
        }  
    };
    
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freq;
        for (auto word : words) {
            freq[word]++;
        }
        
        priority_queue<Word, vector<Word>, greater<Word>> pq;
        // priority_queue<Word, vector<Word>, Comparator> pq;
        for (auto t : freq) {
            pq.push(Word(t.first, t.second));
        }
        
        vector<string> res;
        for (int i = 0; i < k; i++) {
            auto w = pq.top();
            pq.pop();
            res.push_back(w.word);
        }
        
        return res;
    }
};
```
