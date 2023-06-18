#include <iostream>
#include <map>
#include <vector>

using namespace std;

using ll = long long;
const ll N = 1e5 + 5;
const ll alphabet_size = 26;

inline char to_char(ll i) {
    return (char)(i + 'a');
}

void dfs(ll v, map<char, ll> to[], ll cnt[], bool used[]) {
    cnt[v] = (v != 0);
    for (ll i = 0; i < alphabet_size; ++i) {
        ll u = to[v][to_char(i)];
        if (u) {
            if (!used[u]) {
                dfs(u, to, cnt, used);
                cnt[v] += cnt[u];
            }
        }
    }
    used[v] = true;
}

void add(char c, ll& last, ll& sz, map<char, ll> to[], ll link[], ll len[]/*, bool term[] */, ll cnt[]) {
    ll new_last = sz++;
    len[new_last] = len[last] + 1;
    cnt[new_last] = 0;
    ll p = last;
    while(p != -1 && to[p].find(c) == to[p].end()) {
        to[p][c] = new_last;
        p = link[p];
    }
    if (p == -1) {
        link[new_last] = 0;
    } else {
        ll q = to[p][c];
        if (len[q] == len[p] + 1) {
            link[new_last] = q;
        } else {
            ll clone = sz++;
            while (p != -1 && to[p][c] == q) {
                to[p][c] = clone;
                p = link[p];
            }
            to[clone] = to[q];
            len[clone] = len[p] + 1;
            link[clone] = link[q];
            link[q] = clone;
            link[new_last] = clone;
        }
    }
    last = new_last;
}

void max_lex_string(ll v, map<char, ll> to[]) {
    for (ll i = alphabet_size - 1; i >= 0; --i) {
        if (to[v][to_char(i)]) {
            ll u = to[v][to_char(i)];
            cout << to_char(i);
            max_lex_string(u, to);
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    string s;
    cin >> s;
    ll n, k, sz = 0, last = 0;
    n = s.length();
    auto* to = new map<char, ll>[2 * n];
    ll* link = new ll[2 * n];
    ll* len = new ll[2 * n];

    cin >> k;
    len[0] = 0;
    link[0] = -1;
    sz++;
    ll* cnt = new ll[2 * n];
    bool* used = new bool[2 * n];
    for (ll i = 0; i < 2 * n; ++i) {
        cnt[i] = 0;
        used[i] = false;
    }

    for (ll i = 0; i < n; ++i) {
        add(s[i], last, sz, to, link, len, cnt);
    }
//    for (int i = 0; i < sz; ++i) {
//        cout << i << " ";
//        for (auto j : to[i]) {
//            cout << j.second << " " << j.first << " ";
//        }
//        cout << '\n';
//    }
//    cout << to[0]['b'] << '\n';
    dfs(0, to, cnt, used);
//    cout << cnt_sum[0] << '\n';
//    cout << cnt[0] << '\n';
//    for (ll i = 0; i < sz; ++i) {
//        cout << i << " " << cnt[i] << '\n';
//    }
//    for (int j = 1; j < cnt[0] + 2; ++j) {
//        k = j;
    if (cnt[0] < k) {
//            max_lex_string(0, to);
        k = cnt[0];
    }
    ll curr = 0;
    string ans;
    while (k > 0) {
        for (ll i = 0; i < alphabet_size; ++i) {
            if (to[curr][to_char(i)]) {
                ll j1 = to[curr][to_char(i)];
                if (cnt[j1] >= k) {
                    k -= 1;
                    ans.push_back(to_char(i));
                    curr = j1;
                    break;
                }
                k -= cnt[j1];
            }
        }
    }


    cout << ans;
//    }
    delete[] to;
    delete[] link;
    delete[] len;
    delete[] cnt;
    delete[] used;
    return 0;
}
