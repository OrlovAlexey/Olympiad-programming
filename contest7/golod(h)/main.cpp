#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef long long ll;

ll mod = 1000000007;

inline bool bit(ll mask, ll pos) {
    return (mask >> pos) & 1;
}

int main() {
    ll n, m;
    cin >> n >> m;
    vector<vector<char>> input(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> input[i][j];
        }
    }
    vector<vector<bool> > ok((1 << n), vector<bool>(1 << n, true));
    for (ll mask = 0; mask < (1 << n); ++mask) {
        for (ll mask1 = 0; mask1 < (1 << n); ++mask1) {
            for (ll i = 0; i < n - 1; ++i) {
                if (bit(mask, i)) {
                    if (bit(mask, i + 1)) {
                        if (bit(mask1, i)) {
                            ok[mask][mask1] = false;
                            break;
                        }
                        else {
                            if (bit(mask1, i + 1)) {
                                ok[mask][mask1] = false;
                                break;

                            }
                        }
                    }
                    else {
                        if (bit(mask1, i)) {
                            if (bit(mask1, i + 1)) {
                                ok[mask][mask1] = false;
                                break;
                            }
                        }
                        else {
                            if (!bit(mask1, i + 1)) {
                                ok[mask][mask1] = false;
                                break;
                            }
                        }
                    }
                }
                else {
                    if (bit(mask, i + 1)) {
                        if (bit(mask1, i)) {
                            if (bit(mask1, i + 1)) {
                                ok[mask][mask1] = false;
                                break;
                            }
                        }
                        else {
                            if (!bit(mask1, i + 1)) {
                                ok[mask][mask1] = false;
                                break;
                            }
                        }
                    }
                    else {
                        if (bit(mask1, i)) {
                            if (!bit(mask1, i + 1)) {
                                ok[mask][mask1] = false;
                                break;
                            }
                        }
                        else {
                            ok[mask][mask1] = false;
                            break;
                        }
                    }
                }
            }
        }
    }
    vector<vector<ll> > dp(m + 1, vector<ll>(1 << n, 0));
    for (ll mask = 0; mask < (1 << n); ++mask) {
        dp[1][mask] = 1;
    }
    bool flag;
    for (ll j = 1; j < m; ++j) {
        for (ll mask = 0; mask < (1 << n); ++mask) {

            flag = true;
            for (ll k = 0; k < n; ++k) {
                if ((input[k][j-1] == '+' && bit(mask, k) == 0) || (input[k][j-1] == '-' && bit(mask, k) == 1)) {
                    flag = false;
                    break;
                }
            }
            if (!flag) {
                continue;
            }

            for (ll mask1 = 0; mask1 < (1 << n); ++mask1) {
                flag = true;
                for (ll k = 0; k < n; ++k) {
                    if ((input[k][j] == '+' && bit(mask1, k) == 0) || (input[k][j] == '-' && bit(mask1, k) == 1)) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) {
                    continue;
                }

                if (ok[mask][mask1]) {
                    dp[j + 1][mask1] += dp[j][mask];
                }
            }

        }
    }
    ll ans = 0;
    for (ll mask = 0; mask < (1 << n); ++mask) {
        ans += dp[m][mask] % mod;
    }
    cout << ans % mod << '\n';
    return 0;
}
