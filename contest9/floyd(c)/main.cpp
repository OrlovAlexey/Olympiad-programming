#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct edge {
    long long to;
    long long w;
    edge(long long to, long long w) : to(to), w(w) {}
};

long long inf = 100000000000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n;
    cin >> n;
    vector<vector<edge>> g(n + 1);
    long long v, to, w;
    for (long long i = 1; i <= n; ++i) {
        for (long long j = 1; j <= n; ++j) {
            cin >> w;
            if (i != j)
                g[i].push_back(edge(j, w));
        }
    }
    for (long long s = 1; s <= n; ++s) {
        vector<queue<long long>> q(201 * n + 1);
        vector<long long> dist(n + 1, inf);
        dist[s] = 0;
        q[0].push(s);
        vector<bool> used(n + 1, false);
        for (long long d = 0; d <= 201 * (n - 1); ++d) {
            while (!q[d].empty()) {
                v = q[d].front();
                q[d].pop();
                if (used[v])
                    continue;
                used[v] = true;
                for (edge &e : g[v]) {
                    to = e.to;
                    if (dist[to] <= dist[v] + e.w) {
                        continue;
                    }
                    dist[to] = dist[v] + e.w;
                    q[dist[to] + 100].push(to);
                }
            }
        }
        for (long long i = 1; i <= n; ++i) {
            cout << dist[i] << " ";
        }
        cout << '\n';
    }
    return 0;
}
