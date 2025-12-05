#include "common.hpp"

const auto INPUT_FILE = "../inputs/day05.txt";

using namespace std;

using int_t = long;
using Interval = pair<int_t, int_t>;
using Intervals = vector<Interval>;
using Ids = vector<int_t>;
using Input = pair<Intervals, Ids>;

Interval parse_interval(const string& line) {
    auto start = stol(line.substr(0, line.find('-')));
    auto end = stol(line.substr(line.find('-')+1, line.size()));
    return make_pair(start, end);
}

Intervals collapse_intervals(const Intervals& intervals) {
    Intervals collapsed{};
    if (intervals.empty()) {
        return collapsed;
    }
    size_t i = 0;
    auto [start, end] = intervals.front();
    while (i < intervals.size()) {
        if (intervals.at(i).first <= end + 1) {
            end = max(end, intervals.at(i).second);
        }
        else {
            collapsed.push_back(make_pair(start, end));
            start = intervals.at(i).first;
            end = intervals.at(i).second;
        }
        i++;
    }
    collapsed.push_back(make_pair(start, end));
    return collapsed;
}

Input parse_input() {
    auto infile = ifstream(INPUT_FILE);
    Intervals intervals;
    auto ids = Ids();
    string line;
    bool p1 = true;
    while (getline(infile, line)) {
        if (line.empty()) {
            p1 = false;
            continue;
        }
        if (p1) {
            intervals.push_back(parse_interval(line));
        }
        else {
            ids.push_back(stol(line));
        }
    }
    sort(intervals.begin(), intervals.end());
    sort(ids.begin(), ids.end());
    return make_pair(collapse_intervals(intervals), ids);
}

pair<int_t, int_t> solve(const Input& input) {
    const auto& [intervals, ids] = input;
    int_t p1_result = 0;
    int_t p2_result = 0;

    for (const auto& [start, end] : intervals) {
        p2_result += end - start + 1;
    }

    for (auto ingredient : ids) {
        if (ingredient < intervals.front().first || ingredient > intervals.back().second) {
            continue;
        }
        auto idx = lower_bound(
            intervals.begin(), intervals.end(), ingredient,
            [](const Interval& interval, int_t value) {
                return interval.second < value;
            }
        );
        if (idx != intervals.end() && ingredient >= idx->first) {
            p1_result++;
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
