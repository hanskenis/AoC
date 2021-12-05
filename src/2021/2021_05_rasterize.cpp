#include <bits/stdc++.h>

#include "point_and_line.h"

using namespace std;

void draw(int* grid, Line line, int w) {
    int x = line.start.x;
    int y = line.start.y;
    grid[x * w + y]++;
    while (x != line.end.x || y != line.end.y) {
        if (x < line.end.x)
            x++;
        else if (x > line.end.x)
            x--;

        if (y < line.end.y)
            y++;
        else if (y > line.end.y)
            y--;
        grid[x * w + y]++;
    }
}

int dangerous_areas(vector<Line> lines, int width, int height) {
    int result{};
    int grid[width * height]{};
    for (size_t i = 0; i < lines.size(); i++) {
        draw(grid, lines[i], width);
    }

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            if (grid[i * width + j] > 1) result++;
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