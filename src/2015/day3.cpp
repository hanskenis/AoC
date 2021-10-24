#include <bits/stdc++.h>

using namespace std;

struct Point
{
    int x{0};
    int y{0};
    Point(){};
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

struct HouseTracker
{
    unordered_set<string> houses;

    void handleLocation(Point location)
    {
        houses.insert(ptos(location));
    }

    int nrHousesThatHavePresent()
    {
        return houses.size();
    }

private:
    string ptos(Point &point)
    {
        stringstream ss;
        ss << point.x << "," << point.y;
        return ss.str();
    }
};

Point getMove(char c)
{
    if (c == '>')
    {
        return Point(1, 0);
    }
    else if (c == '<')
    {
        return Point(-1, 0);
    }
    else if (c == '^')
    {
        return Point(0, -1);
    }
    else
    {
        return Point(0, 1);
    }
}

int part2()
{

    return 0;
}

int part2(string input)
{
    HouseTracker tracker = HouseTracker();
    Point santa = Point(0, 0);
    Point robo_santa = Point(0, 0);
    tracker.handleLocation(santa);
    for (uint i = 0; i < input.length(); i++)
    {
        Point move = getMove(input[i]);
        if (i % 2 == 0)
        {
            santa.x += move.x;
            santa.y += move.y;
            tracker.handleLocation(santa);
        }
        else
        {
            robo_santa.x += move.x;
            robo_santa.y += move.y;
            tracker.handleLocation(robo_santa);
        }
    }
    return tracker.nrHousesThatHavePresent();
}

int part1(string input)
{
    HouseTracker tracker = HouseTracker();
    Point location = Point(0, 0);
    tracker.handleLocation(location);

    for (uint i = 0; i < input.length(); i++)
    {
        Point move = getMove(input[i]);
        location.x += move.x;
        location.y += move.y;
        tracker.handleLocation(location);
    }

    return tracker.nrHousesThatHavePresent();
}

int main()
{
    string input;
    cin >> input;

    cout << "part 1: " << part1(input) << endl;
    cout << "part 2: " << part2(input) << endl;

    return 0;
}