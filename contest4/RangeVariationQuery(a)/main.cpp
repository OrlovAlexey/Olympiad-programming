#include <iostream>

using std::pair;
using std::max;
using std::min;
using std::cin;
using std::cout;

void treebuild(pair<long long, long long> t[], long long v, long long tl, long long tr) {
    if (tl == tr) {
        t[v].first = ((tl % 12345 + 1) * (tl % 12345 + 1)) % 12345 + ((tl % 23456 + 1) * (tl % 23456 + 1) * (tl % 23456 + 1)) % 23456;
        t[v].second = t[v].first;
    }
    else {
        long long tm = (tl + tr) / 2;
        treebuild(t, 2 * v, tl, tm);
        treebuild(t, 2 * v + 1, tm + 1, tr);
        t[v].first = max(t[2 * v].first, t[v * 2 + 1].first);
        t[v].second = min(t[2 * v].second, t[v * 2 + 1].second);
    }
}

void print(pair<long long, long long> t[], long long v, long long tl, long long tr) {
    if (tl == tr) {
        cout << t[v].first << '\t';
        cout << t[v].second << '\n';
    }
    else {
        long long tm = (tl + tr) / 2;
        print(t, 2 * v, tl, tm);
        print(t, 2 * v + 1, tm + 1, tr);
    }
}

pair<long long, long long> max_and_min(pair<long long, long long> t[], long long v, long long tl, long long tr, long long l, long long r) {
    if (l > r) {
        return {-100001,100001};
    }
    if (l == tl && r == tr) {
        return t[v];
    }
    long long tm = (tl + tr) / 2;
    pair<long long, long long> p1 = max_and_min(t, 2 * v, tl, tm, l, min(r, tm));
    pair<long long, long long> p2 = max_and_min(t, 2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    return { max(p1.first, p2.first), min(p1.second, p2.second) };
}

void assign(pair<long long, long long> t[], long long v, long long tl, long long tr, long long pos, long long new_value) {
    if (tl == tr) {
        t[v].first = new_value;
        t[v].second = new_value;
    }
    else {
        long long tm = (tl + tr) / 2;
        if (pos <= tm) {
            assign(t, 2 * v, tl, tm, pos, new_value);
        }
        else {
            assign(t, 2 * v + 1, tm + 1, tr, pos, new_value);
        }
        t[v].first = max(t[2 * v].first, t[2 * v + 1].first);
        t[v].second = min(t[2 * v].second, t[2 * v + 1].second);
    }
}

int main() {
    long long n = 100000;
    pair<long long, long long> t[4 * n]; // 0, ..., 400000
//    for (long long i = 0; i < 4 * n; ++i) {
//        t[i] = {0, 0};
//    }
    treebuild(t, 1, 0, n-1); //n-1 = 10
//    cout << t[2].first << '\t' << t[2].second <<'\n';
//    cout << t[3].first << '\t' << t[3].second <<'\n';
//    print(t, 1, 0, 10);

    // t[v] 1, ..., 100000
    long long k, x, y;
    cin >> k;
    for (long long i = 0; i < k; ++i) {
        cin >> x >> y;
        if (x > 0) {
            cout << max_and_min(t, 1, 0, n-1, x-1, y-1).first - max_and_min(t, 1, 0, n-1, x-1, y-1).second << '\n';
        }
        if (x < 0) {
            assign(t, 1, 0, n-1, -x-1, y);
        }
    }
    return 0;
}

