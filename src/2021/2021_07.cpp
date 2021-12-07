#include <bits/stdc++.h>

using namespace std;

int part_1(vector<int> c) {
    sort(c.begin(), c.end());
    int median = c[c.size() / 2];
    int total{};
    for (size_t i = 0; i < c.size(); i++) {
        total += abs(median - c[i]);
    }
    return total;
}

ulong fuel_cost(int distance) {
    return (distance * (distance + 1)) / 2;
}

int part_2(vector<int> c) {
    sort(c.begin(), c.end());
    int count = c.size();
    ulong min_fuel = ULONG_MAX;
    ulong total_fuel{};

    for (int i = 0; i < c[count - 1]; i++) {
        total_fuel = 0;
        for (int j = 0; j < count; j++) {
            total_fuel += fuel_cost(abs(c[j] - i));
        }
        min_fuel = min(total_fuel, min_fuel);
    }

    return min_fuel;
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