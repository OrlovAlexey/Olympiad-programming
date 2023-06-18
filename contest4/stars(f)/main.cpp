#include <iostream>

using namespace std;

typedef long long ll;

ll f(ll x) {
    return x & (x+1);
}

ll g(ll x) {
    return x | (x+1);
}

void build(ll s[][128][128], ll a[][128][128], ll n) {
    ll p[n][128][128];
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            for (ll k = 0; k < n; ++k) {
                if (i > 0 && j > 0 && k > 0) {
                    p[i][j][k] = p[i-1][j][k] + p[i][j-1][k] + p[i][j][k-1] - p[i][j-1][k-1] - p[i-1][j][k-1] - p[i-1][j-1][k] + p[i-1][j-1][k-1] + a[i][j][k];
                }
                else if (j > 0 && k > 0) {
                    p[i][j][k] = p[i][j-1][k] + p[i][j][k-1] - p[i][j-1][k-1] + a[i][j][k];
                }
                else if (i > 0 && k > 0) {
                    p[i][j][k] = p[i-1][j][k] + p[i][j][k-1] - p[i-1][j][k-1] + a[i][j][k];
                }
                else if (i > 0 && j > 0) {
                    p[i][j][k] = p[i-1][j][k] + p[i][j-1][k] - p[i-1][j-1][k] + a[i][j][k];
                }
                else if (i > 0) {
                    p[i][j][k] = p[i-1][j][k] + a[i][j][k];

                }
                else if (j > 0) {
                    p[i][j][k] = p[i][j-1][k] + a[i][j][k];
                }
                else if (k > 0) {
                    p[i][j][k] = p[i][j][k-1] + a[i][j][k];
                }
                else {
                    p[i][j][k] = a[i][j][k];
                }
            }
        }
    }
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            for (ll k = 0; k < n; ++k) {
                if (f(i) - 1 >= 0 && f(j) - 1 >= 0 && f(k) - 1 >= 0) {
                    s[i][j][k] = p[i][j][k] - p[f(i) - 1][j][k] - p[i][f(j) - 1][k] - p[i][j][f(k) - 1] + p[i][f(j) - 1][f(k) - 1] + p[f(i) - 1][j][f(k) - 1] + p[f(i) - 1][f(j) - 1][k] - p[f(i) - 1][f(j) - 1][f(k) - 1];
                }
                else if (f(j) - 1 >= 0 && f(k) - 1 >= 0) {
                    s[i][j][k] = p[i][j][k] - p[i][f(j) - 1][k] - p[i][j][f(k) - 1] + p[i][f(j) - 1][f(k) - 1];
                }
                else if (f(i) - 1 >= 0 && f(k) -1 >= 0) {
                    s[i][j][k] = p[i][j][k] - p[f(i) - 1][j][k] - p[i][j][f(k) - 1] + p[f(i) - 1][j][f(k) - 1];
                }
                else if (f(i) - 1 >= 0 && f(j) - 1 >= 0) {
                    s[i][j][k] = p[i][j][k] - p[f(i) - 1][j][k] - p[i][f(j) - 1][k] + p[f(i) - 1][f(j) - 1][k];
                }
                else if (f(i) - 1 >= 0) {
                    s[i][j][k] = p[i][j][k] - p[f(i) - 1][j][k];
                }
                else if (f(j) - 1 >= 0) {
                    s[i][j][k] = p[i][j][k] - p[i][f(j) - 1][k];
                }
                else if (f(k) - 1 >= 0) {
                    s[i][j][k] = p[i][j][k] - p[i][j][f(k) - 1];
                }
                else {
                    s[i][j][k] = p[i][j][k];
                }
            }
        }
    }
}

ll get_sum(ll s[][128][128], ll x, ll y, ll z) {
    ll ans = 0;
    for (ll i = x; i >= 0; i = f(i) - 1) {
        for (ll j = y; j >= 0; j = f(j) - 1) {
            for (ll k = z; k >= 0; k = f(k) - 1) {
                ans += s[i][j][k];
            }
        }
    }
    return ans;
}

void update(ll s[][128][128], ll a[][128][128], ll n, ll x, ll y, ll z, ll value) {
//    ll prev_value = a[x][y][z];
    for (ll i = x; i < n; i = g(i)) {
        for (ll j = y; j < n; j = g(j)) {
            for (ll k = z; k < n; k = g(k)) {
                s[i][j][k] += value;
            }
        }
    }
    a[x][y][z] += value;
}

int main() {
    ll n, m;
    cin >> n;
    ll a[n][128][128];
//    for (ll i = 0; i < n; ++i) {
//        for (ll j = 0; j < n; ++j) {
//            for (ll k = 0; k < n; ++k) {
//                a[i][j][k] = 0;
//            }
//        }
//    }
    ll s[n][128][128];
//    build(s, a, n);
    ll x, y, z, k;
    ll x1, y1, z1, x2, y2, z2;
    cin >> m;
    while (m != 3) {
        if (m == 1) {
            cin >> x >> y >> z >> k;
            update(s, a, n, x, y, z, k);
        }
        if (m == 2) {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            --x1, --y1, --z1;
            cout << get_sum(s, x2, y2, z2) - get_sum(s, x1, y2, z2) - get_sum(s, x2, y1, z2) - get_sum(s, x2, y2, z1) + get_sum(s, x1, y1, z2) + get_sum(s, x1, y2, z1) + get_sum(s, x2, y1, z1) - get_sum(s, x1, y1, z1) << '\n';
        }
        cin >> m;
    }

//    update(s, a, n, 3, 7);
//    for (ll i = 0; i < n; ++i) cout << a[i] << '\t';
//    cout << '\n';
//    for (ll i = 0; i < n; ++i) cout << s[i] << '\t';
//    cout << '\n';
//    for (ll i = 0; i < n; ++i) cout << get_sum(s, i) << '\t';
    return 0;
}
