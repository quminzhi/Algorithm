#ifndef QUE_HPP
#define QUE_HPP

#include <deque>
#include <vector>
using namespace std;

/**
 * @brief MonotonicQueue is a non-descending queue.
 * 
 */
class MonotonicQueue {
   public:
    void Push(int val);
    void Pop();
    int Front();
    int Tail();

    deque<int> q;
};

vector<int> slideWindow(vector<int> nums, int k);

#endif