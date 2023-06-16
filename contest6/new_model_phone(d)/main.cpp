#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

int main() {
    ll n, k;
    cin >> n >> k;
    if (n == 1) {
        cout << 0 << '\n';
    }
    else if (k == 0) {
        cout << -1 << '\n';
    }
    else {
        ll logn = (ll)log2(n) + 1;
        vector<vector<ll>> dp(logn + 1, vector<ll>(n+1, 0));
        for (ll i = 0; i <= logn; ++i) {
            dp[i][0] = 1;
            dp[i][1] = 1;
        }
        ll j = 1;
        bool end = false;
        for (; !end; ++j) {//попытки
            dp[0][j] = 1;
            for (ll i = 1; i <= logn; ++i) {//телефоны
                dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
                if(dp[i][j] >= n && i <= k) {
                    end = true;
                }
            }
        }
        cout << j - 1 << '\n';
    }
    return 0;
}
