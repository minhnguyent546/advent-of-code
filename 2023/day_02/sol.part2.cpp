/**            
 * author      minhnguyent546
 * created_at  Mon, 2024-01-01 21:29:47
 **/           
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "cp/debug.h"
#else
#define debug(...)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = (int) 1e9 + 7;
const int INF = 0x3f3f3f3f;

vector<string> str_split(const string &str, char delimiter = ' ') {
    vector<string> res;
    int n = (int) str.size();
    for (int i = 0; i < n; ++i) {
        if (str[i] == delimiter) continue;
        int j = i - 1;
        while (j + 1 < n && str[j + 1] != delimiter) {
            ++j;
        }
        res.push_back(str.substr(i, j - i + 1));
        i = j;
    }
    return res;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    map<char, int> has;
    has['r'] = 12;
    has['g'] = 13;
    has['b'] = 14;
    long long tot = 0;
    string bar;
    while (getline(cin, bar)) {
        bar = str_split(bar, ':')[1];
        bar.erase(bar.begin());
        vector<string> arr = str_split(bar, ';');
        map<char, int> max_f;
        for (const string &s : arr) {
            vector<string> brr = str_split(s, ',');
            for (const string &ss : brr) {
                vector<string> each = str_split(ss, ' ');
                assert((int) each.size() == 2);
                int num = stoi(each[0]);
                char which = each[1][0];
                if (!max_f.count(which) || num > max_f[which]) {
                    max_f[which] = num;
                }
            }
        }
        long long cur = 1;
        for (auto [ch, f] : max_f) {
            cur *= f;
        }
        tot += cur;
    }
    cout << tot << '\n';

    return 0;
}
