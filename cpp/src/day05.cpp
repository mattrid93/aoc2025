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
    auto intervals = Intervals();
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
    auto [intervals, ids] = input;
    int_t p1_result = 0;
    int_t p2_result = 0;

    auto starts = vector<int_t>();
    auto ends = vector<int_t>();
    int_t prev = 0;
    for (auto i : intervals) {
        starts.push_back(i.first);
        ends.push_back(i.second);
        p2_result += i.second - i.first + 1;
    }

    for (auto ingredient : ids) {
        if (ingredient < starts.front() || ingredient > ends.back()) {
            continue;
        }
        auto idx = lower_bound(ends.begin(), ends.end(), ingredient);
        if (ingredient >= starts.at(idx - ends.begin())) {
            p1_result++;
        }
    }

    return make_pair(p1_result, p2_result);
}

int main() {
    const auto input = parse_input();
    const auto [p1, p2] = solve(input);
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
