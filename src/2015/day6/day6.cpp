#include <bits/stdc++.h>

using namespace std;

enum Command
{
    turnOn,
    turnOff,
    toggle
};

class PartOne
{
    bool lights[1000][1000];

public:
    void handleCommand(Command command, int i, int j, int k, int l)
    {
        for (size_t x = i; x <= k; x++)
        {
            for (size_t y = j; y <= l; y++)
            {
                switch (command)
                {
                case turnOn:
                    lights[x][y] = true;
                    break;
                case turnOff:
                    lights[x][y] = false;
                    break;
                case toggle:
                    lights[x][y] = !lights[x][y];
                    break;
                default:
                    break;
                }
            }
        }
    }

    int howManyLit()
    {
        int total = 0;
        for (size_t i = 0; i < 1000; i++)
        {
            for (size_t j = 0; j < 1000; j++)
            {
                if (lights[i][j] == true)
                {
                    total++;
                }
            }
        }

        return total;
    }
};

class PartTwo
{
    int lights[1000][1000];

public:
    void handleCommand(Command command, int i, int j, int k, int l)
    {
        for (size_t x = i; x <= k; x++)
        {
            for (size_t y = j; y <= l; y++)
            {
                switch (command)
                {
                case turnOn:
                    lights[x][y]++;
                    break;
                case turnOff:
                    lights[x][y] = max(0, lights[x][y] - 1);
                    break;
                case toggle:
                    lights[x][y] = lights[x][y] + 2;
                    break;
                default:
                    break;
                }
            }
        }
    }

    int totalBrightness()
    {
        int total = 0;
        for (size_t i = 0; i < 1000; i++)
        {
            for (size_t j = 0; j < 1000; j++)
            {
                total += lights[i][j];
            }
        }

        return total;
    }
};

int main()
{
    string instruction;
    PartOne partOne{};
    PartTwo partTwo{};

    while (getline(cin, instruction))
    {
        stringstream ss(instruction);
        string word;
        Command command;
        ss >> word;
        if (word == "toggle")
        {
            command = toggle;
        }
        else
        {
            ss >> word;
            if (word == "on")
            {
                command = turnOn;
            }
            else
            {
                command = turnOff;
            }
        }
        ss >> word;
        int i, j, k, l;
        size_t index = word.find(',');
        i = stoi(word.substr(0, index));
        j = stoi(word.substr(index + 1));
        ss >> word; // through
        ss >> word;
        index = word.find(',');
        k = stoi(word.substr(0, index));
        l = stoi(word.substr(index + 1));
        partOne.handleCommand(command, i, j, k, l);
        partTwo.handleCommand(command, i, j, k, l);
    }

    cout << "Part 1: " << partOne.howManyLit() << endl;
    cout << "Part 2: " << partTwo.totalBrightness() << endl;

    return 0;
}