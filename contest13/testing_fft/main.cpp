#include <iostream>
#include <vector>

using namespace std;

const int mod = 7340033;

using field = long long;
const long long big_constant = mod * (long long)100000000;

field bin_pow_mod(field a, int n) {
    field res = 1;
    while (n) {
        if (n % 2) {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        n /= 2;
    }
    return res;
}

field inverse_in_field_mod(field a) {
    if (a == 0) {
        throw 1;
    }
    return bin_pow_mod(a, mod - 2);
}

const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1 << 20;

void fft(vector<field> &a, int k, const vector<int>& rev, bool invert) {
    int n = (int) a.size();

    vector<field> new_ord(n);
    for (int i = 0; i < n; ++i) {
        new_ord[i] = a[rev[i]];
    }

    field w = (invert ? root_1 : root);
    w = bin_pow_mod(w, (1 << (20 - k)));
    for (int j = 0; j < k; ++j) { // len = 2^(j+1)
        field v = bin_pow_mod(w, 1 << (k - j - 1));
        for (int i = 0; i < (1 << k); i += (1 << (j + 1))) {
//            field w_n = 1;
            for (int s = 0; s < (1 << j); ++s) {
                field x = a[i + s];
                field y = a[i + s + (1 << j)];
                field w_n = bin_pow_mod(v, s);
                a[i + s] = x + (w_n * y) % mod;
                a[i + s + (1 << j)] = (x + mod - (w_n * y) % mod) % mod;
//                w_n = field((w_n * v) % mod);
            }
        }
    }
    if (invert) {
        field n_inv = inverse_in_field_mod(n);
        for (int i = 0; i < n; ++i) {
            a[i] = field(a[i] * n_inv % mod);
        }
    }
}

field norm(field a) {
    while (a < 0) {
        a += mod;
    }
    return (a % mod);
}

void make_rev(vector<int>& rev, int k) {
    rev[0] = 0;
    int oldest = -1;
    for (int mask = 1; mask < (1 << k); ++mask) {
        if (!(mask & (mask - 1))) {
            ++oldest;
        }
        rev[mask] = rev[mask ^ (1 << oldest)] | (1 << (k - oldest - 1));
    }
}

void multiply(const vector<field>& a_int, const vector<field>& b_int, vector<field>& res, vector<int>& rev) {
//    vector<field> a(a_int.begin(), a_int.end()),  b(b_int.begin(), b_int.end());
    vector<field> a(a_int.size()), b(b_int.size());
    for (int i = 0; i < a.size(); ++i) {
        a[i] = norm(a_int[i]);
    }
    for (int i = 0; i < b.size(); ++i) {
        b[i] = norm(b_int[i]);
    }
    size_t n = 1;
    int k = 1;
    while (n < max(a.size(), b.size())) {
        n *= 2;
        ++k;
    }
    n *= 2;
    rev.resize(n);
    make_rev(rev, k);
    a.resize(n), b.resize(n);

    fft(a, k, rev, false);
    fft(b, k, rev, false);
    for (size_t i = 0; i < n; ++i) {
        a.at(i) *= b.at(i);
        a.at(i) %= mod;
    }
    fft(a, k, rev, true);

    res.resize(n);
    for (size_t i = 0; i < n; ++i) {
//        res.at(i) = (field(round(a.at(i).real())) + big_constant) % mod;
        res.at(i) = a.at(i) % mod;
    }
}


int main() {
    int n, m;
    cin >> n;
    vector<field> a(n + 1);
    int temp;
    for (int i = 0; i <= n; ++i) {
        cin >> temp;
        a[i] = temp;
    }
    cin >> m;
    vector<field> b(m + 1);
    for (int i = 0; i <= m; ++i) {
        cin >> temp;
        b[i] = temp;
    }
    vector<int> rev;
    vector<field> result;
    multiply(a, b, result, rev);
    cout << n + m << " ";
    for(int i = 0; i <= n + m; ++i) {
        cout << result[i] % 10 << " ";
    }
    return 0;
}
