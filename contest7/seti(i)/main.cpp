#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

inline bool bit(ll mask, ll pos) {
    return (mask >> pos) & 1;
}

int main() {
    ll n;
    cin >> n;
    vector<vector<bool>> seti(n, vector<bool>(n));
    string s;
    for (ll i = 0; i < n; ++i) {
        cin >> s;
        for (ll j = 0; j < n; ++j) {
            if (s[j] == 'Y') {
                seti[i][j] = true;
            }
            else {
                seti[i][j] = false;
            }
        }
    }
    vector<ll> dp(1 << n, 0);
    ll newmask;
    for (ll mask = 0; mask < (1 << n); ++mask) {
        for (ll i = 0; i < n; ++i) {
            if (bit(mask, i)) {
                for (ll j = i + 1; j < n; ++j) {
                    if (bit(mask, j)) {
                        newmask = mask - (1 << i) - (1 << j);
                        if (seti[i][j]) {
                            dp[mask] = max(dp[mask], dp[newmask] + 1);
                        }
                        else {
                            dp[mask] = max(dp[mask], dp[newmask]);
                        }
                    }
                }
            }
        }
    }
    cout << 2 * dp[(1 << n) - 1] << '\n';
    return 0;
}
