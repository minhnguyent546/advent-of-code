/**            
 * author      minhnguyent546
 * created_at  Mon, 2024-01-08 12:48:35
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

/**
 * @brief tilt the matrix in north direction
 */
void tilt(vector<vector<char>> &grid) {
    int n = (int) grid.size(), m = (int) grid.back().size();
    for (int c = 0; c < m; ++c) {
        for (int i = 0, k = 0; i < n; ++i) {
            if (grid[i][c] != 'O') {
                if (grid[i][c] == '#') {
                    k = i + 1;
                }
                continue;
            }
            swap(grid[i][c], grid[k][c]);
            ++k;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string bar;
    vector<vector<char>> grid;
    while (cin >> bar) {
        grid.emplace_back(bar.size());
        for (int i = 0; i < (int) bar.size(); ++i) {
            grid.back()[i] = bar[i];
        }
    }
    int n = (int) grid.size(), m = (int) grid.back().size();
    tilt(grid);
    long long res = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == 'O') res += n - r;
        }
    }
    cout << res << '\n';

    return 0;
}
