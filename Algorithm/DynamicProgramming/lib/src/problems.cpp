#include "problems.hpp"

#include <iostream>

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
                       vector<vector<int> >& f, int begin, int i) {
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
    vector<vector<int> > f(multipliers.size(), vector<int>(multipliers.size(), -1e4));
    int result = maximumScoreHelper(nums, multipliers, f, 0, 0);
    return result;
}

/**
 * @brief return the area of maximal square
 *
 * @param matrix
 * @return int
 */
int maximalSquare(vector<vector<char> >& matrix) {
    vector<vector<int> > f(matrix.size() + 1,
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

    vector<vector<int> > f(d, vector<int>(jobDifficulty.size(), 1e6));

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