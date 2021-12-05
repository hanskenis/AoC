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

int dangerous_areas(vector<Line> lines, int width, int height) {
    int result{};
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            int hits{};
            for (size_t l = 0; l < lines.size(); l++) {
                if (lines[l].hit(x, y)) hits++;
            }
            if (hits > 1) result++;
        }
    }
    return result;
}

int part_1(vector<Line> input, int width, int height) {
    vector<Line> lines{input};

    lines.erase(remove_if(lines.begin(), lines.end(), [](Line line) { return !(line.isHorizontal() || line.isVertical()); }),
                lines.end());

    return dangerous_areas(lines, width, height);
}

int part_2(vector<Line> input, int width, int height) {
    return dangerous_areas(input, width, height);
}

int main() {
    Line l;
    vector<Line> lines;
    int max_x{}, max_y{};
    while (cin >> l) {
        lines.push_back(l);
        max_x = max(max(l.start.x, l.end.x), max_x);
        max_y = max(max(l.start.y, l.end.y), max_y);
    }
    cout << "Part 1: " << part_1(lines, max_x + 1, max_y + 1) << endl;
    cout << "Part 2: " << part_2(lines, max_x + 1, max_y + 1) << endl;

    return 0;
}