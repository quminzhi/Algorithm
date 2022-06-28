# Code of LeetCode

## 1 to 10

## 11 to 20

## 21 to 30

## 31 to 40

```c++
class Solution {
public:
    /*
        1 2 3 4 5 => 1 2 3 5 4
        1 2 3 6 5 => 1 2 5 3 6
        1 2 7 6 5 => 1 5 2 6 7
        
        5 4 3 2 1 => 1 2 3 4 5
        1 2 3 4 5 5 5 => 1 2 3 5 4 5 5 => 1 2 3 5 5 4 5 => 1 2 3 5 5 5 4
        
        1. from the last, find the first descending number (idx = k)
        2. swap this number with the first one greater than it
        3. rearrange all numbers after k in ascending order. (all numbers after k should be in descending order, just reverse them). 
    */
    void nextPermutation(vector<int>& nums) {
        const int n = nums.size();
        int k = n - 1;
        // k > 0 means there is a number before it
        while (k > 0 && nums[k - 1] >= nums[k]) k--;  // target is nums[k - 1]
        if (k == 0) {
            reverse(nums.begin(), nums.end());
        } else {
            int t = k;
            while (t < n && nums[t] > nums[k - 1]) t++;  // nums[t - 1] is the first number greater than nums[k - 1]
            swap(nums[k - 1], nums[t - 1]);
            reverse(nums.begin() + k, nums.end());
        }
    }
};
```

```c++
class Solution {
public:
    /*
              each prefix in the interval: # of left >= # of right
        -----|----------------------------------------------|----------
            ^
           start
           
        start points to the index before the first element of the interval
    */
    int longestValidParentheses(string s) {
        stack<int> stk;
        
        int res = 0;
        for (int i = 0, start = -1; i < s.size(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                if (!stk.empty()) {
                    stk.pop();
                    if (!stk.empty()) {
                        // ex> (  ( ) ( )
                        //    top j     i
                        // top is the idx of the first opening parentheses that has not matched so far
                        res = max(res, i - (stk.top() + 1) + 1);
                    } else {
                        // such top does not exist, every parentheses matches
                        res = max(res, i - start);
                    }
                } else {
                    // go to next interval
                    start = i;
                }
            }
        }
        
        return res;
    }
};
```

```c++
class Solution {
public:
    /*
        4. 5. 6. 7. 0. 1. 2
              ^
             mid
        if nums[mid] is greater than or equal to nums[left], [left, mid] is ordered
        
        4. 5. 6. 7. 0. 1. 2
                       ^
                      mid
        if nums[mid] is less than nums[left], [mid, right] is ordered
    */
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = l + ((r - l) >> 1);
            if (nums[mid] == target) return mid;
            else if (nums[l] == target) return l;
            else {
                if (nums[mid] < nums[l]) {
                    if (nums[mid] < target && target < nums[l]) {
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                } else {
                    if (nums[mid] > target && target > nums[l]) {
                        r = mid - 1;    
                    } else {
                        l = mid + 1;
                    }
                }
            }
        }
        
        return -1;
    }
};
```

```c++
class Solution {
public:
    /*
        greater or equal
        
                 /        
          o-----o
         /
        /
 < target | >= target
        
        
        less or equal
        
                 /        
          o-----o
         /
        /
      <= target | > target
    */
    vector<int> searchRange(vector<int>& nums, int target) {
        const int n = nums.size();
        vector<int> res;
        res.push_back(GreaterOrEqual(nums, target));
        res.push_back(LessOrEqual(nums, target));
        return res;
    }
    
private:
    
    int GreaterOrEqual(vector<int>& nums, int target) {
        if (nums.size() == 0) return -1;
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = l + ((r - l) >> 1);
            if (nums[mid] >= target) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        
        if (nums[l] != target) return -1;
        return l;
    }
    
    int LessOrEqual(vector<int>& nums, int target) {
        if (nums.size() == 0) return -1;
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = l + ((r - l + 1) >> 1);
            if (nums[mid] <= target) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        
        if (nums[l] != target) return -1;
        return l;
    }
};
```

```c++
class Solution {
public:
    /*
        find the index of first number greater or equal than target

        HINT: let r be nums.size(), mid is less than nums.size() since we round down when make division.
    */
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size();
        while (l < r) {
            int mid = l + ((r - l) >> 1);   // floor => so, mid < nums.size()
            if (nums[mid] >= target) {
                r = mid;    
            } else {
                l = mid + 1;
            }
        }
        
        return l;
    }
};
```

```c++
class Solution {
public:
    /*
        index control
    */
    bool isValidSudoku(vector<vector<char>>& board) {
        bool st[10];
        const int m = board.size(), n = board[0].size();
        // check row
        for (int i = 0; i < m; i++) {
            memset(st, false, sizeof st);
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') continue;
                int t = board[i][j] - '0';
                if (st[t]) return false;
                st[t] = true;
            }
        }
        
        // check column
        for (int j = 0; j < n; j++) {
            memset(st, false, sizeof st);
            for (int i = 0; i < m; i++) {
                if (board[i][j] == '.') continue;
                int t = board[i][j] - '0';
                if (st[t]) return false;
                st[t] = true;
            }
        }
        
        // check 3 x 3 block: enumerate top left cell of each block
        for (int i = 0; i < m; i += 3) {
            for (int j = 0; j < n; j += 3) {
                memset(st, false, sizeof st);
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        if (board[i + x][j + y] == '.') continue;
                        int t = board[i + x][j + y] - '0';
                        if (st[t]) return false;
                        st[t] = true;
                    }
                }
            }
        }
        
        return true;
    }
};
```

```c++
class Solution {
public:
    /*
        simulation
    */
    const int n = 9;
    bool row[9][10], col[9][10], block[3][3][10]; // 10: 0 ~ 9
    
    void solveSudoku(vector<vector<char>>& board) {
        memset(row, false, sizeof row);
        memset(col, false, sizeof col);
        memset(block, false, sizeof block);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != '.') {
                    int t = board[i][j] - '0';
                    row[i][t] = col[j][t] = block[i / 3][j / 3][t] = true;
                }
            }
        }
        
        sudokuHelper(board, 0, 0);
    }

private:
    bool sudokuHelper(vector<vector<char>>& board, int x, int y) {
        if (y == n) x++, y = 0;
        if (x == n) return true;
        
        if (board[x][y] != '.') return sudokuHelper(board, x, y + 1);
        
        for (int i = 1; i <= n; i++) {
            if (!row[x][i] && !col[y][i] && !block[x / 3][y / 3][i]) {
                board[x][y] = i + '0';
                row[x][i] = col[y][i] = block[x / 3][y / 3][i] = true;
                if (sudokuHelper(board, x, y + 1)) return true;
                board[x][y] = '.';
                row[x][i] = col[y][i] = block[x / 3][y / 3][i] = false;
            }
        }
        
        return false;
    }
};
```

```c++
class Solution {
public:
    /*
        simulation:
        
        3 3 2 2 2 5 1
        j   k  
    */
    string countAndSay(int n) {
        string s = "1";
        // iterate n - 1 time
        for (int i = 0; i < n - 1; i++) {
            string t;
            for (int j = 0; j < s.size();) {
                int k = j + 1;
                while (k < s.size() && s[k] == s[j]) k++;
                t += to_string(k - j) + s[j];
                j = k;
            }
            s = t;
        }
        
        return s;
    }
};
```

```c++
class Solution {
public:
    /*
        if we want to get detailed result, recursion is better.
        if the number of solution is required, dynamic programming is better.
    */
    vector<vector<int>> res;
    vector<int> path;

    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        sumHelper(nums, 0, target);
        return res;
    }
    
private:
    void sumHelper(vector<int>& nums, int i, int target) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        if (i >= nums.size()) return;
        
        for (int j = 0; j * nums[i] <= target; j++) {
            sumHelper(nums, i + 1, target - j * nums[i]);
            path.push_back(nums[i]);   // one solution tree to another solution tree
        }
        
        for (int j = 0; j * nums[i] <= target; j++) {
            path.pop_back();
        }
    }
};
```

```c++
class Solution {
public:
    /*
        sort and dfs
    */
    vector<vector<int>> res;
    vector<int> path;
    
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        sumHelper(nums, 0, target);
        
        return res;
    }
    
private:
    void sumHelper(vector<int>& nums, int i, int target) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        
        if (i >= nums.size()) return;
        
        // find consecutive same numbers
        int k = i + 1;
        while (k < nums.size() && nums[k] == nums[k - 1]) k++;
        int sz = k - i;
        // we can select at most 'min(sz, target / nums[i])' nums[i]
        int limit = min(sz, target / nums[i]);
        
        for (int j = 0; j <= limit; j++) {
            sumHelper(nums, k, target - j * nums[i]);
            path.push_back(nums[i]);
        }
        
        for (int j = 0; j <= limit; j++) {
            path.pop_back();
        }
    }
};
```

## 41 to 50