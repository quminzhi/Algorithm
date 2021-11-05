# Algorithm II

## Binary Search

### Search the First and the Last Element

> Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
>
> If target is not found in the array, return [-1, -1].
>
> You must write an algorithm with O(log n) runtime complexity.

The key to the problem is how to refine or design naive binary search. How to design a binary search that can search the index of the first target

The trick is trying to detect neighboring element. For the case of finding the first target.

```c++
// ...binary search code...
    if (nums[mid] == target) {
        // try to detect
        if ((mid > 0) && (nums[mid-1] == target)) {
            // not the first! continue to search in the left half
            r = mid - 1;
        }
        else {
            break;
        }
    }
// ...rest code...
```

Similarly, we can design a binary search finding the last target.

```c++
vector<int> searchRange_sol2(vector<int> nums, int target) {
    if (nums.size() == 0) return {-1, -1};
    vector<int> result;
    // TODO: binary search for the first target
    int l = 0;
    int r = nums.size() - 1;
    int mid = 0;
    while (l <= r) {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target) {
            if ((mid > 0) && (nums[mid-1] == target)) {
                r = mid - 1;
            }
            else {
                // mid is the first
                break;
            }
        }
        else if (nums[mid] > target) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    if (l > r) return {-1, -1};
    result.push_back(mid);

    // TODO: binary search for the last target
    l = 0; r = nums.size() - 1;
    while (l <= r) {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target) {
            if ((mid < nums.size() - 1) && (nums[mid+1] == target)) {
                l = mid + 1;
            }
            else {
                break;
            }
        }
        else if (nums[mid] < target) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    if (l > r) return {-1, -1};
    result.push_back(mid);

    return result;
}
```

Tricks:

- Change the behavior of binary search.


