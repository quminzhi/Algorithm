#include "problems.hpp"

#include <iostream>
#include <unordered_map>

/**
 * @brief return the maximum value we can rob from a sequence of houses.
 *
 * @param nums
 * @return int
 */
int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    if (nums.size() == 2) return max(nums[0], nums[1]);
    vector<int> f(nums.size(), 0);
    // base case
    f[0] = nums[0];
    f[1] = max(nums[0], nums[1]);
    // deduction
    for (int i = 2; i < nums.size(); i++) {
        f[i] = max(f[i - 1], f[i - 2] + nums[i]);
    }

    return f[nums.size() - 1];
}

/**
 * @brief f[i] = min(f[i-1] + cost[i-1], f[i-2] + cost[i-2])
 *
 * cost:  0  1  2  3  4  (5 top)
 *        1 100 2  1  22  ans
 *
 * top index is cost.size() + 1.
 *
 * @param cost
 * @return int
 */
int minCostClimbingStairs(vector<int>& cost) {
    if (cost.size() < 2) return 0;
    int top_idx = cost.size() + 1;
    vector<int> f(top_idx, 1e4);

    // base case: either start from 0th or 1th step
    f[0] = 0;
    f[1] = 0;
    // deduction
    for (int i = 2; i < top_idx; i++) {
        f[i] = min(f[i - 1] + cost[i - 1], f[i - 2] + cost[i - 2]);
    }

    return f[top_idx - 1];
}

/**
 * @brief f[i] = f[i-3] + f[i-2] + f[i-1]
 *
 * @param n
 * @return int
 */
int tribonacci(int n) {
    if (n == 0) return 0;
    if (n < 3) return 1;
    int max_n = 37;
    vector<int> f(max_n + 1, 0);
    f[1] = 1;
    f[2] = 1;
    for (int i = 3; i <= n; i++) {
        f[i] = f[i - 3] + f[i - 2] + f[i - 1];
    }

    return f[n];
}

/**
 * @brief return the maximum points earned.
 *
 * f[i] = max(f[i-2] + earned[i], f[i-1]
 *
 * @param nums
 * @return int
 */
int deleteAndEarn(vector<int>& nums) {
    vector<int> earned(1e4 + 10, 0);   // maximum of nums[i] <= 10^4
    sort(nums.begin(), nums.end());
    int num = nums[0], cnt = 1;
    int maxVal = num;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != num) {
            earned[num] = num * cnt;
            num = nums[i];
            cnt = 1;
            // update max value
            if (nums[i] > maxVal) {
                maxVal = nums[i];
            }
        } else {
            cnt++;
        }
    }
    // add the last one
    earned[num] = num * cnt;
    if (num > maxVal) {
        maxVal = num;
    }

    // dp
    vector<int> f(earned.size(), 0);
    f[0] = earned[0];
    f[1] = max(earned[0], earned[1]);   // we can choose either 0 or 1
    for (int i = 2; i <= maxVal; i++) {
        f[i] = max(f[i - 1], f[i - 2] + earned[i]);
    }

    return f[maxVal];
}

/**
 * @brief recursively solve the problems with memorization.
 *
 * @param nums
 * @param multiplies
 * @param i: ith step.
 * @param result
 */
int maximumScoreHelper(vector<int>& nums, vector<int>& multipliers,
                       vector<vector<int>>& f, int begin, int i) {
    if (f[begin][i] != -1e4) {
        return f[begin][i];
    }

    int end = nums.size() - 1 - (i - begin);
    if (i == multipliers.size() - 1) {
        // check if it is the maximum score
        return max(nums[begin] * multipliers[i], nums[end] * multipliers[i]);
    }

    int maxVal = max(maximumScoreHelper(nums, multipliers, f, begin + 1, i + 1) +
                         nums[begin] * multipliers[i],
                     maximumScoreHelper(nums, multipliers, f, begin, i + 1) +
                         nums[end] * multipliers[i]);
    return maxVal;
}

/**
 * @brief the max score we can get.
 *
 * define memory as f[i][j]: i is begin of nums, and j means jth step of multipliers.
 *
 * the end can be calculated by nums.size() - 1 - (j - i), where 'j - i' is # of selecting
 * the end 'i' is # of selecting the begin.
 *
 * @param nums
 * @param multipliers
 * @return int
 */
int maximumScore(vector<int>& nums, vector<int>& multipliers) {
    vector<vector<int>> f(multipliers.size(), vector<int>(multipliers.size(), -1e4));
    int result = maximumScoreHelper(nums, multipliers, f, 0, 0);
    return result;
}

/**
 * @brief return the area of maximal square
 *
 * @param matrix
 * @return int
 */
int maximalSquare(vector<vector<char>>& matrix) {
    vector<vector<int>> f(matrix.size() + 1,
                          vector<int>(matrix[0].size() + 1, 0));   // 1-based

    int maxLen = 0;
    for (int i = 1; i <= matrix.size(); i++) {
        for (int j = 1; j <= matrix[0].size(); j++) {
            if (matrix[i - 1][j - 1] == '1') {
                f[i][j] = min(f[i][j - 1], f[i - 1][j]);
                f[i][j] = min(f[i][j], f[i - 1][j - 1]);
                f[i][j] += 1;
                maxLen = max(maxLen, f[i][j]);
            }
        }
    }

    return maxLen * maxLen;
}

/**
 * @brief return the minimum difficulty of job scheduling
 *
 * `f[i, j] = f[i-1, j-k] + jobDifficulty of ith day`, j >= i  is must
 *
 * how to obtain max of a specific range? track along the process
 * how to obtain sum of a specific range? prefix.
 *
 * @param jobDifficulty
 * @param d
 * @return int
 */
int minDifficulty(vector<int>& jobDifficulty, int d) {
    if (jobDifficulty.size() < d) return -1;
    if (jobDifficulty.size() == d) {
        int sum = 0;
        for (int i = 0; i < jobDifficulty.size(); i++) {
            sum += jobDifficulty[i];
        }
        return sum;
    }

    vector<vector<int>> f(d, vector<int>(jobDifficulty.size(), 1e6));

    // initialize when i = 0
    int hardest = 0;   // track hardest job from [j-k+1 to j]
    for (int j = 0; j < jobDifficulty.size(); j++) {
        hardest = max(hardest, jobDifficulty[j]);
        f[0][j] = hardest;
    }

    for (int i = 1; i < d; i++) {
        for (int j = i; j < jobDifficulty.size(); j++) {
            // select last k job for ith day
            hardest = 0;
            for (int k = 1; k <= j - i + 1; k++) {
                hardest = max(hardest, jobDifficulty[j - k + 1]);
                f[i][j] = min(f[i][j], hardest + f[i - 1][j - k]);
            }
        }
    }

    return f[d - 1][jobDifficulty.size() - 1];
}

/**
 * @brief f[i][j] = min(f[i-1][j], f[i][j-coins[i]] + 1)
 *
 * @param coins
 * @param amount
 * @return int
 */
int coinChange(vector<int>& coins, int amount) {
    vector<int> f(amount + 1, 1e5);
    f[0] = 0;

    for (int i = 0; i < coins.size(); i++) {
        for (int j = coins[i]; j <= amount; j++) {
            f[j] = min(f[j], f[j - coins[i]] + 1);   // choose
        }
    }

    int res = f[amount] == 1e5 ? -1 : f[amount];
    return res;
}

bool wordBreakHelper(const string& s, const vector<string>& wordDict, vector<bool>& memo,
                     int start) {
    if (start >= s.size()) {
        return true;
    }

    if (memo[start] == true) {
        return true;
    }

    // try all possible words
    for (int i = 0; i < wordDict.size(); i++) {
        if (s.size() - start >= wordDict[i].size() &&
            s.substr(start, wordDict[i].size()) == wordDict[i] &&
            wordBreakHelper(s, wordDict, memo, start + wordDict[i].size())) {
            memo[start] = true;
            return true;
        }
    }
    return false;
}

/**
 * @brief recursion + memo
 *
 * @param s
 * @param wordDict
 * @return true
 * @return false
 */
bool wordBreakWithMemo(string s, vector<string>& wordDict) {
    vector<bool> memo(s.size(), false);
    return wordBreakHelper(s, wordDict, memo, 0);
}

/**
 * @brief check if there is a word breakdown for s
 *
 * @param s
 * @param wordDict
 * @return true
 * @return false
 */
bool wordBreak(string s, vector<string>& wordDict) {
    vector<bool> f(s.size(), false);

    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < wordDict.size(); j++) {
            // cond:
            // 1. f[i](s[0..i]) has not found correct breakdown.
            // 2. s[0..i] with length of i + 1 has at least size of word[j].
            // 3. word[j] matches last k characters (s[k - word[i].size + 1..i]).
            if (!f[i] && i + 1 >= wordDict[j].size() &&
                // s[k..i]: i - k + 1 = word[i].size => k = i - word[i].size + 1
                s.substr(i - wordDict[j].size() + 1, wordDict[j].size()) == wordDict[j]) {
                // if (i - wordDict[j].size() >= 0) { // unsigned int overflow
                if (i - wordDict[j].size() + 1 > 0) {
                    // k > 0
                    f[i] = f[i - wordDict[j].size()];
                } else {
                    f[i] = true;
                }
            }
        }
    }

    return f[s.size() - 1];
}

/**
 * @brief f[i] = max( f[i-j] or f[i-j] + 1 if nums[i-j] == nums[i], where 0 < j < i
 *
 * @param nums
 * @return int
 */
int lengthOfLIS(vector<int>& nums) {
    vector<int> f(nums.size(), 1);

    for (int i = 0; i < nums.size(); i++) {
        for (int j = 1; j <= i; j++) {
            if (nums[i] > nums[i - j]) {
                f[i] = max(f[i], f[i - j] + 1);
            }
        }
    }

    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
        res = max(res, f[i]);
    }

    return res;
}

int maxProfitHelper(vector<vector<vector<int>>>& f, vector<vector<vector<bool>>>& visited,
                    const vector<int>& prices, int i, int j, int k) {
    if (i >= prices.size()) return 0;
    if (j <= 0) return 0;

    if (visited[i][j][k]) {
        return f[i][j][k];
    } else {
        visited[i][j][k] = true;
        if (k == 0) {
            // if we are not holding a stock: buy or not buy
            f[i][j][k] = max(maxProfitHelper(f, visited, prices, i + 1, j, 1) - prices[i],
                             maxProfitHelper(f, visited, prices, i + 1, j, 0));
        } else {
            // holding
            f[i][j][k] =
                max(maxProfitHelper(f, visited, prices, i + 1, j - 1, 0) + prices[i],
                    maxProfitHelper(f, visited, prices, i + 1, j, 1));
        }
        return f[i][j][k];
    }
}

/**
 * @brief return the best profit
 *
 * @param k
 * @param prices
 * @return int
 */
int maxProfit(int k, vector<int>& prices) {
    vector<vector<vector<int>>> f(prices.size(),
                                  vector<vector<int>>(k + 1, vector<int>(2, 0)));
    vector<vector<vector<bool>>> visited(
        prices.size(), vector<vector<bool>>(k + 1, vector<bool>(2, false)));

    return maxProfitHelper(f, visited, prices, 0, k, 0);
}

int maxProfitHelperII(vector<vector<vector<int>>>& f,
                      vector<vector<vector<bool>>>& visited, const vector<int>& prices,
                      int i, int j, int k) {
    if (i >= prices.size()) {
        return 0;
    }

    if (visited[i][j][k]) {
        return f[i][j][k];
    }

    if (k == 1) {
        f[i][j][k] = max(maxProfitHelperII(f, visited, prices, i + 1, i, 0) +
                             prices[i],   // sell and update selling day
                         maxProfitHelperII(f, visited, prices, i + 1, j, k));
    } else {
        // check if this is cooldown day if i want to buy a stock
        if (j != 0 &&
            i == j + 1) {   // if j has been updated (at least 1 trans completed)
            f[i][j][k] = maxProfitHelperII(f, visited, prices, i + 1, j, k);
        } else {
            f[i][j][k] = max(
                maxProfitHelperII(f, visited, prices, i + 1, j, 1) - prices[i],   // buy
                maxProfitHelperII(f, visited, prices, i + 1, j, k));
        }
    }

    visited[i][j][k] = true;
    return f[i][j][k];
}

/**
 * @brief different constrains compared to the last problem
 *
 * @param prices
 * @return int
 */
int maxProfit(vector<int>& prices) {
    vector<vector<vector<int>>> f(prices.size(),
                                  vector<vector<int>>(prices.size(), vector<int>(2, 0)));
    vector<vector<vector<bool>>> visited(
        prices.size(), vector<vector<bool>>(prices.size(), vector<bool>(2, false)));

    int ret = maxProfitHelperII(f, visited, prices, 0, 0, 0);

    return ret;
}

int robHelper(TreeNode2* root, bool available) {
    if (root == nullptr) {
        return 0;
    }

    if (available) {
        return max(robHelper(root->left, !available) +
                       robHelper(root->right, !available) + root->val,
                   robHelper(root->left, available) + robHelper(root->right, available));
    }

    if (!available) {
        return robHelper(root->left, !available) + robHelper(root->right, !available);
    }

    return 0;
}

/**
 * @brief define f[i, j ,k]
 *
 * @param root
 * @return int
 */
int rob(TreeNode2* root) { return max(robHelper(root, true), robHelper(root, false)); }

int minCostClimbingStairsHelper(vector<int>& f, vector<bool>& visited, vector<int>& cost,
                                int start) {
    if (start >= cost.size()) {
        return 0;
    }

    if (visited[start]) {
        return f[start];
    }

    f[start] =
        cost[start] + min(minCostClimbingStairsHelper(f, visited, cost, start + 1),
                          minCostClimbingStairsHelper(f, visited, cost, start + 2));

    return f[start];
}

/**
 * @brief return the minimum cost of climbing stairs, recursion plus memo
 *
 * @param cost
 * @return int
 */
int minCostClimbingStairsII(vector<int>& cost) {
    vector<int> f(cost.size(), 1e5);
    vector<bool> visited(cost.size(), false);
    return min(minCostClimbingStairsHelper(f, visited, cost, 0),
               minCostClimbingStairsHelper(f, visited, cost, 1));
}

/**
 * @brief dynamic programming from bottom to top
 *
 * Define f[i] as minCost from 0 to i (where i is the top).
 *
 * f[i] = min(f[i-1] + cost[i-1], f[i-2] + cost[i-2])
 *
 * @param cost
 * @return int
 */
int minCostClimbingStairsIII(vector<int>& cost) {
    vector<int> f(cost.size() + 1, 1e5);
    f[0] = f[1] = 0;
    for (int i = 2; i <= cost.size(); i++) {
        f[i] = min(f[i - 1] + cost[i - 1], f[i - 2] + cost[i - 2]);
    }

    return f[cost.size()];
}

/**
 * @brief state compression: note that f[i] only relies on f[i-1] and f[i-2], and we are
 * only concerned about the result (f[top]) rather than intermediate calculations. So we
 * can save array space with some variables.
 *
 * we can use only three variables (twosteps, onestep, top) to solve the problem
 * iteratively.
 *
 * @param cost
 * @return int
 */
int minCostClimbingStairsIV(vector<int>& cost) {
    int twosteps = 0;
    int onestep = 0;
    int top;
    for (int i = 2; i <= cost.size(); i++) {
        top = min(twosteps + cost[i - 2], onestep + cost[i - 1]);
        // update
        twosteps = onestep;
        onestep = top;
    }

    return top;
}

/**
 * @brief counting
 *
 * f[i] = (k - 1) * f[i-1] + 1 * (k - 1) * f[i-2]
 *
 * @param n
 * @param k
 * @return int
 */
int numWays(int n, int k) {
    int N_MAX = 52;
    int f[N_MAX];
    memset(f, 0, sizeof(f[0]) * N_MAX);

    f[0] = k;
    f[1] = k * k;
    for (int i = 2; i < n; i++) {
        f[i] = (k - 1) * f[i - 1] + (k - 1) * f[i - 2];
    }

    return f[n - 1];   // 0-indexed
}

/**
 * @brief f[i][j] = f[i-1][j] + f[i][j - coins[i]]
 *
 * base case: select from 0th coin, f[0][j] = j % coins[0] == 0 ? 1 : 0
 *
 * @param amount
 * @param coins
 * @return int
 */
int changeII(int amount, vector<int>& coins) {
    vector<vector<int>> f(coins.size(), vector<int>(amount + 1, 0));

    // base: don't choose is 1 choice when amount == 0
    for (int i = 0; i < coins.size(); i++) {
        f[i][0] = 1;
    }

    // preprocess 0th row for 0-index coins
    for (int j = 1; j <= amount; j++) {
        if (j % coins[0] == 0) {
            f[0][j] = 1;
        }
    }

    for (int i = 1; i < coins.size(); i++) {
        for (int j = 0; j <= amount; j++) {
            f[i][j] = f[i - 1][j];
            if (coins[i] <= j) {
                f[i][j] += f[i][j - coins[i]];
            }
        }
    }

    return f[coins.size() - 1][amount];
}

/**
 * @brief f[i][j] = f[i-1][j] + f[i][j - coins[i]]
 *
 * @param amount
 * @param coins
 * @return int
 */
int changeIII(int amount, vector<int>& coins) {
    vector<int> f(amount + 1, 0);

    // base: don't choose is 1 choice when amount == 0
    f[0] = 1;

    for (int i = 0; i < coins.size(); i++) {
        for (int j = coins[i]; j <= amount; j++) {
            f[j] += f[j - coins[i]];
        }
    }

    return f[amount];
}

/**
 * @brief f[i] = f[i-1] + f[i-2] if ch[i-1]ch[i] is a valid text to be decoded.
 *
 * @param s
 * @return int
 */
int numDecodings(string s) {
    unordered_map<string, char> key;
    for (int i = 1; i <= 26; i++) {
        key[to_string(i)] = 'A' + i - 1;
    }

    vector<int> f(s.size(), 0);
    f[0] = s[0] == '0' ? 0 : 1;   // decode on its own

    for (int i = 1; i < s.size(); i++) {
        if (s[i] != '0') {
            // when s[i] != '0', it can decode on its own
            f[i] += f[i - 1];
        }
        string comb = s.substr(i - 1, 2);
        if (key.find(comb) != key.end()) {
            if (i - 2 >= 0) {
                f[i] += f[i - 2];
            } else {
                f[i] += 1;
            }
        }

        if (s[i] == '0' && key.find(comb) == key.end()) {   // bad 0
            return 0;
        }
    }

    return f[s.size() - 1];
}

/**
 * @brief f[i] = max(nums[i], nums[i] + f[i-1])
 *
 * @param nums
 * @return int
 */
int maxSubArray(vector<int>& nums) {
    vector<int> f(nums.size(), -1e5);
    f[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        f[i] = max(nums[i], nums[i] + f[i - 1]);
    }

    int res = -1e5;
    for (int i = 0; i < nums.size(); i++) {
        res = max(res, f[i]);
    }

    return res;
}

/**
 * @brief state compression
 *
 * @param nums
 * @return int
 */
int maxSubArrayII(vector<int>& nums) {
    int pre = 0;
    int cur = 0;
    int maxSum = -1e5;
    for (int i = 0; i < nums.size(); i++) {
        cur = max(nums[i], pre + nums[i]);   // update f[i]
        maxSum = max(maxSum, cur);
        pre = cur;   // record f[i-1]
    }

    return maxSum;
}

/**
 * @brief f[i] = max(prices[i] - prices[i-1], f[i-1] - prices[i-1] + prices[i])
 *
 * @param prices
 * @return int
 */
int maxProfitI(vector<int>& prices) {
    vector<int> f(prices.size(), 0);
    f[0] = 0;
    for (int i = 1; i < prices.size(); i++) {
        f[i] = max(prices[i] - prices[i - 1], f[i - 1] - prices[i - 1] + prices[i]);
    }

    int maxVal = -1e5;
    for (int i = 0; i < prices.size(); i++) {
        maxVal = max(maxVal, f[i]);
    }

    return maxVal;
}

int maxProfitII(vector<int>& prices) {
    int pre = 0;
    int cur = 0;
    int maxVal = pre;   // assuming f[0] is the maximum
    for (int i = 1; i < prices.size(); i++) {
        cur = max(prices[i] - prices[i - 1], pre - prices[i - 1] + prices[i]);
        maxVal = max(maxVal, cur);
        pre = cur;
    }

    return maxVal;
}

/* inplace shift */
void shiftVector(vector<int>& nums, int shift) {
    // pop back and insert to the front
    for (int i = 0; i < shift; i++) {
        int t = nums[nums.size() - 1];
        nums.pop_back();
        nums.insert(nums.begin(), t);
    }
}

/**
 * @brief f[i] = max(f[i-1] + nums[i], nums[i])
 *
 * @param nums
 * @return int
 */
int maxSubarraySumCircular(vector<int>& nums) {
    int maxVal = -1e5;
    int shift = 0;
    while (shift < nums.size()) {
        shiftVector(nums, 1);
        int pre = 0;
        int cur = 0;
        for (int i = 0; i < nums.size(); i++) {
            cur = max(pre + nums[i], nums[i]);
            maxVal = max(maxVal, cur);
            pre = cur;
        }
        shift++;
    }

    return maxVal;
}

/**
 * @brief divide solution into two parts.
 *
 * @param nums
 * @return int
 */
int maxSubarraySumCircularII(vector<int>& nums) {
    int size = nums.size();

    // solution 1
    int pre = 0;
    int cur = 0;
    int maxSum = -1e5;
    for (int i = 0; i < nums.size(); i++) {
        cur = max(nums[i], pre + nums[i]);
        maxSum = max(maxSum, cur);
        pre = cur;
    }

    // solution 2
    vector<int> f(size, -1e5);   // max sum subarray in [0..i]
    f[0] = nums[0];
    int sum = nums[0];
    for (int i = 1; i < size; i++) {
        sum += nums[i];
        f[i] = max(sum, f[i - 1]);
        maxSum = max(maxSum, f[i]);
    }

    vector<int> ff(size, -1e5);   // max sum subarray in [i..last]
    ff[size - 1] = nums[size - 1];
    sum = nums[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        sum += nums[i];
        ff[i] = max(sum, ff[i + 1]);
    }

    // find the max value among solution 2
    for (int mid = 1; mid < size - 1; mid++) {
        maxSum = max(maxSum, ff[mid] + f[(mid - 1 + size) % size]);
    }

    return maxSum;
}

/**
 * @brief all unique paths from top-left corner to bottom-right corner.
 *
 * @param m
 * @param n
 * @return int
 */
int uniquePaths(int m, int n) {
    vector<vector<int>> f(m, vector<int>(n, 1));
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    }

    return f[m - 1][n - 1];
}

int uniquePathsCompressed(int m, int n) {
    vector<int> f(n, 1);
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[j] = f[j] + f[j - 1];
        }
    }

    return f[n - 1];
}