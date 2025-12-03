#include "common.hpp"

const auto INPUT_FILE = "../inputs/day03.txt";

using namespace std;

auto split_digits(auto line) {
    auto result = vector<int>();
    for (auto c : line) {
        result.push_back(c - '0');
    }
    return result;
}

auto parse_input() {
    auto infile = ifstream(INPUT_FILE);
    auto input = vector<vector<int>>();
    string line;
    while (getline(infile, line)) {
        input.push_back(split_digits(line));
    }
    return input;
}

auto solve_p1(auto input) {
    auto result = 0;
    for (auto bank : input) {
        auto first = 0;
        auto second = 0;
        auto N = bank.size();
        for (auto i = 0; i < N; i++) {
            if (i < N - 1) {
                if (bank.at(i) > first) {
                    first = bank.at(i);
                    second = 0;
                }
                else {
                    second = max(second, bank.at(i));
                }
            }
            else {
                second = max(second, bank.at(i));
            }
        }
        result += 10 * first + second;
    }
    return result;
}

auto solve_p2(auto input) {
    size_t result = 0;

    auto argmax = [] (auto bank, auto start, auto stop) {
        auto max = 0;
        auto idx = -1;
        for (auto i = start; i < stop; i++) {
            if (bank.at(i) > max) {
                max = bank.at(i);
                idx = i;
            }
        }
        return make_pair(idx, max);
    };

    auto N = 12;
    for (auto bank : input) {
        auto start = 0;
        for (auto i = 0; i < N; i++) {
            auto [idx, max] = argmax(bank, start, bank.size() + i + 1 - N);
            start = idx + 1;
            result += max * pow(10, N-1-i);
        }
    }
    return result;
}

int main() {
    auto input = parse_input();
    auto p1 = solve_p1(input);
    auto p2 = solve_p2(input);
    cout << "Part 1: " << p1 << "\nPart 2: " << p2 << "\n";
}
