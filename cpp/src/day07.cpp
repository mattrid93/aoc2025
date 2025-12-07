#include "common.hpp"

const auto INPUT_FILE = "../inputs/day07.txt";

using namespace std;

using int_t = long;
using Input = vector<string>;

Input parse_input() {
    auto infile = ifstream(INPUT_FILE);
    string line;
    Input input;
    while (getline(infile, line)) {
        if (!line.empty()) {
            input.push_back(line);
        }
    }
    return input;
}

pair<int_t, int_t> solve(const Input& input) {
    int_t p1_result = 0;

    set<int_t> beams;
    for (const auto& line : input) {
        if (beams.empty()) {
            beams.insert(line.find('S'));
        }
        else {
            set<int_t> new_beams;
            for (auto b : beams) {
                if (line.at(b) == '^') {
                    p1_result++;
                    new_beams.insert(b-1);
                    new_beams.insert(b+1);
                }
                else {
                    new_beams.insert(b);
                }
            }
            beams = new_beams;
        }
    }
    
    vector<int_t> timelines(input.front().size(), 0);
    bool first = true;
    for (const auto& line : input) {
        if (first) {
            timelines.at(line.find('S')) = 1;
            first = false;
        }
        else {
            vector<int_t> new_timelines(timelines.size(), 0);
            for (auto b = 0; b < timelines.size(); b++) {
                auto t = timelines.at(b);
                if (t > 0) {
                    if (line.at(b) == '^') {
                        new_timelines.at(b-1) += t;
                        new_timelines.at(b+1) += t;
                    }
                    else {
                        new_timelines.at(b) += t;
                    }
                }
            }
            timelines = new_timelines;
        }
    }
    int_t p2_result = reduce(timelines.begin(), timelines.end());

    return {p1_result, p2_result};
}

int main() {
    const auto input = parse_input();
    const auto [p1, p2] = solve(input);
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
