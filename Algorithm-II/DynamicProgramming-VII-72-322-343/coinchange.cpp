#include "coinchange.h"
#include <queue>
#include <testing/SimpleTest.h>

/**
 * @brief coinChange_sol1
 * @param coins
 * @param amount
 * @return
 * To find the fewest number of coins that makes up 'amount', use BFS.
 *
 * ex> {1, 2, 5}
 *
 * min_coin(11) = push(11 - 1), push(11 - 2), and push(11 - 5)
 * min_coin(10) = ...
 *
 * T: O(M^N)
 */
int coinChange_sol1(vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (coins.size() == 0) return -1;

    class QueueNode {
    public:
        int amount;
        int coin_cnt;
        QueueNode(int _amount, int _coin_cnt)
            : amount(_amount), coin_cnt(_coin_cnt) {}
    };

    queue<QueueNode> que;
    que.push(QueueNode(amount, 0));
    while (!que.empty()) {
        QueueNode cur = que.front();
        que.pop();

        if (cur.amount == 0) {
            return cur.coin_cnt;
        }

        if (cur.amount > 0) {
            for (int i = 0; i < coins.size(); i++) {
                que.push(QueueNode(cur.amount - coins[i], cur.coin_cnt + 1));
            }
        }
    }

    return -1;
}

/**
 * @brief coinChange_sol2
 * @param coins
 * @param amount
 * @return
 * How to handle it with dynamic programming, a more efficient way? Define f as:
 *
 * f(amount) is the fewest number of coins selected for making up 'amount'.
 *
 * Derivation:
 * f(amount) = min(f(amount - coins[i])) + 1, where i is in range of coins.
 *
 * Base case:
 * Initialize all with INT_MAX.
 * f(0) = 0; f(coins[i]) = 1;
 *
 * T: O(N * M), where N is amount, M is the size of coins
 */
int coinChange_sol2(vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (coins.size() == 0) return -1;

    vector<int> min_coins(amount+1, INT_MAX);
    min_coins[0] = 0;
    for (int i = 0; i < coins.size(); i++) {
        if (coins[i] < min_coins.size()) {
            min_coins[coins[i]] = 1;
        }
    }

    for (int amt = 1; amt < min_coins.size(); amt++) {
        for (int i = 0; i < coins.size(); i++) {
            if (amt >= coins[i]) {
                min_coins[amt] = min(min_coins[amt], min_coins[amt - coins[i]]);
            }
        }
        if (min_coins[amt] != INT_MAX) {
            min_coins[amt]++;
        }
    }

    if (min_coins[amount] == INT_MAX) {
        return -1;
    }

    return min_coins[amount];
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("test for sol1:") {
    vector<int> coins1 = {1, 2, 5};
    EXPECT_EQUAL(coinChange_sol1(coins1, 11), 3);

    vector<int> coins2 = {2};
    EXPECT_EQUAL(coinChange_sol1(coins2, 3), -1);
}

PROVIDED_TEST("test for sol2:") {
    vector<int> coins1 = {1, 2, 5};
    EXPECT_EQUAL(coinChange_sol2(coins1, 11), 3);

    vector<int> coins2 = {2};
    EXPECT_EQUAL(coinChange_sol2(coins2, 3), -1);
    EXPECT_EQUAL(coinChange_sol2(coins2, 1), -1);
}
