# 💰 Coin Change & Perfect Squares — DP Explained

> **LeetCode 322 & 279** | Time: O(n × k) | Space: O(n)

---

## 🪙 PROBLEM 1: COIN CHANGE (Main Focus)

### 0. 🧠 Thought Process (Before Writing DP)

Before jumping into code, let's think naturally:

**What is the goal?**  
→ Make amount `n` using **minimum number of coins**.

**What is changing each step?**  
→ The remaining amount we need to make.  
→ The number of coins used so far.

**What is fixed?**  
→ The coin denominations available.  
→ We have **infinite supply** of each coin.

**Can I build answers for small amounts first?**  
→ YES! If I know how to make `10` optimally, I can use it to make `11` (by adding a coin of value `1`).

**Can I reuse answers of smaller problems?**  
→ Absolutely! To make `11` with coins `[1,2,5]`:
- Use coin `1`: Need to make `10` first → `dp[10] + 1`
- Use coin `2`: Need to make `9` first → `dp[9] + 1`
- Use coin `5`: Need to make `6` first → `dp[6] + 1`
- Take **minimum** among all!

> 💡 **Key Insight:** Every amount depends on **smaller amounts** that are exactly one coin away. This is the essence of DP!

---

### 1. 📝 Problem Rewording

> Given coins of different denominations and a target amount, find the **fewest coins** needed to make that amount.  
> If impossible, return `-1`.

**Key Points:**
- Unlimited supply of each coin type
- Same coin can be used multiple times
- Must find **minimum** count

---

### 2. ❓ Why DP is Needed

#### Why Greedy Fails?

You might think: *"Always use the largest coin first!"*

**Counterexample:**
```
Coins: [1, 3, 4]
Amount: 6

Greedy approach:
  Pick 4 → remaining 2
  Pick 1 → remaining 1
  Pick 1 → remaining 0
  Total: 3 coins ✗

Optimal approach:
  Pick 3 → remaining 3
  Pick 3 → remaining 0
  Total: 2 coins ✓
```

Greedy gives **3 coins**, but optimal is **2 coins**!

#### Why Recursion Alone is Slow?

```
                    make(11)
            /         |         \
      make(10)    make(9)    make(6)
        /  \        /  \        /  \
  make(9) ...  make(8) make(7) ...
      |             |       |
  make(8)      make(7) make(6)
```

See how `make(9)`, `make(8)`, `make(7)`, `make(6)` appear **multiple times**?

Without memoization, we solve the same subproblems **exponentially many times**!

#### Where Overlapping Subproblems Appear?

To make amount `11`:
- Path 1: Use coin `5`, then make `6`, then make `1`
- Path 2: Use coin `1`, then make `10`, then make `5`, then make `0`

Both paths need to compute "how to make `5`" and "how to make `1`" → **Overlapping subproblems**!

---

### 3. 🎯 State Definition

```
┌─────────────────────────────────────────────────────────────┐
│  dp[x] = Minimum number of coins needed to make amount x    │
└─────────────────────────────────────────────────────────────┘
```

**In one sentence:**  
> `dp[x]` tells us the **fewest coins** required to form exactly amount `x`.

---

### 4. 🔄 Transition (Core Brain of DP)

#### The Formula:

```
dp[x] = min( dp[x - coin] + 1 )  for each coin where coin ≤ x
```

#### Visual Explanation:

```
    Amount: 11
    Coins: [1, 2, 5]
    
    ┌─────────────┐
    │   x = 11    │
    └─────────────┘
          │
    What coins can we use?
    → coins: 1, 2, 5 (all ≤ 11)
          │
    ┌─────┴─────┬─────────┐
    ▼           ▼         ▼
 11-1=10     11-2=9    11-5=6
    │           │         │
    ▼           ▼         ▼
 dp[10]      dp[9]     dp[6]
    │           │         │
    └─────┬─────┴─────────┘
          ▼
   dp[11] = 1 + min(dp[10], dp[9], dp[6])
```

#### Breaking It Down:

```
To make 11:
  
  Option 1: Use coin 1
    → Need dp[11-1] = dp[10] first
    → Total: dp[10] + 1
    
  Option 2: Use coin 2
    → Need dp[11-2] = dp[9] first
    → Total: dp[9] + 1
    
  Option 3: Use coin 5
    → Need dp[11-5] = dp[6] first
    → Total: dp[6] + 1
    
  Pick minimum among all options!
```

#### Why Minimum?

We want the **least number of coins**, so we try ALL possible last coins and pick the one giving the smallest count.

#### Why `+ 1`?

The `+1` accounts for **adding the current coin** we're using.

---

### 5. 🏁 Base Case

```
dp[0] = 0
```

**Why?**  
→ To make amount `0`, we need `0` coins!  
→ This is our starting point — no coins needed.

**Impossible Cases:**
```
dp[x] = INT_MAX  (or infinity)
```
→ If we can't make amount `x`, mark it as impossible.  
→ Later, if `dp[amount] == INT_MAX`, return `-1`.

---

### 6. 📊 Order of Computation (Tabulation Flow)

```
Fill direction: dp[0] → dp[1] → dp[2] → ... → dp[amount]
                ────────────────────────────────────────►
                      small to big
```

#### Why Small to Big?

When computing `dp[x]`, we need `dp[x - coin]`.

Since `coin ≥ 1`, we have `x - coin < x`.

So **all dependencies are already computed!**

```
Computing dp[11]:
  → needs dp[10] ✅ (already computed)
  → needs dp[9] ✅ (already computed)
  → needs dp[6] ✅ (already computed)
```

---

### 7. 🔍 Dry Run on Example

**Input:**  
```
coins = [1, 2, 5]
amount = 11
```

#### Step-by-Step DP Table:

```
Initial: dp = [0, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞]
             (amount 0 to 11)
```

#### **Building dp[1]:**
```
Coins we can use: 1 (since 2>1, 5>1)
  Use coin 1: dp[1-1] + 1 = dp[0] + 1 = 0 + 1 = 1

dp[1] = 1
```

#### **Building dp[2]:**
```
Coins we can use: 1, 2
  Use coin 1: dp[2-1] + 1 = dp[1] + 1 = 1 + 1 = 2
  Use coin 2: dp[2-2] + 1 = dp[0] + 1 = 0 + 1 = 1
  
dp[2] = min(2, 1) = 1
```

#### **Building dp[3]:**
```
Coins we can use: 1, 2
  Use coin 1: dp[3-1] + 1 = dp[2] + 1 = 1 + 1 = 2
  Use coin 2: dp[3-2] + 1 = dp[1] + 1 = 1 + 1 = 2
  
dp[3] = min(2, 2) = 2
```

#### **Building dp[4]:**
```
Coins we can use: 1, 2
  Use coin 1: dp[4-1] + 1 = dp[3] + 1 = 2 + 1 = 3
  Use coin 2: dp[4-2] + 1 = dp[2] + 1 = 1 + 1 = 2
  
dp[4] = min(3, 2) = 2
```

#### **Building dp[5]:**
```
Coins we can use: 1, 2, 5
  Use coin 1: dp[5-1] + 1 = dp[4] + 1 = 2 + 1 = 3
  Use coin 2: dp[5-2] + 1 = dp[3] + 1 = 2 + 1 = 3
  Use coin 5: dp[5-5] + 1 = dp[0] + 1 = 0 + 1 = 1
  
dp[5] = min(3, 3, 1) = 1
```

#### **Building dp[6]:**
```
Coins we can use: 1, 2, 5
  Use coin 1: dp[6-1] + 1 = dp[5] + 1 = 1 + 1 = 2
  Use coin 2: dp[6-2] + 1 = dp[4] + 1 = 2 + 1 = 3
  Use coin 5: dp[6-5] + 1 = dp[1] + 1 = 1 + 1 = 2
  
dp[6] = min(2, 3, 2) = 2
```

#### **Continuing to dp[11]:**

```
┌────────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│ Amount │ 0 │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │10 │11 │
├────────┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│ dp[i]  │ 0 │ 1 │ 1 │ 2 │ 2 │ 1 │ 2 │ 2 │ 3 │ 3 │ 2 │ 3 │
└────────┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘

For dp[11]:
  Use coin 1: dp[10] + 1 = 2 + 1 = 3
  Use coin 2: dp[9] + 1 = 3 + 1 = 4
  Use coin 5: dp[6] + 1 = 2 + 1 = 3
  
  dp[11] = min(3, 4, 3) = 3
```

#### Path Reconstruction:

```
11 ──(coin 5)──► 6 ──(coin 5)──► 1 ──(coin 1)──► 0
   step 1           step 2           step 3

Coins used: 5 + 5 + 1 = 11 ✓
Total: 3 coins
```

---

### 8. 🎁 Final Answer Meaning

```
┌─────────────────────────────────────────────────────────────┐
│  if dp[amount] == INT_MAX:                                  │
│      return -1  (impossible to make this amount)            │
│  else:                                                      │
│      return dp[amount]  (minimum coins needed)              │
└─────────────────────────────────────────────────────────────┘
```

**Why guaranteed optimal?**
- We try **every possible coin** at each step
- We use **previously computed optimal answers**
- `min()` ensures we pick the best choice

---

### 9. ⏱️ Time & Space Complexity

```
┌──────────────────────────────────────────┐
│  Time:  O(amount × coins.length)         │
│         = O(n × k)                       │
│                                          │
│  Why? For each amount from 1 to n,      │
│       we try all k coins                 │
├──────────────────────────────────────────┤
│  Space: O(amount)                        │
│         = O(n)                           │
│         for the dp array                 │
└──────────────────────────────────────────┘
```

---

### 10. 💡 One-Line Memory Trick

> **"dp[x] = 1 + best way to make (x - any coin)"**

Or even simpler:

> **"Try every coin, pick minimum"**

---

### 💻 Implementation Code (Coin Change)

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = amount;
        
        // dp[i] = minimum coins needed to make amount i
        // Initialize with INT_MAX (impossible state)
        vector<int> dp(n + 1, INT_MAX);
        
        // Base case: 0 amount needs 0 coins
        dp[0] = 0;
        
        // Edge case: amount is already 0
        if (n == 0) {
            return 0;
        }

        // Build dp table from 1 to amount
        for (int i = 1; i <= n; i++) {
            // Try every coin
            for (int j = 0; j < coins.size(); j++) {
                // Check if we can use this coin
                if (i >= coins[j]) {
                    // Check if previous state was reachable
                    if (dp[i - coins[j]] != INT_MAX) {
                        // Take minimum between current and using this coin
                        dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                    }
                }
            }
        }
        
        // If still INT_MAX, amount is impossible to make
        if (dp[n] == INT_MAX) {
            return -1;
        }
        
        return dp[n];
    }
};
```

#### 🔍 Code Walkthrough

**Key Points:**

1. **`vector<int> dp(n + 1, INT_MAX)`**  
   → Initialize all as impossible (INT_MAX)  
   → Will update only reachable amounts

2. **`dp[0] = 0`**  
   → Base case: no coins for zero amount

3. **`if (i >= coins[j])`**  
   → Only use coin if it doesn't exceed current amount  
   → Prevents accessing negative indices

4. **`if (dp[i - coins[j]] != INT_MAX)`**  
   → Critical check! Only use previous state if it's reachable  
   → Avoids integer overflow: `INT_MAX + 1` is undefined behavior

5. **`dp[i] = min(dp[i], dp[i - coins[j]] + 1)`**  
   → Compare current best with using this coin  
   → +1 for the coin we're adding

6. **`return dp[n] == INT_MAX ? -1 : dp[n]`**  
   → If still impossible, return -1  
   → Otherwise return minimum coins

---

## 🔢 PROBLEM 2: PERFECT SQUARES (Similar Pattern)

### 📝 Problem Rewording

> Given integer `n`, return the **least number of perfect square numbers** that sum to `n`.  
> Perfect squares: 1, 4, 9, 16, 25, 36, ...

**Example:**  
`n = 12` → `12 = 4 + 4 + 4` → answer: `3`

---

### 🔑 Key Insight

**This is EXACTLY the same as Coin Change!**

```
Coin Change:           Perfect Squares:
─────────────          ────────────────
Coins: [1, 2, 5]       Squares: [1, 4, 9, 16, ...]
Amount: 11             Target: 12
dp[x] = min coins      dp[x] = min squares
```

**Only difference:**  
- Coin Change: coins are given
- Perfect Squares: coins are `1², 2², 3², ...` up to `√n`

---

### 🔄 Transition Formula

```
dp[n] = min( dp[n - square] + 1 )  for each perfect square ≤ n
```

**Visual:**
```
To make 12:
  Use 1² = 1:  dp[12-1] + 1 = dp[11] + 1
  Use 2² = 4:  dp[12-4] + 1 = dp[8] + 1
  Use 3² = 9:  dp[12-9] + 1 = dp[3] + 1
  
  dp[12] = min(all options)
```

---

### 🔍 Dry Run (n = 12)

```
Squares available: [1, 4, 9] (since 4² = 16 > 12)

┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│ i  │ 0 │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │10 │11 │12│
├────┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│dp[]│ 0 │ 1 │ 2 │ 3 │ 1 │ 2 │ 3 │ 4 │ 2 │ 1 │ 2 │ 3 │ 3 │
└────┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘

dp[12]:
  Use 1: dp[11] + 1 = 3 + 1 = 4
  Use 4: dp[8] + 1 = 2 + 1 = 3 ✓ (best)
  Use 9: dp[3] + 1 = 3 + 1 = 4
  
  dp[12] = 3

Path: 12 → 8 → 4 → 0
      (use 4) (use 4) (use 4)
      = 4 + 4 + 4
```

---

### 💻 Implementation Code (Perfect Squares)

```cpp
class Solution {
public:
    int numSquares(int n) {
        // Generate all perfect squares up to n
        vector<int> squares;
        for(int i = 1; i*i <= n; i++){
            squares.push_back(i*i);
        }

        // dp[i] = minimum perfect squares needed to sum to i
        vector<int> dp(n+1, INT_MAX);
        
        // Base case: 0 needs 0 squares
        dp[0] = 0;

        // Build dp table from 1 to n
        for(int i = 1; i <= n; i++){
            // Try every perfect square
            for(int j = 0; j < squares.size(); j++){
                // Check if we can use this square
                if(i >= squares[j]){
                    // Take minimum
                    dp[i] = min(dp[i], dp[i - squares[j]] + 1);
                }
            }
        }

        return dp[n];
    }
};
```

#### 🔍 Differences from Coin Change:

1. **Generate squares dynamically:**
   ```cpp
   for(int i = 1; i*i <= n; i++){
       squares.push_back(i*i);
   }
   ```
   
2. **No need for INT_MAX check:**  
   → Since `1` is always a perfect square, every `n` is reachable!  
   → Worst case: use `1` exactly `n` times

3. **No -1 return:**  
   → Always possible to form `n`

---

## 🎨 Visual Comparison

```
┌─────────────────────────────────────────────────────┐
│           COIN CHANGE vs PERFECT SQUARES            │
├─────────────────────┬───────────────────────────────┤
│   Coin Change       │      Perfect Squares          │
├─────────────────────┼───────────────────────────────┤
│ Coins: given array  │ Squares: 1², 2², 3², ...     │
│ May not use coin 1  │ Always have square 1          │
│ Can return -1       │ Always possible               │
│ Need INT_MAX check  │ No need for check             │
│ coins.size() ≤ 12   │ squares ≈ √n                  │
└─────────────────────┴───────────────────────────────┘
```

---

## 🧩 Pattern Recognition

This is an **"Unbounded Knapsack"** or **"Minimum Ways to Reach Target"** pattern.

**Template:**
```cpp
dp[target] = min/max( dp[target - choice] + 1 ) for all valid choices
```

**Similar Problems:**
- **Coin Change II** (count ways, not minimum)
- **Combination Sum IV** (count combinations)
- **Minimum Cost For Tickets**
- **Integer Break**

---

## 🎓 Key Takeaways

### Why These Problems Are Important:

1. **Foundation for other DP problems**  
   → Understanding this helps with: Knapsack, Subset Sum, Partition problems

2. **Classic interview question**  
   → Tests understanding of DP state design and transitions

3. **Real-world applications**  
   → Currency exchange, resource allocation, optimization problems

### Common Mistakes to Avoid:

❌ **Forgetting INT_MAX check in Coin Change**
```cpp
// WRONG: Can cause overflow
dp[i] = min(dp[i], dp[i - coin] + 1);

// CORRECT: Check if reachable
if(dp[i - coin] != INT_MAX)
    dp[i] = min(dp[i], dp[i - coin] + 1);
```

❌ **Using greedy approach**
```cpp
// WRONG: Greedy doesn't work
while(amount > 0) {
    use largest coin
}
```

❌ **Wrong initialization**
```cpp
// WRONG: Should be INT_MAX, not 0
vector<int> dp(n+1, 0);
```

---

## 💡 Memory Tricks

**Coin Change:**
> "For each amount, try every coin and pick minimum"

**Perfect Squares:**
> "Same as Coin Change, but coins are perfect squares"

**Both:**
> "dp[x] = 1 + best previous state I can jump from"

---

*Happy Coding! 🚀*
