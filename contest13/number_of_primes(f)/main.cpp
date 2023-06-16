#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

using ll = long long;

inline ll geti(ll x, ll sq, ll v_size, ll n) {
    if (x <= sq) {
        return ((int) x - 1);
    } else {
        return (int) (v_size - (n / x));
    }
}

ll count_primes(ll n) {
    vector<ll> v;
    for (ll k = 1; k * k <= n; ++k) {
        v.push_back(n / k);
        v.push_back(k);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    ll sq = sqrt(n);
    ll v_size = v.size();

    vector<ll> dp(v.size());

    // S(n, 0) = n
    for (int i = 0; i < v.size(); ++i) {
        dp[i] = v[i];
    }

    int a = 0;
    for (ll p = 2; p * p <= n; ++p) { // this condition is true for primes
        if (dp[geti(p, sq, v_size, n)] != dp[geti(p - 1, sq, v_size, n)]) {
            ++a;
            for (int i = (int) v.size() - 1; i >= 0; --i) {
                if (v[i] < p * p) {
                    break;
                }
                dp[i] -= dp[geti(v[i] / p, sq, v_size, n)] - a;
            }
        }
    }

    return dp[geti(n, sq, v_size, n)] - 1;
}

int main() {
    ll n; cin >> n;
    cout << count_primes(n);
    return 0;
}
