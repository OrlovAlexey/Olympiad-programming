#include <iostream>
#include <math.h>
using namespace std;

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

bool Point::operator== (const Point& point) const {
    if (cmp(point.x, x) && cmp(point.y, y)) {
        return true;
    }
    return false;
}

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
    bool operator== (const Line&) const;
    bool is_belong(Point p) const {
        return cmp(a * p.x + b * p.y + c, 0);
    }
};


bool Line::operator== (const Line& line) const {
    double ratio_a, ratio_b, ratio_c;
    bool special_case_a = false, special_case_b = false, special_case_c = false;
    if (!cmp(line.a, 0.0)) {
        ratio_a = this->a / line.a;
    }
    else {
        if (!cmp(this->a, 0.0)) {
            return false;
        }
        special_case_a = true;
    }
    if (!cmp(line.b, 0.0)) {
        ratio_b = this->b / line.b;
    }
    else {
        if (!cmp(this->b, 0.0)) {
            return false;
        }
        special_case_b = true;
    }
    if (!cmp(line.c, 0.0)) {
        ratio_c = this->c / line.c;
    }
    else {
        if (!cmp(this->c, 0.0)) {
            return false;
        }
        special_case_c = true;
    }
    if (special_case_a) {
        ratio_a = ratio_b;
    }
    if (special_case_b) {
        ratio_b = ratio_a;
    }
    if (special_case_c) {
        ratio_c = ratio_a;
    }
    if (special_case_c && special_case_a) {
        ratio_c = ratio_b;
    }

    if (cmp(ratio_a, ratio_b) && cmp(ratio_b, ratio_c)) {
        return true;
    }
    return false;
}

//bool operator==(const Line& line1, const Line& line2) {
//    return (cmp(line1.a / line2.a, line1.b / line2.b) && cmp(line1.b / line2.b, line1.c / line2.c));
//}

std::pair<Point, bool> intersect(Line line1, Line line2) {
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

inline bool is_between_x(Point p, Point a1, Point a2) {
    return ((p.x <= a1.x && p.x >= a2.x) || (p.x >= a1.x && p.x <= a2.x));
}

inline bool is_between_y(Point p, Point a1, Point a2) {
    return ((p.y <= a1.y && p.y >= a2.y) || (p.y >= a1.y && p.y <= a2.y));
}

inline bool is_between(Point p, Point a1, Point a2) {
    return (is_between_x(p, a1, a2) && is_between_y(p, a1, a2));
}

inline bool is_intercepting(Point a1, Point a2, Point b1, Point b2) {
    return ((is_between(a1, b1, b2) || is_between(a2, b1, b2)) || (is_between(b1, a1, a2) || is_between(b2, a1, a2)));
}

int main() {
    cout.precision(10);
    Point a1, a2;
    Point b1, b2;
    cin >> a1 >> a2;
    cin >> b1 >> b2;
    if (a1 == a2) {
        if (b1 == b2) {
            if (b1 == a1) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
            return 0;
        }
        Line line_b(b1, b2);
        if (line_b.is_belong(a1) && is_between(a1, b1, b2)) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
        return 0;
    }
    if (b1 == b2) {
        Line line_a(a1, a2);
        if (line_a.is_belong(b1) && is_between(b1, a1, a2)) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
        return 0;
    }
    Line line1(a1, a2), line2(b1, b2);
    pair<Point, bool> intersected = intersect(line1, line2);
    if (intersected.second) {
        Point p = intersected.first;
        if (is_between(p, a1, a2) && is_between(p, b1, b2)) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    } else {
        if (line1 == line2) {
            if (is_intercepting(a1, a2, b1, b2)) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
