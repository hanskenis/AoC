#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Point;

struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return p.first + 100000 * p.second;
    }
};

struct Node {
    Point point;
    int cost;

    Node(Point p, int c) {
        point = p;
        cost = c;
    }

    friend bool operator<(const Node& l, const Node& r) {
        return l.cost < r.cost;
    }
    friend bool operator>(const Node& l, const Node r) { return r < l; }
};

vector<Point> generate_neighbours(const Point& p, int size) {
    vector<Point> result{};
    auto [i, j] = p;
    if (i > 0) result.push_back(make_pair(i - 1, j));
    if (i < size - 1) result.push_back(make_pair(i + 1, j));
    if (j > 0) result.push_back(make_pair(i, j - 1));
    if (j < size - 1) result.push_back(make_pair(i, j + 1));

    return result;
}

int lowest_risk(vector<vector<int>> m) {
    int size = m.size();
    auto start = Node(Point(0, 0), 0);
    auto end = Point(size - 1, size - 1);
    priority_queue<Node, vector<Node>, greater<Node>> queue{};
    unordered_map<pair<int, int>, bool, pair_hash> visited{};

    queue.push(start);
    while (!queue.empty()) {
        auto node = queue.top();
        queue.pop();
        if (visited[node.point]) continue;
        if (node.point == end) return node.cost;

        visited[node.point] = true;

        for (auto&& p : generate_neighbours(node.point, size)) {
            auto [i, j] = p;
            auto cost = node.cost + m[i][j];
            auto child = Node(p, cost);
            queue.push(child);
        }
    }

    return 0;
}

int part2(vector<vector<int>> m) {
    int size = m.size();
    vector<vector<int>> big_map{};

    for (size_t i = 0; i < size * 5; i++) {
        big_map.push_back(vector<int>());
        for (size_t j = 0; j < size * 5; j++) {
            int inc = i / size + j / size;
            int nr = m[i % size][j % size];
            nr = ((nr + inc - 1) % 9) + 1;

            big_map[i].push_back(nr);
        }
    }

    return lowest_risk(big_map);
}

int part1(vector<vector<int>> m) {
    return lowest_risk(m);
}

int main() {
    string line;
    int y{};
    vector<vector<int>> m{};

    while (getline(cin, line)) {
        m.push_back(vector<int>());
        for (size_t i = 0; i < line.size(); i++) {
            int n = line[i] - '0';
            m[y].push_back(n);
        }
        y++;
    }

    // cout << "Part1: " << part1(m) << endl;
    cout << "Part2: " << part2(m) << endl;

    return 0;
}