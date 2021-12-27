#include <bits/stdc++.h>

using namespace std;

typedef pair<long, long> Wins;

struct DeterministicDie {
    vector<int> rolls{};

    int roll() {
        int rolled = rolls.size();
        int substract{};
        if (rolled > 0) {
            substract = rolls[rolled - 1];
        }
        int count = (rolled + 1) * 3;
        int total = count * (count + 1) / 2;
        rolls.push_back(total);

        total = total - substract;

        return total;
    }

    int times_rolled() {
        return rolls.size() * 3;
    }
};
struct Board {
    int players[2]{};
    int scores[2]{};

    Board(int start_p1, int start_p2) {
        players[0] = start_p1;
        players[1] = start_p2;
    }

    void move(int p_index, int places) {
        while (places > 0) {
            players[p_index]++;
            players[p_index] = (players[p_index] - 1) % 10 + 1;
            places--;
        }
        scores[p_index] += players[p_index];
    }

    bool game_over() {
        return scores[0] >= 1000 || scores[1] >= 1000;
    }
};


int move(int place, int moves) {
    place += moves;
    if (place <= 0) {
        place = 10 + place;
    } else {
        place = ((place - 1) % 10) + 1;
    }

    return place;
}

long score(int turn, int place) {
    if (turn == 0) return 0L;
    return move(place, 1) + score(turn, move(place, -1));
}

auto part2(int start1, int start2) {
    long result{};

    for (int i = 0; i < 10; i++) {
        cout << i << ": score: " << score(i, 4) << endl;
    }

    return result;
}

auto part1(int start1, int start2) {
    cout << endl;
    DeterministicDie die{};
    Board board(start1, start2);
    int players_turn{};
    while (!board.game_over()) {
        auto roll = die.roll();
        board.move(players_turn, roll);
        players_turn = (players_turn + 1) % 2;
    }

    cout << "player1 score:  " << board.scores[0] << endl;
    cout << "player2 score: " << board.scores[1] << endl;
    cout << "rolled: " << die.times_rolled() << endl;

    int lowest = min(board.scores[0], board.scores[1]);
    return die.times_rolled() * lowest;
}

int main() {
    int s1, s2;
    int p;
    string text;
    char procent;
    scanf("Player 1 starting position: %d\nPlayer 2 starting position: %d", &s1, &s2);

    cout << endl;
    cout << "s1: " << s1 << ", s2: " << s2 << endl;

   
    // cout << "Part1: " << part1(s1, s2) << endl;
    cout << "Part2: " << part2(s1, s2) << endl;

    return 0;
}