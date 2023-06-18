#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

typedef long long ll;

ll f(ll x) {
    return x & (x+1);
}

ll g(ll x) {
    return x | (x+1);
}

struct Point {
    ll x;
    ll y;
    ll w;
};

bool cmp_y(Point a, Point b) {
    return a.y < b.y;
}

void build(vector<ll> s, vector<Point> a, ll n) {
    ll p[n];
    p[0] = a[0].w;
    for (ll i = 0; i < n-1; ++i) {
        p[i+1] = p[i] + a[i+1].w;
    }
    for (ll i = 0; i < n; ++i) {
        if (f(i) > 0) {
            s[i] = p[i] - p[f(i) - 1];
        }
        else {
            s[i] = p[i];
        }
    }
}

ll get_sum(vector<ll> s, ll pos) {
    ll ans = 0;
    for (ll i = pos; i >= 0; i = f(i) - 1) {
        ans += s[i];
    }
    return ans;
}

void update(vector<ll> s, vector<Point> a, ll n, ll pos, ll value) {
    ll prev_value = a[pos].w;
    for (ll i = pos; i < n; i = g(i)) {
        s[i] += (value - prev_value);
    }
    a[pos].w = value;
}

void bid_build(vector<vector<ll>> s, vector<vector<Point>> a, ll n) {
    vector<vector<ll>> p(n);
    for (ll i = 0; i < a[0].size(); ++i) {
        p[0][i] = a[0][i].w;
    }
    for (ll i = 0; i < n-1; ++i) {
        for (ll j = 0; j < p[i].size(); ++j) {
            p[i+1][j] = p[i][j] + a[i+1][j].w;
        }
    }
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < s[i].size(); ++j) {
            if (f(i) > 0) {
                s[i][j] = p[i][j] - p[f(i) - 1][j];
            }
            else {
                s[i][j] = p[i][j];
            }
        }
    }
}

ll big_get_sum(vector<vector<ll>> s, ll x, ll y) {
    ll ans = 0;
    for (ll i = x; i >= 0; i = f(i) - 1) {
        for (ll j = 0; j < s[i].size(); ++j) {
            ans += s[i][j];
        }
    }
    return ans;
}

void big_update(vector<vector<ll>> s, vector<vector<Point>> a, ll n, ll x, ll y, ll value) {
    ll pos;
    for (ll i = n-1; i >= 0; i = f(i)) {
        if (x <= i && x >= f(i)) {
            pos = i;
            break;
        }
    }
    for (ll i = pos; i < n; i = g(i)) {
//        for (ll j = 0; j < s[i].size(); ++j) {
//            s[i][j] += (value - a[pos][j].w);
//        }
        update(s[i], a[i], n, y, value);
    }
}

int main() {
    ll n;
    cin >> n;
    Point a[n];
    for (ll i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].w;
    }
    vector<ll> xs;
    vector<ll> ys;
    for (Point p : a) {
        xs.push_back(p.x);
        ys.push_back(p.y);
    }
    std::sort(xs.begin(), xs.end());
    std::sort(ys.begin(), ys.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
    for (Point& p : a) {
        p.x = ll(std::lower_bound(xs.begin(), xs.end(), p.x) - xs.begin());
        p.y = ll(std::lower_bound(ys.begin(), ys.end(), p.y) - xs.begin());
    }// сжатие координат

    vector<vector<Point>> L(n);
    ll size = 0;
    for (ll i = n-1; i >= 0; i = f(i)) {
        for (Point p : a) {
            if (p.x <= i && p.x >= f(i)) {
                L[i].push_back(p);
            }
        }
        ++size;
    }// создание много деревьев фенвика
    vector<vector<ll>> tree(size);
    for (ll i = n-1; i >= 0; i = f(i)) {
        std::sort(L[i].begin(), L[i].end(), cmp_y);
        build(tree[i], L[i], size);
    }// сортировка по y и билд

//    ll fy[n];
//    build(fy, ys, n);


//    ll s[n];
//    build(s, a, n);
//    update(s, a, n, 3, 7);
//    for (ll i = 0; i < n; ++i) cout << a[i] << '\t';
//    cout << '\n';
//    for (ll i = 0; i < n; ++i) cout << s[i] << '\t';
//    cout << '\n';
//    for (ll i = 0; i < n; ++i) cout << get_sum(s, i) << '\t';
    return 0;
}
