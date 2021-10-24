<!-- 
# Table of Contents
- [Binary Search and Array](#binarysearchandarray)
    - [Binary Search without Known Size](#binarysearchwithoutknownsize)
    - [Array and Pointers](#arrayandpointers)
        - [Square Array](#squarearray)
        - [Rotate Array](#rotatearray)
        - [Move Zeroes](#movezeroes)
        - [Two Sum Ordered](#twosumordered)
        - [Reverse Words](#reversewords)
        - [Link List](#linklist)
    - [Slide Window](#slidewindow)
    - [Longest Substring Without Repeating Characters](#longestsubstringwithoutrepeatingcharacters)
-->
# Binary Search and Array

## Binary Search without Known Size

> Problem: You have a sorted array of unique elements and an unknown size. You do not have an access to the array but you can use the ArrayReader interface to access it.
> You are also given an integer target. Return the index k of the hidden array where secret[k] == target or return -1 otherwise.
> Constrains: 1 <= secret.length <= 10^4, -10^4 <= secret[i], target <= 10^4, secret is sorted in a strictly increasing order.

*Keyword: unique, sorted, constrains*

There are two ways to solve the problem:

- define search limits
    Start from a small range `[left, right]` and expand it exponentially until the target is in the range.
    If `v[left] > target`, which means target is not in the array.

```c++
int search_sol2(const ArrayReader& reader, int target) {
    if (reader.get(0) == target) {
        return 0;
    }
    
    // TODO: search potential limits
    int left = 0; int right = 1;
    while (target > reader.get(right)) {
        left = right;
        right <<= 2;
    }

    // TODO: binary search
    int num, pivot;
    while (left < right) {
        pivot = left + (right - left) / 2;
        num = reader.get(pivot);
        if (num == target) {
            return pivot;
        }
        else {
            if (num > target) {
                right = pivot - 1;
            }
            else {
                left = pivot + 1;
            }
        }
    }

    return -1;
}
```

- "brute force" binary search
    Notice that with the help of reader function, which return INT_MAX if the index is out of range. So the secret array can be seen as one with size of 10^4, and all null value would be filled with INT_MAX. Therefore, we are able to "brute force" binary search on the secret array directly.
```c++
int search_sol3(const ArrayReader& reader, int target) {
    int left = 0;
    int right = 39999; // 10^4 - 1

    int num, pivot;
    while (left <= right) {
        pivot = left + (right - left) / 2;
        num = reader.get(pivot);
        if (num == target) {
            return pivot;
        }
        else {
            if (num > target) {
                right = pivot - 1;
            }
            else {
                left = pivot + 1;
            }
        }
    }

    return -1;
}
```

Tricks:

- use `pivot = left + (right - left) / 2` instead of `pivot = (left + right) / 2` for the latter may overflow when `left + right > INT_MAX`.
- use `right << 2` to replace `right * 2` if possible.
- double check special cases, such as null input, repetition, and overflow. 

## Array and Pointers

### Square Array

> Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.
> Constrains: 1 <= nums.length <= 10^4, -10^4 <= nums[i] <= 10^4, nums is sorted in non-decreasing order.

What we can learn from the problem is that how to carefully design your pointers. Either scanning from ends and go inward or from center and go outward.

```c++
vector<int> sortedSquares_sol2(vector<int>& nums) {
    vector<int> result;
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        if (abs(nums[left]) >= abs(nums[right])) {
            result.insert(result.begin(), nums[left] * nums[left]);
            left++;
        }
        else {
            result.insert(result.begin(), nums[right] * nums[right]);
            right--;
        }
    }

    return result;
}
```

Tricks:

- insert at the end `vector.push_back`, and at the front `vector.insert(vector.begin(), val)`

### Rotate Array

> Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.
> Constrains: 1 <= nums.length <= 10^4, -10^4 <= nums[i] <= 10^4, nums is sorted in non-decreasing order.

When comes to rotation or circulation, we have to take into consideration effective steps.

`effective steps = steps mod array.size`: if an array has size of 5, the steps is 5. Actually, the effective step is 0 since the elements in the array has not been changed.

So we can enumerate all possible answers with an array which is the double of original array.

```c++
/**
  * ex: original: [1, 2, 3, 5, 7]
  *     enumeration: [1, 2, 3, 5, 7, 1, 2, 3, 5, 7]
  * when step=1:    [^           ^]
  *      step=2:       [^           ^]
  *      step=3:          [^           ^]
  * ...
  */ 
```

The time complexity is O(N), and space complexity is O(2N)

### Move Zeroes

> Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements. Note that you must do this in-place without making a copy of the array.
> Constrains: 1 <= nums.length <= 10^4, -2^31 <= nums[i] <= 2^31 - 1

The problem teaches us how to make use of spaces we have without soliciting unnecessary memory spaces.
For example, if we want to move all non-zero numbers to the front of an array, we don\'t have to worry about the value of some index is overwritten, since we just padding zeroes after the last non-zero number is okay. Following is what code looks like:

```c++
void moveZeroes_sol2(vector<int>& nums) {
    // TODO: move non-zero numbers to the front
    int lastNonZero = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[lastNonZero++] = nums[i];
        }
    }
    
    // TODO: padding zeros
    for (int i = lastNonZero; i < nums.size(); i++) {
        nums[i] = 0;
    }
}
```

Also we are able to solve the problem by STL function `std::stable_partition`, what function does is exectly what we did above.

```c++
void moveZeroes_sol3(vector<int>& nums) {
    // if the third parameter is true, it will be partitioned.
    stable_partition(begin(nums), end(nums), [](int i){ return i; });
}
```

Tricks:

- `std::stable_partition` will make partition according to the lambda expression you pass.
- lambda expression: `[capture clause](param list){ lambda body }`.
- use STL function: `swap(a, b)` if needed.

### Two Sum Ordered

> Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= first < second <= numbers.length.
> Return the indices of the two numbers, index1 and index2, as an integer array [index1, index2] of length 2.
> The tests are generated such that there is exactly one solution. You may not use the same element twice.

```bash
Input: [-100, -10, 0, 0, 6, 18, 22, 22]  Target: 6
Output: [3, 5]
```

There are two common methods: 1. looking for dictionary 2. two pointers (ordered)

Both of methods above are O(N), but the latter does not need extra space.

Since the input is in non-descending order, we assgined two pointers to the maximum and minimum number of array, leftmost and rightmost respectively.

```bash
Input: [-100, -10, 0, 0, 6, 18, 22, 22]  Target: 6
         ^                          ^
        left                       right
```

Then there are three cases:

- `a[left] + a[right] == target`: there you go!
- `a[left] + a[right] < target`: then we know that the left number added the maximum number is still less than target, thereby there is no matching number in the array for `a[left]`. Therefore, `left++`.
- `a[left] + a[right] > target`: with the same logic, right number is out. Consequently, `right--`.

Following is the code for the problem:

```c++
vector<int> twoSum_sol2(vector<int>& numbers, int target) {
    int left = 0;
    int right = numbers.size() - 1;

    int sum = 0;
    while (left < right) {
        sum = numbers[left] + numbers[right];
        if (sum == target) {
            return {left+1, right+1};
        }
        else {
            if (sum < target) {
                left++;
            }
            else {
                right--;
            }
        }
    }

    return {-1, -1};
}
```

BTW: the first method (by looking for dictionary) is a more generic model for those problems. Even if it is disordered, it also works.

### Reverse Words

> Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
> Constrains: 1 <= s.length <= 5 * 104. s contains printable ASCII characters. s does not contain any leading or trailing spaces. There is at least one word in s. All the words in s are separated by a single space.

There are two things to do in the problem:

1. split words from the string.
2. reverse each word found.

```c++
string reverseWords_sol2(string s) {
    int begin = 0;
    for (int end = 0; end < s.size(); end++) {
        if (s[end] == ' ') {    // one word found
            reverse(s.begin() + begin, s.begin() + end);
            // words are separated by a single blank space.
            begin = end + 1;
        }
    }

    reverse(s.begin() + begin, s.end());

    return s;
}
```

Tricks:

- `reverse(iter.begin(), iter.end())`: `iter.end()` is excluded.

### Link List

There are two problems here, but they have similar idea.

The first is find the middle node of a node list.

> Given the head of a singly linked list, return the middle node of the linked list. If there are two middle nodes, return the second middle node.
> Constrains: The number of nodes in the list is in the range [1, 100]. 1 <= Node.val <= 100.

The second is remove Nth node counting from the end.

> Given the head of a linked list, remove the nth node from the end of the list and return its head.
> Constrains: The number of nodes in the list is sz. 1 <= sz <= 30. 0 <= Node.val <= 100. 1 <= n <= sz.

Our method is to track key node with pointers.

For instance in the second problem, we use 'end' and 'del' to track the end of node list and node to delete.

```c++
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* del = nullptr;
    ListNode* end = head;
    ListNode* pre = nullptr;

    // TODO: find the first possible node to delete
    int cnt = 0;
    while (end != nullptr) {
        cnt++;
        end = end->next;
        if (cnt == n) {
            del = head;
            break;
        }
    }

    // TODO: probe to the rest of nodes
    while (end != nullptr) {
        end = end->next;
        pre = del;
        del = del->next;
    }

    // TODO: delete target node
    if (del != nullptr) {
        if (pre == nullptr) {  // delete the first node
            head = head->next;
            delete del;
        }
        else {
            pre->next = del->next;
            delete del;
        }
    }

    return head;
}
```

Tricks:

- WHENEVER accessing to memory where a pointer points, CHECK if the pointer is `nullptr`.

## Slide Window

### Longest Substring Without Repeating Characters

> Given a string s, find the length of the longest substring without repeating characters.
> Constrains: 0 <= s.length <= 5 * 104. s consists of English letters, digits, symbols and spaces.

At first glance, we have to "brute force" all possible substrings and check from longer string to short if there is repeating characters. The time complexity is O(N^3) if so.

In fact, we don't have to check every substring, there are a lot of silly operations. Take 'aaaaa' as example, if I know substring 'aa' has repeating characters, then any substring that includes 'aa' as substring must have repeating characters, at least one.

So there is a pretty smart way to solve the problem called slide window.

```c++
/**
  * string: a   b   c   b   a   b   c   b   b  
  *         ^   ^                              ^
  *       begin end                           END
  */
```

we define a window `[begin, end)` to detect the longest substring without repeating characters. Obviously, the length of window is `end - begin`. The philosophy here is to keep all the characters in the window unique.

The algorithm for the problem is:

- resolve corner cases, null string and string with single character.
- initialize window.
- move end until it is out of the range of the string
    - if s[end] has the same character in window, then find it, and move begin to the next element of repeating character in the window.
    - update max length at each iteration.

```c++
int lengthOfLongestString_sol1(const string s) {
    if ((s.size() == 0) || (s.size() == 1)) return s.size();

    int maxLength = 0;
    int begin = 0;
    int end = 1;
    while (end < s.size()) {
        // TODO: find repeating index
        int repeatingIndex = -1;
        for (int i = begin; i < end; i++) {
            if (s[i] == s[end]) repeatingIndex = i;
        }

        if (repeatingIndex != -1) {
            begin = repeatingIndex + 1;
        }

        end++;
        // TODO: update max length
        if ((end - begin) > maxLength) {
            maxLength = end - begin;
        }
    }
}
```

Solution 1 uses for loop to search repeating character, thereby the time complexity is O(N^2). To improve that, we are able to use `vector` or `hashmap` to buffer characters within the window.

- vector buffer

```c++
int lengthOfLongestString_sol2(const string s) {
    if ((s.size() == 0) || (s.size() == 1)) return s.size();

    vector<int> notes(128, 0);

    int maxLength = 0;
    int begin = 0;
    notes[s[begin]]++;  // !!!
    int end = 1;
    while (end < s.size()) {
        // TODO: find repeating index
        while (notes[s[end]] > 0) {
            notes[s[begin]]--;
            begin++;
        }

        notes[s[end]]++;
        end++;

        // TODO: update max length
        maxLength = max(maxLength, end - begin);
    }

    return maxLength;
}
```

- hashmap buffer

```c++
int lengthOfLongestString_sol3(const string s) {
    if ((s.size() == 0) || (s.size() == 1)) return s.size();

    unordered_map<char, int> index;

    int maxLength = 0;
    int begin = 0;
    index[s[begin]] = 0; // !!!
    int end = 1;
    while (end < s.size()) {
        // TODO: find repeating index
        if (index.find(s[end]) != index.end()) {
            begin = index[s[end]] + 1;
        }

        index[s[end]] = end;
        end++;

        // TODO: update max length
        maxLength = max(maxLength, end - begin);
    }

    return maxLength;
}
```

In general, hash map is better since we have to cover all possible characters in vector method, whereas we only cache occurred characters.

Tricks:

- buffer method: trade off between time and space.


