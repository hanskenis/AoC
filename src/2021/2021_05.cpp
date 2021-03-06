#include <bits/stdc++.h>

#include "point_and_line.h"

using namespace std;

int dangerous_areas(vector<Line> lines, int width, int height) {
    int result{};
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            int hits{};
            for (size_t l = 0; l < lines.size(); l++) {
                if (lines[l].hit(x, y)) hits++;
                if (hits > 1) {
                    result++;
                    break;
                }
            }
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