#include <bits/stdc++.h>

using namespace std;

map<char, int> m1 = {
    {'(', 3},
    {')', 3},
    {']', 57},
    {'[', 57},
    {'}', 1197},
    {'{', 1197},
    {'<', 25137},
    {'>', 25137},
};

map<char, int> m2 = {
    {'(', 1},
    {')', 1},
    {']', 2},
    {'[', 2},
    {'}', 3},
    {'{', 3},
    {'<', 4},
    {'>', 4},
};

long long completion_score(const string& line) {
    stack<int> s{};
    for (size_t i = 0; i < line.size(); i++) {
        switch (line[i]) {
            case '(':
            case '[':
            case '{':
            case '<':
                s.push(m2[line[i]]);
                break;
            case ')':
            case ']':
            case '}':
            case '>':
                if (s.empty()) {
                    return -1;
                }

                if (s.top() == m2[line[i]]) {
                    s.pop();
                } else {
                    return -1;
                }
        }
    }
    if (s.empty()) return -1;

    long long score = 0;
    while (!s.empty()) {
        int top = s.top();
        long long prev = score;
        score = score * 5 + top;
        if (prev > score) {
            return LONG_LONG_MAX;
        }

        s.pop();
    }

    return score;
}

long long part_2(const vector<string>& input) {
    vector<long long> scores{};

    for (size_t i = 0; i < input.size(); i++) {
        auto score = completion_score(input[i]);
        if (score != -1) {
            scores.push_back(score);
        }
    }

    sort(scores.begin(), scores.end());

    return scores[scores.size() / 2];
}

int part_1_error(string& line) {
    int e{};
    stack<int> s{};
    for (size_t i = 0; i < line.size(); i++) {
        switch (line[i]) {
            case '(':
            case '[':
            case '{':
            case '<':
                s.push(m1[line[i]]);
                break;
            case ')':
            case ']':
            case '}':
            case '>':
                if (s.top() == m1[line[i]]) {
                    s.pop();
                } else {
                    return m1[line[i]];
                }
        }
    }

    return e;
}

int main() {
    string line;
    vector<string> input;

    while (getline(cin, line)) {
        input.push_back(line);
    }

    int part1 = accumulate(input.begin(), input.end(), 0, [](int acc, string& line) { return acc + part_1_error(line); });

    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part_2(input) << endl;

    return 0;
}