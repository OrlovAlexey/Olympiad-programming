#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::pair;

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    vector<vector<bool>> incidence(n, vector<bool>(m, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[j].first == i + 1 || a[j].second == i + 1) {
                incidence[i][j] = true;
                cout << 1 << " ";
            }
            else {
                cout << 0 << " ";
            }
        }
        cout << '\n';
    }
    return 0;
}
