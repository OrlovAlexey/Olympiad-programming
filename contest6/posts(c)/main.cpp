#include <iostream>
#include <vector>

using namespace std;

int main() {
    int INF = 1000000000;
    int n, m;
    cin >> n >> m;
    vector<int> a(n+1);
    a[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    vector<vector<int>> prev(n+1, vector<int>(m+1, 0));
    int mini, temp, best_k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j + 1 >= i) {
                dp[i][j] = 0;
            }
            else if (j == 0) {
                mini = INF;
                temp = 0;
                for (int p = 1; p < i; ++p) {
                    temp += a[i] - a[p];
                }
                if (mini > temp) {
                    mini = temp;
                }
                dp[i][j] = mini;
                prev[i][j] = -1;
            }
            else {
                mini = INF;
                for (int k = j + 1; k < i; ++k) {
                    temp = dp[k][j - 1];
                    for (int p = k; p <= i; ++p) {
                        if (a[p] - a[k] <= a[i] - a[p]) {
                            temp += a[p] - a[k];
                        } else {
                            temp += a[i] - a[p];
                        }
                    }
                    if (mini > temp) {
                        mini = temp;
                        best_k = k;
                    }
                }
                dp[i][j] = mini;
                prev[i][j] = best_k;
            }
        }
    }
    int ans = INF;
    int best_i;
    for (int i = m; i <= n; ++i) {
        temp = dp[i][m-1];
        for (int j = i; j <= n; ++j) {
            temp += a[j] - a[i];
        }
        if (ans > temp) {
            ans = temp;
            best_i = i;
        }
    }
    cout << ans << '\n';
    vector<int> inverse;
    int j = m;
    for (int i = best_i; i > 0; i = prev[i][--j]) {
        inverse.push_back(a[i]);
    }
    for (int i = 0; i < inverse.size(); ++i) {
        cout << inverse[inverse.size() - i - 1] << " ";
    }
    return 0;
}
