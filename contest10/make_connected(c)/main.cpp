#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;
using ll = long long;

struct pairhash {
public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &x) const
    {
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
    }
};

const ll inf = 1000000000000000000;

void decreaseKey(set<pair<ll, ll>>& q, ll x, ll delta, vector<ll>& key) {
    q.erase({key[x], x});
    q.insert({delta, x});
}

//void prim(ll start, ll n, const vector<ll>& a, const unordered_multimap<pair<ll, ll>, ll, pairhash>& special_offers, vector<ll>& key, vector<ll>& p, set<pair<ll, ll>>& q, unordered_set<ll>& s) {
//    for (ll v = 0; v < n; ++v) {
//        key[v] = inf;
//        p[v] = inf;
//    }
//    ll r = start;
//    key[r] = 0;
//    q.clear();
//    s.clear();
//    for (ll v = 0; v < n; ++v) {
//        q.insert({key[v], v});
//        s.insert(v);
//    }
//    set<pair<ll, ll>>::iterator it;
//    ll v;
//    while (!q.empty()) {
//        it = q.begin();
//        v = it->second;
//        q.erase(it);
//        s.erase(v);
//        for (ll u = 0; u < n; ++u) {
//            if (u == v)
//                continue;
//            ll weight = a[v] + a[u];
//            auto it1 = special_offers.find({v, u});
//            if (it1 != special_offers.end())
//                weight = std::min(weight, it1->second);
//            auto it2 = special_offers.find({u, v});
//            if (it2 != special_offers.end())
//                weight = std::min(weight, it2->second);
//            if ((s.find(u) != s.end()) && key[u] > weight) {
//                p[u] = v;
//                decreaseKey(q, u, u, key);
//                key[u] = weight;
//            }
//        }
//    }
//}

ll get(ll v, vector<ll>& p) {
    if (p[v] == -1) {
        return v;
    }
    else
        return p[v] = get(p[v], p);
}

void unite(ll u, ll v, vector<ll>& p, vector<ll>& size) {
    u = get(u, p);
    v = get(v, p);
    if (u == v)
        return;
    if (size[u] < size[v])
        std::swap(u, v);
    p[v] = u;
    size[u] += size[v];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    ll min1 = 0;
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[min1] > a[i])
            min1 = i;
    }

    unordered_multimap<pair<ll, ll>, ll, pairhash> special_offers;
    ll x, y, w;
    for (ll i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        special_offers.insert({{x - 1, y - 1}, w});
    }
    /*
    vector<ll> key(n); vector<ll> p(n); set<pair<ll, ll>> q; unordered_set<ll> s;
    prim(0, n, a, special_offers, key, p, q, s);
    ll ans = 0;
    for (ll weight : key) {
        ans += weight;
    }
    cout << ans << '\n';
    */
    vector<pair<ll, pair<ll, ll>>> g(n);
    for (ll i = 0; i < n; ++i) {
        if (i == min1)
            continue;
        g[i].second.first = min1;
        g[i].second.second = i;
        g[i].first = a[i] + a[min1];
        auto it1 = special_offers.find({min1, i});
        if (it1 != special_offers.end())
            g[i].first = std::min(g[i].first, it1->second);
        auto it2 = special_offers.find({i, min1});
        if (it2 != special_offers.end())
            g[i].first = std::min(g[i].first, it2->second);
    }
    std::sort(g.begin(), g.end());
    vector<ll> p(n, -1);
    vector<ll> size(n);
    long long ans = 0;
    ll v, u;
    for (ll i = 0; i < n; ++i) {
        if (i == min1)
            continue;
        v = g[i].second.first;
        u = g[i].second.second;
        w = g[i].first;
        if (get(v, p) != get(u, p)) {
            ans += w;
            unite(v, u, p, size);
        }
    }
    cout << ans << '\n';
    return 0;
}
