#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<long long>> g; // long long -> pair<long long, long long>
vector<long long> tin, tout, ret;
vector<bool> used;
long long timer = 0;
long long count = 0;

struct pair_hash {
    inline std::size_t operator()(const std::pair<long long,long long> & v) const {
        return v.first * 127 + 331 * v.second;
    }
};

void dfs(long long v, unordered_map<pair<long long, long long>, long long, pair_hash>& edges, vector<bool>& ans, long long p = -1) {
    tin[v] = timer++;
    ret[v] = tin[v];
    used[v] = true;
    for (long long to : g[v]) {
        if (to == p)
            continue;
        if (used[to]) {
            ret[v] = min(ret[v], tin[to]);
        }
        else {
            dfs(to, edges, ans, v);
            if (ret[to] >= tin[to]) {
                if (edges.find({v, to}) != edges.end()){
                    ans[edges[{v, to}]] = true;
                }
                else{
                    ans[edges[{to, v}]] = true;
                }// bridge
                (::count)++;
            }
            ret[v] = min(ret[v], ret[to]);
        }
    }
}

int main() {
    long long n, m;
    cin >> n >> m;
    g.resize(n);
    unordered_map<pair<long long, long long>, long long, pair_hash> edges(m);
    vector<bool> ans(m, false);
    long long x, y;
    for (long long i = 0; i < m; ++i) {
        cin >> x >> y;
        g[x - 1].push_back(y - 1);
        g[y - 1].push_back(x - 1);
        edges[{x - 1, y - 1}] = i;
    }
    used.assign(n, false); tin.resize(n); tout.resize(n); ret.resize(n);
    for (long long s = 0; s < n; ++s) {
        if (!used[s]) {
            dfs(s, edges, ans);
        }
    }
    cout << (::count) << '\n';
    for (long long i = 0; i < m; ++i) {
        if (ans[i]) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
