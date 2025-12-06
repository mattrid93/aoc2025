#include "common.hpp"

const auto INPUT_FILE = "../inputs/day06.txt";

using namespace std;

using int_t = long;
using Input = vector<pair<vector<int_t>, bool>>;

Input parse_input() {
    auto infile = ifstream(INPUT_FILE);
    string line;
    bool l1 = true;
    vector<pair<vector<int_t>, bool>> input;
    while (getline(infile, line)) {
        istringstream iss(line);
        if (l1) {
            int_t num;
            while (iss >> num) {
                input.push_back({{num}, true});
            }
            l1 = false;
        }
        else {
            if (line.find("*") != string::npos) {
                size_t i = 0;
                string op;
                while (iss >> op) {
                    input.at(i).second = op == "*";
                    i++;
                }
            }
            else {
                size_t i = 0;
                int_t num;
                while (iss >> num) {
                    input.at(i).first.push_back(num);
                    i++;
                }
            }
        }
    }
    return input;
}

pair<int_t, int_t> solve(const Input& input) {
    int_t p1_result = 0;
    int_t p2_result = 0;

    for (const auto& [nums, mult] : input) {
        if (mult) {
            p1_result += accumulate(nums.begin(), nums.end(), 1.0, multiplies<int_t>());
        }
        else {
            p1_result += accumulate(nums.begin(), nums.end(), 0.0, plus<int_t>());
        }
    }

    return {p1_result, p2_result};
}

int main() {
    const auto input = parse_input();
    const auto [p1, p2] = solve(input);
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
