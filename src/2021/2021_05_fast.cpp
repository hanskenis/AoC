#include <bits/stdc++.h>

using namespace std;

int main() {
    u_char g1[1000 * 1000]{};
    u_char g2[1000 * 1000]{};

    int x1, x2, y1, y2;

    while (scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != EOF) {
        int x = x1;
        int y = y1;

        if (x1 == x2 || y1 == y2) {
            g1[x * 1000 + y]++;
        }

        g2[x * 1000 + y]++;

        while (x != x2 || y != y2) {
            x += x < x2 ? 1 : x > x2 ? -1
                                     : 0;
            y += y < y2 ? 1 : y > y2 ? -1
                                     : 0;

            if (x1 == x2 || y1 == y2) {
                g1[x * 1000 + y]++;
            }
            g2[x * 1000 + y]++;
        }
    }

    int answer1{};
    int answer2{};

    for (size_t i = 0; i < 1000 * 1000; i++) {
        if (g1[i] > 1) answer1++;
        if (g2[i] > 1) answer2++;
    }

    printf("Part 1: %d\n", answer1);
    printf("Part 2: %d\n", answer2);

    return 0;
}