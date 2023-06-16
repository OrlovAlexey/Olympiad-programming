#include <iostream>
#include <math.h>
using namespace std;

bool cmp(double a, double b) {
    double eps = 1e-6;
    return abs(a - b) <= eps;
}

class Point {
public:
    double x;
    double y;

    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
};

class Line {
public:
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    Line() = default;
    Line(double a, double b, double c) : a(a), b(b), c(c) {}
};

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

struct Vector {
    Point start;
    Point end;
    double length() const {
        return sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y));
    }
};

double cross(const Vector& a, const Vector& b) {
    double x1 = a.end.x - a.start.x;
    double x2 = b.end.x - b.start.x;
    double y1 = a.end.y - a.start.y;
    double y2 = b.end.y - b.start.y;
    return (x1 * y2 - y1 * x2);
}

Point point_on_line(const Line& line) {
    Point p;
    if (cmp(line.b, 0)) {
        p.x = - line.c / line.a;
        p.y = 0;
    } else {
        p.x = 1;
        p.y = -(line.c + line.a) / line.b;
    }
    return p;
}

double line_distance(const Line& line1, const Line& line2) {
    // works only if lines are parallel
    Vector h_of_line1;
    h_of_line1.end.x = line1.b;
    h_of_line1.end.y = -line1.a;
    h_of_line1.start.x = h_of_line1.start.y = 0;
    Point p_on_line2 = point_on_line(line2);
    Vector between_lines;
    between_lines.end = p_on_line2;
    between_lines.start = point_on_line(line1);
    double d_square = abs(cross(h_of_line1, between_lines));
    return (d_square / h_of_line1.length());
}

int main() {
    cout.precision(10);
    Line line1, line2;

    cin >> line1.a >> line1.b >> line1.c;
    cin >> line2.a >> line2.b >> line2.c;

    cout << -line1.b << " " << line1.a << endl;
    cout << -line2.b << " " << line2.a << endl;

    pair<Point, bool> intersected = intersect(line1, line2);
    if (intersected.second) {
        Point p = intersected.first;
        cout << p.x << " " << p.y << endl;
    }
    else {
        cout << line_distance(line1, line2) << endl;
    }
    return 0;
}
