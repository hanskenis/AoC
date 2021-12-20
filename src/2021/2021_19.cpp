#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x{};
    int y{};
    int z{};
};

struct Scanner {
    vector<Point> beacons{};
};

Point operator-(const Point& p1, const Point& p2) {
    return Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

bool overlap(Scanner s1, Scanner s2) {
    for (size_t i = 0; i < s1.beacons.size(); i++) {
        auto b1 = s1.beacons[i];
        for (size_t j = 0; j < s2.beacons.size(); j++) {
            auto b2 = s2.beacons[j];
            auto diff = b2 - b1;
        }
    }

    return false;
}

auto part1(vector<Scanner>& scanners) {
    bool overlap = false;
    auto scanner1 = scanners[0];
    auto scanner2 = scanners[1];
    while (!overlap) {
    }
}

int main() {
    string line;
    vector<Scanner> scanners;
    int index{};

    while (getline(cin, line)) {
        if (!line.empty()) {
            if (line[1] == '-') {
                scanners.push_back(Scanner());
            } else {
                int x, y, z;

                sscanf(line.c_str(), "%d,%d,%d", &x, &y, &z);
                scanners[index].beacons.push_back(Point(x, y, z));
            }
        } else {
            index++;
        }
    }

    cout << "Part1: " << part1(scanners) << endl;
    // cout << "Part2: " << part2(numbers2) << endl;

    return 0;
}