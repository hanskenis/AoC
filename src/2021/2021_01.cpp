#include <bits/stdc++.h>

using namespace std;

int part_one(vector<int> input)
{
    int previous_depth = input[0];
    int increased{};

    for (size_t i = 1; i < input.size(); i++)
    {
        if (input[i] > previous_depth)
        {
            increased++;
        }
        previous_depth = input[i];
    }
    return increased;
}

int part_two(vector<int> input)
{
    int increased{};
    int previous_depth = input[2] + input[1] + input[0];

    for (size_t i = 3; i < input.size(); i++)
    {
        int depth = input[i] + input[i - 1] + input[i - 2];
        if (depth > previous_depth)
        {
            increased++;
        }
        previous_depth = depth;
    }

    return increased;
}

int main()
{
    vector<int> measurements{};
    int measurement{};
    while (cin >> measurement)
    {
        measurements.push_back(measurement);
    }

    cout << "part one: " << part_one(measurements) << endl;
    cout << "part two: " << part_two(measurements) << endl;

    return 0;
}