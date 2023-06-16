#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100000;

bool divide_in_primes(int number, vector<bool> handled_dividers) {
    for (int d = 2; d * d <= number; ++d) {
        if (number % d == 0) {
            if (handled_dividers.at(d) || handled_dividers.at(number / d)) {
                return false;
            }
        }
    }
    if (handled_dividers.at(number)) {
        return false;
    }
    return true;
}

bool is_prime(int number) {
    for (int d = 2; d * d <= number; ++d) {
        if (number % d == 0) {
                return false;
        }
    }
    return true;
}

#include "time.h"
int main() {
//    clock_t start = clock();
//    int* primes = new int[1300000];
    vector<int> primes(2*1000000);

    int prev_prime = 2;
    for (int i = 3; i <= 2*1000000; ++i) {
        if (is_prime(i)) {
            primes.at(prev_prime) = i;
            prev_prime = i;
        }
    }
//    clock_t end = clock();
//    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
//    cout << seconds << '\n';

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
//    n = 100000;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a.at(i);
//        a.at(i) = 2;
    }
    vector<bool> handled_dividers(2*1000000);
//    for (int i = 0; i < MAXN; ++i) {
//        handled_dividers.at(i) = false;
//    }
    int number;
    bool flag;
    int i;
    vector<int> to_add;
    for (i = 0; i < n; ++i) {
        number = a.at(i);
        flag = false;
//        if (number == 2 || number == 3) {
//            handled_dividers.at(number) = true;
//        }
        to_add.clear();
        for (int d = 2; d * d <= number; ++d) {
            if (number % d == 0) {
                if (handled_dividers.at(d) || handled_dividers.at(number / d)) {
                    flag = true;
                    break;
                }
                to_add.push_back(d);
                to_add.push_back(number / d);
//                handled_dividers.at(d) = true;
//                handled_dividers.at(number / d) = true;
            }
        }
        if (flag || handled_dividers.at(number)) {
            goto continue_loop;
        }
        for (int u : to_add) {
            handled_dividers.at(u) = true;
        }
        handled_dividers.at(number) = true;
        cout << number << " ";
    }
    return 0;
    continue_loop:
    while (!divide_in_primes(number, handled_dividers)) {
        ++number;
    }
    cout << number << " "; ++i;
    for (int d = 2; d * d <= number; ++d) {
        if (number % d == 0) {
            handled_dividers.at(d) = true;
            handled_dividers.at(number / d) = true;
        }
    }
    handled_dividers.at(number) = true;
    int counter = 2;
    for (; i < n; ++i) {
        for (;;counter = primes.at(counter)) {
            if (!handled_dividers.at(counter)) {
                break;
            }
        }
        cout << counter << " ";
//        handled_dividers.at(counter) = true;
        counter = primes.at(counter);
    }
    return 0;
}
