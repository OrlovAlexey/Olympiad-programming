#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(long long i, long long j, const string& s, const vector<vector<bool>>& prev1, const vector<vector<bool>>& prev2) {
    if (i == 0 || j == 0) {
        return;
    }
    if (!prev1[i][j] && !prev2[i][j]) {
        print(i - 1, j - 1, s, prev1, prev2);
        cout << s[i-1];
    }
    else {
        if (prev2[i][j]) {// <-
            print(i - 1, j, s, prev1, prev2);
        }
        else {
            print(i, j - 1, s, prev1, prev2);
        }
    }
}

int main() {
    //ios.base, untie(0)
    string s, t;
    cin >> s;
    cin >> t;
    long long n = s.size();
    long long m = t.size();
    vector<vector<long long>> dp(n+1, vector<long long>(2));
    vector<vector<bool>> prev1(n+1, vector<bool>(m+1));//отвечает за i
    vector<vector<bool>> prev2(n+1, vector<bool>(m+1));//отвечает за j
    for (long long i = 0; i <= n; ++i) {
        dp[i][0] = 0;
        dp[i][1] = 0;
    }
    for (long long j = 1; j <= m; ++j) {
        for (long long i = 1; i <= n; ++i) {
            if (s[i-1] == t[j-1]) {
//                if ((1 + dp[i-1][(j + 1) % 2] >= dp[i-1][j % 2]) && (dp[i-1][j % 2] >= dp[i][(j + 1) % 2])) {
//                    dp[i][j % 2] = 1 + dp[i-1][(j + 1) % 2];
//                    //prev[i][j] = {i-1, j-1};
//                    prev1[i][j] = false;
//                    prev2[i][j] = false;
//                }
//                else if ((1 + dp[i-1][(j + 1) % 2] >= dp[i][(j + 1) % 2]) && (dp[i][(j + 1) % 2] >= dp[i-1][j % 2])) {
//                    dp[i][j % 2] = 1 + dp[i-1][(j + 1) % 2];
//                    //prev[i][j] = {i-1, j-1};
//                    prev1[i][j] = false;
//                    prev2[i][j] = false;
//                }
//                else if ((dp[i-1][j % 2] >= dp[i][(j + 1) % 2]) && (dp[i][(j + 1) % 2] >= 1 + dp[i-1][(j + 1) % 2])) {
//                    dp[i][j % 2] = dp[i-1][j % 2];
//                    //prev[i][j] = {i-1, j};
//                    prev1[i][j] = false;
//                    prev2[i][j] = true;
//                }
//                else if ((dp[i-1][j % 2] >= 1 + dp[i-1][(j + 1) % 2]) && (1 + dp[i-1][(j + 1) % 2] >= dp[i][(j + 1) % 2])) {
//                    dp[i][j % 2] = dp[i-1][j % 2];
//                    //prev[i][j] = {i-1, j};
//                    prev1[i][j] = false;
//                    prev2[i][j] = true;
//                }
//                else if ((dp[i][(j + 1) % 2] >= 1 + dp[i-1][(j + 1) % 2]) && (1 + dp[i-1][(j + 1) % 2] >= dp[i-1][j % 2])) {
//                    dp[i][j % 2] = dp[i][(j + 1) % 2];
//                    //prev[i][j] = {i, j-1};
//                    prev1[i][j] = true;
//                    prev2[i][j] = false;
//                }
//                else {
//                    dp[i][j % 2] = dp[i][(j + 1) % 2];
//                    //prev[i][j] = {i, j-1};
//                    prev1[i][j] = true;
//                    prev2[i][j] = false;
//                }
//                pos[i][j % 2] = {i, j};
                dp[i][j % 2] = dp[i-1][(j + 1) % 2] + 1;
                prev1[i][j] = false;
                prev2[i][j] = false;
            }
            else {
                if (dp[i-1][j % 2] >= dp[i][(j + 1) % 2]) {
                    dp[i][j % 2] = dp[i-1][j % 2];
                    prev1[i][j] = false;
                    prev2[i][j] = true;
                }
                else {
                    dp[i][j % 2] = dp[i][(j + 1) % 2];
                    prev1[i][j] = true;
                    prev2[i][j] = false;
                }
            }
        }
    }
    print(n, m, s, prev1, prev2);
    return 0;
}
