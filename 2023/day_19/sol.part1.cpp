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
    vector<string> ratings;
    while (getline(cin, bar)) {
        if (bar.empty()) break;
        workflows.emplace_back(bar);
    }
    while (getline(cin, bar)) {
        ratings.emplace_back(bar.substr(1, bar.size() - 1));
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

    long long sum = 0;
    map<char, int> vals;
    for (const string &rating : ratings) {
        vector<string> splited = str_split(rating, ",");
        for (const string &c : splited) {
            vals[c[0]] = stoi(c.substr(2));
        }
        string cur_key = "in";
        while (cur_key != "R" && cur_key != "A") {
            auto& condition_arr = conditions[cur_key];
            bool meet = false;
            for (int i = 0; i < (int) condition_arr.size() - 1; ++i) {
                if (condition_arr[i].type == '<' &&
                    vals[condition_arr[i].category] < condition_arr[i].num) {
                    cur_key = condition_arr[i].key;
                    meet = true;
                    break;
                }
                else if (condition_arr[i].type == '>' &&
                    vals[condition_arr[i].category] > condition_arr[i].num) {
                    cur_key = condition_arr[i].key;
                    meet = true;
                    break;
                }
            }
            if (!meet) cur_key = condition_arr.back().key;
        }
        if (cur_key == "A") {
            for (char ch : "xmas") sum += vals[ch];
        }
    }   
    cout << sum << '\n';
    return 0;
}
