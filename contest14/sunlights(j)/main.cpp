#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
typedef long long ll;

#define M_PI 3.14159265359

bool cmp(double a, double b) {
    double eps = 1e-8;
    return abs(a - b) <= eps;
}

class Point {
public:
    double x;
    double y;

    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    bool operator== (const Point&) const;

};

istream& operator>> (istream& in, Point& p) {
    cin >> p.x >> p.y;
    return in;
}

class Line {
public:
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    Line() = default;
    Line(const Point& point1, const Point& point2) {
        a = point1.y - point2.y;
        b = point2.x - point1.x;
        c = (point1.x * point2.y) - (point2.x * point1.y);
    }
    Line(double a, double b, double c) : a(a), b(b), c(c) {}
    bool operator== (const Line&) const;
    bool is_belong(Point p) const {
        return cmp(a * p.x + b * p.y + c, 0);
    }
};


std::pair<Point, bool> intersect(const Line& line1, const Line& line2) {
    Point result;
    double a1, a2, b1, b2, c1, c2;
    a1 = line1.a;
    b1 = line1.b;
    c1 = line1.c;
    a2 = line2.a;
    b2 = line2.b;
    c2 = line2.c;
    double det = a1 * b2 - a2 * b1;
    if (!cmp(det, 0.0)) {
        result.x = cmp((b1 * c2 - b2 * c1) / det, 0.0) ? 0.0 : (b1 * c2 - b2 * c1) / det;
        result.y = cmp((a2 * c1 - a1 * c2) / det, 0.0) ? 0.0 : (a2 * c1 - a1 * c2) / det;
        return std::make_pair(result, true);
    }
    return std::make_pair(Point(), false);
}

struct Vector {
    Point start;
    Point end;
    Vector(const Point& end, const Point& start) : end(end), start(start) {}
    double length() const {
        return sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y));
    }
    void rotate(double angle) { // angle in radians
        double x1 = end.x - start.x;
        double y1 = end.y - start.y;
        double cs, sn, rx, ry;
        cs = cos(angle);
        sn = sin(angle);
        rx = x1 * cs - y1 * sn;
        ry = x1 * sn + y1 * cs;
        end.x = start.x + rx;
        end.y = start.y + ry;
    }
};

inline bool bit(ll mask, ll pos) {
    return (mask >> pos) & 1;
}

int main() {
    cout.precision(10);
    int n, l, r;
    cin >> n >> l >> r;
    vector<pair<Point, double>> sunlights(n);
    for (int i = 0; i < n; ++i) {
        cin >> sunlights[i].first >> sunlights[i].second;
    }

    vector<double> dp(1 << n, l);
    ll newmask;
    double d, a;
    for (ll mask = 0; mask < (1 << n); ++mask) {
        for (ll i = 0; i < n; ++i) {
            if (!bit(mask, i)) {
                newmask = mask + (1 << i);
                d = dp[mask];
                Vector temp(Point(d, 0), sunlights[i].first);
                if (cmp(sunlights[i].first.y,0) && sunlights[i].first.x > l && sunlights[i].first.x < r) {
                    dp[newmask] = std::max(std::max(sunlights[i].first.x, d), dp[newmask]);
                }
                a = sunlights[i].second * M_PI / 180.0;
                if (sunlights[i].first.y < 0) {
                    a *= -1;
                }
                temp.rotate(a);
                Line path(0, 1, 0);
                pair<Point, bool> intesected = intersect(path, Line(temp.start, temp.end));
                double new_d = intesected.first.x;
                if (!intesected.second || new_d < d || new_d >= r) {
                    goto good_end;
                }
                dp[newmask] = std::max(new_d, dp[newmask]);
            }
        }
    }
    cout << std::abs(dp[(1 << n) - 1] - l) << '\n';
    return 0;
    good_end:
    cout << std::abs(r - l) << '\n';
    return 0;
}
