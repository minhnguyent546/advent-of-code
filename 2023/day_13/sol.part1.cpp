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

int solve(const vector<string> &grid) {
    int n = (int) grid.size();
    for (int i = n - 1; i >= 0; --i) {
        int range = i + 1;
        if (range & 1) continue;
        bool is_palindrome = true;
        for (int k = 0; k < range / 2; ++k) {
            if (grid[k] != grid[i - k]) {
                is_palindrome = false;
                break;
            }
        }
        if (is_palindrome) return (i + 1) / 2;
    }
    for (int i = 0; i < n; ++i) {
        int range = n - i;
        if (range & 1) continue;
        bool is_palindrome = true;
        for (int k = 0; k < range / 2; ++k) {
            if (grid[i + k] != grid[n - 1 - k]) {
                is_palindrome = false;
                break;
            }
        }
        if (is_palindrome) return i + range / 2;
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
