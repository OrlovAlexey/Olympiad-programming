#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

inline bool bit(long long mask, long long pos) {
    return (mask >> pos) & 1;
}

double distance(pair<int, int> p1, pair<int, int> p2) {
    return (sqrt(p1.first * p1.first + p1.second * p1.second)
    + sqrt((p1.first - p2.first) * (p1.first - p2.first)
    + (p1.second - p2.second) * (p1.second - p2.second))
    + sqrt(p2.first * p2.first + p2.second * p2.second));
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> input(n);
    for (int i = 0; i < n; ++i) {
        cin >> input[i].first >> input[i].second;
    }
    vector<double> dp(1 << n);
    dp[0] = 1000000000000000000;
    long long newmask;
    for (long long mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (!bit(mask, i) && !bit(mask, j)) {
                    newmask = mask | (1 << i) | (1 << j);
                    dp[newmask] = min(dp[newmask], dp[mask] + distance(input[i], input[j]));
                }
            }
        }
    }
    if (n % 2 == 1) {
        for (int i = 0; i < n; ++i) {
            dp[(1 << n) - 1] = min(dp[(1 << n) - 1], dp[((1 << n) - 1) ^ (1 << i)]
            + input[i].first * input[i].first + input[i].second * input[i].second);
        }
    }
    cout << dp[(1 << n) - 1];
    return 0;
}