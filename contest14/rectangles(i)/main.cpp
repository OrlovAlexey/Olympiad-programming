#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

class Point {
public:
    ll x;
    ll y;

    Point() : x(0), y(0) {}
    Point(ll x, ll y) : x(x), y(y) {}
    bool operator== (const Point&) const;
    Point& operator-= (const Point& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

istream& operator>> (istream& in, Point& p) {
    cin >> p.x >> p.y;
    return in;
}

Point operator- (const Point& p1, const Point& p2) {
    Point p3 = p1;
    p3 -= p2;
    return p3;
}

struct Vector {
    Point start;
    Point end;
    Vector(const Point& end, const Point& start) : end(end), start(start) {}
};

ll cross(const Vector& a, const Vector& b) {
    ll x1 = a.end.x - a.start.x;
    ll x2 = b.end.x - b.start.x;
    ll y1 = a.end.y - a.start.y;
    ll y2 = b.end.y - b.start.y;
    return (x1 * y2 - y1 * x2);
}

bool cross_special(const Point& a, const Point& b) { // A -> new_p, B -> A
    ll x1 = a.x;
    ll x2 = b.x;
    ll y1 = a.y;
    ll y2 = b.y;
    bool sign;
    double cross;
    if (y2 != 0) {
        cross = double(x1) / double(x2) - double(y1) / double(y2);
        sign = (cross <= 0 && y2 > 0) || (cross >= 0 && y2 < 0);
    }
    else {
        sign = (y1 >= 0 && x2 >= 0) || (x1 <= 0 && y2 <= 0);
    }
    return sign;
}

ll dot(const Point& a, const Point& b) {
    return (a.x * b.x + a.y * b.y);
}

bool x_cmp(const pair<Point, ll>& p1, const pair<Point, ll>& p2) {
    return (p1.first.x < p2.first.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n;
    cin >> n;
    vector<pair<Point, ll>> rectangles(n);
    for (int i = 0; i < n; ++i) {
        cin >> rectangles[i].first >> rectangles[i].second;
    }
    std::sort(rectangles.begin(), rectangles.end(), x_cmp);
    vector<ll> dp(n, 0);
    dp[0] = rectangles[0].first.x * rectangles[0].first.y - rectangles[0].second;
    ll ans = dp[0];
    vector<Point> upper_convex;
    upper_convex.emplace_back(0, 0);
    upper_convex.emplace_back(rectangles[0].first.x, dp[0]);
    int cnvx_sz;
    for (int i = 1; i < n; ++i) {
        // binsearching maximum scalar on upperconvex
        Point temp(-rectangles[i].first.y, 1);
        int l = 0;
        int r = (int)upper_convex.size() - 1;
        while (l - r + 1 < 0) {
            int m = (l + r) / 2;
            if (dot(upper_convex[m], temp) < dot(upper_convex[m + 1], temp)){
                l = m;
            }
            else {
                r = m;
            }
        }
        dp[i] = max(dp[i], max(dot(upper_convex[l], temp), dot(upper_convex[r], temp)));
//        for (auto p : upper_convex) {
//            dp[i] = max(dp[i], dot(p, Point(-rectangles[i].first.y, 1)));
//        } // это был линейный проход
        dp[i] += (rectangles[i].first.x * rectangles[i].first.y - rectangles[i].second);

        // adding new_point to upper_convex
        Point new_p = Point(rectangles[i].first.x, dp[i]);
        while (upper_convex.size() >= 2) {
            cnvx_sz = upper_convex.size();
            Point A = upper_convex[cnvx_sz - 1];
            Point B = upper_convex[cnvx_sz - 2];
            if (cross_special(new_p - A, A - B)) {
//            if (cross(Vector(B, A), Vector(A, new_p)) >= 0) {
                upper_convex.pop_back();
            } else {
                break;
            }
        }
        upper_convex.push_back(new_p);
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }
    cout << ans;
    return 0;
}
