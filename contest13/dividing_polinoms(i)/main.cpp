#include <iostream>
#include <complex>
#include <vector>

#define M_PI  3.14159265358979323846

using namespace std;
using cmplx = complex<long double>;
using field = long long;
const long long big_constant = 7 * 100000000;


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
//            a.at(i) /= 2;
//            a.at(i + (n / 2)) /= 2;
////            a.at(i) *= 4;
////            a.at(i + (n / 2)) *= 4;
//        }
//        w_n *= w;
//    }
//}

const int MAXN = 65536 * 2 + 1;
const int LOG_MAXN = 16;
int rev[MAXN];

void calc_rev(int k) {
    rev[0] = 0;
    int oldest = -1;
    for (int mask = 1; mask < k; ++mask) {
        if (!(mask & (mask - 1))) {
            ++oldest;
        }
        rev[mask] = rev[mask ^ (1 << oldest)] | (k / (1 << (oldest + 1)));
    }
}

void fft(vector<cmplx> &a, bool is_invert) {
    int n = a.size();
    calc_rev(n);
    for (int i = 0; i < n; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * M_PI / len * (is_invert ? -1 : 1);
        cmplx wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cmplx w(1);
            for (int j = 0; j < len / 2; ++j) {
                cmplx u = a[i + j];
                cmplx v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (is_invert) {
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
}

void multiply(const vector<field>& a_int, size_t a_size, const vector<field>& b_int, vector<field>& res) {
    vector<cmplx> a, b(b_int.begin(), b_int.end());
//    vector<cmplx> a(a_int.size()), b(b_int.size());
//    for (int i = 0; i < max(a_int.size(), b_int.size()); ++i) {
//        if (i < a_int.size()) a[i] = a_int[i];
//        if (i < b_int.size()) b[i] = b_int[i];
//    }
    size_t n = 1;
    while (n < max(a_size, b_int.size())) {
        n *= 2;
    }
    n *= 2;
    a.resize(n), b.resize(n);
    if (n >= a_int.size()) a = vector<cmplx>(a_int.begin(), a_int.end());
    else {
        for (int i = 0; i < n; ++i)
            a[i] = a_int[i];
    }
    a.resize(n);

    fft(a, false);
    fft(b, false);
    for (size_t i = 0; i < n; ++i) {
        a.at(i) *= b.at(i);
    }
    fft(a, true);

    res.resize(n);
    for (size_t i = 0; i < n; ++i) {
        res.at(i) = (field(round(a.at(i).real())) + big_constant) % 7;
    }
}

int inverse_in_field_7(int a) {
    int number = a;
    switch (number) {
        case 1:
            return int(1);
        case 2:
            return int(4);
        case 3:
            return int(5);
        case 4:
            return int(2);
        case 5:
            return int(3);
        case 6:
            return int(6);
        default:
            throw 1;
    }
}


void inverse_polinom(vector<field>& a, double t, vector<field>& res) {
    if (t == 1) {
        res.at(0) = inverse_in_field_7(a.at(0));
        return;
    }
    int n = (int)t;
    vector<field> a_0(n);
    inverse_polinom(a, ceil(t / 2), a_0);
    a_0.resize(n);

    vector<field> temp1, temp2;
    multiply(a, n,  a_0, temp1);
    temp1.at(0) = temp1.at(0) - 1;
    multiply(temp1, n, a_0, temp2);
    res.resize(n);
    for (int i = 0; i < n; ++i) {
        res.at(i) = (a_0.at(i) - temp2.at(i) + 7) % 7;
//        cout << res.at(i) << " ";
    }
//    cout << endl;
    // (x^3+2x^2-1) mod x^2 = .at(x + 2 - 1/x^2)
}

void reverse(vector<field>& a) {
    vector<field> b;
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        b.push_back(a.at(n - 1 - i));
    }
    a = b;
}
void out(vector<field>&& b) {
    bool flag = false;
    int size;
    for (int i = 0; i < b.size(); ++i) {
        if (b.at(b.size() - 1 - i) != 0){
            size = i;
            cout << b.size() - 1 - i << " ";
            flag = true;
            break;
        }
    }
    if (!flag) {
        cout << 0 << " " << 0 << '\n';
        return;
    }
    reverse(b);
    for (int i = size; i < b.size(); ++i) {
        cout << b.at(i) << " ";
    } cout << '\n';
}
#include <time.h>

int main() {
//    clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//    calc_rev(MAXN, LOG_MAXN);

    srand(time(0));
//    while (true) {
//        cout << 1 << endl;
//        start:
        int n, m;
//        cin >> n;
//        n = rand() % 50000 + 1;
        n = 50000;
        vector<field> a(n + 1);
        field temp;
        for (int i = 0; i <= n; ++i) {
//            cin >> temp;
            temp = rand() % 7;
            while (i ==0 && temp == 0) {
                temp = rand() % 7;
            }
            a.at(n - i) = temp;
        }
//        cin >> m;
//        m = rand() % 50000 + 1;
        m = 49000;
        vector<field> b(m + 1);
        for (int i = 0; i <= m; ++i) {
//            cin >> temp;
            temp = rand() % 7;
            while (i ==0 && temp == 0) {
                temp = rand() % 7;
            }
            b.at(m - i) = temp;
        }
        if (n <= m - 1) {
            out(vector<field>());
            out(std::move(a));
//            goto start;
            return 0;
        }
        reverse(a);
        reverse(b);
        b[0] = 2;
        b[1] = 5;
        b[2] = 6;
        vector<field> inverse_b(m);
        inverse_polinom(b, n - m + 1, inverse_b);
//        b.resize(m + 1);
        inverse_b.resize(n - m + 1);
        vector<field> d;
        multiply(a, a.size(), inverse_b, d);
        d.resize(n - m + 1);
        reverse(d);
        reverse(a);
        reverse(b);
        vector<field> mult_b_d;
        multiply(b, b.size(), d, mult_b_d);
        vector<field> r(m);
        for (int i = 0; i < m; ++i) {
            r.at(i) = (a.at(i) - mult_b_d.at(i) + 7) % 7;
        }
        out(std::move(d));
        out(std::move(r));
//    }
//    clock_t end = clock();
//    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
//    cout << seconds;
    return 0;
}
