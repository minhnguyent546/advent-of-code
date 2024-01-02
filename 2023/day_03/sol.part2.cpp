/**            
 * author      minhnguyent546
 * created_at  Tue, 2024-01-02 21:12:46
 **/           
#include <bits/stdc++.h>
#include <cctype>
using namespace std;

#ifdef LOCAL
#include "cp/debug.h"
#else
#define debug(...)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = (int) 1e9 + 7;
const int INF = 0x3f3f3f3f;

const char minchar = '0';
const char gear = '*';

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<string> arr;
    string foo;
    while (cin >> foo) {
        arr.push_back(foo);
    }
    int n = (int) arr.size(), m = (int) arr.back().size();
    int comp_cnt = 0;
    vector<vector<long long>> comp(n, vector<long long>(m));
    vector<vector<long long>> value_at(n, vector<long long>(m));
    auto valid = [&](int r, int c) -> bool {
        return (0 <= r && r < n && 0 <= c && c < m);
    };
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (!isdigit(arr[r][c])) continue;
            bool included = false;
            long long num = 0;
            int cur_c = c;
            while (cur_c < m && isdigit(arr[r][cur_c])) {
                num = num * 10 + (arr[r][cur_c] - minchar);
                if (!included) {
                    for (int dr = -1; dr <= 1; ++dr) {
                        for (int dc = -1; dc <= 1; ++dc) {
                            if (dr == 0 && dc == 0) continue;
                            int nr = r + dr;
                            int nc = cur_c + dc;
                            if (valid(nr, nc) && !isdigit(arr[nr][nc]) && arr[nr][nc] != '.') {
                                included = true;
                            }
                        }
                    }
                }
                ++cur_c;
            }
            if (included) {
                for (int i = c; i < cur_c; ++i) {
                    value_at[r][i] = num;
                    comp[r][i] = comp_cnt;
                } 
                ++comp_cnt;
            }
            c = cur_c - 1;
        }   
    }
    long long res = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (arr[r][c] != gear) continue;
            long long prod = 1, cnt = 0;
            set<int> seen;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr;
                    int nc = c + dc;
                    if (valid(nr, nc) && isdigit(arr[nr][nc]) && !seen.count(comp[nr][nc])) {
                        ++cnt;
                        seen.insert(comp[nr][nc]);
                        if (cnt <= 2) prod *= value_at[nr][nc];
                    }
                }
            }
            if (cnt == 2) res += prod;
        }
    }
    cout << res << '\n';
    return 0;
}
