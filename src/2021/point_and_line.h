#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    friend istream& operator>>(istream& is, Point& p);
    friend ostream& operator<<(ostream& os, const Point p);
};

ostream& operator<<(ostream& os, const Point p) {
    os << p.x << "," << p.y;
    return os;
}

istream& operator>>(istream& is, Point& p) {
    char comma = ',';
    is >> p.x >> comma >> p.y;
    return is;
}

struct Line {
    Point start, end;
    friend istream& operator>>(istream& is, Line& p);
    friend ostream& operator<<(ostream& os, const Line p);

    bool isHorizontal() {
        return start.y == end.y;
    }

    bool isVertical() {
        return start.x == end.x;
    }

    int length() {
        return sqrt((start.x - end.x) ^ 2 + (start.y - end.y) ^ 2);
    }

    bool hit(int x, int y) {
        double sp = sqrt((start.x - x) * (start.x - x) + (start.y - y) * (start.y - y));
        double ep = sqrt((end.x - x) * (end.x - x) + (end.y - y) * (end.y - y));
        double se = sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y));

        return se - 0.0001 <= sp + ep && sp + ep <= se + 0.0001;
    }
};

ostream& operator<<(ostream& os, const Line l) {
    os << l.start << " -> " << l.end;
    return os;
}

istream& operator>>(istream& is, Line& l) {
    string arrow = " -> ";
    is >> l.start >> arrow >> l.end;
    return is;
}