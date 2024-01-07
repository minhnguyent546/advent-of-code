/**            
 * author      minhnguyent546
 * created_at  Sun, 2024-01-07 22:09:05
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

const int diff_exactly = 1;

int solve(const vector<string> &grid) {
    int n = (int) grid.size();
    for (int i = n - 1; i >= 0; --i) {
        int range = i + 1;
        if (range & 1) continue;
        int cnt_diff = 0;
        for (int k = 0; k < range / 2; ++k) {
            for (int z = 0; z < (int) grid[k].size(); ++z) {
                cnt_diff += (grid[k][z] != grid[i - k][z]);
            }
        }
        if (cnt_diff == diff_exactly) return (i + 1) / 2;
    }
    for (int i = 0; i < n; ++i) {
        int range = n - i;
        if (range & 1) continue;
        int cnt_diff = 0;
        for (int k = 0; k < range / 2; ++k) {
            for (int z = 0; z < (int) grid[k].size(); ++z) {
                cnt_diff += (grid[i + k][z] != grid[n - 1 - k][z]);
            }
        }
        if (cnt_diff == diff_exactly) return i + range / 2;
    }
    // not found
    return 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    long long res;
    while (true) {
        vector<string> grid;
        string bar;
        while (getline(cin, bar)) {
            if (bar.empty()) break;
            grid.emplace_back(bar);
        }
        if (grid.empty()) break;
        int n = (int) grid.size(), m = (int) grid.back().size();
        vector<string> transposed(m);
        for (int c = 0; c < m; ++c) {
            transposed[c] = string(n, '@');
            for (int r = 0; r < n; ++r) {
                transposed[c][r] = grid[r][c];
            }
        }
        res += 100 * solve(grid);
        res += solve(transposed);
    }
    cout << res << '\n';

    return 0;
}
