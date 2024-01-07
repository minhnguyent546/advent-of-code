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
    const int times = 5;

    string s;
    long long res = 0;
    while (getline(cin, s)) {
        string segments_str = s.substr(s.find(' ') + 1);
        s = s.substr(0, s.find(' '));

        string ns = "";
        string nsegments_str = "";
        for (int i = 0; i < times; ++i) {
            if (i > 0) {
                ns += '?';
                nsegments_str += ',';
            }
            ns += s;
            nsegments_str += segments_str;
        } 
        s = ns;
        vector<int> segments = exact_numbers(str_split(nsegments_str, ","));
        int n = (int) s.size(), m = (int) segments.size();

        int last_hagtag = n - 1;
        while (last_hagtag >= 0 && s[last_hagtag] != '#') --last_hagtag;

        vector<int> cnt_diff(n + 1);
        for (int i = 0; i < n; ++i) {
            cnt_diff[i + 1] = cnt_diff[i] + (s[i] == '.');
        }   
        auto substring_valid = [&](int i, int j) {
            if (i > j) return false;
            return cnt_diff[j + 1] - cnt_diff[i] == 0;
        };

        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1));
        dp[0][0] = 1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '#') break;
            dp[i + 1][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            // at index i - 1 -> check if s[i - 1 + 1] = s[i] is not '#'
            if (i < n && s[i] == '#') continue;
            for (int j = 1; j <= m; ++j) {
                if (j == m && i - 1 < last_hagtag) continue;
                dp[i][j] = dp[i - 1][j];    
                int left = i - segments[j - 1] + 1;
                if (((j == 1 && left > 0) || (j > 1 && left - 2 >= 0)) &&
                    substring_valid(left - 1, i - 1) &&
                    (left - 2 < 0 || s[left - 2] != '#')
                ) {
                    dp[i][j] += (j == 1 ? dp[left - 1][j - 1] : dp[left - 2][j - 1]);
                }
            }
        }
        res += dp[n][m];
    }
    debug(elapsed_time());
    cout << res << '\n';
    return 0;
}
