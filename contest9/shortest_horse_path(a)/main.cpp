#include <iostream>
#include <vector>
#include "queue"
using namespace std;

vector<vector<int>> g;
vector<int> dist, p;
queue<int> q;

int inf = 100000000;

void bfs(int s){
    dist.assign(64, inf);
    dist[s] = 0;
    p[s] = -1;
    q.push(s);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (dist[to] != inf) {
                continue;
            }
            dist[to] = dist[v] + 1;
            p[to] = v;
            q.push(to);
        }
    }
}

int main() {
    g.resize(64);
    for (int i = 0; i < 64; ++i) {
        if (i - 2 * 8 - 1 >= 0 && i % 8 - 1 >= 0) g[i].push_back(i - 2 * 8 - 1);
        if (i - 2 * 8 + 1 >= 0 && i % 8 + 1 < 8) g[i].push_back(i - 2 * 8 + 1);
        if (i - 8 + 2 >= 0 && i % 8 + 2 < 8) g[i].push_back(i - 8 + 2);
        if (i + 8 + 2 < 64 && i % 8 + 2 < 8) g[i].push_back(i + 8 + 2);
        if (i + 2 * 8 + 1 < 64 && i % 8 + 1 < 8) g[i].push_back(i + 2 * 8 + 1);
        if (i + 2 * 8 - 1 < 64 && i % 8 - 1 >= 0) g[i].push_back(i + 2 * 8 - 1);
        if (i + 8 - 2 < 64 && i % 8 - 2 >= 0) g[i].push_back(i + 8 - 2);
        if (i - 8 - 2 >= 0 && i % 8 - 2 >= 0) g[i].push_back(i - 8 - 2);
    }
    dist.resize(64);
    p.resize(64);
    string x, y;
    cin >> x;
    cin >> y;
    int start = 8 * static_cast<int>(x[0] - 103) + x[1] - 1;
    int finish = 8 * static_cast<int>(y[0] - 103) + y[1] - 1;
    bfs(start);
    //cout << dist[finish];
    vector<string> ans;
    for (int i = finish; i != p[start]; i = p[i]) {
        //cout << i << '\n';
        ans.push_back(static_cast<char>(i / 8 + 97) + to_string(i % 8 + 1));
    }
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
        cout << *it << '\n';
    }
    return 0;
}
