/**            
 * author      minhnguyent546
 * created_at  Sat, 2024-01-06 18:54:08
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


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    long long res = 0;
    while (getline(cin, s)) {
        vector<int> segments = exact_numbers(str_split(s.substr(s.find(' ') + 1), ","));
        int total = accumulate(segments.begin(), segments.end(), 0);
        s = s.substr(0, s.find(' '));
        int n = (int) s.size();
        int question_mark = count(s.begin(), s.end(), '?');
        int has = count(s.begin(), s.end(), '#');
        int m = (1 << question_mark);
        int ways = 0;
        for (int mask = 0; mask < m; ++mask) {
            int ones = __builtin_popcount(mask);
            if (has + ones != total) continue;
            string cur = s;
            for (int i = 0, j = 0; i < n; ++i) {
                if (cur[i] != '?') continue;
                if (mask & (1 << j)) {
                    cur[i] = '#';
                }
                ++j;
            }
            vector<int> nums;
            for (int i = 0; i < n; ++i) {
                if (cur[i] != '#') continue;
                int j = i;
                while (j + 1 < n && cur[j + 1] == '#') ++j;
                nums.push_back(j - i + 1);
                i = j;
            }
            ways += (nums == segments);
        }
        res += ways;
    }
    debug(elapsed_time());
    cout << res << '\n';
    return 0;
}
