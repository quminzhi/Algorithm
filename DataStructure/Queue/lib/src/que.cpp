#include "que.hpp"

/**
 * @brief k is the time to life for current val
 * 
 * @param val 
 * @param k 
 */
void MonotonicQueue::Push(int val) {
    while (!q.empty() && val <= q.back()) {
        q.pop_back();
    }
    q.push_back(val);
}

void MonotonicQueue::Pop() {
    if (!q.empty()) {
        q.pop_front();
    }
}

int MonotonicQueue::Front() {
    return q.front();
}

int MonotonicQueue::Tail() {
    return q.back();
}

/**
 * @brief output the minimum value within slide window.
 * 
 * @param nums 
 * @param k 
 * @return vector<int> 
 */
vector<int> slideWindow(vector<int> nums, int k) {
    vector<int> res;
    vector<int> que(1e3, 0); // !!! record the index of number in nums

    int front = 0, end = 0; // range of que is [front, end)
    for (int i = 0; i < nums.size(); i++) {
        // slide: [i - k + 1, i]
        // pop if que is not empty and front is out of the slide range
        if (front < end && que[front] < i - k + 1) front++;
        // push: keep an non-descending queue
        while (front < end && nums[que[end-1]] >= nums[i]) end--;
        que[end++] = i;
        // if length == k, start recording
        if (i >= k-1) {
            res.push_back(nums[que[front]]);
        }
    }

    return res;
}