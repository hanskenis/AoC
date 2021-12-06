#include <bits/stdc++.h>

using namespace std;

unsigned long long part_1(unsigned long long fish[9], int days) {
    while (days > 0) {
        days--;
        ulong fish_to_add = fish[0];
        for (size_t i = 0; i < 8; i++) {
            fish[i] = fish[i + 1];
        }
        fish[8] = fish_to_add;
        fish[6] += fish_to_add;
    }

    return fish[0] + fish[1] + fish[2] + fish[3] + fish[4] + fish[5] + fish[6] + fish[7] + fish[8];
}

int main() {
    unsigned long long fish[9]{};
    int n;

    while (cin >> n) {
        fish[n]++;
        if (cin.peek() == ',')
            cin.ignore();
    }

    // cout << "Part1: " << part_1(fish, 80) << endl;
    cout << "Part2: " << part_1(fish, 256) << endl;

    return 0;
}