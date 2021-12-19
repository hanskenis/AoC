#include <bits/stdc++.h>

using namespace std;

struct SnailfishNumber {
    int depth{};
    SnailfishNumber* parent{};
    variant<int, SnailfishNumber*> left{};
    variant<int, SnailfishNumber*> right{};

    SnailfishNumber(){};

    SnailfishNumber(SnailfishNumber* p, variant<int, SnailfishNumber*> l, variant<int, SnailfishNumber*> r) {
        parent = p;
        left = l;
        right = r;
    }

    SnailfishNumber* copy() {
        variant<int, SnailfishNumber*> newLeft;
        variant<int, SnailfishNumber*> newRight;
        auto result = new SnailfishNumber();
        if (holds_alternative<SnailfishNumber*>(left)) {
            newLeft = get<1>(left)->copy();
            get<1>(newLeft)->parent = result;
        } else {
            newLeft = get<0>(left);
        }

        if (holds_alternative<SnailfishNumber*>(right)) {
            newRight = get<1>(right)->copy();
            get<1>(newRight)->parent = result;
        } else {
            newRight = get<0>(right);
        }
        result->left = newLeft;
        result->right = newRight;
        return result;
    }

    long magnitude() {
        long ml{};
        long mr{};
        if (holds_alternative<int>(left)) {
            ml = 3 * get<int>(left);
        } else {
            auto nr = get<SnailfishNumber*>(left);
            ml = 3 * nr->magnitude();
        }

        if (holds_alternative<int>(right)) {
            mr = 2 * get<int>(right);
        } else {
            auto nr = get<SnailfishNumber*>(right);
            mr = 2 * nr->magnitude();
        }
        return ml + mr;
    }

    void display() {
        if (parent == NULL) cout << endl;
        cout << "[";

        if (holds_alternative<int>(left)) {
            cout << get<int>(left);
        } else {
            auto nr = get<SnailfishNumber*>(left);
            (*nr).display();
        }

        cout << ",";

        if (holds_alternative<int>(right)) {
            cout << get<int>(right);
        } else {
            auto nr = get<SnailfishNumber*>(right);
            (*nr).display();
        }

        cout << "]";

        if (parent == NULL) cout << endl;
    }

    void explode() {
        int l = get<int>(left);
        int r = get<int>(right);

        auto current = this;
        while (current->parent != NULL) {
            if (holds_alternative<int>(current->parent->left)) {
                current->parent->left = get<int>(current->parent->left) + l;
                break;
            } else if (get<1>(current->parent->left) == current) {
                current = current->parent;
            } else {
                current = get<1>(current->parent->left);
                while (holds_alternative<SnailfishNumber*>(current->right)) {
                    current = get<1>(current->right);
                }
                current->right = get<int>(current->right) + l;
                break;
            }
        }

        current = this;
        while (current->parent != NULL) {
            if (holds_alternative<int>(current->parent->right)) {
                current->parent->right = get<int>(current->parent->right) + r;
                break;
            } else if (get<1>(current->parent->right) == current) {
                current = current->parent;
            } else {
                current = get<1>(current->parent->right);
                while (holds_alternative<SnailfishNumber*>(current->left)) {
                    current = get<1>(current->left);
                }
                current->left = get<int>(current->left) + r;
                break;
            }
        }

        if (holds_alternative<SnailfishNumber*>(parent->left) && get<1>(parent->left) == this) {
            parent->left = 0;
        } else {
            parent->right = 0;
        }
    }

    bool reduce_explode() {
        stack<SnailfishNumber*> s{};
        s.push(this);
        this->depth = 0;
        while (!s.empty()) {
            auto nr = s.top();
            s.pop();

            if (nr->depth >= 4 && holds_alternative<int>(nr->left) && holds_alternative<int>(nr->right)) {
                nr->explode();
                return true;
            }

            if (holds_alternative<SnailfishNumber*>(nr->right)) {
                auto child = get<SnailfishNumber*>(nr->right);
                child->depth = nr->depth + 1;
                s.push(child);
            }
            if (holds_alternative<SnailfishNumber*>(nr->left)) {
                auto child = get<SnailfishNumber*>(nr->left);
                child->depth = nr->depth + 1;
                s.push(child);
            }
        }
        return false;
    }

    bool reduce_split() {
        if (holds_alternative<int>(left) && get<int>(left) >= 10) {
            int first = get<int>(left) / 2;
            int second = get<int>(left) - first;
            auto pair = new SnailfishNumber(this, first, second);
            this->left = pair;
            return true;
        } else if (holds_alternative<SnailfishNumber*>(left) && get<1>(left)->reduce_split()) {
            return true;
        }

        else if (holds_alternative<int>(right) && get<int>(right) >= 10) {
            int first = get<int>(right) / 2;
            int second = get<int>(right) - first;
            auto pair = new SnailfishNumber(this, first, second);
            this->right = pair;
            return true;
        } else if (holds_alternative<SnailfishNumber*>(right) && get<1>(right)->reduce_split()) {
            return true;
        }

        return false;
    }

    void reduce() {
        bool reduced = true;

        // this->display();

        while (reduced) {
            reduced = reduce_explode();
            if (!reduced) {
                reduced = reduce_split();
            }

            // this->display();
        }
    }

    SnailfishNumber* operator+(SnailfishNumber* other) {
        auto result = new SnailfishNumber(NULL, this, other);
        this->parent = result;
        other->parent = result;
        result->reduce();
        // result->display();
        return result;
    }
};

SnailfishNumber* parse(string line) {
    SnailfishNumber* root = new SnailfishNumber();
    SnailfishNumber* current = root;
    bool parsingLeft = true;

    for (auto&& c : line.substr(1, string::npos)) {
        if (c == '[') {
            SnailfishNumber* nr = new SnailfishNumber();
            if (parsingLeft)
                current->left = nr;
            else
                current->right = nr;

            nr->parent = current;
            current = nr;
            parsingLeft = true;
        } else if (c == ',') {
            parsingLeft = false;
        } else if (c == ']') {
            parsingLeft = true;
            if (current == root)
                return root;
            else {
                current = current->parent;
            }
        } else {
            int value = c - '0';
            if (parsingLeft)
                current->left = value;
            else
                current->right = value;
        }
    }

    throw;
}

long part1(vector<SnailfishNumber*> numbers) {
    auto result = accumulate(numbers.begin() + 1,
                             numbers.end(),
                             numbers[0],
                             [](SnailfishNumber* acc, SnailfishNumber* nr) { return *acc + nr; });

    result->display();

    return result->magnitude();
}

long part2(vector<SnailfishNumber*> numbers) {
    long result{};
    long sum{};
    SnailfishNumber* first;
    SnailfishNumber* second;
    for (size_t i = 0; i < numbers.size(); i++) {
        for (size_t j = 0; j < numbers.size(); j++) {
            if (i != j) {
                sum = (*(numbers[i]->copy()) + numbers[j]->copy())->magnitude();
                result = max(sum, result);
                sum = (*(numbers[j]->copy()) + numbers[i]->copy())->magnitude();
                result = max(sum, result);
            }
        }
    }
    return result;
}

int main() {
    string line;
    vector<SnailfishNumber*> numbers1{};
    vector<SnailfishNumber*> numbers2{};
    while (getline(cin, line)) {
        auto nr = parse(line);
        numbers1.push_back(nr);
        numbers2.push_back(nr->copy());
    }

    cout << "Part1: " << part1(numbers1) << endl;
    cout << "Part2: " << part2(numbers2) << endl;

    return 0;
}