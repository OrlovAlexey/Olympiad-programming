#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;

inline bool bit(ll mask, ll pos) {
    return (mask >> pos) & 1;
}

int main() {
    ll n, C;
    cin >> n;
    ll x[n];
    for (ll i = 0; i < n; ++i) {
        cin >> x[i];
    }
    cin >> C;
    ll m = n / 2;
    ll sum_w;
    ll ans = 0;
    vector<ll> sums_of_masks;
    for (ll i = 0; i < (1ull << m); ++i) {
        sum_w = 0;
        for (ll j = 0; j < m; ++j) {
            if (bit(i, j)) {
                sum_w += x[j];
            }
        }
        if (sum_w <= C) {
            ++ans;
        }
        sums_of_masks.push_back(sum_w);
    }
    sort(sums_of_masks.begin(), sums_of_masks.end());

    for (ll i = 1; i < (1ull << (m + (n % 2))); ++i) {
        sum_w = 0;
        for (ll j = m; j < n; ++j) {
            if (bit(i, j - m)) {
                sum_w += x[j];
            }
        }
        if (sum_w > C) {
            continue;
        }
        ll j = (ll)(lower_bound(sums_of_masks.begin(), sums_of_masks.end(), C - sum_w + 1) - sums_of_masks.begin());
        ans += j;
    }
    cout << ans << '\n';
    return 0;
}
