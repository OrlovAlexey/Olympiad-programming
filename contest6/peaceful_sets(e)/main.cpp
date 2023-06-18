#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, 0));
    for (ll i = 0; i <= n; ++i) {
        for (ll j = 0; j <= n; ++j) {
            if (i < j) {
                dp[i][j] = 0;
            }
            else if (i == j) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = 0;
                ll k = j / 2;
                while (k >= 0) {
                    dp[i][j] += dp[i-j][k];
                    --k;
                }
            }
        }
    }
    ll ans = 0;
    for (ll i = 0; i <= n; ++i) {
        ans += dp[n][i];
    }
    cout << ans << '\n';
    return 0;
}
