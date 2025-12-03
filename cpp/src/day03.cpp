#include "common.hpp"

const auto INPUT_FILE = "../inputs/day03.txt";

using namespace std;

using Bank = vector<int>;
using Input = vector<Bank>;

Bank split_digits(const string& line) {
    auto result = Bank();
    result.reserve(line.size());
    for (auto c : line) {
        result.push_back(c - '0');
    }
    return result;
}

Input parse_input() {
    auto infile = ifstream(INPUT_FILE);
    auto input = Input();
    string line;
    while (getline(infile, line)) {
        input.push_back(split_digits(line));
    }
    return input;
}

size_t solve(const Input& input, const int digits) {
    size_t result = 0;

    auto argmax = [] (const Bank& bank, size_t start, size_t stop) {
        int max = 0;
        size_t idx = -1;
        for (auto i = start; i < stop; i++) {
            if (bank.at(i) > max) {
                max = bank.at(i);
                idx = i;
            }
        }
        return make_pair(idx, max);
    };

    for (auto bank : input) {
        auto start = 0;

        size_t factor = 1;
        for (auto _ : views::iota(1, digits)) factor *= 10;

        for (auto i = 0; i < digits; i++) {
            auto [idx, max] = argmax(bank, start, bank.size() + i + 1 - digits);
            start = idx + 1;
            result += max * factor;
            factor /= 10;
        }
    }
    return result;
}

int main() {
    const auto input = parse_input();
    const auto p1 = solve(input, 2);
    const auto p2 = solve(input, 12);
    cout << "Part 1: " << p1 << "\nPart 2: " << p2 << "\n";
}
