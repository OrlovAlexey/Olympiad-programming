#include <iostream>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

ll f(ll x) {
    return x & (x+1);
}

ll g(ll x) {
    return x | (x+1);
}

struct Interval {
    ll x;
    ll y;
};

void update(ll t[], ll sz, ll i, ll val) {
    for (; i < sz; i = g(i)) {
        t[i] += val;
    }
}

ll get_sum(ll t[], ll i) {
    ll ans = 0;
    for (; i >= 0; i = f(i) - 1) {
        ans += t[i];
    }
    return ans;
}

bool cmp(Interval a, Interval b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    else {
        return a.y > b.y;
    }
}

bool operator== (Interval a, Interval b ) {
    return (a.x == b.x && a.y == b.y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    Interval a[n];
    for (ll i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a, a+n, cmp);

    tree <pair<ll, ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update> set;


/*
    ll t[4*n];
    for (ll i = 0; i < 4*n; ++i) {
        t[i] = 0;
    }
//    ll ans[n];
//    for (ll i = 0; i < n; ++i) ans[i] = 0;
    ll ans = 0;
    for (ll i = n-1; i >= 0; --i) {
//        cout << a[i].first.x << '\t' << a[i].first.y << '\n';
        ll y_index = ll(lower_bound(ys.begin(), ys.end(), a[i].first.y) - ys.begin());
        ans += get_sum(t, y_index);
        update(t, n, y_index, 1);
    }
    cout << ans;
//    for (ll i = 0; i < n; ++i) {
//        cout << ans[i] << '\n';
//    }
*/

    ll ans = 0, prev = 0;
    for (ll i = 0 ; i < n ; ++i) {
        set.insert({a[i].y, -i});
        if (i != 0 && a[i] == a[i - 1])
            ans += prev;
        else {
            prev = set.size() - set.order_of_key({a[i].y, -i}) - 1;
            ans += prev;
        }
    }
    cout << ans;

    return 0;
}
