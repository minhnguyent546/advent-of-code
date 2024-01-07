/**            
 * author      minhnguyent546
 * created_at  Fri, 2024-01-05 21:50:34
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int times = 1000000;

    vector<string> arr;
    string bar;
    while (cin >> bar) {
        arr.emplace_back(bar);
    }
    int n = (int) arr.size(), m = (int) arr.front().size();
    vector<bool> row_empty(n, true), col_empty(m, true);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (arr[r][c] != '.') {
                row_empty[r] = false;
                col_empty[c] = false;
            }
        }
    }
    vector<int> pref_row(n + 1), pref_col(m + 1);
    for (int r = 0; r < n; ++r) {
        pref_row[r + 1] = pref_row[r] + row_empty[r];
    }
    for (int c = 0; c < m; ++c) {
        pref_col[c + 1] = pref_col[c] + col_empty[c];
    }
    auto get_row = [&](int r, int rr) -> int {
        if (r > rr) swap(r, rr);
        return pref_row[rr + 1] - pref_row[r];
    };
    auto get_col = [&](int c, int cc) -> int {
        if (c > cc) swap(c, cc);
        return pref_col[cc + 1] - pref_col[c];
    };

    vector<pair<int, int>> gal;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (arr[r][c] == '#') {
                gal.emplace_back(r, c);
            }
        }
    }
    long long res = 0;
    int sz = (int) gal.size();
    for (int i = 0; i < sz; ++i) {
        for (int j = i + 1; j < sz; ++j) {
            int dist = abs(gal[i].first - gal[j].first) +
                    abs(gal[i].second - gal[j].second) +
                    1LL * (times - 1) * get_row(gal[i].first, gal[j].first) +
                    1LL * (times - 1) * get_col(gal[i].second, gal[j].second);
            res += dist;
        }
    }
    cout << res << '\n';
    return 0;
}
