#include <iostream>

using std::pair;
using std::max;
using std::min;
using std::cin;
using std::cout;

typedef long long ll;

//struct three {
//    ll first;
//    ll second;
//    ll third;
//};

void build (pair<ll, ll> t[], ll a[], ll v, ll tl, ll tr) {
    if (tl == tr) {
        t[v].first = a[tl];
        t[v].second = a[tl];
//        t[v].third = 1;
    }
    else {
        ll tm = (tl + tr) / 2;
        build (t, a, v*2, tl, tm);
        build (t, a, v*2+1, tm+1, tr);
        t[v].first = -1;
        t[v].second = min(t[v*2].second, t[v*2+1].second);
//        t[v].third = t[v*2].third + t[v*2+1].third;
    }
}// в первой координате проталкиваемая вершина, во второй минимум на отрезке

void push(pair<ll, ll> t[], ll v) {
    if (t[v].first != -1) {
        t[2*v].first = t[2*v+1].first = t[v].first;
        t[2*v+1].second = t[2*v].second = t[v].second;
        t[v].first = -1;
    }
}

void assign(pair<ll, ll> t[], ll v, ll tl, ll tr, ll l, ll r, ll value) {
    if (l > r) {
        return;
    }
    if (l == tl && tr == r) {
        t[v].first = value;
        t[v].second = value;
    }
    else {
        push(t, v);
        ll tm = (tl + tr) / 2;
        assign(t, 2*v, tl, tm, l, min(r, tm), value);
        assign(t, 2*v + 1, tm + 1, tr, max(l, tm+1), r, value);
        t[v].second = min(t[v*2].second, t[v*2+1].second);
    }
}

ll get_min(pair<ll, ll> t[], ll v, ll tl, ll tr, ll l, ll r) {
    if (l > r) {
        return 100001;
    }
    if (tl == l && tr == r) {
        return t[v].second;
    }
    push (t, v);
    ll tm = (tl + tr) / 2;
    return min(get_min(t, v*2, tl, tm, l, min(r,tm)), get_min(t, v*2+1, tm+1, tr, max(l,tm+1), r));

}

int main() {
    ll n, m;
    cin >> n;
    ll a[n];
    ll r, g, b;
    for (ll i = 0; i < n; ++i) {
        cin >> r >> g >> b;
        a[i] = r + g + b;
    }
    pair<ll, ll> tree[4*n];
    build(tree, a, 1, 0, n-1);
    cin >> m;
    ll c, d, e, f;
    for (ll i = 0; i < m; ++i) {
        cin >> c >> d >> r >> g >> b >> e >> f;
        assign(tree, 1, 0, n-1, c, d, r + g + b);
        cout << get_min(tree, 1, 0, n-1, e, f) << " ";
    }
    return 0;
}
