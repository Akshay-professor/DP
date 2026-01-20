// 322. Coin Change
// Solved
// Medium
// Topics
// premium lock icon
// Companies
// You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

// Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

// You may assume that you have an infinite number of each kind of coin.

 

// Example 1:

// Input: coins = [1,2,5], amount = 11
// Output: 3
// Explanation: 11 = 5 + 5 + 1
// Example 2:

// Input: coins = [2], amount = 3
// Output: -1
// Example 3:

// Input: coins = [1], amount = 0
// Output: 0
 

// Constraints:

// 1 <= coins.length <= 12
// 1 <= coins[i] <= 231 - 1
// 0 <= amount <= 104

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = amount;
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        if (n == 0) {
            return 0;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < coins.size(); j++) {
                if (i >= coins[j]) {
                    if (dp[i - coins[j]] != INT_MAX){
                        dp[i] = min(dp[i], dp[i - coins[j]]+1);
                    }
                }
            }
        }
        if (dp[n] == INT_MAX) {
            return -1;
        }
        return dp[n];
    }
};

279. Perfect Squares
Solved
Medium
Topics
premium lock icon
Companies
Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

 

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
 

Constraints:

1 <= n <= 104

class Solution {
public:
    int numSquares(int n) {
        vector<int> squares;
        for(int i = 1; i*i <= n; i++){
            squares.push_back(i*i);
        }

        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;

        for(int i = 1; i <= n; i++){
            for(int j = 0; j < squares.size(); j++){
                if(i >= squares[j]){
                    dp[i] = min(dp[i], dp[i - squares[j]] + 1);
                }
            }
        }

        return dp[n];
    }
};
