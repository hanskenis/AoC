#include <iostream>

using namespace std;

bool hasThreeVowels(string input)
{
    int vowels{0};
    for (size_t i = 0; i < input.length(); i++)
    {
        char c = input[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            vowels++;
        }
    }
    return vowels > 2;
}

bool hasDoubleLetter(string input)
{
    char c1 = input[0];
    char c2{};
    for (size_t i = 1; i < input.length(); i++)
    {
        c2 = input[i];
        if (c1 == c2)
        {
            return true;
        }
        c1 = c2;
    }
    return false;
}

bool noDisallowedSubstring(string input)
{
    return input.find("ab") == string::npos &&
           input.find("cd") == string::npos &&
           input.find("pq") == string::npos &&
           input.find("xy") == string::npos;
}

bool isNiceStringPart1(string input)
{
    return hasThreeVowels(input) && hasDoubleLetter(input) && noDisallowedSubstring(input);
}

bool hasPairTwice(string input)
{
    for (size_t i = 0; i < input.length() - 1; i++)
    {
        string pair = input.substr(i, 2);
        if (input.substr(i + 2).find(pair) != string::npos)
        {
            return true;
        }
    }
    return false;
}

bool hasRepeatingLetter(string input)
{
    for (size_t i = 2; i < input.length(); i++)
    {
        if (input[i] == input[i - 2])
        {
            return true;
        }
    }
    return false;
}

bool isNiceStringPart2(string input)
{
    return hasPairTwice(input) && hasRepeatingLetter(input);
}

int main()
{
    int niceStringsPart1 = 0;
    int niceStringsPart2 = 0;
    string line;
    while (getline(cin, line))
    {
        if (isNiceStringPart1(line))
        {
            niceStringsPart1++;
        }
        if (isNiceStringPart2(line))
        {
            niceStringsPart2++;
        }
    }
    cout << "nice strings part1: " << niceStringsPart1 << endl;
    cout << "nice strings part2: " << niceStringsPart2 << endl;
    return 0;
}