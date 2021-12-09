#include <bits/stdc++.h>

using namespace std;

int w{}, h{};

struct Point {
    int x{};
    int y{};

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int get_value(const vector<int>& m, int x, int y) {
    if (x < 0) return INT_MAX;
    if (x >= w) return INT_MAX;
    if (y < 0) return INT_MAX;
    if (y >= h) return INT_MAX;

    return m[y * w + x];
}

vector<Point> low_points(const vector<int>& m) {
    vector<Point> points{};

    for (size_t x = 0; x < w; x++) {
        for (size_t y = 0; y < h; y++) {
            int height = get_value(m, x, y);
            int Min = min(INT_MAX, get_value(m, x - 1, y));
            Min = min(Min, get_value(m, x + 1, y));
            Min = min(Min, get_value(m, x, y - 1));
            Min = min(Min, get_value(m, x, y + 1));

            if (height < Min) {
                points.push_back(Point(x, y));
            }
        }
    }
    return points;
}
int basin_size(vector<int>& m, const Point& p) {
    int value = get_value(m, p.x, p.y);
    if (value != 9 && value != INT_MAX) {
        m[p.y * w + p.x] = 9;
        int size = 1;
        size += basin_size(m, Point(p.x - 1, p.y));
        size += basin_size(m, Point(p.x + 1, p.y));
        size += basin_size(m, Point(p.x, p.y - 1));
        size += basin_size(m, Point(p.x, p.y + 1));
        return size;
    } else {
        return 0;
    }
}

int part_2(vector<int>& initial_map) {
    auto points = low_points(initial_map);
    vector<int> basin_sizes{};
    vector<int> copy = initial_map;
    for (size_t i = 0; i < points.size(); i++) {
        basin_sizes.push_back(basin_size(copy, points[i]));
    }

    sort(basin_sizes.begin(), basin_sizes.end());
    int n = basin_sizes.size();

    return basin_sizes[n - 1] * basin_sizes[n - 2] * basin_sizes[n - 3];
}

int part_1(vector<int>& m) {
    int total{};
    auto points = low_points(m);

    return accumulate(points.begin(), points.end(), 0, [&m](int acc, Point p) { return acc + get_value(m, p.x, p.y) + 1; });
}

int main() {
    string line;
    vector<int> m;

    while (getline(cin, line)) {
        w = line.size();
        for (size_t i = 0; i < w; i++) {
            int n = line[i] - '0';
            m.push_back(n);
        }
    }

    h = m.size() / w;

    cout << "Part1: " << part_1(m) << endl;
    cout << "Part2: " << part_2(m) << endl;

    return 0;
}