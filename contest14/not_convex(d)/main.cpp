#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

class Point {
public:
    ll x;
    ll y;

    Point() : x(0), y(0) {}
    Point(ll x, ll y) : x(x), y(y) {}
};

istream& operator>> (istream& in, Point& p) {
    cin >> p.x >> p.y;
    return in;
}

bool is_convex(const vector<Point>& vertices) {
    int i, j, k;
    int size = vertices.size();
    ll cross_product;
    int flag = 0;

    if (size < 3) {
        return false;
    }
    for (i = 0; i < size; ++i) {
        j = (i + 1) % size;
        k = (i + 2) % size;
        cross_product = (vertices[j].x - vertices[i].x) * (vertices[k].y - vertices[j].y);
        cross_product -= (vertices[j].y - vertices[i].y) * (vertices[k].x - vertices[j].x);
        if (cross_product < 0) {
            flag |= 1;
        }
        else if (cross_product > 0) {
            flag |= 2;
        }
        if (flag == 3) {
            return false;
        }
    }
    if (flag != 0) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (is_convex(a)) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
    return 0;
}
