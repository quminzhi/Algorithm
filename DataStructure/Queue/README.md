# Queue

## Monotonic Queue

```c++
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
```

`deque` is an indexed sequence container that allows fast insertion and deletion at both its beginning and its end. Different from `queue`, we have operations like `push_front()`, `push_back()` (== `push` in `queue`), `pop_front()` (== `pop` in `queue`), `pop_back()`.

### Slide Window

> Given a sequence of number and a length of slide window, return the minimum value within the window as it goes from left to right.

This is a classic problem for monotonic queue. We need to simulate a monotonic queue.

Notice that index contains much more useful information than value of `nums`. From index, we are able to check if the number being processed is within the slide window.

- keep an monotonic (non-descending) queue as the slide moves.
- all elements in the queue should be within the slide window.

```c++
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
        // push: keep a non-descending queue
        while (front < end && nums[que[end-1]] >= nums[i]) end--;
        que[end++] = i;
        // if length == k (i >= k-1), start recording
        if (i >= k-1) {
            res.push_back(nums[que[front]]);
        }
    }

    return res;
}
```
