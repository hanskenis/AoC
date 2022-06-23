#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Location;
enum AmphipodType { NONE,
                    A,
                    B,
                    C,
                    D };

struct Amphipod {
    AmphipodType type;

    Amphipod(AmphipodType t) {
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
            case NONE:
                cout << '.';
                break;
        }
    }
};

struct Room {
    vector<Amphipod> amphipods{};

    void add(Amphipod a) {
        amphipods.push_back(a);
    }
};

struct Burrow {
    Amphipod hallway[11]{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

    Room rooms[4];

    Burrow(Room rooms[4]) {
        for (size_t i = 0; i < 4; i++) {
            this->rooms[i] = rooms[i];
        }
    }

    bool is_organized() const {
        return true;
    }

    bool operator==(const Burrow& other) const {
        return hallway == other.hallway && rooms == other.rooms;
    }

    void display() const {
        cout << "#############" << endl;
        cout << "#";
        for (size_t i = 0; i < 11; i++) {
            hallway[i].display();
        }
        cout << "#" << endl;
    }
};

// The specialized hash function for `unordered_map` keys
struct hash_fn {
    template <class T1, class T2>
    std::size_t operator()(const Burrow& burrow) const {
        std::size_t h = hash()(burrow.amphipods[0].location.first) ^ hash()(burrow.amphipods[0].location.second);

        for (size_t i = 1; i < burrow.amphipods.size(); i++) {
            h = h ^ hash()(burrow.amphipods[i].location.first);
            h = h ^ hash()(burrow.amphipods[i].location.second);
        }

        return h;
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

typedef pair<long, Burrow> QueueItem;

auto dijkstra(Burrow start, Burrow goal) {
    priority_queue<QueueItem, vector<QueueItem>, greater<QueueItem>> queue{};
    queue.push(QueueItem(0, start));

    unordered_map<Burrow, bool, hash_fn> visited{};

    while (!queue.empty()) {
        auto queue_item = queue.top();
        queue.pop();
        if (visited[queue_item.second]) continue;
        if (queue_item.second == goal) {
        };

        visited[queue_item.second] = true;

        // for (auto&& b : queue_item.generate_neighbours()) {
        // }
    }
}

auto part1(const Burrow& burrow) {
    cout << "Is organized: " << burrow.is_organized() << endl;
    return 0;
}

int main() {
    string line;
    vector<string> input{};
    while (getline(cin, line)) {
        input.push_back(line);
    }

    Room rooms[4];
    for (size_t i = 2; i < input.size(); i++) {
        rooms[0].add(to_type(input[i][3]));
        rooms[1].add(to_type(input[i][5]));
        rooms[2].add(to_type(input[i][7]));
        rooms[3].add(to_type(input[i][9]));
    }

    auto burrow = Burrow(rooms);
    burrow.display();

    cout << "Part1: " << part1(burrow) << endl;
    // cout << "Part2: " << part2(steps) << endl;

    return 0;
}