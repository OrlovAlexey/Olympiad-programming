#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> p;
vector<unordered_set<int>> components;

struct pair_hash {
    inline std::size_t operator()(const pair<pair<int, int>, int>& v) const {
        return v.first.first * 127 + 331 * v.first.second + v.second;
    }
};

void dfs1(int v, int count, vector<int>& tin, vector<int>& tout, vector<char>& color, vector<int>& par, const vector<vector<int>>& g, int& timer, int pa = -1) {
    par.at(v) = pa;
    tin.at(v) = timer++;
    color.at(v) = 'g';
    for (int to : g.at(v)) {
        if (color.at(to) != 'w') {
            continue;
        }
        dfs1(to, count, tin, tout, color, par, g, timer, v);
    }
    tout.at(v) = timer++;
    p.push_back(v);
    color.at(v) = 'b';
}

void dfs2(int v, int count, vector<int>& tin, vector<int>& tout, vector<char>& color, vector<int>& par, const vector<vector<int>>& g, int& timer, int pa = -1) {
    par.at(v) = pa;
    tin.at(v) = timer++;
    color.at(v) = 'g';
    for (int to : g.at(v)) {
        if (color.at(to) != 'w') {
            continue;
        }
        dfs2(to, count, tin, tout, color, par, g, timer, v);
    }
    tout.at(v) = timer++;
    p.push_back(v);
    components[count].insert(v);
    color.at(v) = 'b';
}

int main() {
    int n1, m1, n ,m;
    cin >> n1 >> m1;
    n = 2 * m1;
    m = 4 * n1;
    vector<int> lamps(n1);
    for (int i = 0; i < n1; ++i) {
        cin >> lamps[i];
    }
    vector<vector<int>> turners(n1);
    vector<vector<int>> g(n);
    int x, y;
    for (int i = 0; i < m1; ++i) {
        cin >> x;
        for (int j = 0; j < x; ++j) {
            cin >> y;
            turners[y - 1].push_back(i);
        }
    }
    unordered_set<pair<pair<int, int>, int>, pair_hash> checker;
    for (int i = 0; i < n1; ++i) {
        x = turners[i][0];
        y = turners[i][1];
        if (lamps[i] == 1) {
            if (checker.find({{x, y}, 1}) != checker.end()) {
                continue;
            }
            if (checker.find({{x, y}, 0}) != checker.end()) {
                cout << "NO" << '\n';
                return 0;
            }
            g[x].push_back(y);
            g[y].push_back(x);
            g[x + m1].push_back(y + m1);
            g[y + m1].push_back(x + m1);
            checker.insert({{x, y}, 1});
            checker.insert({{y, x}, 1});
        } else {
            if (checker.find({{x, y}, 0}) != checker.end()) {
                continue;
            }
            if (checker.find({{x, y}, 1}) != checker.end()) {
                cout << "NO" << '\n';
                return 0;
            }
            g[x].push_back(y + m1);
            g[y + m1].push_back(x);
            g[x + m1].push_back(y);
            g[y].push_back(x + m1);
            checker.insert({{x, y}, 0});
            checker.insert({{y, x}, 0});
        }
    }
    vector<int> par(n);
    vector<int> tin(n), tout(n);
    int timer = 0;
    int count = 0;
    vector<char> color(n, 'w');
    components.resize(n);
    for (int s = 0; s < n; ++s) {
        if (color[s] == 'w') {
            dfs1(s, count, tin, tout, color, par, g, timer);
        }
    }
    color.assign(n, 'w');
    for (int i = 0; i < n; ++i) {
        if (color[p[n - 1 - i]] == 'w') {
            dfs2(p[n - 1 - i], count, tin, tout, color, par, g, timer);
            count++;
        }
    }
    for (int i = 0; i < count; ++i) {
        for (int a : components[i]) {
            if (a < m1) {
                if (components[i].find(a + m1) != components[i].end()) {
                    cout << "NO" << '\n';
                    return 0;
                }
            } else {
                if (components[i].find(a - m1) != components[i].end()) {
                    cout << "NO" << '\n';
                    return 0;
                }
            }
        }
//        for (int j = 0; j < components[i].size(); ++j) {
//            for (int k = j + 1; k < components[i].size(); ++k) {
//                if (abs(components[i][j] - components[i][k]) == m1) {
//                    cout << "NO" << '\n';
//                    return 0;
//                }
//            }
//        }
    }
    cout << "YES" << '\n';
//    cout << count << '\n';
//    for (int i = 0; i < n; ++i) {
//        cout << components[i] + 1 << " ";
//    }
    return 0;
}