#include <bits/stdc++.h>
#include "day1_input.cpp"

int upOrDown(char &c)
{
    switch (c)
    {
    case '(':
        return 1;

    case ')':
        return -1;

    default:
        return 0;
    }
}

int part1()
{
    int floor = 0;
    for (uint c = 0; c < input.length(); c++)
    {
        floor += upOrDown(input[c]);
    }

    return floor;
}

int part2()
{
    int floor = 0;
    for (uint c = 0; c < input.length(); c++)
    {
        floor += upOrDown(input[c]);

        if (floor == -1)
        {
            return c + 1;
        }
    }

    return 0;
}

int main()
{
    std::cout << "output part 1: " << part1() << std::endl;
    std::cout << "output part 2: " << part2() << std::endl;

    return 0;
}
