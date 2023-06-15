#include <iostream>
using namespace std;

typedef long long ll;

struct node {
    ll value;
    ll lb, rb;
//    node& operator= (node n) {
//        swap(n);
//        return *this;
//    }
//    void swap (node& n) {
//        std::swap(value, n.value);
//        std::swap(lb, n.lb);
//        std::swap(rb, n.rb);
//    }
};

struct interval_tree {
    const ll MAXN = 200000;
    node* t;

    interval_tree(int n){
        t = new node[4 * n];
        for (ll i = 0; i < 4 * n; ++i) {
            t[i].value = 0;
            t[i].lb = 0;
            t[i].rb = 0;
        }
    }

    void build(ll a[], ll v, ll tl, ll tr, ll x) {
        if (tl == tr) {
//            t[v].value = a[tl];
            t[v].value = a[tl];
            t[v].lb = 0;
            t[v].rb = x;
        } else {
            ll tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm, x);
            build(a, v * 2 + 1, tm + 1, tr, x);
        }
    }

    void update(ll v, ll tl, ll tr, ll l, ll r, ll x) { // l = y1, r = y2
        if (l > r)
            return;
        if (tl == l && tr == r) {
//        t[v].value += x;
            if (t[v].lb < x && x < t[v].rb) {
                if (x - t[v].lb < t[v].rb - x) {
                    t[v].lb = x;
                } else {
                    t[v].rb = x;
                }
            }
        } else {
            ll tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), x);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
        }
    }

    ll get(ll v, ll tl, ll tr, ll pos) {
        if (tl == tr)
            return t[v].rb - t[v].lb;
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            return max(t[v].rb - t[v].lb, get(v * 2, tl, tm, pos));
        else
            return max(t[v].rb - t[v].lb, get(v * 2 + 1, tm + 1, tr, pos));
    }

    ~interval_tree(){
        delete[] t;
    }
};

int main() {
    ll n, y, x;
    cin >> n >> y >> x;
    interval_tree tree(y);
    ll* a = new ll[y+1];
    for (int i = 0; i < y+1; ++i) {
        a[i] = i;
    }
    tree.build(a, 1, 0, y, x);

    for (int i = 0; i < 4*y; ++i) {
        cout << i<< '\t' << tree.t[i].value << '\t' << tree.t[i].lb << '\t' << tree.t[i].rb << '\n';
    }

    ll x1, y1, y2;
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> y2;
        tree.update(1, 0, y, y1, y2, x1);
    }

    for (int i = 0; i < 4*y; ++i) {
        cout << i<< '\t' << tree.t[i].value << '\t' << tree.t[i].lb << '\t' << tree.t[i].rb << '\n';
    }

    for (int i = 0; i < y; ++i) {
        cout << tree.get(1, 0, y, i) << '\n';
    }
    return 0;
}
