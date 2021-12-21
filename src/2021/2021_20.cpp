#include <bits/stdc++.h>

using namespace std;

typedef pair<vector<vector<bool>>, bool> Image;

vector<bool> algorithm{};

bool pixel(const vector<bool>& input) {
    unsigned n{};
    for (auto&& b : input) {
        n <<= 1;
        n |= b;
    }

    return algorithm[n];
}

bool bit(const Image& image, int i, int j) {
    if (i < 0) return image.second;
    if (i > image.first.size() - 1) return image.second;
    if (j < 0) return image.second;
    if (j > image.first.size() - 1) return image.second;

    return image.first[i][j];
}

bool normal_pixel(const Image& image, int i, int j) {
    vector<bool> bits{};
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            bits.push_back(bit(image, i + di, j + dj));
        }
    }
    return pixel(bits);
}

bool infinite_pixel(bool infinite) {
    vector<bool> pixels;
    for (size_t i = 0; i < 9; i++) {
        pixels.push_back(infinite);
    }
    return pixel(pixels);
}

Image enhance(const Image& image) {
    int height = image.first.size();
    int width = image.first[0].size();
    bool infinite = infinite_pixel(image.second);
    vector<vector<bool>> enhanced{};
    for (int i = 0; i < height + 4; i++) {
        enhanced.push_back(vector<bool>());
        for (int j = 0; j < width + 4; j++) {
            enhanced[i].push_back(normal_pixel(image, i - 2, j - 2));
        }
    }

    return Image(enhanced, infinite);
}

void display(const Image& image) {
    cout << endl;
    for (size_t i = 0; i < image.first.size(); i++) {
        for (size_t j = 0; j < image.first[i].size(); j++) {
            char c = image.first[i][j] ? '#' : '.';
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
}

int count(const Image& image) {
    int result{};
    for (size_t i = 0; i < image.first.size(); i++) {
        for (size_t j = 0; j < image.first[i].size(); j++) {
            if (image.first[i][j]) result++;
        }
    }
    return result;
}

auto part2(const Image& image) {
    Image enhanced = image;
    for (size_t i = 0; i < 50; i++) {
        enhanced = enhance(enhanced);
    }

    display(enhanced);

    return count(enhanced);
}

auto part1(const Image& image) {
    Image enhanced = image;
    for (size_t i = 0; i < 2; i++) {
        enhanced = enhance(enhanced);
    }

    return count(enhanced);
}

vector<bool> parse(string input) {
    vector<bool> result{};
    for (auto&& c : input) {
        bool bit = c == '.' ? 0 : 1;
        result.push_back(bit);
    }
    return result;
}

int main() {
    string input;
    cin >> input;

    algorithm = parse(input);

    vector<vector<bool>> image;

    while (getline(cin, input)) {
        if (!input.empty())
            image.push_back(parse(input));
    }

    // cout << "Part1: " << part1(Image(image, false)) << endl;
    cout << "Part2: " << part2(Image(image, false)) << endl;

    return 0;
}