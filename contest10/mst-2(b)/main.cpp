#include <iostream>
#include <vector>
#include <algorithm>
//int get(int v, const int* p) {
//    return (p[v] == - 1 ? v : get(p[v], p));
//}

using std::vector;
using std::pair;
using std::cin;
using std::cout;


int get(int v, vector<int>& p) {
    if (p[v] == -1) {
        return v;
    }
    else
        return p[v] = get(p[v], p);
}

void unite(int u, int v, vector<int>& p, vector<int>& size) {
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
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> g(m);
    for (int i = 0; i < m; ++i) {
        cin >> g[i].second.first >> g[i].second.second >> g[i].first;
    }
    std::sort(g.begin(), g.end());
    vector<int> p(n, -1);
    vector<int> size(n);
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        int v = g[i].second.first - 1;
        int to = g[i].second.second - 1;
        int w = g[i].first;
        if (get(v, p) != get(to, p)) {
            ans += w;
//            res.push_back(std::make_pair(v, to));
            unite(v, to, p, size);
        }
    }
    cout << ans << '\n';
    return 0;
}
