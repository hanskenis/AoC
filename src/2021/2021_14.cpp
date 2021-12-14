#include <bits/stdc++.h>

using namespace std;

unordered_map<string, string> rules{};

unordered_map<string, ulong> step(unordered_map<string, ulong> polymer) {
    unordered_map<string, ulong> result{};
    for (auto &&pairCount : polymer) {
        auto pair = pairCount.first;

        if (rules.find(pair) != rules.end()) {
            string newPair1{}, newPair2{};
            newPair1 = pair.substr(0, 1) + rules[pair];
            newPair2 = rules[pair] + pair.substr(1, 1);
            result[newPair1] += pairCount.second;
            result[newPair2] += pairCount.second;
        } else {
            result[pair]++;
        }
    }
    return result;
}

ulong differenceBetweenMostCommonAndLeastCommon(unordered_map<string, ulong> result, char lastChar) {
    ulong mostCommon = 0;
    ulong leastCommon = LONG_MAX;
    unordered_map<char, ulong> count{};

    for (auto &&pairCount : result) {
        auto pair = pairCount.first;
        count[pair[0]] += pairCount.second;
    }

    count[lastChar]++;

    for (auto &&c : count) {
        mostCommon = max(mostCommon, c.second);
        leastCommon = min(leastCommon, c.second);
    }

    return mostCommon - leastCommon;
}

unordered_map<string, ulong> polymerToPairCount(string polymer) {
    unordered_map<string, ulong> result{};
    for (size_t i = 0; i < polymer.size() - 1; i++) {
        auto pair = polymer.substr(i, 2);
        result[pair]++;
    }
    return result;
}

ulong part2(string polymer) {
    auto result = polymerToPairCount(polymer);
    for (size_t i = 0; i < 40; i++) {
        result = step(result);
    }
    return differenceBetweenMostCommonAndLeastCommon(result, polymer[polymer.size() - 1]);
}

ulong part1(string polymer) {
    auto result = polymerToPairCount(polymer);
    for (size_t i = 0; i < 10; i++) {
        result = step(result);
    }
    return differenceBetweenMostCommonAndLeastCommon(result, polymer[polymer.size() - 1]);
}

int main() {
    string start{};
    string line;
    cin >> start;
    getline(cin, line);

    string pair, element;
    string arrow = " -> ";

    while (cin >> pair >> arrow >> element) {
        rules[pair] = element;
    }

    cout << "Part1: " << part1(start) << endl;
     cout << "Part2: " << part2(start) << endl;

    // cout << "Part1: " << one << endl;

    return 0;
}