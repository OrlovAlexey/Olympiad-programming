#include <iostream>

using namespace std;

int gcd(int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int easy_case = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 1) {
            easy_case++;
        }
    }
    if (easy_case > 0) {
        cout << n - easy_case;
        return 0;
    }
    int min_seq_gcd = n;
    int curr_gcd;
    for (int i = 0; i < n; ++i) {
        curr_gcd = a[i];
        for (int j = i + 1; j < n; ++j) {
            curr_gcd = gcd(curr_gcd, a[j]);
            if (curr_gcd == 1) {
                min_seq_gcd = min(min_seq_gcd, j - i);
            }
        }
    }
    if (min_seq_gcd == n) {
        cout << -1;
        return 0;
    }
    cout << min_seq_gcd + n - 1;
    return 0;
}
