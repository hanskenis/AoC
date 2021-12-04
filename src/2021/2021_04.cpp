#include <bits/stdc++.h>

using namespace std;

struct Card {
    int numbers[5][5]{};
    bool marked[5][5]{};
    int total{};
    int marked_total{};
    int last_number{};

    Card(int data[5][5]) {
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                numbers[i][j] = data[i][j];
                total += numbers[i][j];
            }
        }
    }

    void mark(int number) {
        if (!bingo()) {
            for (size_t i = 0; i < 5; i++) {
                for (size_t j = 0; j < 5; j++) {
                    if (numbers[i][j] == number) {
                        marked[i][j] = true;
                        marked_total += number;
                    }
                }
            }
        }
        last_number = number;
    }

    bool has_row() {
        for (size_t i = 0; i < 5; i++) {
            bool row = true;
            for (size_t j = 0; j < 5; j++) {
                row = row && marked[i][j];
            }
            if (row) return true;
        }
        return false;
    }

    bool has_column() {
        for (size_t j = 0; j < 5; j++) {
            bool column = true;
            for (size_t i = 0; i < 5; i++) {
                column = column && marked[i][j];
            }
            if (column) return true;
        }
        return false;
    }

    int bingo() {
        if (has_row() || has_column()) {
            return (total - marked_total) * last_number;
        }
        return 0;
    }
};

vector<int> read_numbers() {
    string input;
    vector<int> numbers;

    getline(cin, input);
    stringstream ss(input);

    for (int i; ss >> i;) {
        numbers.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    return numbers;
}

Card read_card() {
    string line;
    int numbers[5][5];
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            cin >> numbers[i][j];
        }
    }

    return Card(numbers);
}

vector<Card> read_cards() {
    string input;
    vector<Card> temp{};
    vector<Card> cards{};

    while (getline(cin, input) && cin.peek() != EOF) {
        cards.push_back(read_card());
    }
    return cards;
}

bool has_bingo(Card card) {
    return card.bingo() != 0;
}

int part_two(vector<int> numbers, vector<Card> cards) {
    vector<Card> remaining_cards{cards};

    for (size_t i = 0; i < numbers.size(); i++) {
        int number = numbers[i];
        int last_bingo = 0;

        for (size_t j = 0; j < remaining_cards.size(); j++) {
            remaining_cards[j].mark(number);
            int bingo = remaining_cards[j].bingo();
            if (bingo) last_bingo = bingo;
        }

        remaining_cards.erase(remove_if(remaining_cards.begin(), remaining_cards.end(), has_bingo), remaining_cards.end());

        if (remaining_cards.empty()) {
            return last_bingo;
        }
    }
    return 0;
}

int part_one(vector<int> numbers, vector<Card> cards) {
    for (size_t i = 0; i < numbers.size(); i++) {
        int number = numbers[i];

        for (size_t j = 0; j < cards.size(); j++) {
            cards[j].mark(number);
            int bingo_total = cards[j].bingo();
            if (bingo_total) {
                return bingo_total;
            }
        }
    }
    return 0;
}

int main() {
    auto numbers = read_numbers();
    auto cards = read_cards();

    cout << "Nr of cards: " << cards.size() << endl;

    int one = part_one(numbers, cards);
    int two = part_two(numbers, cards);

    cout << "Part 1: " << one << endl;
    cout << "Part 2: " << two << endl;

    return 0;
}