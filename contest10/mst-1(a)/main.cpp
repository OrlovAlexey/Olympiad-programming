#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>

using namespace std;

const int inf = 100000000;

void decreaseKey(multiset<pair<int, int>>& q, int x, int delta, vector<int>& key) {
    q.erase({key[x], x});
    q.insert({delta, x});
}

void prim(int start, int n, const vector<vector<pair<int, int>>>& g, vector<int>& key, vector<int>& p, multiset<pair<int, int>>& q, unordered_set<int>& s) {
    for (int v = 0; v < n; ++v) {
        key[v] = inf;
        p[v] = inf;
    }
    int r = start;
    key[r] = 0;
    q.clear();
    s.clear();
    for (int v = 0; v < n; ++v) {
        q.insert({key[v], v});
        s.insert(v);
    }
    set<pair<int, int>>::iterator it;
    int v;
    while (!q.empty()) {
        it = q.begin();
        v = it->second;
        q.erase(it);
        s.erase(v);
        for (auto u : g[v]) {
            int weight = u.second;
            if ((s.find(u.first) != s.end()) && key[u.first] > weight) {
                p[u.first] = v;
                decreaseKey(q, u.first, u.second, key);
                key[u.first] = weight;
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    int x, y, w;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        g[x - 1].push_back({y - 1, w});
        g[y - 1].push_back({x - 1, w});
    }
    vector<int> key(n);
    vector<int> p(n);
    multiset<pair<int, int>> q;
    unordered_set<int> s;
    prim(0, n, g, key, p, q, s);
    long long ans = 0;
    for (int weight : key) {
        ans += weight;
    }
    cout << ans << '\n';


//    for (int i = 0 ; i < n; ++i) {
//        cout << i << " " << p[i] << " " << key[i] << '\n';
//    }
    return 0;
}
