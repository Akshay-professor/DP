# 🔢 Removing Digits — DP Explained

> **CSES Problem** | Time: O(n × d) | Space: O(n)

---

## 0. 🧠 Thought Process (Before Writing DP)

Before jumping into code, let's think naturally:

**What is the goal?**  
→ Reduce `n` to `0` in **minimum steps**.

**What is changing each step?**  
→ The number itself. We subtract one of its own digits.

**What is fixed?**  
→ The rules: we can only subtract a digit that **currently exists** in the number.

**Can I build answers for small numbers first?**  
→ YES! If I know the minimum steps for all numbers < x, I can figure out x easily.

**Can I reuse answers of smaller problems?**  
→ Absolutely! When I'm at `27`, I subtract `7` and land at `20`.  
→ If I already know `dp[20]`, I just add `1` to it!

> 💡 **Key Insight:** Every big number **depends on smaller numbers**. This screams DP!

---

## 1. 📝 Problem Rewording

> Given a number `n`, keep subtracting any of its digits until you reach `0`.  
> Find the **minimum number of subtractions** needed.

---

## 2. ❓ Why DP is Needed

### Why Greedy Fails?

You might think: *"Always subtract the largest digit!"*

Let's test on `27`:
```
Greedy: 27 → 20 → 18 → 10 → 9 → 0  ✅ (5 steps)
```
Looks fine here. But greedy doesn't always work for all cases!

The problem is: **the best local choice may not lead to the global optimum**.

### Why Recursion Alone is Slow?

```
                    27
                 /      \
               20        25
              /  \      /   \
            18   ...   20   ...
           /  \
         10   ...
```

See how `20` appears **multiple times**?  
Without memoization, we recompute the same states again and again!

### Where Overlapping Subproblems Appear?

Different paths lead to the **same number**:
- `27 → 20` (subtract 7)
- `25 → 20` (subtract 5)

Both need `dp[20]`! This is **overlapping subproblems** — the heart of DP.

---

## 3. 🎯 State Definition

```
┌─────────────────────────────────────────────────────┐
│  dp[x] = Minimum steps to reduce x to 0             │
└─────────────────────────────────────────────────────┘
```

**In one sentence:**  
> `dp[x]` tells us the **least number of digit-subtractions** needed to go from `x` down to `0`.

---

## 4. 🔄 Transition (Core Brain of DP)

### The Formula:

```
dp[x] = 1 + min( dp[x - d] )  for each digit d in x, where d > 0
```

### Visual Explanation:

```
    ┌─────────────┐
    │   x = 27    │
    └─────────────┘
          │
    What digits does 27 have?
    → digits: 2, 7
          │
    ┌─────┴─────┐
    ▼           ▼
 x - 2       x - 7
  = 25        = 20
    │           │
    ▼           ▼
 dp[25]      dp[20]
    │           │
    └─────┬─────┘
          ▼
   dp[27] = 1 + min(dp[25], dp[20])
```

### Why Minimum?

We want the **shortest path** to 0. So we try ALL possible digit subtractions and pick the one that leads to the smallest answer.

### Why `d > 0`?

Subtracting `0` doesn't change the number — infinite loop! Skip zeros.

---

## 5. 🏁 Base Case

```
dp[0] = 0
```

**Why?**  
→ We're already at `0`. No steps needed!  
→ This is our **destination** — the foundation everything builds upon.

---

## 6. 📊 Order of Computation (Tabulation Flow)

```
Fill direction: dp[0] → dp[1] → dp[2] → ... → dp[n]
                ────────────────────────────────────►
                      small to big
```

### Why Small to Big?

When computing `dp[x]`, we need `dp[x - d]`.

Since `d ≥ 1`, we have `x - d < x`.

So **all dependencies are already computed!**

```
Computing dp[27]:
  → needs dp[25] ✅ (already computed)
  → needs dp[20] ✅ (already computed)
```

---

## 7. 🔍 Dry Run on Small Example

Let's trace through `n = 27`:

```
┌────┬────────────┬──────────────────────────────────┬────────┐
│ i  │  digits    │  transitions                     │ dp[i]  │
├────┼────────────┼──────────────────────────────────┼────────┤
│ 0  │    -       │  BASE CASE                       │   0    │
│ 1  │   {1}      │  dp[1-1] = dp[0] = 0             │   1    │
│ 2  │   {2}      │  dp[2-2] = dp[0] = 0             │   1    │
│ 3  │   {3}      │  dp[3-3] = dp[0] = 0             │   1    │
│ ...│   ...      │  ...                             │  ...   │
│ 9  │   {9}      │  dp[9-9] = dp[0] = 0             │   1    │
│ 10 │  {1, 0}    │  dp[10-1] = dp[9] = 1            │   2    │
│ 18 │  {1, 8}    │  min(dp[17], dp[10]) = min(3,2)  │   3    │
│ 20 │  {2, 0}    │  dp[20-2] = dp[18] = 3           │   4    │
│ 27 │  {2, 7}    │  min(dp[25], dp[20]) = min(5,4)  │   5    │
└────┴────────────┴──────────────────────────────────┴────────┘
```

### Path Reconstruction for 27:

```
27 ──(−7)──► 20 ──(−2)──► 18 ──(−8)──► 10 ──(−1)──► 9 ──(−9)──► 0
     step 1      step 2      step 3      step 4      step 5

Total: 5 steps ✅
```

---

## 8. 🎁 Final Answer Meaning

```
┌─────────────────────────────────────────────────────────────┐
│  dp[n] = Minimum steps to reduce n to 0                     │
│                                                             │
│  It is GUARANTEED optimal because we tried ALL choices      │
│  at each step and picked the BEST one.                      │
└─────────────────────────────────────────────────────────────┘
```

**Why guaranteed optimal?**
- We don't guess — we explore **every valid path**
- We use **previously computed optimal answers** (no redundant work)
- `min()` ensures we always pick the shortest route

---

## 9. ⏱️ Time & Space Complexity

```
┌──────────────────────────────────────────┐
│  Time:  O(n × d)                         │
│         where d = max digits ≈ 7         │
│         (since n ≤ 10^6)                 │
│                                          │
│  Simplified: O(n)                        │
├──────────────────────────────────────────┤
│  Space: O(n)                             │
│         for the dp array                 │
└──────────────────────────────────────────┘
```

**Breakdown:**
- Loop through `1` to `n` → O(n)
- For each number, extract digits → O(log₁₀(i)) ≈ O(7) for n ≤ 10⁶
- Total: O(n × 7) ≈ O(n)

---

## 10. 💡 One-Line Memory Trick

> **"dp[x] = 1 + best past I can reach by removing one digit"**

Or even simpler:

> **"Every number borrows its answer from a smaller friend."**

---

## 🎨 Visual Summary

```
         ┌─────────────────────────────────────┐
         │         REMOVING DIGITS             │
         │              DP                     │
         └─────────────────────────────────────┘
                         │
         ┌───────────────┼───────────────┐
         ▼               ▼               ▼
    ┌─────────┐    ┌──────────┐    ┌──────────┐
    │ STATE   │    │TRANSITION│    │  BASE    │
    │ dp[x]   │    │ dp[x]=   │    │ dp[0]=0  │
    │ = min   │    │ 1+min(   │    │          │
    │ steps   │    │ dp[x-d]) │    │          │
    │ to 0    │    │          │    │          │
    └─────────┘    └──────────┘    └──────────┘
                         │
                         ▼
              ┌─────────────────────┐
              │  Fill small → big   │
              │  Answer = dp[n]     │
              └─────────────────────┘
```

---

## 🧩 Pattern Recognition

This is a **"Min Steps to Reach Target"** DP pattern.

Similar problems:
- Coin Change (min coins to make amount)
- Perfect Squares (min squares to sum to n)
- Jump Game II (min jumps to reach end)

**Template:**
```
dp[target] = 1 + min(dp[reachable states])
```

---

## 💻 Implementation Code

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    // dp[i] = minimum steps to reduce i to 0
    vector<int> dp(n+1, 0);
    
    // Base case: already at 0, no steps needed
    dp[0] = 0;

    // Build dp table from 1 to n
    for(int i = 1; i <= n; i++){
        // Convert current number to string to extract digits
        string s = to_string(i);
        
        // Start with a large value to find minimum
        int mini = INT_MAX;

        // Try removing each digit from current number
        for(int j = 0; j < s.size(); j++){
            int digit = s[j] - '0';    // Convert char to int
            
            // Skip if digit is 0 (subtracting 0 does nothing)
            if(digit > 0)
                // Take minimum among all choices
                // dp[i - digit] already computed (smaller state)
                // Add 1 for current step
                mini = min(mini, dp[i - digit]);
        }

        // Store the minimum steps for current number
        dp[i] = 1 + mini;
    }

    // dp[n] has the final answer
    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}
```

### 🔍 Code Walkthrough

**Line-by-Line Explanation:**

1. **`vector<int> dp(n+1, 0)`**  
   → Create array of size `n+1` (indices 0 to n)  
   → Initialize all to 0

2. **`dp[0] = 0`**  
   → Base case: 0 needs 0 steps

3. **`for(int i = 1; i <= n; i++)`**  
   → Fill dp table from small to large

4. **`string s = to_string(i)`**  
   → Convert number to string to easily access each digit  
   → Example: 27 → "27" → can access '2' and '7'

5. **`int digit = s[j] - '0'`**  
   → Convert character digit to integer  
   → '7' - '0' = 7 (ASCII math)

6. **`if(digit > 0)`**  
   → Only subtract non-zero digits  
   → Subtracting 0 creates infinite loop

7. **`mini = min(mini, dp[i - digit])`**  
   → Try all possible transitions  
   → Pick the one with minimum steps  
   → `i - digit` is already computed (smaller value)

8. **`dp[i] = 1 + mini`**  
   → Current step count = 1 (for this subtraction) + best previous state

9. **`cout << dp[n]`**  
   → Final answer: minimum steps to reduce n to 0

### 🎯 Key Implementation Insights

✅ **Why `to_string(i)` and not `to_string(n)`?**  
We need digits of **current number** `i`, not the input `n`!

✅ **Why `dp[i - digit]` is safe?**  
Since `digit ≥ 1`, we have `i - digit < i`, so it's already computed.

✅ **Why `INT_MAX` as initial?**  
We're finding minimum, so start with large value.

✅ **Space optimization possible?**  
No! Unlike Fibonacci, we need random access to `dp[i - digit]`, can't optimize to O(1).

---

*Happy Coding! 🚀*
