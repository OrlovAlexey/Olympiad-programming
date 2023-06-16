#include <iostream>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll inf = 1000000000000000000;
    ll n, h;
    cin >> h;
    ll a, b, c;
    cin >> a >> b >> c;
    ll temp1, temp2, temp3;
    temp1 = std::min(a, std::min(b, c));
    temp3 = std::max(a, std::max(b, c));
    temp2 = a + b + c - temp1 - temp3;
    a = temp1; b = temp2; c = temp3;
    n = a;
    vector<vector<pair<ll, ll>>> graph(n);
    for (ll i = 0; i < n; ++i) {
        graph[i].push_back({(i + b) % a, b});
        graph[i].push_back({(i + c) % a, c});
    }
    ll s = 1;
    vector<ll> dist(n, inf);
    dist[s - 1] = 0;
    vector<bool> used(n,false);
    set<pair<ll, ll>> set1;
    vector<set<pair<ll, ll>>::iterator> iterators(n);
    for (int i = 0; i < n; ++i) {
        iterators[i] = set1.insert({((i == s - 1) ? 0 : inf), i}).first;
    }
    for (ll i = 0; i < n; ++i) {

        if (set1.begin() == set1.end())
            break;
        ll v = set1.begin()->second;
        for (auto edge : graph[v]) {
            if (!used[v]) {
                if (dist[v] + edge.second < dist[edge.first]) {
                    auto iter = iterators[edge.first];
                    set1.erase(iter);
                    iterators[edge.first] = set1.insert({dist[v] + edge.second, edge.first}).first;
                }
                dist[edge.first] = std::min(dist[edge.first], dist[v] + edge.second);
            }
        }
        used[v] = true;
        set1.erase(iterators[v]);
    }
//    for (ll i = 0; i < n; ++i) {
//        cout << dist[i] << '\n';
//    }
    ll ans = 0;
    for (ll i = 0; i < n; ++i) {
        if (dist[i] != inf && dist[i] <= h - 1) {
            ans += (h - 1 - dist[i]) / a + 1;
        }
    }
    cout << ans << '\n';
    return 0;
}
