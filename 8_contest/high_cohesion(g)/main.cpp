#include <iostream>
#include <vector>

using namespace std;

vector<int> p, ans;

void dfs(int v, int count, vector<int>& tin, vector<int>& tout, vector<char>& color, vector<int>& par, const vector<vector<int>>& g, int& timer, int pa = -1) {
    par.at(v) = pa;
    tin.at(v) = timer++;
    color.at(v) = 'g';
    for (int to : g.at(v)) {
        if (color.at(to) != 'w') {
            continue;
        }
        dfs(to, count, tin, tout, color, par, g, timer, v);
    }
    tout.at(v) = timer++;
    p.push_back(v);
    ans[v] = count;
    color.at(v) = 'b';
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    int x, y;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        g.at(x - 1).push_back(y - 1);
        g.at(y - 1).push_back(x - 1);
    }
    vector<int> par(n);
    vector<int> tin(n), tout(n);
    int timer = 0;
    int count = 0;
    vector<char> color(n, 'w');
    ans.resize(n);
    for (int s = 0; s < n; ++s) {
        if (color[s] == 'w') {
            dfs(s, count, tin, tout, color, par, g, timer);
        }
    }
    color.assign(n, 'w');
    for (int i = 0; i < n; ++i) {
        if (color[p[n - 1 - i]] == 'w') {
            dfs(p[n - 1 - i], count, tin, tout, color, par, g, timer);
            count++;
        }
    }
    cout << count << '\n';
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}