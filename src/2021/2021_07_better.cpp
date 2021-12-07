#include <bits/stdc++.h>

using namespace std;

int fuel_cost_1(int target, int x) {
    return abs(target - x);
}

int part_1(vector<int> c) {
    sort(c.begin(), c.end());
    int median = c[c.size() / 2];
    return accumulate(c.begin(), c.end(), 0, [&median](int acc, int x) { return acc + fuel_cost_1(median, x); });
}

int fuel_cost_2(int target, int x) {
    int distance = abs(target - x);
    return distance * (distance + 1) / 2;
}

int part_2(vector<int> c) {
    int average = reduce(c.begin(), c.end()) / c.size();
    int f1 = accumulate(c.begin(), c.end(), 0, [&average](int acc, int x) { return acc + fuel_cost_2(average, x); });
    int f2 = accumulate(c.begin(), c.end(), 0, [&average](int acc, int x) { return acc + fuel_cost_2(average + 1, x); });

    return min(f1, f2);
}

int main() {
    vector<int> crabs;
    int n;

    while (cin >> n) {
        crabs.push_back(n);
        if (cin.peek() == ',')
            cin.ignore();
    }

    cout << "Part1: " << part_1(crabs) << endl;
    cout << "Part2: " << part_2(crabs) << endl;

    return 0;
}