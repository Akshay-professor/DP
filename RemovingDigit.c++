/*
    ॐ
    Code is poetry.
    – Akshay Poddar
*/

#include <bits/stdc++.h>
using namespace std;

// Fast IO
#define fastio() ios::sync_with_stdio(false); cin.tie(NULL);

// Typedefs
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;

// Constants
const ll INF = 1e18;
const int MOD = 1e9 + 7;

// Common Macros
#define f(i,a,b) for(int i=a;i<b;i++)
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

// Debug
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x << endl;
#else
#define debug(x)
#endif

// Solve function 
void solve() {
    int n;
    cin >> n;

    vector<int> dp(n+1, 0);
    dp[0] = 0;

    for(int i = 1; i <= n; i++){
        string s = to_string(i);   // i, not n
        int mini = INT_MAX;

        for(int j = 0; j < s.size(); j++){
            int p = s[j] - '0';    // correct digit conversion
            if(p > 0)
                mini = min(mini, dp[i - p]);
        }

        dp[i] = 1 + mini;
    }

    cout << dp[n] << "\n";
}


int main() {
    fastio();

    int t = 1;
    while(t--){
        solve();
    }

    return 0;
}
