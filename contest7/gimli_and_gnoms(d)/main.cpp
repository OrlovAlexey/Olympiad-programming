#include <iostream>
#include <vector>

long long mod = 1000000007;
using namespace std;

class matrix{
public:
    vector<vector<long long>> v;
    long long n, m;
    matrix() = default;
    matrix(const vector<vector<long long>>& V) : n(V.size()), m(V[0].size()) {
        v.resize(n);
        for (long long i = 0; i < n; ++i) {
            v[i].resize(m);
            for (long long j = 0; j < m; ++j) {
                v[i][j] = (V[i][j] + mod) % mod;
            }
        }
    }
    matrix(const matrix& matrix1) : n(matrix1.v.size()), m(matrix1.v[0].size()) {
        v.resize(n);
        for (long long i = 0; i < n; ++i) {
            v[i].resize(m);
            for (long long j = 0; j < m; ++j) {
                v[i][j] = matrix1.v[i][j] % mod;
            }
        }
    }
    matrix(long long N) : n(N), m(N) {
        v.resize(N);
        for (long long i = 0; i < N; ++i) {
            v[i].resize(N);
            for (long long j = 0; j < N; ++j) {
                v[i][j] = ((i == j) ? 1 : 0);
            }
        }
    }
    matrix operator* (const matrix& matrix1) const{
        if (m != matrix1.n) {
            throw 1;
        }
        matrix copy(matrix1.v);
        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < matrix1.m; ++j) {
                copy.v[i][j] = 0;
                for (long long k = 0; k < m; ++k) {
                    copy.v[i][j] += ((((v[i][k] + mod) % mod) * ((matrix1.v[k][j] + mod) % mod) + mod) % mod);
                }
            }
        }
        return copy;
    }
    void print() {
        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < m; ++j) {
                cout << v[i][j] << '\t';
            }
            cout << '\n';
        }
    }
    long long rows_count() const {
        return n;
    }
    long long columns_count() const {
        return m;
    }
    long long sum() const {
        long long res = 0;
        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < m; ++j) {
                res += (v[i][j] % mod);
                res %= mod;
            }
        }
        return res;
    }
};

matrix bin_pow(const matrix& m1, long long n) {
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long n, l, m;
    cin >> n >> l >> m;
    vector<long long> first(n), second(n), third(n);
    long long x;
    for (long long i = 0; i < n; ++i) {
        cin >> x;
        first[i] = (x % m);
    }
    for (long long i = 0; i < n; ++i) {
        cin >> x;
        second[i] = (x % m);
    }
    for (long long i = 0; i < n; ++i) {
        cin >> x;//outer
        third[i] = (x % m);
    }
    vector<vector<long long>> start(m, vector<long long>(1, 0));
    for (long long i = 0; i < n; ++i) {
        ++start[first[i] % m][0];
    }
    vector<vector<long long>> dp(m, vector<long long>(m, 0));
    long long bias;
    for (long long i = 0; i < n; ++i) {
        bias = second[i];
        for (long long j = 0; j < m; ++j) {
            ++dp[(j + bias) % m][j];
        }
    }
    matrix m1(start);
    matrix m2(dp);
    matrix final = (bin_pow(m2, l-2) * m1);
    long long ans = 0;
    for (long long i = 0; i < n; ++i) {
        ans = (ans + final.v[(m - third[i] + m - second[i]) % m][0]) % mod;
    }
    cout << ans % mod;
    return 0;
}
