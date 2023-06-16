#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;
using std::pair;

typedef long long ll;

//Дерево отрезков

void treebuild(pair<ll, bool> t[], ll a[], ll v, ll tl, ll tr) {
    if (tl == tr) {
        t[v].first = a[tl];
        t[v].second =  true;
    }
    else {
        ll tm = (tl + tr) / 2;
        treebuild(t, a, 2*v, tl, tm);
        treebuild(t, a, 2*v + 1, tm + 1, tr);
        if (t[2*v].second && t[2*v+1].second) {
            t[v].first = t[2*v].first - t[2*v+1].first;
        } else {
            t[v].first = t[2*v].first + t[2*v+1].first;
        }
        t[v].second = false;
    }
}

pair<ll, bool> alternating_sum(pair<ll, bool> t[], ll v, ll tl, ll tr, ll l, ll r) {
    if (l > r) {
        return {0, 0};
    }
    if (l == tl && r == tr) {
        if ((tr - tl) % 2 != 0) {
            return {t[v].first, false}; // false когда отрезок четной длины
        }
        else {
            return {t[v].first, true};
        }
//        return t[v];
    }
    ll tm = (tl + tr) / 2;
    pair<ll, bool> p1 = alternating_sum(t, 2*v, tl, tm, l, min(r, tm));
    pair<ll, bool> p2 = alternating_sum(t, 2*v + 1, tm + 1, tr, max(l, tm + 1), r);
    pair<ll, bool> p3;
//    p3.second = false;
    if (p1.second && p2.second) {
        p3.first = p1.first - p2.first;
        p3.second = false;
    }
    if (!p1.second && p2.second) {
        p3.first = p1.first + p2.first;
        p3.second = true;
//        if (p1.first == 0) {
//            p3.second = true;
//        }
    }
    if (p1.second && !p2.second) {
        p3.first = p1.first - p2.first;
        p3.second = true;
//        if (p1.first == 0) {
//            p3.second = true;
//        }
    }
    if (!p1.second && !p2.second) {
        p3.first = p1.first + p2.first;
        p3.second = false;
    }
    return p3;
}

void assign(pair<ll, bool> t[], ll v, ll tl, ll tr, ll pos, ll new_value) {
    if (tl == tr) {
        t[v].first = new_value;
//        t[v].second = true;
    }
    else {
        ll tm = (tl + tr) / 2;
        if (pos <= tm) {
            assign(t, 2*v, tl, tm, pos, new_value);
        }
        else {
            assign(t, 2*v + 1, tm + 1, tr, pos, new_value);
        }
        if (t[2*v].second && t[2*v+1].second) {
            t[v].first = t[2*v].first - t[2*v+1].first;
        } else {
            t[v].first = t[2*v].first + t[2*v+1].first;
        }
//        t[v].second = false;
    }
}

int main() {
    ll n, m;
    cin >> n;
    ll n1 = n;
    while((n & (n-1)) != 0) {
        ++n;
    }
    pair<ll, bool> t[4 * n];
    ll a[n];
    ll x, l, r;
    for (ll i = 0; i < n1; ++i) {
        cin >> x;
        a[i] = x;
    }
    for (ll i = n1; i < n; ++i) {
        a[i] = 0;
    }
    treebuild(t, a, 1, 0, n-1);
    cin >> m;
    for (ll i = 0; i < m; ++i) {
        cin >> x;
        cin >> l >> r;
        if (x == 0) {
            assign(t, 1, 0, n-1, l-1, r);
        }
        if (x == 1) {
            cout << alternating_sum(t, 1, 0, n-1, l-1, r-1).first << '\n';
        }
    }
    return 0;
}
