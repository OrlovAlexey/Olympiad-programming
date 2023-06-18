#include <iostream>
#include <vector>
using namespace std;

struct edge {
    int to;
    double r, c;
    edge(int to, double r, double c) : to(to), r(r), c(c) {}
};

int inf = 1000000000;

int main() {
    int n, m, s;
    double sum;
    cin >> n >> m >> s >> sum;
    vector<vector<edge>> g(n + 2);// 1...n+1
    int fake_s = n + 1;
    int v, u;
    double r1, c1, r2, c2;
    for (int i = 0; i < m; ++i) {
        cin >> v >> u;
        cin >> r1 >> c1 >> r2 >> c2;
        if (v == s) {
            g[v].push_back(edge(u, r1, c1));
            g[u].push_back(edge(fake_s, r2, c2));// splitting s
        }
        else if (u == s) {
            g[v].push_back(edge(fake_s, r1, c1));
            g[u].push_back(edge(v, r2, c2));
        }
        else {
            g[v].push_back(edge(u, r1, c1));
            g[u].push_back(edge(v, r2, c2));
        }
    }
    vector<double> dp(n + 2, -inf);
    dp[s] = sum;
    for (int k = 0; k < 10000; ++k) {
        for (u = 1; u <= n + 1; ++u) {
            /*
            double max1 = -inf;
            for (auto& e : g[u]) {
                if (dp[e.to][k] != -inf && max1 < (dp[e.to][k] - e.c) * e.r) {
                    max1 = (dp[e.to][k] - e.c) * e.r;
                }
            }
            dp[u][k + 1] = max(dp[u][k], max1);
             */
            for (auto& e : g[u]) {
                if (dp[u] != -inf) {
                    dp[e.to] = max(dp[e.to], (dp[u] - e.c) * e.r);
                }
            }
        }
    }//ford bellman
    if (dp[fake_s] > sum) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
    return 0;
}
