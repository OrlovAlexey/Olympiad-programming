#include <iostream>
#include <vector>
#include <complex>

using namespace std;

#define M_PI  3.14159265358979323846
const int mod = 7340033;
using cmplx = complex<long double>;

using field = long long;
const long long big_constant = mod * (long long)100000000;

field bin_pow_mod(field a, int n) {
    field res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        n >>= 1;
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
const int root_pw = 1<<20;

//void fft(vector<long long>& a, bool is_invert) {
//    int n = (int)a.size();
//    if (n == 1) {
//        return;
//    }
//
//    vector<long long> a_even(n / 2), a_odd(n / 2);
//    for (int i = 0; 2 * i < n; ++i) {
//        a_even.at(i) = a.at(2 * i);
//        a_odd.at(i) = a.at(2 * i + 1);
//    }
//    fft(a_even, is_invert);
//    fft(a_odd, is_invert);
//
////    double angle = 2.0 * M_PI / n;
////    if (is_invert) {
////        angle *= -1;
////    }
////    cmplx w_n(1.0, 0.0),  w(cos(angle), sin(angle));
//    long long _inv_2 = inverse_in_field_mod(2);
//    long long w_n(1), w(is_invert ? root_1 : root);
//    for (int i = 0; i < (n / 2); ++i) {
//        a.at(i) = (a_even.at(i) + (w_n * a_odd.at(i) % mod)) % mod;
//        a.at(i + (n / 2)) = ( a_even.at(i) + mod - (w_n * a_odd.at(i) % mod) ) % mod;
//        if (is_invert) { // dividing on n = 2^k
////            a.at(i) /= 2;
////            a.at(i + (n / 2)) /= 2;
//            a.at(i) *= _inv_2;
//            a.at(i) %= mod;
//            a.at(i + (n / 2)) *= _inv_2;
//            a.at(i + (n / 2)) %= mod;
//        }
//        w_n *= w;
//        w_n %= mod;
//    }
//}
//
//void fft(vector<cmplx>& a, bool is_invert) {
//    int n = (int)a.size();
//    if (n == 1) {
//        return;
//    }
//
//    vector<cmplx> a_even(n / 2), a_odd(n / 2);
//    for (int i = 0; 2 * i < n; ++i) {
//        a_even.at(i) = a.at(2 * i);
//        a_odd.at(i) = a.at(2 * i + 1);
//    }
//    fft(a_even, is_invert);
//    fft(a_odd, is_invert);
//
//    double angle = 2.0 * M_PI / n;
//    if (is_invert) {
//        angle *= -1;
//    }
//    cmplx w_n(1.0, 0.0),  w(cos(angle), sin(angle));
//    for (int i = 0; i < (n / 2); ++i) {
//        a.at(i) = a_even.at(i) + (w_n * a_odd.at(i));
//        a.at(i + (n / 2)) = a_even.at(i) - (w_n * a_odd.at(i));
//        if (is_invert) { // dividing on n = 2^k
////            a.at(i) /= 2;
////            a.at(i + (n / 2)) /= 2;
//            a.at(i) *= 4;
//            a.at(i + (n / 2)) *= 4;
//        }
//        w_n *= w;
//    }
//}

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


void inverse_polinom(const vector<field>& a, long long t, vector<field>& res, vector<int>& rev) {
    if (t == 1) {
        res.at(0) = inverse_in_field_mod(a.at(0));
        return;
    }
    vector<field> a_0(t);
    inverse_polinom(a, t / 2 + (t % 2), a_0, rev);

    vector<field> temp1, temp2;
    multiply(a, a_0, temp1, rev);
    temp1.at(0) = temp1.at(0) - 1;
    multiply(temp1, a_0, temp2, rev);
    res.resize(t);
    a_0.resize(t);
    for (int i = 0; i < t; ++i) {
        res.at(i) = (a_0.at(i) - temp2.at(i) + mod) % mod;
    }
}

#include <time.h>

int main() {
//    srand(time(0));
//    while (true) {
        int n, m;
        cin >> m >> n;
//        m = rand() % 10000, n = rand() % 10000;
//        m = 200, n = 200;
        vector<field> p(n + 1);
        for (int i = 0; i < n + 1; ++i) {
            cin >> p[i];
//            p[i] = rand() % mod;
        }
        if (p[0] == 0) {
            cout << "The ears of a dead donkey";
            return 0;
        }
//        p[0] = 6126346;
        vector<field> q(n + 1);
        vector<int> rev;
        inverse_polinom(p, m, q, rev);
        for (int i = 0; i < m; ++i) {
            cout << q[i] << " ";
        }
//        vector<field> res;
//        multiply(p, q, res);
//        for (int i = 0; i < m; ++i) {
//            if (i == 0 && res[i] != 1)
//                throw 1;
//            if (i != 0 && res[i] != 0)
//                throw 1;
//        }
//        cout << "yes" << endl;
//    }
    return 0;
}
// (2149956 * 3921871) / 7340033