#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> energy{};

struct Point {
    int x{};
    int y{};

    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }
};

void bump_enery(vector<vector<int>>& energy, int x, int y) {
    energy[x][y] = (energy[x][y] + 1) % 10;
}

vector<Point> bump_adjacent(vector<vector<int>>& energy, int x, int y) {
    vector<Point> flashed{};
    int h = energy.size();
    int w = energy[0].size();
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int i = x + dx;
            int j = y + dy;
            if (i >= 0 && i < w && j >= 0 && j < h && energy[i][j]) {
                bump_enery(energy, i, j);
                if (energy[i][j] == 0) {
                    flashed.push_back(Point(i, j));
                }
            }
        }
    }

    return flashed;
}

int step(vector<vector<int>>& energy) {
    queue<Point> flashes_to_handle{};

    for (size_t y = 0; y < energy.size(); y++) {
        for (size_t x = 0; x < energy[y].size(); x++) {
            bump_enery(energy, x, y);
            if (energy[x][y] == 0) {
                flashes_to_handle.push(Point(x, y));
            }
        }
    }
    vector<Point> handled{};
    while (!flashes_to_handle.empty()) {
        int size = flashes_to_handle.size();
        Point next = flashes_to_handle.front();
        flashes_to_handle.pop();
        // only if not handled before
        if (find(handled.begin(), handled.end(), next) == handled.end()) {
            auto flashed_neighbours = bump_adjacent(energy, next.x, next.y);
            for (size_t i = 0; i < flashed_neighbours.size(); i++) {
                // add to to_handle if not handled before
                if (find(handled.begin(), handled.end(), flashed_neighbours[i]) == handled.end()) {
                    flashes_to_handle.push(flashed_neighbours[i]);
                }
            }
        }
        handled.push_back(next);
    }

    return handled.size();
}

void display(vector<vector<int>>& energy, int step, int total) {
    // cout << endl;
    // cout << "Step: " << step << "Total: " << total << endl;
    // for (size_t x = 0; x < energy[0].size(); x++) {
    //     for (size_t y = 0; y < energy.size(); y++) {
    //         cout << energy[x][y] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
}

int part_1(vector<vector<int>> energy) {
    int total{};
    for (size_t i = 0; i < 100; i++) {
        total += step(energy);
        display(energy, i, total);
    }

    return total;
}

bool all_flashed(vector<vector<int>>& energy) {
    for (size_t x = 0; x < energy[0].size(); x++) {
        for (size_t y = 0; y < energy.size(); y++) {
            if (energy[x][y] != 0) return false;
        }
    }
    return true;
}

int part_2(vector<vector<int>> energy) {
    int steps{};
    while (!all_flashed(energy)) {
        step(energy);
        steps++;
    }
    return steps;
}

int main() {
    string line;
    vector<vector<int>> energy{};
    int y{};

    while (getline(cin, line)) {
        energy.push_back(vector<int>());
        for (size_t i = 0; i < line.size(); i++) {
            int n = line[i] - '0';
            energy[y].push_back(n);
        }
        y++;
    }

    cout << "w:" << energy[1].size() << endl;
    cout << "h:" << energy.size() << endl;

    display(energy, 0, 0);

    cout << "Part1: " << part_1(energy) << endl;
    cout << "Part2: " << part_2(energy) << endl;

    return 0;
}