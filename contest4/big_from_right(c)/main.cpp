#include <iostream>

using namespace std;

void build(int t[], int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    }
    else {
        int tm = (tl + tr) / 2;
        build(t, a, 2*v, tl, tm);
        build(t, a, 2*v + 1, tm + 1, tr);
        t[v] = max(t[2*v], t[2*v+1]);
    }
}

int get_max(int t[], int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return -1;
    }
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return max(get_max(t, 2 * v, tl, tm, l, min(r, tm)), get_max(t, 2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
}

void assign(int t[], int v, int tl, int tr, int pos, int value) {
    if (tl == tr) {
        t[v] = value;
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            assign(t, 2*v, tl, tm, pos, value);
        }
        else {
            assign(t, 2*v + 1, tm + 1, tr, pos, value);
        }
        t[v] = max(t[2*v], t[2*v+1]);
    }
}

int find_k(int t[], int n, int v, int tl, int tr, int i, int x) {
    if (x > t[v]) {
        return -2;
    }
    if (tl == tr) {
//        if (i <= tl) {
            return tl;
//        }
//        else {
//            return -2;
//        }
    }
    int tm = (tl + tr) / 2;
    if (get_max(t, 1, 0, n-1, i, tm) >= x) {
//        int p1 = find_k(t, 2*v, tl, tm, i, x);
//        int p2 = find_k(t, 2*v + 1, tm + 1, tr, i, x);
//        if (p1 == -2) {
//            return p2;
//        }
//        else {
//            return p1;
//        }
        return  find_k(t, n, 2*v, tl, tm, i, x);
    }
    else {
        return find_k(t, n, 2*v + 1, tm + 1, tr, i, x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int t[4*n];
    build(t, a, 1, 0, n-1);
    int r, i, x;
    for (int j = 0; j < m; ++j) {
        cin >> r >> i >> x;
        if (r == 0) {
            assign(t, 1, 0, n-1, i-1, x);
        }
        if (r == 1) {
            cout << find_k(t, n, 1, 0, n-1, i-1, x) + 1 << '\n';
        }
    }
    return 0;
}

