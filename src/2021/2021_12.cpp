#include <bits/stdc++.h>

using namespace std;

unordered_map<string, vector<string>> g{};

std::vector<std::string> split(const std::string& s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void addEdge(string v1, string v2) {
    g[v1].push_back(v2);
    g[v2].push_back(v1);
}

bool isUpperCase(string s) {
    return isupper(s[0]);
}

bool isLowerCase(string s) {
    return islower(s[0]);
}

int nrPathsPart1(string v1, string v2, unordered_map<string, bool> forbidden) {
    if (v1 == v2) {
        return 1;
    } else {
        int paths{};
        if (isLowerCase(v1)) {
            forbidden[v1] = true;
        }
        for (auto&& v : g[v1]) {
            if (!forbidden[v]) {
                paths += nrPathsPart1(v, v2, forbidden);
            }
        }
        return paths;
    }
}

bool visitedSmallCaveTwiceBefore(unordered_map<string, int> visited) {
    for (auto&& v : visited) {
        if (isLowerCase(v.first) && v.second == 2) return true;
    }
    return false;
}

bool canVisit(string v, unordered_map<string, int> visited) {
    if (v == "start") return false;
    if (v == "end") return true;
    if (isUpperCase(v)) return true;
    bool visitedSmallTwice = visitedSmallCaveTwiceBefore(visited);
    if (!visitedSmallTwice) return true;

    return visited[v] < 1;
}

int nrPathsPart2(string v1, string v2, unordered_map<string, int> visited) {
    visited[v1]++;
    if (v1 == v2) {
        return 1;
    } else {
        int paths{};

        for (auto&& v : g[v1]) {
            bool allowed = canVisit(v, visited);
            if (allowed) {
                paths += nrPathsPart2(v, v2, visited);
            }
        }
        return paths;
    }
}

int part2() {
    unordered_map<string, int> visited{};
    cout << endl;
    return nrPathsPart2("start", "end", visited);
}

int part1() {
    unordered_map<string, bool> visited{};
    return nrPathsPart1("start", "end", visited);
}

int main() {
    string line;

    while (getline(cin, line)) {
        auto splitted = split(line, '-');
        addEdge(splitted[0], splitted[1]);
    }

    auto one = part1();
    auto two = part2();
    
    cout << "Part1: " << one << endl;
    cout << "Part2: " << two << endl;

    return 0;
}