#include <bits/stdc++.h>
#include <openssl/md5.h>

using namespace std;

// Print the MD5 sum as hex-digits.
void print_md5_sum(unsigned char *md)
{
    int i;
    for (i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", md[i]);
    }
}

bool startsWith6Zeroes(string key)
{
    return key[0] == '0' && key[1] == '0' && key[2] == '0' && key[3] == '0' && key[4] == '0' && key[5] == '0';
}

string ToHex(const unsigned char *s)
{
    ostringstream ret;

    for (string::size_type i = 0; i < MD5_DIGEST_LENGTH; ++i)
        ret << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << (int)s[i];

    return ret.str();
}

string md5(string key)
{
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)key.c_str(), key.length(), result);

    return ToHex(result);
}

int main()
{
    string input;
    cin >> input;
    int i = 1;
    while (true)
    {
        string key = input + to_string(i);
        string hash = md5(key);
        if (startsWith6Zeroes(hash))
        {
            cout << i << endl;
            break;
        }
        i++;
    }

    return 0;
}