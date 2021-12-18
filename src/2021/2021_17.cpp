#include <bits/stdc++.h>

using namespace std;

int minX, maxX, minY, maxY;

pair<bool, int> willHit(int dx, int dy) {
    int x{};
    int y{};
    int Max = y;
    while (x < maxX && y > maxY) {
        x += dx;
        y += dy;
        Max = max(y, Max);

        if (x >= minX && x <= maxX && y <= minY && y >= maxY) return make_pair(true, Max);

        if (dx < 0) dx++;
        if (dx > 0) dx--;
        dy--;
    }
    return make_pair(false, 0);
}

int part2() {
    int n{};
    for (size_t dx = 1; dx <= maxX; dx++) {
        for (int dy = -1000; dy < 1000; dy++) {
            auto [hits, max] = willHit(dx, dy);
            if (hits) n++;
        }
    }

    return n;
}

int part1() {
    int highestPoint{};

    for (size_t dx = 1; dx < maxX; dx++) {
        for (size_t dy = 1; dy < 1000; dy++) {
            auto [hits, max] = willHit(dx, dy);

            if (hits && max > highestPoint) {
                highestPoint = max;
            }
        }
    }

    return highestPoint;
}

int main() {
    scanf("target area: x=%d..%d, y=%d..%d", &minX, &maxX, &maxY, &minY);

    cout << "Part1: " << part1() << endl;
    cout << "Part2: " << part2() << endl;

    return 0;
}