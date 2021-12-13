#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x{};
    int y{};
    Point() : x(0), y(0){};
    Point(const int& x, const int& y) : x(x), y(y){};
    Point(const Point& other) {
        x = other.x;
        y = other.y;
    };

    Point& operator=(const Point& other) {
        x = other.x;
        y = other.y;
        return *this;
    };

    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }

    bool operator<(const Point& other) {
        if (x < other.x)
            return true;
        else if (x == other.x && y == other.y)
            return true;

        return false;
    };

    size_t operator()(const Point& pointToHash) const noexcept {
        size_t hash = pointToHash.x + 10 * pointToHash.y;
        return hash;
    };
};
namespace std {
template <>
struct hash<Point> {
    std::size_t operator()(const Point& p) const noexcept {
        return p(p);
    }
};
}  // namespace std

struct FoldInstruction {
    char axis{};
    int nr{};
};

std::vector<std::string> split(const std::string& s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

unordered_set<Point> fold(unordered_set<Point> points, FoldInstruction instruction) {
    int maxX, maxY;
    maxX = 0;
    maxY = 0;
    unordered_set<Point> result{};
    for (auto&& p : points) {
        maxX = max(maxX, p.x);
        maxY = max(maxY, p.y);
    }
    for (auto&& p : points) {
        if (instruction.axis == 'y' && p.y > instruction.nr) {
            result.insert(Point(p.x, 2 * instruction.nr - p.y));
        } else if (instruction.axis == 'x' && p.x > instruction.nr) {
            result.insert(Point(instruction.nr * 2 - p.x, p.y));
        } else {
            result.insert(p);
        }
    }
    return result;
}

void display(unordered_set<Point> points, int maxX, int maxY) {
    bool grid[maxX][maxY]{};
    for (auto&& p : points) {
        grid[p.x][p.y] = true;
    }

    for (size_t y = 0; y < maxY; y++) {
        for (size_t x = 0; x < maxX; x++) {
            char c = grid[x][y] ? '#' : '.';
            cout << c;
        }
        cout << endl;
    }
}

void part2(unordered_set<Point> input, vector<FoldInstruction> instructions) {
    unordered_set<Point> result = input;
    int x, y;
    for (auto&& i : instructions) {
        result = fold(result, i);
        if (i.axis == 'x') x = i.nr;
        if (i.axis == 'y') y = i.nr;
    }
    display(result, x, y);
}

int part1(unordered_set<Point> points, FoldInstruction instruction) {
    auto result = fold(points, instruction);
    return result.size();
}

int main() {
    string line;
    bool reading_dots = true;
    int x, y;
    vector<Point> points{};
    vector<FoldInstruction> instructions{};

    while (getline(cin, line)) {
        if (reading_dots) {
            if (line.empty()) {
                reading_dots = false;
            } else {
                sscanf(line.c_str(), "%d,%d", &x, &y);
                points.push_back(Point(x, y));
            }
        } else {
            char axis;
            int nr;
            sscanf(line.c_str(), "fold along %c=%d", &axis, &nr);
            instructions.push_back(FoldInstruction(axis, nr));
        }
    }

    unordered_set<Point> set(points.begin(), points.end());

    auto one = part1(set, instructions[0]);

    cout << "Part1: " << one << endl;
    part2(set, instructions);

    return 0;
}