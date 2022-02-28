#ifndef HEAP_HPP
#define HEAP_HPP
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Min Heap implemented with an array.
 * Trick:
 * - formula to find parent becomes easy: parent index of node i is '(i - 1) / 2'
 * - left child is '2 * i + 1' and right child is '2 * i + 2'
 * 
 */
class Heap {
   public:
    Heap();
    Heap(vector<int>);

    int size() const;
    int peek() const;
    bool isEmpty() const;

    // operations
    void push(int val);
    int pop(); // pop the first element

    int heapSize;
    int capacity;
    vector<int> heap;

    friend std::ostream& operator<<(std::ostream& os, const Heap& h);

   private:
    void expandHeap();
    string toString() const;

    int INIT_CAPACITY = 10;
    int EXPAND_FACTOR = 2;
};

std::ostream& operator<<(std::ostream& os, const Heap& h);

// related problems:
vector<int> heapSort(const vector<int>& v);
int findKthLargest(vector<int>& nums, int k);
vector<int> topKFrequent(vector<int>& nums, int k);

#endif