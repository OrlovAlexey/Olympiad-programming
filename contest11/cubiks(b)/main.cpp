#include <iostream>
#include <vector>
using namespace std;

vector<long long> z_function(const vector<long long>& s) {
    long long n = s.size();
    vector<long long> z(n);
    long long l = 0;
    long long r = 0;
    for (long long i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main(){
    long long n, m;
    cin >> n >> m;
    vector<long long> s(2*n + 1);
    for (long long i = 0; i < n; ++i)
        cin >> s[i];
    s[n] = m + 1;
    for (long long i = n + 1; i <= 2*n; ++i)
        s[i] = s[2*n - i];
    vector<long long> z = z_function(s);
    for (long long i = 0; i <= 2*n; ++i) {
        if (z[i] % 2 == 0 && i + z[i] == 2*n + 1) {
            cout << (z[i] / 2 - n + i - 1) << " ";
        }
    }
    if (n != 0) cout << n;
    return 0;
}
