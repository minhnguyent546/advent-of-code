/**            
 * author      minhnguyent546
 * created_at  Sun, 2024-01-14 00:46:38
 **/           
#include <bits/stdc++.h>
#include "../lib/functions.h"
using namespace std;

#ifdef LOCAL
#include "cp/debug.h"
#else
#define debug(...)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = (int) 1e9 + 7;
const int INF = 0x3f3f3f3f;

const int MIN_V = 1, MAX_V = 4000;
const string xmas = "xmas";

struct Condition {
    char category;
    char type;
    int num;
    string key;
    Condition() {}
    Condition(const string &str) {
        size_t colon_pos = str.find(':');
        if (colon_pos == str.npos) {
            key = str;
            type = '@';
        }
        else {
            category = str[0];
            type = str[1];
            num = stoi(str.substr(2, colon_pos - 2));
            key = str.substr(colon_pos + 1);
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string bar;
    vector<string> workflows;
    while (getline(cin, bar)) {
        if (bar.empty()) break;
        workflows.emplace_back(bar);
    }

    map<string, vector<Condition>> conditions;
    for (const string &workflow : workflows) {
        string key = workflow.substr(0, workflow.find('{'));
        string content = workflow.substr(workflow.find('{') + 1);
        content.pop_back();
        vector<string> splited = str_split(content, ",");
        for (const string &foo : splited) {
            conditions[key].emplace_back(foo);
        }
    }

    auto walk = [&](auto self, string key, map<char, pair<int, int>> ranges) -> long long {
        if (key == "R") return 0;
        if (key == "A") {
            long long prod = 1;
            for (auto [ch, range] : ranges) {
                assert(range.first <= range.second);
                prod *= (range.second - range.first + 1);
            }
            return prod;
        }
        long long total = 0;
        auto& condition_arr = conditions[key];
        bool has_zero_range = false;
        for (int i = 0; i < (int) condition_arr.size() - 1; ++i) {
            auto [category, type, num, next_key] = condition_arr[i];
            auto [left, right] = ranges[category];
            pair<int, int> T, F;
            if (type == '<') {
                T = {left, num - 1};
                F = {num, right};
            }
            else { // '>'
                T = {num + 1, right};
                F = {left, num};
            }
            if (T.first <= T.second) {
                auto nranges = ranges;
                nranges[category] = T;
                total += self(self, next_key, nranges);
            }
            if (F.first <= F.second) {
                ranges[category] = F;
            } else {
                has_zero_range = true;
                break;
            }
        }
        if (!has_zero_range) {
            total += self(self, condition_arr.back().key, ranges);
        }
        return total;
    };

    map<char, pair<int, int>> initial_ranges;
    for (char ch : xmas) {
        initial_ranges[ch] = {MIN_V, MAX_V};
    }
    long long answer = walk(walk, "in", initial_ranges);
    cout << answer << '\n';
    return 0;
}
