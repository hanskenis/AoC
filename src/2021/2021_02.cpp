#include <bits/stdc++.h>

using namespace std;

struct SubmarineOne
{
    int x{};
    int y{};

    void handle_command(string command, int amount)
    {
        if (command == "forward")
            x += amount;
        if (command == "down")
            y += amount;
        if (command == "up")
            y -= amount;
    }
};

struct SubmarineTwo
{
    int aim{};
    int x{};
    int y{};

    void handle_command(string command, int amount)
    {
        if (command == "forward")
        {
            x += amount;
            y += amount * aim;
        }
        if (command == "down")
            aim += amount;
        if (command == "up")
            aim -= amount;
    }
};

int main()
{
    SubmarineOne sub_one{};
    SubmarineTwo sub_two{};
    string command;
    int amount;
    while (cin >> command >> amount)
    {
        sub_one.handle_command(command, amount);
        sub_two.handle_command(command, amount);
    }

    cout << "Part 1: " << sub_one.x * sub_one.y << endl;
    cout << "Part 2: " << sub_two.x * sub_two.y << endl;

    return 0;
}