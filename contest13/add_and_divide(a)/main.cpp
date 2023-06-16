#include <iostream>

const long long p = 1000000007;

inline long long mod_p(long long x) {
    return (x + p) % p;
}

long long bin_power(long long x, long long y) {
    long long res = 1;
    while (y) {
        if (y % 2 == 1) {
            res = (mod_p(res) * mod_p(x)) % p;
        }
        x = (mod_p(x) * mod_p(x)) % p;
        y = y >> 1;
    }
    return res;
}

int main() {
    long long a, b, c, d;
    std::cin >> a >> b >> c >> d;
    a = mod_p(mod_p(a) * mod_p(d));
    c = mod_p(mod_p(b) * mod_p(c));
    std::cout << ((((a + c) % p ) * bin_power(mod_p(b), p-2)) % p) * bin_power(mod_p(d), p-2) %p;
    return 0;
}
