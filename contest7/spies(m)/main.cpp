#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

ll mod = 1000000007;


inline bool bit(ll mask, ll pos) {
    return (mask >> pos) & 1;
}

class matrix{
public:
    vector<vector<ll>> v;
    ll n, m;
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
    ll last() {
        return v[0][m-1];
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

int main() {
    ll n, k;
    cin >> n >> k;
    ll a, b, c;
    vector<vector<ll>> start;
    vector<vector<ll>> finish;
    matrix base;
    matrix final;
    matrix dp;
    ll power;
    for (ll i = 0; i < n; ++i) {
        cin >> a >> b >> c;
        if (i == 0) {
            start.resize(c+1);
            start[0].resize(0);
            start[0].push_back(1);
            for (ll j = 1; j <= c; ++j) {
                start[j].resize(0);
                start[j].push_back(0);
            }
        }
        else {
            start.resize(c+1);
            for (ll j = 0; j <= c; ++j) {
                start[j].resize(0);
                if (j < final.v.size()) {
//                    start[j].push_back((j != 0 ? final.v[j-1][0] : 0) + final.v[j][0] + (j != (final.v.size() - 1) ? final.v[j+1][0] : 0));
                    start[j].push_back(final.v[j][0]);
                }
                else {
                    start[j].push_back(0);
                }
            }
        }
        vector<vector<ll>> v(c+1, vector<ll>(c+1));
        for (int s = 0; s <= c; ++s) {
            for (int t = 0; t <= c; ++t) {
                if (t == s || (s > 0 && t == s - 1) || (s < c && t == s + 1)) {
                    v[s][t] = 1;
                }
                else {
                    v[s][t] = 0;
                }
            }
        }
        dp = matrix(v);
//        dp.print();
        base = matrix(start);
//        base.print();
        if (k < b) {
            power = k - a;
        }
        else {
            power = b - a;
        }
        final = bin_pow(dp, power) * start;
//        final.print();
    }
    cout << final.last() % mod;
    return 0;
}
