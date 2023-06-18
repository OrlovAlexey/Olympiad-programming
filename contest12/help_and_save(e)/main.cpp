#include <iostream>
#include <map>

using namespace std;

using ll = long long;
const ll N = 1e5 + 5;
const ll alphabet_size = 26;

inline char to_char(ll i) {
    return (char)(i + 'a');
}

void dfs(ll v, map<char, ll> to[], ll cnt[], ll cnt_used[]) {
    cnt[v] = (v != 0);
    for (ll i = 0; i < alphabet_size; ++i) {
        ll u = to[v][to_char(i)];
        if (u) {
            if (cnt_used[u] == -1) {
                dfs(u, to, cnt, cnt_used);
                cnt[v] += cnt[u];
            }
        }
    }
    cnt_used[v] = 1;
}

void add(char c, ll& last, ll& sz, map<char, ll> to[], ll link[], ll len[], ll& new_substrings) {
    ll new_last = sz++;
    len[new_last] = len[last] + 1;
    new_substrings = len[new_last];
    ll p = last;
    while(p != -1 && to[p].find(c) == to[p].end()) {
        to[p][c] = new_last;
        p = link[p];
    }
    if (p == -1) {
        link[new_last] = 0;
    } else {
        ll q = to[p][c];
        new_substrings -= len[p] + 1;
        if (len[q] == len[p] + 1) {
            link[new_last] = q;
        } else {
            ll clone = sz++;
            len[clone] = len[p] + 1;
            while (p != -1 && to[p][c] == q) {
                to[p][c] = clone;
                p = link[p];
            }
            to[clone] = to[q];
            link[clone] = link[q];
            link[q] = clone;
            link[new_last] = clone;
        }
    }
    last = new_last;
}

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    string s;
    cin >> s;
    ll n = s.length(), sz = 0, last = 0;
    auto* to = new map<char, ll>[2 * n];
    ll* link = new ll[2 * n];
    ll* len = new ll[2 * n];

    len[0] = 0;
    link[0] = -1;
    sz++;

    ll answer = 0;
    ll new_substrings;
    for (ll i = 0; i < n; ++i) {
        add(s[i], last, sz, to, link, len, new_substrings);
        cout << (answer += new_substrings) << '\n';
//        for (int j = 0; j < sz; ++j) {
//            cout << j << " ";
//            for (auto k : to[j]) {
//                cout << k.second << " " << k.first << " ";
//            }
//            cout << " | " << link[j]<< '\n';
//        }
//        cout << '\n';
    }
    
    return 0;
}
