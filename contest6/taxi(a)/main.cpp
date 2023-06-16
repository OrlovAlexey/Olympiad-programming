#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
    ll INF = 100000000;
    ll n, m;
    cin >> n;
    vector<pair<ll, string>> boys(n); // first = name, second = value
    for (ll i = 0; i < n; ++i) {
        cin >> boys[i].second >> boys[i].first;
    }
    cin >> m;
    vector<pair<ll, string>> girls(m); // first = name, second = value
    for (ll j = 0; j < m; ++j) {
        cin >> girls[j].second >> girls[j].first;
    }
    sort(boys.rbegin(), boys.rend());
    sort(girls.rbegin(), girls.rend());
//    for (ll i = 0; i < n; ++i) {
//        cout << boys[i].first << " " << boys[i].second << '\n';
//    }
//    for (ll j = 0; j < m; ++j) {
//        cout << girls[j].first << " " << girls[j].second << '\n';
//    }
    vector<vector<ll>> dp(n+1, vector<ll>(m+1));
    vector<vector<pair<ll, ll>>> prev(n+1, vector<pair<ll, ll>>(m+1));

//    for (ll i = 1; i <= n; ++i) {
//        dp[i][0] = dp[i-1][0] + boys[i-1].first;
//    }
    dp[0][0] = 0;
    for (ll j = 1; j <= m; ++j) {
        dp[0][j] = INF;
    }
    ll big_expr, min1, best_k, best_l;
    for (ll i = 1; i <= n; ++i) {//boys
        for (ll j = 0; j <= m; ++j) {//girls
            min1 = INF;
            for (ll k = 1; k <= 4 && i - k >= 0; ++k) {
                for (ll l = 0; l <= 4 - k && j - l >= 0; ++l) {
                    big_expr = dp[i - k][j - l] + max(boys[i - k].first, (l == 0 ? 0 : girls[j - l].first));
                    if (min1 > big_expr) {
                        min1 = big_expr;
                        best_k = k;
                        best_l = l;
                    }
                }
            }
            dp[i][j] = min1;
            prev[i][j] = {best_k, best_l};
        }
    }
    cout << dp[n][m] << '\n';
//    for (ll i = 0; i <= n; ++i) {
//        for (ll j = 0; j <= m; ++j) {
//            cout << dp[i][j] << '\t';
//        }
//        cout << '\n';
//    }
//    for (ll i = 0; i <= n; ++i) {
//        for (ll j = 0; j <= m; ++j) {
//            cout << prev[i][j].first << prev[i][j].second << '\t';
//        }
//        cout << '\n';
//    }
    ll i = n;
    ll j = m;
    ll prev_i, prev_j;
    vector<vector<string>> ans;
    ll size = 0;
    while (i > 0 || j > 0) {
        prev_i = i;
        prev_j = j;
        i = prev_i - prev[prev_i][prev_j].first;
        j = prev_j - prev[prev_i][prev_j].second;
        ans.emplace_back();
        for (; prev_i > i; --prev_i) {
            ans[size].push_back(boys[prev_i - 1].second);
        }
        for (; prev_j > j; --prev_j) {
            ans[size].push_back(girls[prev_j - 1].second);
        }
        ++size;
    }
    cout << size << '\n';
    for (ll k = 0; k < size; ++k) {
        cout << "Taxi " << k + 1 << ": ";
        if (ans[k].size() > 1) {
            for (ll z = 0; z < ans[k].size() - 1; ++z) {
                if (z == ans[k].size() - 2) {
                    cout << ans[k][z] << " ";
                }
                else {
                    cout << ans[k][z] << ", ";
                }
            }
            cout << "and " << ans[k][ans[k].size() - 1] << ".";
        }
        else {
            cout << ans[k][0] << ".";
        }
        cout << '\n';
    }
    return 0;
}
