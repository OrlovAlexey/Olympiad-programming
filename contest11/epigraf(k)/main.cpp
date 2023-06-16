#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

long long z_function(const string& s) {
    long long n = s.length();
    vector<long long> z(n);
    long long l = 0;
    long long r = 0;
    long long max_z = 0;
    for (long long i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
        max_z = std::max(max_z, z[i]);
    }
    return max_z;
}
int main() {
    string s;
    cin >> s;
    long long n = s.size();
    string t;
    for (long long i = 0; i < n; ++i) {
        t.push_back(s[n-i-1]);
    }
    string normal_string;
    string reversed_string;
    long long max_z;
    long long answer = 0;
    for (long long i = 0 ; i < n; ++i) {
        normal_string += s[i];
        reversed_string = s[i] + reversed_string;
        max_z = z_function(reversed_string);
        answer += (normal_string.length() - max_z) * (normal_string.length() + max_z + 1) / 2;
    }
    cout << answer;
    return 0;
}
