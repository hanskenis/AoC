#include <bits/stdc++.h>

using namespace std;

typedef pair<long, long> Range;
typedef tuple<Range, Range, Range> Cuboid;
typedef pair<bool, Cuboid> RebootStep;

vector<Cuboid> splitX(const Cuboid& c, long x, bool down) {
    vector<Cuboid> result{};
    auto [x_range, y_range, z_range] = c;

    if (x >= x_range.first && x <= x_range.second) {
        Cuboid c1, c2;
        if (down) {
            c1 = Cuboid(Range(x_range.first, x - 1), y_range, z_range);
            c2 = Cuboid(Range(x, x_range.second), y_range, z_range);
        } else {
            c1 = Cuboid(Range(x_range.first, x), y_range, z_range);
            c2 = Cuboid(Range(x + 1, x_range.second), y_range, z_range);
        }
        result.push_back(c1);
        result.push_back(c2);
    } else {
        result.push_back(c);
    }

    return result;
}
vector<Cuboid> splitY(const Cuboid& c, long y, bool down) {
    vector<Cuboid> result{};
    auto [x_range, y_range, z_range] = c;

    if (y >= y_range.first && y <= y_range.second) {
        Cuboid c1, c2;
        if (down) {
            c1 = Cuboid(x_range, Range(y_range.first, y - 1), z_range);
            c2 = Cuboid(x_range, Range(y, y_range.second), z_range);
        } else {
            c1 = Cuboid(x_range, Range(y_range.first, y), z_range);
            c2 = Cuboid(x_range, Range(y + 1, y_range.second), z_range);
        }
        result.push_back(c1);
        result.push_back(c2);
    } else {
        result.push_back(c);
    }

    return result;
}

vector<Cuboid> splitZ(const Cuboid& c, long z, bool down) {
    vector<Cuboid> result{};
    auto [x_range, y_range, z_range] = c;

    if (z >= z_range.first && z <= z_range.second) {
        Cuboid c1, c2;
        if (down) {
            c1 = Cuboid(x_range, y_range, Range(z_range.first, z - 1));
            c2 = Cuboid(x_range, y_range, Range(z, z_range.second));
        } else {
            c1 = Cuboid(x_range, y_range, Range(z_range.first, z));
            c2 = Cuboid(x_range, y_range, Range(z + 1, z_range.second));
        }
        result.push_back(c1);
        result.push_back(c2);
    } else {
        result.push_back(c);
    }

    return result;
}

bool overlap(const Cuboid& c1, const Cuboid& c2) {
    auto [x_range1, y_range1, z_range1] = c1;
    auto [x_range2, y_range2, z_range2] = c2;

    auto x_overlap = x_range1.first <= x_range2.second && x_range1.second >= x_range2.first;
    auto y_overlap = y_range1.first <= y_range2.second && y_range1.second >= y_range2.first;
    auto z_overlap = z_range1.first <= z_range2.second && z_range1.second >= z_range2.first;

    return (x_overlap && y_overlap && z_overlap);
}

vector<Cuboid> split(const Cuboid& onC, const Cuboid& offC) {
    vector<Cuboid> result{};
    auto [x_range_off, y_range_off, z_range_off] = offC;
    auto [x_range_on, y_range_on, z_range_on] = onC;

    result = splitX(onC, x_range_off.first, true);
    vector<Cuboid> tmp{};
    for (auto&& c : result) {
        auto splitted =
            splitX(c, x_range_off.second, false);
        tmp.insert(tmp.end(), splitted.begin(), splitted.end());
    }
    result = tmp;

    tmp.clear();
    for (auto&& c : result) {
        auto splitted =
            splitY(c, y_range_off.first, true);
        tmp.insert(tmp.end(), splitted.begin(), splitted.end());
    }
    result = tmp;

    tmp.clear();
    for (auto&& c : result) {
        auto splitted =
            splitY(c, y_range_off.second, false);
        tmp.insert(tmp.end(), splitted.begin(), splitted.end());
    }
    result = tmp;

    tmp.clear();
    for (auto&& c : result) {
        auto splitted =
            splitZ(c, z_range_off.first, true);
        tmp.insert(tmp.end(), splitted.begin(), splitted.end());
    }
    result = tmp;

    tmp.clear();
    for (auto&& c : result) {
        auto splitted =
            splitZ(c, z_range_off.second, false);
        tmp.insert(tmp.end(), splitted.begin(), splitted.end());
    }
    result = tmp;

    return result;
}

vector<Cuboid> subtract(Cuboid offC, const vector<Cuboid>& onCuboids) {
    vector<Cuboid> result{};
    for (auto&& onC : onCuboids) {
        if (overlap(offC, onC)) {
            auto splitted = split(onC, offC);
            vector<Cuboid> newCuboids{};

            for (auto&& c : splitted) {
                if (!overlap(offC, c)) {
                    newCuboids.push_back(c);
                }
            }

            result.insert(result.end(), newCuboids.begin(), newCuboids.end());
        } else {
            result.push_back(onC);
        }
    }
    return result;
}

auto part2(const vector<RebootStep>& steps) {
    vector<Cuboid> onCuboids{};
    for (auto&& [c, cuboid] : steps) {
        if (c) {
            onCuboids = subtract(cuboid, onCuboids);
            onCuboids.push_back(cuboid);
        } else {
            onCuboids = subtract(cuboid, onCuboids);
        }
    }

    long count{};
    for (auto&& [x_range, y_range, z_range] : onCuboids) {
        auto size = (abs(x_range.second - x_range.first + 1)) * (abs(y_range.second - y_range.first + 1)) * (abs(z_range.second - z_range.first + 1));
        count += size;
    }

    return count;
}

long part1(const vector<RebootStep>& steps) {
    bool reactor[100][100][100]{};
    for (auto&& [c, cuboid] : steps) {
        auto [x_range, y_range, z_range] = cuboid;
        if (x_range.first < 50 && x_range.second > -50 && y_range.first < 50 && y_range.second > -50 && z_range.first < 50 && z_range.second > -50) {
            for (auto x = x_range.first; x <= x_range.second; x++) {
                for (auto y = y_range.first; y <= y_range.second; y++) {
                    for (auto z = z_range.first; z <= z_range.second; z++) {
                        reactor[x + 50][y + 50][z + 50] = c;
                    }
                }
            }
        }
    }
    long count{};

    for (size_t x = 0; x < 100; x++) {
        for (size_t y = 0; y < 100; y++) {
            for (size_t z = 0; z < 100; z++) {
                if (reactor[x][y][z]) count++;
            }
        }
    }

    return count;
}

int main() {
    int x1, x2, y1, y2, z1, z2;
    char tmp[4];
    vector<RebootStep> steps{};

    while (scanf("%3s x=%d..%d,y=%d..%d,z=%d..%d\n", tmp, &x1, &x2, &y1, &y2, &z1, &z2) != EOF) {
        string command = tmp;
        bool on = false;
        if (command == "on") {
            on = true;
        }
        steps.push_back(RebootStep(on, Cuboid(Range(x1, x2), Range(y1, y2), Range(z1, z2))));
    }

    cout << "Part1: " << part1(steps) << endl;
    cout << "Part2: " << part2(steps) << endl;

    return 0;
}