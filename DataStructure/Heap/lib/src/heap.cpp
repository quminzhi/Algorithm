#include "heap.hpp"

Heap::Heap() {
    this->heapSize = 0;
    this->capacity = this->INIT_CAPACITY;
    this->heap.resize(this->capacity, 0);
}

// /**
//  * @brief Construct a new Heap:: Heap object
//  * The tree is built by repeatedly pushing new elements. The time complexity is
//  O(NlogN)
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
    for (int i = this->heapSize - 1; i >= 0; i--) {
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
                root = left;   // update pointer
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
 * - Repeatedly pop an element from the heap until it it empty, and the time complexity
 * `O(NlogN)`
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
    priority_queue<int> pq;   // max heap
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
    auto cmp = [&counter](int lhs, int rhs) { return counter[lhs] > counter[rhs]; };
    priority_queue<int, vector<int>, decltype(cmp)> h(cmp);
    for (pair<int, int> p : counter) {
        h.push(p.first);
        if (h.size() > k) {
            h.pop();
        }
    }

    // output
    vector<int> result(k);
    for (int i = k - 1; i >= 0; i--) {
        result[i] = h.top();
        h.pop();
    }

    return result;
}

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

/**
 * @brief
 * A row i is weaker than a row j if one of the following is true:
 *  - The number of soldiers in row i is less than the number of soldiers in row j.
 *  - Both rows have the same number of soldiers and i < j.
 * @param mat
 * @param k
 * @return vector<int>: k weakest rows in the given matrix.
 */
vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
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

/**
 * @brief return kth smallest number in an semi-ordered matrix
 * 'semi-ordered' means two properties are guaranteed:
 *
 * - each row is ordered
 * - each colum is ordered
 *
 * One brute way is ignore those properties and put all numbers into a max heap with the
 * size of k. Then the root of the max heap is the answer.
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
int minMeetingRooms(vector<vector<int>>& intervals) {
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
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp2)> pq(cmp2);

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

double EuclideanDistanceToOrigin(int i, int j) { return sqrt(pow(i, 2) + pow(j, 2)); }

/**
 * @brief return k closest points to origin
 * Since we want k closest points, we need maintain a max heap and keep its size to be k.
 * @param points
 * @param k
 * @return vector< vector<int> >
 */
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    auto cmp = [&points](vector<int> left, vector<int> right) -> bool {
        return EuclideanDistanceToOrigin(left[0], left[1]) <
               EuclideanDistanceToOrigin(right[0], right[1]);
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

    for (auto& point : points) {
        pq.push(point);
        while (pq.size() > k) {
            pq.pop();
        }
    }

    vector<vector<int>> closest;
    while (!pq.empty()) {
        closest.push_back(pq.top());
        pq.pop();
    }

    return closest;
}

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
    vector<int> margins(heights.size() - 1, 0);   // height margin of (i, i+1)
    for (int i = 0; i < heights.size() - 1; i++) {
        margins[i] = heights[i + 1] - heights[i];
    }

    priority_queue<int, vector<int>, std::greater<int>> pq;   // min heap
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