#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool is_cyclic = false;

void dfs(int v, vector<int>& tin, vector<pair<int, int>>& tout, vector<char>& color, vector<int>& par, const vector<vector<int>>& g, int& timer, int p = -1) {
    par.at(v) = p;
    tin.at(v) = timer++;
    color.at(v) = 'g';
    for (int to : g.at(v)) {
        if (color.at(to) == 'g') {
            is_cyclic = true;
            throw 1;
        }
        if (color.at(to) != 'w') {
            continue;
        }
        try {
            dfs(to, tin, tout, color, par, g, timer, v);
        } catch (...) {
            throw;
        }
    }
    tout[v] = {timer++, v};
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
    }
    vector<int> par(n);
    vector<int> tin(n);
    vector<pair<int, int>> tout(n);
    int timer = 0;
    vector<char> color(n, 'w');
    for (int s = 0; s < n; ++s) {
        if (color.at(s) == 'w') {
            try {
                dfs(s, tin, tout, color, par, g, timer);
            } catch (...) {
                cout << -1;
                return 0;
            }
        }
    }
    sort(tout.rbegin(), tout.rend());
    for (int j = 0; j < n; ++j) {
        cout << tout[j].second + 1 << " ";
    }
    //std::bind, std::function
    return 0;
}
