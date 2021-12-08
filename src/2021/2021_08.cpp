#include <bits/stdc++.h>

using namespace std;

std::vector<std::string> split(const std::string& s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void sort_string(string& s) {
    sort(s.begin(), s.end());
}

void sort_strings(vector<string>& s) {
    for (size_t i = 0; i < s.size(); i++) {
        sort_string(s[i]);
    }
}

bool has_length(string s, int l) {
    return s.size() == l;
}

bool contains(string s1, string s2) {
    for (size_t i = 0; i < s2.size(); i++) {
        char c = s2[i];

        if (s1.find(c) == std::string::npos) {
            return false;
        }
    }
    return true;
}

bool is_five(string s1, string one, string four) {
    four.erase(remove_if(four.begin(), four.end(), [one](char c) { return one.find(c) != string::npos; }), four.end());

    return contains(s1, four);  //
}

unordered_map<string, int> handle_inputs(vector<string> i) {
    unordered_map<string, int> m{};
    auto one = find_if(begin(i), end(i), [](string s) { return has_length(s, 2); })[0];
    i.erase(remove(i.begin(), i.end(), one), i.end());
    auto four = find_if(begin(i), end(i), [](string s) { return has_length(s, 4); })[0];
    i.erase(remove(i.begin(), i.end(), four), i.end());
    auto seven = find_if(begin(i), end(i), [](string s) { return has_length(s, 3); })[0];
    i.erase(remove(i.begin(), i.end(), seven), i.end());
    auto eight = find_if(begin(i), end(i), [](string s) { return has_length(s, 7); })[0];
    i.erase(remove(i.begin(), i.end(), eight), i.end());
    auto three = find_if(begin(i), end(i), [one](string s) { return has_length(s, 5) && contains(s, one); })[0];
    i.erase(remove(i.begin(), i.end(), three), i.end());
    auto five = find_if(begin(i), end(i), [one, four](string s) { return has_length(s, 5) && is_five(s, one, four); })[0];
    i.erase(remove(i.begin(), i.end(), five), i.end());
    auto two = find_if(begin(i), end(i), [](string s) { return has_length(s, 5); })[0];
    i.erase(remove(i.begin(), i.end(), two), i.end());
    auto zero = find_if(begin(i), end(i), [five](string s) { return has_length(s, 6) && !contains(s, five); })[0];
    i.erase(remove(i.begin(), i.end(), zero), i.end());
    auto nine = find_if(begin(i), end(i), [one](string s) { return has_length(s, 6) && contains(s, one); })[0];
    i.erase(remove(i.begin(), i.end(), nine), i.end());
    auto six = find_if(begin(i), end(i), [](string s) { return has_length(s, 6); })[0];
    i.erase(remove(i.begin(), i.end(), six), i.end());

    m[zero] = 0;
    m[one] = 1;
    m[two] = 2;
    m[three] = 3;
    m[four] = 4;
    m[five] = 5;
    m[six] = 6;
    m[seven] = 7;
    m[eight] = 8;
    m[nine] = 9;
    return m;
}

int part_2_value(vector<string> i, vector<string> o) {
    sort_strings(i);
    sort_strings(o);

    auto m = handle_inputs(i);

    int value = {};

    for (size_t i = 0; i < o.size(); i++) {
        value = value * 10 + m[o[i]];
    }

    return value;
}

int part_2(vector<string> data) {
    vector<string> io, inputs, outputs;
    int total{};
    for (size_t i = 0; i < data.size(); i++) {
        io = split(data[i], '|');
        inputs = split(io[0], ' ');
        outputs = split(io[1], ' ');
        total += part_2_value(inputs, outputs);
    }

    return total;
}

int part_1(vector<string> data) {
    vector<string> io, inputs, outputs;
    int answer1 = {};
    for (size_t i = 0; i < data.size(); i++) {
        io = split(data[i], '|');
        inputs = split(io[0], ' ');
        outputs = split(io[1], ' ');
        for (int i = 0; i < outputs.size(); i++) {
            int length = outputs[i].size();
            if (length == 2 || length == 3 || length == 4 || length == 7) {
                answer1++;
            }
        }
    }
    return answer1;
}

int main() {
    string line;
    vector<string> data{};

    while (getline(cin, line)) {
        data.push_back(line);
    }

    // cout << "Part1: " << part_1(data) << endl;
    cout << "Part2: " << part_2(data) << endl;

    return 0;
}