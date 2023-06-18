#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using ll = long long;

void dfs(ll v, vector<bool>& used, const vector<vector<pair<ll,ll>>>& graph) {
    used[v] = true;
    for (auto to : graph[v]) {
        if (used[to.first]) {
            continue;
        }
        dfs(to.first, used, graph);
    }
}

int main() {
    ll inf = 9000000000000000000;
    ll n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<ll ,ll>>> graph(n + 1);
    vector<vector<pair<ll ,ll>>> rgraph(n + 1);
    ll v1, v2, input;
    for (ll i = 0; i < m; ++i) {
        cin >> v1 >> v2;
        cin >> input;
        graph[v1].push_back({v2, input});
        rgraph[v2].push_back({v1, input});
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, inf));
    for (ll v = 1; v <= n; ++v) {
        dp[v][0] = (v == s ? 0 : inf);
    }
    for (ll k = 0; k < n; ++k) {
        for (ll u = 1; u <= n; ++u) {
            ll min1 = inf;
            for (auto& v : rgraph[u]) {
                if (dp[v.first][k] != inf && min1 > dp[v.first][k] + v.second) {
                    min1 = dp[v.first][k] + v.second;
                }
            }
            dp[u][k + 1] = std::min(dp[u][k], min1);
        }
    }
    vector<bool> is_no_way(n + 1, false);
    vector<ll> start;
    for (ll i = 1; i <= n; ++i) {
        if (dp[i][n] < dp[i][n-1]) {
            start.push_back(i);
        }
    }
    for (ll x : start) {
        dfs(x, is_no_way, graph);
    }
    for (ll i = 1; i <= n; ++i) {
        if (dp[i][n - 1] != inf) {
            if (is_no_way[i]) {
                cout << "-" << '\n';
            }
            else {
                cout << dp[i][n - 1] << '\n';
            }
        } else {
            cout << "*" << '\n';
        }
    }
    return 0;
}
