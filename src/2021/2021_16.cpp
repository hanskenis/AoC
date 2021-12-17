#include <bits/stdc++.h>

using namespace std;

struct Packet {
    int version{};
    int type{};
    unsigned long literal{};
    vector<Packet> sub_packets{};

    Packet(int v, int t, unsigned long value) {
        version = v;
        type = t;
        literal = value;
    }

    Packet(int v, int t, vector<Packet> packets) {
        version = v;
        type = t;
        sub_packets = packets;
    }

    int sum_of_version() {
        int sum{};
        if (type == 4) {
            return version;
        } else {
            return accumulate(sub_packets.begin(), sub_packets.end(), version, [](int acc, Packet& packet) { return acc + packet.sum_of_version(); });
        }
    }

    vector<unsigned long> values() {
        vector<unsigned long> values{};
        transform(sub_packets.begin(), sub_packets.end(), back_inserter(values), [](Packet& packet) { return packet.value(); });
        return values;
    }

    unsigned long value() {
        unsigned long result{};
        switch (type) {
            case 0:
                result = accumulate(sub_packets.begin(), sub_packets.end(), 0UL, [](unsigned long acc, Packet& packet) { return acc + packet.value(); });
                break;
            case 1:
                result = accumulate(sub_packets.begin(), sub_packets.end(), 1UL, [](unsigned long acc, Packet& packet) { return acc * packet.value(); });
                break;
            case 2: {
                auto v = values();
                result = *(min_element(v.begin(), v.end()));
                break;
            }
            case 3: {
                auto v = values();
                result = *(max_element(v.begin(), v.end()));
                break;
            }

            case 4:
                result = literal;
                break;

            case 5: {
                result = sub_packets[0].value() > sub_packets[1].value() ? 1 : 0;
                break;
            }
            case 6: {
                result = sub_packets[0].value() < sub_packets[1].value() ? 1 : 0;
                break;
            }
            case 7: {
                result = sub_packets[0].value() == sub_packets[1].value() ? 1 : 0;
                break;
            }

            default:
                throw;
        }
        cout << result << endl;
        return result;
    }
};

vector<bool> hex_to_binary(const string& input) {
    vector<bool> result{};

    for (auto&& h : input) {
        stringstream ss;
        ss << hex << h;
        unsigned n;
        ss >> n;
        bitset<4> b(n);

        for (int i = 3; i >= 0; i--) {
            result.push_back(b[i]);
        }
    }
    return result;
}

long decode(vector<bool> data, int& i, int length) {
    long n{};
    int start = i;
    while (i < start + length) {
        n <<= 1;
        n |= data[i] ? 1 : 0;
        i++;
    }

    return n;
}

long literal(vector<bool> data, int& i) {
    long n{};
    bool keepReading = data[i];
    while (keepReading) {
        i++;
        long nr = decode(data, i, 4);
        n <<= 4;
        n |= nr;
        keepReading = data[i];
    }
    i++;
    long nr = decode(data, i, 4);
    n <<= 4;
    n |= nr;

    return n;
}

Packet decode_to_packet(vector<bool> data, int& i) {
    auto version = decode(data, i, 3);
    auto type = decode(data, i, 3);

    //literal
    if (type == 4) {
        auto value = literal(data, i);
        return Packet(version, type, value);
    } else {
        // operator
        auto lengthType = decode(data, i, 1);
        if (lengthType == 0) {
            auto length = decode(data, i, 15);
            int end = i + length;
            vector<Packet> packets{};
            while (i < end) {
                packets.push_back(decode_to_packet(data, i));
            }
            return Packet(version, type, packets);
        } else {
            auto nrPackets = decode(data, i, 11);
            vector<Packet> packets{};
            for (size_t j = 0; j < nrPackets; j++) {
                packets.push_back(decode_to_packet(data, i));
            }
            return Packet(version, type, packets);
        }
    }
}

long part2(string input) {
    auto bin = hex_to_binary(input);

    int start = 0;

    auto packet = decode_to_packet(bin, start);

    return packet.value();
}

int part1(string input) {
    auto bin = hex_to_binary(input);
    int start = 0;

    auto packet = decode_to_packet(bin, start);

    return packet.sum_of_version();
}

int main() {
    string input;
    cin >> input;

    cout << "Part1: " << part1(input) << endl;
    cout << "Part2: " << part2(input) << endl;

    return 0;
}