#include <bits/stdc++.h>
#include "day2_input.cpp"

using namespace std;

int surfaceArea(int l, int w, int h)
{
    return 2 * l * w + 2 * w * h + 2 * h * l;
}

int extra(int l, int w, int h)
{
    vector<int> mylist;
    mylist.push_back(l);
    mylist.push_back(w);
    mylist.push_back(h);
    sort(mylist.begin(), mylist.end());

    return mylist[0] *
           mylist[1];
}

int wrappingPaper(int l, int w, int h)
{
    return surfaceArea(l, w, h) + extra(l, w, h);
}

int shortestDistance(int l, int w, int h)
{
    vector<int> mylist;
    mylist.push_back(l);
    mylist.push_back(w);
    mylist.push_back(h);
    sort(mylist.begin(), mylist.end());

    return mylist[0] + mylist[0] +
           mylist[1] + mylist[1];
}

int bow(int l, int w, int h)
{
    return l * w * h;
}

int ribbon(int l, int w, int h)
{
    return shortestDistance(l, w, h) + bow(l, w, h);
}

int main()
{
    istringstream f(input);
    string line;
    int part1 = 0;
    int part2 = 0;
    while (std::getline(f, line))
    {
        int l = stoi(line.substr(0, line.find("x")));
        line.erase(0, line.find("x") + 1);
        int w = stoi(line.substr(0, line.find("x")));
        line.erase(0, line.find("x") + 1);
        int h = stoi(line.substr(0, line.find("x")));
        line.erase(0, line.find("x") + 1);

        part1 += wrappingPaper(l, w, h);
        part2 += ribbon(l, w, h);
    }

    std::cout << "output part 1: " << part1 << std::endl;
    std::cout << "output part 2: " << part2 << std::endl;

    return 0;
}
