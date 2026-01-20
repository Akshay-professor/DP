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
 
void solve() {
    int n;
    cin >> n;
 
    if(n == 1){
        int x; 
        cin >> x;     
        cout << 1 << "\n";
        return;
    }
 
    // 1-based indexing
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
 
    vector<int> dp(n+1, 1);
    int ans = 1;
 
    for(int i = 1; i <= n; i++){
        for(int j = 2*i; j <= n; j += i){
            if(a[j] > a[i]){
                dp[j] = max(dp[j], dp[i] + 1);
                ans = max(ans, dp[j]);
            }
        }
    }
 
    cout << ans << "\n";
}
 
int main() {
    fastio();
 
    int t;
    cin >> t;
    while(t--){
        solve();
    }
 
    return 0;
}