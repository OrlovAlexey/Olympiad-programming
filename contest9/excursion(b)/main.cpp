#include <iostream>
#include <queue>
#include <vector>
#include <deque>
using namespace std;

long long counter = 0;

struct edge {
    long long to;
    long long w;
    long long number;
    edge(long long to, long long w, long long number) : to(to), w(w), number(number) {}
    explicit operator long long() {
        return number;
    }
};

long long inf = 1000000000000000000;

void bfs(long long s, long long n, long long m, vector<vector<edge>>& g, vector<bool>& used, vector<bool>& usedE, long long& min1) {
    deque<queue<long long>> q(11);
    vector<long long> dist(n + 1, inf);
    dist[s] = 0;
    q[0].push(s);
    used.assign(n + 1, false);
    usedE.assign(m + 1, false);
    long long v, to;
    long long count = 1;
    while (count > 0) {
        while (q[0].empty()) {
            q.pop_front();
            q.emplace_back();
        }
        v = q[0].front();
        q[0].pop();
        --count;
        if (used[v]) {
            return;
        }
        used[v] = true;
        for (auto& e : g[v]) {
            to = e.to;
            if (usedE[(long long)e]) {
                continue;
            }
            usedE[(long long)e] = true;
            if (dist[to] < inf) {
                min1 = min(min1, dist[to] + dist[v] + e.w);
            }
            if (dist[to] < dist[v] + e.w) {
                continue;
            }
            dist[to] = dist[v] + e.w;
            q[e.w].push(to);
            ++count;
        }

    }
}

int main() {
    long long n, m;
    cin >> n >> m;
    vector<vector<edge>> g(n + 1);
    long long v, to, w;
    for (long long i = 0; i < m; ++i) {
        cin >> v >> to >> w;
        g[v].push_back(edge(to, w, counter));
        g[to].push_back(edge(v, w, counter));
        counter++;
    }
    long long min1 = inf;
    vector<bool> used, usedE;
    for (long long s = 1; s <= n; ++s) {
        bfs(s, n, m, g, used, usedE, min1);
    }
    cout << min1;
    return 0;
}


