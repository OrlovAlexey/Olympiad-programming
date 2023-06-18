#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long ll;

ll mod = 1000000007;

inline bool bit(ll mask, ll pos) {
    return (mask >> pos) & 1;
}

class matrix{
    vector<vector<ll>> v;
    ll n, m;
public:
    matrix() = default;
    matrix(const vector<vector<ll>>& V) : n(V.size()), m(V[0].size()) {
        v.resize(n);
        for (ll i = 0; i < n; ++i) {
            v[i].resize(m);
            for (ll j = 0; j < m; ++j) {
                v[i][j] = (V[i][j] + mod) % mod;
            }
        }
    }
    matrix(const matrix& matrix1) : n(matrix1.v.size()), m(matrix1.v[0].size()) {
        v.resize(n);
        for (ll i = 0; i < n; ++i) {
            v[i].resize(m);
            for (ll j = 0; j < m; ++j) {
                v[i][j] = matrix1.v[i][j] % mod;
            }
        }
    }
    matrix(ll N) : n(N), m(N) {
        v.resize(N);
        for (ll i = 0; i < N; ++i) {
            v[i].resize(N);
            for (ll j = 0; j < N; ++j) {
                v[i][j] = ((i == j) ? 1 : 0);
            }
        }
    }
    matrix operator* (const matrix& matrix1) const{
        if (m != matrix1.n) {
            throw 1;
        }
        matrix copy(matrix1.v);
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < matrix1.m; ++j) {
                copy.v[i][j] = 0;
                for (ll k = 0; k < m; ++k) {
                    copy.v[i][j] += ((((v[i][k] + mod) % mod) * ((matrix1.v[k][j] + mod) % mod) + mod) % mod);
                }
            }
        }
        return copy;
    }
    void print() {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j) {
                cout << v[i][j] << '\t';
            }
            cout << '\n';
        }
    }
    ll rows_count() const {
        return n;
    }
    ll columns_count() const {
        return m;
    }
    ll sum() const {
        ll res = 0;
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j) {
                res += (v[i][j] % mod);
                res %= mod;
            }
        }
        return res;
    }
};

matrix bin_pow(const matrix& m1, ll n) {
    if (n == 0) {
        matrix e(m1.rows_count());
        return e;
    }
    if (n % 2 == 1) {
        return m1 * bin_pow(m1, n - 1);
    }
    else {
        matrix m2 = bin_pow(m1, n / 2);
        return m2 * m2;
    }
}

ll xor_divisible_by_3(ll x, ll y) {
    ll res = x ^ y;
    ll one_count = 0;
//    for (ll i = 0; (1 << i) <= res; ++i) {
//        if (bit(res, i)) {
//            ++one_count;
//        }
//    }
    while (res > 0) {
        if (res % 2 == 1) {
            ++one_count;
        }
        res /= 2;
    }
    if (one_count % 3 == 0) {
        return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, k;
    cin >> n >> k;
    vector<ll> x(n);
    for (ll i = 0; i < n; ++i) {
        cin >> x[i];
    }
    vector<vector<ll>> v(n, vector<ll>(n));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            v[i][j] = xor_divisible_by_3(x[i], x[j]);
        }
    }
    matrix m(v);
    vector<vector<ll>> stolbik(n, vector<ll>(1, 1));
    matrix start(stolbik);
    cout << (bin_pow(m, k-1) * start).sum() % mod;
    return 0;
}
