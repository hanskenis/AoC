#include <bits/stdc++.h>

using namespace std;
const size_t NR_OF_BITS = 12;

void count_appearance(vector<bitset<NR_OF_BITS>> input, int count[NR_OF_BITS])
{
    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t j = 0; j < NR_OF_BITS; j++)
        {
            if (input[i].test(j))
                count[j]++;
        }
    }
}

unsigned long part_one(vector<bitset<NR_OF_BITS>> input)
{
    bitset<NR_OF_BITS> gamma{};
    bitset<NR_OF_BITS> epsilon{};
    int count[NR_OF_BITS]{};

    count_appearance(input, count);

    int total = input.size();
    for (size_t i = 0; i < NR_OF_BITS; i++)
    {
        if (count[i] > total / 2)
        {
            gamma.set(i);
        }
        else
        {
            epsilon.set(i);
        }
    }

    unsigned long result = gamma.to_ulong() * epsilon.to_ulong();
    return result;
}

unsigned long least_common(vector<bitset<NR_OF_BITS>> input)
{
    vector<bitset<NR_OF_BITS>> result{input};

    for (size_t i = NR_OF_BITS - 1; i >= 0; i--)
    {
        vector<bitset<NR_OF_BITS>> rest{};
        int count[NR_OF_BITS]{};
        count_appearance(result, count);
        int total = result.size();
        bool set = !(count[i] >= (double)total / 2);
        for (size_t j = 0; j < total; j++)
        {
            if (result[j].test(i) == set)
            {
                rest.push_back(result[j]);
            }
        }

        result = rest;

        if (result.size() == 1)
        {
            return result[0].to_ulong();
        }
    }

    return 0;
}

unsigned long most_common(vector<bitset<NR_OF_BITS>> input)
{
    vector<bitset<NR_OF_BITS>> result{input};

    for (size_t i = NR_OF_BITS - 1; i >= 0; i--)
    {
        vector<bitset<NR_OF_BITS>> rest{};
        int count[NR_OF_BITS]{};
        count_appearance(result, count);
        int total = result.size();
        bool set = count[i] >= (double)total / 2;
        for (size_t j = 0; j < total; j++)
        {
            if (result[j].test(i) == set)
            {
                rest.push_back(result[j]);
            }
        }

        result = rest;

        if (result.size() == 1)
        {
            return result[0].to_ulong();
        }
    }

    return 0;
}

unsigned long part_two(vector<bitset<NR_OF_BITS>> input)
{
    unsigned long o = most_common(input);
    unsigned long s = least_common(input);

    return o * s;
}

int main()
{
    bitset<NR_OF_BITS> line;
    vector<bitset<NR_OF_BITS>> input;

    while (cin >> line)
    {
        input.push_back(line);
    }

    cout << "Part 1: " << part_one(input) << endl;
    cout << "Part 2: " << part_two(input) << endl;

    return 0;
}