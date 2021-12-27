#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Location;
enum AmphipodType { A,
                    B,
                    C,
                    D };

struct Amphipod {
    Location location;
    AmphipodType type;
    Amphipod(Location s, AmphipodType t) {
        location = s;
        type = t;
    }

    void display() const {
        switch (type) {
            case A:
                cout << 'A';
                break;
            case B:
                cout << 'B';
                break;
            case C:
                cout << 'C';
                break;
            case D:
                cout << 'D';
                break;
        }
    }
};

struct Burrow {
    vector<Amphipod> amphipods;
    vector<Location> walls;

    Burrow(vector<Amphipod> pods, vector<Location> walls) {
        this->amphipods = pods;
        this->walls = walls;
    }

    const Amphipod* pod_at(int x, int y) const {
        for (auto&& p : amphipods) {
            if (p.location.first == x && p.location.second == y) {
                return &p;
            }
        }
        return NULL;
    }
    bool is_organized() const {
        
    }

    void display() const {
        cout << endl;
        for (size_t y = 0; y < 5; y++) {
            for (size_t x = 0; x < 13; x++) {
                if (find(walls.begin(), walls.end(), Location(x, y)) != walls.end())
                    cout << "#";
                else {
                    auto p = pod_at(x, y);
                    if (p) {
                        p->display();
                    } else {
                        cout << '.';
                    }
                }
            }
            cout << endl;
        }
    }
};

AmphipodType to_type(const char c) {
    switch (c) {
        case 'A':
            return A;
        case 'B':
            return B;
        case 'C':
            return C;
        case 'D':
            return D;
        default:
            throw;
    }
}

auto part1(Burrow burrow) {
    return 0;
}

int main() {
    string line;
    vector<string> input{};
    for (size_t i = 0; i < 5; i++) {
        getline(cin, line);
        input.push_back(line);
    }

    vector<Location> walls{};
    vector<Amphipod> pods{};

    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = 0; j < input[i].size(); j++) {
            if (input[i][j] == '#')
                walls.push_back(Location(j, i));
            else if (input[i][j] == '.')
                continue;
            else if (input[i][j] == ' ')
                continue;
            else {
                pods.push_back(Amphipod(Location(j, i), to_type(input[i][j])));
            }
        }
    }

    auto burrow = Burrow(pods, walls);
    burrow.display();

    cout << "Part1: " << part1(burrow) << endl;
    // cout << "Part2: " << part2(steps) << endl;

    return 0;
}