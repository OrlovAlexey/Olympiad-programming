#include <iostream>
#include <unordered_map>

using namespace std;
typedef long long ll;

ll Max = 1000000007;
ll mod(ll n, ll m = Max) {
    return (n % m + n) % m;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll m = 1000000007;
    ll n;
    cin >> n;
    ll a[n+1];
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    ll dp[n+1];
    dp[0] = 1;
    ll sum[n+1];
    sum[0] = dp[0];
    unordered_map<ll, ll> last;
    for (ll i = 1; i <= n; ++i) {
        if (last.find(a[i]) != last.end()) {
            dp[i] = (sum[i - 1] % m - sum[last[a[i]] - 1] % m + m) % m;
        }
        else {
            dp[i] = (sum[i - 1]) % m;
        }
        sum[i] = (sum[i - 1] % m + dp[i] % m) % m;
        last[a[i]] = i;
    }
    cout << sum[n] - 1 << '\n';
    return 0;
}
