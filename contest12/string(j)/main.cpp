#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
const ll N = 1e5 + 5;
const ll alphabet_size = 26;

inline char to_char(ll i) {
    return (char)(i + 'a');
}

void dfs(ll v, map<char, ll> to[], ll cnt[], ll cnt_used[]) {
    if (cnt_used[v] != -1) {
        return;
    }
    cnt_used[v] = cnt[v];
    for (ll i = 0; i < alphabet_size; ++i) {
        if (to[v][to_char(i)]) {
            ll u = to[v][to_char(i)];
            dfs(u, to, cnt, cnt_used);
            cnt[v] += cnt[u];
        }
    }
}

void add(char c, ll& last, ll& sz, map<char, ll> to[], ll link[], ll len[], ll cnt[], vector<pair<ll, ll>>& order) {
    ll new_last = sz++;
    len[new_last] = len[last] + 1;
    cnt[new_last] = 1;
    order.emplace_back(len[new_last], new_last);
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

            to[clone] = to[q];
            len[clone] = len[p] + 1;
            order.emplace_back(len[clone], clone);
            link[clone] = link[q];
            while (p != -1 && to[p][c] == q) {
                to[p][c] = clone;
                p = link[p];
            }
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
    ll n, k, sz = 0, last = 0;
    n = s.length();
    auto* to = new map<char, ll>[2 * N];
    ll* link = new ll[2 * N];
    ll* len = new ll[2 * N];
    vector<pair<ll, ll>> order;

    cin >> k; k += n;
    len[0] = 0;
    link[0] = -1;
    sz++;
    ll* cnt = new ll[2 * N];
    ll* cnt_used = new ll[2 * N];
    for (ll i = 0; i < 2 * n; ++i) {
        cnt[i] = 0;
        cnt_used[i] = -1;
    }

    for (ll i = 0; i < n; ++i) {
        add(s[i], last, sz, to, link, len, cnt, order);
    }
    sort(order.begin(), order.end());
    reverse(order.begin(), order.end());
    for (auto &p: order) {
        cnt[link[p.second]] += cnt[p.second];
    }
    dfs(0, to, cnt, cnt_used);

    if (cnt[0] < k) {
        cout << "No such line.";
    } else {
        ll curr = 0;
        while (k > cnt_used[curr]) {
            k -= cnt_used[curr];
            for (ll i = 0; i < alphabet_size; ++i) {
                if (to[curr][to_char(i)]) {
                    ll j1 = to[curr][to_char(i)];
                    if (cnt[j1] < k) {
                        k -= cnt[j1];
                    } else {
                        cout << to_char(i);
                        curr = j1;
                        break;
                    }
                }
            }
        }

    }
    delete[] to;
    delete[] link;
    delete[] len;
    delete[] cnt;
    delete[] cnt_used;
    return 0;
}
/*
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;

struct state {
    int len, link, next[26];
    ll cnt = 0, cnt2 = -1;
};

string s;
state st[2 * N];
int n, k, sz, last;
vector<pair<int, int>> order;

void st_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++; last = 0;
}

void dfs(int u) {
    if (st[u].cnt2 != -1) return;
    st[u].cnt2 = st[u].cnt;
    for (int i = 0; i < 26; ++i) {
        if (st[u].next[i]) {
            dfs(st[u].next[i]);
            st[u].cnt += st[st[u].next[i]].cnt;
        }
    }
}

void st_extend(int c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].cnt = 1;
    order.emplace_back(st[cur].len, cur);
    int p = last;
    while (p != -1 && !st[p].next[c]) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].link = st[q].link;
            memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            order.emplace_back(st[clone].len, clone);
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[cur].link = st[q].link = clone;
        }
    }
    last = cur;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> s >> k;
    n = s.length(); k += n;
    st_init();
    for (int i = 0; i < n; ++i) st_extend(s[i] - 'a');
    sort(order.begin(), order.end());
    reverse(order.begin(), order.end());
    for (auto &p: order) {
        st[st[p.second].link].cnt += st[p.second].cnt;
    }

    dfs(0);

    if (st[0].cnt < k) {
        cout << "No such line.";
        return 0;
    }

    int cur = 0;
    while (k > st[cur].cnt2) {
        k -= st[cur].cnt2;
        for (int i = 0; i < 26; ++i) {
            if (st[cur].next[i]) {
                int j = st[cur].next[i];
                if (st[j].cnt < k) k -= st[j].cnt;
                else {
                    cout << (char)(i + 'a');
                    cur = j;
                    break;
                }
            }
        }
    }
    return 0;
}*/
