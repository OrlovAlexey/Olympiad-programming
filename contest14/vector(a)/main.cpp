#include <iostream>
#include <math.h>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Vector {
    Point start;
    Point end;
    double length() const {
        return sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y));
    }
};

Vector operator+ (const Vector& a, const Vector& b) {
    Vector res;
    res.end.x = (a.end.x - a.start.x) + (b.end.x - b.start.x);
    res.end.y = (a.end.y - a.start.y) + (b.end.y - b.start.y);
    res.start.x = res.start.y = 0;
    return res;
}

double dot(const Vector& a, const Vector& b) {
    double x1 = a.end.x - a.start.x;
    double x2 = b.end.x - b.start.x;
    double y1 = a.end.y - a.start.y;
    double y2 = b.end.y - b.start.y;
    return (x1 * x2 + y1 * y2);
}

double cross(const Vector& a, const Vector& b) {
    double x1 = a.end.x - a.start.x;
    double x2 = b.end.x - b.start.x;
    double y1 = a.end.y - a.start.y;
    double y2 = b.end.y - b.start.y;
    return (x1 * y2 - y1 * x2);
}

int main() {
    cout.precision(10);

    Vector a, b;
    cin >> a.start.x >> a.start.y >> a.end.x >> a.end.y;
    cin >> b.start.x >> b.start.y >> b.end.x >> b.end.y;

    cout << a.length() << " ";
    cout << b.length() << endl;

    Vector sum = a + b;
    cout << sum.end.x << " " << sum.end.y << endl;

    cout << dot(a, b) << " " << cross(a,b) << endl;

    cout << abs(cross(a,b)) / 2 << endl;
    return 0;
}
