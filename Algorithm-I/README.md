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
        - [Permutation in String](#permutationinstring)
- [BFS and DFS](bfsanddfs)
    - [Flood Fill](#floodfill)
    - [Max Area of Island](#maxareaofisland)
    - [Merge Trees](#mergetrees)
    - [Connect Tree](#connecttree)
    - [Update Matrix](#updatematrix)
- [Recursion and Backtracking]
    - [Reverse LinkList](#reverselinklist)
    - [Combination](#combination)
    - [Permutation](#permutation)
    - [Letter Case Permutation](#lettercasepermutation)
-->
# Binary Search and Array

## Binary Search without Known Size

> Problem: You have a sorted array of unique elements and an unknown size. You do not have an access to the array but you can use the ArrayReader interface to access it.
> You are also given an integer target. Return the index k of the hidden array where secret[k] == target or return -1 otherwise.
>
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
>
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
>
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
>
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
>
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
>
> Constrains: The number of nodes in the list is in the range [1, 100]. 1 <= Node.val <= 100.

The second is remove Nth node counting from the end.

> Given the head of a linked list, remove the nth node from the end of the list and return its head.
>
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
>
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

### Permutation In String

> Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise. In other words, return true if one of s1's permutations is the substring of s2.
>
> 1 <= s1.length, s2.length <= 10^4. s1 and s2 consist of lowercase English letters.

Our preliminary method is decomposing the problem into two subproblems:

- enumerate all permutation of `s1`. (how to deal with repetition) => set
- check if `s2` contains the given string. (how to do it efficiently, notice that the permutation of a string has equal length)

For the second subproblem, we are able to use a slide window with fixed length to check if `s2` contains the given string.

```c++
bool checkInclusion_sol1(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    // TODO: get permutation strings
    unordered_set<string> records;
    string result;
    permutation(s1, result, records);

    // TODO: check if match
    int begin = 0;
    int end = s1.length();
    bool flag = true;
    int index = 0;
    for (string s : records) {
        while (end < s2.length()) {
            for (int i = begin; i < end; i++) {
                if (s[index] != s2[i]) {
                    flag = false;
                    break;
                }
                index++;
            }
            if (flag) {
                return true;
            }

            // TODO: move forward
            begin++;
            end++;
            flag = true;
            index = 0;
        }

        // TODO: reset begin and end
        begin = 0;
        end = s1.length();
    }

    return false;
}
```

Is there anything can be optimized? How about constructing two sets? One for all permutations of `s1`, and the other for all window substrings of `s2`. And we will check if intersection of set1 and set2 is `null`. 

```c++
bool checkInclusion_sol2(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    // TODO: get permutation strings
    unordered_set<string> records_s1;
    string result;
    permutation(s1, result, records_s1);

    // TODO: construct set2
    unordered_set<string> records_s2;
    int begin = 0;
    int size = s1.size();
    while (begin <= (s2.size() - size)) {
        records_s2.insert(s2.substr(begin, size));
        begin++;
    }

    // TODO: check if there is intersection
    for (auto&& str : records_s1) {
        if (records_s2.find(str) != records_s2.end()) {
            return true;
        }
    }

    return false;
}
```

Great! Now we are able to do some optimization for recursion. We are able to simulate recursion with queue for 'BFS' recursion, and stack for 'DFS' recursion.

```c++
bool checkInclusion_sol3(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    // TODO: construct set2
    unordered_set<string> records_s2;
    int begin = 0;
    int size = s1.size();
    while (begin <= (s2.size() - size)) {
        records_s2.insert(s2.substr(begin, size));
        begin++;
    }

    // TODO: search permutations and find if s2 contains it
    class PermutationState {
    public:
        string left;
        string result;
        PermutationState(string left, string result)
            : left(left), result(result) {}
    };

    queue<PermutationState*> buffer;
    buffer.push(new PermutationState(s1, ""));
    while (!buffer.empty()) {
        PermutationState* cur = buffer.front();
        if (cur->left.size() == 0) {
            // Base case: find one
            if (records_s2.find(cur->result) != records_s2.end()) {
                return true;
            }
        }
        else {
            for (int i = 0; i < cur->left.size(); i++) {
                // choose left[i]
                cur->result += cur->left[i];
                cur->left = cur->left.substr(0, i) + cur->left.substr(i+1);
                // recursion
                buffer.push(new PermutationState(cur->left, cur->result));
                // unchoose left[i]
                cur->left = cur->left.substr(0, i) + *cur->result.rbegin() + cur->left.substr(i);
                cur->result.pop_back();
            }
        }
        buffer.pop();
        delete cur;
    }

    return false;
}
```

But, there is a problem here that enumerating all permutation is a time-consuming task! If the length of `s1` is 10, then the number of permutations of `s1` is `10!`, which is gigantic.

Obviously, brute force will result in TLE (Time Limit Error). Think of something else.

How will you check whether one string is a permutation of another string? One way is to sort the string and then compare. But, Is there a better way? If one string is a permutation of another string then they must one common metric. What is that? Both strings must have same *character frequencies*, if one is permutation of another. Which data structure should be used to store frequencies?

There are two ways to check if two strings have the same character frequency.

- hashcode

We will hit it in a method sort of like encryptic algorithm. We will predefined a private key, and calculate each substring. If any substring has the same encrypted code, then they have the same characters without taking order into consideration.

```c++
/**
 * ex> private key:  a: 2,  b: 77, c: 193, o: 1001
 *     s1: ab  =>  1 * 2 + 1 * b = 79
 *     s2: aabacooc:  aa(4), ab(79), ba(79), ac(195), co(1194), oo(2002), oc(1194)
 */
```

By comparing encrypted code, we are able to check if two strings have the same character frequency.

```c++
/**
 *     How to calcualte encrypted code of substrings efficiently?
 *     s2: a  a  b  a  c  o  o  c
 *         ^     ^
 *        begin end (code = 4)
 *
 */
```

As window slides from left to right, we only need subtract the value of the frist character and add the value of the last character. In such way we are able to avoid repeating calculations.

```c++
bool checkInclusion_sol4(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    unordered_map<char, int> privateKey = {
        {'a', 2}, {'b', 77}, {'c', 56}, {'d', 101}, {'e', 89}, {'f', 54},
        {'g', 171}, {'h', 133}, {'i', 179}, {'j', 203}, {'k', 301}, {'l', 111},
        {'m', 511}, {'n', 607}, {'o', 1021}, {'p', 1891}, {'q', 1099}, {'r', 1999},
        {'s', 2117}, {'t', 2738}, {'u', 2919}, {'v', 3113}, {'w', 3573}, {'x', 4011},
        {'y', 4193}, {'z', 5111}
    };

    int code_s1 = 0;
    for (char ch : s1) {
        code_s1 += privateKey[ch];
    }

    int begin = 0;
    int end = s1.size();
    int code_s2 = 0;
    for (int i = begin; i < end; i++) {
        code_s2 += privateKey[s2[i]];
    }
    while (end <= s2.size()) {
        if (code_s2 == code_s1) {
            return true;
        }

        code_s2 -= privateKey[s2[begin]];
        begin++;
        code_s2 += privateKey[s2[end]];
        end++;
    }

    return false;
}
```

- map (vector to simulate)

Solution 5 will use hashmap (or vector) to record the frequency of characters in the window. The idea is similar to that above. Also, we will use `numOfMatch` to count the number of characters whose frequency matches in both strings.

```c++
bool checkInclusion_sol5(string s1, string s2) {
    if (s2.size() < s1.size()) return false;

    const int SIZE_OF_CHARACTERS = 26;
    vector<int> s1map(SIZE_OF_CHARACTERS);
    vector<int> s2map(SIZE_OF_CHARACTERS);
    for (int i = 0; i < s1.size(); i++) {
        s1map[s1[i] - 'a']++;
        s2map[s2[i] - 'a']++;
    }

    int numOfMatch = 0;
    for (int i = 0; i < SIZE_OF_CHARACTERS; i++) {
        if (s1map[i] == s2map[i]) {
            numOfMatch++;
        }
    }

    // TODO: slide window and update numOfMatch
    int begin = 0;
    int end = s1.size();
    while (end <= s2.size()) {
        if (numOfMatch == SIZE_OF_CHARACTERS) {
            return true;
        }
        // TODO: dequeue (en-window)
        if (s1map[s2[begin] - 'a'] == s2map[s2[begin] - 'a']) {
            // if character is match before
            numOfMatch--;
        }
        else {
            if (s1map[s2[begin] - 'a'] == s2map[s2[begin] - 'a'] - 1) {
                // whether match if begin character subtract 1, that's what will happen.
                numOfMatch++;
            }
        }
        s2map[s2[begin] - 'a']--;
        begin++;
        // TODO: enqueue (de-window)
        if (s1map[s2[end] - 'a'] == s2map[s2[end] - 'a']) {
            // if character is match before
            numOfMatch--;
        }
        else {
            if (s1map[s2[end] - 'a'] == s2map[s2[end] - 'a'] + 1) {
                // whether match if end character add 1.
                numOfMatch++;
            }
        }
        s2map[s2[end] - 'a']++;
        end++;
    }

    return false;
}
```

Tricks:

- map: when key is able to be mapped as consecutive integer, we are able to use vector to simulate a map.
- recursion: queue can be used to simulate 'BFS' recursion, and stack used to simulate 'DFS'.
- Standard Template Library (STL): learn to how to utilize some useful function in STL, such as `sort(it_begin, it_end)`.

## BFS and DFS

### Flood Fill

> An image is represented by an `m x n` integer grid image where `image[i][j]` represents the pixel value of the image.
> You are also given three integers `sr`, `sc`, and `newColor`. You should perform a flood fill on the image starting from the pixel `image[sr][sc]`.
> To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with `newColor`.
> Return the modified image after performing the flood fill.
>
> Constrains: m == image.length. n == image[i].length. 1 <= m, n <= 50. 0 <= image[i][j], newColor < 216. 0 <= sr < m. 0 <= sc < n.

The aim to put the answer for this problem here is to show how to use `queue` to simulate BFS.

- Recursion

```c++
void floodFillHelper1(vector< vector<int> >& image, vector< vector<int> >& visited,
                      int sr, int sc, int& sourceVal, int& newColor) {
    if ((sr >= 0) && (sr < image.size()) &&
        (sc >= 0) && (sc < image[0].size()) &&
        (image[sr][sc] == sourceVal) &&
        (visited[sr][sc] == 0)) {
        image[sr][sc] = newColor;
        visited[sr][sc] = 1;

        floodFillHelper1(image, visited, sr - 1, sc, sourceVal, newColor); // up
        floodFillHelper1(image, visited, sr + 1, sc, sourceVal, newColor); // down
        floodFillHelper1(image, visited, sr, sc - 1, sourceVal, newColor); // left
        floodFillHelper1(image, visited, sr, sc + 1, sourceVal, newColor); // right
    }
}

vector< vector<int> > floodFill_sol1(vector< vector<int> >& image, int sr, int sc, int newColor) {
    int sourceVal = image[sr][sc];
    int newVal = newColor;
    if (sourceVal == newVal) return image;
    vector< vector<int> > visited(image.size(), vector<int>(image[0].size(), 0));

    floodFillHelper1(image, visited, sr, sc, sourceVal, newVal);

    return image;
}
```

- Queue Simulation

```c++
vector<vector<int>> floodFill_sol2(vector<vector<int>>& image,
                                   int sr, int sc, int newColor) {
    class QueueState {
    public:
        int sr; int sc;
        QueueState(int sr, int sc) {
            this->sr = sr;
            this->sc = sc;
        }
    };

    int sourceVal = image[sr][sc];
    if (sourceVal == newColor) return image;
    vector< vector<int> > visited(image.size(), vector<int>(image[0].size(), 0));

    queue<QueueState> buffer;
    buffer.push(QueueState(sr, sc));
    while (!buffer.empty()) {
        QueueState cur = buffer.front();
        buffer.pop();
        if ((cur.sr >= 0) && (cur.sr < image.size()) &&
            (cur.sc >= 0) && (cur.sc < image[0].size()) &&
            (image[cur.sr][cur.sc] == sourceVal) &&
            (visited[cur.sr][cur.sc] == 0)) {
                image[cur.sr][cur.sc] = newColor;
                visited[cur.sr][cur.sc] = 1;

                buffer.push(QueueState(cur.sr + 1, cur.sc));
                buffer.push(QueueState(cur.sr - 1, cur.sc));
                buffer.push(QueueState(cur.sr, cur.sc - 1));
                buffer.push(QueueState(cur.sr, cur.sc + 1));
            }
    }
    return image;
}
```

Using `queue` instead of recursion brings many benefits, among which the most obvious one is we do not need to pass 'global' variables, improving resulting performance.

Tricks:

- How to initialize vector of vector: `vector< vector<int> > visited(image.size(), vector<int>(image[0].size(), 0))`
- Treat two dimensional vector as a vector of vector: row number = `image.size()`, col number = `image[0].size()`.

### Max Area of Island

> You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
> The area of an island is the number of cells with a value 1 in the island.
> Return the maximum area of an island in grid. If there is no island, return 0.
>
> Constrains: m == grid.length. n == grid[i].length. 1 <= m, n <= 50. `grid[i][j]` is either 0 or 1

Imagine we are a band of people who are going to travel all over the world. We are trying to find new island. What should we do?

1. Traverse from a starting point in raster order.
2. If I step on to a new island (find a new 1). Then I will explore on the island and tag all the area I have left my steps. Record the area of the island. (DFS or BFS)
3. Go back to where I step on to the island, and start my sea travel until find a new island.

If I have gone to all the area of the world, then there you go. We got the maximum area of island.

```c++
void exploreIsland(vector< vector<int> >& grid, vector< vector<int> >& visited, int row, int col, int& area) {
    if ((row >= 0) && (row < grid.size()) &&
        (col >= 0) && (col < grid[0].size()) &&
        (grid[row][col] == 1) && (visited[row][col] == 0)) {
        visited[row][col] = 1;
        area++;
        exploreIsland(grid, visited, row - 1, col, area);
        exploreIsland(grid, visited, row + 1, col, area);
        exploreIsland(grid, visited, row, col - 1, area);
        exploreIsland(grid, visited, row, col + 1, area);
    }
}

int maxAreaOfIsland_sol1(vector< vector<int> >& grid) {
    int maxIsland = 0;
    vector< vector<int> > visited(grid.size(), vector<int>(grid[0].size(), 0));
    // TODO: start to travel
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if ((grid[i][j] == 1) && (visited[i][j] == 0)) {
                int area = 0;
                exploreIsland(grid, visited, i, j, area);
                if (area > maxIsland) {
                    maxIsland = area;
                }
            }
        }
    }

    return maxIsland;
}
```

Tricks:

- `visited[]` in case of deadlock.

### Merge Trees

> You are given two binary trees root1 and root2.
> 
> Imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge the two trees into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of the new tree.
>
> Return the merged tree.
>
> Constrains: The number of nodes in both trees is in the range [0, 2000]. -10^4 <= Node.val <= 10^4.

The key to solve problem is how to traverse two trees in parallel.

- if root1 is nullptr, then then combined subtree will be replaced by root2, and vice versa.
- if root1 and root2 both are non-nullptr, then add values up and traverse concurrently left and right subtrees.

```c++
TreeNode* mergeTrees_sol2(TreeNode* root1, TreeNode* root2) {
    if (root1 == nullptr) {
        return root2;
    }
    if (root2 == nullptr) {
        return root1;
    }

    root1->val += root2->val;
    root1->left = mergeTrees_sol2(root1->left, root2->left);
    root1->right = mergeTrees_sol2(root1->right, root2->right);

    return root1;
}
```

Tricks:

- The following algorithm for constructing tree from the result of traverse in level order only WORKS for COMPLETE binary tree.

```c++
TreeNode* constructTreeInLevelOrder(TreeNode* root, const vector<int>& res, int i) {
    static int NULL_VAL = 10001;
    // TODO: if there is possible node, then update node.
    if ((i < res.size()) && (res[i] != NULL_VAL)) {
        root = new TreeNode(res[i]);
        root->left = constructTreeInLevelOrder(root->left, res, 2 * i + 1);
        root->right = constructTreeInLevelOrder(root->right, res, 2 * i + 2);
    }

    return root;
}
```

### Connect Tree

> You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition.
> Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
> Initially, all next pointers are set to NULL.

```c++
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```

> Constrains: The number of nodes in the tree is in the range [0, 212 - 1]. -1000 <= Node.val <= 1000.

There are two ways to solve the problem.

- BFS

```
Node* connect_sol2(Node* root) {
    class QueueNode {
    public:
        int level;
        Node* node;

        QueueNode(int level, Node* node) : level(level), node(node) {}
    };

    queue<QueueNode> que;
    if (root == nullptr) return root;
    que.push(QueueNode(0, root));
    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();
        QueueNode next = que.front();
        if (cur.level == next.level) {
            cur.node->next = next.node;
        }
        if (cur.node->left != nullptr) {
            que.push(QueueNode(cur.level + 1, cur.node->left));
        }
        if (cur.node->right != nullptr) {
            que.push(QueueNode(cur.level + 1, cur.node->right));
        }
    }

    return root;
}
```

- Recursion: connect subtrees

The key here is that we need to connect the right edge of left subtree to the left edge of right subtree.

```c++
Node* connect_sol1(Node* root) {
    if ((root != nullptr) && (root->left != nullptr)) {
        // TODO: connect my left subtree's right edge to my right subtree's left edge
        Node* leftSubTree = root->left;
        Node* rightSubTree = root->right;
        while ((leftSubTree != nullptr) &&
               (rightSubTree != nullptr)) {
            leftSubTree->next = rightSubTree;
            leftSubTree = leftSubTree->right;
            rightSubTree = rightSubTree->left;
        }

        root->left = connect_sol1(root->left);
        root->right = connect_sol1(root->right);
    }

    return root;
}
```

Tricks:

- Think of tree problems from different perspectives, both node and subtree. From node, we consider the connection between levels. We take into consideration recursion from subtree perspective.

### Update Matrix

> Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
> 
> The distance between two adjacent cells is 1.
> 
> Constrains: m == mat.length. n == mat[i].length. 1 <= m, n <= 10^4. 1 <= m * n <= 10^4. mat[i][j] is either 0 or 1. There is at least one 0 in mat.

There are two ways to solve the problem:

- BFS and Greedy Algorithm

Use a queue to store cells that can be used to update their neighbors, sort of like Dijkstra Algorithm.
```c++
vector< vector<int> > updateMatrix_sol2(vector< vector<int> >& mat) {
    class QueueState {
    public:
        int i;
        int j;
        QueueState(int row, int col) : i(row), j(col) {};
    };
    queue<QueueState> que;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            if (mat[i][j] == 0) {
                que.push(QueueState(i, j));
            }
            else {
                mat[i][j] = INT_MAX;
            }
        }
    }

    int shorter = 0;
    while (!que.empty()) {
        QueueState cur = que.front();
        que.pop();
        // TODO: try to update my neighbors
        shorter = mat[cur.i][cur.j] + 1;
        if ((cur.i + 1 < mat.size()) && (shorter < mat[cur.i+1][cur.j])) {
            mat[cur.i+1][cur.j] = shorter;
            que.push(QueueState(cur.i+1, cur.j));
        }
        if ((cur.i - 1 >= 0) && (shorter < mat[cur.i-1][cur.j])) {
            mat[cur.i-1][cur.j] = shorter;
            que.push(QueueState(cur.i-1, cur.j));
        }
        if ((cur.j + 1 < mat[0].size()) && (shorter < mat[cur.i][cur.j+1])) {
            mat[cur.i][cur.j+1] = shorter;
            que.push(QueueState(cur.i, cur.j+1));
        }
        if ((cur.j - 1 >= 0) && (shorter < mat[cur.i][cur.j-1])) {
            mat[cur.i][cur.j-1] = shorter;
            que.push(QueueState(cur.i, cur.j-1));
        }
    }

    return mat;
}
```

- Dynamic Programming

One important fact: the shortest path to 0 will hit two possibles

- `mat[i][j]` is 0 itself.
- `mat[i][j]` has a shortest path passing one of its 4-dimentional neighbors. Thereby, `dist[i][j] = min(d[i][j], d[i-1][j] + 1, d[i][j-1] + 1, d[i+1][j] + 1, d[i-1][j] +1)`.

And one property: left-top dependency and right-bottom dependency.

```c++
vector< vector<int> > updateMatrix_sol3(vector< vector<int> >& mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    if (rows == 0) return mat;
    int MAX_VAL = 10001;
    vector< vector<int> > dist(rows, vector<int>(cols, MAX_VAL));

    // TODO: check for left and top
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == 0) {
                dist[i][j] = 0;
            }
            else {
                if (i > 0) {
                    dist[i][j] = min(dist[i][j], dist[i-1][j] + 1);
                }
                if (j > 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j-1] + 1);
                }
            }
        }
    }

    // TODO: check for right and bottom
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 0; j--) {
            if (i + 1 < rows) {
                dist[i][j] = min(dist[i][j], dist[i+1][j] + 1);
            }
            if (j + 1 < cols) {
                dist[i][j] = min(dist[i][j], dist[i][j+1] + 1);
            }
        }
    }

    return dist;
}
```

Tricks:

- Making use of surrounding information.

## Recursion and Backtracking

### Reverse LinkList

> Given the head of a singly linked list, reverse the list, and return the reversed list.
> 
> Constrains: The number of nodes in the list is the range [0, 5000]. -5000 <= Node.val <= 5000.

The purpose of this problem is to give us an intuition on how recursion is used to solve problem. Keep in mind that it includes two stages, go down deeply and back up.

Recursion has a function sort of like "Hey, let me take a break, and do things after me first.". Figure out what the return value means in the recursion process.

```c++
ListNode* reverseList_sol3(ListNode* head) {
    if ((head == nullptr) || (head->next == nullptr)) {
        return head;
    }

    // TODO: reverse the rest
    ListNode* newHead = reverseList_sol3(head->next);

    // TODO: reverse myself
    ListNode* nextNode = head->next;
    nextNode->next = head;
    head->next = nullptr;

    return newHead;
}
```

### Merge Two Sorted LinkList

> Merge two sorted linked lists and return it as a sorted list. The list should be made by splicing together the nodes of the first two lists.
>
> Constrains: The number of nodes in both lists is in the range [0, 50]. -100 <= Node.val <= 100. Both l1 and l2 are sorted in non-decreasing order.

The aim of the problem is to show how clean the recursion algorithm is and how to use it to solve problem recursively that has similar structure.

```c++
ListNode* mergeTwoLists_sol2(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    if (l1->val <= l2->val) {
        return new ListNode(l1->val, mergeTwoLists_sol2(l1->next, l2));
    }
    else {
        return new ListNode(l2->val, mergeTwoLists_sol2(l1, l2->next));
    }
}
```

### Combination

> Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].
>
> Constrains: 1 <= n <= 20. 1 <= k <= n.

```c++
void combineHelper(int n, int k, vector<int>& selected, vector< vector<int> >& result) {
    if (n < k) return;
    if (k == 0) {
        result.push_back(selected);
        return;
    }

    // TODO: choose and unchoose
    // not choose
    combineHelper(n - 1, k, selected, result);
    // choose
    selected.push_back(n);
    combineHelper(n - 1, k - 1, selected, result);
    selected.pop_back();
}
```

### Permutation

> Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
>
> 1 <= nums.length <= 6. -10 <= nums[i] <= 10. All the integers of nums are unique.

```c++
void permuteHelper(vector<int>& choices, vector<int>& selected,
                   vector< vector<int> >& result) {
    if (choices.empty()) {
        result.push_back(selected);
        return;
    }

    int selectedNum = 0;
    for (int i = 0; i < choices.size(); i++) {
        // choose
        selectedNum = choices[i];
        choices.erase(choices.begin() + i);
        selected.push_back(selectedNum);
        permuteHelper(choices, selected, result);
        // unchoose
        choices.insert(choices.begin() + i, selectedNum);
        selected.pop_back();
    }
}
```

### Letter Case Permutation

> Given a string s, we can transform every letter individually to be lowercase or uppercase to create another string.
>
> Return a list of all possible strings we could create.
>
> s will be a string with length between 1 and 12. s will consist only of letters or digits.

Combinations, permutations and its variant like this problem are paradigm for this kind of problem. Notice that we have to keep some environment variable unchanged in same level of recursion, meaning `choose` and restore environment by `unchoose`.

```c++
void letterCasePermutationHelper(string& s, string& soFar, vector<string>& result) {
    if (s.length() == 0) {
        result.push_back(soFar);
        return;
    }

    char cur = s[0];
    s = s.substr(1);
    if (isdigit(cur)) {
        soFar.push_back(cur);
        letterCasePermutationHelper(s, soFar, result);
        soFar.pop_back();
    }
    else {
        // current character is not digit, two choises: toupper or tolower
        // choose to upper
        soFar.push_back(toupper(cur));
        letterCasePermutationHelper(s, soFar, result);
        soFar.pop_back();
        // choose to lower
        soFar.push_back(tolower(cur));
        letterCasePermutationHelper(s, soFar, result);
        soFar.pop_back();
    }
    s.insert(s.begin(), cur);
    return;
}
```

Tricks:

- `vector.erase(iter)`: delete v[1] is same as `v.erase(iter + 1)`.
- `string.substr(start, number)`: s.str(1) means get rid of the first character from the string.

